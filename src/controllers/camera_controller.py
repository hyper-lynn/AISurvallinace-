import sys
import os
import base64
import asyncio
import time
import io
import urllib.parse
from typing import Optional, Callable

def sanitize_rtsp_url(url: str) -> str:
    """
    Sanitize and validate RTSP URLs for OpenCV/FFmpeg VideoCapture.
    Supports Dahua & IMOU cameras with Safety Code credentials.
    Automatically URL-encodes special characters in passwords to prevent RTSP 401 Unauthorized errors.
    """
    if not isinstance(url, str) or not url.strip():
        return url
    url = url.strip()
    if not (url.startswith("rtsp://") or url.startswith("rtsps://")):
        url = "rtsp://" + url
    
    try:
        proto, rest = url.split("://", 1)
        if "@" in rest:
            user_pass, host_path = rest.rsplit("@", 1)
            if ":" in user_pass:
                user, pwd = user_pass.split(":", 1)
                # Unquote first in case it was partially quoted, then quote safely
                unquoted_pwd = urllib.parse.unquote(pwd)
                encoded_pwd = urllib.parse.quote(unquoted_pwd, safe="")
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

# Configure OpenCV FFmpeg RTSP stream options for zero latency & instant connection
os.environ["OPENCV_FFMPEG_CAPTURE_OPTIONS"] = "rtsp_transport;tcp|stimeout;2000000|probesize;32|analyzeduration;0|fflags;nobuffer|flags;low_delay|max_delay;0|buffer_size;102400"
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

_cpu_count = os.cpu_count() or 4
CAMERA_EXECUTOR = concurrent.futures.ThreadPoolExecutor(
    max_workers=min(8, _cpu_count * 2),
    thread_name_prefix="CamWorker"
)


