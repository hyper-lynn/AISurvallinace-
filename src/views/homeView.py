# src/views/homeView.py
import flet as ft
from views.components.typography import AppText
from core.auth_context import use_user, use_auth, use_has_role
from core.helper import use_loc

# ─── Default Extensible Card Configurations ─────────────────────────────────
# 5 cards per row on large screens (col = 2.4 out of 12)
DEFAULT_DASHBOARD_CARDS = [
    {
        "id": "admin",
        "title_key": "admin_panel",
        "desc_key": "admin_panel_desc",
        "icon": ft.Icons.ADMIN_PANEL_SETTINGS_ROUNDED,
        "route": "/admin",
        "admin_only": True,
        "badge_key": "admin_badge",
        "badge_color": ft.Colors.RED_400,
        "icon_color": ft.Colors.RED_400,
        "button_text_key": "open_admin",
    },
    {
        "id": "dashboard",
        "title_key": "dashboard",
        "desc_key": "dashboard_desc",
        "icon": ft.Icons.DASHBOARD_ROUNDED,
        "route": "/dashboard",
        "admin_only": False,
        "badge_key": "stats_badge",
        "badge_color": ft.Colors.BLUE_400,
        "icon_color": ft.Colors.BLUE_400,
        "button_text_key": "view_reports",
    },
    {
        "id": "live_monitor",
        "title_key": "nav_live_monitor",
        "desc_key": "overview_subtitle",
        "icon": ft.Icons.VIDEOCAM_ROUNDED,
        "route": "/live-monitor",
        "admin_only": False,
        "badge_key": "system_online",
        "badge_color": ft.Colors.RED_400,
        "icon_color": ft.Colors.RED_400,
        "button_text_key": "open_admin",
    },
    {
        "id": "ai_chat",
        "title_key": "ai_assistant",
        "desc_key": "ai_assistant_desc",
        "icon": ft.Icons.SMART_TOY_ROUNDED,
        "route": "/ai-chat?from=/home",
        "admin_only": False,
        "badge_key": "ai_badge",
        "badge_color": ft.Colors.PURPLE_400,
        "icon_color": ft.Colors.PURPLE_400,
        "button_text_key": "open_chat",
    },
    {
        "id": "settings",
        "title_key": "settings",
        "desc_key": "settings_desc",
        "icon": ft.Icons.SETTINGS_ROUNDED,
        "route": "/settings",
        "admin_only": False,
        "badge_key": None,
        "badge_color": None,
        "icon_color": ft.Colors.TEAL_400,
        "button_text_key": "configure",
    },
    {
        "id": "about",
        "title_key": "about_system",
        "desc_key": "about_system_desc",
        "icon": ft.Icons.INFO_ROUNDED,
        "route": "/about",
        "admin_only": False,
        "badge_key": None,
        "badge_color": None,
        "icon_color": ft.Colors.AMBER_400,
        "button_text_key": "view_info",
    },
]


