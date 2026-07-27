#src/views/404View.py


import flet as ft 
from views.components.typography import AppText
from config import logger 

@ft.component
def View404():
    
    """_404View

    Returns:
        ft.Container: _description_
    """
    # return AppText("404 Page")
    try:
        return ft.Container(
            expand= True,
            alignment=ft.Alignment.CENTER,
            content=ft.Column(
                
                horizontal_alignment=ft.CrossAxisAlignment.CENTER,
                alignment=ft.MainAxisAlignment.CENTER,
                expand=True,
                controls=[
                    ft.IconButton(ft.Icon(ft.Icons.EMOJI_EMOTIONS,color=ft.Colors.RED, size=100, ),on_click=lambda : ft.context.page.navigate("/")),
                    AppText("404 Page note Found!",variant="caption")          
                ]
        ))
    except Exception as e:
        logger.error(f"cannot rendering : {e}")
        