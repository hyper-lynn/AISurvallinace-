import os
import cv2
import numpy as np
from config import logger
import math

try:
    from ultralytics import YOLO
    ULTRALYTICS_AVAILABLE = True
except ImportError:
    YOLO = None
    ULTRALYTICS_AVAILABLE = False
    logger.warning("Ultralytics library not found. AI Detection will be disabled. Run: pip install ultralytics")

try:
    import torch
    TORCH_AVAILABLE = True
except ImportError:
    TORCH_AVAILABLE = False

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

    def detect_and_draw(self, frame: np.ndarray, skip_inference: bool = False, last_detections: list = None) -> tuple[np.ndarray, bool, list]:
        """
        Runs high-speed inference on frame (imgsz=320).
        If skip_inference=True, draws last_detections cached boxes to eliminate lag!
        Returns tuple: (Processed Frame, fall_detected_boolean, updated_detections_list)
        """
        if not self.model_loaded or self.model is None or frame is None:
            return frame, False, []

        if skip_inference and last_detections is not None:
            # High-speed rendering of cached bounding boxes on intermediate video frames
            fall_detected = False
            for det in last_detections:
                x1, y1, x2, y2 = det["box"]
                is_falling = det["is_falling"]
                label = det["label"]
                if is_falling:
                    fall_detected = True
                    color = (0, 0, 255)
                else:
                    color = (255, 255, 0)

                cv2.rectangle(frame, (x1, y1), (x2, y2), color, 2)
                (label_w, label_h), _ = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.5, 1)
                cv2.rectangle(frame, (x1, y1 - 20), (x1 + label_w, y1), color, -1)
                cv2.putText(frame, label, (x1, y1 - 5), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0) if not is_falling else (255, 255, 255), 1)

            return frame, fall_detected, last_detections

        try:
            # Run high-speed inference with imgsz=320 on target device (GPU/CPU)
            results = self.model(frame, verbose=False, conf=0.45, imgsz=320, device=self.device)
            
            fall_detected = False
            current_detections = []
            
            # The pose model returns boxes and keypoints for each detected person
            if len(results) > 0 and results[0].boxes is not None and results[0].keypoints is not None:
                boxes = results[0].boxes.xyxy.cpu().numpy() # [x1, y1, x2, y2]
                keypoints = results[0].keypoints.xy.cpu().numpy() # [N, 17, 2]
                confidences = results[0].boxes.conf.cpu().numpy()

                for i, box in enumerate(boxes):
                    x1, y1, x2, y2 = map(int, box)
                    conf = confidences[i]
                    
                    width = x2 - x1
                    height = y2 - y1
                    
                    is_falling = False
                    
                    # Strict Fall Detection Algorithm (Eliminates False Positives during sitting/standing/walking)
                    is_falling = False
                    
                    if len(keypoints) > i:
                        kpts = keypoints[i]
                        # Verify shoulder (5,6) and hip (11,12) keypoint coordinates
                        if len(kpts) >= 13 and kpts[5][1] > 0 and kpts[6][1] > 0 and kpts[11][1] > 0 and kpts[12][1] > 0:
                            shoulder_y = (kpts[5][1] + kpts[6][1]) / 2
                            hip_y = (kpts[11][1] + kpts[12][1]) / 2
                            
                            shoulder_x = (kpts[5][0] + kpts[6][0]) / 2
                            hip_x = (kpts[11][0] + kpts[12][0]) / 2
                            
                            dx = abs(shoulder_x - hip_x)
                            dy = hip_y - shoulder_y # Positive when head/shoulder is above hips
                            
                            # Spine angle relative to horizontal ground (90 deg = standing, 0 deg = horizontal fall)
                            spine_angle = math.degrees(math.atan2(dy, dx)) if (dx > 0 or dy != 0) else 90
                            
                            # A true fall requires horizontal posture (dy < 15 or angle < 30) AND bounding box width > height * 1.25
                            if (dy < 15 or spine_angle < 30) and (width > height * 1.25):
                                is_falling = True
                    
                    # Secondary fallback if keypoints obscured: Require overwhelming horizontal aspect ratio (width > height * 1.6)
                    if not is_falling and (width > height * 1.6):
                        is_falling = True

                    if is_falling:
                        fall_detected = True
                        color = (0, 0, 255) # Red for Fall
                        label = f"FALL DETECTED {conf:.2f}"
                    else:
                        color = (255, 255, 0) # Cyan for normal human
                        label = f"HUMAN {conf:.2f}"

                    current_detections.append({
                        "box": [x1, y1, x2, y2],
                        "is_falling": is_falling,
                        "label": label
                    })

                    # Draw Bounding Box
                    cv2.rectangle(frame, (x1, y1), (x2, y2), color, 2)
                    (label_w, label_h), _ = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.5, 1)
                    cv2.rectangle(frame, (x1, y1 - 20), (x1 + label_w, y1), color, -1)
                    cv2.putText(frame, label, (x1, y1 - 5), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0) if not is_falling else (255, 255, 255), 1)

            return frame, fall_detected, current_detections
            
        except Exception as e:
            logger.error(f"Error during AI inference: {e}")
            return frame, False, []
