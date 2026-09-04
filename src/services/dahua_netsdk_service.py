import os
import logging
from typing import Optional, Dict, Any
from dotenv import load_dotenv

from core.dahua_netsdk import (
    DahuaNetSDK, NET_DEVICEINFO_Ex,
    DH_PTZ_UP, DH_PTZ_DOWN, DH_PTZ_LEFT, DH_PTZ_RIGHT,
    DH_PTZ_ZOOM_ADD, DH_PTZ_ZOOM_DEC
)

logger = logging.getLogger(__name__)

class DahuaNetSDKService:
    """
    High-level Dahua General NetSDK Service (dhnetsdk.dll).
    Manages direct LAN/IP device connection, channels, realplay, PTZ, and video streaming.
    """
    _instance: Optional['DahuaNetSDKService'] = None

    def __init__(self, env_path: Optional[str] = None):
        if env_path is None:
            base_dir = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
            env_path = os.path.join(base_dir, '.env')

        if os.path.exists(env_path):
            load_dotenv(env_path)

        self.ip = os.getenv("DAHUA_IP", "").strip()
        self.port = int(os.getenv("DAHUA_PORT", "37777"))
        self.user = os.getenv("DAHUA_USER") or os.getenv("DAHUA_P2P_USER", "admin")
        self.password = os.getenv("DAHUA_PASS") or os.getenv("DAHUA_P2P_PASS", "")
        self.serial_number = os.getenv("DAHUA_SN") or os.getenv("DAHUA_P2P_SN", "")

        self.netsdk = DahuaNetSDK.get_instance()
        self.login_handle = 0
        self.device_info: Optional[NET_DEVICEINFO_Ex] = None
        self.active_play_handles: Dict[int, int] = {} # channel -> play_handle

    @classmethod
    def get_instance(cls) -> 'DahuaNetSDKService':
        if cls._instance is None:
            cls._instance = DahuaNetSDKService()
        return cls._instance

    def connect(self, ip: Optional[str] = None, port: Optional[int] = None, user: Optional[str] = None, password: Optional[str] = None) -> bool:
        """
        Login to Dahua Device via Direct NetSDK TCP Port (37777).
        """
        target_ip = ip if ip else self.ip
        target_port = port if port else self.port
        target_user = user if user else self.user
        target_pass = password if password else self.password

        if not target_ip:
            logger.debug("Dahua NetSDK Direct IP not configured in environment. Skipping auto-connect.")
            return False

        if self.login_handle > 0:
            logger.info("Already logged in via Dahua NetSDK.")
            return True

        try:
            logger.info(f"Connecting via Dahua General NetSDK to {target_ip}:{target_port} (User: {target_user})...")
            handle, dev_info = self.netsdk.login(target_ip, target_port, target_user, target_pass)

            if handle > 0:
                self.login_handle = handle
                self.device_info = dev_info
                sn = dev_info.sSerialNumber.decode('utf-8', errors='ignore').strip('\x00')
                logger.info(f"Dahua NetSDK Direct Login Successful! SN: {sn}, Total Channels: {dev_info.nChanNum}")
                return True
            else:
                logger.error(f"Dahua NetSDK Direct Login Failed for {target_ip}:{target_port}.")
                return False
        except Exception as e:
            logger.error(f"Exception during Dahua NetSDK login: {e}", exc_info=True)
            return False

    def get_total_channels(self) -> int:
        if self.device_info:
            return self.device_info.nChanNum
        return 0

    def get_serial_number(self) -> str:
        if self.device_info:
            return self.device_info.sSerialNumber.decode('utf-8', errors='ignore').strip('\x00')
        return self.serial_number

    def get_rtsp_url(self, channel: int = 1, subtype: int = 0, rtsp_port: int = 554) -> str:
        """
        Generate sanitized RTSP URL for OpenCV VideoCapture frame acquisition.
        """
        if not self.ip:
            return ""
        import urllib.parse
        encoded_pass = urllib.parse.quote(self.password, safe="")
        return f"rtsp://{self.user}:{encoded_pass}@{self.ip}:{rtsp_port}/cam/realmonitor?channel={channel}&subtype={subtype}"

    def start_channel_stream(self, channel: int = 0, hwnd_ptr: int = 0, stream_type: int = 0) -> int:
        """
        Start RealPlay stream for a channel. Returns play_handle.
        """
        if self.login_handle <= 0:
            if not self.connect():
                return 0

        play_handle = self.netsdk.start_real_play(self.login_handle, channel=channel, hwnd_ptr=hwnd_ptr, stream_type=stream_type)
        if play_handle > 0:
            self.active_play_handles[channel] = play_handle
            logger.info(f"RealPlay stream started for Channel {channel} (PlayHandle: {play_handle}).")
        else:
            logger.error(f"Failed to start RealPlay stream for Channel {channel}.")
        return play_handle

    def stop_channel_stream(self, channel: int = 0) -> bool:
        play_handle = self.active_play_handles.pop(channel, 0)
        if play_handle > 0:
            res = self.netsdk.stop_real_play(play_handle)
            logger.info(f"Stopped RealPlay stream for Channel {channel}.")
            return res
        return True

    def ptz_move_up(self, channel: int = 0, speed: int = 4, stop: bool = False) -> bool:
        return self.netsdk.ptz_control(self.login_handle, channel, DH_PTZ_UP, speed, stop)

    def ptz_move_down(self, channel: int = 0, speed: int = 4, stop: bool = False) -> bool:
        return self.netsdk.ptz_control(self.login_handle, channel, DH_PTZ_DOWN, speed, stop)

    def ptz_move_left(self, channel: int = 0, speed: int = 4, stop: bool = False) -> bool:
        return self.netsdk.ptz_control(self.login_handle, channel, DH_PTZ_LEFT, speed, stop)

    def ptz_move_right(self, channel: int = 0, speed: int = 4, stop: bool = False) -> bool:
        return self.netsdk.ptz_control(self.login_handle, channel, DH_PTZ_RIGHT, speed, stop)

    def disconnect(self):
        if self.login_handle > 0:
            for ch in list(self.active_play_handles.keys()):
                self.stop_channel_stream(ch)
            self.netsdk.logout(self.login_handle)
            self.login_handle = 0
            logger.info("Disconnected Dahua NetSDK session.")
