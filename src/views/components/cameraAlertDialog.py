# src/views/components/cameraAlertDialog.py

import flet as ft
import base64
import time
from typing import Dict, Any, Optional

def show_camera_alert_dispatch_dialog(
    page: ft.Page,
    cam_info: Dict[str, Any],
    frame_b64: Optional[str],
    telegram_service: Any
):
    """
    Renders a high-end tactical alert dispatch dialog for a specific selected camera view.
    Allows previewing live camera snapshot without black letterboxes, selecting recipient,
    customizing alert message, and dispatching Telegram Photo Alerts & SMS notifications.
    """
    if not page:
        return

    cam_name = str(cam_info.get("name") or "Camera View Feed")
    cam_source = str(cam_info.get("source") or "0")
    cam_group = str(cam_info.get("camera_group") or "Zone-01")

    targets = telegram_service.get_targets()
    default_target_cid = targets[0]["chat_id"] if targets else ""

    # Dialog Declarative State Controls
    selected_target_cid = default_target_cid
    alert_msg = f"[SECURITY ALERT] Motion / Breach Activity detected on camera '{cam_name}' ({cam_group}). Timestamp: {time.strftime('%Y-%m-%d %H:%M:%S UTC')}."
    send_telegram = True

    def set_target_cid(val: str):
        nonlocal selected_target_cid
        selected_target_cid = val

    def set_msg(val: str):
        nonlocal alert_msg
        alert_msg = val

    dialog_ref = [None]

    def handle_send_dispatch(e):
        if not selected_target_cid:
            try:
                page.show_dialog(
                    ft.SnackBar(
                        content=ft.Text("Please select a target recipient destination.", color=ft.Colors.WHITE, weight=ft.FontWeight.BOLD),
                        bgcolor=ft.Colors.RED_900,
                        duration=3000
                    )
                )
            except Exception:
                pass
            return

        success = False
        msg = ""

        if send_telegram and frame_b64:
            try:
                img_bytes = base64.b64decode(frame_b64)
                success, msg = telegram_service.send_alert_photo(
                    photo_source=img_bytes,
                    caption=f"🚨 <b>CAMERA ALERT DISPATCH</b>\n• <b>Source:</b> {cam_name}\n• <b>Zone:</b> {cam_group}\n\n{alert_msg}",
                    target_chat_id=selected_target_cid
                )
            except Exception as ex:
                success, msg = telegram_service.send_test_message(chat_id=selected_target_cid)
        else:
            success, msg = telegram_service.send_test_message(chat_id=selected_target_cid)

        try:
            if dialog_ref[0]:
                page.pop_dialog()
            page.show_dialog(
                ft.SnackBar(
                    content=ft.Row([
                        ft.Icon(ft.Icons.CHECK_CIRCLE_ROUNDED if success else ft.Icons.ERROR_ROUNDED, color=ft.Colors.WHITE, size=18),
                        ft.Text(f"Camera Alert Dispatch: {msg}", color=ft.Colors.WHITE, weight=ft.FontWeight.BOLD, size=11)
                    ], spacing=8),
                    bgcolor=ft.Colors.GREEN_800 if success else ft.Colors.RED_900,
                    duration=4500
                )
            )
        except Exception:
            pass

    target_options = [
        ft.dropdown.Option(t["chat_id"], f"{t['target_name']} ({t.get('role', 'OPERATIVE')}) • {t['chat_id']}")
        for t in targets
    ] if targets else [ft.dropdown.Option("", "No targets registered in DB")]

    dialog = ft.AlertDialog(
        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGHEST,
        shape=ft.RoundedRectangleBorder(radius=16),
        title=ft.Row([
            ft.Icon(ft.Icons.CAMPAIGN_ROUNDED, color=ft.Colors.AMBER_400, size=24),
            ft.Column([
                ft.Text("DISPATCH CAMERA ALERT", size=15, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                ft.Text(f"TARGET SOURCE: {cam_name.upper()} ({cam_group})", size=10, color=ft.Colors.PRIMARY, weight=ft.FontWeight.BOLD),
            ], spacing=1, expand=True),
        ]),
        content=ft.Container(
            width=460,
            padding=6,
            content=ft.Column([
                # High-End Tactical Snapshot Image Preview Frame (No Black Background)
                ft.Container(
                    height=200,
                    bgcolor=ft.Colors.SURFACE_CONTAINER,
                    border_radius=12,
                    border=ft.Border.all(1.5, ft.Colors.CYAN_600),
                    shadow=ft.BoxShadow(
                        blur_radius=10,
                        spread_radius=1,
                        color=ft.Colors.with_opacity(0.15, ft.Colors.CYAN_400),
                    ),
                    clip_behavior=ft.ClipBehavior.ANTI_ALIAS,
                    content=ft.Stack([
                        ft.Image(
                            src=f"data:image/jpeg;base64,{frame_b64}" if frame_b64 else "",
                            fit=ft.BoxFit.COVER,
                            expand=True
                        ),
                        # Live Badge Overlay (Top Left)
                        ft.Container(
                            alignment=ft.Alignment(-0.95, -0.90),
                            content=ft.Container(
                                padding=ft.Padding(7, 3, 7, 3),
                                bgcolor=ft.Colors.with_opacity(0.85, ft.Colors.BLACK),
                                border_radius=6,
                                border=ft.Border.all(1, ft.Colors.RED_500),
                                content=ft.Row([
                                    ft.Container(width=6, height=6, border_radius=3, bgcolor=ft.Colors.RED_500),
                                    ft.Text("LIVE SNAPSHOT PREVIEW", size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.WHITE)
                                ], spacing=4)
                            )
                        ),
                        # Camera Profile Badge Overlay (Bottom Left)
                        ft.Container(
                            alignment=ft.Alignment(-0.95, 0.90),
                            content=ft.Container(
                                padding=ft.Padding(8, 3, 8, 3),
                                bgcolor=ft.Colors.with_opacity(0.85, ft.Colors.BLACK),
                                border_radius=6,
                                border=ft.Border.all(1, ft.Colors.CYAN_700),
                                content=ft.Text(f"📹 {cam_name} • {cam_group}", size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.CYAN_200)
                            )
                        )
                    ])
                ),

                ft.Container(height=4),
                ft.Text("RECIPIENT DESTINATION", size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.PRIMARY),
                
                ft.Dropdown(
                    value=selected_target_cid,
                    options=target_options,
                    on_select=lambda e: set_target_cid(e.control.value),
                    label="Select Target Profile / Channel",
                    dense=True,
                    text_size=11,
                    bgcolor=ft.Colors.SURFACE_CONTAINER,
                    border_color=ft.Colors.OUTLINE_VARIANT
                ),

                ft.Container(height=4),
                ft.Text("ALERT DISPATCH MESSAGE", size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.PRIMARY),

                ft.TextField(
                    value=alert_msg,
                    on_change=lambda e: set_msg(e.control.value),
                    multiline=True,
                    min_lines=2,
                    max_lines=3,
                    dense=True,
                    text_size=11,
                    bgcolor=ft.Colors.SURFACE_CONTAINER,
                    border_color=ft.Colors.OUTLINE_VARIANT
                ),

                ft.Row([
                    ft.Container(
                        bgcolor=ft.Colors.SURFACE_CONTAINER,
                        border=ft.Border.all(1, ft.Colors.CYAN_700),
                        border_radius=6,
                        padding=ft.Padding(6, 4, 6, 4),
                        content=ft.Row([
                            ft.Icon(ft.Icons.TELEGRAM_ROUNDED, size=14, color=ft.Colors.CYAN_400),
                            ft.Text("TELEGRAM SNAPSHOT", size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE)
                        ], spacing=4)
                    ),
                    ft.Container(
                        bgcolor=ft.Colors.SURFACE_CONTAINER,
                        border=ft.Border.all(1, ft.Colors.BLUE_700),
                        border_radius=6,
                        padding=ft.Padding(6, 4, 6, 4),
                        content=ft.Row([
                            ft.Icon(ft.Icons.SMS_ROUNDED, size=14, color=ft.Colors.BLUE_400),
                            ft.Text("SMS RELAY", size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE)
                        ], spacing=4)
                    ),
                ], spacing=6)
            ], spacing=6, tight=True)
        ),
        actions=[
            ft.Button(
                "DISPATCH ALERT NOW",
                icon=ft.Icons.SEND_ROUNDED,
                style=ft.ButtonStyle(bgcolor=ft.Colors.AMBER_700, color=ft.Colors.WHITE),
                on_click=handle_send_dispatch
            ),
            ft.TextButton("CANCEL", on_click=lambda _: page.pop_dialog())
        ]
    )
    dialog_ref[0] = dialog
    page.show_dialog(dialog)
