# src/views/dashboardView.py

import flet as ft
from views.components.typography import AppText
from core.helper import use_loc

@ft.component
def dashboardView():
    loc = use_loc()
    
    # Metrics cards data with localization keys
    metrics = [
        {
            "title_key": "total_users",
            "value": "1,248",
            "icon": ft.Icons.PEOPLE_ROUNDED,
            "color": ft.Colors.BLUE_400,
            "trend": "+12% this week",
        },
        {
            "title_key": "active_cameras",
            "value": "42 / 45",
            "icon": ft.Icons.VIDEOCAM_ROUNDED,
            "color": ft.Colors.GREEN_400,
            "trend": "93% operational",
        },
        {
            "title_key": "today_alerts",
            "value": "15",
            "icon": ft.Icons.NOTIFICATIONS_ACTIVE_ROUNDED,
            "color": ft.Colors.ORANGE_400,
            "trend": "-3 from yesterday",
        },
        {
            "title_key": "server_load",
            "value": "28%",
            "icon": ft.Icons.MEMORY_ROUNDED,
            "color": ft.Colors.PURPLE_400,
            "trend": "Normal performance",
        },
        {
            "title_key": "storage_used",
            "value": "1.4 TB",
            "icon": ft.Icons.STORAGE_ROUNDED,
            "color": ft.Colors.TEAL_400,
            "trend": "70% capacity",
        },
    ]

    metric_cards = []
    for m in metrics:
        card = ft.Container(
            col={"xs": 12, "sm": 6, "md": 4, "lg": 2.4, "xl": 2.4},
            content=ft.Container(
                padding=16,
                border_radius=14,
                bgcolor=ft.Colors.SURFACE_CONTAINER_HIGH,
                border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
                content=ft.Column(
                    spacing=8,
                    controls=[
                        ft.Row(
                            alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                            controls=[
                                ft.Text(
                                    loc(m["title_key"]),
                                    size=13,
                                    color=ft.Colors.ON_SURFACE_VARIANT,
                                    weight=ft.FontWeight.W_500,
                                ),
                                ft.Icon(m["icon"], color=m["color"], size=22),
                            ],
                        ),
                        ft.Text(
                            m["value"],
                            size=24,
                            weight=ft.FontWeight.BOLD,
                        ),
                        ft.Text(
                            m["trend"],
                            size=11,
                            color=ft.Colors.ON_SURFACE_VARIANT,
                        ),
                    ],
                ),
            ),
        )
        metric_cards.append(card)

    return ft.Container(
        padding=24,
        expand=True,
        content=ft.Column(
            expand=True,
            scroll=ft.ScrollMode.AUTO,
            spacing=24,
            controls=[
                # Header Section
                ft.Container(
                    padding=20,
                    border_radius=16,
                    bgcolor=ft.Colors.SURFACE_CONTAINER_LOW,
                    border=ft.Border.all(1, ft.Colors.OUTLINE_VARIANT),
                    content=ft.Row(
                        alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
                        controls=[
                            ft.Column(
                                spacing=4,
                                controls=[
                                    AppText("dashboard_analytics", variant="h1", weight=ft.FontWeight.BOLD),
                                    AppText("analytics_overview", color=ft.Colors.ON_SURFACE_VARIANT, variant="body"),
                                ],
                            ),
                            ft.Icon(ft.Icons.ANALYTICS_ROUNDED, size=36, color=ft.Colors.PRIMARY),
                        ],
                    ),
                ),
                
                # Metrics Section Title
                ft.Row(
                    spacing=8,
                    controls=[
                        ft.Icon(ft.Icons.QUERY_STATS_ROUNDED, size=20, color=ft.Colors.PRIMARY),
                        AppText("system_status", variant="h3", weight=ft.FontWeight.BOLD),
                    ],
                ),
                
                # Responsive Metrics Grid (5 cards per row on large screens)
                ft.ResponsiveRow(
                    spacing=16,
                    run_spacing=16,
                    controls=metric_cards,
                ),
            ],
        ),
    )