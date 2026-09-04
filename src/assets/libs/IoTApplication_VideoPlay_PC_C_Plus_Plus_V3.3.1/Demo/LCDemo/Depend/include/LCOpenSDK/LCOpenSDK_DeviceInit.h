#ifndef _LCOPENSDK_DEVICEINIT_H_
#define _LCOPENSDK_DEVICEINIT_H_

#include "lcopensdk_global.h"

class LCOPENSDK_EXPORT LCOpenSDK_DeviceInit
{
public:
    typedef struct _DEVICE_INIT_INFO_
    {
        char szMac[64];
        char szIp[64];
        int  port;
        int  initStatus;
    }DEVICE_INIT_INFO;

public:
    static LCOpenSDK_DeviceInit* getInstance();
    int searchDeviceInitInfo(const char* deviceId, DEVICE_INIT_INFO& devInitInfo, int timeout);
    int initDevice(const char* szMac, const char* pwd);
    int initDevice(const char* szMac, const char* pwd, const char* szIp);
    int checkPwdValidity(const char* deviceId, const char* szIp, int port, const char* pwd);

private:
    LCOpenSDK_DeviceInit();
    ~LCOpenSDK_DeviceInit();

private:
    static LCOpenSDK_DeviceInit* sm_instance;

};

#endif /* _LCOPENSDK_DEVICEINIT_H_ */
