import os
import sys
import ctypes
import logging
from typing import Callable, Optional, Dict, Any

logger = logging.getLogger(__name__)

# Callback ctypes prototypes
# void(*LCOpenSDK_onPlayerResult)(int index, const char* code, int resultSource);
ON_PLAYER_RESULT_CB = ctypes.CFUNCTYPE(None, ctypes.c_int, ctypes.c_char_p, ctypes.c_int)

# void(*LCOpenSDK_onResolutionChanged)(int index, int width, int height);
ON_RESOLUTION_CHANGED_CB = ctypes.CFUNCTYPE(None, ctypes.c_int, ctypes.c_int, ctypes.c_int)

# void(*LCOpenSDK_onPlayBegan)(int index);
ON_PLAY_BEGAN_CB = ctypes.CFUNCTYPE(None, ctypes.c_int)

# void(*LCOpenSDK_onReceiveData)(int index, int len);
ON_RECEIVE_DATA_CB = ctypes.CFUNCTYPE(None, ctypes.c_int, ctypes.c_int)

# void(*LCOpenSDK_onPlayFinished)(int index);
ON_PLAY_FINISHED_CB = ctypes.CFUNCTYPE(None, ctypes.c_int)

# void(*LCOpenSDK_onPlayerTime)(int index, long time);
ON_PLAYER_TIME_CB = ctypes.CFUNCTYPE(None, ctypes.c_int, ctypes.c_long)

