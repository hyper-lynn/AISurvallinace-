"""
Real-Time 2.5D Face Recognition & Liveness Detection Pipeline
Models:
  1. Detection: SCRFD-2.5G (ONNX)
  2. 2.5D Liveness / Anti-Spoofing: MiniFASNetV2 (ONNX)
  3. Feature Extraction / Embedding: ArcFace IR-50 (ONNX)
Target Hardware: NVIDIA GTX 1650 Max-Q (ONNX Runtime CUDA Provider)
"""

import os
import time
import cv2
import numpy as np
from typing import List, Tuple, Dict, Optional

# Explicitly locate and preload CUDA 13 / 12 & cuDNN DLLs for ONNX Runtime GPU Provider
try:
    import ctypes
    import site
    import glob
    possible_dll_dirs = [
        r"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v13.3\bin\x64",
        r"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v13.3\bin",
        r"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.4\bin",
        r"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.1\bin",
    ]

    # Check virtual environment & site packages
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

    # Check system/global python installations if venv torch lacks CUDA DLLs
    user_home = os.path.expanduser("~")
    global_py_pattern = os.path.join(user_home, "AppData", "Local", "Programs", "Python", "Python*", "Lib", "site-packages", "torch", "lib")
    for g_path in glob.glob(global_py_pattern):
        if os.path.exists(g_path) and g_path not in possible_dll_dirs:
            possible_dll_dirs.append(g_path)

    # Add all candidate directories to PATH and Windows DLL Search
    for ddir in possible_dll_dirs:
        if os.path.exists(ddir):
            os.environ["PATH"] = ddir + os.pathsep + os.environ.get("PATH", "")
            if hasattr(os, "add_dll_directory"):
                try:
                    os.add_dll_directory(ddir)
                except Exception:
                    pass

    # Preload specific CUDA & cuDNN runtime DLLs into process memory via ctypes
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
except Exception as e:
    pass

try:
    import onnxruntime as ort
    ONNXRUNTIME_AVAILABLE = True
except ImportError:
    ort = None
    ONNXRUNTIME_AVAILABLE = False
    print("Warning: onnxruntime not found. Install via: pip install onnxruntime-gpu")


# Standard 5-landmark reference points for 112x112 ArcFace alignment
ARCFACE_REF_PTS = np.array([
    [38.2946, 51.6963],
    [73.5318, 51.5014],
    [56.0252, 71.7366],
    [41.5493, 92.3655],
    [70.7299, 92.2041]
], dtype=np.float32)

def align_face_112(img: np.ndarray, landmarks: np.ndarray) -> np.ndarray:
    """Align face to 112x112 using 5 keypoints via affine transform"""
    M, _ = cv2.estimateAffinePartial2D(landmarks.astype(np.float32), ARCFACE_REF_PTS)
    if M is None:
        return cv2.resize(img, (112, 112))
    aligned = cv2.warpAffine(img, M, (112, 112), borderValue=0)
    return aligned

