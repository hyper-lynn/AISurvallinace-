#ifndef _LCOPENSDK_NETSDKLOGIN_H_
#define _LCOPENSDK_NETSDKLOGIN_H_

#include "lcopensdk_global.h"
#include "dhnetsdk.h"

class LCOPENSDK_EXPORT LCOpenSDK_NetSDKLogin
{
private:
    LCOpenSDK_NetSDKLogin();
    ~LCOpenSDK_NetSDKLogin();

public:
    static LCOpenSDK_NetSDKLogin* GetInstance();
    LLONG getNetSDKHandle(const char* token, const char* deviceId);

private:
    static LCOpenSDK_NetSDKLogin* sm_instance;

};

#endif /* _LCOPENSDK_NETSDKLOGIN_H_ */
