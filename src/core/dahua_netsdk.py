import os
import sys
import ctypes
import logging
from typing import Optional, Callable, Dict, Any

logger = logging.getLogger(__name__)

# Callback Prototype for Disconnect Event
# void(CALLBACK *fDisConnect)(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
DISCONNECT_CB = ctypes.CFUNCTYPE(None, ctypes.c_longlong, ctypes.c_char_p, ctypes.c_int, ctypes.c_size_t)

# Callback Prototype for RealData Event
# void(CALLBACK *fRealDataCallBackEx2)(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LONG param, LDWORD dwUser)
REALDATA_CB_EX2 = ctypes.CFUNCTYPE(None, ctypes.c_longlong, ctypes.c_uint, ctypes.POINTER(ctypes.c_ubyte), ctypes.c_uint, ctypes.c_long, ctypes.c_size_t)

class NET_DEVICEINFO_Ex(ctypes.Structure):
    """Dahua NetSDK Device Info Structure"""
    _fields_ = [
        ("sSerialNumber", ctypes.c_char * 48),    # Device Serial Number
        ("nAlarmInPortCount", ctypes.c_int),      # Alarm input count
        ("nAlarmOutPortCount", ctypes.c_int),     # Alarm output count
        ("nDiskCount", ctypes.c_int),            # Hard disk count
        ("nDVRType", ctypes.c_int),              # DVR Type
        ("nChanNum", ctypes.c_int),              # Total Channels
        ("byLimitLoginTime", ctypes.c_byte),
        ("byLeftLogTimes", ctypes.c_byte),
        ("bReserved", ctypes.c_byte * 2),
        ("nLockLeftTime", ctypes.c_int),
        ("sReserved", ctypes.c_char * 24),
    ]

# PTZ Command Constants
DH_PTZ_UP = 0
DH_PTZ_DOWN = 1
DH_PTZ_LEFT = 2
DH_PTZ_RIGHT = 3
DH_PTZ_ZOOM_ADD = 4
DH_PTZ_ZOOM_DEC = 5
DH_PTZ_FOCUS_ADD = 6
DH_PTZ_FOCUS_DEC = 7

