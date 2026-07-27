import flet as ft
from core.helper import use_localization_context
from config import logger

@ft.component
def LanguageSwitcher():
    loc_ctx = use_localization_context()
    current_lang = loc_ctx.lang if loc_ctx else "en"
    
    def on_lang_change(e):
        if loc_ctx:
            loc_ctx.set_lang(e.control.data)
            logger.info(f"Language switcher changed language to: {e.control.data}")
            
    def get_current_lang_name():
        if current_lang == "mm":
            return "မြန်မာ"
        if current_lang == "zh":
            return "中文"
        return "English"
        
    def get_current_flag():
        if current_lang == "mm":
            return "🇲🇲"
        if current_lang == "zh":
            return "🇨🇳"
        return "🇺🇸"

    return ft.PopupMenuButton(
        content=ft.Container(
            content=ft.Row(
                spacing=8,
                alignment=ft.MainAxisAlignment.CENTER,
                controls=[
                    ft.Container(
                        content=ft.Text(get_current_flag(), size=16),
                        alignment=ft.Alignment(0, 0),
                        width=24,
                        height=24,
                        border_radius=12,
                        bgcolor=ft.Colors.SECONDARY,
                    ),
                    ft.Text(
                        value=get_current_lang_name(),
                        size=14,
                        color=ft.Colors.BLUE_900,
                        weight=ft.FontWeight.W_600,
                    ),
                    ft.Icon(
                        ft.Icons.KEYBOARD_ARROW_DOWN_ROUNDED,
                        size=18,
                        color=ft.Colors.BLUE_900,
                    )
                ]
            ),
            padding=ft.Padding(12, 8, 12, 8),
            bgcolor=ft.Colors.SURFACE_CONTAINER_LOW,
            border=ft.Border.all(width=1, color=ft.Colors.BLUE_100),
            border_radius=10,
            shadow=ft.BoxShadow(
                spread_radius=0,
                blur_radius=4,
                color=ft.Colors.with_opacity(0.05, ft.Colors.SHADOW),
                offset=ft.Offset(0, 2),
            ),
        ),
        items=[
            ft.PopupMenuItem(
                content=ft.Row(
                    spacing=10,
                    controls=[
                        ft.Text("🇲🇲", size=16),
                        ft.Text("မြန်မာ (Myanmar)", size=14, weight=ft.FontWeight.W_500),
                    ]
                ),
                data="mm", 
                on_click=on_lang_change,
                checked=(current_lang == "mm")
            ),
            ft.PopupMenuItem(
                content=ft.Row(
                    spacing=10,
                    controls=[
                        ft.Text("🇺🇸", size=16),
                        ft.Text("English (US)", size=14, weight=ft.FontWeight.W_500),
                    ]
                ),
                data="en", 
                on_click=on_lang_change,
                checked=(current_lang == "en")
            ),
            ft.PopupMenuItem(
                content=ft.Row(
                    spacing=10,
                    controls=[
                        ft.Text("🇨🇳", size=16),
                        ft.Text("中文 (Chinese)", size=14, weight=ft.FontWeight.W_500),
                    ]
                ),
                data="zh", 
                on_click=on_lang_change,
                checked=(current_lang == "zh")
            ),
        ]
    )
