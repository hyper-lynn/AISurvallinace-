# src/views/settingsView.py
import flet as ft
from typing import Callable
from core.auth_context import use_user, use_auth
from core.helper import use_loc, use_localization_context, use_theme_context
from services.auth_service import AuthService
from services.camera_service import CameraService
from services.telegram_service import TelegramService
from views.components.model_selector import ModelSelector
from views.components.userProfileDialog import show_user_profile_dialog, show_edit_target_dialog
from views.components.target_face_manager import TargetFaceManager
from config.fonts import AppFonts



@ft.component
def EditCameraModal(cam_item: dict, on_close: Callable[[], None], on_saved: Callable[[], None]):
    """
    Pure Declarative UI Component for Editing Camera Channel Details & AI Profile Settings.
    """
    page = ft.context.page
    t = use_loc()
    camera_service = ft.use_memo(lambda: CameraService(), [])
    telegram_service = ft.use_memo(lambda: TelegramService(), [])
    tg_targets = telegram_service.get_targets()

    edit_name, set_edit_name = ft.use_state(cam_item["name"])
    edit_type, set_edit_type = ft.use_state(cam_item["device_type"])
    edit_source, set_edit_source = ft.use_state(cam_item["source"])
    edit_group, set_edit_group = ft.use_state(cam_item.get("camera_group", "Zone-01"))

    # Per-Camera Profile Settings State (Default OFF as requested)
    edit_model, set_edit_model = ft.use_state(cam_item.get("detection_model", "yolov8n"))
    edit_motion, set_edit_motion = ft.use_state(bool(cam_item.get("motion_detection", 0)))
    edit_human, set_edit_human = ft.use_state(bool(cam_item.get("human_detection", 0)))
    edit_tg_chat, set_edit_tg_chat = ft.use_state(cam_item.get("telegram_chat_id", ""))
    edit_tg_enable, set_edit_tg_enable = ft.use_state(bool(cam_item.get("telegram_alert_enabled", 0)))

    target_options = [ft.dropdown.Option("", "Use Global Telegram Chat ID")]
    for target in tg_targets:
        target_options.append(
            ft.dropdown.Option(
                target["chat_id"],
                f"{target['target_name']} ({target['target_type'].upper()}: {target['chat_id']})"
            )
        )

    def handle_save_camera_edit(e):
        name = edit_name.strip()
        source = edit_source.strip()
        if source and not (source.startswith("rtsp://") or source.startswith("rtsps://") or source == "0" or source.startswith("p2p://") or source.upper().startswith("SN:")):
            if edit_type == "p2p_dahua" or len(source) >= 6:
                source = f"SN:{source}"
        if name and source:
            camera_service.update_camera(
                camera_id=cam_item["id"],
                name=name,
                device_type=edit_type,
                source=source,
                camera_group=edit_group,
                detection_model=edit_model,
                motion_detection=1 if edit_motion else 0,
                human_detection=1 if edit_human else 0,
                telegram_chat_id=edit_tg_chat,
                telegram_alert_enabled=1 if edit_tg_enable else 0
            )
            on_saved()
            on_close()
            dialog = ft.AlertDialog(
                open=True,
                title=ft.Row([
                    ft.Icon(ft.Icons.CHECK_CIRCLE_ROUNDED, color=ft.Colors.GREEN_400),
                    ft.Text("Camera Profile Saved", weight=ft.FontWeight.BOLD, size=15)
                ], spacing=8),
                content=ft.Text(f"Camera '{name}' profile updated successfully!", font_family=AppFonts.MYANMAR, size=13),
                actions=[ft.Button("OK", on_click=lambda _: page.pop_dialog())]
            )
            page.show_dialog(dialog)
        else:
            dialog = ft.AlertDialog(
                open=True,
                title=ft.Row([
                    ft.Icon(ft.Icons.ERROR_ROUNDED, color=ft.Colors.RED_400),
                    ft.Text("Validation Error", weight=ft.FontWeight.BOLD, size=15)
                ], spacing=8),
                content=ft.Text("Camera Name and Source URL cannot be empty!", font_family=AppFonts.MYANMAR, size=13),
                actions=[ft.Button("OK", on_click=lambda _: page.pop_dialog())]
            )
            page.show_dialog(dialog)

    return ft.AlertDialog(
        open=True,
        title=ft.Row([
            ft.Icon(ft.Icons.TUNE_ROUNDED, color=ft.Colors.CYAN_400),
            ft.Text(f"{t('camera_profile_setup')}: {cam_item['name']}", weight=ft.FontWeight.BOLD, size=15)
        ], spacing=8),
        content=ft.Container(
            width=500,
            padding=10,
            content=ft.Column(
                tight=True,
                spacing=12,
                scroll=ft.ScrollMode.HIDDEN,
                controls=[
                    ft.Text(t("hardware_channel_details"), size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE),
                    ft.TextField(
                        value=edit_name,
                        on_change=lambda e: set_edit_name(e.control.value),
                        label=t("camera_name"),
                        dense=True,
                        text_size=12
                    ),
                    ft.Dropdown(
                        value=edit_type,
                        on_select=lambda e: set_edit_type(e.control.value),
                        label=t("camera_type"),
                        dense=True,
                        text_size=12,
                        options=[
                            ft.dropdown.Option("webcam", "PC Webcam (Local)"),
                            ft.dropdown.Option("rtsp_wireless", "Wireless CCTV (RTSP)"),
                            ft.dropdown.Option("rtsp_wired", "Wired CCTV (RTSP)"),
                            ft.dropdown.Option("p2p_dahua", "Dahua P2P Cloud"),
                        ]
                    ),
                    ft.TextField(
                        value=edit_group,
                        on_change=lambda e: set_edit_group(e.control.value),
                        label="Operational Tag / Group",
                        hint_text="e.g. Zone-01 or DEPT: SURV-01",
                        dense=True,
                        text_size=12
                    ),
                    ft.TextField(
                        value=edit_source,
                        on_change=lambda e: set_edit_source(e.control.value),
                        label=t("camera_source"),
                        dense=True,
                        text_size=12
                    ),

                    ft.Divider(height=1),
                    ft.Text(t("ai_detection_telegram_profile_settings"), size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.CYAN_400),

                    ft.Dropdown(
                        value=edit_model,
                        on_select=lambda e: set_edit_model(e.control.value),
                        label=t("scan_model_engine"),
                        dense=True,
                        text_size=12,
                        options=[
                            ft.dropdown.Option("yolov8n", "YOLOv8 Nano (Fast Real-time Human Detection)"),
                            ft.dropdown.Option("mog2", "OpenCV MOG2 (Ultra-fast Motion Subtractor)"),
                            ft.dropdown.Option("gemini-3.6-flash", "Gemini 3.6 Flash (AI Multimodal Scene Analysis)"),
                        ]
                    ),

                    ft.Row([
                        ft.Switch(
                            value=edit_motion,
                            on_change=lambda e: set_edit_motion(e.control.value),
                            active_color=ft.Colors.CYAN_400
                        ),
                        ft.Text(t("motion_detection_scan"), size=12)
                    ], spacing=6),

                    ft.Row([
                        ft.Switch(
                            value=edit_human,
                            on_change=lambda e: set_edit_human(e.control.value),
                            active_color=ft.Colors.AMBER_400
                        ),
                        ft.Text(t("human_detection_scan"), size=12)
                    ], spacing=6),

                    ft.Divider(height=1),

                    ft.Dropdown(
                        value=edit_tg_chat,
                        on_select=lambda e: set_edit_tg_chat(e.control.value),
                        label=t("custom_telegram_chat_id"),
                        dense=True,
                        text_size=12,
                        options=target_options
                    ),
                    ft.TextField(
                        value=edit_tg_chat,
                        on_change=lambda e: set_edit_tg_chat(e.control.value),
                        label="Or Direct Custom Chat ID / Username",
                        hint_text="e.g. -1001234567890 or @my_alert_channel",
                        dense=True,
                        text_size=12
                    ),
                    ft.Row([
                        ft.Switch(
                            value=edit_tg_enable,
                            on_change=lambda e: set_edit_tg_enable(e.control.value),
                            active_color=ft.Colors.BLUE_400
                        ),
                        ft.Text(t("enable_telegram_alerts_camera"), size=12)
                    ], spacing=6),
                ]
            )
        ),
        actions=[
            ft.TextButton(t("cancel_btn"), on_click=lambda e: on_close()),
            ft.Button(
                t("save_profile_btn"),
                icon=ft.Icons.SAVE_ROUNDED,
                style=ft.ButtonStyle(bgcolor=ft.Colors.CYAN_700, color=ft.Colors.WHITE),
                on_click=handle_save_camera_edit
            )
        ]
    )


