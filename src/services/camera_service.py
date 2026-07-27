# src/services/camera_service.py

import sqlite3
import os
from typing import Optional, List, Dict
from config import logger

BASE_DIR = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
DEFAULT_DB_PATH = os.path.join(BASE_DIR, "assets", "storage", "auth.db")

class CameraService:
    """
    Service to manage SQLite3 persistence for CCTV & Webcam sources.
    Supports PC Default Webcams, Wireless IP CCTV (RTSP), and Wired IP CCTV streams.
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
        """Create camera_devices table if not exists & seed defaults"""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("""
                    CREATE TABLE IF NOT EXISTS camera_devices (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        name TEXT NOT NULL,
                        device_type TEXT NOT NULL,
                        source TEXT NOT NULL,
                        is_active INTEGER DEFAULT 1,
                        created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                    )
                """)
                conn.commit()

                # Seed default cameras if empty
                cursor.execute("SELECT COUNT(*) as count FROM camera_devices")
                count = cursor.fetchone()["count"]
                if count == 0:
                    cursor.executemany("""
                        INSERT INTO camera_devices (name, device_type, source)
                        VALUES (?, ?, ?)
                    """, [
                        ("Default PC Webcam", "webcam", "0"),
                        ("Wireless CCTV - Sector 7G", "rtsp_wireless", "rtsp://192.168.1.100:554/stream1"),
                        ("Wired CCTV - Main Gate", "rtsp_wired", "rtsp://192.168.1.101:554/stream1"),
                    ])
                    conn.commit()
                    logger.info("Default CCTV camera sources seeded into SQLite database.")
        except Exception as e:
            logger.error(f"Error initializing camera_devices table: {e}")

    def get_cameras(self) -> List[Dict]:
        """Fetch all camera sources from SQLite database"""
        default_list = [
            {"id": 1, "name": "Default PC Webcam", "device_type": "webcam", "source": "0"},
            {"id": 2, "name": "Wireless CCTV - Sector 7G", "device_type": "rtsp_wireless", "source": "rtsp://192.168.1.100:554/stream1"},
            {"id": 3, "name": "Wired CCTV - Main Gate", "device_type": "rtsp_wired", "source": "rtsp://192.168.1.101:554/stream1"},
        ]
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("SELECT * FROM camera_devices ORDER BY id ASC")
                rows = cursor.fetchall()
                result = [dict(r) for r in rows]
                return result if result else default_list
        except Exception as e:
            logger.error(f"Error fetching cameras: {e}")
            return default_list

    def add_camera(self, name: str, device_type: str, source: str) -> int:
        """Add a new CCTV / Webcam camera source"""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("""
                    INSERT INTO camera_devices (name, device_type, source)
                    VALUES (?, ?, ?)
                """, (name, device_type, source))
                conn.commit()
                logger.info(f"Added new camera source: {name}")
                return cursor.lastrowid
        except Exception as e:
            logger.error(f"Error adding camera source: {e}")
            return -1

    def delete_camera(self, camera_id: int) -> bool:
        """Delete a camera source by ID"""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("DELETE FROM camera_devices WHERE id = ?", (camera_id,))
                conn.commit()
                logger.info(f"Deleted camera source ID: {camera_id}")
                return True
        except Exception as e:
            logger.error(f"Error deleting camera source: {e}")
            return False

    def update_camera(self, camera_id: int, name: str, device_type: str, source: str) -> bool:
        """Update an existing camera source in SQLite DB"""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("""
                    UPDATE camera_devices
                    SET name = ?, device_type = ?, source = ?
                    WHERE id = ?
                """, (name, device_type, source, camera_id))
                conn.commit()
                logger.info(f"Updated camera source ID: {camera_id}")
                return True
        except Exception as e:
            logger.error(f"Error updating camera source: {e}")
            return False