@ft.component
def DashboardCard(card_data: dict, is_admin: bool, loc):
    """
    Declarative Dashboard Card component using ft.use_state for hover state.
    col={"xs": 12, "sm": 6, "md": 4, "lg": 2.4, "xl": 2.4} -> 5 cards per row on lg/xl!
    """
    if card_data.get("admin_only") and not is_admin:
        return ft.Container()

    is_hovered, set_is_hovered = ft.use_state(False)

    # Retrieve translated strings
    title = (
        loc(card_data.get("title_key"))
        if card_data.get("title_key")
        else card_data.get("title", "Module")
    )
    desc = (
        loc(card_data.get("desc_key"))
        if card_data.get("desc_key")
        else card_data.get("desc", "")
    )
    button_text = (
        loc(card_data.get("button_text_key"))
        if card_data.get("button_text_key")
        else card_data.get("button_text", "Open")
    )

    badge_key = card_data.get("badge_key")
    badge = loc(badge_key) if badge_key else card_data.get("badge")

    icon = card_data.get("icon", ft.Icons.WIDGETS_ROUNDED)
    route = card_data.get("route", "/home")
    badge_color = card_data.get("badge_color", ft.Colors.PRIMARY)
    icon_color = card_data.get("icon_color", ft.Colors.PRIMARY)

    badge_widget = (
        ft.Container(
            content=ft.Text(
                badge,
                size=10,
                weight=ft.FontWeight.BOLD,
                color=ft.Colors.WHITE,
            ),
            bgcolor=badge_color,
            padding=ft.Padding.symmetric(horizontal=8, vertical=3),
            border_radius=10,
        )
        if badge
        else ft.Container()
    )

    return ft.Container(
        col={"xs": 12, "sm": 6, "md": 4, "lg": 2.4, "xl": 2.4},
        on_hover=lambda e: set_is_hovered(e.data == "true"),
        border_radius=14,
        padding=16,
        bgcolor=(
            ft.Colors.SURFACE_CONTAINER_HIGHEST
            if is_hovered
            else ft.Colors.SURFACE_CONTAINER_HIGH
        ),
        border=(
            ft.Border.all(1, icon_color)
            if is_hovered
            else ft.Border.all(1, ft.Colors.OUTLINE_VARIANT)
        ),
        animate=ft.Animation(200, ft.AnimationCurve.EASE_IN_OUT),
        content=ft.Column(
            alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
            spacing=12,
            controls=[
                # Top Row: Icon + Badge
                ft.Column(
                    spacing=8,
                    controls=[
                        ft.Row(
                            alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                            vertical_alignment=ft.CrossAxisAlignment.CENTER,
                            controls=[
                                ft.Container(
                                    content=ft.Icon(icon, size=28, color=icon_color),
                                    padding=8,
                                    border_radius=10,
                                    bgcolor=ft.Colors.with_opacity(0.12, icon_color),
                                ),
                                badge_widget,
                            ],
                        ),
                        # Title
                        ft.Text(
                            title,
                            size=16,
                            weight=ft.FontWeight.BOLD,
                            max_lines=1,
                            overflow=ft.TextOverflow.ELLIPSIS,
                        ),
                        # Description
                        ft.Text(
                            desc,
                            size=12,
                            color=ft.Colors.ON_SURFACE_VARIANT,
                            max_lines=2,
                            overflow=ft.TextOverflow.ELLIPSIS,
                        ),
                    ],
                ),
                # Bottom Action Button
                ft.Button(
                    content=ft.Row(
                        alignment=ft.MainAxisAlignment.CENTER,
                        spacing=6,
                        controls=[
                            ft.Text(button_text, size=13, weight=ft.FontWeight.W_600),
                            ft.Icon(ft.Icons.ARROW_FORWARD_ROUNDED, size=14),
                        ],
                    ),
                    style=ft.ButtonStyle(
                        shape=ft.RoundedRectangleBorder(radius=8),
                    ),
                    on_click=lambda _: ft.context.page.navigate(route),
                ),
            ],
        ),
    )