@ft.component
def settingsView():
    page = ft.context.page
    t = use_loc()
    loc_ctx = use_localization_context()
    theme_ctx = use_theme_context()
    user = use_user()
    auth = use_auth()
    auth_service = ft.use_memo(lambda: AuthService(), [])
    camera_service = ft.use_memo(lambda: CameraService(), [])
    telegram_service = ft.use_memo(lambda: TelegramService(), [])

    # Active Tab Index State (0: Preferences, 1: Telegram Bot, 2: CCTV Sources, 3: Operatives)
    active_tab, set_active_tab = ft.use_state(2)
    
    # Refresh State
    refresh_key, set_refresh_key = ft.use_state(0)
    cameras = ft.use_memo(lambda: camera_service.get_cameras(), [refresh_key])
    tg_config = ft.use_memo(lambda: telegram_service.get_config(), [refresh_key])
    tg_targets = ft.use_memo(lambda: telegram_service.get_targets(), [refresh_key])

    # Search & Group Filtering State (Requested)
    search_query, set_search_query = ft.use_state("")
    target_search_query, set_target_search_query = ft.use_state("")
    selected_group, set_selected_group = ft.use_state("ALL GROUPS")

    # Telegram Bot Settings State
    tg_bot_token, set_tg_bot_token = ft.use_state(tg_config["bot_token"])
    tg_chat_id, set_tg_chat_id = ft.use_state(tg_config["chat_id"])
    tg_enable_motion, set_tg_enable_motion = ft.use_state(tg_config["enable_motion_alert"])
    tg_enable_human, set_tg_enable_human = ft.use_state(tg_config["enable_human_alert"])
    tg_model, set_tg_model = ft.use_state(tg_config["selected_model"])
    tg_testing, set_tg_testing = ft.use_state(False)
    tg_ai_listener, set_tg_ai_listener = ft.use_state(getattr(telegram_service, "_polling_active", False))

    def handle_toggle_tg_ai_listener(e):
        val = e.control.value
        set_tg_ai_listener(val)
        if val:
            telegram_service.start_ai_bot_polling()
            show_feedback("Telegram AI Chat Enabled", "Telegram Bot Gemini AI Chat Listener Worker Started!", is_success=True)
        else:
            telegram_service.stop_ai_bot_polling()
            show_feedback("Telegram AI Chat Disabled", "Telegram Bot Gemini AI Chat Listener Worker Stopped.", is_success=True)

    # State for Add Telegram Target Destination Inputs
    new_target_name, set_new_target_name = ft.use_state("")
    new_target_type, set_new_target_type = ft.use_state("user")
    new_target_chat_id, set_new_target_chat_id = ft.use_state("")
    new_target_note, set_new_target_note = ft.use_state("")

    # Edit Camera Modal Active State
    editing_cam, set_editing_cam = ft.use_state(None)

    # Declarative State for Create User Inputs
    new_username, set_new_username = ft.use_state("")
    new_password, set_new_password = ft.use_state("")
    new_role, set_new_role = ft.use_state("operator")

    # Declarative State for Add Camera Inputs (AEGIS Architecture Form)
    cam_name, set_cam_name = ft.use_state("")
    cam_type, set_cam_type = ft.use_state("webcam")
    cam_group, set_cam_group = ft.use_state("DEPT: SURV-01")
    cam_source, set_cam_source = ft.use_state("")

    # Helper function to present clean AlertDialog feedback
    def show_feedback(dialog_title: str, message: str, is_success: bool = True):
        dialog = ft.AlertDialog(
            open=True,
            title=ft.Row([
                ft.Icon(
                    ft.Icons.CHECK_CIRCLE_ROUNDED if is_success else ft.Icons.ERROR_ROUNDED,
                    color=ft.Colors.GREEN_400 if is_success else ft.Colors.RED_400,
                    size=22
                ),
                ft.Text(dialog_title, weight=ft.FontWeight.BOLD, size=15)
            ], spacing=8),
            content=ft.Container(
                padding=10,
                width=420,
                content=ft.Text(message, size=13, font_family=AppFonts.MYANMAR)
            ),
            actions=[
                ft.Button(
                    "OK",
                    style=ft.ButtonStyle(bgcolor=ft.Colors.BLUE_700, color=ft.Colors.WHITE),
                    on_click=lambda _: page.pop_dialog()
                )
            ]
        )
        page.show_dialog(dialog)

    # Action Handlers for Telegram Bot Config
    def handle_save_telegram_config(e):
        success, msg = telegram_service.save_config(
            tg_bot_token, tg_chat_id, tg_enable_motion, tg_enable_human, tg_model
        )
        show_feedback(
            dialog_title="Telegram Setup Saved" if success else "Save Error",
            message=msg,
            is_success=success
        )

    def handle_test_telegram_connection(e, target_cid: str = None):
        set_tg_testing(True)
        cid = target_cid or tg_chat_id
        success, msg = telegram_service.send_test_message(tg_bot_token, cid)
        set_tg_testing(False)
        show_feedback(
            dialog_title="Telegram Target Test Success" if success else "Telegram Target Test Failed",
            message=msg,
            is_success=success
        )

    # Action Handlers for Telegram Targets (Users, Channels, Groups)
    def handle_add_target(e):
        success, msg = telegram_service.add_target(
            new_target_name, new_target_type, new_target_chat_id, new_target_note
        )
        if success:
            set_new_target_name("")
            set_new_target_chat_id("")
            set_new_target_note("")
            set_refresh_key(refresh_key + 1)
            show_feedback("Telegram Target Added", msg, is_success=True)
        else:
            show_feedback("Input Error", msg, is_success=False)

    def handle_delete_target(tid: int):
        success, msg = telegram_service.delete_target(tid)
        set_refresh_key(refresh_key + 1)
        show_feedback("Target Deleted", msg, is_success=True)

    # Action Handlers for Camera Management
    def handle_add_camera(e):
        name = cam_name.strip()
        source = cam_source.strip()
        grp = cam_group.strip() or "Zone-01"
        if source and not (source.startswith("rtsp://") or source.startswith("rtsps://") or source == "0" or source.startswith("p2p://") or source.upper().startswith("SN:")):
            if cam_type == "p2p_dahua" or len(source) >= 6:
                source = f"SN:{source}"
        if name and source:
            camera_service.add_camera(
                name=name,
                device_type=cam_type,
                source=source,
                camera_group=grp
            )
            set_refresh_key(refresh_key + 1)
            set_cam_name("")
            set_cam_source("")
            show_feedback("Camera Deployed", f"Camera '{name}' deployed to registry successfully under '{grp}'!", is_success=True)
        else:
            show_feedback("Input Error", "Please fill in Camera Name and Source Link / Serial Number!", is_success=False)

    def handle_open_quick_sn_dialog(e):
        known_sn_items = []
        for c in cameras:
            src = str(c.get("source", "")).strip()
            if "SN:" in src or src.startswith("p2p://") or len(src) >= 8 and not src.startswith("http") and not src.startswith("rtsp"):
                sn_clean = src.replace("p2p://", "").replace("SN:", "").replace("sn:", "").strip()
                known_sn_items.append({"sn": sn_clean, "name": c.get("name"), "group": c.get("camera_group", "Zone-01")})

        sn_name_input = ft.TextField(label="CAMERA NAME", hint_text="e.g. Wired Channel 1 / IMOU Gate", dense=True, text_size=12)
        sn_val_input = ft.TextField(label="SERIAL NUMBER (SN)", hint_text="e.g. 66350BDPSF37F69 or 07474BCPSFDB9D7", dense=True, text_size=12)
        sn_group_input = ft.TextField(label="ZONE / GROUP TAG", value="Wired Channel", hint_text="e.g. IMOU Wireless or Wired Channel", dense=True, text_size=12)

        def handle_select_known_sn(evt):
            val = evt.control.value
            if val:
                for k in known_sn_items:
                    if k["sn"] == val:
                        sn_val_input.value = k["sn"]
                        sn_name_input.value = k["name"]
                        sn_group_input.value = k["group"]
                        break
                page.update()

        sn_picker_dropdown = ft.Dropdown(
            label="🔑 SELECT STORED SERIAL NUMBER (SN)",
            hint_text="Select a known Serial Number from Database...",
            dense=True,
            text_size=11,
            options=[
                ft.dropdown.Option(item["sn"], f"{item['sn']} ({item['name']} - {item['group']})") for item in known_sn_items
            ],
            on_select=handle_select_known_sn
        ) if known_sn_items else ft.Container()

        def save_quick_sn(evt):
            name = sn_name_input.value.strip()
            sn = sn_val_input.value.strip()
            grp = sn_group_input.value.strip() or "Zone-01"
            if name and sn:
                sn_source = f"SN:{sn}" if not sn.startswith("SN:") and not sn.startswith("p2p://") else sn
                camera_service.add_camera(
                    name=name,
                    device_type="p2p_dahua",
                    source=sn_source,
                    camera_group=grp
                )
                set_refresh_key(refresh_key + 1)
                page.pop_dialog()
                show_feedback("SN Camera Added", f"Camera '{name}' with SN '{sn}' added under '{grp}' successfully!", is_success=True)
            else:
                show_feedback("Input Error", "Please fill in both Camera Name and Serial Number!", is_success=False)

        dialog = ft.AlertDialog(
            open=True,
            title=ft.Row([
                ft.Icon(ft.Icons.QR_CODE_ROUNDED, color=ft.Colors.BLUE_400),
                ft.Text("Quick Select / Add Camera by Serial Number (SN)", weight=ft.FontWeight.BOLD, size=15)
            ], spacing=8),
            content=ft.Container(
                width=480,
                padding=10,
                content=ft.Column(
                    tight=True,
                    spacing=12,
                    controls=[
                        ft.Text("Select a known Serial Number from DB or type a new custom SN:", size=11, color=ft.Colors.ON_SURFACE_VARIANT, font_family=AppFonts.MYANMAR),
                        sn_picker_dropdown,
                        ft.Divider(height=1),
                        sn_name_input,
                        sn_val_input,
                        sn_group_input,
                    ]
                )
            ),
            actions=[
                ft.Button("Cancel", on_click=lambda _: page.pop_dialog()),
                ft.Button("Save SN Camera", style=ft.ButtonStyle(bgcolor=ft.Colors.BLUE_700, color=ft.Colors.WHITE), on_click=save_quick_sn)
            ]
        )
    def handle_open_wired_import_dialog(e):
        nvr_ip_input = ft.TextField(label="NVR / CAMERA IP ADDRESS", value="192.168.100.97", hint_text="e.g. 192.168.100.97", dense=True, text_size=12)
        nvr_user_input = ft.TextField(label="USERNAME", value="admin", dense=True, text_size=12)
        nvr_pass_input = ft.TextField(label="PASSWORD", value="12345asd@", password=True, can_reveal_password=True, dense=True, text_size=12)
        nvr_chans_input = ft.TextField(label="TOTAL CHANNELS COUNT", value="16", hint_text="e.g. 16, 8, or 4", dense=True, text_size=12)

        def do_import_wired(evt):
            target_ip = nvr_ip_input.value.strip() or "192.168.100.97"
            target_user = nvr_user_input.value.strip() or "admin"
            target_pass = nvr_pass_input.value.strip() or "12345asd@"
            try:
                ch_count = int(nvr_chans_input.value.strip())
            except Exception:
                ch_count = 16

            imported_cnt = camera_service.import_all_dahua_channels(
                ip=target_ip,
                user=target_user,
                password=target_pass,
                channel_count=ch_count,
                overwrite=True
            )
            set_refresh_key(refresh_key + 1)
            page.pop_dialog()
            show_feedback("Wired CCTV Imported", f"Successfully imported/updated {imported_cnt} Dahua Wired CCTV channels for IP {target_ip}!", is_success=True)

        dialog = ft.AlertDialog(
            open=True,
            title=ft.Row([
                ft.Icon(ft.Icons.AUTO_AWESOME_ROUNDED, color=ft.Colors.CYAN_400),
                ft.Text("Bulk Import Wired NVR / CCTV Channels", weight=ft.FontWeight.BOLD, size=15)
            ], spacing=8),
            content=ft.Container(
                width=450,
                padding=10,
                content=ft.Column(
                    tight=True,
                    spacing=12,
                    controls=[
                        ft.Text("Enter your Dahua/Wired NVR IP details to auto-generate and import all RTSP channels:", size=11, color=ft.Colors.ON_SURFACE_VARIANT, font_family=AppFonts.MYANMAR),
                        nvr_ip_input,
                        ft.Row([
                            ft.Container(col={"xs": 6}, content=nvr_user_input, expand=True),
                            ft.Container(col={"xs": 6}, content=nvr_pass_input, expand=True),
                        ], spacing=8),
                        nvr_chans_input,
                    ]
                )
            ),
            actions=[
                ft.Button("Cancel", on_click=lambda _: page.pop_dialog()),
                ft.Button("Import All Channels", style=ft.ButtonStyle(bgcolor=ft.Colors.CYAN_900, color=ft.Colors.CYAN_100), on_click=do_import_wired)
            ]
        )
        page.show_dialog(dialog)

    def handle_confirm_delete_camera(cam_item: dict):
        cid = cam_item["id"]
        cname = cam_item["name"]
        dialog = ft.AlertDialog(
            open=True,
            title=ft.Row([
                ft.Icon(ft.Icons.DELETE_FOREVER_ROUNDED, color=ft.Colors.RED_400),
                ft.Text("Confirm Delete Camera", weight=ft.FontWeight.BOLD, size=15)
            ], spacing=8),
            content=ft.Text(f"Are you sure you want to delete camera '{cname}' from database registry?", font_family=AppFonts.MYANMAR, size=12),
            actions=[
                ft.Button("Cancel", on_click=lambda _: page.pop_dialog()),
                ft.Button("Delete Camera", style=ft.ButtonStyle(bgcolor=ft.Colors.RED_900, color=ft.Colors.WHITE), on_click=lambda _: (
                    camera_service.delete_camera(cid),
                    set_refresh_key(refresh_key + 1),
                    page.pop_dialog(),
                    show_feedback("Camera Deleted", f"Camera '{cname}' deleted from database successfully.", is_success=True)
                ))
            ]
        )
        page.show_dialog(dialog)

    def handle_purge_all_cameras(e):
        dialog = ft.AlertDialog(
            open=True,
            title=ft.Row([
                ft.Icon(ft.Icons.WARNING_ROUNDED, color=ft.Colors.AMBER_400),
                ft.Text("Reset & Clear All Cameras Registry", weight=ft.FontWeight.BOLD, size=15)
            ], spacing=8),
            content=ft.Text("⚠️ Warning: This action will purge and delete ALL cameras and P2P entries from the database so you can start fresh. Continue?", font_family=AppFonts.MYANMAR, size=12),
            actions=[
                ft.Button("Cancel", on_click=lambda _: page.pop_dialog()),
                ft.Button("Purge All Cameras", style=ft.ButtonStyle(bgcolor=ft.Colors.RED_900, color=ft.Colors.WHITE), on_click=lambda _: (
                    camera_service.delete_all_cameras(),
                    set_refresh_key(refresh_key + 1),
                    page.pop_dialog(),
                    show_feedback("Registry Cleared", "All camera devices purged from database successfully.", is_success=True)
                ))
            ]
        )
        page.show_dialog(dialog)

    def handle_open_step_by_step_wizard(e):
        current_step = [1]  # Mutable step tracker
        
        wizard_type = ["rtsp_wired"]  # Default setup type
        name_in = ft.TextField(label="1. CAMERA / STREAM NAME", value="Dahua NVR Channel 01", dense=True, text_size=12)
        ip_in = ft.TextField(label="2. IP ADDRESS / HOST", value="192.168.100.97", dense=True, text_size=12)
        user_in = ft.TextField(label="3. USERNAME", value="admin", dense=True, text_size=12)
        pass_in = ft.TextField(label="4. PASSWORD / SAFETY CODE", value="12345asd@", password=True, can_reveal_password=True, dense=True, text_size=12)
        chan_in = ft.TextField(label="5. CHANNEL NUMBER", value="1", hint_text="1 to 16", dense=True, text_size=12)
        group_in = ft.TextField(label="6. ZONE / GROUP TAG", value="Zone-01", dense=True, text_size=12)

        status_text = ft.Text("Click 'Test Stream Connection' to verify live feed...", size=11, color=ft.Colors.CYAN_200)
        status_container = ft.Container(
            padding=10,
            bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
            border_radius=8,
            content=status_text
        )

        def build_current_source_str():
            t = wizard_type[0]
            if t == "webcam":
                return "0"
            elif t == "p2p_dahua":
                sn = chan_in.value.strip() or "8M0435CPAZ0E327"
                return f"SN:{sn}"
            else:
                ip = ip_in.value.strip() or "192.168.100.97"
                usr = user_in.value.strip() or "admin"
                pwd = pass_in.value.strip() or "12345asd@"
                ch = chan_in.value.strip() or "1"
                import urllib.parse
                enc_p = urllib.parse.quote(pwd, safe="")
                return f"rtsp://{usr}:{enc_p}@{ip}:554/cam/realmonitor?channel={ch}&subtype=0"

        def test_connection_action(evt):
            status_text.value = "⏳ Testing RTSP Stream Connection... Please wait..."
            status_text.color = ft.Colors.PRIMARY
            page.update()
            
            src = build_current_source_str()
            def _test():
                from controllers.camera_controller import CameraController
                cam_ctl = CameraController(source=src)
                cap = cam_ctl.open_cam_blocking()
                if cap and cap.isOpened():
                    ret, frame = cap.read()
                    cap.release()
                    if ret and frame is not None:
                        status_text.value = f"✅ SUCCESS: Connected to Stream! ({frame.shape[1]}x{frame.shape[0]} px)"
                        status_text.color = ft.Colors.GREEN_400
                    else:
                        status_text.value = "⚠️ WARNING: Opened stream but failed to read frame."
                        status_text.color = ft.Colors.AMBER_400
                else:
                    status_text.value = "❌ FAILED: Could not connect to camera stream. Check IP/Password."
                    status_text.color = ft.Colors.RED_400
                page.update()
            page.run_thread(_test)

        def save_wizard_camera(evt):
            cname = name_in.value.strip() or "New CCTV Stream"
            ctype = wizard_type[0]
            csource = build_current_source_str()
            cgroup = group_in.value.strip() or "Zone-01"

            camera_service.add_camera(
                name=cname,
                device_type=ctype,
                source=csource,
                camera_group=cgroup
            )
            set_refresh_key(refresh_key + 1)
            page.pop_dialog()
            show_feedback("Camera Saved", f"Camera '{cname}' configured and deployed successfully!", is_success=True)

        def handle_select_type(selected_type: str, default_name: str, is_sn: bool):
            wizard_type[0] = selected_type
            name_in.value = default_name
            chan_in.label = "5. SERIAL NUMBER (SN)" if is_sn else "5. CHANNEL NUMBER"
            btn_wired.style = ft.ButtonStyle(bgcolor=ft.Colors.CYAN_900 if selected_type == "rtsp_wired" else ft.Colors.SURFACE_CONTAINER_HIGH, color=ft.Colors.CYAN_200 if selected_type == "rtsp_wired" else ft.Colors.ON_SURFACE)
            btn_imou.style = ft.ButtonStyle(bgcolor=ft.Colors.CYAN_900 if selected_type == "rtsp_wireless" else ft.Colors.SURFACE_CONTAINER_HIGH, color=ft.Colors.CYAN_200 if selected_type == "rtsp_wireless" else ft.Colors.ON_SURFACE)
            btn_webcam.style = ft.ButtonStyle(bgcolor=ft.Colors.CYAN_900 if selected_type == "webcam" else ft.Colors.SURFACE_CONTAINER_HIGH, color=ft.Colors.CYAN_200 if selected_type == "webcam" else ft.Colors.ON_SURFACE)
            btn_custom.style = ft.ButtonStyle(bgcolor=ft.Colors.CYAN_900 if selected_type == "p2p_dahua" else ft.Colors.SURFACE_CONTAINER_HIGH, color=ft.Colors.CYAN_200 if selected_type == "p2p_dahua" else ft.Colors.ON_SURFACE)
            page.update()

        btn_wired = ft.Button("Dahua Wired NVR", icon=ft.Icons.ROUTER_ROUNDED, style=ft.ButtonStyle(bgcolor=ft.Colors.CYAN_900, color=ft.Colors.CYAN_200), on_click=lambda _: handle_select_type("rtsp_wired", "Dahua Wired CH01", False))
        btn_imou = ft.Button("IMOU Wireless", icon=ft.Icons.WIFI_ROUNDED, style=ft.ButtonStyle(bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH, color=ft.Colors.ON_SURFACE), on_click=lambda _: handle_select_type("rtsp_wireless", "IMOU Wireless Gate", False))
        btn_webcam = ft.Button("PC Webcam", icon=ft.Icons.VIDEOCAM_ROUNDED, style=ft.ButtonStyle(bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH, color=ft.Colors.ON_SURFACE), on_click=lambda _: handle_select_type("webcam", "PC Webcam", False))
        btn_custom = ft.Button("Custom RTSP/SN", icon=ft.Icons.LINK_ROUNDED, style=ft.ButtonStyle(bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH, color=ft.Colors.ON_SURFACE), on_click=lambda _: handle_select_type("p2p_dahua", "Custom RTSP Stream", True))

        type_selector_row = ft.Row([btn_wired, btn_imou, btn_webcam, btn_custom], spacing=6, wrap=True)

        dialog = ft.AlertDialog(
            open=True,
            title=ft.Row([
                ft.Icon(ft.Icons.AUTO_FIX_HIGH_ROUNDED, color=ft.Colors.CYAN_400),
                ft.Text("Step-by-Step Camera Setup Wizard", weight=ft.FontWeight.BOLD, size=16)
            ], spacing=8),
            content=ft.Container(
                width=520,
                padding=10,
                content=ft.Column(
                    tight=True,
                    spacing=12,
                    controls=[
                        ft.Text("Step 1: Choose Hardware Type", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.CYAN_300),
                        type_selector_row,
                        ft.Divider(height=1),
                        ft.Text("Step 2: Connection Settings", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.CYAN_300),
                        name_in,
                        ft.Row([
                            ft.Container(col={"xs": 6}, content=ip_in, expand=True),
                            ft.Container(col={"xs": 6}, content=chan_in, expand=True),
                        ], spacing=8),
                        ft.Row([
                            ft.Container(col={"xs": 6}, content=user_in, expand=True),
                            ft.Container(col={"xs": 6}, content=pass_in, expand=True),
                        ], spacing=8),
                        group_in,
                        ft.Divider(height=1),
                        ft.Text("Step 3: Test & Deploy", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.CYAN_300),
                        ft.Row([
                            ft.Button("⚡ TEST STREAM CONNECTION", icon=ft.Icons.SENSORS_ROUNDED, on_click=test_connection_action),
                        ]),
                        status_container,
                    ]
                )
            ),
            actions=[
                ft.Button("Cancel", on_click=lambda _: page.pop_dialog()),
                ft.Button("SAVE & DEPLOY CAMERA", style=ft.ButtonStyle(bgcolor=ft.Colors.BLUE_700, color=ft.Colors.WHITE), on_click=save_wizard_camera)
            ]
        )
        page.show_dialog(dialog)

    def handle_toggle_camera_ai(cam_item: dict):
        cur_human = bool(cam_item.get("human_detection", 0))
        camera_service.update_camera(
            camera_id=cam_item["id"],
            name=cam_item["name"],
            device_type=cam_item["device_type"],
            source=cam_item["source"],
            camera_group=cam_item.get("camera_group", "Zone-01"),
            detection_model=cam_item.get("detection_model", "yolov8n"),
            motion_detection=cam_item.get("motion_detection", 0),
            human_detection=0 if cur_human else 1,
            telegram_chat_id=cam_item.get("telegram_chat_id", ""),
            telegram_alert_enabled=cam_item.get("telegram_alert_enabled", 0)
        )
        set_refresh_key(refresh_key + 1)
        show_feedback("AI Detection Toggled", f"AI Human Detection for '{cam_item['name']}' turned {'OFF' if cur_human else 'ON'}.", is_success=True)

    # Password Reset Action Handler
    def handle_reset_password(target_username: str):
        success, temp_pw, msg = auth_service.reset_user_password_temp(target_username)
        if success:
            dialog = ft.AlertDialog(
                open=True,
                title=ft.Row([
                    ft.Icon(ft.Icons.KEY_ROUNDED, color=ft.Colors.BLUE_400),
                    ft.Text("Password Reset Successful", weight=ft.FontWeight.BOLD, size=15)
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
                actions=[ft.Button("OK", on_click=lambda _: page.pop_dialog())]
            )
            page.show_dialog(dialog)
        else:
            show_feedback("Reset Failed", msg, is_success=False)

    def handle_create_user(e):
        uname = new_username.strip()
        pwd = new_password.strip()
        success, msg = auth_service.create_user(uname, pwd, new_role)
        if success:
            set_new_username("")
            set_new_password("")
            set_refresh_key(refresh_key + 1)
            show_feedback("User Created", msg, is_success=True)
        else:
            show_feedback("Create User Error", msg, is_success=False)

    # ── Search & Filter Camera Stream Processing ────────────────────────────
    distinct_groups = ["ALL GROUPS"]
    for c in cameras:
        grp = c.get("camera_group", "Zone-01")
        if grp and grp not in distinct_groups:
            distinct_groups.append(grp)

    filtered_cameras = []
    sq = search_query.strip().lower()
    for c in cameras:
        matches_search = (
            not sq or
            sq in c["name"].lower() or
            sq in c["source"].lower() or
            sq in c["device_type"].lower() or
            sq in c.get("camera_group", "").lower()
        )
        matches_group = (selected_group == "ALL GROUPS" or c.get("camera_group") == selected_group)

        if matches_search and matches_group:
            filtered_cameras.append(c)

    # Fetch User List for Operatives Tab
    users_list = auth_service.get_all_users()
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
                        ft.Button(
                            t("reset_pw_btn"),
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
                            ft.Text(t("user_profile_session"), size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                        ], spacing=8),
                        ft.Container(
                            padding=ft.Padding(8, 4, 8, 4),
                            bgcolor=ft.Colors.GREEN_900,
                            border_radius=6,
                            content=ft.Row([
                                ft.Container(width=6, height=6, border_radius=3, bgcolor=ft.Colors.GREEN_400),
                                ft.Text(t("active_session"), size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.WHITE)
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
                                    t("authenticated_account_desc"),
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

    # 2. App Preferences & Localization Card
    localization_card = ft.Container(
        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
        border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
        border_radius=14,
        padding=16,
        content=ft.Column(
            spacing=14,
            controls=[
                ft.Row([
                    ft.Icon(ft.Icons.TRANSLATE_ROUNDED, color=ft.Colors.BLUE_400, size=20),
                    ft.Text(t("app_preferences_localization"), size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                ], spacing=8),
                ft.Divider(height=1),
                ft.Row([
                    ft.Text(t("system_language"), size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE_VARIANT),
                    ft.Dropdown(
                        value=loc_ctx.lang if loc_ctx else "mm",
                        on_select=lambda e: loc_ctx.set_lang(e.control.value) if loc_ctx else None,
                        dense=True,
                        width=180,
                        text_size=12,
                        options=[
                            ft.dropdown.Option("mm", t("lang_mm")),
                            ft.dropdown.Option("en", t("lang_en")),
                            ft.dropdown.Option("zh", t("lang_zh")),
                        ]
                    )
                ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN),
                ft.Divider(height=1),
                ft.Row([
                    ft.Text(t("appearance_theme"), size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE_VARIANT),
                    ft.Row([
                        ft.IconButton(
                            icon=ft.Icons.LIGHT_MODE_ROUNDED,
                            tooltip=t("light_mode"),
                            icon_color=ft.Colors.AMBER_400,
                            on_click=lambda e: theme_ctx.toggle(ft.ThemeMode.LIGHT) if theme_ctx else None
                        ),
                        ft.IconButton(
                            icon=ft.Icons.DARK_MODE_ROUNDED,
                            tooltip=t("dark_mode"),
                            icon_color=ft.Colors.PURPLE_400,
                            on_click=lambda e: theme_ctx.toggle(ft.ThemeMode.DARK) if theme_ctx else None
                        ),
                        ft.IconButton(
                            icon=ft.Icons.SETTINGS_APPLICATIONS,
                            tooltip=t("system_mode"),
                            icon_color=ft.Colors.CYAN_400,
                            on_click=lambda e: theme_ctx.toggle(ft.ThemeMode.SYSTEM) if theme_ctx else None
                        ),
                    ], spacing=4)
                ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN)
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
                    ft.Text(t("security_account_access"), size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                ], spacing=8),
                ft.Divider(height=1),
                ft.ListTile(
                    leading=ft.Icon(ft.Icons.LOCK_OUTLINED, size=20, color=ft.Colors.CYAN_400),
                    title=ft.Text(t("change_pin"), size=13),
                    trailing=ft.Icon(ft.Icons.CHEVRON_RIGHT_ROUNDED, size=18),
                    on_click=lambda _: None,
                ),
                ft.ListTile(
                    leading=ft.Icon(ft.Icons.LOGOUT_ROUNDED, size=20, color=ft.Colors.RED_400),
                    title=ft.Text(t("sign_out_session"), size=13, color=ft.Colors.RED_400, weight=ft.FontWeight.BOLD),
                    trailing=ft.Icon(ft.Icons.CHEVRON_RIGHT_ROUNDED, size=18, color=ft.Colors.RED_400),
                    on_click=lambda e: auth.logout(),
                ),
            ]
        )
    )

    # 4. BOT PROTOCOLS (FRAMELESS 2-COLUMN BALANCED LAYOUT)
    bot_left_column = ft.Column(
        expand=1,
        spacing=14,
        controls=[
            ft.Row([
                ft.Icon(ft.Icons.KEY_ROUNDED, color=ft.Colors.CYAN_400, size=18),
                ft.Text("BOT ACCESS CREDENTIALS", size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE)
            ], spacing=6),
            ft.Text("Enter Telegram Bot Access Token and Default Chat Destination ID.", size=10, color=ft.Colors.ON_SURFACE_VARIANT),
            ft.TextField(
                value=tg_bot_token,
                on_change=lambda e: set_tg_bot_token(e.control.value),
                label=t("telegram_bot_token"),
                hint_text="e.g. 8123456789:AAFg...",
                password=True,
                can_reveal_password=True,
                dense=True,
                text_size=11,
                bgcolor=ft.Colors.SURFACE_CONTAINER_HIGHEST,
                border_color=ft.Colors.OUTLINE_VARIANT
            ),
            ft.TextField(
                value=tg_chat_id,
                on_change=lambda e: set_tg_chat_id(e.control.value),
                label=t("telegram_chat_id_label"),
                hint_text="e.g. -1001234567890 or 123456789",
                dense=True,
                text_size=11,
                bgcolor=ft.Colors.SURFACE_CONTAINER_HIGHEST,
                border_color=ft.Colors.OUTLINE_VARIANT
            ),
            ft.Divider(height=1),
            ft.Row([
                ft.Icon(ft.Icons.PSYCHOLOGY_ROUNDED, color=ft.Colors.CYAN_400, size=18),
                ft.Text("AI VISION & DETECTION ENGINE", size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE)
            ], spacing=6),
            ft.Dropdown(
                value=tg_model,
                on_select=lambda e: set_tg_model(e.control.value),
                label=t("detection_engine_label"),
                dense=True,
                text_size=11,
                bgcolor=ft.Colors.SURFACE_CONTAINER_HIGHEST,
                border_color=ft.Colors.OUTLINE_VARIANT,
                options=[
                    ft.dropdown.Option("yolov8n", "YOLOv8 Nano (Ultra-fast Real-time Human & Fall Detection)"),
                    ft.dropdown.Option("yolov8s", "YOLOv8 Small (High Precision Pose Detection)"),
                    ft.dropdown.Option("mog2", "OpenCV MOG2 (Ultra-fast Motion Subtractor)"),
                    ft.dropdown.Option("gemini-3.6-flash", "Gemini 3.6 Flash (Multimodal AI Scene Analysis)"),
                ]
            ),
            ft.Row([
                ft.OutlinedButton(
                    t("test_connection_btn"),
                    icon=ft.Icons.SEND_ROUNDED,
                    style=ft.ButtonStyle(color=ft.Colors.CYAN_400),
                    on_click=handle_test_telegram_connection,
                    disabled=tg_testing
                ),
                ft.Button(
                    t("save_telegram_setup_btn"),
                    icon=ft.Icons.SAVE_ROUNDED,
                    style=ft.ButtonStyle(bgcolor=ft.Colors.BLUE_700, color=ft.Colors.WHITE),
                    on_click=handle_save_telegram_config
                )
            ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN)
        ]
    )

    bot_right_column = ft.Column(
        expand=1,
        spacing=14,
        controls=[
            ft.Row([
                ft.Icon(ft.Icons.TUNE_ROUNDED, color=ft.Colors.AMBER_400, size=18),
                ft.Text("AUTOMATED ALERT TRIGGERS", size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE)
            ], spacing=6),
            ft.Row([
                ft.Switch(
                    value=tg_enable_motion,
                    on_change=lambda e: set_tg_enable_motion(e.control.value),
                    active_color=ft.Colors.CYAN_400
                ),
                ft.Column([
                    ft.Text(t("enable_motion_alert_label"), size=11, weight=ft.FontWeight.BOLD),
                    ft.Text("Instant photo alert on motion trigger.", size=9, color=ft.Colors.ON_SURFACE_VARIANT)
                ], spacing=1, expand=True)
            ], spacing=8),
            ft.Row([
                ft.Switch(
                    value=tg_enable_human,
                    on_change=lambda e: set_tg_enable_human(e.control.value),
                    active_color=ft.Colors.AMBER_400
                ),
                ft.Column([
                    ft.Text(t("enable_human_alert_label"), size=11, weight=ft.FontWeight.BOLD),
                    ft.Text("Instant photo alert on Human or Fall detection.", size=9, color=ft.Colors.ON_SURFACE_VARIANT)
                ], spacing=1, expand=True)
            ], spacing=8),
            ft.Row([
                ft.Switch(
                    value=tg_ai_listener,
                    on_change=handle_toggle_tg_ai_listener,
                    active_color=ft.Colors.PURPLE_400
                ),
                ft.Column([
                    ft.Text("Telegram Gemini AI Pro Chat Assistant", size=11, weight=ft.FontWeight.BOLD),
                    ft.Text("Operators can chat directly with Gemini AI via Bot.", size=9, color=ft.Colors.ON_SURFACE_VARIANT)
                ], spacing=1, expand=True)
            ], spacing=8),
            ft.Divider(height=1),
            ft.Row([
                ft.Icon(ft.Icons.SHIELD_ROUNDED, color=ft.Colors.GREEN_400, size=18),
                ft.Text("AI SECURITY GUARDRAILS ACTIVE", size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE)
            ], spacing=6),
            ft.Column([
                ft.Row([
                    ft.Icon(ft.Icons.CHECK_CIRCLE_ROUNDED, color=ft.Colors.GREEN_400, size=14),
                    ft.Text("Prompt Injection Shield (DAN / Jailbreak Filter)", size=10, color=ft.Colors.ON_SURFACE_VARIANT)
                ], spacing=6),
                ft.Row([
                    ft.Icon(ft.Icons.CHECK_CIRCLE_ROUNDED, color=ft.Colors.GREEN_400, size=14),
                    ft.Text("Credential Theft Prevention (API Keys & Secrets Protected)", size=10, color=ft.Colors.ON_SURFACE_VARIANT)
                ], spacing=6),
                ft.Row([
                    ft.Icon(ft.Icons.CHECK_CIRCLE_ROUNDED, color=ft.Colors.GREEN_400, size=14),
                    ft.Text("Privileged Admin Session Control", size=10, color=ft.Colors.ON_SURFACE_VARIANT)
                ], spacing=6),
            ], spacing=4)
        ]
    )

    bot_protocols_layout = ft.Column(
        spacing=16,
        controls=[
            ft.Row([
                ft.Icon(ft.Icons.SMART_TOY_ROUNDED, color=ft.Colors.CYAN_400, size=22),
                ft.Text("BOT PROTOCOLS & AI INTEGRATION STUDIO", size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                ft.Container(
                    padding=ft.Padding(6, 2, 6, 2),
                    bgcolor=ft.Colors.GREEN_900,
                    border_radius=4,
                    content=ft.Text("ACTIVE", size=8, weight=ft.FontWeight.BOLD, color=ft.Colors.GREEN_200)
                )
            ], spacing=8),
            ft.Divider(height=1),
            ft.Row(
                controls=[bot_left_column, bot_right_column],
                spacing=28,
                vertical_alignment=ft.CrossAxisAlignment.START
            )
        ]
    )

    # 4a. AI Security Policy Terms & Prompt Injection Guardrails Card
    ai_security_policy_card = ft.Container(
        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
        border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
        border_radius=14,
        padding=16,
        content=ft.Column(
            spacing=12,
            controls=[
                ft.Row(
                    alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                    controls=[
                        ft.Row([
                            ft.Icon(ft.Icons.SECURITY_ROUNDED, color=ft.Colors.AMBER_400, size=22),
                            ft.Text("AI Security Policy Terms & Prompt Injection Guardrails", size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                        ], spacing=8),
                        ft.Container(
                            padding=ft.Padding(8, 3, 8, 3),
                            bgcolor=ft.Colors.AMBER_900,
                            border_radius=6,
                            content=ft.Row([
                                ft.Icon(ft.Icons.SHIELD_ROUNDED, color=ft.Colors.AMBER_400, size=12),
                                ft.Text("GUARDRAILS ACTIVE", size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.AMBER_200)
                            ], spacing=4)
                        )
                    ]
                ),
                ft.Text("Protecting Gemini AI Pro Engine from Prompt Injection Attacks, Credential Exfiltration & Unauthorized Access.", size=11, color=ft.Colors.ON_SURFACE_VARIANT),
                ft.Divider(height=1),
                ft.Container(
                    bgcolor=ft.Colors.SURFACE_CONTAINER,
                    padding=12,
                    border_radius=8,
                    border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
                    content=ft.Column([
                        ft.Row([
                            ft.Icon(ft.Icons.CHECK_CIRCLE_ROUNDED, color=ft.Colors.GREEN_400, size=16),
                            ft.Text("Prompt Injection Filter:", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                            ft.Text("Scans & blocks jailbreak vectors (DAN, ignore rules, bypass safety).", size=11, color=ft.Colors.ON_SURFACE_VARIANT)
                        ], spacing=6),
                        ft.Row([
                            ft.Icon(ft.Icons.CHECK_CIRCLE_ROUNDED, color=ft.Colors.GREEN_400, size=16),
                            ft.Text("Credential Theft Prevention:", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                            ft.Text("Strictly blocks dumping API keys, database passwords, or .env secrets.", size=11, color=ft.Colors.ON_SURFACE_VARIANT)
                        ], spacing=6),
                        ft.Row([
                            ft.Icon(ft.Icons.CHECK_CIRCLE_ROUNDED, color=ft.Colors.GREEN_400, size=16),
                            ft.Text("Privileged User Access Control:", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                            ft.Text("Admin database operations are restricted to verified Admin sessions.", size=11, color=ft.Colors.ON_SURFACE_VARIANT)
                        ], spacing=6),
                        ft.Row([
                            ft.Icon(ft.Icons.CHECK_CIRCLE_ROUNDED, color=ft.Colors.GREEN_400, size=16),
                            ft.Text("System Policy Terms:", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                            ft.Text("Injected into Gemini REST API system_instruction payload.", size=11, color=ft.Colors.ON_SURFACE_VARIANT)
                        ], spacing=6),
                    ], spacing=8)
                )
            ]
        )
    )

    # 4b. Telegram Target Destinations (Users, Channels, Groups) Listing Card
    filtered_tg_targets = [
        t for t in tg_targets
        if not target_search_query.strip() or
        target_search_query.lower() in t.get("target_name", "").lower() or
        target_search_query.lower() in t.get("chat_id", "").lower() or
        target_search_query.lower() in t.get("role", "").lower() or
        target_search_query.lower() in t.get("phone", "").lower() or
        target_search_query.lower() in t.get("note", "").lower()
    ]

    target_tiles = []
    for tgt in filtered_tg_targets:
        ttype = tgt.get("target_type", "user").lower()
        badge_color = ft.Colors.CYAN_600 if ttype == "user" else ft.Colors.BLUE_600 if ttype == "channel" else ft.Colors.PURPLE_600

        target_tiles.append(
            ft.Container(
                width=210,
                height=200,
                bgcolor=ft.Colors.SURFACE_CONTAINER_HIGHEST,
                border_radius=12,
                padding=12,
                border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
                shadow=ft.BoxShadow(
                    blur_radius=6,
                    spread_radius=1,
                    color=ft.Colors.with_opacity(0.08, ft.Colors.BLACK)
                ),
                content=ft.Column([
                    # Top Row: Avatar Initials & Role Badge
                    ft.Row([
                        ft.Stack([
                            ft.CircleAvatar(
                                content=ft.Text(tgt["target_name"][:2].upper(), size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.WHITE),
                                radius=20,
                                bgcolor=ft.Colors.CYAN_700
                            ),
                            ft.Container(
                                width=8, height=8, border_radius=4, bgcolor=ft.Colors.GREEN_400,
                                alignment=ft.Alignment(1, 1)
                            )
                        ]),
                        ft.Column([
                            ft.Container(
                                content=ft.Text(tgt.get("role", "OPERATIVE").upper(), size=8, weight=ft.FontWeight.BOLD, color=ft.Colors.WHITE),
                                bgcolor=badge_color, padding=ft.Padding(5, 1, 5, 1), border_radius=4
                            ),
                            ft.Text(ttype.upper(), size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE_VARIANT)
                        ], spacing=1, horizontal_alignment=ft.CrossAxisAlignment.END, expand=True)
                    ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN),

                    ft.Container(height=2),
                    # Target Name & Username/Chat ID
                    ft.Text(tgt["target_name"], size=13, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE, max_lines=1, overflow=ft.TextOverflow.ELLIPSIS),
                    ft.Text(f"ID: {tgt['chat_id']}", size=10, color=ft.Colors.CYAN_400, weight=ft.FontWeight.BOLD, max_lines=1, overflow=ft.TextOverflow.ELLIPSIS),
                    ft.Text(f"Note: {tgt['note']}" if tgt.get("note") else "No description", size=9, color=ft.Colors.ON_SURFACE_VARIANT, max_lines=2, overflow=ft.TextOverflow.ELLIPSIS, expand=True),

                    ft.Divider(height=1),
                    # Action Toolbar (Edit Profile, View Profile, Send Test, Delete)
                    ft.Row([
                        ft.IconButton(
                            icon=ft.Icons.EDIT_NOTE_ROUNDED,
                            icon_size=17,
                            icon_color=ft.Colors.CYAN_400,
                            tooltip="Edit Target Profile",
                            on_click=lambda e, target=tgt: show_edit_target_dialog(page, target, telegram_service, on_success=lambda: set_refresh_key(refresh_key + 1))
                        ),
                        ft.IconButton(
                            icon=ft.Icons.ACCOUNT_BOX_ROUNDED,
                            icon_size=17,
                            icon_color=ft.Colors.CYAN_400,
                            tooltip="View Details",
                            on_click=lambda e, target=tgt: show_user_profile_dialog(page, target, telegram_service)
                        ),
                        ft.IconButton(
                            icon=ft.Icons.SEND_ROUNDED,
                            icon_size=16,
                            icon_color=ft.Colors.BLUE_400,
                            tooltip="Test Alert",
                            on_click=lambda e, cid=tgt["chat_id"]: handle_test_telegram_connection(e, target_cid=cid)
                        ),
                        ft.IconButton(
                            icon=ft.Icons.DELETE_OUTLINED,
                            icon_size=16,
                            icon_color=ft.Colors.RED_400,
                            tooltip="Delete Target",
                            on_click=lambda e, tid=tgt["id"]: handle_delete_target(tid)
                        )
                    ], spacing=0, alignment=ft.MainAxisAlignment.SPACE_AROUND)
                ], spacing=3)
            )
        )

    telegram_targets_card = ft.Column(
        spacing=14,
        controls=[
            ft.Row(
                alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                controls=[
                    ft.Divider(),
                    ft.Row([
                        ft.Icon(ft.Icons.CONTACT_MAIL_ROUNDED, color=ft.Colors.CYAN_400, size=20),
                        ft.Text("Telegram Alert Recipients & Profiles", size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                    ], spacing=8),
                    ft.Container(
                        padding=ft.Padding(8, 3, 8, 3),
                        bgcolor=ft.Colors.CYAN_900,
                        border_radius=6,
                        content=ft.Text(f"{len(filtered_tg_targets)} Targets Filtered", size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.CYAN_200)
                    )
                ]
            ),
            ft.Text("Manage Telegram User Profiles, Channels, and Groups for AI Detection Snapshot Dispatching.", size=11, color=ft.Colors.ON_SURFACE_VARIANT),
            
            # Search Bar for Telegram Targets
            ft.TextField(
                value=target_search_query,
                on_change=lambda e: set_target_search_query(e.control.value),
                hint_text="Search target name, chat ID, username, or role...",
                hint_style=ft.TextStyle(color=ft.Colors.ON_SURFACE_VARIANT),
                text_style=ft.TextStyle(color=ft.Colors.ON_SURFACE, weight=ft.FontWeight.BOLD),
                prefix_icon=ft.Icons.SEARCH_ROUNDED,
                suffix=ft.IconButton(
                    icon=ft.Icons.CLEAR_ROUNDED,
                    icon_size=15,
                    icon_color=ft.Colors.PRIMARY,
                    on_click=lambda _: set_target_search_query("")
                ) if target_search_query else None,
                dense=True,
                text_size=12,
                border_radius=8,
                bgcolor=ft.Colors.SURFACE_CONTAINER_HIGHEST,
                border_color=ft.Colors.OUTLINE_VARIANT
            ),

            # ft.Divider(height=1),
            ft.Row(controls=target_tiles if target_tiles else [
                ft.Container(
                    padding=12,
                    alignment=ft.Alignment(0, 0),
                    content=ft.Text("No Telegram alert target destinations found matching query.", size=11, color=ft.Colors.ON_SURFACE_VARIANT)
                )
            ], wrap=True, spacing=14, run_spacing=14),
            ft.Divider(height=1),
            ft.Text("Add Telegram Alert Destination Target Profile", size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE),
            ft.ResponsiveRow([
                ft.Container(
                    col={"xs": 12, "md": 6},
                    content=ft.TextField(
                        value=new_target_name,
                        on_change=lambda e: set_new_target_name(e.control.value),
                        label="Target Name / Profile Label",
                        hint_text="e.g. Commander Miller / Duty Security Group",
                        dense=True,
                        text_size=12,
                        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGHEST,
                        border_color=ft.Colors.OUTLINE_VARIANT
                    )
                ),
                ft.Container(
                    col={"xs": 12, "md": 6},
                    content=ft.Dropdown(
                        value=new_target_type,
                        on_select=lambda e: set_new_target_type(e.control.value),
                        label="Target Type",
                        dense=True,
                        text_size=12,
                        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGHEST,
                        border_color=ft.Colors.OUTLINE_VARIANT,
                        options=[
                            ft.dropdown.Option("user", "User Profile / Direct Chat"),
                            ft.dropdown.Option("channel", "Telegram Channel"),
                            ft.dropdown.Option("group", "Telegram Group"),
                        ]
                    )
                ),
            ], spacing=10),
            ft.ResponsiveRow([
                ft.Container(
                    col={"xs": 12, "md": 6},
                    content=ft.TextField(
                        value=new_target_chat_id,
                        on_change=lambda e: set_new_target_chat_id(e.control.value),
                        label="Chat ID / Channel Username / @Handle",
                        hint_text="e.g. 8647823342 or -1001234567890 or @seye_alerts",
                        dense=True,
                        text_size=12,
                        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGHEST,
                        border_color=ft.Colors.OUTLINE_VARIANT
                    )
                ),
                ft.Container(
                    col={"xs": 12, "md": 6},
                    content=ft.TextField(
                        value=new_target_note,
                        on_change=lambda e: set_new_target_note(e.control.value),
                        label="Mission Note / Description",
                        hint_text="e.g. Main Gate Fast Response Alerts",
                        dense=True,
                        text_size=12,
                        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGHEST,
                        border_color=ft.Colors.OUTLINE_VARIANT
                    )
                ),
            ], spacing=10),
            ft.Row([
                ft.Button(
                    "ADD TELEGRAM DESTINATION",
                    icon=ft.Icons.ADD_LINK_ROUNDED,
                    style=ft.ButtonStyle(bgcolor=ft.Colors.CYAN_700, color=ft.Colors.WHITE),
                    on_click=handle_add_target
                )
            ], alignment=ft.MainAxisAlignment.END)
        ]
    )

    # 5. AEGIS Tactical CCTV & Hardware Sources Card (Matches User Reference Screenshot)
    cctv_card_rows = []
    for c in filtered_cameras:
        dev_type = c["device_type"].lower()
        tag_label = "LOCAL SOURCE" if dev_type == "webcam" else "RTSP STREAM" if "rtsp" in dev_type else "OFFLINE" if "p2p" in dev_type else "IP STREAM"
        tag_color = ft.Colors.BLUE_900 if tag_label == "LOCAL SOURCE" else ft.Colors.CYAN_900 if tag_label == "RTSP STREAM" else ft.Colors.SURFACE_CONTAINER_HIGHEST

        cam_icon = ft.Icons.CAMERA_ALT_ROUNDED if dev_type == "webcam" else ft.Icons.WIFI_ROUNDED if dev_type == "rtsp_wireless" else ft.Icons.CABLE_ROUNDED if dev_type == "rtsp_wired" else ft.Icons.VIDEOCAM_OFF_ROUNDED

        sub_info = f"ID: 0x{c['id']:04X} • TYPE: {c['device_type'].upper()}" if dev_type == "webcam" else f"IP: {c['source']} • TYPE: {c['device_type'].upper()}"

        cctv_card_rows.append(
            ft.Container(
                bgcolor=ft.Colors.SURFACE_CONTAINER,
                border_radius=10,
                padding=14,
                border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
                content=ft.Row([
                    # Left Icon Container Box
                    ft.Container(
                        width=46,
                        height=46,
                        border_radius=8,
                        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
                        content=ft.Icon(cam_icon, color=ft.Colors.ON_SURFACE_VARIANT, size=22),
                        alignment=ft.Alignment.CENTER
                    ),
                    # Info Column
                    ft.Column([
                        ft.Row([
                            ft.Text(c["name"], size=13, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                            ft.Container(
                                content=ft.Text(tag_label, size=8, weight=ft.FontWeight.BOLD, color=ft.Colors.BLUE_200),
                                bgcolor=tag_color,
                                padding=ft.Padding(6, 2, 6, 2),
                                border_radius=4
                            )
                        ], spacing=8),
                        ft.Text(sub_info, size=10, color=ft.Colors.ON_SURFACE_VARIANT, font_family=AppFonts.MYANMAR),
                        ft.Row([
                            ft.Container(
                                content=ft.Text(f"MODEL: {c.get('detection_model', 'yolov8n').upper()}", size=8, weight=ft.FontWeight.BOLD, color=ft.Colors.BLUE_200),
                                bgcolor=ft.Colors.BLUE_900, padding=ft.Padding(5, 1, 5, 1), border_radius=4
                            ),
                            ft.Container(
                                content=ft.Text("MOTION: ON" if c.get("motion_detection", 0) else "MOTION: OFF", size=8, weight=ft.FontWeight.BOLD, color=ft.Colors.WHITE),
                                bgcolor=ft.Colors.GREEN_900 if c.get("motion_detection", 0) else ft.Colors.RED_900, padding=ft.Padding(5, 1, 5, 1), border_radius=4
                            ),
                            ft.Container(
                                content=ft.Text("HUMAN: ON" if c.get("human_detection", 0) else "HUMAN: OFF", size=8, weight=ft.FontWeight.BOLD, color=ft.Colors.WHITE),
                                bgcolor=ft.Colors.AMBER_900 if c.get("human_detection", 0) else ft.Colors.RED_900, padding=ft.Padding(5, 1, 5, 1), border_radius=4
                            ),
                            ft.Container(
                                content=ft.Text(f"GROUP: {c.get('camera_group', 'Zone-01').upper()}", size=8, weight=ft.FontWeight.BOLD, color=ft.Colors.CYAN_200),
                                bgcolor=ft.Colors.CYAN_900, padding=ft.Padding(5, 1, 5, 1), border_radius=4
                            ),
                        ], spacing=6)
                    ], spacing=4, expand=True),
                    # Action Buttons
                    ft.Row([
                        ft.IconButton(
                            icon=ft.Icons.PERSON_SEARCH_ROUNDED,
                            icon_size=18,
                            icon_color=ft.Colors.GREEN_400 if c.get("human_detection", 0) else ft.Colors.ON_SURFACE_VARIANT,
                            tooltip="Turn AI Detection " + ("OFF" if c.get("human_detection", 0) else "ON"),
                            on_click=lambda e, target_cam=c: handle_toggle_camera_ai(target_cam)
                        ),
                        ft.IconButton(
                            icon=ft.Icons.EDIT_OUTLINED,
                            icon_size=18,
                            icon_color=ft.Colors.ON_SURFACE_VARIANT,
                            tooltip="Edit Camera Setup",
                            on_click=lambda e, target_cam=c: set_editing_cam(target_cam)
                        ),
                        ft.IconButton(
                            icon=ft.Icons.DELETE_OUTLINED,
                            icon_size=18,
                            icon_color=ft.Colors.RED_300,
                            tooltip="Delete Camera Setup",
                            on_click=lambda e, target_cam=c: handle_confirm_delete_camera(target_cam)
                        )
                    ], spacing=2)
                ])
            )
        )

    cctv_config_card = ft.Container(
        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
        border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
        border_radius=14,
        padding=18,
        content=ft.Column(
            spacing=16,
            controls=[
                # Header Section
                ft.Row([
                    ft.Icon(ft.Icons.VIDEOCAM_ROUNDED, color=ft.Colors.BLUE_400, size=20),
                    ft.Column([
                        ft.Text("CCTV & HARDWARE SOURCES", size=13, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                        ft.Text("Manage operational PC Webcams, Wireless IP CCTV (RTSP) & Wired Surveillance Streams.", size=10, color=ft.Colors.ON_SURFACE_VARIANT),
                    ], spacing=2, expand=True)
                ], spacing=10),
                ft.Divider(height=1),

                # Search Bar & Group Filter (Requested)
                ft.ResponsiveRow([
                    ft.Container(
                        col={"xs": 12, "md": 7},
                        content=ft.TextField(
                            value=search_query,
                            on_change=lambda e: set_search_query(e.control.value),
                            hint_text="Search CCTV Name, Source URL, Type or Group...",
                            prefix_icon=ft.Icons.SEARCH_ROUNDED,
                            dense=True,
                            text_size=12
                        )
                    ),
                    ft.Container(
                        col={"xs": 12, "md": 5},
                        content=ft.Dropdown(
                            value=selected_group,
                            on_select=lambda e: set_selected_group(e.control.value),
                            label="Filter by Group / Zone",
                            dense=True,
                            text_size=12,
                            options=[ft.dropdown.Option(g, g) for g in distinct_groups]
                        )
                    ),
                ], spacing=10),

                # Camera Stream Cards List
                ft.Column(
                    controls=cctv_card_rows if cctv_card_rows else [
                        ft.Container(
                            padding=20,
                            content=ft.Text("No CCTV Camera streams found matching search criteria.", size=11, color=ft.Colors.ON_SURFACE_VARIANT)
                        )
                    ],
                    spacing=10
                ),
                ft.Divider(height=1),

                # Initialize New Hardware Source Form
                ft.Row([
                    ft.Icon(ft.Icons.ADD_CIRCLE_OUTLINE_ROUNDED, color=ft.Colors.BLUE_400, size=18),
                    ft.Text("INITIALIZE / EDIT HARDWARE SOURCE", size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                ], spacing=8),

                # Existing DB Cameras Picker Dropdown for 1-Click Select & Auto-Fill
                ft.Container(
                    padding=ft.Padding(0, 0, 0, 4),
                    content=ft.Dropdown(
                        label="⚡ QUICK SELECT SAVED CAMERA / SN FROM DATABASE (AUTO-FILL)",
                        hint_text="Select any camera stored in Database to auto-fill details...",
                        dense=True,
                        text_size=11,
                        options=[
                            ft.dropdown.Option(
                                str(c["id"]),
                                f"[{c.get('camera_group', 'Zone-01')}] {c['name']} - ({c['source']})"
                            ) for c in cameras
                        ],
                        on_select=lambda e: (
                            next((
                                (
                                    set_cam_name(c["name"]),
                                    set_cam_source(c["source"]),
                                    set_cam_group(c.get("camera_group", "Zone-01")),
                                    set_cam_type(c.get("device_type", "p2p_dahua"))
                                ) for c in cameras if str(c["id"]) == e.control.value
                            ), None)
                        )
                    )
                ),

                ft.ResponsiveRow([
                    ft.Container(
                        col={"xs": 12, "md": 4},
                        content=ft.TextField(
                            value=cam_name,
                            on_change=lambda e: set_cam_name(e.control.value),
                            label="CAMERA NAME",
                            hint_text="e.g. Backdoor Wireless CCTV",
                            dense=True,
                            text_size=11
                        )
                    ),
                    ft.Container(
                        col={"xs": 12, "md": 4},
                        content=ft.Dropdown(
                            value=cam_type,
                            on_select=lambda e: set_cam_type(e.control.value),
                            label="INTERFACE TYPE",
                            dense=True,
                            text_size=11,
                            options=[
                                ft.dropdown.Option("webcam", "PC Webcam (Local)"),
                                ft.dropdown.Option("rtsp_wireless", "Wireless IP CCTV (RTSP)"),
                                ft.dropdown.Option("rtsp_wired", "Wired CCTV (RTSP)"),
                                ft.dropdown.Option("p2p_dahua", "Dahua P2P Cloud (Serial)"),
                            ]
                        )
                    ),
                    ft.Container(
                        col={"xs": 12, "md": 4},
                        content=ft.TextField(
                            value=cam_group,
                            on_change=lambda e: set_cam_group(e.control.value),
                            label="OPERATIONAL TAG / GROUP",
                            hint_text="e.g. DEPT: SURV-01 or Zone-01",
                            dense=True,
                            text_size=11
                        )
                    ),
                ], spacing=10),

                ft.TextField(
                    value=cam_source,
                    on_change=lambda e: set_cam_source(e.control.value),
                    label="SOURCE LINK (INDEX / RTSP URL / SERIAL)",
                    hint_text="rtsp://admin:pass@192.168.1.1:554/live or 0",
                    dense=True,
                    text_size=11
                ),

                ft.Row([
                    ft.Button(
                        "✨ STEP-BY-STEP SETUP WIZARD",
                        icon=ft.Icons.AUTO_FIX_HIGH_ROUNDED,
                        style=ft.ButtonStyle(
                            bgcolor=ft.Colors.BLUE_900,
                            color=ft.Colors.CYAN_200,
                            padding=ft.Padding(14, 10, 14, 10)
                        ),
                        tooltip="Open step-by-step camera setup wizard with live connection testing",
                        on_click=handle_open_step_by_step_wizard
                    ),
                    ft.Button(
                        "🔑 ADD BY SERIAL (SN)",
                        icon=ft.Icons.QR_CODE_ROUNDED,
                        style=ft.ButtonStyle(
                            bgcolor=ft.Colors.PURPLE_900,
                            color=ft.Colors.PURPLE_200,
                            padding=ft.Padding(14, 10, 14, 10)
                        ),
                        tooltip="Easily add any Wired or Wireless CCTV camera by typing its Serial Number (SN)",
                        on_click=handle_open_quick_sn_dialog
                    ),
                    ft.Button(
                        "⚡ BULK IMPORT WIRED NVR",
                        icon=ft.Icons.ROUTER_ROUNDED,
                        style=ft.ButtonStyle(
                            bgcolor=ft.Colors.CYAN_900,
                            color=ft.Colors.CYAN_200,
                            padding=ft.Padding(14, 10, 14, 10)
                        ),
                        tooltip="Bulk import/update all Wired NVR CCTV channels (CH01-CH16) into Database",
                        on_click=handle_open_wired_import_dialog
                    ),
                    ft.Button(
                        "🧹 PURGE ALL",
                        icon=ft.Icons.DELETE_SWEEP_ROUNDED,
                        style=ft.ButtonStyle(
                            bgcolor=ft.Colors.RED_900,
                            color=ft.Colors.WHITE,
                            padding=ft.Padding(12, 10, 12, 10)
                        ),
                        tooltip="Clear all old/stale camera entries from database registry to start fresh",
                        on_click=handle_purge_all_cameras
                    ),
                    ft.Button(
                        "DEPLOY SOURCE",
                        icon=ft.Icons.SEND_ROUNDED,
                        style=ft.ButtonStyle(
                            bgcolor=ft.Colors.BLUE_700,
                            color=ft.Colors.WHITE,
                            padding=ft.Padding(16, 12, 16, 12)
                        ),
                        on_click=handle_add_camera
                    )
                ], alignment=ft.MainAxisAlignment.END, spacing=8, wrap=True)
            ]
        )
    )

    # 6. Admin User Studio Card (Rendered ONLY if user is admin)
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
                            ft.Text(t("user_management_studio"), size=14, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                        ], spacing=8),
                        ft.Container(
                            padding=ft.Padding(8, 3, 8, 3),
                            bgcolor=ft.Colors.PURPLE_900,
                            border_radius=6,
                            content=ft.Text(t("admin_only"), size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.PURPLE_200)
                        )
                    ]
                ),
                ft.Text(t("user_management_desc"), size=11, color=ft.Colors.ON_SURFACE_VARIANT),
                ft.Divider(height=1),
                ft.Text(t("create_new_account"), size=12, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE),
                ft.ResponsiveRow([
                    ft.Container(
                        col={"xs": 12, "md": 6},
                        content=ft.TextField(
                            value=new_username,
                            on_change=lambda e: set_new_username(e.control.value),
                            label=t("username_label"),
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
                            label=t("password_label"),
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
                        label=t("system_role"),
                        dense=True,
                        text_size=12,
                        expand=True,
                        options=[
                            ft.dropdown.Option("operator", "Operator (Standard Access)"),
                            ft.dropdown.Option("admin", "Administrator (Full Access)"),
                        ]
                    ),
                    ft.Button(
                        t("create_user_btn"),
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
                ft.Row([
                    ft.Text(t("registered_accounts"), size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE),
                    ft.Text(f"{len(users_list)} Accounts", size=11, color=ft.Colors.ON_SURFACE_VARIANT, weight=ft.FontWeight.BOLD)
                ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN),
                ft.Column(controls=user_rows, spacing=8)
            ]
        )
    )

    # ── AEGIS Tab Header Buttons Matching User Screenshot ───────────────────
    tab_items = [
        {"index": 0, "label": "PREFERENCES", "icon": ft.Icons.TUNE_ROUNDED},
        {"index": 1, "label": "BOT PROTOCOLS", "icon": ft.Icons.TELEGRAM_ROUNDED},
        {"index": 2, "label": "CCTV SOURCES", "icon": ft.Icons.VIDEOCAM_ROUNDED},
        {"index": 4, "label": "TARGET FACES", "icon": ft.Icons.FACE_UNLOCK_ROUNDED},
    ]

    if user and user.is_admin():
        tab_items.append({"index": 3, "label": "OPERATIVES", "icon": ft.Icons.PERSON_ROUNDED})

    tab_buttons = []
    for item in tab_items:
        is_active = (active_tab == item["index"])
        tab_buttons.append(
            ft.Container(
                content=ft.Row([
                    ft.Icon(
                        item["icon"],
                        size=15,
                        color=ft.Colors.WHITE if is_active else ft.Colors.ON_SURFACE
                    ),
                    ft.Text(
                        item["label"],
                        size=11,
                        weight=ft.FontWeight.BOLD,
                        color=ft.Colors.WHITE if is_active else ft.Colors.ON_SURFACE
                    )
                ], spacing=6, alignment=ft.MainAxisAlignment.CENTER),
                padding=ft.Padding(16, 9, 16, 9),
                border_radius=6,
                bgcolor=ft.Colors.BLUE_700 if is_active else ft.Colors.SURFACE_CONTAINER_HIGH,
                border=None if is_active else ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
                on_click=lambda e, idx=item["index"]: set_active_tab(idx)
            )
        )

    # Render body content according to active tab index
    if active_tab == 0:
        tab_body = ft.Column(
            spacing=14,
            scroll=ft.ScrollMode.HIDDEN,
            controls=[bot_protocols_layout,profile_card, localization_card, security_card]
        )
    elif active_tab == 1:
        tab_body = ft.Column(
            spacing=16,
            scroll=ft.ScrollMode.HIDDEN,
            controls=[ telegram_targets_card, ModelSelector()]
        )
    elif active_tab == 2:
        tab_body = ft.Column(
            spacing=14,
            scroll=ft.ScrollMode.HIDDEN,
            controls=[cctv_config_card]
        )
    elif active_tab == 4:
        tab_body = ft.Column(
            spacing=14,
            scroll=ft.ScrollMode.HIDDEN,
            controls=[TargetFaceManager()]
        )
    elif active_tab == 3 and user and user.is_admin():
        tab_body = ft.Column(
            spacing=14,
            scroll=ft.ScrollMode.HIDDEN,
            controls=[admin_studio_card]
        )
    else:
        tab_body = ft.Container()


    return ft.Container(
        expand=True,
        padding=16,
        content=ft.Column(
            spacing=14,
            expand=True,
            scroll=ft.ScrollMode.HIDDEN,
            controls=[
                # Render Edit Camera Modal if active
                EditCameraModal(
                    cam_item=editing_cam,
                    on_close=lambda: set_editing_cam(None),
                    on_saved=lambda: set_refresh_key(refresh_key + 1)
                ) if editing_cam else ft.Container(),

                # AEGIS Breadcrumb & Header Section
                ft.Container(
                    padding=ft.Padding(0, 0, 0, 4),
                    content=ft.Column([
                        ft.Row([
                            ft.Text("SYSTEM CONTROL CENTER", size=10, color=ft.Colors.BLUE_600, weight=ft.FontWeight.BOLD),
                            ft.Text(">", size=10, color=ft.Colors.OUTLINE),
                            ft.Text("HARDWARE ARCHITECTURE", size=10, color=ft.Colors.BLUE, weight=ft.FontWeight.BOLD),
                        ], spacing=6),
                        ft.Row(
                            alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                            controls=[
                                ft.Text("SETTINGS & CONFIGURATIONS", size=22, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE),
                                ft.Row(controls=tab_buttons, spacing=8)
                            ]
                        )
                    ], spacing=6)
                ),
                # ft.Divider(height=1),

                # Active Tab Body
                ft.Container(
                    expand=True,
                    content=tab_body
                )
            ]
        )
    )