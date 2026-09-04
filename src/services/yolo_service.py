import os
import sys
import glob
import ctypes
import site
import cv2
import numpy as np
from config import logger
import math
import time

# Preload CUDA 13 / 12 & cuDNN DLLs for PyTorch GPU
try:
    possible_dll_dirs = [
        r"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v13.3\bin\x64",
        r"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v13.3\bin",
        r"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.4\bin",
        r"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.1\bin",
    ]
    for sp in site.getsitepackages():
        nvidia_base = os.path.join(sp, "nvidia")
        if os.path.exists(nvidia_base):
            for pkg in os.listdir(nvidia_base):
                for sub in ["bin", "lib"]:
                    candidate = os.path.join(nvidia_base, pkg, sub)
                    if os.path.exists(candidate):
                        possible_dll_dirs.append(candidate)
        t_lib = os.path.join(sp, "torch", "lib")
        if os.path.exists(t_lib):
            possible_dll_dirs.append(t_lib)

    user_home = os.path.expanduser("~")
    global_py_pattern = os.path.join(user_home, "AppData", "Local", "Programs", "Python", "Python*", "Lib", "site-packages", "torch", "lib")
    for g_path in glob.glob(global_py_pattern):
        if os.path.exists(g_path) and g_path not in possible_dll_dirs:
            possible_dll_dirs.append(g_path)

    for ddir in possible_dll_dirs:
        if os.path.exists(ddir):
            # Prevent infinite PATH growth if module is re-evaluated
            if ddir not in os.environ.get("PATH", ""):
                os.environ["PATH"] = ddir + os.pathsep + os.environ.get("PATH", "")
            if hasattr(os, "add_dll_directory"):
                try:
                    os.add_dll_directory(ddir)
                except Exception:
                    pass

    critical_cuda_dlls = ["cublas64_12.dll", "cudnn64_9.dll", "cudnn64_8.dll", "zlibwapi.dll", "cudart64_12.dll", "cufft64_11.dll", "curand64_10.dll", "cusparse64_12.dll"]
    for ddir in possible_dll_dirs:
        if os.path.exists(ddir):
            for target_dll in critical_cuda_dlls:
                full_dll_path = os.path.join(ddir, target_dll)
                if os.path.exists(full_dll_path):
                    try:
                        ctypes.CDLL(full_dll_path)
                    except Exception:
                        pass
except Exception:
    pass

try:
    from ultralytics import YOLO
    ULTRALYTICS_AVAILABLE = True
except Exception as e:
    YOLO = None
    ULTRALYTICS_AVAILABLE = False
    logger.warning(f"Ultralytics library or PyTorch failed to load. AI Detection will be disabled. Error: {e}")

try:
    import torch
    TORCH_AVAILABLE = True
except Exception:
    TORCH_AVAILABLE = False


