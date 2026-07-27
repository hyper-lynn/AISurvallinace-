# src/services/chat_service.py

import sqlite3
import os
from typing import Optional, List, Dict
from config import logger

BASE_DIR = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
DEFAULT_DB_PATH = os.path.join(BASE_DIR, "assets", "storage", "auth.db")

class ChatService:
    """
    Service to manage SQLite3 persistence for AI chat history.
    """
    _instance = None
    
    def __new__(cls, *args, **kwargs):
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
        self._create_table()
        
    def _ensure_db_directory(self) -> None:
        db_dir = os.path.dirname(self.db_path)
        if db_dir:
            os.makedirs(db_dir, exist_ok=True)
            
    def _get_connection(self) -> sqlite3.Connection:
        conn = sqlite3.connect(self.db_path)
        conn.row_factory = sqlite3.Row
        return conn
        
    def _create_table(self) -> None:
        """Create chat_messages table if not exists"""
        with self._get_connection() as conn:
            cursor = conn.cursor()
            cursor.execute("""
                CREATE TABLE IF NOT EXISTS chat_messages (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    user_id INTEGER,
                    sender TEXT NOT NULL,
                    text TEXT NOT NULL,
                    media_type TEXT,
                    media_url TEXT,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                )
            """)
            conn.commit()
            
    def save_message(self, sender: str, text: str, media_type: Optional[str] = None, media_url: Optional[str] = None, user_id: Optional[int] = None) -> int:
        """Save a new chat message into SQLite database"""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("""
                    INSERT INTO chat_messages (user_id, sender, text, media_type, media_url)
                    VALUES (?, ?, ?, ?, ?)
                """, (user_id, sender, text, media_type, media_url))
                conn.commit()
                return cursor.lastrowid
        except Exception as e:
            logger.error(f"Error saving chat message to SQLite: {e}")
            return -1
            
    def get_messages(self, user_id: Optional[int] = None, limit: int = 100) -> List[Dict]:
        """Fetch chat history from SQLite database"""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                if user_id is not None:
                    cursor.execute("""
                        SELECT sender, text, media_type, media_url 
                        FROM chat_messages 
                        WHERE user_id = ? OR user_id IS NULL
                        ORDER BY id ASC LIMIT ?
                    """, (user_id, limit))
                else:
                    cursor.execute("""
                        SELECT sender, text, media_type, media_url 
                        FROM chat_messages 
                        ORDER BY id ASC LIMIT ?
                    """, (limit,))
                    
                rows = cursor.fetchall()
                if not rows:
                    # Return welcome message if database is empty
                    return [{
                        "sender": "AI",
                        "text": "မင်္ဂလာပါ! ကျွန်တော်ကတော့ Shadow EYE ရဲ့ AI Assistant ဖြစ်ပါတယ်။ စာသားများ၊ ပုံများ သို့မဟုတ် ဗီဒီယို ဖန်တီးပေးရန် မေးမြန်းနိုင်ပါတယ်ခင်ဗျာ။",
                        "media_type": None,
                        "media_url": None
                    }]
                
                return [
                    {
                        "sender": r["sender"],
                        "text": r["text"],
                        "media_type": r["media_type"],
                        "media_url": r["media_url"]
                    }
                    for r in rows
                ]
        except Exception as e:
            logger.error(f"Error loading chat history from SQLite: {e}")
            return [{
                "sender": "AI",
                "text": "မင်္ဂလာပါ! ကျွန်တော်ကတော့ Shadow EYE ရဲ့ AI Assistant ဖြစ်ပါတယ်။",
                "media_type": None,
                "media_url": None
            }]

    def clear_history(self, user_id: Optional[int] = None) -> bool:
        """Clear chat history in SQLite database"""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                if user_id is not None:
                    cursor.execute("DELETE FROM chat_messages WHERE user_id = ?", (user_id,))
                else:
                    cursor.execute("DELETE FROM chat_messages")
                conn.commit()
                return True
        except Exception as e:
            logger.error(f"Error clearing chat history: {e}")
            return False
