# src/views/loginView.py
import flet as ft
import asyncio
from config import logger
from views.components.typography import AppText
from views.components.language_switcher import LanguageSwitcher
from views.components.terminal_info import TerminalInfo
from views.components.clock import Clock
from views.components.status_indicator import StatusIndicator
from core.helper import use_loc
from core.auth_context import use_auth  # auth hook


# ─── Layout Breakpoints ─────────────────────────────────────────────────────
def _get_layout(width: float, height: float) -> dict:
    if width <= 1024 or height <= 720:
        return dict(
            card_width=320, card_padding=24,
            btn_width=70, btn_height=50, btn_font=16,
            logo_size=36, circle_size=13, circle_radius=6,
            card_spacing=8, outer_padding=16, gap=12
        )
    elif width <= 1440 or height <= 900:
        return dict(
            card_width=400, card_padding=40,
            btn_width=90, btn_height=60, btn_font=20,
            logo_size=50, circle_size=16, circle_radius=8,
            card_spacing=10, outer_padding=20, gap=20
        )
    else:
        return dict(
            card_width=480, card_padding=52,
            btn_width=110, btn_height=72, btn_font=24,
            logo_size=64, circle_size=20, circle_radius=10,
            card_spacing=14, outer_padding=28, gap=28
        )


# ─── LoginView Component ────────────────────────────────────────────────────
@ft.component
def loginView():
    logger.info("Rendering loginView component...")
    loc = use_loc()
    page = ft.context.page
    
    # ⭐ Use auth context instead of local auth service
    auth = use_auth()
    
    # ─── Local State ────────────────────────────────────────────────────────
    pin, set_pin = ft.use_state("")
    card_scale, set_card_scale = ft.use_state(1.0)
    
    # Window size
    win_w, set_win_w = ft.use_state(page.width or 1920.0)
    win_h, set_win_h = ft.use_state(page.height or 1080.0)
    
    # ─── Resize Handler ─────────────────────────────────────────────────────
    def resize_effect():
        def on_resize(e: ft.PageResizeEvent):
            set_win_w(e.width)
            set_win_h(e.height)
        page.on_resize = on_resize
        
        def cleanup():
            page.on_resize = None
        return cleanup
    
    ft.use_effect(resize_effect, [])
    
    # ─── PIN Authentication ─────────────────────────────────────────────────
    async def process_login(entered_pin: str):
        logger.info("process_login called with pin")
        success = auth.get("login")("admin", entered_pin)   # sync — returns bool
        logger.info(f"success is {success}")
        if success:
            # Yield to let Flet flush the state update (set_user) before navigating.
            # Without this, ProtectedRoute may still see is_authenticated=False.
            await asyncio.sleep(0.05)
            logger.info("Login successful, navigating to /dashboard")
            page.navigate("/home")
        else:
            set_pin("")  # Clear PIN on failure
    
    # ─── Error Display ──────────────────────────────────────────────────────
    error_text = auth.get("error", "")
    is_loading = auth.get("is_loading", False)
    
    # ─── PIN Animation Effect ───────────────────────────────────────────────
    def handle_pin_animation():
        if len(pin) == 4:
            set_card_scale(1.05)
            page.run_task(process_login, pin)
        else:
            set_card_scale(1.0)
            # Clear error when user starts typing again
            if auth.get("error") and len(pin) > 0:
                auth.get("clear_error")()
    
    ft.use_effect(handle_pin_animation, [pin])
    
    # ─── Layout Values ──────────────────────────────────────────────────────
    L = _get_layout(win_w, win_h)
    
    # ─── Numpad Handlers ────────────────────────────────────────────────────
    def on_number_click(number: str):
        if len(pin) < 4 and not auth.get("is_loading"):
            set_pin(pin + number)
    
    def on_clear_click(e):
        if not auth.get("is_loading"):
            set_pin("")
            auth.get("clear_error")()
    
    def on_backspace_click(e):
        if len(pin) > 0 and not auth.get("is_loading"):
            set_pin(pin[:-1])
    
    def border_all(width, color):
        side = ft.BorderSide(width, color)
        return ft.Border(top=side, right=side, bottom=side, left=side)
    
    # ─── PIN Circles ────────────────────────────────────────────────────────
    circles = [
        ft.Container(
            width=L["circle_size"],
            height=L["circle_size"],
            border_radius=L["circle_radius"],
            border=border_all(2, ft.Colors.BLUE_900) if i >= len(pin) else None,
            bgcolor=ft.Colors.BLUE_900 if i < len(pin) else None,
            animate=ft.Animation(duration=200, curve=ft.AnimationCurve.EASE_OUT),
        )
        for i in range(4)
    ]
    
    # ─── Numpad Button Factory ──────────────────────────────────────────────
    def numpad_button(text, on_click, is_icon=False, is_clear=False):
        if is_icon:
            content = ft.Icon(ft.Icons.BACKSPACE_OUTLINED, color=ft.Colors.BLUE_900, size=L["btn_font"])
        elif is_clear:
            content = ft.Text(text, size=L["btn_font"] - 5, weight=ft.FontWeight.BOLD, color=ft.Colors.BLUE_900)
        else:
            content = ft.Text(text, size=L["btn_font"], weight=ft.FontWeight.BOLD, color=ft.Colors.BLUE_900)
        
        return ft.Container(
            content=content,
            alignment=ft.Alignment(0, 0),
            width=L["btn_width"],
            height=L["btn_height"],
            border_radius=8,
            bgcolor=ft.Colors.BLUE_50,
            on_click=on_click if not auth.get("is_loading") else None,
            ink=True if not auth.get("is_loading") else False,
            animate=ft.Animation(duration=100, curve=ft.AnimationCurve.EASE_IN_OUT),
        )
    
    # ─── Numpad Grid ────────────────────────────────────────────────────────
    numpad = ft.Column(
        spacing=L["card_spacing"],
        controls=[
            ft.Row(spacing=L["card_spacing"], alignment=ft.MainAxisAlignment.CENTER, controls=[
                numpad_button("1", lambda e: on_number_click("1")),
                numpad_button("2", lambda e: on_number_click("2")),
                numpad_button("3", lambda e: on_number_click("3")),
            ]),
            ft.Row(spacing=L["card_spacing"], alignment=ft.MainAxisAlignment.CENTER, controls=[
                numpad_button("4", lambda e: on_number_click("4")),
                numpad_button("5", lambda e: on_number_click("5")),
                numpad_button("6", lambda e: on_number_click("6")),
            ]),
            ft.Row(spacing=L["card_spacing"], alignment=ft.MainAxisAlignment.CENTER, controls=[
                numpad_button("7", lambda e: on_number_click("7")),
                numpad_button("8", lambda e: on_number_click("8")),
                numpad_button("9", lambda e: on_number_click("9")),
            ]),
            ft.Row(spacing=L["card_spacing"], alignment=ft.MainAxisAlignment.CENTER, controls=[
                numpad_button("Clear", on_clear_click, is_clear=True),
                numpad_button("0", lambda e: on_number_click("0")),
                numpad_button("", on_backspace_click, is_icon=True),
            ]),
        ],
    )
    
    # ─── UI Sections ────────────────────────────────────────────────────────
    top_bar = ft.Row(
        alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
        controls=[
            TerminalInfo(),
            ft.Row(
                spacing=12,
                vertical_alignment=ft.CrossAxisAlignment.CENTER,
                controls=[Clock(), ft.Container(width=1, height=16, bgcolor=ft.Colors.OUTLINE_VARIANT), StatusIndicator()]
            ),
        ],
    )
    
    bottom_bar = ft.Row(
        alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
        controls=[
            ft.Column(
                spacing=2,
                controls=[
                    AppText("version", variant="caption", color=ft.Colors.ON_SURFACE_VARIANT, weight=ft.FontWeight.BOLD),
                    AppText("copyright", variant="caption", color=ft.Colors.ON_SURFACE_VARIANT),
                ]
            ),
            ft.Row(
                spacing=10,
                controls=[
                    LanguageSwitcher(),
                    ft.Button(
                        content=ft.Row(spacing=5, controls=[
                            ft.Icon(ft.Icons.HELP_OUTLINE, size=16),
                            AppText("support", variant="body")
                        ]),
                        style=ft.ButtonStyle(bgcolor=ft.Colors.BLUE_50, color=ft.Colors.BLUE_900, shape=ft.RoundedRectangleBorder(radius=8))
                    ),
                    ft.Button(
                        content=ft.Row(spacing=5, controls=[
                            ft.Icon(ft.Icons.CHAT, size=16),
                            AppText("ask_ai", variant="body")
                        ]),
                        style=ft.ButtonStyle(bgcolor=ft.Colors.BLUE_50, color=ft.Colors.BLUE_900, shape=ft.RoundedRectangleBorder(radius=8))
                    ),
                ],
            ),
        ],
    )
    
    # ─── PIN Card with Auth States ──────────────────────────────────────────
    pin_card = ft.Container(
        key="pin_entry",
        width=L["card_width"],
        padding=L["card_padding"],
        border_radius=16,
        scale=card_scale,
        animate_scale=ft.Animation(duration=600, curve=ft.AnimationCurve.BOUNCE_OUT),
        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGHEST,
        shadow=ft.BoxShadow(
            spread_radius=1, blur_radius=15,
            color=ft.Colors.with_opacity(0.1, ft.Colors.SHADOW),
            offset=ft.Offset(0, 5)
        ),
        content=ft.Column(
            horizontal_alignment=ft.CrossAxisAlignment.CENTER,
            controls=[
                ft.Row(alignment=ft.MainAxisAlignment.CENTER, spacing=20, controls=circles),
                ft.Container(height=L["gap"] / 2),
                
                # ⭐ Loading indicator from auth context
                ft.ProgressRing(width=20, height=20, visible=auth.get("is_loading")),
                
                # ⭐ Error message from auth context
                ft.Text(
                    error_text or "",
                    color=ft.Colors.ERROR,
                    size=12,
                    visible=bool(error_text)
                ),
                
                ft.Container(height=L["gap"] / 2),
                numpad,
                ft.Container(height=L["gap"]),
                ft.TextButton(
                    content=ft.Row(
                        alignment=ft.MainAxisAlignment.CENTER,
                        spacing=5,
                        controls=[
                            ft.Icon(ft.Icons.SWITCH_ACCOUNT, size=16, color=ft.Colors.ON_SURFACE_VARIANT),
                            AppText("switch_login", variant="body", color=ft.Colors.ON_SURFACE_VARIANT),
                        ]
                    ),
                ),
            ],
        ),
    )
    
    return ft.Container(
        expand=True,
        padding=L["outer_padding"],
        bgcolor=ft.Colors.SURFACE,
        content=ft.Column(
            alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
            controls=[
                top_bar,
                ft.Column(
                    horizontal_alignment=ft.CrossAxisAlignment.CENTER,
                    spacing=10,
                    controls=[
                        ft.Image(src="images/logo.png", width=L["logo_size"], fit=ft.BoxFit.CONTAIN),
                        AppText("app_title", variant="h1", color=ft.Colors.BLUE_900, weight=ft.FontWeight.BOLD),
                        AppText("subtitle", variant="body", color=ft.Colors.ON_SURFACE_VARIANT),
                        ft.Container(height=L["gap"]),
                        pin_card,
                    ],
                ),
                bottom_bar,
            ],
        ),
    )