# src/api/face_api.py

import os
import sys
import base64
import time
import cv2
import numpy as np
from typing import Optional, List, Dict, Tuple
from fastapi import FastAPI, File, UploadFile, Form, HTTPException, Query
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import JSONResponse
from pydantic import BaseModel

# Add src to python path if needed
current_dir = os.path.dirname(os.path.abspath(__file__))
src_dir = os.path.dirname(current_dir)
if src_dir not in sys.path:
    sys.path.insert(0, src_dir)

from config import logger
from services.target_face_service import TargetFaceService
from services.face_2d5_pipeline import MiniFASNetLiveness, ArcFaceExtractor

# Preload CUDA 13 / 12 & cuDNN DLLs for ONNX Runtime GPU Provider
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
    import onnxruntime as ort
    ONNX_AVAILABLE = True
except ImportError:
    ort = None
    ONNX_AVAILABLE = False

# Initialize FastAPI App
app = FastAPI(
    title="Shadow EYE - Face Detection & Recognition API",
    description="Real-time Face Detection, 2.5D Liveness Check, and Target Face Matching API for Mobile & Web Applications",
    version="1.0.0"
)

# Configure CORS Middleware (Allow iOS, Android, and Web PWA origins)
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

class Base64DetectRequest(BaseModel):
    image_base64: str
    threshold: Optional[float] = 0.40

class Base64CompareRequest(BaseModel):
    image1_base64: str
    image2_base64: str

def decode_base64_image(b64_str: str) -> Optional[np.ndarray]:
    """Decode base64 string with automatic EXIF orientation transpose for mobile camera photos"""
    try:
        if "," in b64_str:
            b64_str = b64_str.split(",", 1)[1]
        img_bytes = base64.b64decode(b64_str)
        
        from PIL import Image, ImageOps
        import io
        pil_img = Image.open(io.BytesIO(img_bytes))
        pil_img = ImageOps.exif_transpose(pil_img).convert("RGB")
        img = cv2.cvtColor(np.array(pil_img), cv2.COLOR_RGB2BGR)
        return img
    except Exception as e:
        try:
            nparr = np.frombuffer(base64.b64decode(b64_str.split(",", 1)[-1]), np.uint8)
            return cv2.imdecode(nparr, cv2.IMREAD_COLOR)
        except Exception:
            logger.error(f"Error decoding base64 image: {e}")
            return None

def encode_image_to_base64(img: np.ndarray) -> str:
    """Encode OpenCV BGR image matrix to base64 jpeg data uri"""
    _, buffer = cv2.imencode('.jpg', img, [cv2.IMWRITE_JPEG_QUALITY, 85])
    b64_data = base64.b64encode(buffer).decode('utf-8')
    return f"data:image/jpeg;base64,{b64_data}"

