# src/views/liveMonitorView.py

import flet as ft
import math
from typing import Optional, Callable
from controllers.camera_controller import CameraController
from services.camera_service import CameraService
from services.telegram_service import TelegramService
from views.components.userProfileDialog import show_user_profile_dialog
from views.components.typography import AppText
from core.helper import use_loc
from config.fonts import AppFonts

from views.components.cameraAlertDialog import show_camera_alert_dispatch_dialog

def show_bot_qr_dialog(page: ft.Page):
    dlg = ft.AlertDialog(
        title=ft.Text("Telegram Bot QR Code", size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.CYAN_400),
        content=ft.Column([
            ft.Text("Scan this QR code with Telegram to connect to the @SITE_Alert_101_bot.", size=11, text_align=ft.TextAlign.CENTER),
            ft.Image(src="telegram_bot_qr.png", width=250, height=250, fit=ft.BoxFit.CONTAIN, border_radius=8)
        ], tight=True, alignment=ft.MainAxisAlignment.CENTER, horizontal_alignment=ft.CrossAxisAlignment.CENTER),
        actions=[ft.TextButton("CLOSE", on_click=lambda _: page.pop_dialog())],
        actions_alignment=ft.MainAxisAlignment.END,
    )
    page.show_dialog(dlg)

@ft.component
def SingleCameraTile(
    cam_info: dict,
    height: int = 200,
    on_focus: Optional[Callable[[], None]] = None,
    is_focused: bool = False,
    hud_enabled: bool = True,
    is_selected: bool = False,
    on_select_toggle: Optional[Callable[[], None]] = None,
    on_dispatch_alert: Optional[Callable[[dict, str], None]] = None
):
    """
    Sub-component for an individual camera stream tile with data stream loading indicator,
    tactical HUD overlay toggle, single/multi view focus action, camera selection,
    and per-camera direct SMS/Telegram alert dispatching.
    """
    cam_source = cam_info.get("source", "0")
    cam_name = cam_info.get("name", "Camera Stream")

    cam_controller = ft.use_memo(lambda: CameraController(source=cam_source), [cam_source])
    initial_b64 = ft.use_memo(lambda: cam_controller._generate_synthetic_frame(0), [cam_source])
    
    frame_b64, set_frame_b64 = ft.use_state(initial_b64)
    is_loading, set_is_loading = ft.use_state(True)
    camera_service = ft.use_memo(lambda: CameraService(), [])
    ai_enabled, set_ai_enabled = ft.use_state(bool(cam_info.get("human_detection", 1)))
    face_enabled, set_face_enabled = ft.use_state(False)
    crowd_mode, set_crowd_mode = ft.use_state(False)
    alarm_enabled, set_alarm_enabled = ft.use_state(bool(cam_info.get("telegram_alert_enabled", 0)))

    def handle_toggle_ai(e=None):
        new_val = not ai_enabled
        set_ai_enabled(new_val)
        if cam_info.get("id"):
            camera_service.update_camera(
                camera_id=cam_info["id"],
                name=cam_info.get("name", "Camera"),
                device_type=cam_info.get("device_type", "webcam"),
                source=cam_source,
                camera_group=cam_info.get("camera_group", "Zone-01"),
                detection_model=cam_info.get("detection_model", "yolov8n"),
                motion_detection=cam_info.get("motion_detection", 0),
                human_detection=1 if new_val else 0,
                telegram_chat_id=cam_info.get("telegram_chat_id", ""),
                telegram_alert_enabled=1 if alarm_enabled else 0
            )

    def handle_toggle_face(e=None):
        new_face = not face_enabled
        set_face_enabled(new_face)
        if new_face:
            # Face Detection ON → disable human (AI) detection and motion detection
            set_ai_enabled(False)
            if cam_info.get("id"):
                camera_service.update_camera(
                    camera_id=cam_info["id"],
                    name=cam_info.get("name", "Camera"),
                    device_type=cam_info.get("device_type", "webcam"),
                    source=cam_source,
                    camera_group=cam_info.get("camera_group", "Zone-01"),
                    detection_model=cam_info.get("detection_model", "yolov8n"),
                    motion_detection=0,
                    human_detection=0,
                    telegram_chat_id=cam_info.get("telegram_chat_id", ""),
                    telegram_alert_enabled=1 if alarm_enabled else 0
                )

    def handle_toggle_crowd(e=None):
        set_crowd_mode(not crowd_mode)

    def handle_toggle_alarm(e=None):
        new_val = not alarm_enabled
        set_alarm_enabled(new_val)
        if cam_info.get("id"):
            camera_service.update_camera(
                camera_id=cam_info["id"],
                name=cam_info.get("name", "Camera"),
                device_type=cam_info.get("device_type", "webcam"),
                source=cam_source,
                camera_group=cam_info.get("camera_group", "Zone-01"),
                detection_model=cam_info.get("detection_model", "yolov8n"),
                motion_detection=cam_info.get("motion_detection", 0),
                human_detection=1 if ai_enabled else 0,
                telegram_chat_id=cam_info.get("telegram_chat_id", ""),
                telegram_alert_enabled=1 if new_val else 0
            )

    # Safely capture page reference during component render time (when context is valid)
    try:
        page = ft.context.page
    except Exception:
        page = None

    def setup_tile():
        mounted = {"active": True}
        set_is_loading(True)
        set_frame_b64(cam_controller._generate_synthetic_frame(0))
        
        def on_frame(b64: str):
            if mounted["active"]:
                set_frame_b64(b64)
                set_is_loading(False)
        cam_controller.start(on_frame)
        def cleanup():
            mounted["active"] = False
            cam_controller.stop()
        return cleanup

    ft.use_effect(setup_tile, [cam_source, cam_info.get("id")])

    # Sync HUD overlay setting with CameraController
    cam_controller.hud_enabled = hud_enabled
    
    # Sync AI Detection, Face Detection, Crowd Mode, and Alert Callback
    cam_controller.ai_detection_enabled = ai_enabled
    cam_controller.face_detection_enabled = face_enabled
    cam_controller.crowd_mode_enabled = crowd_mode
    
    def on_human_detected(source: str, b64_frame: str, event_type: str = "HUMAN DETECTED", person_name: Optional[str] = None):
        if not alarm_enabled:
            return
        try:
            import base64
            telegram_service = TelegramService()
            photo_bytes = base64.b64decode(b64_frame) if isinstance(b64_frame, str) else b64_frame

            # Face detection model label override
            model_label = "OpenCV Haar Cascade" if "FACE" in event_type else "YOLOv8 + ArcFace 2.5D"

            telegram_service.send_camera_alert(
                camera=cam_info,
                photo_source=photo_bytes,
                detection_type=event_type,
                confidence=0.92,
                model_used=model_label,
                person_name=person_name
            )
            # Show a snackbar on UI as well using captured page reference
            if page:
                try:
                    display_msg = f"🚨 {event_type} ({person_name}) on {cam_name}!" if person_name else f"🚨 {event_type} on {cam_name}!"
                    page.show_dialog(
                        ft.SnackBar(
                            content=ft.Text(f"{display_msg} Telegram Alert Dispatched.", color=ft.Colors.WHITE, weight=ft.FontWeight.BOLD),
                            bgcolor=ft.Colors.PURPLE_800 if "FACE" in event_type else (
                                ft.Colors.RED_800 if "FALL" in event_type else ft.Colors.AMBER_900
                            )
                        )
                    )
                except Exception:
                    pass
        except Exception as e:
            pass

    cam_controller.on_human_detected_callback = on_human_detected
    cam_controller.on_fall_detected_callback = lambda src, b64: on_human_detected(src, b64, "FALL DETECTED")



    img_control = ft.Image(
        key=f"tile_{cam_info.get('id', 1)}_{cam_source}",
        src=f"data:image/jpeg;base64,{frame_b64}" if frame_b64 else "",
        fit=ft.BoxFit.COVER,
        gapless_playback=True,
        border_radius=8,
        expand=True
    )

    # Loading / Stream Fetching Overlay Component
    loading_overlay = ft.Container(
        alignment=ft.Alignment(0, 0),
        bgcolor=ft.Colors.with_opacity(0.85, ft.Colors.BLACK),
        content=ft.Column([
            ft.ProgressRing(width=24, height=24, stroke_width=2.5, color=ft.Colors.CYAN_400),
            ft.Text("FETCHING RTSP DATA STREAM...", size=10, color=ft.Colors.CYAN_300, weight=ft.FontWeight.BOLD, ),
            ft.Text("ESTABLISHING ENCRYPTED HANDSHAKE", size=8, color=ft.Colors.WHITE_54)
        ], alignment=ft.MainAxisAlignment.CENTER, horizontal_alignment=ft.CrossAxisAlignment.CENTER, spacing=6)
    )

    # HUD Overlay Status Badge (Top-Left alignment to match screenshot)
    hud_overlay_layer = ft.Container(
        alignment=ft.Alignment(-0.96, -0.92),
        content=ft.Row([
            ft.Container(
                padding=ft.Padding(6, 2, 6, 2),
                bgcolor=ft.Colors.with_opacity(0.85, ft.Colors.BLACK),
                border_radius=4,
                border=ft.Border.all(1, ft.Colors.CYAN_900),
                content=ft.Row([
                    ft.Container(width=6, height=6, border_radius=3, bgcolor=ft.Colors.CYAN_400),
                    ft.Text(f"HUD ACTIVE • {cam_info.get('device_type', 'cctv').upper()}", size=8, color=ft.Colors.CYAN_200, weight=ft.FontWeight.BOLD)
                ], spacing=4)
            )
        ])
    ) if hud_enabled else ft.Container()

    return ft.Container(
        height=height,
        bgcolor=ft.Colors.BLACK,
        border_radius=10,
        border=ft.Border.all(2, ft.Colors.CYAN_400) if is_selected else ft.Border.all(1, ft.Colors.CYAN_600 if is_focused else ft.Colors.BLUE_900),
        clip_behavior=ft.ClipBehavior.ANTI_ALIAS,
        alignment=ft.Alignment(0, 0),
        content=ft.Stack([
            img_control,
            
            # Data Stream Reloading / Connecting Spinner Overlay
            loading_overlay if is_loading else ft.Container(),

            # Top-Left HUD Overlay Badge (if HUD enabled)
            hud_overlay_layer,

            # Top-Center: Face Detection mode status badge (generic, no individual name)
            ft.Container(
                alignment=ft.Alignment(0, -0.92),
                content=ft.Container(
                    padding=ft.Padding(8, 4, 10, 4),
                    bgcolor=ft.Colors.with_opacity(0.85, ft.Colors.PURPLE_900),
                    border_radius=14,
                    border=ft.Border.all(1.5, ft.Colors.PURPLE_400),
                    content=ft.Row([
                        ft.Icon(ft.Icons.FACE_5, size=15, color=ft.Colors.PURPLE_300),
                        ft.Text("FACE DETECT: ON", size=10, color=ft.Colors.PURPLE_100, weight=ft.FontWeight.BOLD)
                    ], spacing=5, tight=True)
                )
            ) if face_enabled else ft.Container(),


            # Top-Right Layer: Webcam Name Badge (without extra SELECTED tag as requested)
            ft.Container(
                alignment=ft.Alignment(0.96, -0.92),
                content=ft.Container(
                    padding=ft.Padding(7, 3, 7, 3),
                    bgcolor=ft.Colors.with_opacity(0.9, ft.Colors.CYAN_900 if is_selected else ft.Colors.BLACK),
                    border_radius=6,
                    border=ft.Border.all(1, ft.Colors.CYAN_400 if is_selected else ft.Colors.CYAN_900),
                    on_click=lambda _: on_select_toggle() if on_select_toggle else None,
                    tooltip="Click to toggle selection for " + cam_name,
                    content=ft.Row([
                        ft.Icon(
                            ft.Icons.CHECK_BOX_ROUNDED if is_selected else ft.Icons.CHECK_BOX_OUTLINE_BLANK_ROUNDED,
                            size=14,
                            color=ft.Colors.CYAN_400 if is_selected else (ft.Colors.GREY_500 if is_loading else ft.Colors.GREEN_400)
                        ),
                        ft.Text(cam_name, size=10, color=ft.Colors.WHITE, weight=ft.FontWeight.BOLD)
                    ], spacing=5, tight=True)
                )
            ),

            # Bottom-Left Layer: Action Icon Buttons (Select Checkbox, AI Detection, Alarm Mode, Alert Dispatch, Focus View)
            ft.Container(
                alignment=ft.Alignment(-0.96, 0.92),
                content=ft.Row([
                    # 0. Select / Deselect CCTV Checkbox Button
                    ft.IconButton(
                        icon=ft.Icons.CHECK_BOX_ROUNDED if is_selected else ft.Icons.CHECK_BOX_OUTLINE_BLANK_ROUNDED,
                        icon_color=ft.Colors.CYAN_400 if is_selected else ft.Colors.WHITE_54,
                        icon_size=18,
                        tooltip="Select / Deselect Camera",
                        on_click=lambda _: on_select_toggle() if on_select_toggle else None
                    ),
                    # 1. Toggle AI Detection
                    ft.IconButton(
                        icon=ft.Icons.PERSON_SEARCH_ROUNDED,
                        icon_color=ft.Colors.GREEN_400 if ai_enabled else ft.Colors.WHITE_54,
                        icon_size=18,
                        tooltip="Turn AI Human Pose Detection " + ("OFF" if ai_enabled else "ON"),
                        on_click=handle_toggle_ai
                    ),
                    # 1b. Toggle Dedicated Face Detection
                    ft.IconButton(
                        icon=ft.Icons.FACE_5,
                        icon_color=ft.Colors.PURPLE_300 if face_enabled else ft.Colors.WHITE_54,
                        icon_size=18,
                        tooltip="Turn Face Detection " + ("OFF" if face_enabled else "ON"),
                        on_click=handle_toggle_face
                    ),
                    # 1c. Toggle Crowd / High-Density Mode
                    ft.IconButton(
                        icon=ft.Icons.GROUPS_ROUNDED,
                        icon_color=ft.Colors.ORANGE_400 if crowd_mode else ft.Colors.WHITE_54,
                        icon_size=18,
                        tooltip="Crowd Scanning Mode: " + ("ACTIVE (Low Conf + High Resolution)" if crowd_mode else "OFF (Standard Mode)"),
                        on_click=handle_toggle_crowd
                    ),
                    # 2. Toggle Alarm Mode (Auto Telegram Alert on Detection)
                    ft.IconButton(
                        icon=ft.Icons.NOTIFICATIONS_ACTIVE_ROUNDED if alarm_enabled else ft.Icons.NOTIFICATIONS_OFF_ROUNDED,
                        icon_color=ft.Colors.AMBER_400 if alarm_enabled else ft.Colors.WHITE_54,
                        icon_size=18,
                        tooltip="Alarm Mode: " + ("ACTIVE (Auto Alert to Telegram when Human seen)" if alarm_enabled else "OFF"),
                        on_click=handle_toggle_alarm
                    ),
                    # 3. Dispatch Manual Snapshot Alert Icon
                    ft.IconButton(
                        icon=ft.Icons.CAMPAIGN_ROUNDED,
                        icon_color=ft.Colors.CYAN_300,
                        icon_size=18,
                        tooltip="Manual Dispatch Snapshot Alert for THIS Camera",
                        on_click=lambda _: on_dispatch_alert(cam_info, frame_b64) if on_dispatch_alert else None
                    ),
                    # 4. Focus / Enlarge Icon
                    ft.IconButton(
                        icon=ft.Icons.ASPECT_RATIO_ROUNDED if not is_focused else ft.Icons.GRID_VIEW_ROUNDED,
                        icon_color=ft.Colors.CYAN_400,
                        icon_size=18,
                        tooltip="Focus Single Feed" if not is_focused else "Back to 4-View Grid Matrix",
                        on_click=lambda _: on_focus() if on_focus else None
                    )
                ], spacing=0)
            )
        ], alignment=ft.Alignment(0, 0))
    )

