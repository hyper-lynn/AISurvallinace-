#ifndef _C_API_LCOPENSDK_H_
#define _C_API_LCOPENSDK_H_

#ifdef C_API_LCOPENSDK_EXPORTS
# define C_API_LCOPENSDK_EXPORT extern "C" _declspec(dllexport)
#else
# define C_API_LCOPENSDK_EXPORT
#endif

C_API_LCOPENSDK_EXPORT void LCOpenSDK_Api_InitOpenApi(const char* host, int port, const char* caPath);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_Api_Request(void* req, void* resp, int timeout, void* pOpenApiClient, const char* playInfo);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_Api_UninitOpenApi();

typedef struct _LCOpenSDK_PTZParams_
{
    const char* deviceId;
    const char* playInfo;
    int channelId;
    const char* operation;
    int duration;
    double speed;
}LCOpenSDK_PTZParams;
C_API_LCOPENSDK_EXPORT int LCOpenSDK_Api_ControlMovePtz(LCOpenSDK_PTZParams* params);

typedef void(*LCOpenSDK_onPlayerResult)(int index, const char* code, int resultSource);
typedef void(*LCOpenSDK_onResolutionChanged)(int index, int width, int height);
typedef void(*LCOpenSDK_onPlayBegan)(int index);
typedef void(*LCOpenSDK_onReceiveData)(int index, int len);
typedef void(*LCOpenSDK_onStreamCallback)(int index, const unsigned char* data, unsigned int dataLen);
typedef void(*LCOpenSDK_onPlayFinished)(int index);
typedef void(*LCOpenSDK_onPlayerTime)(int index, long time);
typedef void(*LCOpenSDK_onIVSInfo)(int index, char* pBuf, long lType, long lLen, long lReallen);
typedef void(*LCOpenSDK_onProgressStatus)(int index, const char* status);
typedef void(*LCOpenSDK_onFrameLost)(const char* context);
typedef void(*LCOpenSDK_onRecordStop)(const char* context, int error);
typedef void(*LCOpenSDK_onFileTime)(const char* context, long beginTime, long endTime);
typedef void(*LCOpenSDK_onNetworkDisconnected)(const char* context);
typedef void(*LCOpenSDK_onBadFile)(const char* context);
typedef void(*LCOpenSDK_onDraw)(const char* context, void *hdc);
typedef void(*LCOpenSDK_onPlayerTimeAndStamp)(const char* context, long time, long stampTime);
typedef void(*LCOpenSDK_onAudioTimeAndStamp)(const char* context, long time, long stampTime, bool isDetach);
typedef void(*LCOpenSDK_onStreamLogInfo)(const char* context, const char* message, unsigned int length);
typedef void(*LCOpenSDK_onIPFrameTimeOver)(const char* context, long timeInterval);
typedef void(*LCOpenSDK_onConnectInfoConfig)(const char* context, const char* message, int msgLen, const char* ip, int ipLen, int localPort, int remotePort, const char* deviceSn, int snLen);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onPlayerResult_Callback(LCOpenSDK_onPlayerResult cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onResolutionChanged_Callback(LCOpenSDK_onResolutionChanged cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onPlayBegan_Callback(LCOpenSDK_onPlayBegan cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onReceiveData_Callback(LCOpenSDK_onReceiveData cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onStreamCallback_Callback(LCOpenSDK_onStreamCallback cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onPlayFinished_Callback(LCOpenSDK_onPlayFinished cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onPlayerTime_Callback(LCOpenSDK_onPlayerTime cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onIVSInfo_Callback(LCOpenSDK_onIVSInfo cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onProgressStatus_Callback(LCOpenSDK_onProgressStatus cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onFrameLost_Callback(LCOpenSDK_onFrameLost cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onRecordStop_Callback(LCOpenSDK_onRecordStop cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onFileTime_Callback(LCOpenSDK_onFileTime cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onNetworkDisconnected_Callback(LCOpenSDK_onNetworkDisconnected cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onBadFile_Callback(LCOpenSDK_onBadFile cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onDraw_Callback(LCOpenSDK_onDraw cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onPlayerTimeAndStamp_Callback(LCOpenSDK_onPlayerTimeAndStamp cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onAudioTimeAndStamp_Callback(LCOpenSDK_onAudioTimeAndStamp cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onStreamLogInfo_Callback(LCOpenSDK_onStreamLogInfo cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onIPFrameTimeOver_Callback(LCOpenSDK_onIPFrameTimeOver cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Set_onConnectInfoConfig_Callback(LCOpenSDK_onConnectInfoConfig cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_SetStreamCallback(void* handle, int streamFormat);

C_API_LCOPENSDK_EXPORT void* LCOpenSDK_VideoPlay_CreateHandle();
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_InitVideoPlay(void* handle, int index, void* hWnd);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_UninitVideoPlay(void* handle);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_PlayRtspReal(void* handle, const char* token, const char* deviceID, const char* decryptKey, int channelID, int definitionMode, bool isOpt, const char* playInfo, bool isTryP2P);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_StopRtspReal(void* handle);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_PlayDeviceRecord(void* handle, const char* token, const char* deviceID, const char* decryptKey, int channelID, const char* fileID, int needBeginTime, int needEndTime, int streamType, const char* playInfo, bool isTryP2P);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_StopDeviceRecord(void* handle);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_PlayCloud(void* handle, const char* deviceID, int channelID, const char* decryptKey, const char* recordId, int offsetTime, const char* playInfo, const char* signatureUrl, const char* recordPath, const char* recordRegionId);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_StopCloud(void* handle);

C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_PlayAudio(void* handle);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_StopAudio(void* handle);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_Seek(void* handle, long seconds);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_Pause(void* handle);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_Resume(void* handle);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_rewake(void* handle);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_SnapShot(void* handle, const char* filePath);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_StartRecord(void* handle, const char* filePath, int recordType, long long spaceRemain, int convertMode);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_StopRecord(void* handle);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_SetPlaySpeed(void* handle, float speed);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_SetIndex(void* handle, int index);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_GetIndex(void* handle);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_DoScale(void* handle, float scale);
C_API_LCOPENSDK_EXPORT float LCOpenSDK_VideoPlay_GetScale(void* handle);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_Translate(void* handle, float x, float y);
C_API_LCOPENSDK_EXPORT float LCOpenSDK_VideoPlay_GetTranslateX(void* handle);
C_API_LCOPENSDK_EXPORT float LCOpenSDK_VideoPlay_GetTranslateY(void* handle);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_SetMaxScale(void* handle, float maxScale);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_SetIdentity(void* handle);
C_API_LCOPENSDK_EXPORT Dahua::LCOpenSDK::E_STREAM_MODE LCOpenSDK_VideoPlay_GetCurrentStreamMode(void* handle);
C_API_LCOPENSDK_EXPORT bool LCOpenSDK_VideoPlay_SetSEnhanceMode(void* handle, int mode);
C_API_LCOPENSDK_EXPORT bool LCOpenSDK_VideoPlay_IsRecording(void* handle);
C_API_LCOPENSDK_EXPORT bool LCOpenSDK_VideoPlay_IsStreamPlayed(void* handle);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_VideoPlay_GetPlayerStatus(void* handle);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_SetKey(void* handle, const char* passwordKey);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_VideoPlay_SetDecodeEngine(void* handle, int engineType);


typedef struct _LCOpenSDK_DEVICE_INIT_INFO_
{
    char szMac[64];
    char szIp[64];
    int  port;
    int  initStatus;
}LCOpenSDK_DEVICE_INIT_INFO;
C_API_LCOPENSDK_EXPORT int LCOpenSDK_DeviceInit_SearchDeviceInitInfo(const char* deviceId, LCOpenSDK_DEVICE_INIT_INFO* devInitInfo, int timeout);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_DeviceInit_Multicast_InitDevice(const char* szMac, const char* pwd);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_DeviceInit_Unicast_InitDevice(const char* szMac, const char* pwd, const char* szIp);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_DeviceInit_CheckPwdValidity(const char* deviceId, const char* szIp, int port, const char* pwd);

typedef void(*LCOpenSDK_onDownloadState)(int index, const char* code, int type);
typedef void(*LCOpenSDK_onDownloadReceiveData)(int index, int datalen);
typedef void(*LCOpenSDK_onDownloadOnProgress)(int index, float progress, int type);
typedef void(*LCOpenSDK_onThumbnailState)(int index, int code);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_Download_Set_onDownloadState_Callback(LCOpenSDK_onDownloadState cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_Download_Set_onDownloadReceiveData_Callback(LCOpenSDK_onDownloadReceiveData cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_Download_Set_onDownloadProgress_Callback(LCOpenSDK_onDownloadOnProgress cb);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_Download_StartDownload_DeviceRecord(int index, const char* token, const char* filepath, const char* deviceID, const char* decryptKey, const char* fileID, int beginTime, int endTime, const char* playInfo, int channelID);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_Download_StartDownload_CloudRecord(int index, const char* filepath, const char* deviceID, int channelID, const char* recordId, int needBeginTime, int needEndTime, int offsetTime, const char* playInfo, const char* signatureUrl, const char* recordPath, const char* recordRegionId);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_Download_StopDownload(int index);
						

C_API_LCOPENSDK_EXPORT bool LCOpenSDK_LoginManager_AddDevices(const char* token, const char* deviceJsonString);


C_API_LCOPENSDK_EXPORT int  LCOpenSDK_Utils_DecryptPic(const char *pSrcBufIn,int srcBufLenIn,const char *encryptKey, const char *sDevId,const char *sDevPwd, char *pDestBufOut,int* destBufLenOut);
C_API_LCOPENSDK_EXPORT void LCOpenSdk_Utils_SetLogInfo(int level, const char* fileName, int maxSize, int fileMode);

C_API_LCOPENSDK_EXPORT const char* LCOpenSdk_Utils_GetSaveStreamPath();
C_API_LCOPENSDK_EXPORT void LCOpenSdk_Utils_ComputeMD5Upper(const char* srcStr, char outStr[128]);
C_API_LCOPENSDK_EXPORT void LCOpenSdk_Utils_ComputeMD5Lower(const char* srcStr, char outStr[128]);
C_API_LCOPENSDK_EXPORT char* LCOpenSdk_Utils_Sha512Cry(const char* data);
C_API_LCOPENSDK_EXPORT void LCOpenSdk_Utils_Compute1(const char* srcStr, char outStr[128]);
C_API_LCOPENSDK_EXPORT void LCOpenSdk_Utils_Compute2(const char* srcStr, char outStr[128]);
C_API_LCOPENSDK_EXPORT void LCOpenSdk_Utils_GetMac(char outMac[128]);
C_API_LCOPENSDK_EXPORT void LCOpenSdk_Utils_GetOsVersion(char outMac[128]);
C_API_LCOPENSDK_EXPORT void LCOpenSdk_Utils_LoadSubModules();
C_API_LCOPENSDK_EXPORT void LCOpenSdk_Utils_SetMobileLogLevel(int level);
C_API_LCOPENSDK_EXPORT void LCOpenSdk_Utils_SetSaveStreamFlag(bool isOpen);

typedef void(*LCOpenSDK_onTalkResult)(const char* error, int type);
typedef void(*LCOpenSDK_onTalkProgressStatus)(const char* status);
typedef void(*LCOpenSDK_onTalkPlayReady)();
typedef void(*LCOpenSDK_onTalkAudioRecord)(unsigned char* pData, int dataLen, int audioFormat, int sampleRate, int sampleDepth);
typedef void(*LCOpenSDK_onTalkvoidAudioReceive)(unsigned char* pData, int dataLen, int audioFormat, int sampleRate, int sampleDepth);
typedef bool(*LCOpenSDK_onTalkRealAudioInfo)(int realSampleRate, int realSampleDepth);
typedef void(*LCOpenSDK_onTalkStreamLogInfo)(const char* message, unsigned int length);
typedef void(*LCOpenSDK_onTalkConnectInfoConfig)(const char* message, int msgLen, const char* ip, int ipLen, int localPort, int remotePort, const char* deviceSn, int snLen);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_AudioTalk_Set_onTalkResult_Callback(LCOpenSDK_onTalkResult cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_AudioTalk_Set_onTalkProgressStatus(LCOpenSDK_onTalkProgressStatus cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_AudioTalk_Set_onTalkPlayReady(LCOpenSDK_onTalkPlayReady cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_AudioTalk_Set_onTalkAudioRecord(LCOpenSDK_onTalkAudioRecord cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_AudioTalk_Set_onTalkAudioReceive(LCOpenSDK_onTalkvoidAudioReceive cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_AudioTalk_Set_onTalkRealAudioInfo(LCOpenSDK_onTalkRealAudioInfo cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_AudioTalk_Set_onTalkConnectInfoConfig(LCOpenSDK_onTalkConnectInfoConfig cb);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_AudioTalk_PlayTalk(const char* token, const char* deviceID, int channelID, const char* decryptKey, bool isOpt, const char* playInfo, bool isTryP2P);
C_API_LCOPENSDK_EXPORT int LCOpenSDK_AudioTalk_StopTalk();
C_API_LCOPENSDK_EXPORT int LCOpenSDK_AudioTalk_PlaySound();
C_API_LCOPENSDK_EXPORT int LCOpenSDK_AudioTalk_StopSound();
C_API_LCOPENSDK_EXPORT int LCOpenSDK_AudioTalk_StartSampleAudio();
C_API_LCOPENSDK_EXPORT int LCOpenSDK_AudioTalk_StopSampleAudio();

typedef void(*LCOpenSDK_convertOnConvertProgress)(int progress, int index);
typedef void(*LCOpenSDK_convertOnConvertFrame)(void* data, int len, int frameType, int index);
typedef void(*LCOpenSDK_convertOnConvertError)(int errorCode, int index);
C_API_LCOPENSDK_EXPORT void* LCOpenSDK_Convert_CreateHandle();
C_API_LCOPENSDK_EXPORT int LCOpenSDK_Convert_InitVideoPlay(void* handle, int index);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_Convert_DestoryHandle(void* handle);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_Convert_Set_onConvertProgress_Callback(LCOpenSDK_convertOnConvertProgress cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_Convert_Set_onConvertFrame_Callback(LCOpenSDK_convertOnConvertFrame cb);
C_API_LCOPENSDK_EXPORT void LCOpenSDK_Convert_Set_onConvertError_Callback(LCOpenSDK_convertOnConvertError cb);

C_API_LCOPENSDK_EXPORT bool LCOpenSDK_Login_ConfigureP2PServers(const char* p2pKey, const char* p2pInfo, int encryptMode);
C_API_LCOPENSDK_EXPORT bool LCOpenSDK_Login_AddDevices(const char* deviceIds[], const char* playInfos[], int count);
C_API_LCOPENSDK_EXPORT bool LCOpenSDK_Login_DelDevicesWithDeviceIds(const char* deviceIds[]);
C_API_LCOPENSDK_EXPORT bool LCOpenSDK_Login_DelAllDevices();
C_API_LCOPENSDK_EXPORT void LCOpenSDK_Login_UnInit();

C_API_LCOPENSDK_EXPORT void* LCOpenSDK_Crypter_CreateHandle();
C_API_LCOPENSDK_EXPORT bool LCOpenSDK_Crypter_InitWithRuleVersion(void* handle, int rule); 
C_API_LCOPENSDK_EXPORT int LCOpenSDK_Crypter_DecryptIOTPlayInfo(void* handle, const char *sBuf, int iLen, const char *sDevId, int sDevIdLen, const char *sSalt, int sSaltLen, char *sBufOut, int &iBufLenOut); 
C_API_LCOPENSDK_EXPORT int LCOpenSDK_Crypter_DecryptDataWithoutHead(void* handle, const char* pSrcBufIn, int srcBuflen, const char* key, const char *sDevId,const char *sDevPwd, char* dstBufOut, int &dstBufLenOut);
#endif /* _C_API_LCOPENSDK_H_ */
