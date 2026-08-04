import sys
import os
import base64
import asyncio
import time
import io
import urllib.parse
from typing import Optional, Callable

def sanitize_rtsp_url(url: str) -> str:
    """Fix RTSP URLs where passwords contain special characters like '@' causing '@@'."""
    if not isinstance(url, str) or not (url.startswith("rtsp://") or url.startswith("rtsps://")):
        return url
    try:
        proto, rest = url.split("://", 1)
        if "@@" in rest:
            user_pass, host_path = rest.rsplit("@@", 1)
            if ":" in user_pass:
                user, pwd = user_pass.split(":", 1)
                encoded_pwd = urllib.parse.quote(pwd + "@", safe="")
                return f"{proto}://{user}:{encoded_pwd}@{host_path}"
    except Exception:
        pass
    return url


# Ensure src root directory is in sys.path
SRC_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
if SRC_DIR not in sys.path:
    sys.path.insert(0, SRC_DIR)

# Fallback: Add global site-packages if running inside a venv or custom launcher without cv2 installed
GLOBAL_SITE_PACKAGES = [
    r"C:\Users\lynn\AppData\Local\Programs\Python\Python312\Lib\site-packages",
    r"C:\Users\lynn\AppData\Local\Programs\Python\Python311\Lib\site-packages",
    os.path.join(os.path.dirname(sys.executable), "Lib", "site-packages")
]
for pkg_path in GLOBAL_SITE_PACKAGES:
    if os.path.exists(pkg_path) and pkg_path not in sys.path:
        sys.path.append(pkg_path)

# Configure OpenCV FFmpeg RTSP stream options & silence OpenCV internal C++ warnings
os.environ["OPENCV_FFMPEG_CAPTURE_OPTIONS"] = "rtsp_transport;tcp|stimeout;3000000"
os.environ["OPENCV_LOG_LEVEL"] = "OFF"

try:
    from config import logger
except Exception:
    import logging
    logger = logging.getLogger("CameraController")

try:
    from services.dahua_p2p_service import DahuaP2PService
    DAHUA_P2P_SERVICE_AVAILABLE = True
except Exception:
    DahuaP2PService = None
    DAHUA_P2P_SERVICE_AVAILABLE = False

try:
    from services.dahua_netsdk_service import DahuaNetSDKService
    DAHUA_NETSDK_SERVICE_AVAILABLE = True
except Exception:
    DahuaNetSDKService = None
    DAHUA_NETSDK_SERVICE_AVAILABLE = False

try:
    import cv2
    import numpy as np
    from PIL import Image, ImageDraw, ImageFont
    OPENCV_AVAILABLE = True
    try:
        cv2.utils.logging.setLogLevel(cv2.utils.logging.LOG_LEVEL_SILENT)
    except Exception:
        pass
except Exception as ie:
    cv2 = None
    np = None
    OPENCV_AVAILABLE = False
    logger.warning(f"OpenCV/PIL not fully available ({ie}). CameraController will use synthetic stream mode.")


import concurrent.futures

CAMERA_EXECUTOR = concurrent.futures.ThreadPoolExecutor(max_workers=8, thread_name_prefix="CamWorker")


