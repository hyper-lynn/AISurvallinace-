# src/views/components/model_selector.py

import flet as ft
from services.ai_service import AVAILABLE_MODELS, get_active_model, set_active_model
from config.fonts import AppFonts

@ft.component
def ModelSelector(compact: bool = False, on_model_changed = None):
    page = ft.context.page
    active_model = get_active_model()
    current_model, set_current_model = ft.use_state(active_model)

    def handle_select(e):
        selected_id = e.control.data
        set_active_model(selected_id)
        set_current_model(selected_id)
        if on_model_changed:
            on_model_changed(selected_id)
        page.show_dialog(
            ft.SnackBar(
                content=ft.Text(f"Active Gemini Model: '{selected_id}'", font_family=AppFonts.MYANMAR),
                bgcolor=ft.Colors.GREEN_700,
                duration=2500
            )
        )

    # Find display name for active model
    active_name = current_model
    for m in AVAILABLE_MODELS:
        if m["id"] == current_model:
            active_name = m["name"].split(" (")[0]
            break

    items = []
    for m in AVAILABLE_MODELS:
        is_selected = (m["id"] == current_model)
        items.append(
            ft.PopupMenuItem(
                content=ft.Row(
                    controls=[
                        ft.Icon(
                            ft.Icons.CHECK_ROUNDED if is_selected else ft.Icons.MEMORY_ROUNDED,
                            size=16,
                            color=ft.Colors.BLUE_600 if is_selected else ft.Colors.ON_SURFACE_VARIANT
                        ),
                        ft.Text(
                            m["name"],
                            size=12,
                            weight=ft.FontWeight.BOLD if is_selected else ft.FontWeight.NORMAL,
                            color=ft.Colors.BLUE_600 if is_selected else ft.Colors.ON_SURFACE,
                            overflow=ft.TextOverflow.ELLIPSIS,
                            max_lines=1,
                            expand=True
                        )
                    ],
                    spacing=8,
                    alignment=ft.MainAxisAlignment.START
                ),
                data=m["id"],
                on_click=handle_select,
                checked=is_selected
            )
        )

    if compact:
        # Compact style for Headers & Overlay Chat Window
        return ft.PopupMenuButton(
            tooltip="Select Gemini Model",
            content=ft.Container(
                padding=ft.Padding(8, 4, 8, 4),
                bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
                border_radius=12,
                border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
                content=ft.Row([
                    ft.Icon(ft.Icons.AUTO_AWESOME_ROUNDED, size=13, color=ft.Colors.BLUE_600),
                    ft.Text(
                        active_name,
                        size=11,
                        weight=ft.FontWeight.BOLD,
                        overflow=ft.TextOverflow.ELLIPSIS,
                        max_lines=1
                    ),
                    ft.Icon(ft.Icons.ARROW_DROP_DOWN_ROUNDED, size=16)
                ], spacing=4, alignment=ft.MainAxisAlignment.CENTER)
            ),
            items=items
        )

    # Full Card style for Settings View
    return ft.PopupMenuButton(
        tooltip="Change Gemini AI Model",
        content=ft.Container(
            padding=ft.Padding(14, 10, 14, 10),
            bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
            border_radius=12,
            border=ft.Border.all(1, ft.Colors.BLUE_600),
            content=ft.Row([
                ft.Row([
                    ft.Icon(ft.Icons.MEMORY_ROUNDED, size=18, color=ft.Colors.BLUE_600),
                    ft.Text(
                        f"Current Model: {active_name}",
                        size=13,
                        weight=ft.FontWeight.BOLD,
                        overflow=ft.TextOverflow.ELLIPSIS,
                        max_lines=1
                    )
                ], spacing=8, expand=True),
                ft.Row([
                    ft.Text("Change", size=12, color=ft.Colors.BLUE_600, weight=ft.FontWeight.BOLD),
                    ft.Icon(ft.Icons.KEYBOARD_ARROW_DOWN_ROUNDED, size=18, color=ft.Colors.BLUE_600)
                ], spacing=4)
            ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN)
        ),
        items=items
    )
