#src/main.py

import flet as ft 

from config import logger
from config.fonts import AppFonts
from config.colors import get_app_theme
from core.routerApp import routingApp

async def main(page:ft.Page):
    
    try:
        logger.info("Shadow Eye is trying to start!")
        page.fonts = AppFonts.FONTS_MAPPING
        page.title = "Shadow EYE"
        
        # page.vertical_alignment = ft.MainAxisAlignment.CENTER
        # page.horizontal_alignment = ft.CrossAxisAlignment.CENTER
        page.window.icon = r"images/logo.ico"
        # page.padding = 0
        # page.update()
        await page.window.center()
        
        
        #Apply custom themes before rendering
        try:
            page.theme = get_app_theme(ft.ThemeMode.LIGHT)
            page.dark_theme = get_app_theme(ft.ThemeMode.DARK)
            logger.info("Custom themes applied successfully")
        except Exception as e:
            logger.error(f"Failed to apply custom themes: {e}")
            
        #rendering the view
        page.render(routingApp)
        # page.window.full_screen = True
        
    except Exception as e:
        logger.debug(f"ZayYaungPOS failed to start: {e}")
    

if __name__ == "__main__":
    ft.run(main,assets_dir="assets")

    
# import flet as ft

# def main(page: ft.Page):
#     # Font file ကို ချိတ်ဆက်ခြင်း (assets folder ထဲမှာ font ရှိရပါမယ်)
#     page.fonts = {
#         "Pyidaungsu": "/fonts/Pyidaungsu.ttf" 
#     }
    
#     # App တစ်ခုလုံးအတွက် Default Font ကို Pyidaungsu အဖြစ် သတ်မှတ်ခြင်း
#     page.theme = ft.Theme(font_family="Pyidaungsu")

#     tf = ft.TextField(label="ဒီမှာ ရိုက်ကြည့်ပါ", text_size=20)
#     page.add(tf)

# ft.app(target=main, assets_dir="assets")