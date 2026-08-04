# src/views/components/userProfileDialog.py

import flet as ft
from typing import Dict, Any, Callable, Optional

def show_user_profile_dialog(page: ft.Page, target: Dict[str, Any], telegram_service: Any):
    """
    Renders a modern, interactive Telegram User Profile & Recipient Details Modal Dialog.
    """
    if not page:
        return

    ttype = str(target.get("target_type") or "user").lower()
    tname = str(target.get("target_name") or "Unknown Target")
    cid = str(target.get("chat_id") or "")
    role = str(target.get("role") or "OPERATIVE").upper()
    phone = str(target.get("phone") or "+1 (555) 091-0000")
    note = str(target.get("note") or "No additional description available.")
    
    username = target.get("username")
    if not username:
        username = cid if cid.startswith("@") else f"@{tname.lower().replace(' ', '_')}"

    badge_icon = ft.Icons.ACCOUNT_CIRCLE_ROUNDED if ttype == "user" else ft.Icons.CAMPAIGN_ROUNDED if ttype == "channel" else ft.Icons.GROUPS_ROUNDED
    badge_color = ft.Colors.CYAN_400

    def send_test_alert(e):
        success, msg = telegram_service.send_test_message(chat_id=cid)
        try:
            page.show_dialog(
                ft.SnackBar(
                    content=ft.Row([
                        ft.Icon(ft.Icons.CHECK_CIRCLE_ROUNDED if success else ft.Icons.ERROR_ROUNDED, color=ft.Colors.WHITE, size=18),
                        ft.Text(msg, color=ft.Colors.WHITE, weight=ft.FontWeight.BOLD, size=11)
                    ], spacing=8),
                    bgcolor=ft.Colors.GREEN_800 if success else ft.Colors.RED_900,
                    duration=4000
                )
            )
        except Exception:
            pass

    dialog_ref = [None]

    dialog = ft.AlertDialog(
        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGHEST,
        shape=ft.RoundedRectangleBorder(radius=16),
        title=ft.Row([
            ft.Icon(badge_icon, color=badge_color, size=24),
            ft.Column([
                ft.Text(tname, size=16, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                ft.Text(f"{ttype.upper()} RECIPIENT PROFILE • {role}", size=10, color=ft.Colors.CYAN_400, weight=ft.FontWeight.BOLD),
            ], spacing=1, expand=True),
        ]),
        content=ft.Container(
            width=440,
            padding=6,
            content=ft.Column([
                # Avatar Card with Verified Badge
                ft.Container(
                    bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
                    border_radius=12,
                    padding=14,
                    border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
                    content=ft.Row([
                        ft.Stack([
                            ft.CircleAvatar(
                                content=ft.Text(tname[:2].upper(), size=16, weight=ft.FontWeight.BOLD, color=ft.Colors.WHITE),
                                radius=28,
                                bgcolor=ft.Colors.CYAN_700
                            ),
                            ft.Container(
                                width=12, height=12, border_radius=6, bgcolor=ft.Colors.GREEN_500,
                                alignment=ft.Alignment(1, 1)
                            )
                        ]),
                        ft.Column([
                            ft.Row([
                                ft.Text(username, size=13, weight=ft.FontWeight.BOLD, color=ft.Colors.CYAN_300),
                                ft.Container(
                                    content=ft.Text("VERIFIED TARGET", size=8, weight=ft.FontWeight.BOLD, color=ft.Colors.GREEN_100),
                                    bgcolor=ft.Colors.GREEN_800,
                                    padding=ft.Padding(5, 1, 5, 1),
                                    border_radius=4
                                )
                            ], spacing=6),
                            ft.Text(f"Target Chat ID: {cid}", size=11, color=ft.Colors.ON_SURFACE, weight=ft.FontWeight.BOLD),
                            ft.Text(f"Contact Phone: {phone}", size=10, color=ft.Colors.ON_SURFACE_VARIANT),
                        ], spacing=3, expand=True)
                    ], spacing=12)
                ),

                ft.Container(height=4),
                ft.Text("SECURITY TARGET DETAILS", size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.CYAN_400),
                
                # Profile Details Grid
                ft.Container(
                    bgcolor=ft.Colors.SURFACE_CONTAINER,
                    border_radius=10,
                    padding=12,
                    border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
                    content=ft.Column([
                        ft.Row([
                            ft.Icon(ft.Icons.BADGE_ROUNDED, size=14, color=ft.Colors.CYAN_400),
                            ft.Text("ASSIGNED ROLE:", size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE_VARIANT),
                            ft.Text(role, size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE)
                        ], spacing=6),
                        ft.Row([
                            ft.Icon(ft.Icons.TELEGRAM_ROUNDED, size=14, color=ft.Colors.CYAN_400),
                            ft.Text("TELEGRAM DESTINATION:", size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE_VARIANT),
                            ft.Text(cid, size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE)
                        ], spacing=6),
                        ft.Row([
                            ft.Icon(ft.Icons.DESCRIPTION_ROUNDED, size=14, color=ft.Colors.CYAN_400),
                            ft.Text("NOTE / MISSION:", size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE_VARIANT),
                            ft.Text(note, size=10, color=ft.Colors.ON_SURFACE)
                        ], spacing=6),
                    ], spacing=8)
                ),
            ], spacing=6, tight=True)
        ),
        actions=[
            ft.Button(
                "SEND DIRECT TEST ALERT",
                icon=ft.Icons.SEND_ROUNDED,
                style=ft.ButtonStyle(bgcolor=ft.Colors.CYAN_700, color=ft.Colors.WHITE),
                on_click=send_test_alert
            ),
            ft.TextButton("CLOSE", on_click=lambda _: page.pop_dialog())
        ]
    )
    dialog_ref[0] = dialog
    page.show_dialog(dialog)

def show_edit_target_dialog(page: ft.Page, target: Dict[str, Any], telegram_service: Any, on_success: Optional[Callable] = None):
    """
    Renders an interactive Edit Target Profile Dialog to edit Target Name, Type, Chat ID, Role, Phone, Note.
    """
    if not page:
        return

    tid = target.get("id")
    name_field = ft.TextField(value=target.get("target_name", ""), label="Target Name / Label", dense=True, text_size=12)
    cid_field = ft.TextField(value=target.get("chat_id", ""), label="Chat ID / Username", dense=True, text_size=12)
    type_drop = ft.Dropdown(
        value=target.get("target_type", "user").lower(),
        label="Destination Type",
        dense=True,
        text_size=12,
        options=[
            ft.dropdown.Option("user", "User Profile"),
            ft.dropdown.Option("channel", "Public/Private Channel"),
            ft.dropdown.Option("group", "Tactical Group Chat"),
        ]
    )
    role_drop = ft.Dropdown(
        value=target.get("role", "OPERATIVE").upper(),
        label="Assigned Role",
        dense=True,
        text_size=12,
        options=[
            ft.dropdown.Option("DIRECTOR", "Director / Command"),
            ft.dropdown.Option("FIELD LEAD", "Field Lead / Inspector"),
            ft.dropdown.Option("TACTICAL UNIT", "Tactical Unit / Response"),
            ft.dropdown.Option("BROADCAST", "Broadcast / Alert Log"),
            ft.dropdown.Option("OPERATIVE", "Security Operative"),
        ]
    )
    phone_field = ft.TextField(value=target.get("phone", ""), label="Contact Phone Number", dense=True, text_size=12)
    note_field = ft.TextField(value=target.get("note", ""), label="Operational Note / Zone", multiline=True, min_lines=2, max_lines=3, dense=True, text_size=12)

    dialog_ref = [None]

    def handle_save_edit(e):
        success, msg = telegram_service.update_target(
            target_id=tid,
            target_name=name_field.value,
            target_type=type_drop.value,
            chat_id=cid_field.value,
            note=note_field.value,
            role=role_drop.value,
            phone=phone_field.value,
            username=cid_field.value if cid_field.value.startswith("@") else ""
        )
        try:
            if dialog_ref[0]:
                page.pop_dialog()
            page.show_dialog(
                ft.SnackBar(
                    content=ft.Row([
                        ft.Icon(ft.Icons.CHECK_CIRCLE_ROUNDED if success else ft.Icons.ERROR_ROUNDED, color=ft.Colors.WHITE, size=18),
                        ft.Text(msg, color=ft.Colors.WHITE, weight=ft.FontWeight.BOLD, size=11)
                    ], spacing=8),
                    bgcolor=ft.Colors.GREEN_800 if success else ft.Colors.RED_900,
                    duration=3000
                )
            )
            if success and on_success:
                on_success()
        except Exception:
            pass

    dialog = ft.AlertDialog(
        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGHEST,
        shape=ft.RoundedRectangleBorder(radius=14),
        title=ft.Row([
            ft.Icon(ft.Icons.EDIT_NOTE_ROUNDED, color=ft.Colors.CYAN_400, size=22),
            ft.Text("EDIT TARGET PROFILE", size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE)
        ], spacing=8),
        content=ft.Container(
            width=420,
            padding=6,
            content=ft.Column([
                name_field,
                type_drop,
                cid_field,
                role_drop,
                phone_field,
                note_field
            ], spacing=10, tight=True)
        ),
        actions=[
            ft.Button(
                "SAVE TARGET CHANGES",
                icon=ft.Icons.SAVE_ROUNDED,
                style=ft.ButtonStyle(bgcolor=ft.Colors.CYAN_700, color=ft.Colors.WHITE),
                on_click=handle_save_edit
            ),
            ft.TextButton("CANCEL", on_click=lambda _: page.pop_dialog())
        ]
    )
    dialog_ref[0] = dialog
    page.show_dialog(dialog)