@ft.component
def homeView(extra_cards: list = None):
    # ⭐ Get user data & localization context
    user = use_user()
    role = use_auth()
    loc = use_loc()

    # ⭐ Role checks
    is_admin = use_has_role(user.user_name)

    # ⭐ Extensible Card List
    cards_config = list(DEFAULT_DASHBOARD_CARDS)
    if extra_cards:
        cards_config.extend(extra_cards)

    # Filter and create card widgets
    card_widgets = []
    for c_data in cards_config:
        if c_data.get("admin_only") and not is_admin:
            continue
        card_widgets.append(DashboardCard(c_data, is_admin, loc))

    return ft.Container(
        padding=24,
        expand=True,
        content=ft.Column(
            expand=True,
            scroll=ft.ScrollMode.HIDDEN,
            spacing=24,
            controls=[
                # ─── Welcome Header ─────────────────────────────────────────
                ft.Container(
                    padding=20,
                    border_radius=16,
                    bgcolor=ft.Colors.SURFACE_CONTAINER_LOW,
                    border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
                    content=ft.Row(
                        alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                        vertical_alignment=ft.CrossAxisAlignment.CENTER,
                        controls=[
                            ft.Column(
                                spacing=6,
                                controls=[
                                    ft.Row(
                                        spacing=8,
                                        vertical_alignment=ft.CrossAxisAlignment.CENTER,
                                        controls=[
                                            ft.Text(
                                                f"{loc('welcome_back')}, {user.user_name}!",
                                                size=24,
                                                weight=ft.FontWeight.BOLD,
                                            ),
                                            ft.Container(
                                                content=ft.Text(
                                                    user.role.upper(),
                                                    size=11,
                                                    weight=ft.FontWeight.BOLD,
                                                    color=ft.Colors.BLUE_ACCENT,
                                                ),
                                                bgcolor=ft.Colors.with_opacity(
                                                    0.15, ft.Colors.BLUE_ACCENT
                                                ),
                                                padding=ft.Padding.symmetric(
                                                    horizontal=8, vertical=4
                                                ),
                                                border_radius=6,
                                            ),
                                        ],
                                    ),
                                    ft.Text(
                                        loc("overview_subtitle"),
                                        color=ft.Colors.ON_SURFACE_VARIANT,
                                        size=14,
                                    ),
                                ],
                            ),
                            ft.Icon(
                                ft.Icons.AUTO_AWESOME_ROUNDED,
                                size=36,
                                color=ft.Colors.PRIMARY,
                            ),
                        ],
                    ),
                ),
                # ─── Section Title ──────────────────────────────────────────
                ft.Row(
                    alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                    vertical_alignment=ft.CrossAxisAlignment.CENTER,
                    controls=[
                        ft.Row(
                            spacing=8,
                            controls=[
                                ft.Icon(
                                    ft.Icons.GRID_VIEW_ROUNDED,
                                    size=20,
                                    color=ft.Colors.PRIMARY,
                                ),
                                AppText("modules_header", variant="h3", weight=ft.FontWeight.BOLD),
                            ],
                        ),
                        ft.Text(
                            f"{len(card_widgets)} • {loc('modules_active_status')}",
                            size=12,
                            color=ft.Colors.ON_SURFACE_VARIANT,
                        ),
                    ],
                ),
                # ─── Responsive Grid Row (5 cards per row on lg/xl) ──────────
                ft.ResponsiveRow(
                    spacing=16,
                    run_spacing=16,
                    controls=card_widgets,
                ),
                ft.Divider(height=1, color=ft.Colors.OUTLINE_VARIANT),
                # ─── User Info Card ─────────────────────────────────────────
                ft.Card(
                    elevation=0,
                    bgcolor=ft.Colors.SURFACE_CONTAINER_LOW,
                    content=ft.Container(
                        padding=20,
                        border_radius=12,
                        content=ft.Column(
                            spacing=12,
                            controls=[
                                ft.Row(
                                    spacing=8,
                                    controls=[
                                        ft.Icon(
                                            ft.Icons.ACCOUNT_CIRCLE_OUTLINED,
                                            size=20,
                                            color=ft.Colors.PRIMARY,
                                        ),
                                        AppText("account_info", variant="h3", weight=ft.FontWeight.BOLD),
                                    ],
                                ),
                                ft.Divider(height=1),
                                ft.Row(
                                    controls=[
                                        ft.Container(
                                            width=120,
                                            content=AppText("user_id", color=ft.Colors.ON_SURFACE_VARIANT),
                                        ),
                                        ft.Text(
                                            str(user.id), weight=ft.FontWeight.BOLD
                                        ),
                                    ]
                                ),
                                ft.Row(
                                    controls=[
                                        ft.Container(
                                            width=120,
                                            content=AppText("username", color=ft.Colors.ON_SURFACE_VARIANT),
                                        ),
                                        ft.Text(
                                            user.user_name, weight=ft.FontWeight.BOLD
                                        ),
                                    ]
                                ),
                                ft.Row(
                                    controls=[
                                        ft.Container(
                                            width=120,
                                            content=AppText("role", color=ft.Colors.ON_SURFACE_VARIANT),
                                        ),
                                        ft.Text(
                                            user.role, weight=ft.FontWeight.BOLD
                                        ),
                                    ]
                                ),
                            ],
                        ),
                    ),
                ),
            ],
        ),
    )

