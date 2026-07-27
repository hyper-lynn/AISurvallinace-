import sys
import os
import base64
import asyncio
import time
import io
from typing import Optional, Callable

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

# Configure OpenCV FFmpeg RTSP stream options (TCP transport & 3-second stimeout)
os.environ["OPENCV_FFMPEG_CAPTURE_OPTIONS"] = "rtsp_transport;tcp|stimeout;3000000"

try:
    from config import logger
except Exception:
    import logging
    logger = logging.getLogger("CameraController")

try:
    import cv2
    import numpy as np
    from PIL import Image, ImageDraw, ImageFont
    OPENCV_AVAILABLE = True
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
        self._frame_callback: Optional[Callable[[str], None]] = None

    def start(self, frame_callback: Callable[[str], None]):
        """Start streaming camera frames asynchronously without blocking UI thread"""
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
                        for b in backends:
                            try:
                                c = cv2.VideoCapture(dev_id, b)
                                if c and c.isOpened():
                                    ret, test_frame = c.read()
                                    if ret and test_frame is not None:
                                        logger.info(f"PC Webcam device index {dev_id} verified working with backend {b}.")
                                        return c
                                    else:
                                        c.release()
                            except Exception:
                                pass
                    else:
                        logger.info(f"Attempting to open CCTV RTSP stream URL: {self.source}")
                        c = cv2.VideoCapture(self.source)
                        if c and c.isOpened():
                            ret, test_frame = c.read()
                            if ret and test_frame is not None:
                                logger.info(f"CCTV Stream URL {self.source} opened successfully.")
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

        asyncio.create_task(_async_init_and_loop())

    def stop(self):
        """Stop streaming camera frames"""
        self.is_running = False
        if self.cap:
            def release_cam():
                try:
                    self.cap.release()
                except Exception:
                    pass
            try:
                loop = asyncio.get_running_loop()
                loop.run_in_executor(CAMERA_EXECUTOR, release_cam)
            except Exception:
                release_cam()
            self.cap = None
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
                
                if self.cap and self.cap.isOpened():
                    def read_and_encode():
                        if not self.cap or not self.cap.isOpened():
                            return None
                        ret, frame = self.cap.read()
                        if ret and frame is not None:
                            if self.hud_enabled:
                                frame = self._draw_tactical_overlay(frame, frame_count)
                            _, buffer = cv2.imencode('.jpg', frame, [cv2.IMWRITE_JPEG_QUALITY, 70])
                            return base64.b64encode(buffer).decode('utf-8')
                        return None

                    # Offload frame read & JPEG base64 encoding to thread pool
                    base64_img = await loop.run_in_executor(CAMERA_EXECUTOR, read_and_encode)

                    if base64_img is None and self.cap:
                        def release_cam():
                            try: self.cap.release()
                            except Exception: pass
                        await loop.run_in_executor(CAMERA_EXECUTOR, release_cam)
                        self.cap = None

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