class DahuaNetSDK:
    """
    Low-level Python Wrapper for Dahua General NetSDK (dhnetsdk.dll).
    Direct LAN/WAN TCP Communication without Cloud.
    """
    _instance: Optional['DahuaNetSDK'] = None

    def __init__(self, release_dir: Optional[str] = None):
        if release_dir is None:
            base_dir = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
            release_dir = os.path.join(
                base_dir,
                'src', 'assets', 'libs', 'IoTApplication_VideoPlay_PC_C_Plus_Plus_V3.3.1',
                'Demo', 'x64', 'Release'
            )

        self.release_dir = release_dir
        self.dll: Optional[ctypes.CDLL] = None
        self.loaded = False
        self._disconnect_cb_ref = None

    @classmethod
    def get_instance(cls, release_dir: Optional[str] = None) -> 'DahuaNetSDK':
        if cls._instance is None:
            cls._instance = DahuaNetSDK(release_dir)
        return cls._instance

    def initialize_dll(self) -> bool:
        if self.loaded and self.dll:
            return True

        if not os.path.exists(self.release_dir):
            logger.error(f"Release directory for NetSDK not found: {self.release_dir}")
            return False

        try:
            if hasattr(os, 'add_dll_directory'):
                os.add_dll_directory(self.release_dir)

            dll_path = os.path.join(self.release_dir, 'dhnetsdk.dll')
            if not os.path.exists(dll_path):
                logger.error(f"dhnetsdk.dll not found at {dll_path}")
                return False

            self.dll = ctypes.CDLL(dll_path)
            self._setup_function_signatures()
            self.loaded = True

            # Init NetSDK
            @DISCONNECT_CB
            def _on_disconnect(lLoginID, pchDVRIP, nDVRPort, dwUser):
                ip_str = pchDVRIP.decode('utf-8', errors='ignore') if pchDVRIP else ""
                logger.warning(f"[Dahua NetSDK] Device disconnected: {ip_str}:{nDVRPort} (LoginID: {lLoginID})")

            self._disconnect_cb_ref = _on_disconnect
            init_ok = self.dll.CLIENT_Init(_on_disconnect, 0)
            logger.info(f"Dahua NetSDK (dhnetsdk.dll) CLIENT_Init status: {init_ok}")
            return init_ok
        except Exception as e:
            logger.error(f"Failed to load dhnetsdk.dll: {e}", exc_info=True)
            return False

    def _setup_function_signatures(self):
        assert self.dll is not None

        # CLIENT_Init
        self.dll.CLIENT_Init.restype = ctypes.c_bool
        self.dll.CLIENT_Init.argtypes = [DISCONNECT_CB, ctypes.c_size_t]

        # CLIENT_Cleanup
        self.dll.CLIENT_Cleanup.restype = None
        self.dll.CLIENT_Cleanup.argtypes = []

        # CLIENT_LoginEx2
        self.dll.CLIENT_LoginEx2.restype = ctypes.c_longlong
        self.dll.CLIENT_LoginEx2.argtypes = [
            ctypes.c_char_p,                 # pchDVRIP
            ctypes.c_ushort,                 # wDVRPort
            ctypes.c_char_p,                 # pchUserName
            ctypes.c_char_p,                 # pchPassword
            ctypes.c_int,                    # nSpecCap
            ctypes.c_void_p,                 # pCapParam
            ctypes.POINTER(NET_DEVICEINFO_Ex),# lpDeviceInfo
            ctypes.POINTER(ctypes.c_int)     # error
        ]

        # CLIENT_Logout
        self.dll.CLIENT_Logout.restype = ctypes.c_bool
        self.dll.CLIENT_Logout.argtypes = [ctypes.c_longlong]

        # CLIENT_RealPlayEx
        self.dll.CLIENT_RealPlayEx.restype = ctypes.c_longlong
        self.dll.CLIENT_RealPlayEx.argtypes = [
            ctypes.c_longlong, # lLoginID
            ctypes.c_int,      # nChannelID
            ctypes.c_void_p,   # hWnd
            ctypes.c_int       # rType (0: RealPlay, 1: MultiPlay, etc.)
        ]

        # CLIENT_StopRealPlayEx
        self.dll.CLIENT_StopRealPlayEx.restype = ctypes.c_bool
        self.dll.CLIENT_StopRealPlayEx.argtypes = [ctypes.c_longlong]

        # CLIENT_SetRealDataCallBackEx2
        self.dll.CLIENT_SetRealDataCallBackEx2.restype = ctypes.c_bool
        self.dll.CLIENT_SetRealDataCallBackEx2.argtypes = [
            ctypes.c_longlong, # lRealHandle
            REALDATA_CB_EX2,   # cbRealData
            ctypes.c_size_t,   # dwUser
            ctypes.c_uint      # dwFlag (1: RealData, 2: FrameData)
        ]

        # CLIENT_DHPTZControlEx2
        self.dll.CLIENT_DHPTZControlEx2.restype = ctypes.c_bool
        self.dll.CLIENT_DHPTZControlEx2.argtypes = [
            ctypes.c_longlong, # lLoginID
            ctypes.c_int,      # nChannelID
            ctypes.c_uint,     # dwPTZCommand
            ctypes.c_int,      # lParam1 (step / speed 1-8)
            ctypes.c_int,      # lParam2
            ctypes.c_int,      # lParam3
            ctypes.c_bool,     # dwStop (True: stop, False: start)
            ctypes.c_void_p    # param4
        ]

    def login(self, ip: str, port: int, user: str, password: str) -> tuple[int, NET_DEVICEINFO_Ex]:
        """
        Login directly to Dahua device via NetSDK (Port 37777).
        Returns (login_handle, NET_DEVICEINFO_Ex).
        """
        if not self.initialize_dll():
            raise RuntimeError("Dahua NetSDK not initialized.")

        dev_info = NET_DEVICEINFO_Ex()
        error_code = ctypes.c_int(0)

        login_handle = self.dll.CLIENT_LoginEx2(
            ip.encode('utf-8'),
            port,
            user.encode('utf-8'),
            password.encode('utf-8'),
            0,
            None,
            ctypes.byref(dev_info),
            ctypes.byref(error_code)
        )

        if login_handle <= 0:
            logger.error(f"CLIENT_LoginEx2 failed for {ip}:{port}. Error code: {error_code.value}")
        else:
            sn = dev_info.sSerialNumber.decode('utf-8', errors='ignore').strip('\x00')
            logger.info(f"CLIENT_LoginEx2 succeeded for {ip}:{port} (Handle: {login_handle}, SN: {sn}, Channels: {dev_info.nChanNum})")

        return login_handle, dev_info

    def logout(self, login_handle: int) -> bool:
        if self.dll and login_handle > 0:
            return self.dll.CLIENT_Logout(login_handle)
        return True

    def start_real_play(self, login_handle: int, channel: int = 0, hwnd_ptr: int = 0, stream_type: int = 0) -> int:
        """
        Start RealPlay stream for specified channel.
        """
        if not self.dll or login_handle <= 0:
            return 0
        return self.dll.CLIENT_RealPlayEx(login_handle, channel, ctypes.c_void_p(hwnd_ptr), stream_type)

    def stop_real_play(self, play_handle: int) -> bool:
        if self.dll and play_handle > 0:
            return self.dll.CLIENT_StopRealPlayEx(play_handle)
        return True

    def ptz_control(self, login_handle: int, channel: int, command: int, speed: int = 4, stop: bool = False) -> bool:
        """
        Control PTZ camera movement.
        """
        if not self.dll or login_handle <= 0:
            return False
        return self.dll.CLIENT_DHPTZControlEx2(login_handle, channel, command, speed, 0, 0, stop, None)

    def cleanup(self):
        if self.dll:
            self.dll.CLIENT_Cleanup()
            self.loaded = False
