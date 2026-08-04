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
            idx = int(e.control.selected_index) if (hasattr(e.control, "selected_index") and e.control.selected_index is not None) else int(e.data)
            route = NAV_ROUTES[idx]
            logger.info(f"Navigating to: {route}")
            page.go(route)
        except Exception as ex:
            logger.warning(f"Navigation error: {ex}")
            try:
                page.go("/dashboard")
            except Exception:
                pass
    
    # ─── Logout Handler ─────────────────────────────────────────────────────
    def on_logout_click(e):
        logger.info("Logout button clicked")
        auth.logout()
    
    # ─── User Info Display ──────────────────────────────────────────────────
    def build_user_chip():
        """Profile Chip matching AEGIS ADM-01 Active status pill"""
        if not user:
            return ft.Container()
        
        chip = ft.Container(
            content=ft.Row(
                spacing=6,
                vertical_alignment=ft.CrossAxisAlignment.CENTER,
                controls=[
                    ft.Container(width=6, height=6, border_radius=3, bgcolor=ft.Colors.BLUE_400),
                    ft.Text(
                        f"{user.user_name[:6].upper()}-01 ACTIVE",
                        color=ft.Colors.ON_SURFACE,
                        size=11,
                        weight=ft.FontWeight.BOLD
                    ),
                    ft.Icon(
                        ft.Icons.ARROW_DROP_DOWN_ROUNDED,
                        color=ft.Colors.ON_SURFACE_VARIANT,
                        size=16,
                    ),
                ],
            ),
            padding=ft.Padding.symmetric(horizontal=10, vertical=4),
            border_radius=16,
            bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
            border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
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

    # Mobile threshold check (Android/iOS native platforms or narrow width < 600px)
    is_mobile = page.platform in [ft.PagePlatform.ANDROID, ft.PagePlatform.IOS] or (screen_width < 600)

    # ─── AEGIS Tactical Header AppBar ─────────────────────────────────────────
    app_bar = ft.AppBar(
        title=ft.Row([
            ft.Text("AEGIS SURVEILLANCE", size=17, weight=ft.FontWeight.BOLD, color=ft.Colors.BLUE_700),
            ft.Row([
                ft.Container(
                    content=ft.Text("SYSTEM CENTER", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.BLUE_700 if selected == 0 else ft.Colors.ON_SURFACE_VARIANT),
                    on_click=lambda _: page.go("/dashboard")
                ),
                ft.Container(
                    content=ft.Text("DATA FEED", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.BLUE_700 if selected == 1 else ft.Colors.ON_SURFACE_VARIANT),
                    on_click=lambda _: page.go("/live-monitor")
                ),
                ft.Container(
                    content=ft.Text("NETWORK MAP", size=11, weight=ft.FontWeight.BOLD, color=ft.Colors.BLUE_700 if selected == 2 else ft.Colors.ON_SURFACE_VARIANT),
                    on_click=lambda _: page.go("/about")
                ),
            ], spacing=18)
        ], spacing=24, alignment=ft.MainAxisAlignment.START),
        bgcolor=ft.Colors.SURFACE_CONTAINER_LOW,
        actions=[
            LanguageSwitcher(),
            ft.IconButton(icon=ft.Icons.SHIELD_ROUNDED, icon_color=ft.Colors.BLUE_600, tooltip="Security System Active"),
            ft.IconButton(icon=ft.Icons.LANGUAGE_ROUNDED, icon_color=ft.Colors.BLUE_600, tooltip="Network Status"),
            build_user_chip(),
            ft.VerticalDivider(color=ft.Colors.TRANSPARENT),
        ],
    )

    # Sidebar Network Load Progress Card
    network_load_widget = ft.Container(
        padding=10,
        margin=ft.Margin(8, 0, 8, 12),
        bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
        border_radius=8,
        border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
        content=ft.Column([
            ft.Text("NETWORK LOAD", size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.OUTLINE),
            ft.ProgressBar(value=0.34, color=ft.Colors.BLUE_600, bgcolor=ft.Colors.SURFACE_CONTAINER),
            ft.Row([
                ft.Text("34%", size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE_VARIANT),
                ft.Text("1.2 GBPS", size=10, weight=ft.FontWeight.BOLD, color=ft.Colors.ON_SURFACE_VARIANT),
            ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN)
        ], spacing=4)
    )

    # Footer Status Bar
    footer_bar = ft.Container(
        bgcolor=ft.Colors.SURFACE_CONTAINER_LOW,
        padding=ft.Padding(16, 6, 16, 6),
        border=ft.Border(top=ft.BorderSide(1, ft.Colors.OUTLINE_VARIANT)),
        content=ft.Row([
            ft.Text("© 2024 AEGIS TACTICAL SYSTEMS. ALL RIGHTS RESERVED. CLASSIFIED MATERIAL.", size=9, color=ft.Colors.PRIMARY),
            ft.Row([
                ft.Row([
                    ft.Container(width=6, height=6, border_radius=3, bgcolor=ft.Colors.BLUE_400),
                    ft.Text("System Status: Operational", size=9, weight=ft.FontWeight.BOLD, color=ft.Colors.PRIMARY)
                ], spacing=4),
                ft.Text("Legal Disclaimers", size=9, color=ft.Colors.OUTLINE),
                ft.Text("Privacy Protocol", size=9, color=ft.Colors.OUTLINE),
                ft.Text("Security Clearance", size=9, color=ft.Colors.OUTLINE),
            ], spacing=14)
        ], alignment=ft.MainAxisAlignment.SPACE_BETWEEN)
    )

    # ─── Navigation Layout: Mobile vs Desktop ───
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
                footer_bar
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
                        ft.Column([
                            ft.NavigationRail(
                                selected_index=selected,
                                label_type=ft.NavigationRailLabelType.ALL,
                                bgcolor=ft.Colors.SURFACE_CONTAINER_LOW,
                                height=ft.context.page.height,
                                min_width=150,
                                destinations=[
                                    ft.NavigationRailDestination(
                                        icon=ft.Icons.GRID_VIEW_ROUNDED,
                                        selected_icon=ft.Icons.DASHBOARD,
                                        label="DASHBOARD",
                                    ),
                                    ft.NavigationRailDestination(
                                        icon=ft.Icons.VIDEOCAM_OUTLINED,
                                        selected_icon=ft.Icons.VIDEOCAM_ROUNDED,
                                        label="LIVE MONITOR",
                                    ),
                                    ft.NavigationRailDestination(
                                        icon=ft.Icons.INFO_OUTLINED,
                                        selected_icon=ft.Icons.INFO,
                                        label="SYSTEM INFO",
                                    ),
                                    ft.NavigationRailDestination(
                                        icon=ft.Icons.SETTINGS_OUTLINED,
                                        selected_icon=ft.Icons.SETTINGS,
                                        label="SETTINGS",
                                    ),
                                ],
                                on_change=on_nav_change,
                                expand=True
                            ),
                            # network_load_widget
                        ], expand=False, spacing=0),
                        ft.VerticalDivider(width=1),
                        # ft.Text(f'{ft.context.page.route}')
                        ft.Container(
                            content=outlet,
                            expand=True,
                            padding=0,
                        ),
                    ],
                ),
                footer_bar
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