@ft.component
def liveMonitorView():
    loc = use_loc()
    page = ft.context.page
    page_width = page.width if (page and page.width) else 1000

    # Fetch Camera Devices from SQLite DB Service
    camera_service = ft.use_memo(lambda: CameraService(), [])
    db_cameras = ft.use_memo(lambda: camera_service.get_cameras(), [])

    safe_cameras = db_cameras if (db_cameras and len(db_cameras) > 0) else [
        {"id": 1, "name": "Default PC Webcam", "device_type": "webcam", "source": "0", "camera_group": "Zone-01", "human_detection": 0, "motion_detection": 0, "telegram_alert_enabled": 0},
    ]

    # Zone Filter Selection State
    selected_zone, set_selected_zone = ft.use_state("ALL ZONES")
    available_zones = ["ALL ZONES"] + sorted(list(set([c.get("camera_group", "Zone-01") for c in safe_cameras])))

    # Filtered Cameras by Active Zone
    filtered_cams = [c for c in safe_cameras if selected_zone == "ALL ZONES" or c.get("camera_group") == selected_zone]
    active_display_cams = filtered_cams if filtered_cams else safe_cameras

    # View Mode State: "quad" (4-View 2x2 Grid) vs "single" (Focus 1 Camera)
    view_mode, set_view_mode = ft.use_state("quad")
    focused_cam, set_focused_cam = ft.use_state(active_display_cams[0])
    
    # 4-View Matrix Pagination State
    page_index, set_page_index = ft.use_state(0)
    cams_per_page = 4
    total_pages = max(1, math.ceil(len(active_display_cams) / cams_per_page))

    # HUD Overlay Toggle State (ON/OFF)
    hud_overlay_active, set_hud_overlay_active = ft.use_state(True)
    
    # Camera Selection & Batch Alert Dispatch State
    selected_cam_ids, set_selected_cam_ids = ft.use_state([])

    def handle_toggle_cam_selection(cam_id: int):
        if cam_id in selected_cam_ids:
            set_selected_cam_ids([cid for cid in selected_cam_ids if cid != cam_id])
        else:
            set_selected_cam_ids(selected_cam_ids + [cam_id])

    def handle_toggle_select_all():
        active_ids = [c["id"] for c in active_display_cams]
        all_selected = len(active_ids) > 0 and all(cid in selected_cam_ids for cid in active_ids)
        if all_selected:
            set_selected_cam_ids([cid for cid in selected_cam_ids if cid not in active_ids])
        else:
            new_selected = list(set(selected_cam_ids + active_ids))
            set_selected_cam_ids(new_selected)

    def handle_dispatch_single_cam_alert(cam_info: dict, frame_b64: str):
        show_camera_alert_dispatch_dialog(page, cam_info, frame_b64, telegram_service)

    def handle_dispatch_batch_alert(e):
        selected_cams = [c for c in safe_cameras if c["id"] in selected_cam_ids]
        target_cam = selected_cams[0] if selected_cams else active_display_cams[0]
        cam_controller = CameraController(source=target_cam.get("source", "0"))
        b64 = cam_controller._generate_synthetic_frame(0)
        show_camera_alert_dispatch_dialog(page, target_cam, b64, telegram_service)

    def handle_send_test_alert(cid: str):
        def _send():
            ok, msg = telegram_service.send_test_message(chat_id=cid)
            if page:
                try:
                    page.show_dialog(
                        ft.SnackBar(
                            content=ft.Text(f"{'✅' if ok else '⚠️'} {msg}", color=ft.Colors.WHITE, font_family=AppFonts.MYANMAR),
                            bgcolor=ft.Colors.GREEN_800 if ok else ft.Colors.RED_800
                        )
                    )
                except Exception:
                    pass
        if page:
            page.run_thread(_send)
        else:
            telegram_service.send_test_message(chat_id=cid)

    is_recording, set_is_recording = ft.use_state(True)
    alert_acknowledged, set_alert_acknowledged = ft.use_state(False)
    sms_relay_active, set_sms_relay_active = ft.use_state(True)

    # Telegram Service & Target Persistence State
    telegram_service = ft.use_memo(lambda: TelegramService(), [])
    tg_refresh_key, set_tg_refresh_key = ft.use_state(0)
    db_targets = ft.use_memo(lambda: telegram_service.get_targets(), [tg_refresh_key])

    # Recipient Search Query & Input Declarative State
    rec_search_query, set_rec_search_query = ft.use_state("")
    new_target_name, set_new_target_name = ft.use_state("")
    new_target_chat_id, set_new_target_chat_id = ft.use_state("")
    new_target_type_state, set_new_target_type_state = ft.use_state("user")

    # Filter Recipients dynamically by search query
    filtered_recipients = [
        t for t in db_targets
        if not rec_search_query.strip() or
        rec_search_query.lower() in t.get("target_name", "").lower() or
        rec_search_query.lower() in t.get("chat_id", "").lower() or
        rec_search_query.lower() in t.get("role", "").lower() or
        rec_search_query.lower() in t.get("phone", "").lower() or
        rec_search_query.lower() in t.get("note", "").lower()
    ]

    intelligence_alerts, set_intelligence_alerts = ft.use_state([
        {
            "id": 1,
            "type": "BIOMETRIC MATCH",
            "text": "Profile 88% match with known insurgent record A-409.",
            "icon": ft.Icons.FINGERPRINT_ROUNDED,
            "color": ft.Colors.BLUE_600
        },
        {
            "id": 2,
            "type": "PATTERN ALERT",
            "text": "Unusual loitering detected at Access Point Beta.",
            "icon": ft.Icons.WARNING_AMBER_ROUNDED,
            "color": ft.Colors.AMBER_600
        }
    ])

    logs, set_logs = ft.use_state([
        {"time": "14:02:11", "event": "Object Detection Cluster 4A", "status": "CRITICAL", "color": ft.Colors.RED_600},
        {"time": "14:01:45", "event": "Sensor Pulse Sector 7G", "status": "NOMINAL", "color": ft.Colors.GREEN_600},
        {"time": "13:58:22", "event": "Credential Verification Fail", "status": "WARNING", "color": ft.Colors.AMBER_600},
    ])

    # Show Priority Alpha Alert as a SnackBar Notification
    def trigger_alert_snack():
        if not alert_acknowledged and page:
            try:
                page.show_dialog(
                    ft.SnackBar(
                        content=ft.Row([
                            ft.Icon(ft.Icons.WARNING_ROUNDED, color=ft.Colors.WHITE, size=20),
                            ft.Text(
                                "PRIORITY ALPHA-1: UNAUTHORIZED PERIMETER BREACH DETECTED - SECTOR 7G",
                                color=ft.Colors.WHITE,
                                weight=ft.FontWeight.BOLD,
                                size=12
                            )
                        ], spacing=8),
                        bgcolor=ft.Colors.RED_900,
                        duration=6000,
                        action="ACKNOWLEDGE",
                        on_action=lambda _: set_alert_acknowledged(True)
                    )
                )
            except Exception:
                pass

    ft.use_effect(trigger_alert_snack, [])

    # Handlers for Pagination & View Actions
    def handle_prev_page(e):
        if page_index > 0:
            set_page_index(page_index - 1)

    def handle_next_page(e):
        if page_index < total_pages - 1:
            set_page_index(page_index + 1)

    def handle_remove_intel(alert_id: int):
        set_intelligence_alerts([a for a in intelligence_alerts if a["id"] != alert_id])

    def handle_remove_recipient(target_id: int):
        telegram_service.delete_target(target_id)
        set_tg_refresh_key(tg_refresh_key + 1)

    def handle_add_recipient(e):
        name = new_target_name.strip()
        cid = new_target_chat_id.strip()
        if name and cid:
            success, msg = telegram_service.add_target(
                target_name=name,
                target_type=new_target_type_state,
                chat_id=cid,
                note="Added from Live Monitor",
                role="OPERATIVE"
            )
            if success:
                set_new_target_name("")
                set_new_target_chat_id("")
                set_tg_refresh_key(tg_refresh_key + 1)

    def handle_focus_camera(cam: dict):
        """Enter single-camera focus view and immediately stop all other RTSP streams."""
        set_focused_cam(cam)
        set_view_mode("single")
        # Stop all active camera streams EXCEPT the focused one to save network bandwidth
        focused_source = str(cam.get("source", ""))
        try:
            from controllers.camera_controller import CameraController
            CameraController.stop_all_except(focused_source)
        except Exception:
            pass

    def handle_return_to_quad(e=None):
        """Return to quad grid view — stopped cameras will auto-reconnect via their setup_tile effect."""
        set_view_mode("quad")

    # Dynamic Layout Responsive Heights
    single_view_height = 420 if page_width > 1100 else 320 if page_width > 700 else 220
    grid_tile_height = 210 if page_width > 1100 else 180 if page_width > 700 else 160

    # Slice Cameras for Current Page (4 Cameras per Page)
    start_idx = page_index * cams_per_page
    end_idx = min(len(active_display_cams), start_idx + cams_per_page)
    current_page_cams = active_display_cams[start_idx:end_idx]

    def handle_change_zone(zone_val: str):
        set_selected_zone(zone_val)
        set_page_index(0)
        cams_in_zone = [c for c in safe_cameras if zone_val == "ALL ZONES" or c.get("camera_group") == zone_val]
        if cams_in_zone:
            set_focused_cam(cams_in_zone[0])

    # Zone Filter Selector Control Bar
    zone_selector_bar = ft.Container(
        content=ft.Row([
            ft.Icon(ft.Icons.LOCATION_ON_ROUNDED, color=ft.Colors.CYAN_400, size=18),
            ft.Text("ZONE / SECTION FILTER:", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.CYAN_300),
            ft.Dropdown(
                value=selected_zone,
                options=[ft.dropdown.Option(z, z) for z in available_zones],
                on_select=lambda e: handle_change_zone(e.control.value),
                width=240,
                dense=True,
                text_style=ft.TextStyle(size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.CYAN_100),
                bgcolor=ft.Colors.SURFACE_CONTAINER_HIGHEST,
                border_color=ft.Colors.CYAN_700,
            ),
            ft.Container(expand=True),
            ft.Text(f"ACTIVE: {len(active_display_cams)} CAMS IN {selected_zone.upper()}", size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.CYAN_400)
        ], alignment=ft.MainAxisAlignment.START, vertical_alignment=ft.CrossAxisAlignment.CENTER),
        padding=ft.Padding.symmetric(horizontal=12, vertical=6),
        bgcolor=ft.Colors.with_opacity(0.15, ft.Colors.BLACK),
        border_radius=8,
        border=ft.Border.all(1, ft.Colors.CYAN_900)
    )

    # Camera Selection & Batch Dispatch Toolbar Bar (Top Right Layout)
    active_ids = [c["id"] for c in active_display_cams]
    is_all_selected = len(active_ids) > 0 and all(cid in selected_cam_ids for cid in active_ids)
    selected_count_in_view = sum(1 for cid in active_ids if cid in selected_cam_ids)

    camera_selection_bar = ft.Container(
        padding=ft.Padding(6, 3, 6, 3),
        bgcolor=ft.Colors.SURFACE_CONTAINER,
        border_radius=8,
        border=ft.Border.all(1, ft.Colors.CYAN_700 if len(selected_cam_ids) > 0 else ft.Colors.OUTLINE_VARIANT),
        content=ft.Row([
            ft.IconButton(
                icon=ft.Icons.SELECT_ALL_ROUNDED if not is_all_selected else ft.Icons.DESELECT_ROUNDED,
                icon_size=16,
                icon_color=ft.Colors.CYAN_400 if is_all_selected else ft.Colors.ON_SURFACE_VARIANT,
                tooltip="Deselect All Cameras" if is_all_selected else "Select All Cameras",
                on_click=lambda _: handle_toggle_select_all()
            ),
            ft.Container(
                padding=ft.Padding(6, 2, 6, 2),
                bgcolor=ft.Colors.CYAN_900 if selected_count_in_view > 0 else ft.Colors.SURFACE_CONTAINER_HIGH,
                border_radius=4,
                content=ft.Text(
                    f"{selected_count_in_view}/{len(active_display_cams)} SELECTED",
                    size=9,
                    weight=ft.FontWeight.BOLD,
                    color=ft.Colors.CYAN_200 if selected_count_in_view > 0 else ft.Colors.ON_SURFACE_VARIANT
                )
            ),
            ft.Button(
                "DISPATCH ALERT",
                icon=ft.Icons.CAMPAIGN_ROUNDED,
                style=ft.ButtonStyle(
                    bgcolor=ft.Colors.AMBER_700 if selected_count_in_view > 0 else ft.Colors.SURFACE_CONTAINER_HIGH,
                    color=ft.Colors.WHITE if selected_count_in_view > 0 else ft.Colors.ON_SURFACE_VARIANT,
                    padding=ft.Padding(10, 4, 10, 4)
                ),
                on_click=handle_dispatch_batch_alert
            )
        ], spacing=6)
    )

    # 1. Main Live Video Feed Container (4-View Matrix vs Single Focus View)
    if view_mode == "single":
        active_focus = focused_cam if any(c["id"] == focused_cam.get("id") for c in active_display_cams) else active_display_cams[0]
        video_display_area = ft.Container(
            key=f"single_view_area_{active_focus['id']}_{selected_zone}",
            content=SingleCameraTile(
                key=f"single_tile_{active_focus['id']}_{active_focus['source']}",
                cam_info=active_focus,
                height=single_view_height,
                on_focus=handle_return_to_quad,
                is_focused=True,
                hud_enabled=hud_overlay_active,
                is_selected=active_focus["id"] in selected_cam_ids,
                on_select_toggle=lambda fid=active_focus["id"]: handle_toggle_cam_selection(fid),
                on_dispatch_alert=lambda cam_info=active_focus, b64="": handle_dispatch_single_cam_alert(cam_info, b64)
            )
        )
    else:
        # 4-View Grid Matrix (2x2 Layout per Page)
        grid_tiles = []
        for c in current_page_cams:
            grid_tiles.append(
                ft.Container(
                    key=f"grid_tile_{c['id']}_{selected_zone}_{page_index}",
                    col={"xs": 12, "md": 6},
                    content=SingleCameraTile(
                        key=f"tile_{c['id']}_{c['source']}",
                        cam_info=c,
                        height=grid_tile_height,
                        on_focus=lambda target_cam=c: handle_focus_camera(target_cam),
                        is_focused=False,
                        hud_enabled=hud_overlay_active,
                        is_selected=c["id"] in selected_cam_ids,
                        on_select_toggle=lambda cid=c["id"]: handle_toggle_cam_selection(cid),
                        on_dispatch_alert=lambda cam_info=c, b64="": handle_dispatch_single_cam_alert(cam_info, b64)
                    )
                )
            )
        video_display_area = ft.Container(
            key=f"quad_grid_area_{selected_zone}_{page_index}",
            content=ft.ResponsiveRow(controls=grid_tiles, spacing=10)
        )

    video_feed_card = ft.Container(
        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
        border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
        border_radius=14,
        padding=14,
        content=ft.Column(
            spacing=12,
            controls=[
                # Header Bar
                ft.Row(
                    alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                    vertical_alignment=ft.CrossAxisAlignment.CENTER,
                    controls=[
                        ft.Column([
                            ft.Row([
                                ft.Container(width=6, height=14, bgcolor=ft.Colors.CYAN_400, border_radius=3),
                                ft.Text("MULTI-CAMERA SURVEILLANCE MATRIX", size=10, color=ft.Colors.CYAN_400, weight=ft.FontWeight.BOLD,),
                            ], spacing=6),
                            ft.Text("4-VIEW QUAD MATRIX" if view_mode == "quad" else f"SINGLE VIEW - {focused_cam['name'].upper()}", size=16, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                        ], spacing=2),
                        
                        # Top Action Toolbar (Camera Selector Dropdown, HUD Overlay Toggle, View Mode Selector)
                        ft.Row([
                            ft.Dropdown(
                                value=str(focused_cam.get("id", "")),
                                label="🎥 SELECT CAMERA / SN STREAM",
                                hint_text="Switch camera stream...",
                                dense=True,
                                text_size=11,
                                width=260,
                                options=[
                                    ft.dropdown.Option(
                                        str(c["id"]),
                                        f"[{c.get('camera_group', 'Zone')}] {c['name']}"
                                    ) for c in safe_cameras
                                ],
                                on_select=lambda e: next(
                                    (handle_focus_camera(c) for c in safe_cameras if str(c["id"]) == e.control.value),
                                    None
                                )
                            ),
                            ft.Button(
                                "HUD OVERLAY: ON" if hud_overlay_active else "HUD OVERLAY: OFF",
                                icon=ft.Icons.GRID_ON_ROUNDED if hud_overlay_active else ft.Icons.GRID_OFF_ROUNDED,
                                style=ft.ButtonStyle(
                                    bgcolor=ft.Colors.CYAN_900 if hud_overlay_active else ft.Colors.SURFACE_CONTAINER,
                                    color=ft.Colors.CYAN_300 if hud_overlay_active else ft.Colors.GREY_400,
                                    padding=ft.Padding(10, 6, 10, 6)
                                ),
                                tooltip="Toggle Tactical Crosshairs & HUD Data Overlay",
                                on_click=lambda _: set_hud_overlay_active(not hud_overlay_active)
                            ),

                            # View Mode Selector (4-View Grid vs Single Focus)
                            ft.Container(
                                padding=ft.Padding(4, 4, 4, 4),
                                bgcolor=ft.Colors.SURFACE_CONTAINER,
                                border_radius=8,
                                border=ft.Border.all(1, ft.Colors.BLUE_900),
                                content=ft.Row([
                                    ft.IconButton(
                                        icon=ft.Icons.GRID_VIEW_ROUNDED,
                                        icon_size=18,
                                        icon_color=ft.Colors.CYAN_400 if view_mode == "quad" else ft.Colors.GREY_500,
                                        tooltip="4-View Quad Grid Matrix",
                                        on_click=handle_return_to_quad
                                    ),
                                    ft.IconButton(
                                        icon=ft.Icons.ASPECT_RATIO_ROUNDED,
                                        icon_size=18,
                                        icon_color=ft.Colors.CYAN_400 if view_mode == "single" else ft.Colors.GREY_500,
                                        tooltip="Single Camera Focused View",
                                        on_click=lambda _: handle_focus_camera(focused_cam)
                                    )
                                ], spacing=2)
                            ),

                            # Live Recording Indicator
                            ft.Container(
                                padding=ft.Padding(8, 4, 8, 4),
                                bgcolor=ft.Colors.RED_900 if is_recording else ft.Colors.SURFACE_CONTAINER,
                                border_radius=6,
                                content=ft.Row([
                                    ft.Container(width=8, height=8, border_radius=4, bgcolor=ft.Colors.RED_500 if is_recording else ft.Colors.GREY_500),
                                    ft.Text("REC ● LIVE" if is_recording else "PAUSED", size=11, color=ft.Colors.WHITE, weight=ft.FontWeight.BOLD)
                                ], spacing=6)
                            ),

                            # Camera Selection & Batch Alert Control Bar (Top Right)
                            camera_selection_bar
                        ], spacing=8, alignment=ft.MainAxisAlignment.END)
                    ]
                ),

                # Video Feed Display Area (4-View Grid or Single View)
                video_display_area,

                # Bottom Controls Toolbar: Camera Picker & 4-View Grid Pagination Controls (< PREV | NEXT >)
                ft.Row(
                    alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                    controls=[
                        # Left: Camera Dropdown Picker
                        ft.PopupMenuButton(
                            tooltip="Focus Specific Camera",
                            content=ft.Container(
                                padding=ft.Padding(8, 4, 8, 4),
                                bgcolor=ft.Colors.SURFACE_CONTAINER,
                                border_radius=6,
                                content=ft.Row([
                                    ft.Icon(ft.Icons.VIDEOCAM_ROUNDED, size=14, color=ft.Colors.BLUE_400),
                                    ft.Text(f"Focus: {focused_cam['name']}", size=11, weight=ft.FontWeight.BOLD, overflow=ft.TextOverflow.ELLIPSIS, max_lines=1),
                                    ft.Icon(ft.Icons.ARROW_DROP_DOWN_ROUNDED, size=14)
                                ], spacing=4)
                            ),
                            items=[
                                ft.PopupMenuItem(
                                    content=f"{c['name']} ({c['device_type'].upper()})",
                                    on_click=lambda e, target_c=c: handle_focus_camera(target_c)
                                ) for c in safe_cameras
                            ]
                        ),

                        # Right: 4-View Matrix Pagination Controls (< PREV | PAGE X / Y | NEXT >)
                        ft.Container(
                            padding=ft.Padding(4, 2, 4, 2),
                            bgcolor=ft.Colors.SURFACE_CONTAINER,
                            border_radius=8,
                            border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
                            content=ft.Row([
                                ft.IconButton(
                                    icon=ft.Icons.CHEVRON_LEFT_ROUNDED,
                                    icon_size=18,
                                    disabled=(page_index == 0),
                                    tooltip="Previous 4 Cameras",
                                    on_click=handle_prev_page
                                ),
                                ft.Text(f"PAGE {page_index + 1} OF {total_pages} ({len(safe_cameras)} CAMS)", size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.CYAN_300),
                                ft.IconButton(
                                    icon=ft.Icons.CHEVRON_RIGHT_ROUNDED,
                                    icon_size=18,
                                    disabled=(page_index >= total_pages - 1),
                                    tooltip="Next 4 Cameras",
                                    on_click=handle_next_page
                                ),
                            ], spacing=4)
                        ) if (view_mode == "quad" and total_pages > 1) else ft.Container()
                    ]
                )
            ]
        )
    )

    # 2. System Health & Intelligence Panel (Right Side Panel)
    system_health_panel = ft.Container(
        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
        border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
        border_radius=12,
        padding=14,
        content=ft.Column(
            spacing=14,
            controls=[
                ft.Text("SYSTEM HEALTH", size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE),
                ft.Column([
                    ft.Row([
                        ft.Text("Processing Load", size=12, color=ft.Colors.ON_SURFACE),
                        ft.Text("78%", size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.BLUE_400)
                    ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN),
                    ft.ProgressBar(value=0.78, color=ft.Colors.BLUE_500, bgcolor=ft.Colors.SURFACE_CONTAINER),
                    ft.Row([
                        ft.Text("Network Latency", size=12, color=ft.Colors.ON_SURFACE),
                        ft.Text("12ms", size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.GREEN_400)
                    ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN),
                ], spacing=6),

                ft.Divider(height=1),

                # Active Intelligence Section
                ft.Row([
                    ft.Text("ACTIVE INTELLIGENCE", size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE),
                ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN),

                ft.Column(
                    spacing=8,
                    controls=[
                        ft.Container(
                            key=f"intel_{item['id']}",
                            bgcolor=ft.Colors.SURFACE_CONTAINER,
                            border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
                            border_radius=8,
                            padding=10,
                            content=ft.Row([
                                ft.Icon(item["icon"], color=item["color"], size=20),
                                ft.Column([
                                    ft.Text(item["type"], size=11, weight=ft.FontWeight.BOLD, color=item["color"]),
                                    ft.Text(item["text"], size=11, color=ft.Colors.ON_SURFACE_VARIANT)
                                ], spacing=2, expand=True),
                                ft.IconButton(
                                    icon=ft.Icons.DELETE_OUTLINED,
                                    icon_size=16,
                                    tooltip="Dismiss Alert",
                                    on_click=lambda e, aid=item["id"]: handle_remove_intel(aid)
                                )
                            ], spacing=10)
                        ) for item in intelligence_alerts
                    ]
                ),

                ft.Divider(height=1),

                # Tactical Map Grid Section
                ft.Text("TACTICAL MAP", size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE),
                ft.Container(
                    height=130,
                    bgcolor=ft.Colors.BLACK,
                    border_radius=8,
                    padding=10,
                    content=ft.Stack([
                        ft.Column([
                            ft.Row([
                                ft.Text("SECTOR: 7G_A", size=10, color=ft.Colors.CYAN_400, weight=ft.FontWeight.BOLD),
                                ft.Text("MAP VIEW: LIGHT NODE", size=10, color=ft.Colors.WHITE_54)
                            ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN),
                            ft.Container(expand=True)
                        ]),
                        ft.Alignment(0, 0),
                        ft.Icon(ft.Icons.MAP_ROUNDED, size=50, color=ft.Colors.BLUE_900)
                    ])
                )
            ]
        )
    )

    # 3. Accumulator Logs Table Card
    accumulator_logs_card = ft.Container(
        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
        border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
        border_radius=12,
        padding=14,
        content=ft.Column(
            spacing=10,
            controls=[
                ft.Row([
                    ft.Text("ACCUMULATOR LOGS", size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE),
                    ft.Icon(ft.Icons.FILE_DOWNLOAD_OUTLINED, size=16, color=ft.Colors.OUTLINE)
                ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN),

                # Table Header
                ft.Row([
                    ft.Text("TIMESTAMP", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE, width=80),
                    ft.Text("EVENT", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE, expand=True),
                    ft.Text("STATUS", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE, width=70),
                ]),
                ft.Divider(height=1),

                # Table Rows
                ft.Column(
                    spacing=8,
                    controls=[
                        ft.Row([
                            ft.Text(row["time"], size=11, color=ft.Colors.ON_SURFACE, width=80),
                            ft.Text(row["event"], size=11, color=ft.Colors.ON_SURFACE_VARIANT, expand=True),
                            ft.Container(
                                padding=ft.Padding(6, 2, 6, 2),
                                bgcolor=row["color"],
                                border_radius=4,
                                content=ft.Text(row["status"], size=9, color=ft.Colors.WHITE, weight=ft.FontWeight.BOLD)
                            )
                        ]) for row in logs
                    ]
                )
            ]
        )
    )

    # 4. Security Notifications Card
    security_notifications_card = ft.Container(
        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
        border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
        border_radius=12,
        padding=14,
        content=ft.Column(
            spacing=12,
            controls=[
                ft.Text("SECURITY NOTIFICATIONS", size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE),

                ft.Container(
                    bgcolor=ft.Colors.SURFACE_CONTAINER,
                    border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
                    border_radius=8,
                    padding=10,
                    content=ft.Row([
                        ft.Icon(ft.Icons.SMS_OUTLINED, color=ft.Colors.BLUE_400, size=20),
                        ft.Column([
                            ft.Text("SMS Alert Relay", size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                            ft.Text("Automated SMS for breach events", size=11, color=ft.Colors.ON_SURFACE_VARIANT)
                        ], spacing=2, expand=True),
                        ft.Switch(
                            value=sms_relay_active,
                            on_change=lambda e: set_sms_relay_active(e.control.value),
                            active_color=ft.Colors.BLUE_600
                        )
                    ])
                ),
                ft.Divider(),
                ft.Row([
                    ft.Icon(ft.Icons.MARK_CHAT_UNREAD_ROUNDED, color=ft.Colors.CYAN_400, size=18),
                    ft.Text("TELEGRAM ALERT RECIPIENTS", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                    ft.Container(expand=True),
                    ft.IconButton(
                        icon=ft.Icons.QR_CODE_ROUNDED,
                        icon_size=16,
                        icon_color=ft.Colors.CYAN_400,
                        tooltip="Show Telegram Bot QR Code",
                        on_click=lambda e: show_bot_qr_dialog(page)
                    ),
                    ft.Container(
                        padding=ft.Padding(6, 2, 6, 2),
                        bgcolor=ft.Colors.CYAN_900,
                        border_radius=4,
                        content=ft.Text(f"{len(filtered_recipients)} RECIPIENTS", size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.CYAN_200)
                    )
                ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN),

                # Search Bar for Recipients & Targets
                ft.TextField(
                    value=rec_search_query,
                    on_change=lambda e: set_rec_search_query(e.control.value),
                    hint_text="Search recipient name, chat ID, role...",
                    hint_style=ft.TextStyle(color=ft.Colors.ON_SURFACE_VARIANT),
                    text_style=ft.TextStyle(color=ft.Colors.ON_SURFACE, weight=ft.FontWeight.BOLD),
                    prefix_icon=ft.Icons.SEARCH_ROUNDED,
                    suffix=ft.IconButton(
                        icon=ft.Icons.CLEAR_ROUNDED,
                        icon_size=15,
                        icon_color=ft.Colors.PRIMARY,
                        on_click=lambda _: set_rec_search_query("")
                    ) if rec_search_query else None,
                    dense=True,
                    text_size=11,
                    border_radius=8,
                    bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
                    border_color=ft.Colors.OUTLINE_VARIANT,
                ),

                # Recipient Tiles List
                ft.Column(
                    spacing=6,
                    controls=[
                        ft.Container(
                            key=f"rec_{r['id']}",
                            bgcolor=ft.Colors.SURFACE_CONTAINER,
                            border_radius=8,
                            padding=ft.Padding(8, 6, 8, 6),
                            border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
                            content=ft.Row([
                                ft.Stack([
                                    ft.CircleAvatar(
                                        content=ft.Text(r["target_name"][:2].upper(), size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_PRIMARY),
                                        radius=14,
                                        bgcolor=ft.Colors.PRIMARY
                                    ),
                                    ft.Container(
                                        width=7, height=7, border_radius=4, bgcolor=ft.Colors.GREEN_500,
                                        alignment=ft.Alignment(1, 1)
                                    )
                                ]),
                                ft.Column([
                                    ft.Row([
                                        ft.Text(r["target_name"], size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                                        ft.Container(
                                            padding=ft.Padding(4, 1, 4, 1),
                                            bgcolor=ft.Colors.PRIMARY_CONTAINER,
                                            border_radius=3,
                                            content=ft.Text(r.get("role", "OPERATIVE"), size=7, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_PRIMARY_CONTAINER)
                                        )
                                    ], spacing=4),
                                    ft.Text(f"ID: {r['chat_id']}", size=9, color=ft.Colors.ON_SURFACE_VARIANT, weight=ft.FontWeight.BOLD),
                                ], spacing=1, expand=True),
                                ft.Row([
                                    ft.IconButton(
                                        icon=ft.Icons.ACCOUNT_BOX_ROUNDED,
                                        icon_size=15,
                                        icon_color=ft.Colors.PRIMARY,
                                        tooltip="View User Profile",
                                        on_click=lambda e, target=r: show_user_profile_dialog(page, target, telegram_service)
                                    ),
                                    ft.IconButton(
                                        icon=ft.Icons.SEND_ROUNDED,
                                        icon_size=14,
                                        icon_color=ft.Colors.PRIMARY,
                                        tooltip="Send Test Alert",
                                        on_click=lambda e, cid=r["chat_id"]: handle_send_test_alert(cid)
                                    ),
                                    ft.IconButton(
                                        icon=ft.Icons.DELETE_OUTLINED,
                                        icon_size=14,
                                        icon_color=ft.Colors.RED_400,
                                        tooltip="Remove Target",
                                        on_click=lambda e, rid=r["id"]: handle_remove_recipient(rid)
                                    )
                                ], spacing=-4)
                            ])
                        ) for r in filtered_recipients
                    ] if filtered_recipients else [
                        ft.Container(
                            padding=10,
                            alignment=ft.Alignment(0, 0),
                            content=ft.Text("No matching recipients found", size=10, color=ft.Colors.ON_SURFACE_VARIANT)
                        )
                    ]
                ),

                ft.Divider(height=1),
                ft.Text("ADD TELEGRAM TARGET", size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE),
                
                ft.TextField(
                    value=new_target_name,
                    on_change=lambda e: set_new_target_name(e.control.value),
                    hint_text="Recipient / Target Name...",
                    dense=True,
                    text_size=11,
                    border_radius=8
                ),
                ft.Row([
                    ft.TextField(
                        value=new_target_chat_id,
                        on_change=lambda e: set_new_target_chat_id(e.control.value),
                        hint_text="Chat ID / Username...",
                        dense=True,
                        text_size=11,
                        expand=True,
                        border_radius=8
                    ),
                    ft.Button(
                        "+ ADD",
                        icon=ft.Icons.PERSON_ADD_ALT_1_ROUNDED,
                        style=ft.ButtonStyle(bgcolor=ft.Colors.CYAN_700, color=ft.Colors.WHITE),
                        on_click=handle_add_recipient
                    )
                ], spacing=6)
            ]
        )
    )

    # Emergency Action Button (Initiate Lockdown)
    lockdown_button = ft.Button(
        "INITIATE LOCKDOWN",
        icon=ft.Icons.LOCK_ROUNDED,
        style=ft.ButtonStyle(
            bgcolor=ft.Colors.RED_700,
            color=ft.Colors.WHITE,
            padding=ft.Padding(16, 14, 16, 14)
        ),
        on_click=lambda _: page.show_dialog(
            ft.AlertDialog(
                title=ft.Text("EMERGENCY LOCKDOWN INITIATED", color=ft.Colors.RED, weight=ft.FontWeight.BOLD),
                content=ft.Text("All access control points have been sealed. Security teams dispatched."),
                actions=[ft.TextButton("DISMISS", on_click=lambda e: page.pop_dialog())]
            )
        )
    )

    # Assembly into Responsive Grid Layout
    return ft.Container(
        expand=True,
        padding=12,
        content=ft.Column(
            spacing=12,
            expand=True,
            scroll=ft.ScrollMode.HIDDEN,
            controls=[
                ft.ResponsiveRow(
                    spacing=12,
                    controls=[
                        # Left / Center Main Content (Video Feed + Logs & Recipients)
                        ft.Container(
                            col={"xs": 12, "lg": 8, "xl": 8},
                            content=ft.Column([
                                video_feed_card,
                                ft.ResponsiveRow(
                                    spacing=12,
                                    controls=[
                                        ft.Container(col={"xs": 12, "md": 6}, content=accumulator_logs_card),
                                        ft.Container(col={"xs": 12, "md": 6}, content=security_notifications_card),
                                    ]
                                ),
                                lockdown_button
                            ], spacing=12)
                        ),

                        # Right Side Panel (Health, Active Intelligence, Tactical Map)
                        ft.Container(
                            col={"xs": 12, "lg": 4, "xl": 4},
                            content=system_health_panel
                        )
                    ]
                )
            ]
        )
    )