class CameraController:
    """
    PC Webcam & Tactical Camera Controller for Live Monitoring View.
    Handles OpenCV VideoCapture(source), RTSP wireless/wired CCTV streams,
    frame conversion to base64, camera switching, and synthetic tactical HUD stream fallback.
    Uses ThreadPoolExecutor to prevent any GIL or asyncio thread UI freeze.
    """
    _active_instances: dict = {}

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
        self.face_detection_enabled = False
        self.crowd_mode_enabled = False
        self.last_alert_time = 0
        self.alert_cooldown_seconds = 30
        self.ai_last_detections = []
        self._last_raw_frame = None
        self._frame_callback: Optional[Callable[[str], None]] = None
        self.on_fall_detected_callback: Optional[Callable[[str, str], None]] = None
        self.__class__._active_instances[self.source] = self

    @classmethod
    def stop_all_except(cls, keep_source: Optional[str] = None):
        """Stop and release all active camera instances except the specified keep_source."""
        keep_str = str(keep_source).strip() if keep_source is not None else None
        for src, ctrl in list(cls._active_instances.items()):
            if keep_str is None or str(src).strip() != keep_str:
                try:
                    if ctrl and ctrl.is_running:
                        logger.info(f"Auto-stopping background camera instance for source '{src}'")
                        ctrl.stop()
                except Exception:
                    pass

    @classmethod
    def stop_all_webcams_except(cls, keep_source: Optional[str] = None):
        """Stop all active webcam instances except keep_source to release hardware webcam lock & turn off webcam light."""
        keep_str = str(keep_source).strip() if keep_source is not None else None
        for src, ctrl in list(cls._active_instances.items()):
            if (keep_str is None or str(src).strip() != keep_str) and (str(src).strip().isdigit() or "webcam" in str(src).lower()):
                try:
                    if ctrl and ctrl.is_running:
                        logger.info(f"Auto-closing hardware webcam '{src}' to release hardware lock")
                        ctrl.stop()
                except Exception:
                    pass

    @classmethod
    def capture_snapshot(cls, source: str = "0") -> Optional[str]:
        """
        Capture a live frame/snapshot from camera source (webcam/CCTV)
        and save it as a local JPEG image in assets/cache/.
        If the camera stream is currently active in memory, captures in 0ms directly!
        Returns absolute filepath of saved image or None if failed.
        """
        try:
            cache_dir = os.path.abspath(os.path.normpath(os.path.join(SRC_DIR, "..", "assets", "cache")))
            os.makedirs(cache_dir, exist_ok=True)
            snapshot_path = os.path.abspath(os.path.normpath(os.path.join(cache_dir, f"snapshot_{int(time.time())}.jpg")))

            src_str = str(source).strip()

            # 1. Check if camera is currently running live in active memory
            active_ctl = cls._active_instances.get(src_str)
            if active_ctl and active_ctl._last_raw_frame is not None:
                frame = active_ctl._last_raw_frame
                if OPENCV_AVAILABLE and cv2 is not None:
                    cv2.imwrite(snapshot_path, frame)
                    logger.info(f"Captured live active camera '{src_str}' snapshot from memory: {snapshot_path}")
                    return snapshot_path

            # 2. Open target camera source directly
            ctl = cls(source=src_str)
            cap = ctl.open_cam_blocking()
            if cap and cap.isOpened():
                for _ in range(3):
                    cap.grab()
                ret, frame = cap.read()
                cap.release()
                if ret and frame is not None:
                    if OPENCV_AVAILABLE and cv2 is not None:
                        cv2.imwrite(snapshot_path, frame)
                        logger.info(f"Captured live camera snapshot for '{src_str}' to: {snapshot_path}")
                        return snapshot_path

            # Fallback synthetic frame if offline/unreadable
            b64_synth = ctl._generate_synthetic_frame(frame_count=0)
            img_data = base64.b64decode(b64_synth)
            with open(snapshot_path, "wb") as f:
                f.write(img_data)
            logger.info(f"Captured synthetic camera snapshot fallback for '{src_str}' to: {snapshot_path}")
            return snapshot_path
        except Exception as e:
            logger.error(f"Error capturing camera snapshot for '{source}': {e}")
            return None


    def start(self, frame_callback: Callable[[str], None]):
        """Start streaming camera frames asynchronously without blocking UI thread"""
        self.subscribe_frames(frame_callback)

    def subscribe_frames(self, frame_callback: Callable[[str], None]):
        """Subscribe frame callback listener and start camera feed."""
        if self.is_running and self._frame_callback == frame_callback and self.cap is not None:
            return

        self._frame_callback = frame_callback
        self.is_running = True
        
    def open_cam_blocking(self):
        """Open VideoCapture device/stream synchronously and return VideoCapture object."""
        if not OPENCV_AVAILABLE:
            return None
        try:
            if self.source.isdigit():
                # Auto-release and turn off any other active webcams to prevent hardware locks & turn off webcam light
                self.stop_all_webcams_except(self.source)
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

                return None

            elif self.source.startswith("p2p://") or self.source.upper().startswith("SN:"):
                sn_raw = self.source.replace("p2p://", "").replace("SN:", "").replace("sn:", "").strip()
                sn = sn_raw
                user = os.getenv("DAHUA_P2P_USER") or os.getenv("DAHUA_USER", "admin")
                pwd = os.getenv("DAHUA_P2P_PASS") or os.getenv("DAHUA_PASS", "12345asd@")
                
                if "@" in sn_raw:
                    cred, sn = sn_raw.split("@", 1)
                    if ":" in cred:
                        user, pwd = cred.split(":", 1)
                    else:
                        pwd = cred

                logger.info(f"Attempting Dahua/IMOU Direct Connection for SN: {sn} (User: {user})")
                stream_urls_to_try = []

                if DAHUA_NETSDK_SERVICE_AVAILABLE and DahuaNetSDKService:
                    netsdk_svc = DahuaNetSDKService.get_instance()
                    if netsdk_svc.connect(user=user, password=pwd):
                        logger.info(f"NetSDK Session established for SN {sn}")
                        stream_urls_to_try.append(netsdk_svc.get_rtsp_url())

                # Fallback candidate RTSP URL for SN device (only if DAHUA_IP is configured in .env)
                env_ip = os.getenv("DAHUA_IP", "").strip()
                if env_ip:
                    import urllib.parse
                    encoded_pass = urllib.parse.quote(pwd, safe="")
                    stream_urls_to_try.append(f"rtsp://{user}:{encoded_pass}@{env_ip}:554/cam/realmonitor?channel=1&subtype=0")
                    stream_urls_to_try.append(f"rtsp://{user}:{encoded_pass}@{env_ip}:554/cam/realmonitor?channel=1&subtype=1")

                for url_candidate in stream_urls_to_try:
                    if not url_candidate:
                        continue
                    clean_url = sanitize_rtsp_url(url_candidate)
                    logger.info(f"Opening video stream for SN device via URL: {clean_url}")
                    c = cv2.VideoCapture(clean_url)
                    if c and c.isOpened():
                        c.set(cv2.CAP_PROP_BUFFERSIZE, 1)
                        ret, test_frame = c.read()
                        if ret and test_frame is not None:
                            logger.info(f"CCTV Stream {clean_url} opened successfully.")
                            return c
                        else:
                            c.release()
            else:
                urls_to_try = [sanitize_rtsp_url(self.source)]
                if "subtype=0" in self.source:
                    urls_to_try.append(sanitize_rtsp_url(self.source.replace("subtype=0", "subtype=1")))
                elif "/cam/realmonitor" in self.source and "subtype=" not in self.source:
                    urls_to_try.append(sanitize_rtsp_url(self.source + "&subtype=1" if "?" in self.source else self.source + "?subtype=1"))

                for clean_url in urls_to_try:
                    logger.info(f"Attempting to open CCTV RTSP stream URL: {clean_url}")
                    c = cv2.VideoCapture(clean_url)
                    if c and c.isOpened():
                        c.set(cv2.CAP_PROP_BUFFERSIZE, 1)
                        ret, test_frame = c.read()
                        if ret and test_frame is not None:
                            logger.info(f"CCTV Stream URL {clean_url} opened successfully.")
                            return c
                        else:
                            c.release()

        except Exception as e:
            logger.error(f"Error opening camera source '{self.source}': {e}")
        return None

    def start(self, frame_callback: Callable[[str], None]):
        """Subscribe frame callback listener and start camera feed."""
        if self.is_running and self._frame_callback == frame_callback and self.cap is not None:
            return

        self._frame_callback = frame_callback
        self.is_running = True
        
        async def _async_init_and_loop():
            loop = asyncio.get_running_loop()
            # Offload blocking VideoCapture open call to worker thread pool (Zero UI Freeze!)
            self.cap = await loop.run_in_executor(CAMERA_EXECUTOR, self.open_cam_blocking)
            if not self.cap:
                logger.warning(f"Camera source '{self.source}' could not grab frames. Using tactical simulation feed.")

            await self._capture_loop()  # Single capture loop — do NOT call twice

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
                frame_start = time.monotonic()  # Track frame start for adaptive sleep
                base64_img = None
                
                cap_ref = self.cap
                if cap_ref and cap_ref.isOpened():
                    def read_and_encode():
                        if not cap_ref or not cap_ref.isOpened():
                            return None
                        try:
                            # Drain up to 2 stale frames from the FFmpeg buffer (balance latency vs CPU cost)
                            for _ in range(2):
                                if not cap_ref.grab():
                                    break
                            ret, frame =    cap_ref.retrieve()
                            if not ret or frame is None:
                                ret, frame = cap_ref.read()
                        except Exception as grab_err:
                            logger.debug(f"Frame grab exception safely caught: {grab_err}")
                            return None
                        if ret and frame is not None:
                            self._last_raw_frame = frame.copy()
                            # Downscale 2K / 4K high-res streams (2560x1440 / 3840x2160) to max width 1080 for ultra-fast 60 FPS UI rendering
                            h, w = frame.shape[:2]
                            if w > 1080:
                                new_w = 1080
                                new_h = int(h * (1080.0 / w))
                                frame = cv2.resize(frame, (new_w, new_h), interpolation=cv2.INTER_NEAREST)

                            # 1. AI Detection Layer (Frame Skipping & Cached Box Rendering for Zero Lag)
                            fall_detected = False
                            human_detected = False
                            if self.ai_detection_enabled or self.face_detection_enabled:
                                try:
                                    from services.yolo_service import YOLOService
                                    skip_inference = (frame_count % 3 != 0)
                                    frame, fall_detected, self.ai_last_detections = YOLOService.get_instance().detect_and_draw(
                                        frame,
                                        skip_inference=skip_inference,
                                        last_detections=self.ai_last_detections,
                                        face_detection_enabled=self.face_detection_enabled,
                                        crowd_mode_enabled=self.crowd_mode_enabled
                                    )
                                    human_detected = len(self.ai_last_detections) > 0
                                except Exception as e:
                                    logger.error(f"Failed to run AI detection: {e}")

                            # 2. HUD Overlay Layer
                            if self.hud_enabled:
                                frame = self._draw_tactical_overlay(frame, frame_count)
                                
                            _, buffer = cv2.imencode('.jpg', frame, [cv2.IMWRITE_JPEG_QUALITY, 55])
                            b64_img = base64.b64encode(buffer).decode('utf-8')

                            
                            # 3. Alert Logic: Prepare alert payload for main thread dispatch
                            alert_payload = None
                            callback = getattr(self, "on_human_detected_callback", None) or self.on_fall_detected_callback
                            if (human_detected or fall_detected) and callback:
                                current_time = time.time()
                                if current_time - self.last_alert_time > self.alert_cooldown_seconds:
                                    self.last_alert_time = current_time
                                    matched_person = next((d.get("matched_name") for d in self.ai_last_detections if d.get("matched_name")), None)
                                    face_only_detections = all(d.get("is_face", False) for d in self.ai_last_detections) if self.ai_last_detections else False

                                    if fall_detected:
                                        event_type = "FALL DETECTED"
                                    elif face_only_detections and matched_person:
                                        # OpenCV face detection matched a known target
                                        event_type = f"FACE DETECTED: {matched_person.upper()}"
                                    elif face_only_detections:
                                        # OpenCV face detection (unknown face)
                                        event_type = "FACE DETECTED"
                                    elif matched_person:
                                        # YOLO human detection with matched target face
                                        event_type = f"TARGET FACE DETECTED ({matched_person.upper()})"
                                    else:
                                        event_type = "HUMAN DETECTED"

                                    alert_payload = (event_type, matched_person)


                            return b64_img, alert_payload
                        return None, None

                    # Offload frame read & JPEG base64 encoding to thread pool
                    res = await loop.run_in_executor(CAMERA_EXECUTOR, read_and_encode)
                    if isinstance(res, tuple):
                        base64_img, alert_payload = res
                    else:
                        base64_img, alert_payload = res, None

                    # Safely dispatch alert callback on the main asyncio thread to allow Flet UI state updates
                    if alert_payload and base64_img:
                        event_type, matched_person = alert_payload
                        callback = getattr(self, "on_human_detected_callback", None) or self.on_fall_detected_callback
                        if callback:
                            try:
                                callback(self.source, base64_img, event_type, matched_person)
                            except TypeError:
                                try:
                                    callback(self.source, base64_img, event_type)
                                except TypeError:
                                    callback(self.source, base64_img)


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
                    # If camera/network disconnected, attempt background reconnection every ~3 seconds (30 frames)
                    if frame_count % 30 == 0:
                        def try_reconnect():
                            try:
                                return self.open_cam_blocking()
                            except Exception:
                                return None
                        new_cap = await loop.run_in_executor(CAMERA_EXECUTOR, try_reconnect)
                        if new_cap:
                            self.cap = new_cap
                            logger.info(f"Successfully re-established live stream connection for '{self.source}'!")

                    # Generate synthetic tactical live loading feed
                    base64_img = self._generate_synthetic_frame(frame_count)

                if self._frame_callback and base64_img and self.is_running:
                    self._frame_callback(base64_img)

                frame_count += 1
                # Adaptive sleep: maintain ~10 FPS target regardless of AI inference overhead
                elapsed = time.monotonic() - frame_start
                target_interval = 0.10  # 10 FPS
                remaining = target_interval - elapsed
                if remaining > 0.005:
                    await asyncio.sleep(remaining)
                else:
                    await asyncio.sleep(0.005)  # Always yield to event loop
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
        """Generate animated Loading & Reconnecting HUD frame during network drops"""
        w, h = 640, 360
        if OPENCV_AVAILABLE:
            frame = np.zeros((h, w, 3), dtype=np.uint8)
            # Dark futuristic CCTV grid background
            cv2.rectangle(frame, (0, 0), (w, h), (20, 24, 28), -1)
            
            # Grid pattern
            for x in range(0, w, 40):
                cv2.line(frame, (x, 0), (x, h), (30, 36, 42), 1)
            for y in range(0, h, 40):
                cv2.line(frame, (0, y), (w, y), (30, 36, 42), 1)

            # Animated loading spinner ring (Center)
            cx, cy = w // 2, h // 2
            angle = (frame_count * 15) % 360
            radius = 35
            end_x = int(cx + radius * np.cos(np.radians(angle)))
            end_y = int(cy + radius * np.sin(np.radians(angle)))
            cv2.circle(frame, (cx, cy), radius, (60, 70, 80), 2)
            cv2.circle(frame, (end_x, end_y), 6, (0, 220, 255), -1)
            cv2.line(frame, (cx, cy), (end_x, end_y), (0, 220, 255), 2)

            # Animated Loading Dots
            dots = "." * ((frame_count // 3) % 4)
            status_str = f"CONNECTING / RECONNECTING{dots}"
            
            # Warning Banner (Top & Center)
            cv2.rectangle(frame, (cx - 190, cy - 70), (cx + 190, cy - 45), (0, 100, 200), -1)
            cv2.putText(frame, "NETWORK INTERRUPTED - AUTO RETRY", (cx - 180, cy - 53), cv2.FONT_HERSHEY_SIMPLEX, 0.45, (255, 255, 255), 1)
            
            cv2.putText(frame, status_str, (cx - 110, cy + 60), cv2.FONT_HERSHEY_SIMPLEX, 0.55, (0, 220, 255), 2)
            cv2.putText(frame, "RE-ESTABLISHING RTSP STREAM...", (cx - 135, cy + 85), cv2.FONT_HERSHEY_SIMPLEX, 0.4, (180, 190, 200), 1)

            # Bottom Timestamp
            ts_str = time.strftime("%Y-%m-%d %H:%M:%S UTC")
            cv2.putText(frame, ts_str, (w - 240, h - 15), cv2.FONT_HERSHEY_SIMPLEX, 0.4, (150, 160, 170), 1)

            _, buffer = cv2.imencode('.jpg', frame, [cv2.IMWRITE_JPEG_QUALITY, 70])
            return base64.b64encode(buffer).decode('utf-8')
        else:
            img = Image.new('RGB', (w, h), color=(20, 24, 28))
            draw = ImageDraw.Draw(img)
            draw.text((20, 20), "RECONNECTING RTSP STREAM...", fill=(0, 220, 255))
            buf = io.BytesIO()
            img.save(buf, format='JPEG')
            return base64.b64encode(buf.getvalue()).decode('utf-8')
