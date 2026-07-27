# src/views/liveMonitorView.py

import flet as ft
import math
from typing import Optional, Callable
from controllers.camera_controller import CameraController
from services.camera_service import CameraService
from views.components.typography import AppText
from core.helper import use_loc
from config.fonts import AppFonts

@ft.component
def SingleCameraTile(
    cam_info: dict,
    height: int = 200,
    on_focus: Optional[Callable[[], None]] = None,
    is_focused: bool = False,
    hud_enabled: bool = True
):
    """
    Sub-component for an individual camera stream tile with data stream loading indicator,
    tactical HUD overlay toggle, and single/multi view focus action.
    """
    cam_source = cam_info.get("source", "0")
    cam_name = cam_info.get("name", "Camera Stream")

    cam_controller = ft.use_memo(lambda: CameraController(source=cam_source), [cam_source])
    initial_b64 = ft.use_memo(lambda: cam_controller._generate_synthetic_frame(0), [cam_source])
    
    frame_b64, set_frame_b64 = ft.use_state(initial_b64)
    is_loading, set_is_loading = ft.use_state(True)

    def setup_tile():
        set_is_loading(True)
        set_frame_b64(cam_controller._generate_synthetic_frame(0))
        
        def on_frame(b64: str):
            set_frame_b64(b64)
            set_is_loading(False)
        cam_controller.start(on_frame)
        return lambda: cam_controller.stop()

    ft.use_effect(setup_tile, [cam_source])

    # Sync HUD overlay setting with CameraController
    cam_controller.hud_enabled = hud_enabled

    img_control = ft.Image(
        key=f"tile_{cam_info.get('id', 1)}_{cam_source}",
        src=f"data:image/jpeg;base64,{frame_b64}" if frame_b64 else "",
        fit=ft.BoxFit.CONTAIN,
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
            ft.Text("ESTABLISHING ENCRYPTED HANDSHAKE", size=8, color=ft.Colors.WHITE54)
        ], alignment=ft.MainAxisAlignment.CENTER, horizontal_alignment=ft.CrossAxisAlignment.CENTER, spacing=6)
    )

    # HUD Overlay Badges (Toggleable)
    hud_overlay_layer = ft.Container(
        alignment=ft.Alignment(-0.96, 0.92),
        content=ft.Row([
            ft.Container(
                padding=ft.Padding(6, 2, 6, 2),
                bgcolor=ft.Colors.with_opacity(0.75, ft.Colors.BLACK),
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
        border=ft.Border.all(1, ft.Colors.CYAN_400 if is_focused else ft.Colors.BLUE_900),
        clip_behavior=ft.ClipBehavior.ANTI_ALIAS,
        alignment=ft.Alignment(0, 0),
        content=ft.Stack([
            img_control,
            
            # Data Stream Reloading / Connecting Spinner Overlay
            loading_overlay if is_loading else ft.Container(),
            
            # HUD Overlay Layer (Toggleable)
            hud_overlay_layer,

            # Top Camera Label Badge
            ft.Container(
                alignment=ft.Alignment(-0.96, -0.92),
                content=ft.Row([
                    ft.Container(
                        padding=ft.Padding(6, 3, 6, 3),
                        bgcolor=ft.Colors.with_opacity(0.85, ft.Colors.BLACK),
                        border_radius=4,
                        border=ft.Border.all(1, ft.Colors.CYAN_900),
                        content=ft.Row([
                            ft.Container(width=6, height=6, border_radius=3, bgcolor=ft.Colors.GREY_500 if is_loading else ft.Colors.GREEN_400),
                            ft.Text(cam_name, size=10, color=ft.Colors.WHITE, weight=ft.FontWeight.BOLD)
                        ], spacing=4)
                    )
                ])
            ),

            # Focus / Enlarge Icon Button
            ft.Container(
                alignment=ft.Alignment(0.96, -0.92),
                content=ft.IconButton(
                    icon=ft.Icons.ASPECT_RATIO_ROUNDED if not is_focused else ft.Icons.GRID_VIEW_ROUNDED,
                    icon_color=ft.Colors.CYAN_400,
                    icon_size=18,
                    tooltip="Focus Single Feed" if not is_focused else "Back to 4-View Grid Matrix",
                    on_click=lambda _: on_focus() if on_focus else None
                )
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
        {"id": 1, "name": "Default PC Webcam", "device_type": "webcam", "source": "0"},
        {"id": 2, "name": "Wireless CCTV - Sector 7G", "device_type": "rtsp_wireless", "source": "rtsp://192.168.1.100:554/stream1"},
        {"id": 3, "name": "Wired CCTV - Main Gate", "device_type": "rtsp_wired", "source": "rtsp://192.168.1.101:554/stream1"},
        {"id": 4, "name": "Perimeter Guard Post", "device_type": "rtsp_wired", "source": "rtsp://192.168.1.102:554/stream1"},
    ]

    # View Mode State: "quad" (4-View 2x2 Grid) vs "single" (Focus 1 Camera)
    view_mode, set_view_mode = ft.use_state("quad")
    focused_cam, set_focused_cam = ft.use_state(safe_cameras[0])
    
    # 4-View Matrix Pagination State
    page_index, set_page_index = ft.use_state(0)
    cams_per_page = 4
    total_pages = max(1, math.ceil(len(safe_cameras) / cams_per_page))

    # HUD Overlay Toggle State (ON/OFF)
    hud_overlay_active, set_hud_overlay_active = ft.use_state(True)
    
    is_recording, set_is_recording = ft.use_state(True)
    alert_acknowledged, set_alert_acknowledged = ft.use_state(False)
    sms_relay_active, set_sms_relay_active = ft.use_state(True)

    # Recipient Input State
    new_name_ref = ft.use_ref()
    new_phone_ref = ft.use_ref()
    
    recipients, set_recipients = ft.use_state([
        {"id": 1, "name": "Maj. Arnold Miller", "phone": "+1 (555) 091-2331", "role": "DIRECTOR"},
        {"id": 2, "name": "Sarah Chen", "phone": "+1 (555) 091-4456", "role": "FIELD LEAD"}
    ])

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

    def handle_remove_recipient(rec_id: int):
        set_recipients([r for r in recipients if r["id"] != rec_id])

    def handle_add_recipient(e):
        name = new_name_ref.current.value.strip() if (new_name_ref.current and new_name_ref.current.value) else ""
        phone = new_phone_ref.current.value.strip() if (new_phone_ref.current and new_phone_ref.current.value) else ""
        if name:
            new_item = {
                "id": len(recipients) + 1,
                "name": name,
                "phone": phone or "+1 (555) 000-0000",
                "role": "AGENT"
            }
            set_recipients(recipients + [new_item])

    def handle_focus_camera(cam: dict):
        set_focused_cam(cam)
        set_view_mode("single")

    # Dynamic Layout Responsive Heights
    single_view_height = 420 if page_width > 1100 else 320 if page_width > 700 else 220
    grid_tile_height = 210 if page_width > 1100 else 180 if page_width > 700 else 160

    # Slice Cameras for Current Page (4 Cameras per Page)
    start_idx = page_index * cams_per_page
    end_idx = min(len(safe_cameras), start_idx + cams_per_page)
    current_page_cams = safe_cameras[start_idx:end_idx]

    # 1. Main Live Video Feed Container (4-View Matrix vs Single Focus View)
    if view_mode == "single":
        video_display_area = SingleCameraTile(
            cam_info=focused_cam,
            height=single_view_height,
            on_focus=lambda: set_view_mode("quad"),
            is_focused=True,
            hud_enabled=hud_overlay_active
        )
    else:
        # 4-View Grid Matrix (2x2 Layout per Page)
        grid_tiles = []
        for c in current_page_cams:
            grid_tiles.append(
                ft.Container(
                    key=f"grid_tile_{c['id']}_{page_index}_{c['source']}",
                    col={"xs": 12, "md": 6},
                    content=SingleCameraTile(
                        cam_info=c,
                        height=grid_tile_height,
                        on_focus=lambda target_cam=c: handle_focus_camera(target_cam),
                        is_focused=False,
                        hud_enabled=hud_overlay_active
                    )
                )
            )
        video_display_area = ft.ResponsiveRow(controls=grid_tiles, spacing=10)

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
                    controls=[
                        ft.Column([
                            ft.Row([
                                ft.Container(width=6, height=14, bgcolor=ft.Colors.CYAN_400, border_radius=3),
                                ft.Text("MULTI-CAMERA SURVEILLANCE MATRIX", size=10, color=ft.Colors.CYAN_400, weight=ft.FontWeight.BOLD,),
                            ], spacing=6),
                            ft.Text("4-VIEW QUAD MATRIX" if view_mode == "quad" else f"SINGLE VIEW - {focused_cam['name'].upper()}", size=16, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                        ], spacing=2),
                        
                        # Top Action Toolbar (HUD Overlay Toggle & View Mode Matrix Selector)
                        ft.Row([
                            # HUD Overlay ON/OFF Showoff Button
                            ft.ElevatedButton(
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
                                        on_click=lambda _: set_view_mode("quad")
                                    ),
                                    ft.IconButton(
                                        icon=ft.Icons.ASPECT_RATIO_ROUNDED,
                                        icon_size=18,
                                        icon_color=ft.Colors.CYAN_400 if view_mode == "single" else ft.Colors.GREY_500,
                                        tooltip="Single Camera Focused View",
                                        on_click=lambda _: set_view_mode("single")
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
                            )
                        ], spacing=8)
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
                                ft.Text("MAP VIEW: LIGHT NODE", size=10, color=ft.Colors.WHITE54)
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

                ft.Text("AUTHORIZED RECIPIENTS", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE),

                ft.Column(
                    spacing=6,
                    controls=[
                        ft.Container(
                            key=f"rec_{r['id']}",
                            bgcolor=ft.Colors.SURFACE_CONTAINER,
                            border_radius=8,
                            padding=8,
                            content=ft.Row([
                                ft.CircleAvatar(content=ft.Text(r["name"][:2].upper(), size=10), radius=14, bgcolor=ft.Colors.BLUE_900),
                                ft.Column([
                                    ft.Text(r["name"], size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                                    ft.Text(r["phone"], size=11, color=ft.Colors.ON_SURFACE_VARIANT)
                                ], spacing=1, expand=True),
                                ft.Container(
                                    padding=ft.Padding(6, 2, 6, 2),
                                    bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
                                    border_radius=4,
                                    content=ft.Text(r["role"], size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE)
                                ),
                                ft.IconButton(
                                    icon=ft.Icons.DELETE_OUTLINED,
                                    icon_size=16,
                                    on_click=lambda e, rid=r["id"]: handle_remove_recipient(rid)
                                )
                            ])
                        ) for r in recipients
                    ]
                ),

                ft.Row([
                    ft.TextField(
                        ref=new_name_ref,
                        hint_text="NEW RECIPIENT ID...",
                        text_size=11,
                        dense=True,
                        expand=True,
                        border_radius=8
                    ),
                    ft.ElevatedButton(
                        "+ ADD",
                        icon=ft.Icons.PERSON_ADD_ALT_1_ROUNDED,
                        style=ft.ButtonStyle(bgcolor=ft.Colors.BLUE_600, color=ft.Colors.WHITE),
                        on_click=handle_add_recipient
                    )
                ], spacing=8)
            ]
        )
    )

    # Emergency Action Button (Initiate Lockdown)
    lockdown_button = ft.ElevatedButton(
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
                actions=[ft.TextButton("DISMISS", on_click=lambda e: page.close_dialog())]
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
            scroll=ft.ScrollMode.AUTO,
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
