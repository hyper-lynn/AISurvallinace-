import flet as ft
from config.fonts import AppFonts

class AppPalette:
    # Light Theme Palette
    L_BG = "#F8FAFC"
    L_SURFACE = "#FFFFFF"
    L_PRIMARY = "#2563EB"
    L_TEXT = "#1E293B"
    L_SECONDARY = "#64748B"
    L_BORDER = "#E2E8F0"
    
    # Dark Theme Palette
    D_BG = "#0C1117"
    D_SURFACE = "#161B22"
    D_PRIMARY = "#2563EB"
    D_TEXT = "#F1F5F9"
    D_SECONDARY = "#94A3B8"
    D_BORDER = "#1E293B"

def get_app_theme(mode: ft.ThemeMode = ft.ThemeMode.LIGHT) -> ft.Theme:
    """
    Generates a Flet Theme object based on our custom palette using Material 3 spec.
    """
    if mode == ft.ThemeMode.LIGHT:
        return ft.Theme(
            font_family=AppFonts.DEFAULT_FAMILY,
            color_scheme=ft.ColorScheme(
                primary=AppPalette.L_PRIMARY,
                # In latest Flet/M3, background is renamed to surface
                surface=AppPalette.L_BG,
                on_surface=AppPalette.L_TEXT,
                secondary=AppPalette.L_SECONDARY,
                outline=AppPalette.L_BORDER,
            )
        )
    else:
        return ft.Theme(
            font_family=AppFonts.DEFAULT_FAMILY,
            color_scheme=ft.ColorScheme(
                primary=AppPalette.D_PRIMARY,
                # In latest Flet/M3, background is renamed to surface
                surface=AppPalette.D_BG,
                on_surface=AppPalette.D_TEXT,
                secondary=AppPalette.D_SECONDARY,
                outline=AppPalette.D_BORDER,
            )
        )