class TargetFaceTracker:
    """
    Lightweight multi-face tracker with sticky identity for real-time target tracking.
    Maintains recognized identities across frames via IoU centroid matching —
    eliminates re-running expensive ArcFace embedding on every frame for known targets.

    Features:
    - IoU + centroid-based track association (no external dependencies)
    - Sticky identity: once recognized, cached for max_age frames (~0.5s at 30fps)
    - Smooth bounding box interpolation (EMA) for stutter-free rendering
    - Auto-expiry of stale tracks when person leaves frame
    """

    def __init__(self, max_age: int = 18, iou_threshold: float = 0.25, smooth_factor: float = 0.6):
        """
        Args:
            max_age: Frames to keep a track alive without a matching detection (default 18 = ~0.6s @ 30fps)
            iou_threshold: Minimum IoU to associate detection with existing track
            smooth_factor: EMA smoothing (0=no smooth, 1=fully smooth). 0.6 = smooth but responsive
        """
        self.max_age = max_age
        self.iou_threshold = iou_threshold
        self.smooth_factor = smooth_factor
        self._next_id = 0
        self.tracks = {}  # track_id -> track dict

    @staticmethod
    def _iou(box_a, box_b):
        """Compute IoU between two boxes [x1, y1, x2, y2]"""
        xa = max(box_a[0], box_b[0])
        ya = max(box_a[1], box_b[1])
        xb = min(box_a[2], box_b[2])
        yb = min(box_a[3], box_b[3])
        inter = max(0, xb - xa) * max(0, yb - ya)
        area_a = max(1, (box_a[2] - box_a[0]) * (box_a[3] - box_a[1]))
        area_b = max(1, (box_b[2] - box_b[0]) * (box_b[3] - box_b[1]))
        return inter / (area_a + area_b - inter + 1e-6)

    def update(self, detections: list) -> list:
        """
        Update tracker with new frame detections.
        Each detection dict must have: box=[x1,y1,x2,y2], matched_name, label, is_face, is_falling

        Returns: updated detections list with sticky identities applied and smooth boxes.
        """
        # Build cost matrix (IoU) between existing tracks and new detections
        track_ids = list(self.tracks.keys())
        used_det = set()
        used_track = set()

        if track_ids and detections:
            iou_matrix = np.zeros((len(track_ids), len(detections)), dtype=np.float32)
            for ti, tid in enumerate(track_ids):
                t_box = self.tracks[tid]["box"]
                for di, det in enumerate(detections):
                    d_box = det.get("box", [0, 0, 0, 0])
                    iou_matrix[ti, di] = self._iou(t_box, d_box)

            # Greedy matching: best IoU first
            while True:
                if iou_matrix.size == 0:
                    break
                best = np.unravel_index(np.argmax(iou_matrix), iou_matrix.shape)
                best_iou = iou_matrix[best[0], best[1]]
                if best_iou < self.iou_threshold:
                    break

                ti, di = best
                tid = track_ids[ti]
                det = detections[di]
                raw_box = det["box"]

                # Smooth box update (EMA)
                s = self.smooth_factor
                old_box = self.tracks[tid]["box"]
                smooth_box = [
                    int(old_box[0] * s + raw_box[0] * (1 - s)),
                    int(old_box[1] * s + raw_box[1] * (1 - s)),
                    int(old_box[2] * s + raw_box[2] * (1 - s)),
                    int(old_box[3] * s + raw_box[3] * (1 - s)),
                ]
                self.tracks[tid]["box"] = smooth_box
                self.tracks[tid]["age"] = 0
                self.tracks[tid]["hits"] += 1

                # Sticky identity: keep existing recognized name if new detection has no match
                if det.get("matched_name"):
                    self.tracks[tid]["matched_name"] = det["matched_name"]
                    self.tracks[tid]["label"] = det["label"]
                    self.tracks[tid]["last_match_time"] = time.time()
                elif self.tracks[tid].get("matched_name"):
                    # Carry forward sticky identity
                    det["matched_name"] = self.tracks[tid]["matched_name"]
                    det["label"] = self.tracks[tid]["label"]

                det["box"] = smooth_box
                det["_track_id"] = tid

                self.tracks[tid]["is_falling"] = det.get("is_falling", False)
                self.tracks[tid]["is_face"] = det.get("is_face", False)

                used_det.add(di)
                used_track.add(ti)
                iou_matrix[ti, :] = -1
                iou_matrix[:, di] = -1

        # Create new tracks for unmatched detections
        for di, det in enumerate(detections):
            if di not in used_det:
                tid = self._next_id
                self._next_id += 1
                self.tracks[tid] = {
                    "box": det["box"],
                    "matched_name": det.get("matched_name"),
                    "label": det.get("label", ""),
                    "is_face": det.get("is_face", False),
                    "is_falling": det.get("is_falling", False),
                    "age": 0,
                    "hits": 1,
                    "last_match_time": time.time() if det.get("matched_name") else 0,
                }
                det["_track_id"] = tid

        # Age all tracks and expire stale ones
        expired = []
        for tid in self.tracks:
            if tid not in {track_ids[ti] for ti in used_track} if track_ids else True:
                self.tracks[tid]["age"] += 1
            if self.tracks[tid]["age"] > self.max_age:
                expired.append(tid)
        for tid in expired:
            del self.tracks[tid]

        return detections

    def get_active_target_tracks(self) -> list:
        """Return all active tracks that have a recognized target identity (for skip-frame rendering)."""
        results = []
        now = time.time()
        for tid, t in self.tracks.items():
            if t.get("matched_name") and (now - t.get("last_match_time", 0)) < 2.0:
                results.append({
                    "box": t["box"],
                    "matched_name": t["matched_name"],
                    "label": t["label"],
                    "is_face": t.get("is_face", False),
                    "is_falling": t.get("is_falling", False),
                    "_track_id": tid,
                })
        return results

    def get_face_count(self) -> tuple:
        """Returns (total_tracked_faces, identified_count)"""
        total = sum(1 for t in self.tracks.values() if t.get("is_face"))
        identified = sum(1 for t in self.tracks.values() if t.get("is_face") and t.get("matched_name"))
        return total, identified


