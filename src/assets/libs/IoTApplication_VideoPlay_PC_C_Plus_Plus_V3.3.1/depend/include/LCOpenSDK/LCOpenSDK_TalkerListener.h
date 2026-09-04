#ifndef _LCOPENSDK_TALKERLISTENER_H_
#define _LCOPENSDK_TALKERLISTENER_H_

#include "lcopensdk_global.h"

class LCOPENSDK_EXPORT LCOpenSDK_TalkerListener
{
public:
    virtual ~LCOpenSDK_TalkerListener(){};
	virtual void onTalkPlayReady() = 0;
    virtual void onTalkResult(const char* error, int type) = 0;
	virtual void onProgressStatus(const char* status) = 0;
	virtual void onAudioRecord(unsigned char* pData, int dataLen, int audioFormat, int sampleRate, int sampleDepth) = 0;
	virtual void onAudioReceive(unsigned char* pData, int dataLen, int audioFormat, int sampleRate, int sampleDepth) = 0;
	virtual bool onRealAudioInfo(int realSampleRate, int realSampleDepth) = 0;
	virtual void onStreamLogInfo(const char* message, unsigned int length) = 0;
	virtual void onConnectInfoConfig(const char* message, int msgLen, const char* ip, int ipLen, int localPort, int remotePort, const char* deviceSn, int snLen) = 0;

};

#endif /* _LCOPENSDK_TALKERLISTENER_H_ */