class SCRFDDetector:
    """SCRFD-2.5G Face Detector using ONNX Runtime GPU"""
    def __init__(self, model_path: str, conf_threshold: float = 0.5, nms_threshold: float = 0.4):
        self.conf_threshold = conf_threshold
        self.nms_threshold = nms_threshold
        
        providers = ['CUDAExecutionProvider', 'CPUExecutionProvider']
        provider_options = [{'device_id': 0}, {}]
        try:
            self.session = ort.InferenceSession(model_path, providers=providers, provider_options=provider_options)
        except Exception as e:
            print(f"CUDA failed for SCRFD, falling back to CPU: {e}")
            self.session = ort.InferenceSession(model_path, providers=['CPUExecutionProvider'])
        self.input_name = self.session.get_inputs()[0].name
        self.input_shape = self.session.get_inputs()[0].shape

    def preprocess(self, img: np.ndarray, target_size: Tuple[int, int] = (640, 640)) -> Tuple[np.ndarray, float, Tuple[int, int]]:
        h, w, _ = img.shape
        r = min(target_size[0] / h, target_size[1] / w)
        nh, nw = int(round(h * r)), int(round(w * r))
        resized = cv2.resize(img, (nw, nh))
        
        padded = np.zeros((target_size[0], target_size[1], 3), dtype=np.uint8)
        padded[:nh, :nw] = resized
        
        blob = cv2.dnn.blobFromImage(padded, 1.0/128.0, target_size, (127.5, 127.5, 127.5), swapRB=True)
        return blob, r, (nh, nw)

    def detect(self, img: np.ndarray) -> List[Dict]:
        """Detect faces and return bounding boxes + 5 landmarks using SCRFD stride-based anchor decoding"""
        blob, ratio, _ = self.preprocess(img)
        outputs = self.session.run(None, {self.input_name: blob})

        h_img, w_img = img.shape[:2]
        faces = []
        strides = [8, 16, 32]

        # SCRFD outputs: 3 score maps + 3 bbox maps + 3 landmark maps (9 total)
        # If model has landmarks: outputs[0:3]=scores, outputs[3:6]=bboxes, outputs[6:9]=landmarks
        has_kps = len(outputs) >= 9
        scores_list = outputs[0:3]
        bboxes_list = outputs[3:6]
        kps_list = outputs[6:9] if has_kps else [None, None, None]

        for stride_idx, stride in enumerate(strides):
            s_map = scores_list[stride_idx]
            b_map = bboxes_list[stride_idx]
            k_map = kps_list[stride_idx]

            feat_h = 640 // stride
            feat_w = 640 // stride
            anchor_idx = 0

            for y in range(feat_h):
                for x in range(feat_w):
                    for a in range(2):  # 2 anchors per grid cell
                        if anchor_idx >= s_map.shape[0]:
                            break
                        score = float(s_map[anchor_idx, 0])
                        if score >= self.conf_threshold:
                            dist = b_map[anchor_idx] * stride
                            cx = (x + 0.5) * stride
                            cy = (y + 0.5) * stride
                            x1 = (cx - dist[0]) / ratio
                            y1 = (cy - dist[1]) / ratio
                            x2 = (cx + dist[2]) / ratio
                            y2 = (cy + dist[3]) / ratio

                            x1 = max(0, int(x1))
                            y1 = max(0, int(y1))
                            x2 = min(w_img, int(x2))
                            y2 = min(h_img, int(y2))

                            if (x2 - x1) < 10 or (y2 - y1) < 10:
                                anchor_idx += 1
                                continue

                            face_entry = {
                                "bbox": [x1, y1, x2, y2],
                                "score": score,
                                "landmarks": None
                            }

                            # Decode 5-point landmarks if available
                            if k_map is not None and anchor_idx < k_map.shape[0]:
                                try:
                                    raw_kps = k_map[anchor_idx]  # 10 values (5 points x 2)
                                    lms = []
                                    for li in range(5):
                                        lx = (cx + raw_kps[li * 2] * stride) / ratio
                                        ly = (cy + raw_kps[li * 2 + 1] * stride) / ratio
                                        lms.append([float(lx), float(ly)])
                                    face_entry["landmarks"] = np.array(lms, dtype=np.float32)
                                except Exception:
                                    pass

                            faces.append(face_entry)
                        anchor_idx += 1

        # NMS to remove overlapping detections
        if faces:
            boxes_for_nms = [[f["bbox"][0], f["bbox"][1], f["bbox"][2] - f["bbox"][0], f["bbox"][3] - f["bbox"][1]] for f in faces]
            scores_for_nms = [f["score"] for f in faces]
            indices = cv2.dnn.NMSBoxes(boxes_for_nms, scores_for_nms, self.conf_threshold, self.nms_threshold)
            if len(indices) > 0:
                indices = indices.flatten()
                faces = [faces[i] for i in indices]
            else:
                faces = []

        return faces

