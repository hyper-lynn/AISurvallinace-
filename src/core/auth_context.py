# src/core/auth_context.py
import flet as ft
from typing import Optional
from models.userModel import UserProfile
from models.auth_context_model import AuthContextModel

# ─── Create Context  ────────────────────────────────────────────────────────
# Default value is an empty AuthContextModel instance.
# If no provider is found in the tree, this default model is returned.
AuthContext = ft.create_context(AuthContextModel()) 

# ─── Hook: use_auth ─────────────────────────────────────────────────────────
def use_auth() -> AuthContextModel:
    """
    Access auth state anywhere in the component tree.
    Returns AuthContextModel instance.
    """
    return ft.use_context(AuthContext)

# ─── Hook: use_user ─────────────────────────────────────────────────────────
def use_user() -> Optional[UserProfile]:
    """Get current user profile or None"""
    auth = use_auth()
    return auth.user

# ─── Hook: use_is_authenticated ─────────────────────────────────────────────
def use_is_authenticated() -> bool:
    return use_auth().is_authenticated

# ─── Hook: use_has_role ─────────────────────────────────────────────────────
def use_has_role(role: str) -> bool:
    user = use_user()
    return user is not None and user.role == role