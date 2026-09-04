#ifndef _LCOPENSDK_PLAYERLISTENER_H_
#define _LCOPENSDK_PLAYERLISTENER_H_

#include "lcopensdk_global.h"

class LCOpenSDK_PlayerListener
{
public:
    virtual ~LCOpenSDK_PlayerListener(){};
    virtual void onPlayerResult(int index, const char* code, int resultSource) = 0;
    virtual void onResolutionChanged(int index, int width, int height) = 0;
    virtual void onPlayBegan(int index) = 0;
    virtual void onReceiveData(int index, int len) = 0;
    virtual void onStreamCallback(int index, const unsigned char* data, unsigned int dataLen) = 0;
    virtual void onPlayFinished(int index) = 0;
    virtual void onPlayerTime(int index, long time) = 0;
	virtual void onIVSInfo(int index, char* pBuf, long lType, long lLen, long lReallen) = 0;
	virtual void onProgressStatus(int index, const char* status) = 0;
	virtual void onFrameLost(const char* context) = 0;
	virtual void onRecordStop(const char* context, int error) = 0;
	virtual void onFileTime(const char* context, long beginTime, long endTime) = 0;
	virtual void onNetworkDisconnected(const char* context) = 0;
	virtual void onBadFile(const char* context) = 0;
	virtual void onDraw(const char* context, void *hdc) = 0;
	virtual void onPlayerTimeAndStamp(const char* context, long time, long stampTime) = 0;
	virtual void onAudioTimeAndStamp(const char* context, long time, long stampTime, bool isDetach) = 0;
	virtual void onStreamLogInfo(const char* context, const char* message, unsigned int length) = 0;
	virtual void onIPFrameTimeOver(const char* context, long timeInterval) = 0;
	virtual void onConnectInfoConfig(const char* context, const char* message, int msgLen, const char* ip, int ipLen, int localPort, int remotePort, const char* deviceSn, int snLen) = 0;
};

#endif /* _LCOPENSDK_PLAYERLISTENER_H_ */
