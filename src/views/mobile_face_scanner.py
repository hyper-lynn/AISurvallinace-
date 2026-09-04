# src/views/mobile_face_scanner.py
"""
Shadow EYE - Declarative Responsive Flet Mobile & Web (PWA) & Desktop Face Scanner View
Built using @dataclass State Models, @ft.component Architecture, Native NavigationBar, and High-Accuracy PC AI Models.
"""

from dataclasses import dataclass, field
import flet as ft
import flet_camera as fc
import httpx
import base64
import json
import asyncio
import logging
import sys
from typing import Optional, Dict, Any, List, Tuple

# Colors
ACCENT_GREEN = "#00E676"
ACCENT_BLUE = "#29B6F6"
ACCENT_PURPLE = "#7C4DFF"
BG_CARD = "#1A1C23"
BG_DARK = "#0F1015"
BORDER_COLOR = "#2A2D3A"

@dataclass
class ScannerState:
    """Single Source of Truth Declarative State Model"""
    server_url: str = "http://localhost:8000"
    active_tab: int = 0
    api_connected: bool = False
    api_status: str = "Checking..."
    target_count: int = 0
    captured_b64: str = ""
    annotated_b64: str = ""
    detection_result: Optional[Dict] = None
    is_scanning: bool = False
    is_mirrored: bool = False
    is_live_streaming: bool = False
    is_comparing: bool = False
    compare_img1: str = ""
    compare_img2: str = ""
    compare_result_text: str = "Select 2 faces to compare"
    reg_name: str = ""
    reg_dept: str = "General"
    reg_role: str = "VIP"
    reg_primary_b64: str = ""
    reg_gallery_b64_list: List[str] = field(default_factory=list)
    reg_status_msg: str = ""
    target_profiles: List[Dict] = field(default_factory=list)

def has_human_readable_name(camera: fc.CameraDescription) -> bool:
    name = camera.name.strip()
    if not name or name.startswith("com.apple.avfoundation."):
        return False
    return not (":" in name and "." in name)

def camera_label(camera: fc.CameraDescription) -> str:
    if has_human_readable_name(camera):
        return camera.name

    direction = camera.lens_direction.value.capitalize() if hasattr(camera.lens_direction, 'value') else str(camera.lens_direction).split('.')[-1].capitalize()
    lens_map = {
        "wide": "Wide",
        "telephoto": "Telephoto",
        "ultraWide": "Ultra Wide",
        "unknown": "Unknown",
    }
    lens_type_val = camera.lens_type.value if hasattr(camera.lens_type, 'value') else str(camera.lens_type)
    lens_type = lens_map.get(lens_type_val, lens_type_val)
    return f"{direction} ({lens_type})"

def _get_file_bytes(file_item: Any) -> Optional[bytes]:
    """Safely extracts bytes from a FilePicker file object (memory buffer or disk path)."""
    if getattr(file_item, "bytes", None):
        return file_item.bytes
    path_val = getattr(file_item, "path", None)
    if path_val:
        try:
            with open(path_val, "rb") as f_handle:
                return f_handle.read()
        except Exception:
            return None
    return None