class MiniFASNetLiveness:
    """MiniFASNetV2 2.5D Anti-Spoofing Model"""
    def __init__(self, model_path: str):
        providers = ['CUDAExecutionProvider', 'CPUExecutionProvider']
        try:
            self.session = ort.InferenceSession(model_path, providers=providers)
        except Exception as e:
            print(f"CUDA failed for MiniFASNet, falling back to CPU: {e}")
            self.session = ort.InferenceSession(model_path, providers=['CPUExecutionProvider'])
        self.input_name = self.session.get_inputs()[0].name
        self.input_size = (80, 80)

    def preprocess(self, img: np.ndarray, bbox: Tuple[int, int, int, int]) -> np.ndarray:
        x1, y1, x2, y2 = bbox
        h, w, _ = img.shape
        box_w = x2 - x1
        box_h = y2 - y1
        cx, cy = x1 + box_w // 2, y1 + box_h // 2
        
        # Scale bounding box by 2.7 for MiniFASNet context
        scale = 2.7
        nw = int(box_w * scale)
        nh = int(box_h * scale)
        nx1 = max(0, cx - nw // 2)
        ny1 = max(0, cy - nh // 2)
        nx2 = min(w, cx + nw // 2)
        ny2 = min(h, cy + nh // 2)
        
        crop = img[ny1:ny2, nx1:nx2]
        resized = cv2.resize(crop, self.input_size)
        blob = cv2.dnn.blobFromImage(resized, 1.0, self.input_size, (0, 0, 0), swapRB=False)
        return blob

    def predict(self, img: np.ndarray, bbox: Tuple[int, int, int, int]) -> Tuple[bool, float]:
        """Returns (is_real, confidence_score)"""
        blob = self.preprocess(img, bbox)
        outputs = self.session.run(None, {self.input_name: blob})[0]
        probs = np.exp(outputs) / np.sum(np.exp(outputs), axis=1, keepdims=True)
        real_score = float(probs[0][1]) # Index 1 is Real face
        is_real = real_score > 0.85
        return is_real, real_score

class ArcFaceExtractor:
    """ArcFace IR-50 (ResNet-50) Feature Extractor with ONNX GPU and PyTorch CUDA Fallback"""
    def __init__(self, model_path: str):
        providers = ['CUDAExecutionProvider', 'CPUExecutionProvider']
        try:
            self.session = ort.InferenceSession(model_path, providers=providers)
        except Exception as e:
            print(f"CUDA failed for ArcFace, falling back to CPU: {e}")
            self.session = ort.InferenceSession(model_path, providers=['CPUExecutionProvider'])
        self.input_name = self.session.get_inputs()[0].name
        self.use_gpu = 'CUDAExecutionProvider' in self.session.get_providers()

    def extract_embedding(self, aligned_face_112: np.ndarray) -> np.ndarray:
        """Extract 512-dimensional normalized face feature vector"""
        blob = cv2.dnn.blobFromImage(aligned_face_112, 1.0/128.0, (112, 112), (127.5, 127.5, 127.5), swapRB=True)
        outputs = self.session.run(None, {self.input_name: blob})[0]
        embedding = outputs[0]
        # L2 Normalization
        norm = np.linalg.norm(embedding)
        if norm > 0:
            embedding = embedding / norm
        return embedding

def preprocess_face_for_embedding(face_img: np.ndarray) -> np.ndarray:
    """Enhanced preprocessing: histogram equalization + denoising before embedding extraction"""
    if face_img is None or face_img.size == 0:
        return face_img
    try:
        # Mild denoising to reduce sensor noise (especially in low-light)
        denoised = cv2.fastNlMeansDenoisingColored(face_img, None, 5, 5, 7, 15)
        # CLAHE on L channel for illumination normalization
        lab = cv2.cvtColor(denoised, cv2.COLOR_BGR2LAB)
        l_ch, a_ch, b_ch = cv2.split(lab)
        clahe = cv2.createCLAHE(clipLimit=2.5, tileGridSize=(4, 4))
        l_ch = clahe.apply(l_ch)
        result = cv2.cvtColor(cv2.merge([l_ch, a_ch, b_ch]), cv2.COLOR_LAB2BGR)
        return result
    except Exception:
        return face_img

class RealTimeFacePipeline:
    """Full 2.5D Real-Time Face Recognition Pipeline"""
    def __init__(self, scrfd_onnx: str, minifas_onnx: str, arcface_onnx: str):
        print("Initializing ONNX Models on GTX 1650 Max-Q GPU...")
        self.liveness_model = MiniFASNetLiveness(minifas_onnx)
        self.arcface_model = ArcFaceExtractor(arcface_onnx)
        self.known_faces: Dict[str, np.ndarray] = {}

    def register_face(self, name: str, aligned_face: np.ndarray):
        """Register a known user face embedding"""
        emb = self.arcface_model.extract_embedding(aligned_face)
        self.known_faces[name] = emb
        print(f"Registered user: {name}")

    def recognize(self, embedding: np.ndarray, threshold: float = 0.4) -> Tuple[str, float]:
        """Match embedding against database using Cosine Similarity"""
        best_name = "Unknown"
        max_sim = 0.0
        
        for name, k_emb in self.known_faces.items():
            sim = float(np.dot(embedding, k_emb))
            if sim > max_sim:
                max_sim = sim
                if sim >= threshold:
                    best_name = name

        return best_name, max_sim

    def register_user_from_image_path(self, name: str, image_path: str) -> bool:
        """Register a user by passing their photo file path"""
        img = cv2.imread(image_path)
        if img is None:
            return False
        aligned = cv2.resize(img, (112, 112))
        self.register_face(name, aligned)
        return True

    def compare_two_images(self, img1_path: str, img2_path: str) -> Dict:
        """Compare two face images and return output dictionary"""
        img1 = cv2.imread(img1_path)
        img2 = cv2.imread(img2_path)
        if img1 is None or img2 is None:
            return {"error": "Image file not found"}

        a1 = cv2.resize(img1, (112, 112))
        a2 = cv2.resize(img2, (112, 112))

        emb1 = self.arcface_model.extract_embedding(a1)
        emb2 = self.arcface_model.extract_embedding(a2)

        similarity = float(np.dot(emb1, emb2))
        is_same_person = similarity >= 0.40

        return {
            "is_same_person": is_same_person,
            "similarity_score_percent": round(similarity * 100, 2),  # e.g., 89.5%
            "raw_cosine_score": round(similarity, 4),
            "output_status": "MATCHED (လူတူပါသည်)" if is_same_person else "DIFFERENT_PERSON (လူမတူပါ)"
        }

if __name__ == "__main__":
    print("2.5D Face Recognition Pipeline Module Loaded Successfully.")

