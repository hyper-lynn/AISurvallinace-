# src/services/auth_service.py
import sqlite3
import os
import hashlib
import random
import string
from typing import Optional, List
from dotenv import load_dotenv
from config import logger
from models.userModel import User, UserProfile

# ─── Environment Setup ──────────────────────────────────────────────────────
load_dotenv()
DEFAULT_ADMIN_PASSWORD = os.getenv("default_admin_password", "0000")

# ─── Database Path Resolution ───────────────────────────────────────────────
BASE_DIR = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
DEFAULT_DB_PATH = os.path.join(BASE_DIR, "assets", "storage", "auth.db")


class AuthService:
    """
    Singleton-style auth service for SQLite-backed user authentication.
    Thread-safe connection handling with context managers.
    """
    
    _instance = None
    
    def __new__(cls, *args, **kwargs):
        """Singleton pattern to prevent multiple DB connections"""
        if cls._instance is None:
            cls._instance = super().__new__(cls)
            cls._instance._initialized = False
        return cls._instance
    
    def __init__(self, db_path: Optional[str] = None):
        if self._initialized:
            return
            
        self.db_path = db_path or DEFAULT_DB_PATH
        self._ensure_db_directory()
        self._initialized = True
        
        # Initialize schema on first creation and sync default admin
        self._create_table()
    
    # ─── Database Connection ────────────────────────────────────────────────
    def _ensure_db_directory(self) -> None:
        """Ensure database directory exists"""
        db_dir = os.path.dirname(self.db_path)
        if db_dir:
            os.makedirs(db_dir, exist_ok=True)
    
    def _get_connection(self) -> sqlite3.Connection:
        """Get configured database connection"""
        conn = sqlite3.connect(self.db_path)
        conn.row_factory = sqlite3.Row  # Enable dict-like access
        return conn
    
    # ─── Schema Management ──────────────────────────────────────────────────
    def _create_table(self) -> None:
        """Initialize users table with default admin"""
        with self._get_connection() as conn:
            cursor = conn.cursor()
            cursor.execute("""
                CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    user_name TEXT UNIQUE NOT NULL,
                    password_hash TEXT NOT NULL,
                    role TEXT DEFAULT 'operator'
                )
            """)
            conn.commit()
            self._create_default_admin()
    
    def _create_default_admin(self) -> None:
        """Create or update default admin user automatically from environment (.env)"""
        password = os.getenv("default_admin_password", "0000")
        hashed_pw = self._hash_password(password)
        
        with self._get_connection() as conn:
            cursor = conn.cursor()
            cursor.execute("SELECT id FROM users WHERE user_name = ?", ("admin",))
            row = cursor.fetchone()
            if row:
                cursor.execute(
                    "UPDATE users SET password_hash = ? WHERE user_name = ?",
                    (hashed_pw, "admin")
                )
                logger.info("Default admin password synced with .env")
            else:
                cursor.execute(
                    "INSERT INTO users (user_name, password_hash, role) VALUES (?, ?, ?)",
                    ("admin", hashed_pw, "admin")
                )
                logger.info("Default admin user created from .env")
            conn.commit()
    
    # ─── Password Handling ──────────────────────────────────────────────────
    @staticmethod
    def _hash_password(password: str) -> str:
        """SHA-256 password hashing"""
        return hashlib.sha256(password.encode()).hexdigest()
    
    # ─── Public API ─────────────────────────────────────────────────────────
    def authenticate_user(self, user_name: str, password: str) -> Optional[UserProfile]:
        """
        Authenticate user and return safe profile (no password hash)
        """
        hashed_password = self._hash_password(password)
        
        with self._get_connection() as conn:
            cursor = conn.cursor()
            cursor.execute(
                """SELECT id, user_name, password_hash, role 
                   FROM users 
                   WHERE user_name = ? AND password_hash = ?""",
                (user_name, hashed_password)
            )
            row = cursor.fetchone()
            
            if row:
                return UserProfile(
                    id=row["id"],
                    user_name=row["user_name"],
                    role=row["role"]
                )
            return None
    
    def get_user_by_username(self, user_name: str) -> Optional[UserProfile]:
        """Get user profile by username (for admin operations)"""
        with self._get_connection() as conn:
            cursor = conn.cursor()
            cursor.execute(
                "SELECT id, user_name, role FROM users WHERE user_name = ?",
                (user_name,)
            )
            row = cursor.fetchone()
            
            if row:
                return UserProfile(
                    id=row["id"],
                    user_name=row["user_name"],
                    role=row["role"]
                )
            return None

    def get_all_users(self) -> List[UserProfile]:
        """Get list of all registered users in system"""
        with self._get_connection() as conn:
            cursor = conn.cursor()
            cursor.execute("SELECT id, user_name, role FROM users ORDER BY id ASC")
            rows = cursor.fetchall()
            return [
                UserProfile(id=r["id"], user_name=r["user_name"], role=r["role"])
                for r in rows
            ]

    def create_user(self, user_name: str, password: str, role: str = "operator") -> tuple[bool, str]:
        """
        Create a new user account (Admin privilege required)
        """
        user_name = user_name.strip()
        if not user_name:
            return False, "User name မဖြစ်မနေ ထည့်သွင်းရပါမည်။"
            
        if not password or len(password) < 4:
            return False, "Password သည် အနည်းဆုံး ၄ လုံး ရှိရပါမည်။"

        hashed_pw = self._hash_password(password)
        
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute(
                    "INSERT INTO users (user_name, password_hash, role) VALUES (?, ?, ?)",
                    (user_name, hashed_pw, role)
                )
                conn.commit()
                logger.info(f"User account created: {user_name} ({role})")
                return True, f"User '{user_name}' ကို အောင်မြင်စွာ ဖန်တီးပြီးပါပြီ။"
        except sqlite3.IntegrityError:
            return False, f"User name '{user_name}' သည် ရှိပြီးသား ဖြစ်နေပါသည်။"
        except Exception as e:
            logger.error(f"Error creating user: {e}")
            return False, f"User ဖန်တီးရာတွင် အမှားဖြစ်ပွားခဲ့သည်: {e}"

    def reset_user_password_temp(self, user_name: str) -> tuple[bool, str, str]:
        """
        Reset a user's password to a temporary password (or .env admin password for admin).
        Returns: (success, temp_password, message)
        """
        user = self.get_user_by_username(user_name)
        if not user:
            return False, "", f"User '{user_name}' ကို ရှာမတွေ့ပါခင်ဗျာ။"
            
        # If resetting admin user, default back to .env default_admin_password
        if user_name.lower() == "admin":
            temp_pw = os.getenv("default_admin_password", "0000")
        else:
            digits = "".join(random.choices(string.digits, k=4))
            letters = "".join(random.choices(string.ascii_uppercase, k=4))
            temp_pw = f"Temp{letters}{digits}"
            
        hashed_pw = self._hash_password(temp_pw)

        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute(
                    "UPDATE users SET password_hash = ? WHERE user_name = ?",
                    (hashed_pw, user_name)
                )
                conn.commit()
                logger.info(f"Password reset for user: {user_name}")
                return True, temp_pw, f"User '{user_name}' ၏ စကားဝှက်ကို ယာယီစကားဝှက် '{temp_pw}' ဖြင့် အောင်မြင်စွာ ပြောင်းလဲပြီးပါပြီ။"
        except Exception as e:
            logger.error(f"Error resetting password for {user_name}: {e}")
            return False, "", f"Password reset အဆင်မပြေပါခင်ဗျာ: {e}"