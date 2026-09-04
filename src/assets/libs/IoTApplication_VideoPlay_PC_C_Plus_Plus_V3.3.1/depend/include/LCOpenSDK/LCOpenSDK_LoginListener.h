#ifndef _LCOPENSDK_LOGINLISTENER_H_
#define _LCOPENSDK_LOGINLISTENER_H_

#include "lcopensdk_global.h"

class LCOPENSDK_EXPORT LCOpenSDK_LoginListener
{
public:
    virtual ~LCOpenSDK_LoginListener(){}

	virtual void onNetSDKDisconnect(const char* deviceSn, const int devType) = 0;

	virtual int onLoginResult(const int type, const char* deviceSn, const int code, const int devType, const bool isDetach, const char* netDeviceInfoEx) = 0;

	virtual void onP2PLogInfo(const char* logMessage, const int length) = 0;

	virtual void onDeviceState(const char* deviceSn, int deviceState, const char* ip, const bool isDetach) = 0;
};

#endif /* _LCOPENSDK_LOGINLISTENER_H_ */
