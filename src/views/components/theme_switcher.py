#src/views/components

            
import flet as ft 
from core.helper import use_theme_context, use_loc
from config import logger
from views.components.typography import AppText

@ft.component
def themeSwitcher():
    theme_ctx = use_theme_context()
    current_theme = theme_ctx.mode if theme_ctx else ft.ThemeMode.SYSTEM
    lang = use_loc()
    
    def handle_toggle_theme(e: ft.ControlEvent):
        if theme_ctx:         
            selected_mode_str = e.control.value
            new_mode = ft.ThemeMode(selected_mode_str)
            theme_ctx.toggle(new_mode)
            logger.info(f"Theme is changed to: {selected_mode_str}")
            
    try:
        return ft.Container(
            content=ft.Column(
                controls=[
                    ft.RadioGroup(
                        value=current_theme.value if hasattr(current_theme, 'value') else "system", 
                        on_change=handle_toggle_theme,
                        content=ft.Column(
                            controls=[
                                # AppText ထဲမှာ ပြချင်တဲ့ စာသား ထည့်ပေးရပါမယ် (ဥပမာ - ခေါင်းစဉ်)
                                AppText(value_key=lang("theme_mode") or "Choose Theme"), 
                                
                                ft.Radio(
                                    label=lang("dark_mode") or "Dark Theme", 
                                    value=ft.ThemeMode.DARK.value
                                ),
                                ft.Radio(
                                    label=lang("light_mode") or "Light Theme", 
                                    value=ft.ThemeMode.LIGHT.value
                                ),
                                ft.Radio(
                                    label=lang("system_mode") or "System Theme", 
                                    value=ft.ThemeMode.SYSTEM.value
                                ),
                            ]
                        )
                    )
                ]            
            )
        )
        
    except Exception as e:
        logger.error(f"ThemeSwitcher error: {e}")
        return ft.Text("Error loading theme switcher")


@ft.component
def neumorphicThemeSwitcher(scale: float = 0.8):
    theme_ctx = use_theme_context()
    current_theme = theme_ctx.mode if theme_ctx else ft.ThemeMode.SYSTEM
    
    # Resolve actual theme mode if it is set to SYSTEM
    # Since page.platform_brightness can be checked if needed, let's treat SYSTEM as LIGHT for now or fallback
    page = ft.context.page
    
    def handle_click(e):
        if theme_ctx:
            # Toggle between light and dark
            new_mode = ft.ThemeMode.DARK if current_theme != ft.ThemeMode.DARK else ft.ThemeMode.LIGHT
            theme_ctx.toggle(new_mode)
            logger.info(f"Theme toggled to: {new_mode}")

    is_dark = current_theme == ft.ThemeMode.DARK
    
    # Colors matching the neumorphic reference image
    track_bgcolor = "#2C313C" if is_dark else "#EBEFF2"
    track_border = ft.Border.all(1.5, "#232730") if is_dark else ft.Border.all(1.5, "#DFE4E8")
    
    text_val = "DARK\nMODE" if is_dark else "LIGHT\nMODE"
    text_color = "#9CA3AF" if is_dark else "#5E6675"
    text_align = ft.TextAlign.RIGHT if is_dark else ft.TextAlign.LEFT
    
    # Soft neumorphic shadow for the knob
    knob_shadow = ft.BoxShadow(
        spread_radius=1,
        blur_radius=8,
        color=ft.Colors.with_opacity(0.25, ft.Colors.BLACK if is_dark else "#8A95A5"),
        offset=ft.Offset(1, 2)
    )
    
    knob_icon = ft.Icons.NIGHTLIGHT_ROUNDED if is_dark else ft.Icons.WB_SUNNY_ROUNDED
    knob_icon_color = "#8E98A5" if is_dark else "#A5B0BE"
    
    knob = ft.Container(
        width=38,
        height=38,
        shape=ft.BoxShape.CIRCLE,
        bgcolor="#F4F7F9" if is_dark else "#FFFFFF",
        shadow=knob_shadow,
        alignment=ft.Alignment.CENTER,
        content=ft.Icon(
            knob_icon,
            color=knob_icon_color,
            size=20
        ),
        animate=ft.Animation(200, ft.AnimationCurve.EASE_OUT)
    )
    
    text_control = ft.Text(
        text_val,
        color=text_color,
        size=10,
        weight=ft.FontWeight.W_800,
        text_align=text_align,
        # line_height=1.1,
    )
    
    if is_dark:
        controls = [
            ft.Container(content=knob, padding=ft.Padding(left=4, right=0, top=0, bottom=0)),
            ft.Container(content=text_control, padding=ft.Padding(left=0, right=14, top=0, bottom=0), expand=True, alignment=ft.Alignment.CENTER_LEFT)
        ]
    else:
        controls = [
            ft.Container(content=text_control, padding=ft.Padding(left=14, right=0, top=0, bottom=0), expand=True, alignment=ft.Alignment.CENTER_LEFT),
            ft.Container(content=knob, padding=ft.Padding(left=0, right=4, top=0, bottom=0))
        ]
        
    return ft.Container(
        width=135,
        height=46,
        scale=scale,
        # bgcolor=track_bgcolor,
        border=track_border,
        border_radius=23,
        on_click=handle_click,
        content=ft.Row(
            controls=controls,
            alignment=ft.MainAxisAlignment.SPACE_BETWEEN,
            vertical_alignment=ft.CrossAxisAlignment.CENTER,
            spacing=0
        ),
        # Subtle scale animation on hover/click to feel alive and premium
        animate=ft.Animation(250, ft.AnimationCurve.EASE_IN_OUT),
        shadow=ft.BoxShadow(
            spread_radius=-1,
            blur_radius=4,
            color=ft.Colors.with_opacity(0.1, ft.Colors.BLACK),
            offset=ft.Offset(0, 1)
        )
    )