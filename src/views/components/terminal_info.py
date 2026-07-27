import flet as ft
from core.helper import use_loc

@ft.component
def TerminalInfo():
    loc = use_loc()
    
    return ft.Row(
        spacing=8,
        vertical_alignment=ft.CrossAxisAlignment.CENTER,
        controls=[
            ft.Icon(
                ft.Icons.COMPUTER_ROUNDED, 
                color=ft.Colors.BLUE_900, 
                size=18
            ),
            ft.Text(
                value=f"{loc('station')} • {loc('main_terminal')}", 
                weight=ft.FontWeight.W_500, 
                color=ft.Colors.ON_SURFACE,
                size=14
            )
        ]
    )
