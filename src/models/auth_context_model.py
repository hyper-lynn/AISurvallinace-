# src/models/auth_context_model.py
from dataclasses import dataclass
from typing import Optional, Callable
from models.userModel import UserProfile
import flet as ft 


@ft.observable
@dataclass
class AuthContextModel:
    """Auth context value model """
    user: Optional[UserProfile] = None
    is_authenticated: bool = False
    is_loading: bool = False
    error: Optional[str] = None
    
    
    # Actions
    login: Optional[Callable] = None
    logout: Optional[Callable] = None
    clear_error: Optional[Callable] = None

    def get(self, key: str, default=None):
        """Allow dict-like get() access for compatibility"""
        return getattr(self, key, default)

    def __getitem__(self, key: str):
        """Allow dict-like subscription access (e.g. auth['user']) for compatibility"""
        if hasattr(self, key):
            return getattr(self, key)
        raise KeyError(key)