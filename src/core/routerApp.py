# src/core/routerApp.py
import flet as ft
from config import logger
from models.app_route_model import (
    ThemeContext, ThemeContextModel,
    LocalizationContext, LocalizationContextModel
)
from config.localization import LocalizationManager
from core.auth_provider import build_auth_state          # ← plain helper, not a component
from core.auth_context import AuthContext, use_auth      # ← context object + hook
from views.loginView import loginView
from views.components.pageWrapper import create_page_wrapper
from views.homeView import homeView
from views.aboutView import aboutView
from views.settingsView import settingsView
from core.appLayout import rootLayout
from views.View404 import View404
from views.dashboardView import dashboardView
from views.aiChatView import aiChatView
from views.liveMonitorView import liveMonitorView



# ─── Route Guard Component ──────────────────────────────────────────────────
@ft.component
def ProtectedRoute(children: list, required_role: str = None):
    """
    Route guard that redirects unauthenticated users to login.
    Optionally checks for a specific role.
    """
    auth = use_auth()
    page = ft.context.page

    # Not authenticated → redirect to login
    if not auth.is_authenticated:
        logger.warning("Unauthenticated access attempt, redirecting to login")
        ft.use_effect(lambda: page.navigate("/"), [])
        return ft.Container()   # empty while redirecting

    # Role check
    if required_role and not auth.user.has_role(required_role):
        logger.warning(
            f"Role '{required_role}' required, user has '{auth.user.role}'"
        )
        return ft.Container(
            content=ft.Column(
                alignment=ft.MainAxisAlignment.CENTER,
                horizontal_alignment=ft.CrossAxisAlignment.CENTER,
                controls=[
                    ft.Icon(ft.Icons.LOCK_OUTLINE, size=64, color=ft.Colors.ERROR),
                    ft.Text(
                        "Access Denied",
                        size=24,
                        weight=ft.FontWeight.BOLD,
                        color=ft.Colors.ERROR,
                    ),
                    ft.Text(
                        f"Required role: {required_role}",
                        color=ft.Colors.ON_SURFACE_VARIANT,
                    ),
                    ft.Button(
                        "Go Back",
                        icon=ft.Icons.ARROW_BACK,
                        on_click=lambda _: page.navigate("/home"),
                    ),
                ],
            ),
            alignment=ft.alignment.center,
        )

    return ft.Column(controls=children)


# ─── Main App Component ──────────────────────────────────────────────────────
@ft.component
def routingApp():
    logger.info("Entering routingApp component function...")

    # ── Auth State ─────────────────────────────────────────────────────────
    # build_auth_state() calls ft.use_state / use_callback / use_memo
    # internally, then returns a ready-to-use dict.
    # AuthContext(auth_value, callback) works exactly like ThemeContext /
    # LocalizationContext — no extra @ft.component wrapper needed.
    auth_value = build_auth_state()

    # ── Theme State ─────────────────────────────────────────────────────────
    theme_mode, set_theme_mode = ft.use_state(ft.ThemeMode.LIGHT)
    language, set_language = ft.use_state("mm")

    def handle_toggle_theme(mode: ft.ThemeMode = None):
        if mode:
            set_theme_mode(mode)
        else:
            new_mode = (
                ft.ThemeMode.DARK
                if theme_mode == ft.ThemeMode.LIGHT
                else ft.ThemeMode.LIGHT
            )
            set_theme_mode(new_mode)

    toggle_theme = ft.use_callback(handle_toggle_theme, [theme_mode])

    theme_value = ft.use_memo(
        lambda: ThemeContextModel(mode=theme_mode, toggle=toggle_theme),
        [theme_mode, toggle_theme],
    )

    def update_theme_mode():
        logger.info(f"Theme mode changed to: {theme_mode}")
        ft.context.page.theme_mode = theme_mode
        ft.context.page.scroll = None

    ft.on_updated(update_theme_mode, [theme_mode])

    # ── Localization ────────────────────────────────────────────────────────
    loc_value = ft.use_memo(
        lambda: LocalizationContextModel(
            lang=language,
            get=lambda k: LocalizationManager.get_string(language, k),
            font_scale=0.85 if language == "mm" else 1.0,
            set_lang=set_language,
        ),
        [language],
    )

    # ── Page Wrapper ────────────────────────────────────────────────────────
    # auth_value is passed so each route subtree gets AuthContext re-provided.
    # ft.Router creates an isolated render tree — without this, use_auth()
    # inside loginView / homeView etc. would fall back to the dummy dict.
    wrap = create_page_wrapper(theme_value, loc_value, auth_value)

    # ── Route Definitions ───────────────────────────────────────────────────
    standalone_routes = [
        ft.Route(path="/", index=True, component=lambda: wrap(loginView)),
        ft.Route(
            path="/home",
            component=lambda: wrap(lambda: ProtectedRoute([homeView()])),
        ),
        ft.Route(
            path="/ai-chat",
            component=lambda: wrap(lambda: ProtectedRoute([aiChatView()])),
        ),
    ]

    protected_layout_routes = ft.Route(
        component=lambda: wrap(rootLayout),
        children=[
            ft.Route(
                path="/dashboard",
                component=lambda: wrap(lambda: ProtectedRoute([dashboardView()])),
            ),
            ft.Route(
                path="/live-monitor",
                component=lambda: wrap(lambda: ProtectedRoute([liveMonitorView()])),
            ),
            ft.Route(
                path="/about",
                component=lambda: wrap(lambda: ProtectedRoute([aboutView()])),
            ),
            ft.Route(
                path="/settings",
                component=lambda: wrap(lambda: ProtectedRoute([settingsView()])),
            ),
        ],
    )

    not_found_route = ft.Route(path="/404", component=lambda: wrap(View404))

    app_router = ft.Router(
        routes=[
            *standalone_routes,
            protected_layout_routes,
            not_found_route,
        ],
        manage_views=False,
    )

    logger.info("routingApp initialized successfully")

    # ── Provide all contexts — same pattern for Auth / Theme / Localization ──
    #
    #   AuthContext(auth_value, callback)
    #     └── ThemeContext(theme_value, callback)
    #           └── LocalizationContext(loc_value, callback)
    #                 └── ft.SafeArea(content=app_router)
    #
    # Every child component can now call:
    #   use_auth()  /  use_context(ThemeContext)  /  use_context(LocalizationContext)
    #
    try:
        return AuthContext(
            auth_value,
            lambda: ThemeContext(
                theme_value,
                lambda: LocalizationContext(
                    loc_value,
                    lambda: ft.SafeArea(content=app_router, expand=True),
                ),
            ),
        )
    except Exception as e:
        logger.error(f"Error in routingApp: {e}")
        raise