class CameraController:
    """
    PC Webcam & Tactical Camera Controller for Live Monitoring View.
    Handles OpenCV VideoCapture(source), RTSP wireless/wired CCTV streams,
    frame conversion to base64, camera switching, and synthetic tactical HUD stream fallback.
    Uses ThreadPoolExecutor to prevent any GIL or asyncio thread UI freeze.
    """
    def __init__(self, source: str = "0", device_id: Optional[int] = None):
        if device_id is not None:
            self.source = str(device_id)
        else:
            self.source = str(source)
        self.cap = None
        self.is_running = False
        self.is_recording = True
        self.hud_enabled = True
        self.ai_detection_enabled = False
        self.last_alert_time = 0
        self.alert_cooldown_seconds = 30
        self.ai_last_detections = []
        self._frame_callback: Optional[Callable[[str], None]] = None
        self.on_fall_detected_callback: Optional[Callable[[str, str], None]] = None

    def start(self, frame_callback: Callable[[str], None]):
        """Start streaming camera frames asynchronously without blocking UI thread"""
        self.subscribe_frames(frame_callback)

    def subscribe_frames(self, frame_callback: Callable[[str], None]):
        """Subscribe frame callback listener and start camera feed."""
        if self.is_running and self._frame_callback == frame_callback and self.cap is not None:
            return

        self._frame_callback = frame_callback
        self.is_running = True
        
        async def _async_init_and_loop():
            loop = asyncio.get_running_loop()

            def open_cam_blocking():
                if not OPENCV_AVAILABLE:
                    return None
                try:
                    if self.source.isdigit():
                        dev_id = int(self.source)
                        backends = [cv2.CAP_DSHOW, cv2.CAP_MSMF, cv2.CAP_ANY] if sys.platform == "win32" else [cv2.CAP_ANY]
                        
                        # Try requested webcam index first
                        for b in backends:
                            try:
                                c = cv2.VideoCapture(dev_id, b)
                                if c and c.isOpened():
                                    for _ in range(5):
                                        ret, test_frame = c.read()
                                        if ret and test_frame is not None:
                                            logger.info(f"PC Webcam device index {dev_id} verified working with backend {b}.")
                                            return c
                                        time.sleep(0.05)
                                    c.release()
                            except Exception as ex:
                                pass

                        # Fallback to primary webcam index 0 if requested index (e.g. index 1) is not plugged in / out of range
                        if dev_id != 0:
                            logger.info(f"Webcam index {dev_id} unavailable. Attempting default webcam index 0 fallback.")
                            for b in backends:
                                try:
                                    c = cv2.VideoCapture(0, b)
                                    if c and c.isOpened():
                                        for _ in range(5):
                                            ret, test_frame = c.read()
                                            if ret and test_frame is not None:
                                                logger.info(f"Fallback PC Webcam device index 0 verified working with backend {b}.")
                                                return c
                                            time.sleep(0.05)
                                        c.release()
                                except Exception:
                                    pass
                    elif self.source.startswith("p2p://") or self.source.upper().startswith("SN:") or "DAHUA" in self.source.upper():
                        sn = self.source.replace("p2p://", "").replace("SN:", "").replace("sn:", "").strip()
                        logger.info(f"Attempting Dahua General NetSDK Direct Login for SN/Device: {sn}")
                        stream_url = self.source
                        if DAHUA_NETSDK_SERVICE_AVAILABLE and DahuaNetSDKService:
                            netsdk_svc = DahuaNetSDKService.get_instance()
                            if netsdk_svc.connect():
                                logger.info(f"Dahua NetSDK Session established for SN {sn} (Channels: {netsdk_svc.get_total_channels()})")
                                stream_url = netsdk_svc.get_rtsp_url()
                        clean_url = sanitize_rtsp_url(stream_url)
                        logger.info(f"Opening video stream for Dahua device via URL: {clean_url}")
                        c = cv2.VideoCapture(clean_url)
                        if c and c.isOpened():
                            ret, test_frame = c.read()
                            if ret and test_frame is not None:
                                logger.info(f"Dahua CCTV Stream {clean_url} opened successfully.")
                                return c
                            else:
                                c.release()
                    else:
                        clean_url = sanitize_rtsp_url(self.source)
                        logger.info(f"Attempting to open CCTV RTSP stream URL: {clean_url}")
                        c = cv2.VideoCapture(clean_url)
                        if c and c.isOpened():
                            ret, test_frame = c.read()
                            if ret and test_frame is not None:
                                logger.info(f"CCTV Stream URL {clean_url} opened successfully.")
                                return c
                            else:
                                c.release()
                except Exception as e:
                    logger.error(f"Error opening camera source '{self.source}': {e}")
                return None

            # Offload blocking VideoCapture open call to worker thread pool (Zero UI Freeze!)
            self.cap = await loop.run_in_executor(CAMERA_EXECUTOR, open_cam_blocking)
            if not self.cap:
                logger.warning(f"Camera source '{self.source}' could not grab frames. Using tactical simulation feed.")

            await self._capture_loop()

        try:
            loop = asyncio.get_running_loop()
            loop.create_task(_async_init_and_loop())
        except RuntimeError:
            def _run_in_thread():
                asyncio.run(_async_init_and_loop())
            import threading
            threading.Thread(target=_run_in_thread, daemon=True).start()

    def stop(self):
        """Stop streaming camera frames"""
        self.is_running = False
        cap_to_release = self.cap
        self.cap = None
        if cap_to_release is not None:
            def release_cam():
                try:
                    if hasattr(cap_to_release, "release"):
                        cap_to_release.release()
                except Exception:
                    pass
            try:
                loop = asyncio.get_running_loop()
                loop.run_in_executor(CAMERA_EXECUTOR, release_cam)
            except Exception:
                release_cam()
        logger.info("CameraController stopped.")

    def switch_source(self, new_source: str):
        """Switch camera source (e.g. '0' or 'rtsp://...')"""
        self.stop()
        self.source = str(new_source)

    def toggle_recording(self) -> bool:
        self.is_recording = not self.is_recording
        return self.is_recording

    def toggle_hud(self) -> bool:
        self.hud_enabled = not self.hud_enabled
        return self.hud_enabled

    async def _capture_loop(self):
        loop = asyncio.get_running_loop()
        frame_count = 0
        while self.is_running:
            try:
                base64_img = None
                
                cap_ref = self.cap
                if cap_ref and cap_ref.isOpened():
                    def read_and_encode():
                        if not cap_ref or not cap_ref.isOpened():
                            return None
                        ret, frame = cap_ref.read()
                        if ret and frame is not None:
                            # 1. AI Detection Layer (Frame Skipping & Cached Box Rendering for Zero Lag)
                            fall_detected = False
                            human_detected = False
                            if self.ai_detection_enabled:
                                try:
                                    from services.yolo_service import YOLOService
                                    skip_inference = (frame_count % 3 != 0)
                                    frame, fall_detected, self.ai_last_detections = YOLOService.get_instance().detect_and_draw(
                                        frame,
                                        skip_inference=skip_inference,
                                        last_detections=self.ai_last_detections
                                    )
                                    human_detected = len(self.ai_last_detections) > 0
                                except Exception as e:
                                    logger.error(f"Failed to run AI detection: {e}")

                            # 2. HUD Overlay Layer
                            if self.hud_enabled:
                                frame = self._draw_tactical_overlay(frame, frame_count)
                                
                            _, buffer = cv2.imencode('.jpg', frame, [cv2.IMWRITE_JPEG_QUALITY, 70])
                            b64_img = base64.b64encode(buffer).decode('utf-8')
                            
                            # 3. Alert Logic (Triggers when Human or Fall detected and callback is registered)
                            callback = getattr(self, "on_human_detected_callback", None) or self.on_fall_detected_callback
                            if (human_detected or fall_detected) and callback:
                                current_time = time.time()
                                if current_time - self.last_alert_time > self.alert_cooldown_seconds:
                                    self.last_alert_time = current_time
                                    event_type = "FALL DETECTED" if fall_detected else "HUMAN DETECTED"
                                    try:
                                        callback(self.source, b64_img, event_type)
                                    except TypeError:
                                        callback(self.source, b64_img)
                                    
                            return b64_img
                        return None

                    # Offload frame read & JPEG base64 encoding to thread pool
                    base64_img = await loop.run_in_executor(CAMERA_EXECUTOR, read_and_encode)

                    if base64_img is None and self.cap:
                        to_rel = self.cap
                        self.cap = None
                        def release_cam():
                            try:
                                if hasattr(to_rel, "release"):
                                    to_rel.release()
                            except Exception:
                                pass
                        await loop.run_in_executor(CAMERA_EXECUTOR, release_cam)

                if not base64_img:
                    # Generate synthetic tactical live feed if webcam/CCTV URL fails or is unavailable
                    base64_img = self._generate_synthetic_frame(frame_count)

                if self._frame_callback and base64_img and self.is_running:
                    self._frame_callback(base64_img)

                frame_count += 1
                await asyncio.sleep(0.10) # 10 FPS for crisp live surveillance feed
            except Exception as e:
                logger.error(f"Error in camera capture loop: {e}")
                await asyncio.sleep(0.1)

    def _draw_tactical_overlay(self, frame, frame_count: int):
        """Draw tactical HUD overlay onto OpenCV frame"""
        try:
            h, w, _ = frame.shape
            
            # Target Reticle Box (Center)
            cx, cy = w // 2, h // 2
            box_size = 120 + int(np.sin(frame_count * 0.1) * 10)
            x1, y1 = cx - box_size // 2, cy - box_size // 2
            x2, y2 = cx + box_size // 2, cy + box_size // 2
            
            # Draw Bounding Box (Cyan/Blue)
            cv2.rectangle(frame, (x1, y1), (x2, y2), (255, 180, 0), 2)
            cv2.putText(frame, "TARGET: OPERATOR-741", (x1, y1 - 8), cv2.FONT_HERSHEY_SIMPLEX, 0.45, (255, 180, 0), 1)
            
            # Draw Corner Crosshairs
            cv2.circle(frame, (cx, cy), 8, (255, 180, 0), 1)
            cv2.line(frame, (cx - 15, cy), (cx + 15, cy), (255, 180, 0), 1)
            cv2.line(frame, (cx, cy - 15), (cx, cy + 15), (255, 180, 0), 1)

            # Draw Threat Alert Box (Top Left)
            cv2.rectangle(frame, (20, 20), (320, 70), (0, 0, 180), -1)
            cv2.putText(frame, "THREAT LEVEL: HIGH", (30, 42), cv2.FONT_HERSHEY_SIMPLEX, 0.55, (255, 255, 255), 2)
            cv2.putText(frame, "SUSPECT_ID: UNKNOWN_042", (30, 62), cv2.FONT_HERSHEY_SIMPLEX, 0.45, (255, 255, 255), 1)

            # Draw Status Details (Top Right)
            cv2.putText(frame, "SYSTEM STATUS: OPERATIONAL", (w - 240, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.4, (0, 255, 0), 1)
            cv2.putText(frame, "FPS: 60.0 | BITRATE: 4.2 Mbps", (w - 240, 45), cv2.FONT_HERSHEY_SIMPLEX, 0.35, (200, 200, 200), 1)
            cv2.putText(frame, "ALERT: SUBJECT DETECTED", (w - 240, 60), cv2.FONT_HERSHEY_SIMPLEX, 0.35, (0, 0, 255), 1)

            # Bottom Timestamp
            ts_str = time.strftime("%Y-%m-%d %H:%M:%S UTC")
            cv2.putText(frame, ts_str, (w - 260, h - 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 1)
        except Exception as e:
            logger.error(f"Error drawing tactical overlay: {e}")

        return frame

    def _generate_synthetic_frame(self, frame_count: int) -> str:
        """Generate synthetic tactical CCTV feed if no webcam hardware is available"""
        w, h = 640, 360
        if OPENCV_AVAILABLE:
            frame = np.zeros((h, w, 3), dtype=np.uint8)
            # Dark industrial CCTV grid simulation
            cv2.rectangle(frame, (0, 0), (w, h), (30, 35, 40), -1)
            cv2.line(frame, (50, 0), (50, h), (40, 45, 50), 1)
            cv2.line(frame, (w - 50, 0), (w - 50, h), (40, 45, 50), 1)
            cv2.line(frame, (0, h // 2), (w, h // 2), (40, 45, 50), 1)
            
            # Simulating live corridor / perimeter background lines
            cv2.line(frame, (100, 50), (200, 280), (70, 75, 80), 2)
            cv2.line(frame, (w - 100, 50), (w - 200, 280), (70, 75, 80), 2)
            
            frame = self._draw_tactical_overlay(frame, frame_count)
            _, buffer = cv2.imencode('.jpg', frame, [cv2.IMWRITE_JPEG_QUALITY, 70])
            return base64.b64encode(buffer).decode('utf-8')
        else:
            # Fallback simple PIL image if numpy/cv2 missing
            img = Image.new('RGB', (w, h), color=(30, 35, 40))
            draw = ImageDraw.Draw(img)
            draw.text((20, 20), "TACTICAL LIVE FEED SIMULATION", fill=(255, 255, 255))
            draw.text((20, 50), f"TIMESTAMP: {time.strftime('%Y-%m-%d %H:%M:%S UTC')}", fill=(0, 255, 0))
            buf = io.BytesIO()
            img.save(buf, format='JPEG')
            return base64.b64encode(buf.getvalue()).decode('utf-8')
