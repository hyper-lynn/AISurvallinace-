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

                # Seed default PC webcam if empty
                cursor.execute("SELECT COUNT(*) as count FROM camera_devices")
                count = cursor.fetchone()["count"]
                if count == 0:
                    cursor.execute("""
                        INSERT INTO camera_devices (name, device_type, source, camera_group, detection_model, motion_detection, human_detection, telegram_chat_id, telegram_alert_enabled)
                        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
                    """, ("Default PC Webcam", "webcam", "0", "Zone-01", "yolov8n", 0, 0, "", 0))
                    conn.commit()
                    logger.info("Default PC Webcam seeded into SQLite database.")
        except Exception as e:
            logger.error(f"Error initializing camera_devices table: {e}")

    def get_cameras(self) -> List[Dict]:
        """Fetch all camera sources with full profile settings and camera_group"""
        default_list = [
            {
                "id": 1, "name": "Default PC Webcam", "device_type": "webcam", "source": "0", "camera_group": "Zone-01",
                "detection_model": "yolov8n", "motion_detection": 0, "human_detection": 0,
                "telegram_chat_id": "", "telegram_alert_enabled": 0
            }
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

    def delete_all_cameras(self) -> bool:
        """Purge all camera devices from SQLite DB"""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("DELETE FROM camera_devices")
                conn.commit()
                logger.info("Purged all camera devices from registry.")
                return True
        except Exception as e:
            logger.error(f"Error purging all cameras: {e}")
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
        ip: Optional[str] = None,
        port: int = 554,
        user: Optional[str] = None,
        password: Optional[str] = None,
        channel_count: int = 16,
        overwrite: bool = True
    ) -> int:
        """
        Seed/Import/Update all Dahua NVR channels into the camera database automatically.
        """
        target_ip = ip if ip else os.getenv("DAHUA_IP", "").strip()
        target_user = user if user else os.getenv("DAHUA_USER", "admin")
        target_pass = password if password else os.getenv("DAHUA_PASS", "")

        if not target_ip:
            logger.info("DAHUA_IP is not configured. Skipping automatic channel import.")
            return 0

        import urllib.parse
        encoded_pass = urllib.parse.quote(target_pass, safe="")
        inserted_count = 0
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                for ch in range(1, channel_count + 1):
                    zone_num = ((ch - 1) // 4) + 1
                    zone_name = f"Zone-0{zone_num}"
                    cam_name = f"Dahua NVR - CH{ch:02d} ({zone_name})"
                    rtsp_source = f"rtsp://{target_user}:{encoded_pass}@{target_ip}:{port}/cam/realmonitor?channel={ch}&subtype=0"

                    cursor.execute("SELECT id FROM camera_devices WHERE name LIKE ?", (f"%CH{ch:02d}%",))
                    existing = cursor.fetchone()
                    if existing and overwrite:
                        cursor.execute("""
                            UPDATE camera_devices SET source = ?, camera_group = ?, device_type = 'rtsp_wired'
                            WHERE id = ?
                        """, (rtsp_source, zone_name, existing["id"]))
                        inserted_count += 1
                    elif not existing:
                        cursor.execute("""
                            INSERT INTO camera_devices (name, device_type, source, camera_group, detection_model, motion_detection, human_detection, telegram_chat_id, telegram_alert_enabled)
                            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
                        """, (cam_name, "rtsp_wired", rtsp_source, zone_name, "yolov8n", 0, 0, "", 0))
                        inserted_count += 1
                conn.commit()
                logger.info(f"Imported/Updated {inserted_count} Dahua NVR channels (IP: {target_ip}) into database.")
        except Exception as e:
            logger.error(f"Error importing Dahua channels: {e}")
        return inserted_count

    def import_sn_devices(self, devices: List[Dict[str, str]]) -> int:
        """
        Bulk import/organize camera Serial Numbers (SN) into SQLite database.
        Each item in `devices` can contain:
          - "name": e.g. "IMOU Ranger 2 (Front Yard)"
          - "sn": e.g. "8M0435CPAZ0E327"
          - "group": e.g. "IMOU Wireless" or "Wired Channel"
          - "device_type": e.g. "p2p_dahua" (default)
        """
        inserted_count = 0
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                for dev in devices:
                    sn = str(dev.get("sn", "")).strip()
                    if not sn:
                        continue
                    sn_source = f"SN:{sn}" if not sn.startswith("SN:") and not sn.startswith("p2p://") else sn
                    name = dev.get("name", f"Camera ({sn})").strip()
                    group = dev.get("group", "Zone-01").strip()
                    device_type = dev.get("device_type", "p2p_dahua").strip()

                    cursor.execute("SELECT COUNT(*) as count FROM camera_devices WHERE source LIKE ?", (f"%{sn}%",))
                    if cursor.fetchone()["count"] == 0:
                        cursor.execute("""
                            INSERT INTO camera_devices (name, device_type, source, camera_group, detection_model, motion_detection, human_detection, telegram_chat_id, telegram_alert_enabled)
                            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
                        """, (name, device_type, sn_source, group, "yolov8n", 0, 0, "", 0))
                        inserted_count += 1
                conn.commit()
                logger.info(f"Imported {inserted_count} SN camera devices into database.")
        except Exception as e:
            logger.error(f"Error importing SN devices: {e}")
        return inserted_count