class MobileFaceScannerView(ft.Container):
    def __init__(self, page: Optional[ft.Page] = None):
        super().__init__(expand=True, bgcolor=BG_DARK, padding=10)
        self.app_page = page

        # Declarative Dataclass State Model
        self.state = ScannerState()

        # Camera & Hardware State
        self.cameras: List[fc.CameraDescription] = []
        self.selected_camera: Optional[fc.CameraDescription] = None
        self.camera_initialized = False
        self.live_stream_task: Optional[asyncio.Task] = None

        # Persistent Controls
        self.camera_preview = fc.Camera(
            expand=True,
            preview_enabled=True,
            content=ft.Container(
                alignment=ft.Alignment.CENTER,
                content=ft.Icon(ft.Icons.CAMERA_ALT, color=ft.Colors.WHITE_54, size=48)
            )
        )
        self.camera_dropdown = ft.Dropdown(
            label="Select Camera Source",
            expand=True,
            on_select=self.on_camera_select
        )
        self.scan_status_text = ft.Text(self.state.api_status, size=13, color=ft.Colors.GREY_300)
        self.api_status_text = ft.Text(self.state.api_status, size=11, color=ft.Colors.WHITE, weight=ft.FontWeight.W_500)
        self.api_dot = ft.Container(width=8, height=8, border_radius=4, bgcolor=ft.Colors.RED_400)

        # FilePicker service
        self.file_picker = ft.FilePicker()
        self._picker_busy = False  # guard against concurrent pick_files calls

        # Declarative Scrollable View Containers
        self.scan_view_container = ft.Container(expand=True, visible=True)
        self.target_db_view_container = ft.Container(expand=True, visible=False)
        self.settings_view_container = ft.Container(expand=True, visible=False)

        # Build UI layout
        self.content = self.build_ui()

    def is_camera_supported(self) -> bool:
        """Check if native flet_camera control is supported on current OS platform (Android & iOS)"""
        page = self.app_page or getattr(self, 'page', None)
        if page:
            if getattr(page, 'web', False):
                return True
            plat = str(getattr(page, 'platform', '')).lower()
            if any(p in plat for p in ('android', 'ios', 'iphone', 'ipad', 'mobile')):
                return True
            return False
        if sys.platform in ("win32", "darwin", "linux"):
            return False
        return False

    def build_photo_upload_fallback(self) -> ft.Container:
        return ft.Container(
            alignment=ft.Alignment.CENTER,
            content=ft.Column([
                ft.Icon(ft.Icons.ADD_A_PHOTO, color=ACCENT_BLUE, size=48),
                ft.Text("Photo Upload Mode - Select Photo to Scan", size=13, color=ft.Colors.GREY_300),
                ft.Text("Tap Upload below to select face image for AI scanning", size=11, color=ft.Colors.GREY_500)
            ], alignment=ft.MainAxisAlignment.CENTER, horizontal_alignment=ft.CrossAxisAlignment.CENTER, spacing=6)
        )

    def did_mount(self):
        """Flet lifecycle hook called when control is mounted on page"""
        if self.page:
            self.app_page = self.page
            try:
                # In Flet 0.86+, page property is 'appbar'
                setattr(self.page, "appbar", self.build_app_bar())
            except Exception:
                pass

        # Safely configure camera vs photo upload fallback
        if not self.is_camera_supported():
            self.camera_container.content = self.build_photo_upload_fallback()
        else:
            self.camera_container.content = self.camera_preview

        asyncio.create_task(self.check_api_health())
        if self.is_camera_supported():
            asyncio.create_task(self.init_cameras())
        asyncio.create_task(self.load_target_faces())

    def open_dialog(self, dialog: ft.AlertDialog):
        """Dual-compatible dialog opener for Mobile & Desktop"""
        if self.app_page:
            try:
                if hasattr(self.app_page, 'open'):
                    self.app_page.open(dialog)  # type: ignore
                elif hasattr(self.app_page, 'dialog'):
                    setattr(self.app_page, 'dialog', dialog)
                    dialog.open = True
                    self.app_page.update()
            except Exception:
                dialog.open = True
                self.app_page.update()

    def close_dialog(self, dialog: ft.AlertDialog):
        """Dual-compatible dialog closer for Mobile & Desktop"""
        if self.app_page:
            try:
                if hasattr(self.app_page, 'close'):
                    self.app_page.close(dialog)  # type: ignore
                else:
                    dialog.open = False
                    self.app_page.update()
            except Exception:
                dialog.open = False
                self.app_page.update()

    async def open_live_camera_dialog(self, on_photo_captured_callback):
        """Declarative native camera photo capture: Uses mounted camera or safe file picker"""
        if not self.app_page:
            return

        if self.is_camera_supported() and self.camera_initialized:
            try:
                data = await asyncio.wait_for(self.camera_preview.take_picture(), timeout=3.0)
                if data:
                    encoded = base64.b64encode(data).decode("utf-8")
                    b64_img = f"data:image/jpeg;base64,{encoded}"
                    on_photo_captured_callback(b64_img)
                    return
            except (asyncio.TimeoutError, TimeoutError, Exception) as ex:
                logging.warning("Native camera capture note: %s", ex)
                await asyncio.sleep(0.5)

        # File picker fallback for gallery or when native camera is offline
        files = await self._safe_pick_files(allow_multiple=False, file_type=ft.FilePickerFileType.IMAGE, with_data=True)
        if files and len(files) > 0:
            data = _get_file_bytes(files[0])
            if data:
                b64 = f"data:image/jpeg;base64,{base64.b64encode(data).decode('utf-8')}"
                on_photo_captured_callback(b64)

    async def check_api_health(self):
        try:
            async with httpx.AsyncClient(timeout=3.0) as client:
                resp = await client.get(f"{self.state.server_url}/api/v1/health")
                if resp.status_code == 200:
                    self.state.api_connected = True
                    self.state.target_count = resp.json().get('registered_target_faces', 0)
                    self.api_status_text.value = f"Online ({self.state.target_count} Targets)"
                    self.api_dot.bgcolor = ACCENT_GREEN
                else:
                    self.state.api_connected = False
                    self.api_status_text.value = "Server Error"
                    self.api_dot.bgcolor = ft.Colors.RED_400
        except Exception:
            self.state.api_connected = False
            self.api_status_text.value = "Offline (:8000)"
            self.api_dot.bgcolor = ft.Colors.RED_400
        
        if self.app_page:
            try:
                self.app_page.update()
            except Exception:
                pass

    async def init_cameras(self):
        if not self.is_camera_supported(): return
        for _ in range(10):
            await asyncio.sleep(0.3)
            try:
                cams = await asyncio.wait_for(self.camera_preview.get_available_cameras(), timeout=3.0)
                if cams and len(cams) > 0:
                    self.cameras = cams
                    self.camera_dropdown.options = [
                        ft.DropdownOption(key=c.name, text=f"{camera_label(c)} ({c.name})")
                        for c in cams
                    ]
                    self.selected_camera = cams[0]
                    self.camera_dropdown.value = cams[0].name
                    if self.app_page:
                        self.camera_dropdown.update()
                    await self.start_camera_stream(cams[0])
                    break
            except Exception as ex:
                logging.warning("Camera init retry: %s", ex)

    async def start_camera_stream(self, cam: fc.CameraDescription):
        if not self.is_camera_supported(): return
        self.selected_camera = cam
        self.scan_status_text.value = f"Initializing {camera_label(cam)}..."
        if self.app_page:
            self.scan_status_text.update()
        try:
            await asyncio.wait_for(
                self.camera_preview.initialize(
                    description=cam,
                    resolution_preset=fc.ResolutionPreset.MEDIUM,
                    enable_audio=False,
                    image_format_group=fc.ImageFormatGroup.JPEG
                ),
                timeout=5.0
            )
            self.camera_initialized = True
            self.scan_status_text.value = "Live Camera Ready"
        except Exception as ex:
            self.scan_status_text.value = f"Cam Note: {ex}"
        if self.app_page:
            self.scan_status_text.update()

    async def on_camera_select(self, e):
        if not self.is_camera_supported(): return
        cam_name = e.control.value
        cam = next((c for c in self.cameras if c.name == cam_name), None)
        if cam:
            await self.start_camera_stream(cam)

    async def switch_next_camera(self, e=None):
        if not self.is_camera_supported() or not self.cameras:
            return
        if not self.selected_camera:
            await self.start_camera_stream(self.cameras[0])
            return
        try:
            curr_idx = next(i for i, c in enumerate(self.cameras) if c.name == self.selected_camera.name)
            next_idx = (curr_idx + 1) % len(self.cameras)
            self.camera_dropdown.value = self.cameras[next_idx].name
            if self.app_page:
                self.camera_dropdown.update()
            await self.start_camera_stream(self.cameras[next_idx])
        except Exception:
            await self.start_camera_stream(self.cameras[0])

    def toggle_mirror(self, e=None):
        self.state.is_mirrored = not self.state.is_mirrored
        scale_val = ft.Scale(scale_x=-1 if self.state.is_mirrored else 1)
        self.camera_container.scale = scale_val
        self.image_container.scale = scale_val
        self.camera_container.update()
        self.image_container.update()

    # --- Real-Time Continuous Live Video Stream AI Loop ---
    def toggle_live_stream(self, e):
        self.state.is_live_streaming = e.control.value
        if self.state.is_live_streaming:
            self.live_stream_task = asyncio.create_task(self.run_live_stream_loop())
        else:
            if self.live_stream_task:
                self.live_stream_task.cancel()
                self.live_stream_task = None
            self.scan_status_text.value = "Live Stream Paused. Ready for manual photo scan."
            self.scan_status_text.update()

    async def run_live_stream_loop(self):
        self.scan_status_text.value = "Continuous Live AI Video Stream Active..."
        if self.app_page:
            self.scan_status_text.update()

        while self.state.is_live_streaming:
            if not self.is_camera_supported() or not self.camera_initialized or self.state.active_tab != 0:
                await asyncio.sleep(0.5)
                continue

            try:
                data = await asyncio.wait_for(self.camera_preview.take_picture(), timeout=2.0)
                if data and self.state.is_live_streaming:
                    encoded = base64.b64encode(data).decode("utf-8")
                    b64_img = f"data:image/jpeg;base64,{encoded}"

                    async with httpx.AsyncClient(timeout=3.0) as client:
                        try:
                            resp = await client.post(
                                f"{self.state.server_url}/api/v1/detect-face-base64",
                                json={"image_base64": b64_img, "threshold": 0.48}
                            )
                            if resp.status_code == 200 and self.state.is_live_streaming:
                                data_json = resp.json()
                                self.state.detection_result = data_json
                                if data_json.get("annotated_image_base64"):
                                    self.state.annotated_b64 = data_json["annotated_image_base64"]
                                    self.state.captured_b64 = b64_img
                                    self.update_scan_results()
                        except Exception:
                            pass
            except Exception:
                pass

            await asyncio.sleep(0.3)

    async def capture_from_camera(self, e):
        if not self.is_camera_supported() or not self.camera_initialized:
            self.scan_status_text.value = "Camera not available. Please click Upload to select photo."
            self.scan_status_text.update()
            await self.pick_scan_image(e)
            return
        self.scan_status_text.value = "Capturing photo..."
        self.scan_status_text.update()
        try:
            data = await asyncio.wait_for(self.camera_preview.take_picture(), timeout=3.0)
            if data:
                encoded = base64.b64encode(data).decode("utf-8")
                self.state.captured_b64 = f"data:image/jpeg;base64,{encoded}"
                self.scan_status_text.value = "Photo captured. Running Face AI..."
                self.scan_status_text.update()
                self.update_scan_display()
                asyncio.create_task(self.run_detection(self.state.captured_b64))
        except (asyncio.TimeoutError, Exception) as ex:
            err_msg = str(ex)
            if "Timeout" in err_msg or "TimeoutException" in err_msg or isinstance(ex, asyncio.TimeoutError):
                self.scan_status_text.value = "Camera stream timeout. Launching Camera Picker..."
                self.scan_status_text.update()
                await asyncio.sleep(0.5)
                await self.pick_scan_image(e)
            else:
                self.scan_status_text.value = f"Capture Note: {ex}"
                self.scan_status_text.update()

    async def pick_scan_image(self, e):
        files = await self._safe_pick_files(allow_multiple=False, file_type=ft.FilePickerFileType.IMAGE, with_data=True)
        if files and len(files) > 0:
            try:
                data = _get_file_bytes(files[0])
                if data:
                    encoded = base64.b64encode(data).decode("utf-8")
                    self.state.captured_b64 = f"data:image/jpeg;base64,{encoded}"
                    self.scan_status_text.value = "Photo loaded. Running Face AI..."
                    self.scan_status_text.update()
                    self.update_scan_display()
                    asyncio.create_task(self.run_detection(self.state.captured_b64))
            except Exception as ex:
                self.scan_status_text.value = f"Error reading file: {ex}"
                self.scan_status_text.update()

    async def _safe_pick_files(self, **kwargs):
        """Wrapper around file_picker.pick_files that prevents concurrent native dialog calls."""
        if self._picker_busy:
            return None
        self._picker_busy = True
        try:
            return await self.file_picker.pick_files(**kwargs)
        finally:
            self._picker_busy = False

    def clear_captured_photo(self, e=None):
        if self.state.is_live_streaming:
            self.state.is_live_streaming = False
            self.live_stream_switch.value = False
            self.live_stream_switch.update()
        self.state.captured_b64 = ""
        self.state.annotated_b64 = ""
        self.state.detection_result = None
        self.captured_image_control.src = ""
        self.scan_status_text.value = "Live Feed Restored. Ready to scan."
        self.scan_status_text.update()
        self.update_scan_results()

        if self.is_camera_supported() and self.selected_camera:
            asyncio.create_task(self.start_camera_stream(self.selected_camera))

    async def run_detection(self, b64_img: str):
        if not b64_img: return
        self.state.is_scanning = True
        self.scan_status_text.value = "Scanning face via FastAPI AI..."
        self.scan_status_text.update()
        try:
            async with httpx.AsyncClient(timeout=10.0) as client:
                try:
                    resp = await client.post(
                        f"{self.state.server_url}/api/v1/detect-face-base64",
                        json={"image_base64": b64_img, "threshold": 0.48}
                    )
                except Exception:
                    resp = await client.post(
                        f"{self.state.server_url}/api/v1/detect-face",
                        data={"image_base64": b64_img, "threshold": "0.48"}
                    )

                if resp.status_code == 200:
                    data = resp.json()
                    self.state.detection_result = data
                    if data.get("annotated_image_base64"):
                        self.state.annotated_b64 = data["annotated_image_base64"]
                    count = data.get("face_count", 0)
                    self.scan_status_text.value = f"Scan complete: {count} face(s) detected."
                else:
                    self.scan_status_text.value = f"Detection API response ({resp.status_code})"
        except Exception as ex:
            self.scan_status_text.value = f"API Server Connection: {ex}"
        finally:
            self.state.is_scanning = False
            self.scan_status_text.update()
            self.update_scan_results()

    def update_scan_display(self):
        display_src = self.state.annotated_b64 if self.state.annotated_b64 else self.state.captured_b64
        self.camera_container.visible = not bool(display_src)
        self.image_container.visible = bool(display_src)
        self.delete_btn.visible = bool(display_src)
        if display_src:
            self.captured_image_control.src = display_src
            self.captured_image_control.update()
        self.camera_container.update()
        self.image_container.update()
        self.delete_btn.update()

    def update_scan_results(self):
        self.update_scan_display()
        faces_list = self.state.detection_result.get("faces", []) if self.state.detection_result else []
        self.results_column.controls.clear()

        if faces_list:
            for f in faces_list:
                is_matched = f.get("matched_name") != "UNKNOWN"
                self.results_column.controls.append(
                    ft.Container(
                        content=ft.Row([
                            ft.Container(content=ft.Icon(ft.Icons.VERIFIED_USER if is_matched else ft.Icons.ACCOUNT_BOX, color=ACCENT_GREEN if is_matched else ACCENT_BLUE, size=32), padding=8, bgcolor="#2000E676" if is_matched else "#2029B6F6", border_radius=10),
                            ft.Column([
                                ft.Row([
                                    ft.Text(f.get("matched_name", "UNKNOWN"), size=16, weight=ft.FontWeight.BOLD, color=ft.Colors.WHITE),
                                    ft.Container(content=ft.Text(f.get("role", "VISITOR"), size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.BLACK), bgcolor=ACCENT_GREEN if is_matched else ft.Colors.ORANGE_400, padding=ft.Padding.symmetric(horizontal=6, vertical=2), border_radius=6)
                                ], spacing=8),
                                ft.Text(f"Similarity Match: {f.get('similarity_percent', 0)}%", size=12, color=ft.Colors.GREY_300),
                                ft.Text(f"2.5D Liveness Score: {f.get('liveness_score', 0)} ({'REAL FACE' if f.get('is_real') else 'SPOOF'})", size=11, color=ACCENT_BLUE if f.get('is_real') else ft.Colors.RED_400)
                            ], spacing=3, expand=True)
                        ]), padding=12, bgcolor=BG_CARD, border_radius=12, border=ft.Border.all(1, BORDER_COLOR)
                    )
                )
        else:
            self.results_column.controls.append(ft.Container(content=ft.Text("No faces detected in current frame.", size=13, color=ft.Colors.GREY_500), padding=15, bgcolor=BG_CARD, border_radius=12))

        if self.app_page:
            self.results_column.update()

    def build_scan_view_layout(self):
        self.captured_image_control = ft.Image(src="", fit=ft.BoxFit.COVER, border_radius=12)
        
        self.camera_container = ft.Container(
            content=self.camera_preview if self.is_camera_supported() else self.build_photo_upload_fallback(),
            left=0, right=0, top=0, bottom=0,
            alignment=ft.Alignment.CENTER, bgcolor="#0A0B0E", border_radius=12,
            visible=True
        )
        self.image_container = ft.Container(
            content=self.captured_image_control,
            left=0, right=0, top=0, bottom=0,
            alignment=ft.Alignment.CENTER, bgcolor="#0A0B0E", border_radius=12,
            visible=False
        )

        main_display = ft.Stack([self.camera_container, self.image_container], height=280)
        self.results_column = ft.Column([ft.Container(content=ft.Text("No faces detected in current frame.", size=13, color=ft.Colors.GREY_500), padding=15, bgcolor=BG_CARD, border_radius=12)], spacing=10)

        self.delete_btn = ft.Row([
            ft.Button(
                "Delete Photo & Retake Live Stream",
                icon=ft.Icons.DELETE_FOREVER,
                style=ft.ButtonStyle(
                    bgcolor=ft.Colors.RED_700,
                    color=ft.Colors.WHITE,
                    alignment=ft.Alignment.CENTER
                ),
                on_click=self.clear_captured_photo,
                expand=True
            )
        ], alignment=ft.MainAxisAlignment.CENTER, visible=False)

        self.live_stream_switch = ft.Switch(
            label="Real-Time Live Video AI Stream",
            value=False,
            active_color=ACCENT_GREEN,
            on_change=self.toggle_live_stream
        )

        return ft.Column([
            ft.Container(
                content=ft.Stack([
                    main_display,
                    ft.Container(
                        content=ft.Row([
                            ft.Container(
                                content=ft.Text("LIVE RETICLE READY", size=10, weight=ft.FontWeight.BOLD, color=ACCENT_GREEN),
                                padding=ft.Padding.symmetric(horizontal=8, vertical=4), bgcolor="#B0000000", border_radius=8
                            ),
                            ft.Row([
                                ft.IconButton(
                                    icon=ft.Icons.TRANSFORM, icon_color=ft.Colors.WHITE, bgcolor="#B0000000", icon_size=18,
                                    tooltip="Mirror / Flip Selfie", on_click=self.toggle_mirror
                                ),
                                ft.IconButton(
                                    icon=ft.Icons.FLIP_CAMERA_IOS, icon_color=ft.Colors.WHITE, bgcolor="#B0000000", icon_size=18,
                                    tooltip="Switch Camera Source", on_click=self.switch_next_camera
                                )
                            ], spacing=4)
                        ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN),
                        top=8, left=8, right=8
                    )
                ]),
                border_radius=12, border=ft.Border.all(1, BORDER_COLOR)
            ),
            ft.Row([
                self.live_stream_switch
            ], alignment=ft.MainAxisAlignment.CENTER),
            ft.Row([
                self.camera_dropdown,
                ft.IconButton(ft.Icons.REFRESH, on_click=lambda e: asyncio.create_task(self.init_cameras()), tooltip="Refresh Camera List")
            ]),
            ft.Row([
                ft.Button("Take Photo", icon=ft.Icons.CAMERA, style=ft.ButtonStyle(bgcolor=ACCENT_GREEN, color=ft.Colors.BLACK),
                          on_click=self.capture_from_camera, expand=True),
                ft.Button("Upload", icon=ft.Icons.UPLOAD_FILE, style=ft.ButtonStyle(bgcolor=ACCENT_BLUE, color=ft.Colors.BLACK),
                          on_click=self.pick_scan_image),
                ft.IconButton(icon=ft.Icons.AUTORENEW, icon_color=ft.Colors.WHITE, bgcolor=BORDER_COLOR,
                              tooltip="Reset Live Camera", on_click=self.clear_captured_photo)
            ], spacing=10),
            self.delete_btn,
            ft.Row([
                ft.Icon(ft.Icons.CHECK_CIRCLE, size=16, color=ACCENT_GREEN),
                self.scan_status_text
            ], spacing=8),
            ft.Text("SCAN RESULTS & MATCHES", size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.GREY_400),
            self.results_column
        ], spacing=15, scroll=ft.ScrollMode.AUTO, expand=True)

    # --- Compare View Handlers ---
    async def pick_comp1_image(self, e):
        files = await self._safe_pick_files(allow_multiple=False, file_type=ft.FilePickerFileType.IMAGE, with_data=True)
        if files and len(files) > 0:
            data = _get_file_bytes(files[0])
            if data:
                self.state.compare_img1 = f"data:image/jpeg;base64,{base64.b64encode(data).decode('utf-8')}"
                self.comp1_img_control.src = self.state.compare_img1
                self.comp1_img_control.update()

    async def pick_comp2_image(self, e):
        files = await self._safe_pick_files(allow_multiple=False, file_type=ft.FilePickerFileType.IMAGE, with_data=True)
        if files and len(files) > 0:
            data = _get_file_bytes(files[0])
            if data:
                self.state.compare_img2 = f"data:image/jpeg;base64,{base64.b64encode(data).decode('utf-8')}"
                self.comp2_img_control.src = self.state.compare_img2
                self.comp2_img_control.update()

    async def run_compare(self, e=None):
        if not self.state.compare_img1 or not self.state.compare_img2: return
        self.state.is_comparing = True
        self.compare_status_text.value = "Comparing faces..."
        self.compare_status_text.update()
        try:
            async with httpx.AsyncClient(timeout=8.0) as client:
                resp = await client.post(
                    f"{self.state.server_url}/api/v1/compare-faces",
                    data={"image1_base64": self.state.compare_img1, "image2_base64": self.state.compare_img2}
                )
                if resp.status_code == 200:
                    data = resp.json()
                    verdict = data.get("verdict", "UNKNOWN")
                    sim = data.get("similarity_percent", 0.0)
                    self.compare_status_text.value = f"Verdict: {verdict} | Similarity: {sim}%"
                else:
                    self.compare_status_text.value = f"Comparison Error ({resp.status_code})"
        except Exception as ex:
            self.compare_status_text.value = f"API Error: {ex}"
        finally:
            self.state.is_comparing = False
            self.compare_status_text.update()

    def build_compare_view_layout(self):
        self.comp1_img_control = ft.Image(src="", height=120, fit=ft.BoxFit.COVER, border_radius=8)
        self.comp2_img_control = ft.Image(src="", height=120, fit=ft.BoxFit.COVER, border_radius=8)
        self.compare_status_text = ft.Text(self.state.compare_result_text, size=13, color=ft.Colors.WHITE)

        return ft.Column([
            ft.Text("2-PHOTO FACE COMPARISON TOOL", size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.GREY_400),
            ft.Row([
                ft.Container(
                    content=ft.Column([
                        self.comp1_img_control,
                        ft.Row([
                            ft.Button("Upload", on_click=self.pick_comp1_image),
                            ft.IconButton(ft.Icons.CAMERA_ALT, tooltip="Live Cam", on_click=lambda e: self.open_live_camera_dialog(lambda b64: setattr(self.state, 'compare_img1', b64) or setattr(self.comp1_img_control, 'src', b64) or self.comp1_img_control.update()))
                        ], spacing=4)
                    ], alignment=ft.MainAxisAlignment.CENTER, horizontal_alignment=ft.CrossAxisAlignment.CENTER),
                    height=200, expand=True, bgcolor=BG_CARD, border_radius=12, padding=8, border=ft.Border.all(1, BORDER_COLOR)
                ),
                ft.Container(
                    content=ft.Column([
                        self.comp2_img_control,
                        ft.Row([
                            ft.Button("Upload", on_click=self.pick_comp2_image),
                            ft.IconButton(ft.Icons.CAMERA_ALT, tooltip="Live Cam", on_click=lambda e: self.open_live_camera_dialog(lambda b64: setattr(self.state, 'compare_img2', b64) or setattr(self.comp2_img_control, 'src', b64) or self.comp2_img_control.update()))
                        ], spacing=4)
                    ], alignment=ft.MainAxisAlignment.CENTER, horizontal_alignment=ft.CrossAxisAlignment.CENTER),
                    height=200, expand=True, bgcolor=BG_CARD, border_radius=12, padding=8, border=ft.Border.all(1, BORDER_COLOR)
                )
            ], spacing=10),
            ft.Button("COMPARE FACES", icon=ft.Icons.COMPARE, style=ft.ButtonStyle(bgcolor=ACCENT_PURPLE, color=ft.Colors.WHITE),
                      on_click=lambda e: asyncio.create_task(self.run_compare()), width=300),
            self.compare_status_text
        ], spacing=15, horizontal_alignment=ft.CrossAxisAlignment.CENTER, scroll=ft.ScrollMode.AUTO, expand=True)

    # --- Multi-Photo Target Profile Gallery & Modals Handlers ---
    async def load_target_faces(self, e=None):
        try:
            async with httpx.AsyncClient(timeout=5.0) as client:
                resp = await client.get(f"{self.state.server_url}/api/v1/target-profiles")
                if resp.status_code == 200:
                    self.state.target_profiles = resp.json().get("profiles", [])
                    self.update_target_list_display()
        except Exception:
            pass

    def open_photo_preview(self, img_b64: str):
        if not self.app_page or not img_b64: return
        dialog = ft.AlertDialog(
            content=ft.Container(
                content=ft.Image(src=img_b64, fit=ft.BoxFit.CONTAIN),
                width=320, height=360, alignment=ft.Alignment.CENTER
            ),
            actions=[ft.TextButton("Close", on_click=lambda e: self.close_dialog(dialog))]
        )
        self.open_dialog(dialog)

    def open_view_profile_modal(self, p: Dict):
        if not self.app_page: return
        p_name = p.get("name", "")
        p_role = p.get("role", "VIP")
        p_dept = p.get("department", "General")
        photos = p.get("photos", [])
        profile_pic = p.get("profile_picture", "")
        created_at = p.get("created_at", "")

        role_color = ACCENT_GREEN if p_role == "VIP" else (ft.Colors.RED_400 if p_role == "BLACKLIST" else ACCENT_BLUE)

        gallery_grid = []
        for b64 in photos:
            if b64:
                gallery_grid.append(
                    ft.Container(
                        content=ft.Image(src=b64, width=76, height=76, fit=ft.BoxFit.COVER, border_radius=8),
                        border=ft.Border.all(1, BORDER_COLOR), border_radius=8,
                        ink=True, on_click=lambda e, src=b64: self.open_photo_preview(src)
                    )
                )

        gallery_container = ft.Container(
            content=ft.Row(gallery_grid, scroll=ft.ScrollMode.ALWAYS, spacing=8),
            height=84, clip_behavior=ft.ClipBehavior.ANTI_ALIAS
        ) if gallery_grid else ft.Text("No gallery photos available", size=12, color=ft.Colors.GREY_500)

        dialog = ft.AlertDialog(
            title=ft.Text(f"Target Profile: {p_name}", size=16, weight=ft.FontWeight.BOLD),
            content=ft.Container(
                content=ft.Column([
                    ft.Row([
                        ft.Image(src=profile_pic, width=56, height=56, fit=ft.BoxFit.COVER, border_radius=28) if profile_pic else ft.Icon(ft.Icons.ACCOUNT_CIRCLE, size=56, color=role_color),
                        ft.Column([
                            ft.Row([
                                ft.Text(p_name, size=16, weight=ft.FontWeight.BOLD, color=ft.Colors.WHITE),
                                ft.Container(content=ft.Text(p_role, size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.BLACK), bgcolor=role_color, padding=ft.Padding.symmetric(horizontal=6, vertical=2), border_radius=6)
                            ], spacing=6),
                            ft.Text(f"Department: {p_dept}", size=12, color=ft.Colors.GREY_300),
                            ft.Text(f"Registered: {str(created_at)[:10]}", size=11, color=ft.Colors.GREY_400)
                        ], spacing=3, expand=True)
                    ], spacing=12),
                    ft.Divider(height=1),
                    ft.Text(f"GALLERY PHOTOS ({len(photos)}) - Tap to enlarge:", size=11, weight=ft.FontWeight.BOLD, color=ACCENT_BLUE),
                    gallery_container
                ], spacing=10, tight=True),
                width=320, padding=6
            ),
            actions=[
                ft.TextButton("Close", on_click=lambda e: self.close_dialog(dialog))
            ]
        )
        self.open_dialog(dialog)

    def open_edit_profile_modal(self, p: Dict):
        if not self.app_page: return
        old_name = p.get("name", "")

        edit_name = ft.TextField(label="Full Name", value=old_name, height=40, text_size=13)
        edit_dept = ft.TextField(label="Department", value=p.get("department", "General"), height=40, text_size=13)
        edit_role = ft.Dropdown(
            label="Role", value=p.get("role", "VIP"), height=40, text_size=13,
            options=[ft.DropdownOption("VIP"), ft.DropdownOption("STAFF"), ft.DropdownOption("BLACKLIST")]
        )
        status_txt = ft.Text("", size=11, color=ACCENT_GREEN)

        async def save_profile_edit(e):
            if not edit_name.value: return
            status_txt.value = "Saving profile edits..."
            status_txt.update()
            try:
                async with httpx.AsyncClient(timeout=8.0) as client:
                    resp = await client.put(
                        f"{self.state.server_url}/api/v1/target-profiles/{old_name}",
                        data={
                            "new_name": edit_name.value,
                            "new_role": edit_role.value,
                            "new_department": edit_dept.value
                        }
                    )
                    if resp.status_code == 200:
                        status_txt.value = "Profile updated!"
                        self.close_dialog(dialog)
                        await self.load_target_faces()
                    else:
                        status_txt.value = "Update failed"
                        status_txt.update()
            except Exception as ex:
                status_txt.value = f"Error: {ex}"
                status_txt.update()

        dialog = ft.AlertDialog(
            title=ft.Text(f"Edit Profile: {old_name}", size=16, weight=ft.FontWeight.BOLD),
            content=ft.Container(
                content=ft.Column([
                    edit_name,
                    edit_dept,
                    edit_role,
                    status_txt
                ], spacing=10),
                width=320, padding=10
            ),
            actions=[
                ft.TextButton("Cancel", on_click=lambda e: self.close_dialog(dialog)),
                ft.Button("Save Changes", style=ft.ButtonStyle(bgcolor=ACCENT_GREEN, color=ft.Colors.BLACK),
                          on_click=lambda e: asyncio.create_task(save_profile_edit(e)))
            ]
        )
        self.open_dialog(dialog)

    def open_delete_confirm_modal(self, name: str):
        if not self.app_page: return
        dialog = ft.AlertDialog(
            title=ft.Text("Delete Target Profile?", size=16, weight=ft.FontWeight.BOLD, color=ft.Colors.RED_400),
            content=ft.Text(f"Are you sure you want to delete '{name}'? This cannot be undone.", size=13, color=ft.Colors.GREY_300),
            actions=[
                ft.TextButton("Cancel", on_click=lambda e: self.close_dialog(dialog)),
                ft.Button("Delete Profile", style=ft.ButtonStyle(bgcolor=ft.Colors.RED_700, color=ft.Colors.WHITE),
                          on_click=lambda e: self._do_delete_profile(dialog, name))
            ]
        )
        self.open_dialog(dialog)

    def _do_delete_profile(self, dialog: ft.AlertDialog, name: str):
        self.close_dialog(dialog)
        asyncio.create_task(self.delete_target_profile(name))

    def update_target_list_display(self):
        self.target_list_column.controls.clear()
        if self.state.target_profiles:
            for p in self.state.target_profiles:
                p_name = p.get("name", "")
                p_role = p.get("role", "VIP")
                p_dept = p.get("department", "General")
                photos = p.get("photos", [])
                profile_pic = p.get("profile_picture", "")

                role_color = ACCENT_GREEN if p_role == "VIP" else (ft.Colors.RED_400 if p_role == "BLACKLIST" else ACCENT_BLUE)

                # Build Photo Gallery Carousel/Row (Clickable thumbnails)
                gallery_items = []
                for p_b64 in photos:
                    if p_b64:
                        gallery_items.append(
                            ft.Container(
                                content=ft.Stack([
                                    ft.Image(src=p_b64, width=64, height=64, fit=ft.BoxFit.COVER, border_radius=8),
                                    ft.Container(
                                        content=ft.Icon(ft.Icons.ZOOM_IN, size=12, color=ft.Colors.WHITE),
                                        alignment=ft.Alignment.BOTTOM_RIGHT,
                                        padding=2,
                                        bgcolor="#80000000",
                                        border_radius=ft.BorderRadius(top_left=4, bottom_right=8, top_right=0, bottom_left=0)
                                    )
                                ]),
                                border=ft.Border.all(1, BORDER_COLOR),
                                border_radius=8,
                                ink=True,
                                tooltip="Tap to enlarge photo",
                                on_click=lambda e, src=p_b64: self.open_photo_preview(src)
                            )
                        )

                gallery_container = ft.Container(
                    content=ft.Row(gallery_items, scroll=ft.ScrollMode.ALWAYS, spacing=8),
                    height=72,
                    clip_behavior=ft.ClipBehavior.ANTI_ALIAS,
                    padding=ft.Padding.symmetric(vertical=2)
                ) if gallery_items else ft.Container()

                avatar_control = ft.Image(src=profile_pic, width=44, height=44, fit=ft.BoxFit.COVER, border_radius=22) if profile_pic else ft.Icon(ft.Icons.ACCOUNT_CIRCLE, size=44, color=role_color)

                target_card_data = p

                self.target_list_column.controls.append(
                    ft.Container(
                        content=ft.Column([
                            ft.Row([
                                avatar_control,
                                ft.Column([
                                    ft.Row([
                                        ft.Text(p_name, size=15, weight=ft.FontWeight.BOLD, color=ft.Colors.WHITE),
                                        ft.Container(
                                            content=ft.Text(p_role, size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.BLACK),
                                            bgcolor=role_color, padding=ft.Padding.symmetric(horizontal=6, vertical=2), border_radius=6
                                        )
                                    ], spacing=6),
                                    ft.Text(f"Dept: {p_dept} • Photos: {len(photos)}", size=11, color=ft.Colors.GREY_400)
                                ], spacing=2, expand=True),
                                ft.Row([
                                    ft.IconButton(
                                        icon=ft.Icons.VISIBILITY_OUTLINED, icon_color=ACCENT_BLUE, icon_size=20,
                                        tooltip="View Full Profile",
                                        on_click=lambda e, data=target_card_data: self.open_view_profile_modal(data)
                                    ),
                                    ft.IconButton(
                                        icon=ft.Icons.EDIT_OUTLINED, icon_color=ACCENT_GREEN, icon_size=20,
                                        tooltip="Edit Profile",
                                        on_click=lambda e, data=target_card_data: self.open_edit_profile_modal(data)
                                    ),
                                    ft.IconButton(
                                        icon=ft.Icons.DELETE_OUTLINED, icon_color=ft.Colors.RED_400, icon_size=20,
                                        tooltip="Delete Target Profile",
                                        on_click=lambda e, name=p_name: self.open_delete_confirm_modal(name)
                                    )
                                ], spacing=0)
                            ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN),
                            ft.Row([
                                ft.Icon(ft.Icons.PHOTO_LIBRARY_OUTLINED, size=12, color=ft.Colors.GREY_400),
                                ft.Text("MULTI-PHOTO GALLERY (Tap to view)", size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.GREY_400),
                            ], spacing=4) if gallery_items else ft.Container(),
                            gallery_container
                        ], spacing=6),
                        padding=12, bgcolor=BG_CARD, border_radius=12, border=ft.Border.all(1, BORDER_COLOR)
                    )
                )
        else:
            self.target_list_column.controls.append(ft.Container(content=ft.Text("No registered target profiles in SQLite DB", size=12, color=ft.Colors.GREY_500), padding=15, bgcolor=BG_CARD, border_radius=10))

        if self.app_page:
            self.target_list_column.update()

    async def delete_target_profile(self, name: str):
        try:
            async with httpx.AsyncClient(timeout=5.0) as client:
                resp = await client.delete(f"{self.state.server_url}/api/v1/target-profiles/{name}")
                if resp.status_code == 200:
                    await self.load_target_faces()
        except Exception:
            pass

    async def pick_reg_primary_image(self, e):
        self.reg_loading_ring.visible = True
        self.reg_status_text.value = "Loading primary photo..."
        self.reg_loading_ring.update()
        self.reg_status_text.update()
        try:
            files = await self._safe_pick_files(allow_multiple=False, file_type=ft.FilePickerFileType.IMAGE, with_data=True)
            if files and len(files) > 0:
                data = _get_file_bytes(files[0])
                if data:
                    self.state.reg_primary_b64 = f"data:image/jpeg;base64,{base64.b64encode(data).decode('utf-8')}"
                    self.update_reg_previews()
        finally:
            self.reg_loading_ring.visible = False
            self.reg_loading_ring.update()

    async def pick_reg_gallery_images(self, e):
        self.reg_loading_ring.visible = True
        self.reg_status_text.value = "Loading gallery photos..."
        self.reg_loading_ring.update()
        self.reg_status_text.update()
        try:
            files = await self._safe_pick_files(allow_multiple=True, file_type=ft.FilePickerFileType.IMAGE, with_data=True)
            if files and len(files) > 0:
                for f in files:
                    data = _get_file_bytes(f)
                    if data:
                        b64 = f"data:image/jpeg;base64,{base64.b64encode(data).decode('utf-8')}"
                        if b64 not in self.state.reg_gallery_b64_list:
                            self.state.reg_gallery_b64_list.append(b64)
                self.update_reg_previews()
        finally:
            self.reg_loading_ring.visible = False
            self.reg_loading_ring.update()

    def update_reg_previews(self):
        self.reg_preview_row.controls.clear()
        
        # Primary avatar preview
        if self.state.reg_primary_b64:
            self.reg_preview_row.controls.append(
                ft.Container(
                    content=ft.Stack([
                        ft.Image(src=self.state.reg_primary_b64, width=68, height=68, fit=ft.BoxFit.COVER, border_radius=34),
                        ft.Container(
                            content=ft.Text("PRIMARY", size=8, weight=ft.FontWeight.BOLD, color=ft.Colors.BLACK),
                            bgcolor=ACCENT_GREEN, padding=ft.Padding.symmetric(horizontal=4, vertical=1), border_radius=4,
                            bottom=0, right=0
                        )
                    ]),
                    border=ft.Border.all(2, ACCENT_GREEN), border_radius=34
                )
            )

        # Multi-gallery previews
        for idx, b64 in enumerate(self.state.reg_gallery_b64_list):
            def make_remove_handler(target_idx: int):
                return lambda e: self._remove_reg_gallery_photo(target_idx)

            self.reg_preview_row.controls.append(
                ft.Container(
                    content=ft.Stack([
                        ft.Image(src=b64, width=64, height=64, fit=ft.BoxFit.COVER, border_radius=8),
                        ft.Container(
                            content=ft.IconButton(
                                icon=ft.Icons.CLOSE, icon_size=12, icon_color=ft.Colors.WHITE,
                                tooltip="Remove Photo",
                                on_click=make_remove_handler(idx)
                            ),
                            bgcolor="#90000000", border_radius=10, width=20, height=20,
                            alignment=ft.Alignment.CENTER, top=2, right=2
                        )
                    ]),
                    border=ft.Border.all(1, BORDER_COLOR), border_radius=8
                )
            )

        total_photos = (1 if self.state.reg_primary_b64 else 0) + len(self.state.reg_gallery_b64_list)
        self.reg_status_text.value = f"{total_photos} photo(s) selected for target profile."
        if self.app_page:
            self.reg_preview_row.update()
            self.reg_status_text.update()

    def _remove_reg_gallery_photo(self, index: int):
        if 0 <= index < len(self.state.reg_gallery_b64_list):
            self.state.reg_gallery_b64_list.pop(index)
            self.update_reg_previews()

    async def register_new_target(self, e=None):
        name_val = self.reg_name_input.value.strip() if self.reg_name_input.value else ""
        all_photos = ([self.state.reg_primary_b64] if self.state.reg_primary_b64 else []) + self.state.reg_gallery_b64_list

        if not name_val or not all_photos:
            self.reg_status_text.value = "Please enter Name and select/capture Primary or Gallery photo."
            self.reg_status_text.update()
            return
        
        self.reg_loading_ring.visible = True
        self.reg_status_text.value = f"Registering '{name_val}' with {len(all_photos)} photo(s)..."
        self.reg_loading_ring.update()
        self.reg_status_text.update()
        success_count = 0
        try:
            async with httpx.AsyncClient(timeout=10.0) as client:
                for b64 in all_photos:
                    try:
                        resp = await client.post(
                            f"{self.state.server_url}/api/v1/register-face-json",
                            json={
                                "name": name_val,
                                "role": self.reg_role_dropdown.value or "VIP",
                                "department": self.reg_dept_input.value or "General",
                                "image_base64": b64
                            }
                        )
                    except Exception:
                        resp = await client.post(
                            f"{self.state.server_url}/api/v1/register-face",
                            data={
                                "name": name_val,
                                "role": self.reg_role_dropdown.value or "VIP",
                                "department": self.reg_dept_input.value or "General",
                                "image_base64": b64
                            }
                        )
                    if resp.status_code == 200:
                        success_count += 1

                if success_count > 0:
                    self.reg_status_text.value = f"Target '{name_val}' registered with {success_count} photo(s)!"
                    self.reg_name_input.value = ""
                    self.state.reg_primary_b64 = ""
                    self.state.reg_gallery_b64_list.clear()
                    self.update_reg_previews()
                    await self.load_target_faces()
                else:
                    self.reg_status_text.value = "Registration failed."
        except Exception as ex:
            self.reg_status_text.value = f"Error: {ex}"
        finally:
            self.reg_loading_ring.visible = False
            self.reg_loading_ring.update()
            self.reg_status_text.update()

    def build_target_db_view_layout(self):
        self.reg_name_input = ft.TextField(label="Full Name", height=40, text_size=13)
        self.reg_dept_input = ft.TextField(label="Department", height=40, text_size=13, expand=True)
        self.reg_role_dropdown = ft.Dropdown(
            label="Role", value="VIP", height=40, text_size=13, width=120,
            options=[ft.DropdownOption("VIP"), ft.DropdownOption("STAFF"), ft.DropdownOption("BLACKLIST")]
        )
        self.reg_status_text = ft.Text("", size=12, color=ACCENT_GREEN)
        self.reg_loading_ring = ft.ProgressRing(width=16, height=16, stroke_width=2, visible=False, color=ACCENT_GREEN)
        self.reg_preview_row = ft.Row([], scroll=ft.ScrollMode.ALWAYS, spacing=8)
        self.reg_preview_container = ft.Container(
            content=self.reg_preview_row,
            height=76,
            clip_behavior=ft.ClipBehavior.ANTI_ALIAS,
            padding=ft.Padding.symmetric(vertical=2)
        )
        self.target_list_column = ft.Column([ft.Text("No registered target profiles in SQLite DB", size=12, color=ft.Colors.GREY_500)], spacing=8)

        def add_primary_cam_photo(b64):
            self.state.reg_primary_b64 = b64
            self.update_reg_previews()

        def add_gallery_cam_photo(b64):
            if b64 not in self.state.reg_gallery_b64_list:
                self.state.reg_gallery_b64_list.append(b64)
            self.update_reg_previews()

        return ft.Column([
            ft.Row([
                ft.Text("TARGET FACES DATABASE & GALLERY", size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.GREY_400),
                ft.IconButton(ft.Icons.REFRESH, on_click=lambda e: asyncio.create_task(self.load_target_faces()), tooltip="Refresh List")
            ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN),
            ft.Container(
                content=ft.Column([
                    ft.Text("Register Target Profile (Primary Pic + Multi-Gallery)", size=13, weight=ft.FontWeight.BOLD, color=ACCENT_GREEN),
                    self.reg_name_input,
                    ft.Row([self.reg_dept_input, self.reg_role_dropdown], spacing=10),
                    ft.Row([
                        ft.Button("Primary Pic (Upload)", icon=ft.Icons.ACCOUNT_BOX, on_click=self.pick_reg_primary_image, expand=True),
                        ft.IconButton(ft.Icons.CAMERA_ALT, tooltip="Live Cam Primary Photo", on_click=lambda e: self.open_live_camera_dialog(add_primary_cam_photo))
                    ], spacing=6),
                    ft.Row([
                        ft.Button("Add Gallery Photos (Multi)", icon=ft.Icons.ADD_A_PHOTO, on_click=self.pick_reg_gallery_images, expand=True),
                        ft.IconButton(ft.Icons.CAMERA_ALT, tooltip="Live Cam Gallery Photo", on_click=lambda e: self.open_live_camera_dialog(add_gallery_cam_photo))
                    ], spacing=6),
                    self.reg_preview_container,
                    ft.Button("Register Target Profile", icon=ft.Icons.PERSON_ADD, style=ft.ButtonStyle(bgcolor=ACCENT_GREEN, color=ft.Colors.BLACK),
                              on_click=lambda e: asyncio.create_task(self.register_new_target())),
                    ft.Row([self.reg_loading_ring, self.reg_status_text], spacing=8)
                ], spacing=8),
                padding=12, bgcolor=BG_CARD, border_radius=12, border=ft.Border.all(1, BORDER_COLOR)
            ),
            self.target_list_column
        ], spacing=15, scroll=ft.ScrollMode.AUTO, expand=True)

    def build_settings_view_layout(self):
        return ft.Column([
            ft.Text("FASTAPI SERVER CONNECTION SETTINGS", size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.GREY_400),
            ft.TextField(
                label="FastAPI Server Host URL", value=self.state.server_url,
                on_change=lambda e: setattr(self.state, 'server_url', e.control.value),
                hint_text="e.g. http://localhost:8000 or http://192.168.1.10:8000"
            ),
            ft.Button("Test Ping Health Endpoint", icon=ft.Icons.NETWORK_CHECK, on_click=lambda e: asyncio.create_task(self.check_api_health()))
        ], spacing=15, scroll=ft.ScrollMode.AUTO, expand=True)

    def set_tab(self, index: int):
        self.state.active_tab = index
        self.scan_view_container.visible = (index == 0)
        self.target_db_view_container.visible = (index == 1)
        self.settings_view_container.visible = (index == 2)
        self.bottom_nav.selected_index = index
        if self.app_page:
            self.app_page.update()

    def on_nav_change(self, e):
        idx = int(e.control.selected_index)
        self.set_tab(idx)

    def build_bottom_nav(self):
        self.bottom_nav = ft.NavigationBar(
            selected_index=self.state.active_tab,
            on_change=self.on_nav_change,
            bgcolor=BG_CARD,
            destinations=[
                ft.NavigationBarDestination(icon=ft.Icons.CENTER_FOCUS_STRONG_OUTLINED, selected_icon=ft.Icons.CENTER_FOCUS_STRONG, label="Detect"),
                ft.NavigationBarDestination(icon=ft.Icons.PEOPLE_OUTLINE, selected_icon=ft.Icons.PEOPLE, label="Targets"),
                ft.NavigationBarDestination(icon=ft.Icons.SETTINGS_OUTLINED, selected_icon=ft.Icons.SETTINGS, label="Settings"),
            ]
        )
        return self.bottom_nav

    def build_app_bar(self):
        self.app_bar = ft.AppBar(
            leading=ft.Container(
                content=ft.Icon(ft.Icons.SECURITY_ROUNDED, color=ACCENT_GREEN, size=24),
                padding=ft.Padding.only(left=12)
            ),
            leading_width=36,
            title=ft.Column([
                ft.Text("SHADOW EYE", size=16, weight=ft.FontWeight.BOLD, color=ft.Colors.WHITE),
                ft.Text("Mobile & Web Face AI Scanner", size=11, color=ft.Colors.GREY_400)
            ], spacing=1),
            center_title=False,
            bgcolor=BG_CARD,
            actions=[
                ft.Container(
                    content=ft.Row([self.api_dot, self.api_status_text], spacing=6),
                    padding=ft.Padding.symmetric(horizontal=10, vertical=4),
                    border_radius=12, bgcolor=BORDER_COLOR,
                    margin=ft.Margin.only(right=12)
                )
            ]
        )
        return self.app_bar

    def build_ui(self):
        self.scan_view_container = ft.Container(content=self.build_scan_view_layout(), expand=True, visible=True)
        self.target_db_view_container = ft.Container(content=self.build_target_db_view_layout(), expand=True, visible=False)
        self.settings_view_container = ft.Container(content=self.build_settings_view_layout(), expand=True, visible=False)

        active_content = ft.Stack([
            self.scan_view_container,
            self.target_db_view_container,
            self.settings_view_container,
        ], expand=True)

        layout_col = ft.Column([
            ft.Container(content=active_content, expand=True, padding=ft.Padding.symmetric(vertical=4)),
            self.build_bottom_nav()
        ], expand=True, spacing=0)

        return ft.SafeArea(content=layout_col, expand=True)

def main(page: ft.Page):
    page.title = "Shadow EYE - Face AI Scanner"
    page.theme_mode = ft.ThemeMode.DARK
    page.padding = 0
    view = MobileFaceScannerView(page)
    page.add(ft.SafeArea(content=view, expand=True))
    page.update()

if __name__ == "__main__":
    ft.run(main)
