# src/views/settingsView.py
import flet as ft
from typing import Callable
from core.auth_context import use_user, use_auth
from services.auth_service import AuthService
from services.camera_service import CameraService
from views.components.model_selector import ModelSelector
from config.fonts import AppFonts

@ft.component
def EditCameraModal(cam_item: dict, on_close: Callable[[], None], on_saved: Callable[[], None]):
    """
    Pure Declarative UI Component for Editing Camera Channel Details.
    """
    page = ft.context.page
    camera_service = ft.use_memo(lambda: CameraService(), [])

    edit_name, set_edit_name = ft.use_state(cam_item["name"])
    edit_type, set_edit_type = ft.use_state(cam_item["device_type"])
    edit_source, set_edit_source = ft.use_state(cam_item["source"])

    def handle_save_camera_edit(e):
        name = edit_name.strip()
        source = edit_source.strip()
        if name and source:
            camera_service.update_camera(cam_item["id"], name, edit_type, source)
            on_saved()
            on_close()
            page.show_dialog(
                ft.SnackBar(
                    content=ft.Text(f"Camera '{name}' updated successfully!", font_family=AppFonts.MYANMAR),
                    bgcolor=ft.Colors.GREEN_900,
                    duration=3000
                )
            )
        else:
            page.show_dialog(
                ft.SnackBar(
                    content=ft.Text("Camera Name and Source URL cannot be empty!", font_family=AppFonts.MYANMAR),
                    bgcolor=ft.Colors.RED_900,
                    duration=3000
                )
            )

    return ft.AlertDialog(
        open=True,
        title=ft.Row([
            ft.Icon(ft.Icons.EDIT_ROUNDED, color=ft.Colors.CYAN_400),
            ft.Text("Edit Camera Setup", weight=ft.FontWeight.BOLD, size=15)
        ], spacing=8),
        content=ft.Container(
            width=450,
            padding=10,
            content=ft.Column(
                tight=True,
                spacing=12,
                controls=[
                    ft.TextField(
                        value=edit_name,
                        on_change=lambda e: set_edit_name(e.control.value),
                        label="Camera Name",
                        dense=True,
                        text_size=12
                    ),
                    ft.Dropdown(
                        value=edit_type,
                        on_select=lambda e: set_edit_type(e.control.value),
                        label="Type",
                        dense=True,
                        text_size=12,
                        options=[
                            ft.dropdown.Option("webcam", "PC Webcam"),
                            ft.dropdown.Option("rtsp_wireless", "Wireless CCTV (RTSP)"),
                            ft.dropdown.Option("rtsp_wired", "Wired CCTV (RTSP)"),
                        ]
                    ),
                    ft.TextField(
                        value=edit_source,
                        on_change=lambda e: set_edit_source(e.control.value),
                        label="Source (Index / RTSP URL)",
                        dense=True,
                        text_size=12
                    ),
                ]
            )
        ),
        actions=[
            ft.TextButton("CANCEL", on_click=lambda e: on_close()),
            ft.ElevatedButton(
                "SAVE CHANGES",
                icon=ft.Icons.SAVE_ROUNDED,
                style=ft.ButtonStyle(bgcolor=ft.Colors.CYAN_700, color=ft.Colors.WHITE),
                on_click=handle_save_camera_edit
            )
        ]
    )


