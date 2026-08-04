import os
import sys
import time
import uuid
import hmac
import hashlib
import logging
from typing import Optional, Callable
import requests
from dotenv import load_dotenv

try:
    from core.dahua_sdk import DahuaSDK
except ImportError:
    from src.core.dahua_sdk import DahuaSDK

logger = logging.getLogger(__name__)

def calculate_iot_sign(access_key: str, secret_key: str, timestamp: str, nonce: str, body_sha512: str = "", app_access_token: str = "") -> str:
    """
    Calculate DoLynk IOT HMAC-SHA512 Signature.
    """
    if body_sha512:
        string_to_sign = f"POST\n{body_sha512}"
    else:
        string_to_sign = "POST"
    if app_access_token:
        str_src = f"{access_key}{app_access_token}{timestamp}{nonce}{string_to_sign}"
    else:
        str_src = f"{access_key}{timestamp}{nonce}{string_to_sign}"
    return hmac.new(secret_key.encode('utf-8'), str_src.encode('utf-8'), hashlib.sha512).hexdigest().upper()

class DahuaP2PService:
    """
    High-level Service Layer for Dahua P2P Video Streaming.
    Reads credentials from .env and wraps DahuaSDK low-level calls.
    """

    def __init__(self, env_path: Optional[str] = None):
        if env_path is None:
            base_dir = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
            env_path = os.path.join(base_dir, '.env')

        if os.path.exists(env_path):
            load_dotenv(env_path)

        self.device_sn = os.getenv("DAHUA_P2P_SN", "")
        self.device_user = os.getenv("DAHUA_P2P_USER", "admin")
        self.device_pass = os.getenv("DAHUA_P2P_PASS", "")

        self.access_key = os.getenv("DOLYNK_ACCESS_KEY", "")
        self.secret_key = os.getenv("DOLYNK_SECRET_KEY", "")
        self.product_id = os.getenv("DOLYNK_PRODUCT_ID", "")
        self.host = os.getenv("DOLYNK_HOST", "open.cloud-dahua.com").replace("https://", "").replace("http://", "").strip()

        self.sdk = DahuaSDK.get_instance()
        self.handle = None
        self.is_playing = False
        self.status_code = ""

    def initialize(self) -> bool:
        """
        Initialize the Dahua SDK DLL and load submodules.
        """
        if not self.sdk.initialize_dll():
            logger.error("Failed to initialize Dahua SDK DLL.")
            return False

        try:
            self.sdk.set_mobile_log_level(5)
            self.sdk.load_sub_modules()
            self.handle = self.sdk.create_handle()

            # Set default callbacks
            self.sdk.set_on_player_result_callback(self._on_player_result)
            self.sdk.set_on_play_began_callback(self._on_play_began)

            logger.info(f"DahuaP2PService initialized successfully with handle: {self.handle}")
            return True
        except Exception as e:
            logger.error(f"Error initializing DahuaP2PService: {e}", exc_info=True)
            return False

    def _on_player_result(self, index: int, code: str, result_source: int):
        self.status_code = code
        logger.info(f"[SDK Callback] onPlayerResult index={index}, code={code}, source={result_source}")
        if code == "Param Error":
            logger.warning(
                "Dahua P2P SDK returned 'Param Error'. "
                "This occurs when 'playInfo' payload from Dahua Cloud API (/open-api/api-iot/device/getDeviceList) "
                "is missing or empty. Please ensure Dahua Developer Platform API credentials or playInfo payload are provided."
            )

    def _on_play_began(self, index: int):
        self.is_playing = True
        logger.info(f"[SDK Callback] onPlayBegan index={index}")

    def login_p2p(
        self,
        serial_number: str = "",
        username: Optional[str] = None,
        password: Optional[str] = None,
        play_info: str = "",
        hwnd_ptr: int = 0
    ) -> bool:
        """
        Alias method for camera_controller and external services attempting Dahua P2P connection.
        """
        target_sn = serial_number if serial_number else self.device_sn
        target_pass = password if password else self.device_pass
        logger.info(f"Logging in / starting Dahua P2P stream for SN: {target_sn}")
        return self.start_p2p_stream(
            device_id=target_sn,
            decrypt_key=target_pass,
            play_info=play_info,
            hwnd_ptr=hwnd_ptr
        )

    def fetch_cloud_play_info(self, target_sn: str) -> Optional[str]:
        """
        Fetch playInfo payload for target SN from DoLynk Cloud REST API.
        """
        if not self.access_key or not self.secret_key:
            logger.info("DOLYNK_ACCESS_KEY / DOLYNK_SECRET_KEY not set in .env. Skipping cloud REST API fetch.")
            return None

        try:
            logger.info(f"Fetching DoLynk Cloud AppAccessToken for host: {self.host}...")
            ts = str(int(time.time() * 1000))
            nonce = str(uuid.uuid4()).replace("-", "")
            trace_id = str(uuid.uuid4()).replace("-", "")
            sign = calculate_iot_sign(self.access_key, self.secret_key, ts, nonce, body_sha512="", app_access_token="")

            url_token = f"https://{self.host}/open-api/api-base/auth/getAppAccessToken"
            headers_token = {
                "Content-Type": "application/json",
                "Version": "v1",
                "AccessKey": self.access_key,
                "ProductId": self.product_id,
                "X-TraceId-Header": trace_id,
                "Timestamp": ts,
                "Sign": sign,
                "Nonce": nonce
            }

            resp_token = requests.post(url_token, headers=headers_token, timeout=5)
            token_json = resp_token.json()
            app_token = None

            if isinstance(token_json, dict):
                data_field = token_json.get("data")
                if isinstance(data_field, dict):
                    app_token = data_field.get("appAccessToken")
                elif isinstance(data_field, str):
                    app_token = data_field
                if not app_token:
                    app_token = token_json.get("appAccessToken")

            if not app_token or not isinstance(app_token, str):
                logger.warning(f"Failed to obtain AppAccessToken from DoLynk Cloud response: {token_json}")
                return None

            logger.info("Successfully fetched DoLynk AppAccessToken. Fetching device playInfo...")
            json_body = '{"pageSize":"10","pageNum":"1"}'
            body_sha512 = hashlib.sha512(json_body.encode('utf-8')).hexdigest().upper()
            ts2 = str(int(time.time() * 1000))
            nonce2 = str(uuid.uuid4()).replace("-", "")
            trace_id2 = str(uuid.uuid4()).replace("-", "")
            sign2 = calculate_iot_sign(self.access_key, self.secret_key, ts2, nonce2, body_sha512, app_token)

            url_dev = f"https://{self.host}/open-api/api-iot/device/getDeviceList"
            headers_dev = {
                "Content-Type": "application/json",
                "Version": "v1",
                "AppAccessToken": app_token,
                "AccessKey": self.access_key,
                "ProductId": self.product_id,
                "X-TraceId-Header": trace_id2,
                "Timestamp": ts2,
                "Sign": sign2,
                "Nonce": nonce2
            }

            resp_dev = requests.post(url_dev, data=json_body, headers=headers_dev, timeout=5)
            dev_json = resp_dev.json()
            devices = []
            if isinstance(dev_json, dict):
                data_field = dev_json.get("data")
                if isinstance(data_field, dict):
                    devices = data_field.get("list") or []
                elif isinstance(data_field, list):
                    devices = data_field

            if isinstance(devices, list):
                for dev in devices:
                    if isinstance(dev, dict):
                        if dev.get("deviceSn") == target_sn or dev.get("deviceId") == target_sn:
                            play_info = dev.get("playInfo", "")
                            logger.info(f"Found playInfo for SN {target_sn} from DoLynk Cloud API.")
                            return play_info
                if devices and isinstance(devices[0], dict):
                    return devices[0].get("playInfo", "")
        except Exception as e:
            logger.error(f"Error fetching DoLynk cloud playInfo: {e}")
        return None

    def start_p2p_stream(
        self,
        token: str = "",
        device_id: Optional[str] = None,
        decrypt_key: Optional[str] = None,
        hwnd_ptr: int = 0,
        channel_id: int = 0,
        definition_mode: int = 0,
        play_info: str = ""
    ) -> bool:
        """
        Start P2P live stream.
        """
        if not self.handle:
            if not self.initialize():
                return False

        target_device_sn = device_id if device_id else self.device_sn
        target_decrypt_key = decrypt_key if decrypt_key else self.device_pass

        if not target_device_sn:
            logger.error("No device serial number (DAHUA_P2P_SN) provided.")
            return False

        # Auto-fetch playInfo if missing
        if not play_info:
            fetched_info = self.fetch_cloud_play_info(target_device_sn)
            if fetched_info:
                play_info = fetched_info

        # Decrypt playInfo if provided
        final_play_info = play_info
        if play_info:
            final_play_info = self.sdk.decrypt_play_info(play_info, target_device_sn)

        # 1. Initialize video play window (index 0)
        ret_init = self.sdk.init_video_play(self.handle, index=0, hwnd_ptr=hwnd_ptr)
        logger.info(f"init_video_play returned: {ret_init}")

        # 2. Call play_rtsp_real with P2P enabled (isTryP2P=True)
        ret_play = self.sdk.play_rtsp_real(
            handle=self.handle,
            token=token,
            device_id=target_device_sn,
            decrypt_key=target_decrypt_key,
            channel_id=channel_id,
            definition_mode=definition_mode,
            is_opt=False,
            play_info=final_play_info,
            is_try_p2p=True
        )

        logger.info(f"play_rtsp_real returned: {ret_play}")
        return ret_play == 0

    def stop_p2p_stream(self) -> bool:
        """
        Stop P2P live stream and cleanup.
        """
        if not self.handle:
            return True

        ret_stop = self.sdk.stop_rtsp_real(self.handle)
        self.sdk.uninit_video_play(self.handle)
        self.is_playing = False
        logger.info(f"stop_p2p_stream returned: {ret_stop}")
        return ret_stop == 0

    def capture_snapshot(self, save_path: str) -> bool:
        """
        Capture local snapshot frame to JPG file.
        """
        if not self.handle:
            return False
        ret = self.sdk.snap_shot(self.handle, save_path)
        return ret == 0
