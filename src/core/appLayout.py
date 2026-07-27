# src/core/appLayout.py
import flet as ft
from config import logger
from views.components.typography import AppText
from core.helper import use_loc, LocalizationContext
from views.components.language_switcher import LanguageSwitcher
from views.components.theme_switcher import themeSwitcher, neumorphicThemeSwitcher
from views.components.status_indicator import StatusIndicator
from core.auth_context import use_auth, use_user  

NAV_ROUTES = ["/dashboard", "/live-monitor", "/about", "/settings"]

@ft.component
def rootLayout():
    loc = use_loc()
    page = ft.context.page
    
    # Get auth state
    auth = use_auth()
    user = use_user()
    outlet = ft.use_route_outlet()
    
    # ─── Navigation State ───────────────────────────────────────────────────
    curr_route = page.route if (page and page.route) else "/dashboard"
    selected = 0
    if curr_route in ["/dashboard", "/home"]:
        selected = 0
    elif curr_route.startswith("/live-monitor"):
        selected = 1
    elif curr_route.startswith("/about"):
        selected = 2
    elif curr_route.startswith("/settings"):
        selected = 3
    
    # ─── Navigation Handler ─────────────────────────────────────────────────
    def on_nav_change(e):
        try:
            route = NAV_ROUTES[e.control.selected_index]
            logger.info(f"Navigating to: {route}")
            page.navigate(route)
        except Exception as ex:
            logger.warning(f"Navigation error: {ex}")
            page.navigate("/404")
    
    # ─── Logout Handler ─────────────────────────────────────────────────────
    def on_logout_click(e):
        logger.info("Logout button clicked")
        auth.logout()  #  Use auth context logout
    
    # ─── User Info Display ──────────────────────────────────────────────────
    def build_user_chip():
        """Profile Chip"""
        if not user:
            return ft.Container()
        
        # This is the visible chip on the AppBar
        chip = ft.Container(
            content=ft.Row(
                spacing=8,
                vertical_alignment=ft.CrossAxisAlignment.CENTER,
                controls=[
                    # User avatar circle
                    ft.CircleAvatar(
                        content=ft.Text(
                            user.user_name[0].upper(),
                            color=ft.Colors.WHITE,
                            weight=ft.FontWeight.BOLD
                        ),
                        bgcolor=ft.Colors.BLUE_700,
                        radius=16,
                    ),
                    # User name and role
                    ft.Column(
                        spacing=0,
                        alignment=ft.MainAxisAlignment.CENTER,
                        controls=[
                            ft.Text(
                                user.user_name,
                                color=ft.Colors.WHITE,
                                size=13,
                                weight=ft.FontWeight.W_500
                            ),
                            ft.Text(
                                user.role.upper(),
                                color=ft.Colors.WHITE_70,
                                size=10,
                            ),
                        ],
                    ),
                    ft.Icon(
                        ft.Icons.ARROW_DROP_DOWN_ROUNDED,
                        color=ft.Colors.WHITE_70,
                        size=18,
                    ),
                ],
            ),
            padding=ft.Padding.symmetric(horizontal=12, vertical=6),
            border_radius=20,
            bgcolor=ft.Colors.with_opacity(0.15, ft.Colors.WHITE),
        )
        
        return ft.Container(
            theme=ft.Theme(
                hover_color=ft.Colors.TRANSPARENT,
                splash_color=ft.Colors.TRANSPARENT,
                highlight_color=ft.Colors.TRANSPARENT,
            ),
            content=ft.PopupMenuButton(
                content=chip,
                items=[
                    ft.PopupMenuItem(
                        content=ft.Container(
                            content=ft.Row(
                                spacing=12,
                                controls=[
                                    ft.CircleAvatar(
                                        content=ft.Text(
                                            user.user_name[0].upper(),
                                            color=ft.Colors.WHITE,
                                            weight=ft.FontWeight.BOLD
                                        ),
                                        bgcolor=ft.Colors.BLUE_700,
                                        radius=20,
                                    ),
                                    ft.Column(
                                        spacing=2,
                                        controls=[
                                            ft.Text(
                                                user.user_name,
                                                weight=ft.FontWeight.BOLD,
                                                size=14,
                                                color=ft.Colors.ON_SURFACE,
                                            ),
                                            ft.Container(
                                                content=ft.Text(
                                                    user.role.upper(),
                                                    color=ft.Colors.BLUE_700,
                                                    size=9,
                                                    weight=ft.FontWeight.BOLD,
                                                ),
                                                bgcolor=ft.Colors.with_opacity(0.1, ft.Colors.BLUE_700),
                                                padding=ft.Padding.symmetric(horizontal=6, vertical=2),
                                                border_radius=4,
                                            )
                                        ]
                                    )
                                ]
                            ),
                            padding=ft.Padding.symmetric(horizontal=4, vertical=6),
                        ),
                        disabled=True,
                    ),
                    ft.PopupMenuItem(
                        content=ft.Container(
                            content=neumorphicThemeSwitcher(scale=0.85),
                            alignment=ft.Alignment.CENTER,
                            padding=ft.Padding.symmetric(horizontal=4, vertical=4),
                        ),
                        disabled=False
                    ),
                    ft.PopupMenuItem(
                        content=ft.Divider(height=1, thickness=1),
                        disabled=True
                    ),
                    ft.PopupMenuItem(
                        content=ft.Row(
                            spacing=10,
                            controls=[
                                ft.Icon(ft.Icons.LOGOUT_ROUNDED, color=ft.Colors.RED_400, size=18),
                                AppText("logout", color=ft.Colors.RED_400, weight=ft.FontWeight.W_500),
                            ]
                        ),
                        on_click=on_logout_click
                    )
                ]
            )
        )
    
    from views.components.chat_window import AIChatOverlay
    
    # ─── Dynamic Responsive Screen Width Listener ─────────────────────────────
    screen_width, set_screen_width = ft.use_state(page.width if (page and page.width) else 1000)
    screen_height, set_screen_height = ft.use_state(page.height if (page and page.height) else 800)

    def listen_page_resize():
        def handle_resize(e):
            if page and page.width and page.height:
                set_screen_width(page.width)
                set_screen_height(page.height)
        page.on_resized = handle_resize
        return lambda: None

    ft.use_effect(listen_page_resize, [])

    # Android Mobile / Small Screen Threshold Check (<= 768px width or <= 500px height)
    is_mobile = page.platform in [ft.PagePlatform.ANDROID, ft.PagePlatform.IOS] or (screen_width <= 768) or (screen_height <= 500)

    # ─── Original Theme Header AppBar ─────────────────────────────────────────
    app_bar = ft.AppBar(
        title=AppText("app_title", variant="h1"),
        color=ft.Colors.WHITE,
        bgcolor=ft.Colors.BLUE,
        actions=[
            LanguageSwitcher(),
            ft.VerticalDivider(color=ft.Colors.TRANSPARENT),
            build_user_chip(),
            ft.VerticalDivider(color=ft.Colors.TRANSPARENT),
        ],
    )

    # ─── Navigation Layout: Mobile (Bottom NavigationBar) vs Desktop (Side NavigationRail) ───
    if is_mobile:
        body_content = ft.Column(
            spacing=0,
            expand=True,
            controls=[
                app_bar,
                ft.Container(
                    content=outlet,
                    expand=True,
                    padding=0,
                ),
                ft.NavigationBar(
                    selected_index=selected,
                    bgcolor=ft.Colors.SURFACE_CONTAINER_LOW,
                    destinations=[
                        ft.NavigationBarDestination(
                            icon=ft.Icons.HOME_OUTLINED,
                            selected_icon=ft.Icons.DASHBOARD,
                            label=loc("nav_dashboard"),
                        ),
                        ft.NavigationBarDestination(
                            icon=ft.Icons.VIDEOCAM_OUTLINED,
                            selected_icon=ft.Icons.VIDEOCAM_ROUNDED,
                            label=loc("nav_live_monitor"),
                        ),
                        ft.NavigationBarDestination(
                            icon=ft.Icons.PERM_DEVICE_INFORMATION,
                            selected_icon=ft.Icons.PERM_DEVICE_INFORMATION,
                            label=loc("nav_about"),
                        ),
                        ft.NavigationBarDestination(
                            icon=ft.Icons.SETTINGS_OUTLINED,
                            selected_icon=ft.Icons.SETTINGS,
                            label=loc("nav_settings"),
                        ),
                    ],
                    on_change=on_nav_change,
                ),
            ],
        )
    else:
        body_content = ft.Column(
            spacing=0,
            expand=True,
            controls=[
                app_bar,
                ft.Row(
                    vertical_alignment=ft.CrossAxisAlignment.START,
                    expand=True,
                    spacing=0,
                    controls=[
                        ft.NavigationRail(
                            selected_index=selected,
                            label_type=ft.NavigationRailLabelType.ALL,
                            bgcolor=ft.Colors.SURFACE_CONTAINER_LOW,
                            destinations=[
                                ft.NavigationRailDestination(
                                    icon=ft.Icons.HOME_OUTLINED,
                                    selected_icon=ft.Icons.DASHBOARD,
                                    label=loc("nav_dashboard"),
                                ),
                                ft.NavigationRailDestination(
                                    icon=ft.Icons.VIDEOCAM_OUTLINED,
                                    selected_icon=ft.Icons.VIDEOCAM_ROUNDED,
                                    label=loc("nav_live_monitor"),
                                ),
                                ft.NavigationRailDestination(
                                    icon=ft.Icons.PERM_DEVICE_INFORMATION,
                                    selected_icon=ft.Icons.PERM_DEVICE_INFORMATION,
                                    label=loc("nav_about"),
                                ),
                                ft.NavigationRailDestination(
                                    icon=ft.Icons.SETTINGS_OUTLINED,
                                    selected_icon=ft.Icons.SETTINGS,
                                    label=loc("nav_settings"),
                                ),
                            ],
                            on_change=on_nav_change,
                        ),
                        ft.VerticalDivider(width=1),
                        ft.Container(
                            content=outlet,
                            expand=True,
                            padding=0,
                        ),
                    ],
                ),
            ],
        )

    main_content = ft.Container(
        expand=True,
        padding=0,
        content=body_content,
    )

    return ft.Stack(
        expand=True,
        controls=[
            main_content,
            AIChatOverlay()
        ]
    )