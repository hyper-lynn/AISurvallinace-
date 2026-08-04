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
    Supports PC Default Webcams, Wireless IP CCTV (RTSP), and Wired IP CCTV streams
    with Camera Grouping/Zones and AI profile settings.
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
        """Create camera_devices table if not exists, migrate schema & seed defaults"""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("""
                    CREATE TABLE IF NOT EXISTS camera_devices (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        name TEXT NOT NULL,
                        device_type TEXT NOT NULL,
                        source TEXT NOT NULL,
                        camera_group TEXT DEFAULT 'Zone-01',
                        is_active INTEGER DEFAULT 1,
                        detection_model TEXT DEFAULT 'yolov8n',
                        motion_detection INTEGER DEFAULT 0,
                        human_detection INTEGER DEFAULT 0,
                        telegram_chat_id TEXT DEFAULT '',
                        telegram_alert_enabled INTEGER DEFAULT 0,
                        created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                    )
                """)
                conn.commit()

                # Migration check: Ensure camera_group and profile columns exist for legacy DBs
                cursor.execute("PRAGMA table_info(camera_devices)")
                existing_cols = [row["name"] for row in cursor.fetchall()]

                schema_migrations = [
                    ("camera_group", "TEXT DEFAULT 'Zone-01'"),
                    ("detection_model", "TEXT DEFAULT 'yolov8n'"),
                    ("motion_detection", "INTEGER DEFAULT 0"),
                    ("human_detection", "INTEGER DEFAULT 0"),
                    ("telegram_chat_id", "TEXT DEFAULT ''"),
                    ("telegram_alert_enabled", "INTEGER DEFAULT 0"),
                ]

                for col_name, col_def in schema_migrations:
                    if col_name not in existing_cols:
                        cursor.execute(f"ALTER TABLE camera_devices ADD COLUMN {col_name} {col_def}")
                conn.commit()

                # Seed default cameras if empty
                cursor.execute("SELECT COUNT(*) as count FROM camera_devices")
                count = cursor.fetchone()["count"]
                if count == 0:
                    cursor.executemany("""
                        INSERT INTO camera_devices (name, device_type, source, camera_group, detection_model, motion_detection, human_detection, telegram_chat_id, telegram_alert_enabled)
                        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
                    """, [
                        ("Updated PC Cam", "webcam", "0", "DEPT: SURV-01", "yolov8n", 0, 0, "", 0),
                        ("Home - Zone 01", "rtsp_wired", "192.168.100.93:554/cam/main", "Zone-01", "yolov8n", 0, 0, "", 0),
                        ("Dahua P2P Cloud (Secure)", "p2p_dahua", "SN: AE44-99X2", "Zone-02", "yolov8n", 0, 0, "", 0),
                    ])
                    conn.commit()
                    logger.info("Default CCTV camera sources seeded into SQLite database.")
        except Exception as e:
            logger.error(f"Error initializing camera_devices table: {e}")

    def _sync_env_cameras(self) -> None:
        """Check .env for DAHUA_P2P_SN and auto-insert into SQLite DB if missing"""
        try:
            sn = ""
            env_path = os.path.abspath(".env")
            if os.path.exists(env_path):
                with open(env_path, "r", encoding="utf-8") as f:
                    for line in f:
                        if "=" in line and not line.strip().startswith("#"):
                            k, v = line.split("=", 1)
                            if k.strip() == "DAHUA_P2P_SN":
                                sn = v.strip().strip('"').strip("'")
                                break
            if sn:
                sn_source = f"SN:{sn}"
                with self._get_connection() as conn:
                    cursor = conn.cursor()
                    cursor.execute("SELECT COUNT(*) as count FROM camera_devices WHERE source LIKE ?", (f"%{sn}%",))
                    exists = cursor.fetchone()["count"]
                    if exists == 0:
                        cursor.execute("""
                            INSERT INTO camera_devices (name, device_type, source, camera_group, detection_model, motion_detection, human_detection, telegram_chat_id, telegram_alert_enabled)
                            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
                        """, (f"Dahua P2P Cloud ({sn})", "p2p_dahua", sn_source, "Zone-02", "yolov8n", 0, 0, "", 0))
                        conn.commit()
                        logger.info(f"Auto-synced Dahua P2P SN '{sn}' from .env into SQLite camera_devices.")
        except Exception as e:
            logger.error(f"Error syncing .env camera sources: {e}")

    def get_cameras(self) -> List[Dict]:
        """Fetch all camera sources with full profile settings and camera_group"""
        self._sync_env_cameras()
        default_list = [
            {
                "id": 1, "name": "Updated PC Cam", "device_type": "webcam", "source": "0", "camera_group": "DEPT: SURV-01",
                "detection_model": "yolov8n", "motion_detection": 0, "human_detection": 0,
                "telegram_chat_id": "", "telegram_alert_enabled": 0
            },
            {
                "id": 2, "name": "Home - Zone 01", "device_type": "rtsp_wired", "source": "192.168.100.93:554/cam/main", "camera_group": "Zone-01",
                "detection_model": "yolov8n", "motion_detection": 0, "human_detection": 0,
                "telegram_chat_id": "", "telegram_alert_enabled": 0
            },
            {
                "id": 3, "name": "Dahua P2P Cloud (Secure)", "device_type": "p2p_dahua", "source": "SN: AE44-99X2", "camera_group": "Zone-02",
                "detection_model": "yolov8n", "motion_detection": 0, "human_detection": 0,
                "telegram_chat_id": "", "telegram_alert_enabled": 0
            },
        ]
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("SELECT * FROM camera_devices ORDER BY id ASC")
                rows = cursor.fetchall()
                result = []
                for r in rows:
                    item = dict(r)
                    # Normalize defaults for any null values
                    item["camera_group"] = item.get("camera_group") or "Zone-01"
                    item["detection_model"] = item.get("detection_model") or "yolov8n"
                    item["motion_detection"] = 0 if item.get("motion_detection") is None else int(item["motion_detection"])
                    item["human_detection"] = 0 if item.get("human_detection") is None else int(item["human_detection"])
                    item["telegram_chat_id"] = item.get("telegram_chat_id") or ""
                    item["telegram_alert_enabled"] = 0 if item.get("telegram_alert_enabled") is None else int(item["telegram_alert_enabled"])
                    result.append(item)
                return result if result else default_list
        except Exception as e:
            logger.error(f"Error fetching cameras: {e}")
            return default_list

    def add_camera(
        self,
        name: str,
        device_type: str,
        source: str,
        camera_group: str = "Zone-01",
        detection_model: str = "yolov8n",
        motion_detection: int = 0,
        human_detection: int = 0,
        telegram_chat_id: str = "",
        telegram_alert_enabled: int = 0
    ) -> int:
        """Add a new CCTV / Webcam camera source with profile settings and camera_group"""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("""
                    INSERT INTO camera_devices (name, device_type, source, camera_group, detection_model, motion_detection, human_detection, telegram_chat_id, telegram_alert_enabled)
                    VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
                """, (
                    name.strip(),
                    device_type.strip(),
                    source.strip(),
                    camera_group.strip() if camera_group else "Zone-01",
                    detection_model.strip(),
                    1 if motion_detection else 0,
                    1 if human_detection else 0,
                    telegram_chat_id.strip(),
                    1 if telegram_alert_enabled else 0
                ))
                conn.commit()
                logger.info(f"Added new camera source: {name} in group {camera_group}")
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

    def update_camera(
        self,
        camera_id: int,
        name: str,
        device_type: str,
        source: str,
        camera_group: str = "Zone-01",
        detection_model: str = "yolov8n",
        motion_detection: int = 0,
        human_detection: int = 0,
        telegram_chat_id: str = "",
        telegram_alert_enabled: int = 0
    ) -> bool:
        """Update an existing camera source and its profile settings in SQLite DB"""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("""
                    UPDATE camera_devices
                    SET name = ?,
                        device_type = ?,
                        source = ?,
                        camera_group = ?,
                        detection_model = ?,
                        motion_detection = ?,
                        human_detection = ?,
                        telegram_chat_id = ?,
                        telegram_alert_enabled = ?
                    WHERE id = ?
                """, (
                    name.strip(),
                    device_type.strip(),
                    source.strip(),
                    camera_group.strip() if camera_group else "Zone-01",
                    detection_model.strip(),
                    1 if motion_detection else 0,
                    1 if human_detection else 0,
                    telegram_chat_id.strip(),
                    1 if telegram_alert_enabled else 0,
                    camera_id
                ))
                conn.commit()
                logger.info(f"Updated camera profile ID: {camera_id}")
                return True
        except Exception as e:
            logger.error(f"Error updating camera profile: {e}")
            return False

    def get_all_zones(self) -> List[str]:
        """Fetch list of distinct non-empty Zone names from database."""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("SELECT DISTINCT camera_group FROM camera_devices WHERE camera_group IS NOT NULL AND camera_group != '' ORDER BY camera_group ASC")
                rows = cursor.fetchall()
                zones = [r["camera_group"] for r in rows if r["camera_group"]]
                return zones if zones else ["Zone-01", "Zone-02", "Zone-03", "Zone-04"]
        except Exception as e:
            logger.error(f"Error fetching zones: {e}")
            return ["Zone-01", "Zone-02", "Zone-03", "Zone-04"]

    def import_all_dahua_channels(
        self,
        ip: str = "192.168.100.93",
        port: int = 554,
        user: str = "admin",
        password: str = "12345asd@",
        channel_count: int = 16
    ) -> int:
        """
        Seed/Import all 16 Dahua channels into the camera database automatically.
        """
        import urllib.parse
        encoded_pass = urllib.parse.quote(password, safe="")
        inserted_count = 0
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                for ch in range(1, channel_count + 1):
                    # Group into zones (e.g. Ch 1-4: Zone-01, Ch 5-8: Zone-02, Ch 9-12: Zone-03, Ch 13-16: Zone-04)
                    zone_num = ((ch - 1) // 4) + 1
                    zone_name = f"Zone-0{zone_num}"
                    cam_name = f"Dahua NVR - CH{ch:02d} ({zone_name})"
                    rtsp_source = f"rtsp://{user}:{encoded_pass}@{ip}:{port}/cam/realmonitor?channel={ch}&subtype=0"

                    cursor.execute("SELECT COUNT(*) as count FROM camera_devices WHERE source = ?", (rtsp_source,))
                    if cursor.fetchone()["count"] == 0:
                        cursor.execute("""
                            INSERT INTO camera_devices (name, device_type, source, camera_group, detection_model, motion_detection, human_detection, telegram_chat_id, telegram_alert_enabled)
                            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
                        """, (cam_name, "rtsp_wired", rtsp_source, zone_name, "yolov8n", 0, 0, "", 0))
                        inserted_count += 1
                conn.commit()
                logger.info(f"Imported {inserted_count} Dahua NVR channels into database.")
        except Exception as e:
            logger.error(f"Error importing Dahua channels: {e}")
        return inserted_count