class DahuaSDK:
    """
    Low-level Python wrapper over Dahua LCOpenSDKmd.dll C API.
    """
    _instance: Optional['DahuaSDK'] = None

    def __init__(self, release_dir: Optional[str] = None):
        if release_dir is None:
            base_dir = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
            candidates = [
                os.path.join(base_dir, 'src', 'assets', 'libs', 'IoTApplication_VideoPlay_PC_C_Plus_Plus_V3.3.1', 'Demo', 'x64', 'Release'),
                os.path.join(base_dir, 'src', 'assets', 'libs', 'lcopensdk'),
                os.path.join(base_dir, 'src', 'assets', 'libs'),
                os.path.join(base_dir, 'assets', 'libs'),
                os.path.join(os.getcwd(), 'libs'),
            ]
            release_dir = next((p for p in candidates if os.path.exists(os.path.join(p, 'LCOpenSDKmd.dll'))), candidates[0])

        self.release_dir = release_dir
        self.dll: Optional[ctypes.CDLL] = None
        self._callback_refs: Dict[str, Any] = {}
        self.loaded = False

    @classmethod
    def get_instance(cls, release_dir: Optional[str] = None) -> 'DahuaSDK':
        if cls._instance is None:
            cls._instance = DahuaSDK(release_dir)
        return cls._instance

    def initialize_dll(self) -> bool:
        if self.loaded and self.dll:
            return True

        dll_path = os.path.join(self.release_dir, 'LCOpenSDKmd.dll')
        if not os.path.exists(self.release_dir) or not os.path.exists(dll_path):
            logger.info(f"Dahua LCOpenSDK DLL (LCOpenSDKmd.dll) not found at {self.release_dir}. Direct stream mode active.")
            return False

        try:
            # On Windows Python 3.8+, add dll directory to search path
            if hasattr(os, 'add_dll_directory'):
                os.add_dll_directory(self.release_dir)

            dll_path = os.path.join(self.release_dir, 'LCOpenSDKmd.dll')
            if not os.path.exists(dll_path):
                logger.error(f"LCOpenSDKmd.dll not found at {dll_path}")
                return False

            self.dll = ctypes.CDLL(dll_path)
            self._setup_function_signatures()
            self.loaded = True
            logger.info("Successfully loaded LCOpenSDKmd.dll and configured signatures.")
            return True
        except Exception as e:
            logger.error(f"Failed to load LCOpenSDKmd.dll: {e}", exc_info=True)
            return False

    def _setup_function_signatures(self):
        assert self.dll is not None

        # Utils
        self.dll.LCOpenSdk_Utils_LoadSubModules.restype = None
        self.dll.LCOpenSdk_Utils_LoadSubModules.argtypes = []

        self.dll.LCOpenSdk_Utils_SetMobileLogLevel.restype = None
        self.dll.LCOpenSdk_Utils_SetMobileLogLevel.argtypes = [ctypes.c_int]

        self.dll.LCOpenSDK_Api_InitOpenApi.restype = None
        self.dll.LCOpenSDK_Api_InitOpenApi.argtypes = [ctypes.c_char_p, ctypes.c_int, ctypes.c_char_p]

        self.dll.LCOpenSDK_Api_UninitOpenApi.restype = None
        self.dll.LCOpenSDK_Api_UninitOpenApi.argtypes = []

        # VideoPlay Handle Management
        self.dll.LCOpenSDK_VideoPlay_CreateHandle.restype = ctypes.c_void_p
        self.dll.LCOpenSDK_VideoPlay_CreateHandle.argtypes = []

        self.dll.LCOpenSDK_VideoPlay_InitVideoPlay.restype = ctypes.c_int
        self.dll.LCOpenSDK_VideoPlay_InitVideoPlay.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_void_p]

        self.dll.LCOpenSDK_VideoPlay_UninitVideoPlay.restype = None
        self.dll.LCOpenSDK_VideoPlay_UninitVideoPlay.argtypes = [ctypes.c_void_p]

        # VideoPlay Stream Control
        self.dll.LCOpenSDK_VideoPlay_PlayRtspReal.restype = ctypes.c_int
        self.dll.LCOpenSDK_VideoPlay_PlayRtspReal.argtypes = [
            ctypes.c_void_p,    # handle
            ctypes.c_char_p,    # token
            ctypes.c_char_p,    # deviceID
            ctypes.c_char_p,    # decryptKey
            ctypes.c_int,       # channelID
            ctypes.c_int,       # definitionMode (0: HD, 1: SD)
            ctypes.c_bool,      # isOpt
            ctypes.c_char_p,    # playInfo
            ctypes.c_bool       # isTryP2P
        ]

        self.dll.LCOpenSDK_VideoPlay_StopRtspReal.restype = ctypes.c_int
        self.dll.LCOpenSDK_VideoPlay_StopRtspReal.argtypes = [ctypes.c_void_p]

        self.dll.LCOpenSDK_VideoPlay_PlayAudio.restype = ctypes.c_int
        self.dll.LCOpenSDK_VideoPlay_PlayAudio.argtypes = [ctypes.c_void_p]

        self.dll.LCOpenSDK_VideoPlay_StopAudio.restype = ctypes.c_int
        self.dll.LCOpenSDK_VideoPlay_StopAudio.argtypes = [ctypes.c_void_p]

        self.dll.LCOpenSDK_VideoPlay_Pause.restype = ctypes.c_int
        self.dll.LCOpenSDK_VideoPlay_Pause.argtypes = [ctypes.c_void_p]

        self.dll.LCOpenSDK_VideoPlay_Resume.restype = ctypes.c_int
        self.dll.LCOpenSDK_VideoPlay_Resume.argtypes = [ctypes.c_void_p]

        self.dll.LCOpenSDK_VideoPlay_SnapShot.restype = ctypes.c_int
        self.dll.LCOpenSDK_VideoPlay_SnapShot.argtypes = [ctypes.c_void_p, ctypes.c_char_p]

        self.dll.LCOpenSDK_VideoPlay_StartRecord.restype = ctypes.c_int
        self.dll.LCOpenSDK_VideoPlay_StartRecord.argtypes = [
            ctypes.c_void_p, ctypes.c_char_p, ctypes.c_int, ctypes.c_longlong, ctypes.c_int
        ]

        self.dll.LCOpenSDK_VideoPlay_StopRecord.restype = ctypes.c_int
        self.dll.LCOpenSDK_VideoPlay_StopRecord.argtypes = [ctypes.c_void_p]

        self.dll.LCOpenSDK_VideoPlay_GetCurrentStreamMode.restype = ctypes.c_int
        self.dll.LCOpenSDK_VideoPlay_GetCurrentStreamMode.argtypes = [ctypes.c_void_p]

        # Callbacks
        self.dll.LCOpenSDK_VideoPlay_Set_onPlayerResult_Callback.restype = None
        self.dll.LCOpenSDK_VideoPlay_Set_onPlayerResult_Callback.argtypes = [ON_PLAYER_RESULT_CB]

        self.dll.LCOpenSDK_VideoPlay_Set_onResolutionChanged_Callback.restype = None
        self.dll.LCOpenSDK_VideoPlay_Set_onResolutionChanged_Callback.argtypes = [ON_RESOLUTION_CHANGED_CB]

        self.dll.LCOpenSDK_VideoPlay_Set_onPlayBegan_Callback.restype = None
        self.dll.LCOpenSDK_VideoPlay_Set_onPlayBegan_Callback.argtypes = [ON_PLAY_BEGAN_CB]

        self.dll.LCOpenSDK_VideoPlay_Set_onReceiveData_Callback.restype = None
        self.dll.LCOpenSDK_VideoPlay_Set_onReceiveData_Callback.argtypes = [ON_RECEIVE_DATA_CB]

        self.dll.LCOpenSDK_VideoPlay_Set_onPlayFinished_Callback.restype = None
        self.dll.LCOpenSDK_VideoPlay_Set_onPlayFinished_Callback.argtypes = [ON_PLAY_FINISHED_CB]

        self.dll.LCOpenSDK_VideoPlay_Set_onPlayerTime_Callback.restype = None
        self.dll.LCOpenSDK_VideoPlay_Set_onPlayerTime_Callback.argtypes = [ON_PLAYER_TIME_CB]

        # Crypter APIs
        try:
            self.dll.LCOpenSDK_Crypter_CreateHandle.restype = ctypes.c_void_p
            self.dll.LCOpenSDK_Crypter_CreateHandle.argtypes = []

            self.dll.LCOpenSDK_Crypter_InitWithRuleVersion.restype = ctypes.c_bool
            self.dll.LCOpenSDK_Crypter_InitWithRuleVersion.argtypes = [ctypes.c_void_p, ctypes.c_int]

            self.dll.LCOpenSDK_Crypter_DecryptIOTPlayInfo.restype = ctypes.c_int
            self.dll.LCOpenSDK_Crypter_DecryptIOTPlayInfo.argtypes = [
                ctypes.c_void_p, ctypes.c_char_p, ctypes.c_int,
                ctypes.c_char_p, ctypes.c_int,
                ctypes.c_char_p, ctypes.c_int,
                ctypes.c_char_p, ctypes.POINTER(ctypes.c_int)
            ]
        except AttributeError:
            logger.warning("Crypter functions not available in current DLL.")

    def decrypt_play_info(self, raw_play_info: str, device_id: str, salt: str = "") -> str:
        """
        Decrypt encrypted playInfo payload received from Dahua Cloud API.
        """
        if not self.dll or not hasattr(self.dll, 'LCOpenSDK_Crypter_CreateHandle'):
            return raw_play_info

        try:
            crypter_handle = self.dll.LCOpenSDK_Crypter_CreateHandle()
            if not crypter_handle:
                return raw_play_info

            self.dll.LCOpenSDK_Crypter_InitWithRuleVersion(crypter_handle, 1)

            src_buf = raw_play_info.encode('utf-8')
            dev_buf = device_id.encode('utf-8')
            salt_buf = salt.encode('utf-8')

            out_buf = ctypes.create_string_buffer(4096)
            out_len = ctypes.c_int(4096)

            ret = self.dll.LCOpenSDK_Crypter_DecryptIOTPlayInfo(
                crypter_handle,
                src_buf, len(src_buf),
                dev_buf, len(dev_buf),
                salt_buf, len(salt_buf),
                out_buf, ctypes.byref(out_len)
            )

            if ret == 0:
                decrypted_str = out_buf.value.decode('utf-8', errors='ignore')
                logger.info("Successfully decrypted playInfo payload.")
                return decrypted_str
            else:
                logger.warning(f"decryptIOTPlayInfo failed with code: {ret}")
                return raw_play_info
        except Exception as e:
            logger.error(f"Error decrypting playInfo: {e}")
            return raw_play_info

    # API Public Wrapper Methods
    def load_sub_modules(self):
        if self.dll:
            self.dll.LCOpenSdk_Utils_LoadSubModules()

    def set_mobile_log_level(self, level: int = 5):
        if self.dll:
            self.dll.LCOpenSdk_Utils_SetMobileLogLevel(level)

    def init_open_api(self, host: str, port: int = 443, ca_path: Optional[str] = None):
        if self.dll:
            ca_bytes = ca_path.encode('utf-8') if ca_path else None
            self.dll.LCOpenSDK_Api_InitOpenApi(host.encode('utf-8'), port, ca_bytes)

    def create_handle(self) -> ctypes.c_void_p:
        if not self.dll:
            raise RuntimeError("SDK DLL not initialized.")
        return self.dll.LCOpenSDK_VideoPlay_CreateHandle()

    def init_video_play(self, handle: ctypes.c_void_p, index: int, hwnd_ptr: int = 0) -> int:
        if not self.dll:
            return -1
        return self.dll.LCOpenSDK_VideoPlay_InitVideoPlay(handle, index, ctypes.c_void_p(hwnd_ptr))

    def uninit_video_play(self, handle: ctypes.c_void_p):
        if self.dll and handle:
            self.dll.LCOpenSDK_VideoPlay_UninitVideoPlay(handle)

    def play_rtsp_real(
        self,
        handle: ctypes.c_void_p,
        token: str,
        device_id: str,
        decrypt_key: str,
        channel_id: int = 0,
        definition_mode: int = 0,
        is_opt: bool = False,
        play_info: str = "",
        is_try_p2p: bool = True
    ) -> int:
        if not self.dll:
            return -1
        return self.dll.LCOpenSDK_VideoPlay_PlayRtspReal(
            handle,
            token.encode('utf-8'),
            device_id.encode('utf-8'),
            decrypt_key.encode('utf-8'),
            channel_id,
            definition_mode,
            is_opt,
            play_info.encode('utf-8'),
            is_try_p2p
        )

    def stop_rtsp_real(self, handle: ctypes.c_void_p) -> int:
        if not self.dll:
            return -1
        return self.dll.LCOpenSDK_VideoPlay_StopRtspReal(handle)

    def play_audio(self, handle: ctypes.c_void_p) -> int:
        if not self.dll:
            return -1
        return self.dll.LCOpenSDK_VideoPlay_PlayAudio(handle)

    def stop_audio(self, handle: ctypes.c_void_p) -> int:
        if not self.dll:
            return -1
        return self.dll.LCOpenSDK_VideoPlay_StopAudio(handle)

    def pause(self, handle: ctypes.c_void_p) -> int:
        if not self.dll:
            return -1
        return self.dll.LCOpenSDK_VideoPlay_Pause(handle)

    def resume(self, handle: ctypes.c_void_p) -> int:
        if not self.dll:
            return -1
        return self.dll.LCOpenSDK_VideoPlay_Resume(handle)

    def snap_shot(self, handle: ctypes.c_void_p, file_path: str) -> int:
        if not self.dll:
            return -1
        return self.dll.LCOpenSDK_VideoPlay_SnapShot(handle, file_path.encode('utf-8'))

    def set_on_player_result_callback(self, callback_func: Callable[[int, str, int], None]):
        if not self.dll:
            return
        def _wrapper(index: int, code_ptr: bytes, result_source: int):
            code_str = code_ptr.decode('utf-8', errors='ignore') if code_ptr else ""
            callback_func(index, code_str, result_source)
        
        c_cb = ON_PLAYER_RESULT_CB(_wrapper)
        self._callback_refs['onPlayerResult'] = c_cb
        self.dll.LCOpenSDK_VideoPlay_Set_onPlayerResult_Callback(c_cb)

    def set_on_play_began_callback(self, callback_func: Callable[[int], None]):
        if not self.dll:
            return
        def _wrapper(index: int):
            callback_func(index)
        
        c_cb = ON_PLAY_BEGAN_CB(_wrapper)
        self._callback_refs['onPlayBegan'] = c_cb
        self.dll.LCOpenSDK_VideoPlay_Set_onPlayBegan_Callback(c_cb)