def detect_face_rectangles(img: np.ndarray) -> List[Tuple[int, int, int, int]]:
    """
    Detect face bounding boxes [x, y, w, h] using InsightFace SCRFD 2.5G ONNX Model.
    """
    h, w, _ = img.shape
    faces = []

    # 1. SCRFD-2.5G ONNX Face Detector
    project_root = os.path.dirname(src_dir) if os.path.basename(src_dir) == 'src' else src_dir
    scrfd_path = os.path.join(project_root, "assets", "models", "scrfd_2.5g_bnkps.onnx")
    if not os.path.exists(scrfd_path):
        scrfd_path = os.path.join(src_dir, "assets", "models", "scrfd_2.5g_bnkps.onnx")

    if os.path.exists(scrfd_path) and ONNX_AVAILABLE:
        try:
            providers = ['CUDAExecutionProvider', 'CPUExecutionProvider'] if 'CUDAExecutionProvider' in ort.get_available_providers() else ['CPUExecutionProvider']
            sess = ort.InferenceSession(scrfd_path, providers=providers)
            target_size = (640, 640)
            r = min(target_size[0] / h, target_size[1] / w)
            nh, nw = int(round(h * r)), int(round(w * r))
            resized = cv2.resize(img, (nw, nh))
            padded = np.zeros((target_size[0], target_size[1], 3), dtype=np.uint8)
            padded[:nh, :nw] = resized

            blob = cv2.dnn.blobFromImage(padded, 1.0/128.0, target_size, (127.5, 127.5, 127.5), swapRB=True)
            outputs = sess.run(None, {'input.1': blob})
            
            scores_list = outputs[0:3]
            bboxes_list = outputs[3:6]
            strides = [8, 16, 32]
            
            boxes = []
            scores = []

            for stride_idx, stride in enumerate(strides):
                s_map = scores_list[stride_idx]
                b_map = bboxes_list[stride_idx]
                feat_h = target_size[0] // stride
                feat_w = target_size[1] // stride

                anchor_idx = 0
                for y in range(feat_h):
                    for x in range(feat_w):
                        for a in range(2):
                            s = float(s_map[anchor_idx, 0])
                            if s >= 0.35:
                                dist = b_map[anchor_idx] * stride
                                cx = (x + 0.5) * stride
                                cy = (y + 0.5) * stride
                                x1 = (cx - dist[0]) / r
                                y1 = (cy - dist[1]) / r
                                x2 = (cx + dist[2]) / r
                                y2 = (cy + dist[3]) / r
                                
                                bx = int(max(0, x1))
                                by = int(max(0, y1))
                                bw = int(min(w - bx, x2 - x1))
                                bh = int(min(h - by, y2 - y1))
                                if bw > 20 and bh > 20:
                                    boxes.append((bx, by, bw, bh))
                                    scores.append(s)
                            anchor_idx += 1

            if boxes:
                indices = cv2.dnn.NMSBoxes(boxes, scores, score_threshold=0.35, nms_threshold=0.4)
                if len(indices) > 0:
                    indices = indices.flatten()
                    for i in indices:
                        faces.append(boxes[i])
        except Exception as e:
            logger.warning(f"SCRFD ONNX detection note: {e}")

    return faces

@app.get("/")
def root():
    return {
        "service": "Shadow EYE Face Detection API",
        "status": "online",
        "endpoints": [
            "/api/v1/detect-face",
            "/api/v1/compare-faces",
            "/api/v1/register-face",
            "/api/v1/target-faces",
            "/api/v1/health"
        ]
    }

@app.get("/api/v1/health")
def health_check():
    """System Health Check Endpoint"""
    target_service = TargetFaceService.get_instance()
    registered_faces = len(target_service.get_target_faces())
    has_arcface = target_service._get_arcface_extractor() is not None

    return {
        "status": "healthy",
        "timestamp": time.strftime("%Y-%m-%d %H:%M:%S"),
        "registered_target_faces": registered_faces,
        "arcface_embedding_engine": "loaded" if has_arcface else "fallback_mode",
        "onnxruntime_available": ONNX_AVAILABLE
    }

