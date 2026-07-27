#/src/models/app_route_model.py

#ThemeContextModel , Localization & AppRouteModel are created for routing

import flet as ft
from dataclasses import dataclass, field
from collections.abc import Callable
from config import logger

@ft.observable
@dataclass(frozen=True)
class ThemeContextModel:
    mode: ft.ThemeMode
    toggle: Callable[[ft.ThemeMode | None], None]

@ft.observable
@dataclass(frozen=True)
class LocalizationContextModel:
    lang: str
    get: Callable[[str], str]
    font_scale: float
    set_lang: Callable[[str], None]
    
    def __call__(self, key: str) -> str:
        return self.get(key)




# Global Contexts to avoid circular imports
ThemeContext = ft.create_context(ThemeContextModel(ft.ThemeMode.SYSTEM, lambda: None))
LocalizationContext = ft.create_context(LocalizationContextModel("en", lambda k: k, 1.0, lambda l: None))
