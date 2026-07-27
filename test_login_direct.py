import sys
sys.path.append('src')
import flet as ft
from views.loginView import loginView

def main(page: ft.Page):
    try:
        page.render(loginView)
        print("Rendering finished successfully")
    except Exception as e:
        import traceback
        traceback.print_exc()
        print("Error during render:", e)
    
ft.app(target=main)