@ft.component
def settingsView():
    page = ft.context.page
    page_width = page.width if (page and page.width) else 1000
    user = use_user()
    auth = use_auth()
    auth_service = ft.use_memo(lambda: AuthService(), [])
    camera_service = ft.use_memo(lambda: CameraService(), [])
    
    # State for User List refresh & Camera List refresh
    refresh_key, set_refresh_key = ft.use_state(0)
    cameras = ft.use_memo(lambda: camera_service.get_cameras(), [refresh_key])

    # Edit Camera Modal Active State
    editing_cam, set_editing_cam = ft.use_state(None)

    # Declarative React Hooks State for Create User Inputs
    new_username, set_new_username = ft.use_state("")
    new_password, set_new_password = ft.use_state("")
    new_role, set_new_role = ft.use_state("operator")

    # Declarative React Hooks State for Add Camera Inputs
    cam_name, set_cam_name = ft.use_state("")
    cam_type, set_cam_type = ft.use_state("webcam")
    cam_source, set_cam_source = ft.use_state("")

    # Handlers for Camera Management
    def handle_add_camera(e):
        name = cam_name.strip()
        source = cam_source.strip()
        if name and source:
            camera_service.add_camera(name, cam_type, source)
            set_refresh_key(refresh_key + 1)
            set_cam_name("")
            set_cam_source("")
            page.show_dialog(
                ft.SnackBar(
                    content=ft.Text(f"Camera '{name}' added successfully!", font_family=AppFonts.MYANMAR),
                    bgcolor=ft.Colors.GREEN_900,
                    duration=3000
                )
            )
        else:
            page.show_dialog(
                ft.SnackBar(
                    content=ft.Text("Please fill in both Camera Name and Source URL/Index!", font_family=AppFonts.MYANMAR),
                    bgcolor=ft.Colors.RED_900,
                    duration=3000
                )
            )

    def handle_delete_camera(cid: int):
        camera_service.delete_camera(cid)
        set_refresh_key(refresh_key + 1)
        page.show_dialog(
            ft.SnackBar(
                content=ft.Text("Camera setup deleted successfully.", font_family=AppFonts.MYANMAR),
                bgcolor=ft.Colors.BLUE_900,
                duration=3000
            )
        )

    # Reset Password Modal Dialog Helper
    def show_temp_pw_dialog(target_username: str, temp_pw: str):
        dialog = ft.AlertDialog(
            title=ft.Row([
                ft.Icon(ft.Icons.KEY_ROUNDED, color=ft.Colors.BLUE_400),
                ft.Text("Password Reset Successful", weight=ft.FontWeight.BOLD, size=16)
            ], spacing=8),
            content=ft.Container(
                padding=10,
                content=ft.Column(
                    tight=True,
                    spacing=12,
                    controls=[
                        ft.Text(f"User '{target_username}' ၏ စကားဝှက်ကို ယာယီစကားဝှက်သို့ ပြောင်းလဲပြီးပါပြီ။", font_family=AppFonts.MYANMAR, size=13),
                        ft.Container(
                            bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
                            padding=14,
                            border_radius=8,
                            border=ft.Border.all(1, ft.Colors.BLUE_900),
                            content=ft.Row([
                                ft.Text("Temporary Password: ", size=12, color=ft.Colors.ON_SURFACE_VARIANT),
                                ft.Text(temp_pw, size=16, weight=ft.FontWeight.BOLD, color=ft.Colors.CYAN_400, selectable=True)
                            ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN)
                        ),
                        ft.Text("⚠️ ကျေးဇူးပြု၍ ဤ ယာယီစကားဝှက်အား ကူးယူ၍ သက်ဆိုင်ရာ User သို့ ပေးပို့ပေးပါခင်ဗျာ။", font_family=AppFonts.MYANMAR, size=11, color=ft.Colors.AMBER_400)
                    ]
                )
            ),
            actions=[
                ft.TextButton("CLOSE", on_click=lambda e: page.close_dialog())
            ]
        )
        page.show_dialog(dialog)

    # Action Handlers
    def handle_reset_password(target_username: str):
        success, temp_pw, msg = auth_service.reset_user_password_temp(target_username)
        if success:
            show_temp_pw_dialog(target_username, temp_pw)
            set_refresh_key(refresh_key + 1)
        else:
            page.show_dialog(
                ft.SnackBar(
                    content=ft.Text(msg, font_family=AppFonts.MYANMAR),
                    bgcolor=ft.Colors.RED_900,
                    duration=4000
                )
            )

    def handle_create_user(e):
        uname = new_username.strip()
        pwd = new_password.strip()
        
        success, msg = auth_service.create_user(uname, pwd, new_role)
        if success:
            set_new_username("")
            set_new_password("")
            page.show_dialog(
                ft.SnackBar(
                    content=ft.Text(msg, font_family=AppFonts.MYANMAR),
                    bgcolor=ft.Colors.GREEN_900,
                    duration=4000
                )
            )
            set_refresh_key(refresh_key + 1)
        else:
            page.show_dialog(
                ft.SnackBar(
                    content=ft.Text(msg, font_family=AppFonts.MYANMAR),
                    bgcolor=ft.Colors.RED_900,
                    duration=4000
                )
            )

    # Fetch updated user list
    users_list = auth_service.get_all_users()
    
    # Build User List UI controls
    user_rows = []
    for u in users_list:
        is_admin_user = u.role == "admin"
        role_color = ft.Colors.PURPLE_600 if is_admin_user else ft.Colors.BLUE_600
        
        user_rows.append(
            ft.Container(
                padding=ft.Padding(12, 10, 12, 10),
                bgcolor=ft.Colors.SURFACE_CONTAINER,
                border_radius=8,
                border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
                content=ft.Row(
                    alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                    controls=[
                        ft.Row([
                            ft.CircleAvatar(
                                content=ft.Text(u.user_name[0].upper(), weight=ft.FontWeight.BOLD, size=13),
                                radius=15,
                                bgcolor=role_color
                            ),
                            ft.Column([
                                ft.Text(u.user_name, weight=ft.FontWeight.BOLD, size=13, color=ft.Colors.ON_SURFACE),
                                ft.Container(
                                    content=ft.Text(u.role.upper(), size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.WHITE),
                                    bgcolor=role_color,
                                    padding=ft.Padding(6, 2, 6, 2),
                                    border_radius=4
                                )
                            ], spacing=2)
                        ], spacing=10),
                        
                        ft.ElevatedButton(
                            "Reset PW",
                            icon=ft.Icons.LOCK_RESET_ROUNDED,
                            style=ft.ButtonStyle(
                                bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
                                color=ft.Colors.AMBER_400,
                                padding=ft.Padding(10, 6, 10, 6)
                            ),
                            on_click=lambda e, username=u.user_name: handle_reset_password(username)
                        )
                    ]
                )
            )
        )

    # 1. Profile Studio Card
    profile_card = ft.Container(
        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
        border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
        border_radius=14,
        padding=16,
        content=ft.Column(
            spacing=14,
            controls=[
                ft.Row(
                    alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                    controls=[
                        ft.Row([
                            ft.Icon(ft.Icons.PERSON_ROUNDED, color=ft.Colors.BLUE_400, size=20),
                            ft.Text("USER PROFILE SESSION", size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                        ], spacing=8),
                        ft.Container(
                            padding=ft.Padding(8, 4, 8, 4),
                            bgcolor=ft.Colors.GREEN_900,
                            border_radius=6,
                            content=ft.Row([
                                ft.Container(width=6, height=6, border_radius=3, bgcolor=ft.Colors.GREEN_400),
                                ft.Text("ACTIVE SESSION", size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.WHITE)
                            ], spacing=4)
                        )
                    ]
                ),
                ft.Divider(height=1),
                ft.Row(
                    controls=[
                        ft.CircleAvatar(
                            content=ft.Text(
                                user.user_name[0].upper() if user else "?",
                                size=22,
                                weight=ft.FontWeight.BOLD
                            ),
                            radius=28,
                            bgcolor=ft.Colors.PURPLE_700 if (user and user.is_admin()) else ft.Colors.BLUE_700
                        ),
                        ft.Column(
                            spacing=4,
                            controls=[
                                ft.Row([
                                    ft.Text(
                                        user.user_name if user else "Guest User",
                                        size=18,
                                        weight=ft.FontWeight.BOLD
                                    ),
                                    ft.Container(
                                        content=ft.Text(
                                            user.role.upper() if user else "NO ROLE",
                                            size=10,
                                            weight=ft.FontWeight.BOLD,
                                            color=ft.Colors.WHITE
                                        ),
                                        bgcolor=ft.Colors.PURPLE_700 if (user and user.is_admin()) else ft.Colors.BLUE_700,
                                        padding=ft.Padding(8, 3, 8, 3),
                                        border_radius=6
                                    )
                                ], spacing=8),
                                ft.Text(
                                    "Authenticated Account • Full System Privileges",
                                    size=11,
                                    color=ft.Colors.ON_SURFACE_VARIANT
                                ),
                            ],
                            expand=True
                        ),
                    ]
                )
            ]
        )
    )

    # 2. CCTV & Camera Configurations Card
    cctv_config_card = ft.Container(
        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
        border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
        border_radius=14,
        padding=16,
        content=ft.Column(
            spacing=14,
            controls=[
                ft.Row([
                    ft.Icon(ft.Icons.VIDEOCAM_ROUNDED, color=ft.Colors.BLUE_400, size=20),
                    ft.Text("CCTV & HARDWARE SOURCES", size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                ], spacing=8),
                ft.Text(
                    "Manage PC Webcams, Wireless IP CCTV (RTSP) & Wired Surveillance Streams saved in SQLite DB.",
                    size=11,
                    color=ft.Colors.ON_SURFACE_VARIANT
                ),
                ft.Divider(height=1),

                # Registered Cameras List
                ft.Column(
                    spacing=8,
                    controls=[
                        ft.Container(
                            bgcolor=ft.Colors.SURFACE_CONTAINER,
                            border_radius=8,
                            padding=10,
                            border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
                            content=ft.Row([
                                ft.Icon(
                                    ft.Icons.CAMERA_ALT_ROUNDED if c["device_type"] == "webcam" else ft.Icons.WIFI_ROUNDED if c["device_type"] == "rtsp_wireless" else ft.Icons.CABLE_ROUNDED,
                                    color=ft.Colors.CYAN_400,
                                    size=18
                                ),
                                ft.Column([
                                    ft.Text(c["name"], size=12, weight=ft.FontWeight.BOLD),
                                    ft.Text(f"Source: {c['source']} • Type: {c['device_type'].upper()}", size=10, color=ft.Colors.ON_SURFACE_VARIANT)
                                ], spacing=2, expand=True),
                                ft.Row([
                                    ft.IconButton(
                                        icon=ft.Icons.EDIT_OUTLINED,
                                        icon_size=18,
                                        icon_color=ft.Colors.CYAN_400,
                                        tooltip="Edit Camera Setup",
                                        on_click=lambda e, target_cam=c: set_editing_cam(target_cam)
                                    ),
                                    ft.IconButton(
                                        icon=ft.Icons.DELETE_OUTLINED,
                                        icon_size=18,
                                        icon_color=ft.Colors.RED_400,
                                        tooltip="Delete Camera Setup",
                                        on_click=lambda e, cid=c["id"]: handle_delete_camera(cid)
                                    )
                                ], spacing=2)
                            ])
                        ) for c in cameras
                    ]
                ),

                ft.Divider(height=1),

                # Add New Camera Setup Controls (Pure Declarative UI State)
                ft.Text("Add New CCTV / Camera Setup", size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE),
                ft.ResponsiveRow([
                    ft.Container(
                        col={"xs": 12, "md": 7},
                        content=ft.TextField(
                            value=cam_name,
                            on_change=lambda e: set_cam_name(e.control.value),
                            label="Camera Name",
                            hint_text="e.g. Backdoor Wireless CCTV",
                            dense=True,
                            text_size=12
                        )
                    ),
                    ft.Container(
                        col={"xs": 12, "md": 5},
                        content=ft.Dropdown(
                            value=cam_type,
                            on_select=lambda e: set_cam_type(e.control.value),
                            label="Type",
                            dense=True,
                            text_size=12,
                            options=[
                                ft.dropdown.Option("webcam", "PC Webcam"),
                                ft.dropdown.Option("rtsp_wireless", "Wireless CCTV (RTSP)"),
                                ft.dropdown.Option("rtsp_wired", "Wired CCTV (RTSP)"),
                            ]
                        )
                    )
                ], spacing=10),
                ft.Row([
                    ft.TextField(
                        value=cam_source,
                        on_change=lambda e: set_cam_source(e.control.value),
                        label="Source (Index / RTSP URL)",
                        hint_text="0 or rtsp://192.168.1.100:554/live",
                        expand=True,
                        dense=True,
                        text_size=12
                    ),
                    ft.ElevatedButton(
                        "+ ADD",
                        icon=ft.Icons.ADD_ROUNDED,
                        style=ft.ButtonStyle(bgcolor=ft.Colors.BLUE_600, color=ft.Colors.WHITE),
                        on_click=handle_add_camera
                    )
                ], spacing=10)
            ]
        )
    )

    # 3. Security & Access Card
    security_card = ft.Container(
        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
        border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
        border_radius=14,
        padding=16,
        content=ft.Column(
            spacing=12,
            controls=[
                ft.Row([
                    ft.Icon(ft.Icons.SECURITY_ROUNDED, color=ft.Colors.BLUE_400, size=20),
                    ft.Text("SECURITY & ACCOUNT ACCESS", size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                ], spacing=8),
                ft.Divider(height=1),
                ft.ListTile(
                    leading=ft.Icon(ft.Icons.LOCK_OUTLINED, size=20, color=ft.Colors.CYAN_400),
                    title=ft.Text("Change Master Credentials / PIN", size=13),
                    trailing=ft.Icon(ft.Icons.CHEVRON_RIGHT_ROUNDED, size=18),
                    on_click=lambda _: None,
                ),
                ft.ListTile(
                    leading=ft.Icon(ft.Icons.LOGOUT_ROUNDED, size=20, color=ft.Colors.RED_400),
                    title=ft.Text("Sign Out Session", size=13, color=ft.Colors.RED_400, weight=ft.FontWeight.BOLD),
                    trailing=ft.Icon(ft.Icons.CHEVRON_RIGHT_ROUNDED, size=18, color=ft.Colors.RED_400),
                    on_click=lambda e: auth.logout(),
                ),
            ]
        )
    )

    # 4. Admin User Studio Card (Rendered ONLY if user is admin)
    admin_studio_card = ft.Container(
        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
        border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
        border_radius=14,
        padding=16,
        content=ft.Column(
            spacing=14,
            controls=[
                ft.Row(
                    alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                    controls=[
                        ft.Row([
                            ft.Icon(ft.Icons.ADMIN_PANEL_SETTINGS_ROUNDED, color=ft.Colors.PURPLE_400, size=20),
                            ft.Text("USER MANAGEMENT STUDIO", size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                        ], spacing=8),
                        ft.Container(
                            padding=ft.Padding(8, 3, 8, 3),
                            bgcolor=ft.Colors.PURPLE_900,
                            border_radius=6,
                            content=ft.Text("ADMIN ONLY", size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.PURPLE_200)
                        )
                    ]
                ),
                ft.Text("Create new operational accounts and manage security credentials.", size=11, color=ft.Colors.ON_SURFACE_VARIANT),
                ft.Divider(height=1),
                
                # Create User Controls Form (Pure Declarative UI State)
                ft.Text("Create New Account", size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE),
                ft.ResponsiveRow([
                    ft.Container(
                        col={"xs": 12, "md": 6},
                        content=ft.TextField(
                            value=new_username,
                            on_change=lambda e: set_new_username(e.control.value),
                            label="Username",
                            hint_text="e.g. operator_01",
                            dense=True,
                            text_size=12
                        )
                    ),
                    ft.Container(
                        col={"xs": 12, "md": 6},
                        content=ft.TextField(
                            value=new_password,
                            on_change=lambda e: set_new_password(e.control.value),
                            label="Password",
                            password=True,
                            can_reveal_password=True,
                            dense=True,
                            text_size=12
                        )
                    ),
                ], spacing=10),
                ft.Row([
                    ft.Dropdown(
                        value=new_role,
                        on_select=lambda e: set_new_role(e.control.value),
                        label="System Role",
                        dense=True,
                        text_size=12,
                        expand=True,
                        options=[
                            ft.dropdown.Option("operator", "Operator (Standard Access)"),
                            ft.dropdown.Option("admin", "Administrator (Full Access)"),
                        ]
                    ),
                    ft.ElevatedButton(
                        "Create User",
                        icon=ft.Icons.PERSON_ADD_ROUNDED,
                        style=ft.ButtonStyle(
                            bgcolor=ft.Colors.PURPLE_600,
                            color=ft.Colors.WHITE,
                            padding=ft.Padding(14, 10, 14, 10)
                        ),
                        on_click=handle_create_user
                    )
                ], spacing=10),
                
                ft.Divider(height=1),
                
                # Registered Users List Header
                ft.Row([
                    ft.Text("REGISTERED ACCOUNTS", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE),
                    ft.Text(f"{len(users_list)} Accounts", size=11, color=ft.Colors.ON_SURFACE_VARIANT, weight=ft.FontWeight.BOLD)
                ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN),
                
                ft.Column(
                    controls=user_rows,
                    spacing=8
                )
            ]
        )
    )

    # Assembly into Responsive 2-Column Studio Grid Layout
    return ft.Container(
        expand=True,
        padding=14,
        content=ft.Column(
            spacing=16,
            scroll=ft.ScrollMode.AUTO,
            controls=[
                # Render Edit Camera Modal if active
                EditCameraModal(
                    cam_item=editing_cam,
                    on_close=lambda: set_editing_cam(None),
                    on_saved=lambda: set_refresh_key(refresh_key + 1)
                ) if editing_cam else ft.Container(),

                # Page Cyber Header
                ft.Container(
                    padding=ft.Padding(0, 0, 0, 4),
                    content=ft.Row(
                        alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                        controls=[
                            ft.Column([
                                ft.Row([
                                    ft.Container(width=6, height=14, bgcolor=ft.Colors.BLUE_400, border_radius=3),
                                    ft.Text("SYSTEM CONTROL CENTER", size=10, color=ft.Colors.BLUE_400, weight=ft.FontWeight.BOLD, ),
                                ], spacing=6),
                                ft.Text("SETTINGS & CONFIGURATIONS", size=22, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                            ], spacing=2),
                            ft.Icon(ft.Icons.SETTINGS_ROUNDED, size=28, color=ft.Colors.BLUE_400)
                        ]
                    )
                ),
                ft.Divider(height=1),

                # Responsive 2-Column Row Layout
                ft.ResponsiveRow(
                    spacing=14,
                    controls=[
                        # Left Column: Profile, CCTV Hardware Manager & Security
                        ft.Container(
                            col={"xs": 12, "lg": 6},
                            content=ft.Column([
                                profile_card,
                                cctv_config_card,
                                security_card,
                            ], spacing=14)
                        ),

                        # Right Column: AI Model Engine & Admin User Management Studio
                        ft.Container(
                            col={"xs": 12, "lg": 6},
                            content=ft.Column([
                                ModelSelector(),
                                admin_studio_card if (user and user.is_admin()) else ft.Container(),
                            ], spacing=14)
                        )
                    ]
                )
            ]
        )
    )