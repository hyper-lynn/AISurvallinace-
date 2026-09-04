"""
src/services/target_face_service.py
Service for managing target face profiles, persistent database storage (SQLite),
and 512-d ArcFace embedding auto-extraction for 2.5D Real-Time Face Recognition.
"""

import os
import sys
import glob
import ctypes
import site
import sqlite3
import json
import time
import cv2
import numpy as np

# Preload CUDA 13 / 12 & cuDNN DLLs for ONNX Runtime GPU Provider
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

from typing import List, Dict, Optional, Tuple, Any
from config import logger
from services.face_2d5_pipeline import ArcFaceExtractor, align_face_112

# Optional FAISS GPU vector index for high-performance face matching (>1000 faces)
try:
    import logging
    logging.getLogger("faiss").setLevel(logging.ERROR)
    import faiss
    FAISS_AVAILABLE = True
except ImportError:
    faiss = None
    FAISS_AVAILABLE = False

class TargetFaceService:
    _instance = None

    @classmethod
    def get_instance(cls):
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

    def __init__(self):
        base_dir = os.path.dirname(os.path.dirname(os.path.dirname(__file__)))
        self.db_dir = os.path.join(base_dir, "data")
        self.faces_img_dir = os.path.join(base_dir, "assets", "target_faces")
        os.makedirs(self.db_dir, exist_ok=True)
        os.makedirs(self.faces_img_dir, exist_ok=True)

        self.db_path = os.path.join(self.db_dir, "target_faces.db")
        self._init_db()

        # ArcFace Extractor instance lazy loading
        self.arcface_model = None
        self.arcface_model_path = os.path.join(base_dir, "assets", "models", "w600k_r50.onnx")

        # In-memory vector cache for zero-latency face matching
        self._cached_names = None
        self._cached_roles = None
        self._cached_matrix = None
        self._cache_valid = False
        self._faiss_index = None

    def invalidate_cache(self):
        """Invalidate in-memory target face vector cache and FAISS index"""
        self._cache_valid = False
        self._cached_names = None
        self._cached_roles = None
        self._cached_matrix = None
        self._faiss_index = None

    def _rebuild_missing_embeddings(self):
        """Self-healing: Auto-extract ArcFace embeddings for any stored DB profiles missing vectors"""
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            cursor.execute("SELECT id, name, image_path, embedding FROM target_faces")
            rows = cursor.fetchall()
            updated = 0
            for r in rows:
                fid, name, img_path, emb_str = r[0], r[1], r[2], r[3]
                emb_list = json.loads(emb_str) if emb_str else []
                if len(emb_list) != 512 and os.path.exists(img_path):
                    img = cv2.imread(img_path)
                    if img is not None:
                        aligned = cv2.resize(img, (112, 112))
                        ext = self._get_arcface_extractor()
                        if ext:
                            emb = ext.extract_embedding(aligned)
                            if emb is not None and len(emb) == 512:
                                cursor.execute("UPDATE target_faces SET embedding = ? WHERE id = ?", (json.dumps(emb.tolist()), fid))
                                updated += 1
            if updated > 0:
                conn.commit()
                self.invalidate_cache()
                logger.info(f"TargetFaceService auto-rebuilt {updated} missing face embeddings in DB.")
            conn.close()
        except Exception as e:
            logger.debug(f"TargetFaceService embedding rebuild check note: {e}")

    def _init_db(self):
        """Initialize target faces table in SQLite"""
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            cursor.execute("""
                CREATE TABLE IF NOT EXISTS target_faces (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    name TEXT NOT NULL,
                    role TEXT NOT NULL DEFAULT 'VIP',
                    department TEXT DEFAULT 'General',
                    note TEXT DEFAULT '',
                    image_path TEXT NOT NULL,
                    embedding TEXT,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                )
            """)
            conn.commit()
            conn.close()
            logger.info(f"TargetFace DB initialized at {self.db_path}")
        except Exception as e:
            logger.error(f"Failed to initialize TargetFace DB: {e}")

    def _get_arcface_extractor(self) -> Optional[ArcFaceExtractor]:
        """Lazy load ArcFace IR-50 model"""
        if self.arcface_model is not None:
            return self.arcface_model

        if os.path.exists(self.arcface_model_path):
            try:
                self.arcface_model = ArcFaceExtractor(self.arcface_model_path)
                logger.info("ArcFace IR-50 model loaded successfully for TargetFaceService.")
            except Exception as e:
                logger.error(f"Failed to load ArcFace extractor: {e}")
                self.arcface_model = None
        return self.arcface_model

    def add_target_face(self, name: str, role: str, department: str, image_source: Any, note: str = "") -> Tuple[bool, str, Optional[Dict]]:
        """
        Add new target face:
        image_source can be a file path (str) or a numpy array BGR image frame (from camera)
        """
        if not name or not name.strip():
            return False, "Target name cannot be empty", None

        # Load image
        if isinstance(image_source, str):
            if not os.path.exists(image_source):
                return False, f"Image file not found: {image_source}", None
            img = cv2.imread(image_source)
        elif isinstance(image_source, np.ndarray):
            img = image_source
        else:
            return False, "Invalid image source type", None

        if img is None or img.size == 0:
            return False, "Could not decode image", None

        # Auto-detect & crop face from target registration photo for high precision ArcFace embedding
        img_to_save = img
        try:
            from api.face_api import detect_face_rectangles
            face_rects = detect_face_rectangles(img)
            if face_rects:
                x, y, fw, fh = face_rects[0]
                h_img, w_img, _ = img.shape
                x1, y1 = max(0, x), max(0, y)
                x2, y2 = min(w_img, x + fw), min(h_img, y + fh)
                crop = img[y1:y2, x1:x2]
                if crop.size > 0:
                    img_to_save = crop
        except Exception:
            pass

        # Generate unique filename using UUID
        import uuid
        filename = f"face_{uuid.uuid4().hex}.jpg"
        save_path = os.path.join(self.faces_img_dir, filename)

        # Resize & save standard 112x112 face crop
        aligned_112 = cv2.resize(img_to_save, (112, 112))
        cv2.imwrite(save_path, img_to_save)

        # Extract 512d ArcFace Embedding
        embedding_list = []
        extractor = self._get_arcface_extractor()
        if extractor is not None:
            try:
                emb = extractor.extract_embedding(aligned_112)
                embedding_list = emb.tolist()
            except Exception as e:
                logger.warning(f"Could not extract ArcFace embedding: {e}")

        embedding_json = json.dumps(embedding_list) if embedding_list else None

        # Insert into SQLite
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            cursor.execute("""
                INSERT INTO target_faces (name, role, department, note, image_path, embedding)
                VALUES (?, ?, ?, ?, ?, ?)
            """, (name.strip(), role.strip().upper(), department.strip(), note.strip(), save_path, embedding_json))
            conn.commit()
            new_id = cursor.lastrowid
            conn.close()

            self.invalidate_cache()
            record = {
                "id": new_id,
                "name": name.strip(),
                "role": role.strip().upper(),
                "department": department.strip(),
                "note": note.strip(),
                "image_path": save_path,
                "has_embedding": bool(embedding_list),
                "created_at": time.strftime("%Y-%m-%d %H:%M:%S")
            }
            logger.info(f"Target face registered: {name} (ID: {new_id})")
            return True, f"Target face '{name}' registered successfully!", record
        except Exception as e:
            logger.error(f"Error inserting target face to DB: {e}")
            return False, f"Database error: {str(e)}", None

    def get_target_faces(self, search_query: str = "", role_filter: str = "ALL") -> List[Dict]:
        """Fetch target faces with filtering"""
        results = []
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            query = "SELECT id, name, role, department, note, image_path, embedding, created_at FROM target_faces WHERE 1=1"
            params = []

            if search_query:
                query += " AND (name LIKE ? OR department LIKE ? OR note LIKE ?)"
                q = f"%{search_query}%"
                params.extend([q, q, q])

            if role_filter and role_filter.upper() != "ALL":
                query += " AND role = ?"
                params.append(role_filter.upper())

            query += " ORDER BY id DESC"
            cursor.execute(query, params)
            rows = cursor.fetchall()
            conn.close()

            for row in rows:
                emb_json = row[6]
                emb = json.loads(emb_json) if emb_json else []
                results.append({
                    "id": row[0],
                    "name": row[1],
                    "role": row[2],
                    "department": row[3],
                    "note": row[4],
                    "image_path": row[5],
                    "has_embedding": len(emb) > 0,
                    "embedding": emb,
                    "created_at": row[7]
                })
        except Exception as e:
            logger.error(f"Error reading target faces from DB: {e}")

        return results

    def get_target_profiles_grouped(self, search_query: str = "", role_filter: str = "ALL") -> List[Dict]:
        """Fetch target face profiles grouped by person name with multi-photo gallery list"""
        import base64
        faces = self.get_target_faces(search_query=search_query, role_filter=role_filter)
        grouped = {}

        for f in faces:
            name = f["name"]
            img_path = f["image_path"]
            b64_src = ""
            if os.path.exists(img_path):
                try:
                    with open(img_path, "rb") as img_file:
                        encoded = base64.b64encode(img_file.read()).decode("utf-8")
                        b64_src = f"data:image/jpeg;base64,{encoded}"
                except Exception:
                    pass

            if name not in grouped:
                grouped[name] = {
                    "id": f["id"],
                    "name": f["name"],
                    "role": f["role"],
                    "department": f["department"],
                    "note": f["note"],
                    "created_at": f["created_at"],
                    "profile_picture": b64_src,
                    "photos": [b64_src] if b64_src else [],
                    "record_ids": [f["id"]]
                }
            else:
                if b64_src and b64_src not in grouped[name]["photos"]:
                    grouped[name]["photos"].append(b64_src)
                grouped[name]["record_ids"].append(f["id"])

        return list(grouped.values())

    def delete_target_profile_by_name(self, name: str) -> Tuple[bool, str]:
        """Delete all target face records and images associated with a person name"""
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            cursor.execute("SELECT id, image_path FROM target_faces WHERE name = ?", (name,))
            rows = cursor.fetchall()
            if not rows:
                conn.close()
                return False, "Target profile not found"

            for r in rows:
                img_path = r[1]
                if os.path.exists(img_path):
                    try:
                        os.remove(img_path)
                    except Exception:
                        pass

            cursor.execute("DELETE FROM target_faces WHERE name = ?", (name,))
            conn.commit()
            conn.close()

            self.invalidate_cache()
            logger.info(f"Target profile deleted: {name}")
            return True, f"Target profile '{name}' deleted successfully"
        except Exception as e:
            logger.error(f"Failed to delete target profile: {e}")
            return False, f"Error deleting target profile: {str(e)}"

    def update_target_profile_by_name(self, old_name: str, new_name: str, new_role: str, new_dept: str) -> Tuple[bool, str]:
        """Update target profile name, role, and department across all matching records"""
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            cursor.execute("""
                UPDATE target_faces
                SET name = ?, role = ?, department = ?
                WHERE name = ?
            """, (new_name.strip(), new_role.strip().upper(), new_dept.strip(), old_name.strip()))
            conn.commit()
            updated_count = cursor.rowcount
            conn.close()

            if updated_count == 0:
                return False, f"Target profile '{old_name}' not found"

            self.invalidate_cache()
            logger.info(f"Updated {updated_count} records for target profile '{old_name}' -> '{new_name}'")
            return True, f"Target profile '{new_name}' updated successfully!"
        except Exception as e:
            logger.error(f"Failed to update target profile: {e}")
            return False, f"Error updating profile: {str(e)}"

    def delete_target_face(self, face_id: int) -> Tuple[bool, str]:
        """Delete target face record and image file"""
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            cursor.execute("SELECT image_path, name FROM target_faces WHERE id = ?", (face_id,))
            row = cursor.fetchone()
            if not row:
                conn.close()
                return False, "Target face record not found"

            img_path, name = row[0], row[1]
            cursor.execute("DELETE FROM target_faces WHERE id = ?", (face_id,))
            conn.commit()
            conn.close()

            if os.path.exists(img_path):
                try:
                    os.remove(img_path)
                except Exception:
                    pass

            self.invalidate_cache()
            logger.info(f"Target face deleted: {name} (ID: {face_id})")
            return True, f"Target face '{name}' deleted successfully"
        except Exception as e:
            logger.error(f"Failed to delete target face: {e}")
            return False, f"Error deleting target face: {str(e)}"

    def get_known_embeddings_matrix(self) -> Tuple[List[str], List[str], np.ndarray]:
        """Returns lists of names, roles, and 2D matrix of embeddings for fast matching.
        Multiple embeddings for the same person are averaged (mean fusion) for robustness."""
        if self._cache_valid and self._cached_matrix is not None:
            return self._cached_names, self._cached_roles, self._cached_matrix

        # Collect all valid embeddings grouped by person name
        name_embeddings = {}  # {name: [emb1, emb2, ...]}
        name_roles = {}       # {name: role}
        faces = self.get_target_faces(role_filter="ALL")
        for f in faces:
            if f["has_embedding"] and len(f["embedding"]) == 512:
                name = f["name"]
                if name not in name_embeddings:
                    name_embeddings[name] = []
                    name_roles[name] = f.get("role", "VIP")
                name_embeddings[name].append(f["embedding"])

        names = []
        roles = []
        embeddings = []
        for name, emb_list in name_embeddings.items():
            # Mean fusion: average all embeddings for the same person
            if len(emb_list) == 1:
                fused = np.array(emb_list[0], dtype=np.float32)
            else:
                fused = np.mean(emb_list, axis=0).astype(np.float32)
            # Re-normalize after fusion
            norm = np.linalg.norm(fused)
            if norm > 0:
                fused = fused / norm
            names.append(name)
            roles.append(name_roles[name])
            embeddings.append(fused.tolist())

        if not embeddings:
            self._cached_names = []
            self._cached_roles = []
            self._cached_matrix = np.empty((0, 512), dtype=np.float32)
        else:
            self._cached_names = names
            self._cached_roles = roles
            self._cached_matrix = np.array(embeddings, dtype=np.float32)

        self._cache_valid = True
        return self._cached_names, self._cached_roles, self._cached_matrix

    def has_targets(self) -> bool:
        """Fast check: returns True if any target face embeddings are registered in cache/DB."""
        if self._cache_valid:
            return self._cached_matrix is not None and self._cached_matrix.shape[0] > 0
        _, _, matrix = self.get_known_embeddings_matrix()
        return matrix.shape[0] > 0


    def recognize_face_crop(
        self,
        face_crop: np.ndarray,
        landmarks: Optional[np.ndarray] = None,
        threshold: float = 0.38
    ) -> Tuple[Optional[str], float, Optional[str]]:
        """
        Recognize face crop against stored target faces in memory cache.
        Supports 5-landmark geometric affine alignment (align_face_112) and IQA quality filtering.
        Zero DB queries during stream processing for ultra-fast performance.
        Returns: (matched_name, similarity_score, role)
        """
        if face_crop is None or face_crop.size == 0:
            return None, 0.0, None

        # ─── Image Quality Assessment (IQA Filter) ─────────────────────────
        fh, fw = face_crop.shape[:2]
        if fw < 24 or fh < 24:
            return None, 0.0, None  # Skip tiny blurry crops to prevent false matches

        try:
            gray_crop = cv2.cvtColor(face_crop, cv2.COLOR_BGR2GRAY)
            blur_score = cv2.Laplacian(gray_crop, cv2.CV_64F).var()
            if blur_score < 12.0:
                return None, 0.0, None  # Skip severely out-of-focus blurry crops
        except Exception:
            pass

        extractor = self._get_arcface_extractor()
        if extractor is None:
            return None, 0.0, None

        try:
            # ─── 5-Landmark Affine Alignment or Resizing ───────────────────────
            if landmarks is not None and isinstance(landmarks, np.ndarray) and landmarks.shape == (5, 2):
                aligned = align_face_112(face_crop, landmarks)
            else:
                aligned = cv2.resize(face_crop, (112, 112))

            live_emb = extractor.extract_embedding(aligned)
            if live_emb is None or len(live_emb) != 512:
                return None, 0.0, None

            names, roles, matrix = self.get_known_embeddings_matrix()
            if matrix.shape[0] == 0:
                return None, 0.0, None

            # High-speed vectorized dot product across all registered target face templates
            scores = np.dot(matrix, live_emb) # shape (N,)
            best_idx = int(np.argmax(scores))
            best_score = float(scores[best_idx])

            if best_score >= threshold:
                return names[best_idx], best_score, roles[best_idx]

            return None, 0.0, None
        except Exception as e:
            logger.debug(f"Face recognition crop error: {e}")
            return None, 0.0, None

    def recognize_faces_batch(
        self,
        face_crops: List[np.ndarray],
        landmarks_list: List[Optional[np.ndarray]] = None,
        threshold: float = 0.38
    ) -> List[Tuple[Optional[str], float, Optional[str]]]:
        """
        Batch face recognition for crowd mode: process multiple face crops in a single
        vectorized matrix operation for significantly faster throughput.
        Returns: list of (matched_name, similarity_score, role) tuples, one per input crop.
        """
        if not face_crops:
            return []

        extractor = self._get_arcface_extractor()
        if extractor is None:
            return [(None, 0.0, None)] * len(face_crops)

        names, roles, matrix = self.get_known_embeddings_matrix()
        if matrix.shape[0] == 0:
            return [(None, 0.0, None)] * len(face_crops)

        if landmarks_list is None:
            landmarks_list = [None] * len(face_crops)

        # Extract embeddings for all valid face crops
        valid_embeddings = []
        valid_indices = []
        results = [(None, 0.0, None)] * len(face_crops)

        for i, face_crop in enumerate(face_crops):
            if face_crop is None or face_crop.size == 0:
                continue

            fh, fw = face_crop.shape[:2]
            if fw < 24 or fh < 24:
                continue

            try:
                gray_crop = cv2.cvtColor(face_crop, cv2.COLOR_BGR2GRAY)
                blur_score = cv2.Laplacian(gray_crop, cv2.CV_64F).var()
                if blur_score < 12.0:
                    continue
            except Exception:
                pass

            try:
                lm = landmarks_list[i] if i < len(landmarks_list) else None
                if lm is not None and isinstance(lm, np.ndarray) and lm.shape == (5, 2):
                    aligned = align_face_112(face_crop, lm)
                else:
                    aligned = cv2.resize(face_crop, (112, 112))

                emb = extractor.extract_embedding(aligned)
                if emb is not None and len(emb) == 512:
                    valid_embeddings.append(emb)
                    valid_indices.append(i)
            except Exception:
                continue

        if not valid_embeddings:
            return results

        # Batch vectorized matching: (M_faces x 512) @ (512 x N_targets) = (M_faces x N_targets)
        batch_emb = np.array(valid_embeddings, dtype=np.float32)  # (M, 512)
        all_scores = np.dot(batch_emb, matrix.T)  # (M, N)

        for idx, orig_i in enumerate(valid_indices):
            best_target = int(np.argmax(all_scores[idx]))
            best_score = float(all_scores[idx][best_target])
            if best_score >= threshold:
                results[orig_i] = (names[best_target], best_score, roles[best_target])

        return results

    def _build_faiss_index(self, matrix: np.ndarray) -> None:
        """Build FAISS IndexFlatIP for GPU-accelerated face vector search"""
        if not FAISS_AVAILABLE or matrix.shape[0] == 0:
            return
        try:
            index = faiss.IndexFlatIP(512)  # Inner Product (equivalent to cosine on normalized vectors)
            # Try GPU index for GTX 1650 acceleration
            try:
                gpu_res = faiss.StandardGpuResources()
                gpu_res.setTempMemory(64 * 1024 * 1024)  # 64MB temp memory limit
                self._faiss_index = faiss.index_cpu_to_gpu(gpu_res, 0, index)
                logger.info("FAISS GPU index built successfully.")
            except Exception:
                self._faiss_index = index  # Fallback to CPU FAISS
                logger.info("FAISS CPU index built (GPU not available).")
            self._faiss_index.add(matrix)
        except Exception as e:
            logger.warning(f"FAISS index build failed, using NumPy fallback: {e}")
            self._faiss_index = None

    def search_faiss(self, query_embedding: np.ndarray, threshold: float = 0.48) -> Tuple[Optional[str], float, Optional[str]]:
        """Search registered faces using FAISS index (GPU-accelerated if available)"""
        names, roles, matrix = self.get_known_embeddings_matrix()
        if matrix.shape[0] == 0:
            return None, 0.0, None

        # Build FAISS index if not cached
        if FAISS_AVAILABLE and self._faiss_index is None:
            self._build_faiss_index(matrix)

        if self._faiss_index is not None and FAISS_AVAILABLE:
            try:
                query = query_embedding.reshape(1, -1).astype(np.float32)
                scores, indices = self._faiss_index.search(query, k=1)
                best_score = float(scores[0][0])
                best_idx = int(indices[0][0])
                if best_score >= threshold and 0 <= best_idx < len(names):
                    return names[best_idx], best_score, roles[best_idx]
                return None, 0.0, None
            except Exception as e:
                logger.debug(f"FAISS search error, falling back to NumPy: {e}")

        # Fallback: NumPy dot product
        scores = np.dot(matrix, query_embedding)
        best_idx = int(np.argmax(scores))
        best_score = float(scores[best_idx])
        if best_score >= threshold:
            return names[best_idx], best_score, roles[best_idx]
        return None, 0.0, None

