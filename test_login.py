import sys
sys.path.append('src')
import flet as ft
from views.loginView import loginView
from core.routerApp import routingApp

def main(page: ft.Page):
    try:
        # Just call loginView() directly if it's a function component
        # wait, loginView is a component, so we can just add it
        view = loginView()
        print("LoginView returned:", view)
        page.add(view)
        print("Page added view successfully")
    except Exception as e:
        import traceback
        traceback.print_exc()
        print("Error:", e)
    
ft.app(target=main)
