# src/core/helper.py

import flet as ft
from models.app_route_model import LocalizationContext,ThemeContext



def use_theme_context():
    return ft.use_context(ThemeContext)


#create a hook to use the whole context
def use_localization_context():
    return ft.use_context(LocalizationContext)


def use_loc():
    """
    using Localization Hook for every page
    """
    ctx = ft.use_context(LocalizationContext)
    
    def translate(key: str) -> str:
        if ctx is None:
            return key
        return ctx(key) # Model ထဲက __call__ ကို လှမ်းခေါ်ပါလိမ့်မည်
        
    return translate