class YOLOService:
    _instance = None
    
    @classmethod
    def get_instance(cls):
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

    def __init__(self):
        self.model = None
        self.model_loaded = False
        self.is_loading = False
        
        # Determine acceleration device (GPU if CUDA available, else CPU)
        if TORCH_AVAILABLE and torch.cuda.is_available():
            self.device = 0
            gpu_name = torch.cuda.get_device_name(0)
            logger.info(f"YOLOv8 AI Inference target device: GPU ({gpu_name})")
        else:
            self.device = "cpu"
            logger.info("YOLOv8 AI Inference target device: CPU (Install PyTorch CUDA for GPU acceleration)")
        
        # Determine model path (Prefer lightweight yolov8n-pose.pt, fallback to yolov8s-pose.pt)
        base_dir = os.path.dirname(os.path.dirname(os.path.dirname(__file__)))
        nano_path = os.path.join(base_dir, "assets", "models", "yolov8n-pose.pt")
        small_path = os.path.join(base_dir, "assets", "models", "yolov8s-pose.pt")
        
        model_path = nano_path if os.path.exists(nano_path) else small_path
        
        if ULTRALYTICS_AVAILABLE and os.path.exists(model_path):
            try:
                self.is_loading = True
                logger.info(f"Loading YOLOv8 AI Model from {model_path}...")
                self.model = YOLO(model_path)
                self.model_loaded = True
                self.is_loading = False
                logger.info(f"YOLOv8 AI Model ({os.path.basename(model_path)}) loaded successfully on {self.device}.")
            except Exception as e:
                self.is_loading = False
                logger.error(f"Failed to load YOLOv8 model: {e}")
        else:
            logger.warning(f"YOLOv8 model not found at {model_path} or ultralytics not installed.")

        # OpenCV FaceDetectorYN with YuNet (official OpenCV model, compatible with OpenCV 5.0)
        import threading
        self._yunet_lock = threading.Lock()
        self.face_cascade = None  # kept as truthy sentinel for guard checks
        self._face_detector_yn = None
        try:
            yunet_path = os.path.join(base_dir, "assets", "models", "face_detection_yunet_2023mar.onnx")
            if os.path.exists(yunet_path):
                # YuNet is lightweight (~200KB). Use CPU backend for stability across dynamic image sizes.
                _yunet_backend = cv2.dnn.DNN_BACKEND_OPENCV
                _yunet_target = cv2.dnn.DNN_TARGET_CPU

                self._face_detector_yn = cv2.FaceDetectorYN_create(
                    yunet_path,
                    config="",
                    input_size=(480, 480),
                    score_threshold=0.45,
                    nms_threshold=0.30,
                    top_k=300,
                    backend_id=_yunet_backend,
                    target_id=_yunet_target
                )
                self._yunet_current_size = (480, 480)
                self.face_cascade = self._face_detector_yn
                logger.info("FaceDetectorYN (YuNet ONNX) loaded successfully for face detection.")
            else:
                logger.warning(f"YuNet face model not found at {yunet_path}. Face detection disabled.")
        except Exception as e:
            logger.warning(f"FaceDetectorYN init failed: {e}. Face detection disabled.")
            self._face_detector_yn = None
            self.face_cascade = None

        # Target Face Tracker for sticky identity + smooth tracking across frames
        self._face_tracker = TargetFaceTracker(max_age=18, iou_threshold=0.25, smooth_factor=0.6)

    def detect_and_draw(
        self,
        frame: np.ndarray,
        skip_inference: bool = False,
        last_detections: list = None,
        face_detection_enabled: bool = False,
        crowd_mode_enabled: bool = False,
        conf_threshold: float = 0.35,
        imgsz: int = 320
    ) -> tuple[np.ndarray, bool, list]:
        """
        Runs high-speed detection on frame.
        Supports Crowd/High-Density mode (lower conf threshold, higher imgsz, dense crowd IoU).
        Supports Face Detection overlay & real-time Target Face Recognition.
        If skip_inference=True, renders last_detections cached bounding boxes.
        Returns tuple: (Processed Frame, fall_detected_boolean, updated_detections_list)
        """
        if frame is None:
            return frame, False, []

        if skip_inference and last_detections is not None:
            # High-speed rendering of cached bounding boxes + tracked target identities on skipped frames
            fall_detected = False

            # Merge tracked target identities that may not be in last_detections
            # (sticky tracking keeps target visible even when detection skips a frame)
            render_dets = list(last_detections)
            tracked_targets = self._face_tracker.get_active_target_tracks()
            existing_names = {d.get("matched_name") for d in render_dets if d.get("matched_name")}
            for tt in tracked_targets:
                if tt.get("matched_name") and tt["matched_name"] not in existing_names:
                    render_dets.append(tt)

            for det in render_dets:
                box = det.get("box")
                if not box or len(box) != 4:
                    continue
                x1, y1, x2, y2 = box
                is_falling = det.get("is_falling", False)
                is_face = det.get("is_face", False)
                label = det.get("label", "DETECTED")
                
                if is_falling:
                    fall_detected = True
                    color = (0, 0, 255) # Red for Fall
                elif is_face:
                    color = (0, 255, 0) if det.get("matched_name") else (0, 0, 255)
                else:
                    color = (255, 255, 0) # Cyan for Human

                cv2.rectangle(frame, (x1, y1), (x2, y2), color, 2)
                (label_w, label_h), _ = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.45, 1)
                cv2.rectangle(frame, (x1, max(0, y1 - 20)), (x1 + label_w + 4, max(20, y1)), color, -1)
                cv2.putText(frame, label, (x1 + 2, max(14, y1 - 5)), cv2.FONT_HERSHEY_SIMPLEX, 0.45, (0, 0, 0) if not is_falling else (255, 255, 255), 1)

            return frame, fall_detected, render_dets

        try:
            # Crowd Mode tuning
            effective_conf = 0.20 if crowd_mode_enabled else conf_threshold
            effective_imgsz = 640 if crowd_mode_enabled else imgsz
            effective_iou = 0.60 if crowd_mode_enabled else 0.45

            fall_detected = False
            current_detections = []

            # 1. Human Body Pose Inference (YOLOv8)
            if self.model_loaded and self.model is not None:
                results = self.model(
                    frame,
                    verbose=False,
                    conf=effective_conf,
                    iou=effective_iou,
                    imgsz=effective_imgsz,
                    device=self.device
                )

                if len(results) > 0 and results[0].boxes is not None:
                    boxes = results[0].boxes.xyxy.cpu().numpy()
                    confidences = results[0].boxes.conf.cpu().numpy()
                    keypoints = results[0].keypoints.xy.cpu().numpy() if (results[0].keypoints is not None and hasattr(results[0].keypoints, "xy")) else []

                    fh, fw, _ = frame.shape

                    for i, box in enumerate(boxes):
                        x1, y1, x2, y2 = map(int, box)
                        conf = confidences[i]
                        width = x2 - x1
                        height = y2 - y1

                        is_falling = False
                        
                        # Fall Detection check from pose keypoints
                        if len(keypoints) > i:
                            kpts = keypoints[i]
                            if len(kpts) >= 13 and kpts[5][1] > 0 and kpts[6][1] > 0 and kpts[11][1] > 0 and kpts[12][1] > 0:
                                shoulder_y = (kpts[5][1] + kpts[6][1]) / 2
                                hip_y = (kpts[11][1] + kpts[12][1]) / 2
                                shoulder_x = (kpts[5][0] + kpts[6][0]) / 2
                                hip_x = (kpts[11][0] + kpts[12][0]) / 2
                                
                                dx = abs(shoulder_x - hip_x)
                                dy = hip_y - shoulder_y
                                spine_angle = math.degrees(math.atan2(dy, dx)) if (dx > 0 or dy != 0) else 90
                                
                                if (dy < 15 or spine_angle < 30) and (width > height * 1.25):
                                    is_falling = True

                        if not is_falling and (width > height * 1.6):
                            is_falling = True

                        matched_name = None
                        matched_score = 0.0

                        # ─── Distance-Aware Adaptive Face Crop ─────────────────────────────────
                        # Person size (height px) tells us their distance from camera:
                        #   Near  : height >= 150px  → precise head keypoint ROI
                        #   Mid   : 80 <= height < 150px → upper body top-35% crop
                        #   Far   : height < 80px   → upper body top-35% crop + 4x Upscale + Sharpen
                        face_crop = None
                        kpts_available = len(keypoints) > i

                        if kpts_available and height >= 80:
                            # Near / Mid: Use head keypoints (nose=0, eyes=1,2, ears=3,4)
                            kpts = keypoints[i]
                            head_kpts = [k for k in kpts[0:5] if k[0] > 0 and k[1] > 0]
                            if head_kpts:
                                h_xs = [k[0] for k in head_kpts]
                                h_ys = [k[1] for k in head_kpts]
                                # Adaptive padding: bigger for mid-range persons
                                pad = max(18, int(height * 0.18))
                                hx1 = max(0, int(min(h_xs)) - pad)
                                hx2 = min(fw, int(max(h_xs)) + pad)
                                hy1 = max(0, int(min(h_ys)) - pad)
                                hy2 = min(fh, int(max(h_ys)) + pad)
                                if (hx2 - hx1) > 12 and (hy2 - hy1) > 12:
                                    face_crop = frame[hy1:hy2, hx1:hx2]

                        if face_crop is None or face_crop.size == 0:
                            # Fallback: top portion of body bounding box (head + shoulders region)
                            # Use top 38% for near/mid, top 45% for far (head proportion is larger at top)
                            top_ratio = 0.45 if height < 80 else 0.38
                            crop_y1 = max(0, y1)
                            crop_y2 = min(fh, y1 + max(20, int(height * top_ratio)))
                            # Horizontally center-crop to eliminate background noise
                            h_margin = max(0, int(width * 0.10))
                            crop_x1 = max(0, x1 + h_margin)
                            crop_x2 = min(fw, x2 - h_margin)
                            if crop_x2 > crop_x1 and crop_y2 > crop_y1:
                                face_crop = frame[crop_y1:crop_y2, crop_x1:crop_x2]

                        # ─── Far-Person Enhancement: Upscale + Sharpen ─────────────────────────
                        # When person is far (small box), face pixels are tiny and blurry.
                        # Only run expensive enhancement if target faces are registered (has_targets).
                        # Upscale with INTER_LINEAR (fast, ~5x faster than LANCZOS4, sufficient for detection).
                        if face_crop is not None and face_crop.size > 0 and height < 120:
                            try:
                                # Check if any target faces exist before expensive processing
                                _run_enhance = False
                                try:
                                    from services.target_face_service import TargetFaceService
                                    _run_enhance = TargetFaceService.get_instance().has_targets()
                                except Exception:
                                    _run_enhance = False

                                if _run_enhance:
                                    crop_h, crop_w = face_crop.shape[:2]
                                    # Determine upscale factor based on distance estimate
                                    if height < 50:
                                        scale = 5  # Very far: 5x upscale
                                    elif height < 80:
                                        scale = 4  # Far: 4x upscale
                                    else:
                                        scale = 2  # Mid: 2x upscale

                                    up_w = max(60, crop_w * scale)
                                    up_h = max(60, crop_h * scale)
                                    # INTER_LINEAR: fast upscale (sufficient quality for face matching)
                                    face_up = cv2.resize(face_crop, (up_w, up_h), interpolation=cv2.INTER_LINEAR)

                                    # CLAHE on L channel for contrast enhancement
                                    face_lab = cv2.cvtColor(face_up, cv2.COLOR_BGR2LAB)
                                    l_ch, a_ch, b_ch = cv2.split(face_lab)
                                    clahe = cv2.createCLAHE(clipLimit=2.5, tileGridSize=(4, 4))
                                    l_ch = clahe.apply(l_ch)
                                    face_up = cv2.cvtColor(cv2.merge([l_ch, a_ch, b_ch]), cv2.COLOR_LAB2BGR)

                                    # Unsharp Masking: sharpen fine facial details
                                    blur = cv2.GaussianBlur(face_up, (3, 3), 0.8)
                                    face_crop = cv2.addWeighted(face_up, 1.5, blur, -0.5, 0)
                                    # Denoise for low-light sensor noise reduction
                                    face_crop = cv2.fastNlMeansDenoisingColored(face_crop, None, 6, 6, 7, 21)
                            except Exception:
                                pass  # Keep original crop if enhancement fails

                        if face_crop is not None and face_crop.size > 0:
                            try:
                                from services.target_face_service import TargetFaceService
                                matched_name, matched_score, _ = TargetFaceService.get_instance().recognize_face_crop(face_crop)
                            except Exception:
                                matched_name = None

                        if is_falling:
                            fall_detected = True
                            color = (0, 0, 255)
                            label = f"FALL DETECTED {conf:.2f}"
                        elif matched_name:
                            color = (0, 255, 0)
                            label = f"TARGET: {matched_name.upper()} ({int(matched_score * 100)}%)"
                        else:
                            if face_detection_enabled:
                                color = (0, 0, 255)  # Red for Unknown Face when Face Mode is active
                                label = "UNKNOWN FACE"
                            else:
                                color = (255, 255, 0) # Cyan for Human Pose when Face Mode is off
                                label = f"HUMAN {conf:.2f}"

                        current_detections.append({
                            "box": [x1, y1, x2, y2],
                            "is_falling": is_falling,
                            "is_face": False,
                            "label": label,
                            "matched_name": matched_name
                        })

                        cv2.rectangle(frame, (x1, y1), (x2, y2), color, 2)
                        (label_w, label_h), _ = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.45, 1)
                        cv2.rectangle(frame, (x1, max(0, y1 - 20)), (x1 + label_w + 4, max(20, y1)), color, -1)
                        cv2.putText(frame, label, (x1 + 2, max(14, y1 - 5)), cv2.FONT_HERSHEY_SIMPLEX, 0.45, (255, 255, 255), 1)

            # 2. Dedicated Face Detection Engine — FaceDetectorYN (YuNet ONNX with 5-Landmark Affine Alignment)
            #    Crowd Mode: Higher resolution (640x640), lower NMS for dense face packing, batch recognition
            if face_detection_enabled and self._face_detector_yn is not None:
                try:
                    fh, fw = frame.shape[:2]
                    faces_raw = None
                    if fh >= 50 and fw >= 50:
                        _face_det_size = 640 if crowd_mode_enabled else 480
                        target_size = (_face_det_size, _face_det_size)
                        resized_face = cv2.resize(frame, target_size, interpolation=cv2.INTER_LINEAR)
                        resized_face = np.ascontiguousarray(resized_face)

                        with self._yunet_lock:
                            if getattr(self, '_yunet_current_size', None) != target_size:
                                self._face_detector_yn.setInputSize(target_size)
                                self._yunet_current_size = target_size

                            # In crowd mode, temporarily lower score threshold for dense face capture
                            if crowd_mode_enabled:
                                self._face_detector_yn.setScoreThreshold(0.35)
                                self._face_detector_yn.setNMSThreshold(0.20)  # Lower NMS: allow closely packed faces
                                self._face_detector_yn.setTopK(500)           # Allow more face candidates
                            else:
                                self._face_detector_yn.setScoreThreshold(0.45)
                                self._face_detector_yn.setNMSThreshold(0.30)
                                self._face_detector_yn.setTopK(300)

                            try:
                                _, faces_raw = self._face_detector_yn.detect(resized_face)
                            except Exception as cverr:
                                logger.debug(f"FaceDetectorYN detect exception safely caught: {cverr}")
                                faces_raw = None

                    if faces_raw is not None:
                        sx = fw / float(_face_det_size)
                        sy = fh / float(_face_det_size)

                        # ─── Collect existing YOLO body detection centers for deduplication ───
                        body_centers = []
                        for det in current_detections:
                            if not det.get("is_face") and det.get("matched_name"):
                                bx1, by1, bx2, by2 = det["box"]
                                body_centers.append(((bx1 + bx2) / 2, (by1 + by2) / 2, det.get("matched_name")))

                        # ─── Phase A: Collect all valid face ROIs + landmarks ───────────────
                        face_entries = []  # (fx1, fy1, fx2, fy2, face_roi, landmarks, skip_recognition, assoc_name)
                        for face_row in faces_raw:
                            fx, fy, fw_box, fh_box = face_row[0], face_row[1], face_row[2], face_row[3]
                            fx1 = max(0, int(fx * sx))
                            fy1 = max(0, int(fy * sy))
                            fx2 = min(fw, int((fx + fw_box) * sx))
                            fy2 = min(fh, int((fy + fh_box) * sy))

                            if (fx2 - fx1) < 20 or (fy2 - fy1) < 20:
                                continue

                            face_roi = frame[fy1:fy2, fx1:fx2]

                            landmarks = None
                            if len(face_row) >= 14:
                                try:
                                    landmarks = np.array([
                                        [face_row[4] * sx, face_row[5] * sy],
                                        [face_row[6] * sx, face_row[7] * sy],
                                        [face_row[8] * sx, face_row[9] * sy],
                                        [face_row[10] * sx, face_row[11] * sy],
                                        [face_row[12] * sx, face_row[13] * sy]
                                    ], dtype=np.float32)
                                except Exception:
                                    landmarks = None

                            # Deduplication check: inherit target name if body box already recognized person
                            face_cx = (fx1 + fx2) / 2
                            face_cy = (fy1 + fy2) / 2
                            skip_recog = False
                            assoc_name = None
                            for bcx, bcy, bname in body_centers:
                                if abs(face_cx - bcx) < (fx2 - fx1) * 2.5 and abs(face_cy - bcy) < (fy2 - fy1) * 4:
                                    skip_recog = True
                                    assoc_name = bname
                                    break

                            face_entries.append((fx1, fy1, fx2, fy2, face_roi, landmarks, skip_recog, assoc_name))

                        # ─── Phase B: Batch Recognition (crowd-optimized) ──────────────────
                        from services.target_face_service import TargetFaceService
                        target_svc = TargetFaceService.get_instance()

                        if crowd_mode_enabled and len(face_entries) >= 3:
                            # Batch mode: collect all crops → single vectorized matrix match
                            crops_for_batch = []
                            lms_for_batch = []
                            for (_, _, _, _, roi, lm, skip, _) in face_entries:
                                if skip or roi.size == 0:
                                    crops_for_batch.append(None)
                                    lms_for_batch.append(None)
                                else:
                                    crops_for_batch.append(roi)
                                    lms_for_batch.append(lm)

                            try:
                                batch_results = target_svc.recognize_faces_batch(
                                    crops_for_batch, lms_for_batch
                                )
                                # Fill associated names for skipped entries
                                for idx, (_, _, _, _, _, _, _, assoc_name) in enumerate(face_entries):
                                    if assoc_name and idx < len(batch_results) and not batch_results[idx][0]:
                                        batch_results[idx] = (assoc_name, 0.88, "VIP")
                            except Exception:
                                batch_results = [(None, 0.0, None)] * len(face_entries)
                        else:
                            # Sequential mode for small face counts
                            batch_results = []
                            for (_, _, _, _, roi, lm, skip, assoc_name) in face_entries:
                                if assoc_name:
                                    batch_results.append((assoc_name, 0.88, "VIP"))
                                elif skip or roi.size == 0:
                                    batch_results.append((None, 0.0, None))
                                else:
                                    try:
                                        name, score, role = target_svc.recognize_face_crop(roi, landmarks=lm)
                                        batch_results.append((name if name else assoc_name, score if name else 0.88, role if role else "VIP"))
                                    except Exception:
                                        batch_results.append((assoc_name, 0.88 if assoc_name else 0.0, "VIP" if assoc_name else None))

                        # ─── Phase C: Render all face detections ───────────────────────────
                        face_count = len(face_entries)
                        identified_count = 0

                        for i, (fx1, fy1, fx2, fy2, *_) in enumerate(face_entries):
                            f_matched_name, f_matched_score, _ = batch_results[i] if i < len(batch_results) else (None, 0.0, None)

                            if f_matched_name:
                                identified_count += 1
                                f_color = (0, 255, 0)  # Green for known target face
                                f_label = f"TARGET: {f_matched_name.upper()} ({int(f_matched_score * 100)}%)"
                            else:
                                f_color = (0, 0, 255)  # Red for unknown face alert
                                f_label = "UNKNOWN FACE"

                            current_detections.append({
                                "box": [fx1, fy1, fx2, fy2],
                                "is_falling": False,
                                "is_face": True,
                                "label": f_label,
                                "matched_name": f_matched_name
                            })

                            # Draw face box
                            cv2.rectangle(frame, (fx1, fy1), (fx2, fy2), f_color, 2)
                            (label_w, label_h), _ = cv2.getTextSize(f_label, cv2.FONT_HERSHEY_SIMPLEX, 0.45, 1)
                            cv2.rectangle(frame, (fx1, max(0, fy1 - 20)), (fx1 + label_w + 4, max(20, fy1)), f_color, -1)
                            cv2.putText(frame, f_label, (fx1 + 2, max(14, fy1 - 5)), cv2.FONT_HERSHEY_SIMPLEX, 0.45, (255, 255, 255), 1)

                        # ─── Crowd Face Counter HUD Overlay ────────────────────────────────
                        if face_count > 0:
                            hud_label = f"FACES: {face_count} | ID: {identified_count}"
                            (hw, hh), _ = cv2.getTextSize(hud_label, cv2.FONT_HERSHEY_SIMPLEX, 0.6, 2)
                            hud_x = fw - hw - 16
                            hud_y = 30
                            cv2.rectangle(frame, (hud_x - 8, hud_y - hh - 8), (hud_x + hw + 8, hud_y + 8), (0, 0, 0), -1)
                            cv2.putText(frame, hud_label, (hud_x, hud_y), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 255), 2)
                except Exception as fe:
                    logger.error(f"FaceDetectorYN detection error: {fe}")

            # ─── Apply Tracker: sticky identity + smooth boxes ────────────────────
            current_detections = self._face_tracker.update(current_detections)

            return frame, fall_detected, current_detections

        except Exception as e:
            logger.error(f"Error during AI inference: {e}")
            return frame, False, []
