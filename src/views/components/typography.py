#AppInstaller/src/components/typography.py

import flet as ft
from models.app_route_model import LocalizationContext

@ft.component
def AppText(value_key: str, variant: str = "body", **kwargs):
    """
    Custom Typography component that handles localization and font scaling automatically.
    
    Args:
        value_key (str): The translation key from the JSON file.
        variant (str): 'h1', 'h2', 'h3', 'body', 'caption'. Defaults to 'body'.
        **kwargs: Additional ft.Text arguments (color, weight, etc.)
    """
    loc = ft.use_context(LocalizationContext)
    
    # Pre-defined sizes for different variants
    sizes = {
        "h1": 32,
        "h2": 24,
        "h3": 20,
        "body": 16,
        "caption": 12
    }
    
    base_size = sizes.get(variant, 16)
    
    # Calculate final size based on localization font_scale
    final_size = base_size * loc.font_scale
    
    return ft.Text(
        value=loc.get(value_key),
        size=final_size,
        **kwargs
    )
