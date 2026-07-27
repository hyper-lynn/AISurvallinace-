# src/core/auth_provider.py
#
# Auth state is managed INSIDE routingApp (@ft.component) so that
# ft.use_state / ft.use_callback / ft.use_memo are called in the correct
# component scope. AuthContext is then provided with a direct call
#   AuthContext(auth_value, callback)
# — identical to how ThemeContext / LocalizationContext are used.
#
# This module exposes a single helper:
#   build_auth_state() → AuthContextModel   ← call ONLY from a @ft.component
#
import flet as ft
from typing import Optional
from config import logger
from models.userModel import UserProfile
from services.auth_service import AuthService
from core.auth_context import AuthContext
from models.auth_context_model import AuthContextModel


def build_auth_state() -> AuthContextModel:
    """
    Build auth state hooks and return the AuthContextModel instance.
    Must be called from inside a @ft.component function.

    Returns:
        AuthContextModel instance with all auth fields (user, is_authenticated,
        is_loading, error, login, logout, clear_error) ready to pass to AuthContext.
    """
    # ─── State ──────────────────────────────────────────────────────────────
    user, set_user         = ft.use_state(None)
    is_loading, set_is_loading = ft.use_state(False)
    error, set_error       = ft.use_state(None)

    # ─── Service (singleton, created once) ──────────────────────────────────
    auth_service = ft.use_memo(lambda: AuthService(), [])

    # ─── Action handlers ────────────────────────────────────────────────────
    def handle_login(username: str, password: str) -> bool:
        set_is_loading(True)
        set_error(None)
        try:
            logger.info(f"Attempting login for '{username}'")
            profile = auth_service.authenticate_user(username, password)
            if profile:
                set_user(profile)
                logger.info(f"User '{profile.user_name}' logged in")
                set_is_loading(False)
                return True
            else:
                logger.warning("Invalid username or password")
                set_error("Invalid username or password")
                set_is_loading(False)
                return False
        except Exception as e:
            set_error(f"Auth error: {str(e)}")
            logger.error(f"Auth error: {e}")
            set_is_loading(False)
            return False

    def handle_logout() -> None:
        set_user(None)
        set_error(None)
        set_is_loading(False)
        logger.info("User logged out")
        try:
            ft.context.page.navigate("/")
        except Exception as e:
            logger.error(f"Logout navigation error: {e}")

    def handle_clear_error() -> None:
        set_error(None)

    # ─── Stable callbacks (prevents stale closures across re-renders) ────────
    login_cb  = ft.use_callback(handle_login,       [user, is_loading, error])
    logout_cb = ft.use_callback(handle_logout,      [user])
    clear_cb  = ft.use_callback(handle_clear_error, [error])

    # ─── Context value (AuthContextModel instance) ──────────────────────────
    auth_value = ft.use_memo(
        lambda: AuthContextModel(
            user=user,
            is_authenticated=user is not None,
            is_loading=is_loading,
            error=error,
            login=login_cb,
            logout=logout_cb,
            clear_error=clear_cb,
        ),
        [user, is_loading, error, login_cb, logout_cb, clear_cb]
    )

    logger.debug(
        f"build_auth_state → is_authenticated={user is not None}, "
        f"is_loading={is_loading}, error={error}"
    )
    return auth_value