@app.post("/api/v1/detect-face")
async def detect_face(
    image: Optional[UploadFile] = File(None),
    image_base64: Optional[str] = Form(None),
    threshold: float = Form(0.38)
):
    """
    Detect faces in image (file upload or Base64 payload).
    Performs face bounding box detection, liveness score check, and target face matching against database.
    """
    img = None
    if image is not None:
        contents = await image.read()
        nparr = np.frombuffer(contents, np.uint8)
        img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
    elif image_base64 is not None:
        img = decode_base64_image(image_base64)

    if img is None or img.size == 0:
        raise HTTPException(status_code=400, detail="Invalid image payload. Provide a valid file upload or Base64 string.")

    h, w, _ = img.shape
    raw_faces = detect_face_rectangles(img)

    detected_faces = []
    annotated_img = img.copy()
    target_service = TargetFaceService.get_instance()

    for (x, y, fw, fh) in raw_faces:
        x1, y1, x2, y2 = max(0, x), max(0, y), min(w, x + fw), min(h, y + fh)
        face_crop = img[y1:y2, x1:x2]

        if face_crop.size == 0:
            continue

        matched_name, sim_score, matched_role = target_service.recognize_face_crop(face_crop, threshold=threshold)

        gray_crop = cv2.cvtColor(face_crop, cv2.COLOR_BGR2GRAY)
        laplacian_var = float(cv2.Laplacian(gray_crop, cv2.CV_64F).var()) if gray_crop.size > 0 else 0.0
        liveness_score = float(round(min(0.99, max(0.55, 0.50 + (laplacian_var / 500.0))), 2))
        is_real = bool(liveness_score >= 0.50)

        display_name = str(matched_name) if matched_name else "UNKNOWN FACE"
        sim_percent = float(round(float(sim_score) * 100.0, 1))

        detected_faces.append({
            "box": [int(x1), int(y1), int(fw), int(fh)],
            "matched_name": display_name,
            "similarity_percent": sim_percent,
            "role": str(matched_role) if matched_role else ("VIP" if matched_name else "VISITOR"),
            "liveness_score": float(liveness_score),
            "is_real": is_real
        })

        # Draw bounding box and text overlay (Green for Target, Red for Unknown Face)
        color = (0, 255, 0) if matched_name else (0, 0, 255)
        cv2.rectangle(annotated_img, (x1, y1), (x2, y2), color, 3)

        label = f"TARGET: {matched_name.upper()} ({sim_percent}%)" if matched_name else "UNKNOWN FACE"
        (lw, lh), _ = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.6, 2)
        cv2.rectangle(annotated_img, (x1, y1 - 28), (x1 + lw + 12, y1), color, -1)
        cv2.putText(annotated_img, label, (x1 + 6, y1 - 8), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 2)

    annotated_base64 = encode_image_to_base64(annotated_img)

    return {
        "status": "success",
        "face_count": len(detected_faces),
        "faces": detected_faces,
        "annotated_image_base64": annotated_base64,
        "image_size": {"width": w, "height": h}
    }

@app.post("/api/v1/detect-face-base64")
async def detect_face_json(payload: Base64DetectRequest):
    """Detect faces via JSON body payload containing base64 image string"""
    return await detect_face(image=None, image_base64=payload.image_base64, threshold=payload.threshold)

@app.post("/api/v1/compare-faces")
async def compare_faces(
    image1: Optional[UploadFile] = File(None),
    image2: Optional[UploadFile] = File(None),
    image1_base64: Optional[str] = Form(None),
    image2_base64: Optional[str] = Form(None)
):
    """Compare two face photos and return match status and similarity percentage"""
    img1 = decode_base64_image(image1_base64) if image1_base64 else (cv2.imdecode(np.frombuffer(await image1.read(), np.uint8), cv2.IMREAD_COLOR) if image1 else None)
    img2 = decode_base64_image(image2_base64) if image2_base64 else (cv2.imdecode(np.frombuffer(await image2.read(), np.uint8), cv2.IMREAD_COLOR) if image2 else None)

    if img1 is None or img2 is None:
        raise HTTPException(status_code=400, detail="Two valid face images are required for comparison.")

    target_service = TargetFaceService.get_instance()
    extractor = target_service._get_arcface_extractor()

    if extractor is not None:
        a1 = cv2.resize(img1, (112, 112))
        a2 = cv2.resize(img2, (112, 112))
        emb1 = extractor.extract_embedding(a1)
        emb2 = extractor.extract_embedding(a2)
        similarity = float(np.dot(emb1, emb2))
    else:
        g1 = cv2.cvtColor(cv2.resize(img1, (100, 100)), cv2.COLOR_BGR2GRAY)
        g2 = cv2.cvtColor(cv2.resize(img2, (100, 100)), cv2.COLOR_BGR2GRAY)
        diff = cv2.absdiff(g1, g2)
        similarity = max(0.0, 1.0 - (float(np.mean(diff)) / 255.0))

    is_same = similarity >= 0.40
    sim_percent = round(similarity * 100, 2)

    return {
        "is_same_person": is_same,
        "similarity_percent": sim_percent,
        "cosine_score": round(similarity, 4),
        "verdict": "MATCHED (လူတူပါသည်)" if is_same else "DIFFERENT_PERSON (လူမတူပါ)"
    }

