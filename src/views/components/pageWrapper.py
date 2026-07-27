# src/views/components/pageWrapper.py

import flet as ft
from models.app_route_model import (
    ThemeContext,
    ThemeContextModel,
    LocalizationContext,
    LocalizationContextModel,
)
from core.auth_context import AuthContext


def create_page_wrapper(theme_value, loc_value, auth_value=None):
    """
    Returns a wrap(view_component) function that re-provides all three
    contexts into each route's component tree.

    Routes are rendered inside ft.Router which creates a NEW subtree —
    that subtree loses the parent's context chain unless we re-provide
    each context explicitly here.

    We MUST evaluate the view_component() inside the innermost callback
    so that all parent context providers are active on the renderer stack
    at the time the component is instantiated and hooks like use_auth() are called.
    """
    def wrapper(view_component):
        # Inner builder called only when the context stack is fully set up
        def build_content():
            component = view_component() if callable(view_component) else view_component
            return ft.SafeArea(expand=True, content=component)

        # Nest the providers so they are pushed to the stack before build_content runs
        if auth_value is not None:
            return AuthContext(
                auth_value,
                lambda: ThemeContext(
                    theme_value,
                    lambda: LocalizationContext(loc_value, build_content)
                )
            )
        else:
            return ThemeContext(
                theme_value,
                lambda: LocalizationContext(loc_value, build_content)
            )

    return wrapper