# src/models/userModel.py
import flet as ft
from dataclasses import dataclass, field
from typing import Optional

observable_decorator = getattr(ft, "observable", lambda cls: cls)

@observable_decorator
@dataclass
class UserProfile:
    """Safe public user data (no password_hash)"""
    id: int
    user_name: str
    role: str
    
    def is_admin(self) -> bool:
        return self.role == "admin"
    
    def is_operator(self) -> bool:
        return self.role == "operator"
    
    def has_role(self, role: str) -> bool:
        return self.role == role

@observable_decorator
@dataclass  
class User:
    """Internal user model with auth credentials"""
    id: int
    user_name: str
    password_hash: str
    role: str
    
    def to_profile(self) -> UserProfile:
        """Convert to safe public profile"""
        return UserProfile(
            id=self.id,
            user_name=self.user_name,
            role=self.role
        )