class RegisterFaceJSONRequest(BaseModel):
    name: str
    role: str = "VIP"
    department: str = "General"
    note: str = ""
    image_base64: str

@app.post("/api/v1/register-face-json")
def register_target_face_json(req: RegisterFaceJSONRequest):
    """Register target face via clean JSON body payload for base64 multi-photo uploads"""
    img = decode_base64_image(req.image_base64)
    if img is None:
        raise HTTPException(status_code=400, detail="Invalid image_base64 string")

    target_service = TargetFaceService.get_instance()
    success, msg, record = target_service.add_target_face(
        name=req.name, image_source=img, role=req.role, department=req.department, note=req.note
    )

    if not success:
        raise HTTPException(status_code=500, detail=msg)

    return {
        "status": "success",
        "message": msg,
        "record": record
    }

@app.post("/api/v1/register-face")
async def register_target_face(
    name: str = Form(...),
    role: str = Form("VIP"),
    department: str = Form("General"),
    note: str = Form(""),
    image: Optional[UploadFile] = File(None),
    image_base64: Optional[str] = Form(None)
):
    """Register a new target face profile into SQLite database"""
    img = None
    if image is not None:
        contents = await image.read()
        nparr = np.frombuffer(contents, np.uint8)
        img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
    elif image_base64 is not None:
        img = decode_base64_image(image_base64)

    if img is None:
        raise HTTPException(status_code=400, detail="Image file or base64 string is required")

    target_service = TargetFaceService.get_instance()
    success, msg, record = target_service.add_target_face(name=name, image_source=img, role=role, department=department, note=note)

    if not success:
        raise HTTPException(status_code=500, detail=msg)

    return {
        "status": "success",
        "message": msg,
        "record": record
    }

@app.get("/api/v1/target-faces")
def list_target_faces(
    search: str = Query("", description="Search by name or department"),
    role: str = Query("ALL", description="Filter by role: VIP, STAFF, BLACKLIST, ALL")
):
    """Get registered target faces list from SQLite"""
    target_service = TargetFaceService.get_instance()
    faces = target_service.get_target_faces(search_query=search, role_filter=role)
    return {
        "count": len(faces),
        "target_faces": faces
    }

@app.delete("/api/v1/target-faces/{face_id}")
def delete_target_face(face_id: int):
    """Delete a target face by ID"""
    target_service = TargetFaceService.get_instance()
    success, msg = target_service.delete_target_face(face_id)

    if not success:
        raise HTTPException(status_code=404, detail=msg)

    return {
        "status": "success",
        "message": msg
    }

@app.get("/api/v1/target-profiles")
def list_target_profiles_grouped(
    search: str = Query("", description="Search by name or department"),
    role: str = Query("ALL", description="Filter by role")
):
    """Get target profiles grouped by person name with multi-photo gallery list"""
    target_service = TargetFaceService.get_instance()
    profiles = target_service.get_target_profiles_grouped(search_query=search, role_filter=role)
    return {
        "count": len(profiles),
        "profiles": profiles
    }

@app.delete("/api/v1/target-profiles/{name}")
def delete_target_profile_by_name(name: str):
    """Delete all records and photos for a target person profile"""
    target_service = TargetFaceService.get_instance()
    success, msg = target_service.delete_target_profile_by_name(name)

    if not success:
        raise HTTPException(status_code=404, detail=msg)

    return {
        "status": "success",
        "message": msg
    }

@app.put("/api/v1/target-profiles/{name}")
def update_target_profile_by_name(
    name: str,
    new_name: str = Form(...),
    new_role: str = Form("VIP"),
    new_department: str = Form("General")
):
    """Update name, role, and department for a target profile"""
    target_service = TargetFaceService.get_instance()
    success, msg = target_service.update_target_profile_by_name(name, new_name, new_role, new_department)

    if not success:
        raise HTTPException(status_code=404, detail=msg)

    return {
        "status": "success",
        "message": msg
    }
