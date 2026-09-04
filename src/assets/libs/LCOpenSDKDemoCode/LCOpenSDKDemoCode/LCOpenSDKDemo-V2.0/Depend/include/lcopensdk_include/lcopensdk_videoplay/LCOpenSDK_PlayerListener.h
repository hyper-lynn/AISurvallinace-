#ifndef _LCOPENSDK_PLAYERLISTENER_H_
#define _LCOPENSDK_PLAYERLISTENER_H_

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
};

#endif /* _LCOPENSDK_PLAYERLISTENER_H_ */
