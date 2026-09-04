"""
src/views/components/target_face_manager.py
Modern, Production-grade UI Component for Target Face Database Management in Settings View.
Built with clean Flet controls, dark mode glassmorphism accents, non-card list rows, and live photo upload/webcam capture.
"""

import os
import flet as ft
from typing import Callable, Optional, Dict, List
from config.fonts import AppFonts
from services.target_face_service import TargetFaceService

ROLE_COLORS = {
    "VIP": ft.Colors.AMBER_400,
    "EMPLOYEE": ft.Colors.CYAN_400,
    "SECURITY": ft.Colors.BLUE_400,
    "BLACKLIST": ft.Colors.RED_400,
    "VISITOR": ft.Colors.PURPLE_300
}

ROLE_BG_COLORS = {
    "VIP": ft.Colors.AMBER_900,
    "EMPLOYEE": ft.Colors.CYAN_900,
    "SECURITY": ft.Colors.BLUE_900,
    "BLACKLIST": ft.Colors.RED_900,
    "VISITOR": ft.Colors.PURPLE_900
}

@ft.component
def TargetFaceManager():
    page = ft.context.page
    tf_service = TargetFaceService.get_instance()

    search_query, set_search_query = ft.use_state("")
    role_filter, set_role_filter = ft.use_state("ALL")
    faces_list, set_faces_list = ft.use_state(lambda: tf_service.get_target_faces())
    
    # Refresh list helper
    def refresh_faces(query: str = None, r_filter: str = None):
        q = query if query is not None else search_query
        rf = r_filter if r_filter is not None else role_filter
        data = tf_service.get_target_faces(search_query=q, role_filter=rf)
        set_faces_list(data)

    # Search & Filter handlers
    def handle_search_change(e):
        val = e.control.value
        set_search_query(val)
        refresh_faces(query=val)

    def handle_role_select(selected_role: str):
        set_role_filter(selected_role)
        refresh_faces(r_filter=selected_role)

    def handle_delete_face(face_id: int, face_name: str):
        def confirm_delete(evt):
            page.pop_dialog()
            success, msg = tf_service.delete_target_face(face_id)
            refresh_faces()
            page.show_dialog(
                ft.SnackBar(
                    content=ft.Row([
                        ft.Icon(ft.Icons.CHECK_CIRCLE_ROUNDED if success else ft.Icons.ERROR_ROUNDED, color=ft.Colors.WHITE, size=18),
                        ft.Text(msg, color=ft.Colors.WHITE, weight=ft.FontWeight.BOLD, size=12)
                    ], spacing=8),
                    bgcolor=ft.Colors.GREEN_800 if success else ft.Colors.RED_900,
                    duration=3000
                )
            )

        dialog = ft.AlertDialog(
            open=True,
            title=ft.Row([
                ft.Icon(ft.Icons.WARNING_AMBER_ROUNDED, color=ft.Colors.RED_400, size=24),
                ft.Text("Confirm Target Face Deletion", weight=ft.FontWeight.BOLD, size=15)
            ], spacing=8),
            content=ft.Text(f"Are you sure you want to remove target face '{face_name}' from the security database?", font_family=AppFonts.MYANMAR, size=13),
            actions=[
                ft.TextButton("CANCEL", on_click=lambda _: page.pop_dialog()),
                ft.Button(
                    "DELETE",
                    style=ft.ButtonStyle(bgcolor=ft.Colors.RED_700, color=ft.Colors.WHITE),
                    on_click=confirm_delete
                )
            ]
        )
        page.show_dialog(dialog)

    # Open Add Target Face Modal Dialog
    def open_add_face_dialog(e):
        name_input = ft.TextField(label="Full Name / Identifier", dense=True, text_size=12, expand=True)
        role_drop = ft.Dropdown(
            value="VIP",
            label="Security Role Tag",
            dense=True,
            text_size=12,
            options=[
                ft.dropdown.Option("VIP", "⭐ V.I.P Person"),
                ft.dropdown.Option("EMPLOYEE", "💼 Employee / Staff"),
                ft.dropdown.Option("SECURITY", "🛡️ Security Operative"),
                ft.dropdown.Option("BLACKLIST", "⚠️ Blacklist / Threat Alert"),
                ft.dropdown.Option("VISITOR", "👤 Visitor")
            ],
            expand=True
        )
        dept_input = ft.TextField(label="Department / Zone", value="General", dense=True, text_size=12, expand=True)
        note_input = ft.TextField(label="Notes / Security Briefing", dense=True, multiline=True, min_lines=2, max_lines=3, text_size=12)
        
        selected_file_path = [None]
        preview_container = ft.Container(
            width=112,
            height=112,
            border_radius=56,
            bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
            alignment=ft.Alignment(0, 0),
            content=ft.Icon(ft.Icons.ADD_A_PHOTO_ROUNDED, color=ft.Colors.CYAN_400, size=32),
            border=ft.Border.all(2, ft.Colors.CYAN_400)
        )

        file_picker = ft.FilePicker()

        async def handle_pick_photo(e):
            res = await file_picker.pick_files(
                dialog_title="Select Target Face Photo",
                file_type=ft.FilePickerFileType.IMAGE
            )
            if res and len(res) > 0:
                filepath = res[0].path
                selected_file_path[0] = filepath
                preview_container.content = ft.Image(
                    src=filepath,
                    width=112,
                    height=112,
                    fit=ft.BoxFit.COVER,
                    border_radius=56
                )
                preview_container.update()


        def save_target_face(evt):
            name = name_input.value.strip() if name_input.value else ""
            if not name:
                page.show_dialog(
                    ft.SnackBar(content=ft.Text("Target Name cannot be empty!", color=ft.Colors.WHITE), bgcolor=ft.Colors.RED_900)
                )
                return

            if not selected_file_path[0]:
                page.show_dialog(
                    ft.SnackBar(content=ft.Text("Please select or upload a face photo!", color=ft.Colors.WHITE), bgcolor=ft.Colors.RED_900)
                )
                return

            page.pop_dialog()
            success, msg, _ = tf_service.add_target_face(
                name=name,
                role=role_drop.value,
                department=dept_input.value or "General",
                image_source=selected_file_path[0],
                note=note_input.value or ""
            )

            refresh_faces()
            page.show_dialog(
                ft.SnackBar(
                    content=ft.Row([
                        ft.Icon(ft.Icons.CHECK_CIRCLE_ROUNDED if success else ft.Icons.ERROR_ROUNDED, color=ft.Colors.WHITE, size=18),
                        ft.Text(msg, color=ft.Colors.WHITE, weight=ft.FontWeight.BOLD, size=12)
                    ], spacing=8),
                    bgcolor=ft.Colors.GREEN_800 if success else ft.Colors.RED_900,
                    duration=3000
                )
            )

        dialog = ft.AlertDialog(
            open=True,
            shape=ft.RoundedRectangleBorder(radius=16),
            title=ft.Row([
                ft.Icon(ft.Icons.PERSON_ADD_ALT_1_ROUNDED, color=ft.Colors.CYAN_400, size=24),
                ft.Text("Register Target Face Profile", weight=ft.FontWeight.BOLD, size=15)
            ], spacing=8),
            content=ft.Container(
                width=480,
                padding=10,
                content=ft.Column([
                    ft.Row([
                        preview_container,
                        ft.Column([
                            ft.Text("Target Photo Upload", weight=ft.FontWeight.BOLD, size=12, color=ft.Colors.ON_SURFACE),
                            ft.Text("Upload a clear frontal face image for ArcFace 2.5D embedding.", size=10, color=ft.Colors.ON_SURFACE_VARIANT),
                            ft.Button(
                                "CHOOSE FACE PHOTO",
                                icon=ft.Icons.UPLOAD_FILE_ROUNDED,
                                style=ft.ButtonStyle(bgcolor=ft.Colors.CYAN_700, color=ft.Colors.WHITE),
                                on_click=handle_pick_photo
                            )
                        ], spacing=6, expand=True)
                    ], spacing=16, alignment=ft.MainAxisAlignment.START),
                    ft.Divider(color=ft.Colors.OUTLINE_VARIANT, height=1),

                    ft.Row([name_input, role_drop], spacing=10),
                    dept_input,
                    note_input,
                ], spacing=12, tight=True)
            ),
            actions=[
                ft.TextButton("CANCEL", on_click=lambda _: page.pop_dialog()),
                ft.Button(
                    "SAVE TARGET FACE",
                    icon=ft.Icons.SAVE_ROUNDED,
                    style=ft.ButtonStyle(bgcolor=ft.Colors.GREEN_700, color=ft.Colors.WHITE),
                    on_click=save_target_face
                )
            ]
        )
        page.show_dialog(dialog)

    # ── Non-Card Modern List Item Generator ───────────────────────────────────
    def build_face_row(item: dict):
        role = item["role"].upper()
        role_color = ROLE_COLORS.get(role, ft.Colors.CYAN_400)
        role_bg = ROLE_BG_COLORS.get(role, ft.Colors.CYAN_900)
        has_emb = item.get("has_embedding", False)

        img_path = item.get("image_path")
        avatar_content = ft.CircleAvatar(
            radius=22,
            bgcolor=ft.Colors.SURFACE_CONTAINER_HIGHEST,
            content=ft.Icon(ft.Icons.PERSON_ROUNDED, color=ft.Colors.CYAN_400, size=20)
        )
        if img_path and os.path.exists(img_path):
            avatar_content = ft.Image(
                src=img_path,
                width=44,
                height=44,
                border_radius=22,
                fit=ft.BoxFit.COVER
            )

        return ft.Container(
            bgcolor=ft.Colors.SURFACE_CONTAINER,
            padding=ft.Padding(14, 10, 14, 10),
            border_radius=8,
            border=ft.Border.only(
                left=ft.BorderSide(4, role_color),
                top=ft.BorderSide(1, ft.Colors.OUTLINE_VARIANT),
                right=ft.BorderSide(1, ft.Colors.OUTLINE_VARIANT),
                bottom=ft.BorderSide(1, ft.Colors.OUTLINE_VARIANT)
            ),
            content=ft.Row([
                # Avatar with Status Dot
                ft.Stack([
                    avatar_content,
                    ft.Container(
                        width=10, height=10, border_radius=5,
                        bgcolor=ft.Colors.GREEN_400 if has_emb else ft.Colors.AMBER_400,
                        alignment=ft.Alignment(1, 1)
                    )
                ]),
                # User Info Column
                ft.Column([
                    ft.Row([
                        ft.Text(item["name"], weight=ft.FontWeight.BOLD, size=13, color=ft.Colors.ON_SURFACE),
                        # Role Badge Chip (Pill Shape, Non-Card)
                        ft.Container(
                            content=ft.Text(role, size=9, weight=ft.FontWeight.BOLD, color=role_color),
                            bgcolor=role_bg,
                            padding=ft.Padding(8, 2, 8, 2),
                            border_radius=12
                        ),
                        # Embedding Readiness Badge
                        ft.Container(
                            content=ft.Text("2.5D READY" if has_emb else "NO EMBEDDING", size=8, weight=ft.FontWeight.BOLD, color=ft.Colors.WHITE),
                            bgcolor=ft.Colors.GREEN_800 if has_emb else ft.Colors.AMBER_900,
                            padding=ft.Padding(6, 1, 6, 1),
                            border_radius=4
                        )
                    ], spacing=8),
                    ft.Row([
                        ft.Icon(ft.Icons.BUSINESS_ROUNDED, size=12, color=ft.Colors.OUTLINE),
                        ft.Text(f"Dept: {item['department']}", size=11, color=ft.Colors.ON_SURFACE_VARIANT),
                        ft.Text("•", size=11, color=ft.Colors.OUTLINE),
                        ft.Icon(ft.Icons.ACCESS_TIME_ROUNDED, size=12, color=ft.Colors.OUTLINE),
                        ft.Text(f"Added: {item['created_at']}", size=11, color=ft.Colors.ON_SURFACE_VARIANT),
                    ], spacing=6)
                ], spacing=2, expand=True),
                # Action Buttons
                ft.IconButton(
                    icon=ft.Icons.DELETE_OUTLINE_ROUNDED,
                    icon_color=ft.Colors.RED_400,
                    tooltip="Delete Target Face",
                    on_click=lambda _: handle_delete_face(item["id"], item["name"])
                )
            ], spacing=14, alignment=ft.MainAxisAlignment.SPACE_BETWEEN)
        )

    # Filter Chip Generator (Non-card, modern tab pill design)
    def build_filter_chip(role_key: str, label: str):
        is_selected = role_filter == role_key
        return ft.Container(
            content=ft.Text(label, size=11, weight=ft.FontWeight.BOLD if is_selected else ft.FontWeight.NORMAL,
                            color=ft.Colors.WHITE if is_selected else ft.Colors.ON_SURFACE_VARIANT),
            bgcolor=ft.Colors.CYAN_700 if is_selected else ft.Colors.SURFACE_CONTAINER_HIGH,
            padding=ft.Padding(12, 6, 12, 6),
            border_radius=16,
            on_click=lambda _: handle_role_select(role_key),
            border=ft.Border.all(1, ft.Colors.CYAN_500 if is_selected else ft.Colors.OUTLINE_VARIANT)
        )

    # List Control Controls
    list_controls = [build_face_row(item) for item in faces_list] if faces_list else [
        ft.Container(
            padding=30,
            alignment=ft.Alignment(0, 0),
            content=ft.Column([
                ft.Icon(ft.Icons.FACE, size=48, color=ft.Colors.OUTLINE),
                ft.Text("No Target Faces Registered", weight=ft.FontWeight.BOLD, size=14, color=ft.Colors.ON_SURFACE_VARIANT),
                ft.Text("Click 'REGISTER TARGET FACE' above to add VIPs, Employees, or Threat Profiles.", size=11, color=ft.Colors.OUTLINE)
            ], horizontal_alignment=ft.CrossAxisAlignment.CENTER, spacing=6)
        )
    ]

    return ft.Container(
        padding=16,
        bgcolor=ft.Colors.SURFACE_CONTAINER_LOW,
        border_radius=12,
        border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
        content=ft.Column([
            # Section Header Row
            ft.Row([
                ft.Row([
                    ft.Icon(ft.Icons.FACE_UNLOCK_ROUNDED, color=ft.Colors.CYAN_400, size=24),
                    ft.Column([
                        ft.Text("Target Face Database & AI Security", size=15, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                        ft.Text("Manage known target faces & 2.5D embeddings for real-time video surveillance", size=11, color=ft.Colors.ON_SURFACE_VARIANT)
                    ], spacing=1)
                ], spacing=10),
                ft.Button(
                    "REGISTER TARGET FACE",
                    icon=ft.Icons.PERSON_ADD_ALT_1_ROUNDED,
                    style=ft.ButtonStyle(bgcolor=ft.Colors.CYAN_700, color=ft.Colors.WHITE),
                    on_click=open_add_face_dialog
                )
            ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN),
            ft.Divider(color=ft.Colors.OUTLINE_VARIANT, height=1),
            
            # Toolbar Row: Search + Role Filter Chips
            ft.Row([
                ft.TextField(
                    hint_text="Search target face by name or department...",
                    prefix_icon=ft.Icons.SEARCH_ROUNDED,
                    dense=True,
                    text_size=12,
                    width=300,
                    on_change=handle_search_change
                ),
                ft.Row([
                    build_filter_chip("ALL", "All Targets"),
                    build_filter_chip("VIP", "⭐ VIP"),
                    build_filter_chip("EMPLOYEE", "💼 Employee"),
                    build_filter_chip("SECURITY", "🛡️ Security"),
                    build_filter_chip("BLACKLIST", "⚠️ Blacklist"),
                ], spacing=6, scroll=ft.ScrollMode.HIDDEN, expand=True)
            ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN, spacing=14),

            # Non-Card Table List Column
            ft.Column(controls=list_controls, spacing=8)
        ], spacing=14)
    )
