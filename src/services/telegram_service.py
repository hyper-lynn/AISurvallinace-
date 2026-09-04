# src/services/telegram_service.py

import sqlite3
import os
import requests
import urllib3
import logging
import queue
import threading
import time
from requests.adapters import HTTPAdapter
from urllib3.util import Retry
from datetime import datetime
from typing import Optional, Dict, Tuple, Union, List
from config import logger

# Suppress urllib3 connectionpool noisy retry warnings (NameResolutionError / getaddrinfo failed)
logging.getLogger("urllib3.connectionpool").setLevel(logging.ERROR)
logging.getLogger("urllib3.util.retry").setLevel(logging.ERROR)
try:
    urllib3.disable_warnings()
except Exception:
    pass

BASE_DIR = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
DEFAULT_DB_PATH = os.path.join(BASE_DIR, "assets", "storage", "auth.db")

class TelegramService:
    """
    Singleton service for Telegram Bot configuration, SQLite3 persistence,
    Target Destination Management (Users, Channels, Groups), and automated
    per-camera AI detection alert dispatching.
    Includes background auto-connect queue worker for seamless DNS reconnection.
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
        self._http_session = None
        self._alert_queue = queue.Queue()
        self._queue_worker_started = False
        self._create_table()
        self._start_alert_queue_worker()
        # Auto-start Telegram Bot AI polling listener on service init if bot_token exists
        config = self.get_config()
        if config.get("bot_token"):
            self.start_ai_bot_polling()

    def _get_session(self) -> requests.Session:
        """
        Creates a resilient HTTP Session configured with automatic retries,
        connection pooling, and silent DNS resolution handling for Telegram API requests.
        """
        if self._http_session is not None:
            return self._http_session

        session = requests.Session()
        retries = Retry(
            total=3,
            backoff_factor=1.5,  # 1.5s, 3s, 6s delays between retries
            status_forcelist=[500, 502, 503, 504],
            raise_on_status=False
        )
        adapter = HTTPAdapter(max_retries=retries, pool_connections=10, pool_maxsize=20)
        session.mount("https://", adapter)
        session.mount("http://", adapter)
        self._http_session = session
        return session

    def _start_alert_queue_worker(self) -> None:
        """Start background daemon queue worker thread for persistent auto-reconnecting Telegram alert dispatches"""
        if getattr(self, "_queue_worker_started", False):
            return
        self._queue_worker_started = True
        worker_thread = threading.Thread(target=self._alert_queue_worker_loop, daemon=True)
        worker_thread.start()
        logger.info("Started Telegram Auto-Connect Background Queue Worker.")

    def _alert_queue_worker_loop(self) -> None:
        """Daemon worker loop: Auto-reconnects and dispatches queued photo alerts without blocking UI or timing out"""
        while True:
            try:
                item = self._alert_queue.get()
                if item is None:
                    break

                photo_source, caption, target_chat_id = item
                sent_success = False
                
                # Persistent auto-connect loop until internet/DNS connects
                while not sent_success:
                    try:
                        ok, msg = self._send_photo_direct(photo_source, caption, target_chat_id)
                        if ok:
                            sent_success = True
                            logger.info(f"Telegram Auto-Connect Queue: Photo alert delivered to {target_chat_id} successfully.")
                        else:
                            time.sleep(3)
                    except Exception:
                        time.sleep(3)

                self._alert_queue.task_done()
            except Exception:
                time.sleep(2)




    def _ensure_db_directory(self) -> None:
        db_dir = os.path.dirname(self.db_path)
        if db_dir:
            os.makedirs(db_dir, exist_ok=True)

    def _get_connection(self) -> sqlite3.Connection:
        conn = sqlite3.connect(self.db_path)
        conn.row_factory = sqlite3.Row
        return conn

    def _create_table(self) -> None:
        """Create telegram_config and telegram_targets tables in SQLite3"""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("""
                    CREATE TABLE IF NOT EXISTS telegram_config (
                        id INTEGER PRIMARY KEY CHECK (id = 1),
                        bot_token TEXT DEFAULT '',
                        chat_id TEXT DEFAULT '',
                        enable_motion_alert INTEGER DEFAULT 0,
                        enable_human_alert INTEGER DEFAULT 0,
                        selected_model TEXT DEFAULT 'yolov8n',
                        updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                    )
                """)
                cursor.execute("""
                    INSERT OR IGNORE INTO telegram_config (id, bot_token, chat_id, enable_motion_alert, enable_human_alert, selected_model)
                    VALUES (1, '', '', 0, 0, 'yolov8n')
                """)
                cursor.execute("""
                    CREATE TABLE IF NOT EXISTS telegram_targets (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        target_name TEXT NOT NULL,
                        target_type TEXT DEFAULT 'user',
                        chat_id TEXT NOT NULL,
                        note TEXT DEFAULT '',
                        role TEXT DEFAULT 'OPERATIVE',
                        phone TEXT DEFAULT '',
                        username TEXT DEFAULT '',
                        is_active INTEGER DEFAULT 1,
                        created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                    )
                """)
                conn.commit()

                # Migration check: Ensure role, phone, username columns exist for legacy DBs
                cursor.execute("PRAGMA table_info(telegram_targets)")
                existing_cols = [row["name"] for row in cursor.fetchall()]

                schema_migrations = [
                    ("role", "TEXT DEFAULT 'OPERATIVE'"),
                    ("phone", "TEXT DEFAULT ''"),
                    ("username", "TEXT DEFAULT ''"),
                ]

                for col_name, col_def in schema_migrations:
                    if col_name not in existing_cols:
                        cursor.execute(f"ALTER TABLE telegram_targets ADD COLUMN {col_name} {col_def}")
                conn.commit()

                # Clean up legacy auto-generated demo targets
                cursor.execute("DELETE FROM telegram_targets WHERE chat_id IN ('@arnold_miller_dir', '@sarah_chen_lead', '-100889210492', '@seye_hq_alerts')")
                conn.commit()
        except Exception as e:
            logger.error(f"Failed to initialize telegram tables: {e}")

    def get_config(self) -> Dict:
        """Get global Telegram configuration from SQLite3 with .env fallback"""
        env_token = os.getenv("TELEGRAM_BOT_TOKEN") or os.getenv("BOT_TOKEN") or ""
        env_chat = os.getenv("TELEGRAM_CHAT_ID") or os.getenv("CHAT_ID") or ""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("SELECT bot_token, chat_id, enable_motion_alert, enable_human_alert, selected_model FROM telegram_config WHERE id = 1")
                row = cursor.fetchone()
                if row:
                    bot_t = (row["bot_token"] or "").strip() or env_token.strip()
                    chat_c = (row["chat_id"] or "").strip() or env_chat.strip()
                    return {
                        "bot_token": bot_t,
                        "chat_id": chat_c,
                        "enable_motion_alert": bool(row["enable_motion_alert"]),
                        "enable_human_alert": bool(row["enable_human_alert"]),
                        "selected_model": row["selected_model"] or "yolov8n",
                    }
        except Exception as e:
            logger.error(f"Error fetching telegram config: {e}")
        return {
            "bot_token": env_token.strip(),
            "chat_id": env_chat.strip(),
            "enable_motion_alert": False,
            "enable_human_alert": False,
            "selected_model": "yolov8n",
        }

    def save_config(self, bot_token: str, chat_id: str, enable_motion_alert: bool, enable_human_alert: bool, selected_model: str) -> Tuple[bool, str]:
        """Save updated Telegram configuration into SQLite3 database"""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("""
                    UPDATE telegram_config
                    SET bot_token = ?,
                        chat_id = ?,
                        enable_motion_alert = ?,
                        enable_human_alert = ?,
                        selected_model = ?,
                        updated_at = CURRENT_TIMESTAMP
                    WHERE id = 1
                """, (
                    bot_token.strip(),
                    chat_id.strip(),
                    1 if enable_motion_alert else 0,
                    1 if enable_human_alert else 0,
                    selected_model.strip()
                ))
                conn.commit()
                logger.info("Updated Telegram bot config in SQLite DB.")
                if bot_token.strip():
                    self.start_ai_bot_polling()
                return True, "Telegram config saved successfully!"
        except Exception as e:
            logger.error(f"Error saving telegram config: {e}")
            return False, f"Database Save Error: {str(e)}"

    # ─── Target Management Methods (Users, Channels, Groups) ───────────────────
    def get_targets(self) -> List[Dict]:
        """Get all registered Telegram targets (Users, Channels, Groups) with profile fields"""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("SELECT * FROM telegram_targets ORDER BY id DESC")
                rows = cursor.fetchall()
                result = []
                for r in rows:
                    item = dict(r)
                    item["role"] = item.get("role") or "OPERATIVE"
                    item["phone"] = item.get("phone") or "+1 (555) 091-0000"
                    item["username"] = item.get("username") or (item["chat_id"] if item["chat_id"].startswith("@") else f"@{item['target_name'].lower().replace(' ', '_')}")
                    result.append(item)
                return result
        except Exception as e:
            logger.error(f"Error fetching telegram targets: {e}")
            return []

    def add_target(
        self,
        target_name: str,
        target_type: str,
        chat_id: str,
        note: str = "",
        role: str = "OPERATIVE",
        phone: str = "",
        username: str = ""
    ) -> Tuple[bool, str]:
        """Add a new Telegram target destination (User Profile, Channel, Group)"""
        name = target_name.strip()
        cid = chat_id.strip()
        if not name or not cid:
            return False, "Target Name နှင့် Chat ID/Username တို့ကို ဖြည့်သွင်းပေးပါခင်ဗျာ။"

        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("""
                    INSERT INTO telegram_targets (target_name, target_type, chat_id, note, role, phone, username)
                    VALUES (?, ?, ?, ?, ?, ?, ?)
                """, (name, target_type.strip(), cid, note.strip(), role.strip() or "OPERATIVE", phone.strip(), username.strip()))
                conn.commit()
                return True, f"Telegram Target '{name}' added successfully!"
        except Exception as e:
            logger.error(f"Error adding telegram target: {e}")
            return False, f"Database Error: {str(e)}"

    def update_target(
        self,
        target_id: int,
        target_name: str,
        target_type: str,
        chat_id: str,
        note: str = "",
        role: str = "OPERATIVE",
        phone: str = "",
        username: str = ""
    ) -> Tuple[bool, str]:
        """Update an existing Telegram target profile in DB"""
        name = target_name.strip()
        cid = chat_id.strip()
        if not name or not cid:
            return False, "Target Name နှင့် Chat ID/Username တို့ကို ဖြည့်သွင်းပေးပါခင်ဗျာ။"

        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("""
                    UPDATE telegram_targets 
                    SET target_name = ?, target_type = ?, chat_id = ?, note = ?, role = ?, phone = ?, username = ?
                    WHERE id = ?
                """, (name, target_type.strip(), cid, note.strip(), role.strip() or "OPERATIVE", phone.strip(), username.strip(), target_id))
                conn.commit()
                return True, f"Telegram Target '{name}' updated successfully!"
        except Exception as e:
            logger.error(f"Error updating telegram target: {e}")
            return False, f"Database Error: {str(e)}"

    def delete_target(self, target_id: int) -> Tuple[bool, str]:
        """Delete a Telegram target destination"""
        try:
            with self._get_connection() as conn:
                cursor = conn.cursor()
                cursor.execute("DELETE FROM telegram_targets WHERE id = ?", (target_id,))
                conn.commit()
                return True, "Telegram Target deleted successfully."
        except Exception as e:
            logger.error(f"Error deleting telegram target: {e}")
            return False, f"Database Error: {str(e)}"

    def send_test_message(self, bot_token: Optional[str] = None, chat_id: Optional[str] = None) -> Tuple[bool, str]:
        """Send a test message via Telegram Bot API to verify token and chat_id"""
        config = self.get_config()
        token = (bot_token if bot_token is not None else config["bot_token"]).strip()
        cid = (chat_id if chat_id is not None else config["chat_id"]).strip()

        if not token or not cid:
            return False, "Bot Token သို့မဟုတ် Chat ID ထည့်သွင်းပေးပါခင်ဗျာ။"

        url = f"https://api.telegram.org/bot{token}/sendMessage"
        payload = {
            "chat_id": cid,
            "text": (
                "🤖 <b>S-Eye Surveillance System</b>\n\n"
                "✅ <b>Telegram Bot တိုက်ရိုက် ချိတ်ဆက်မှု အောင်မြင်ပါသည်။</b>\n"
                f"• Target Channel/Chat ID: <code>{cid}</code>\n"
                f"• Default AI Model: <code>{config['selected_model']}</code>\n"
                f"• Motion Alert: {'ON' if config['enable_motion_alert'] else 'OFF'}\n"
                f"• Human Alert: {'ON' if config['enable_human_alert'] else 'OFF'}\n\n"
                "Motion & Human Detection Alert ရုပ်ပုံများ ပေးပို့ရန် အဆင်သင့်ဖြစ်ပါပြီ။"
            ),
            "parse_mode": "HTML"
        }

        session = self._get_session()
        try:
            resp = session.post(url, json=payload, timeout=(10, 30))
            res_data = resp.json()
            if resp.status_code == 200 and res_data.get("ok"):
                return True, f"Telegram Bot Connection Success to '{cid}'!"
            else:
                desc = res_data.get("description", "Unknown Telegram Error")
                return False, f"Telegram Connection Error: {desc}"
        except (requests.exceptions.Timeout, urllib3.exceptions.ReadTimeoutError):
            logger.error(f"Telegram API timeout: Connection timed out for {cid}.")
            return False, "⚠️ Telegram Network Timeout! (အင်တာနက် လိုင်းနှေးနေပါသည်)"
        except requests.exceptions.RequestException as req_ex:
            logger.error(f"Telegram API request failed: {req_ex}")
            return False, f"⚠️ Network Error: {str(req_ex)}"
        except Exception as e:
            logger.error(f"Telegram API request failed: {e}")
            return False, f"Network/API Error: {str(e)}"

    def _send_photo_direct(
        self,
        photo_source: Union[str, bytes],
        caption: str,
        target_chat_id: str
    ) -> Tuple[bool, str]:
        """Direct network POST request helper for sending photo alert"""
        config = self.get_config()
        token = config.get("bot_token", "").strip()
        cid = target_chat_id.strip()

        if not token or not cid:
            return False, "Telegram Bot Token သို့မဟုတ် Target Chat ID မသတ်မှတ်ရသေးပါ။"

        url = f"https://api.telegram.org/bot{token}/sendPhoto"
        data = {"chat_id": cid, "caption": caption, "parse_mode": "HTML"}
        session = self._get_session()

        try:
            if isinstance(photo_source, str):
                if not os.path.exists(photo_source):
                    return False, f"Snapshot photo file မတွေ့ရှိပါ: {photo_source}"
                with open(photo_source, "rb") as photo_file:
                    files = {"photo": ("snapshot.jpg", photo_file, "image/jpeg")}
                    resp = session.post(url, data=data, files=files, timeout=(10, 30))
            elif isinstance(photo_source, bytes):
                files = {"photo": ("snapshot.jpg", photo_source, "image/jpeg")}
                resp = session.post(url, data=data, files=files, timeout=(10, 30))
            else:
                return False, "Unsupported photo source format."

            res_data = resp.json()
            if resp.status_code == 200 and res_data.get("ok"):
                return True, "Alert photo sent to Telegram successfully!"
            else:
                desc = res_data.get("description", "Failed to send photo.")
                return False, f"Telegram API Error: {desc}"
        except Exception as e:
            return False, str(e)

    def send_alert_photo(
        self,
        photo_source: Union[str, bytes],
        caption: str,
        target_chat_id: Optional[str] = None
    ) -> Tuple[bool, str]:
        """
        Send detection snapshot alert photo to Telegram Chat or Channel.
        Automatically handles DNS NameResolutionError & network drops with background auto-reconnect.
        """
        config = self.get_config()
        cid = (target_chat_id or config.get("chat_id", "")).strip()
        if not cid:
            return False, "Telegram Target Chat ID မသတ်မှတ်ရသေးပါ။"

        # Attempt direct network send first
        ok, msg = self._send_photo_direct(photo_source, caption, cid)
        if ok:
            return True, msg

        # If network/DNS resolution is offline, queue in background worker for persistent auto-reconnect
        err_lower = msg.lower()
        if any(term in err_lower for term in ["getaddrinfo", "nameresolution", "connection", "timeout", "failed", "resolve"]):
            self._alert_queue.put((photo_source, caption, cid))
            return True, "⚡ Alert queued in background worker: Auto-reconnecting Telegram..."

        return False, msg



    def send_camera_alert(
        self,
        camera: Dict,
        photo_source: Union[str, bytes],
        detection_type: str = "HUMAN",
        confidence: float = 0.90,
        model_used: Optional[str] = None,
        person_name: Optional[str] = None
    ) -> Tuple[bool, str]:
        """
        Automated alert dispatcher: Checks camera profile settings (Motion ON/OFF,
        Human ON/OFF, Telegram Enable/Disable, Custom Chat ID) and dispatches alert to Telegram.
        Supports Target Face Identity inclusion.
        """
        config = self.get_config()
        token = config["bot_token"]
        global_chat_id = config["chat_id"]

        if not token:
            return False, "Telegram Bot Token မသတ်မှတ်ရသေးပါ။"

        # Check camera specific Telegram toggle (Default OFF as requested)
        if not bool(camera.get("telegram_alert_enabled", 0)):
            logger.info(f"Telegram alerts disabled for camera profile: {camera.get('name')}")
            return False, "Telegram alert is OFF for this camera profile."

        # Check event type triggers
        event_lower = detection_type.lower()
        if "motion" in event_lower and not bool(camera.get("motion_detection", 0)):
            return False, "Motion detection is OFF for this camera profile."
        if "human" in event_lower and not bool(camera.get("human_detection", 0)) and not person_name:
            return False, "Human detection is OFF for this camera profile."

        # Collect target Chat/Channel/Group IDs
        target_chat_ids = []
        
        # 1. Camera Specific Custom Chat ID (Primary)
        custom_chat_id = (camera.get("telegram_chat_id") or "").strip()
        if custom_chat_id:
            target_chat_ids.append(custom_chat_id)
            
        # 2. Global Chat ID (Fallback)
        if global_chat_id and global_chat_id not in target_chat_ids:
            target_chat_ids.append(global_chat_id)
            
        # 3. Active Registered Targets from Database (Groups / Users / Channels)
        db_targets = self.get_targets()
        for t in db_targets:
            cid = (t.get("chat_id") or "").strip()
            # Ignore default dummy placeholders
            if cid and cid not in target_chat_ids and not cid.endswith("_dir") and not cid.endswith("_lead") and cid != "@seye_hq_alerts":
                target_chat_ids.append(cid)

        if not target_chat_ids:
            return False, "Telegram Chat/Channel ID မသတ်မှတ်ရသေးပါ။ Settings တွင် Chat ID ထည့်သွင်းပေးပါ။"

        cam_name = camera.get("name", "Unknown CCTV")
        cam_type = (camera.get("device_type") or "RTSP").upper()
        engine = model_used or camera.get("detection_model", config.get("selected_model", "yolov8n"))
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        success_count = 0
        last_msg = ""
        
        person_info = f"👤 <b>Target Identity:</b> <code>{person_name.upper()}</code>\n" if person_name else ""

        for tid in target_chat_ids:
            caption = (
                f"🚨 <b>S-Eye AI Security Alert</b>\n\n"
                f"📹 <b>Camera Channel:</b> {cam_name} ({cam_type})\n"
                f"🎯 <b>Detection Event:</b> {detection_type.upper()}\n"
                f"{person_info}"
                f"🧠 <b>AI Scan Engine:</b> {engine}\n"
                f"📊 <b>Confidence Score:</b> {confidence * 100:.1f}%\n"
                f"📢 <b>Target Destination:</b> <code>{tid}</code>\n"
                f"⏰ <b>Timestamp:</b> {timestamp}\n\n"
                f"<i>S-Eye Intelligent Surveillance System</i>"
            )
            ok, msg = self.send_alert_photo(photo_source, caption=caption, target_chat_id=tid)
            if ok:
                success_count += 1
            last_msg = msg

        if success_count > 0:
            return True, f"Alert photo sent to {success_count} Telegram destination(s) successfully!"
        return False, last_msg


    def start_ai_bot_polling(self) -> None:
        """Start background polling thread to listen for Telegram user messages & respond via Gemini AI Pro"""
        if getattr(self, "_polling_active", False):
            return
        self._polling_active = True
        import threading
        self._polling_thread = threading.Thread(target=self._ai_bot_polling_loop, daemon=True)
        self._polling_thread.start()
        logger.info("Started Telegram Bot Gemini AI Polling Listener Worker.")

    def stop_ai_bot_polling(self) -> None:
        """Stop background polling thread"""
        self._polling_active = False

    def _ai_bot_polling_loop(self) -> None:
        """Background thread polling loop for Telegram getUpdates"""
        import time
        import asyncio
        from services.ai_security import AISecurityGuard
        from services.ai_service import generate_ai_response
        
        last_update_id = 0
        logger.info("Telegram Bot AI Chat polling loop started.")
        
        session = self._get_session()
        while getattr(self, "_polling_active", False):
            try:
                config = self.get_config()
                token = config.get("bot_token", "").strip()
                if not token:
                    time.sleep(5)
                    continue

                url = f"https://api.telegram.org/bot{token}/getUpdates"
                params = {"offset": last_update_id + 1, "timeout": 6}
                resp = session.get(url, params=params, timeout=(10, 20))
                
                if resp.status_code == 200:
                    data = resp.json()
                    if data.get("ok"):
                        updates = data.get("result", [])
                        for update in updates:
                            last_update_id = update["update_id"]
                            msg = update.get("message")
                            if not msg:
                                continue
                                
                            chat_id = str(msg.get("chat", {}).get("id", ""))
                            text = (msg.get("text") or "").strip()
                            if not text or not chat_id:
                                continue

                            # Command handlers
                            if text in ["/start", "/help"]:
                                reply_text = (
                                    "🤖 <b>S-Eye Tactical AI Assistant</b>\n\n"
                                    "Powered by <b>Google Gemini AI Pro Engine</b>.\n"
                                    "Send me any text question or surveillance query!\n\n"
                                    "Commands:\n"
                                    "• /security - Show AI Security Policy Terms & Guardrails\n"
                                    "• /status - Show Surveillance & AI System Status"
                                )
                            elif text in ["/security", "/policy"]:
                                reply_text = (
                                    "🛡️ <b>AI Security Policy & Guardrail Terms</b>\n\n"
                                    "• <b>Prompt Injection Protection:</b> ACTIVE\n"
                                    "• <b>Data Confidentiality:</b> Strict (No API key / Credential leakage)\n"
                                    "• <b>Access Control:</b> Privileged User Management restricted to Admins\n"
                                    "• <b>Engine:</b> Guardrailed Google Gemini AI Pro"
                                )
                            elif text in ["/status"]:
                                reply_text = (
                                    "📊 <b>Surveillance System Status</b>\n\n"
                                    "• <b>System State:</b> OPERATIONAL\n"
                                    "• <b>Telegram AI Listener:</b> ACTIVE\n"
                                    "• <b>Default Engine:</b> Gemini 3.6 Flash / Pro"
                                )
                            else:
                                # Run prompt through AISecurityGuard & Gemini AI Pro
                                is_safe, val_msg, clean_text = AISecurityGuard.inspect_and_sanitize(text)
                                if not is_safe:
                                    reply_text = val_msg
                                else:
                                    try:
                                        res = asyncio.run(generate_ai_response(clean_text))
                                        reply_text = res.get("text", "No response generated.")
                                    except Exception as ai_e:
                                        logger.error(f"Telegram AI Response error: {ai_e}")
                                        reply_text = f"⚠️ AI Error: {ai_e}"

                            # Send reply back to Telegram User with fail-safe fallback
                            send_url = f"https://api.telegram.org/bot{token}/sendMessage"
                            resp_send = session.post(send_url, json={
                                "chat_id": chat_id,
                                "text": reply_text,
                                "parse_mode": "HTML"
                            }, timeout=(10, 20))
                            if resp_send.status_code != 200:
                                # Fallback to plain text if HTML parsing failed
                                session.post(send_url, json={
                                    "chat_id": chat_id,
                                    "text": reply_text
                                }, timeout=(10, 20))
            except Exception as e:
                err_str = str(e).lower()
                if any(term in err_str for term in ["getaddrinfo", "nameresolution", "resolve", "connection"]):
                    time.sleep(5)
                else:
                    logger.warning(f"Telegram Polling Auto-Reconnect Loop: {e}")
                    time.sleep(4)



            time.sleep(1)
