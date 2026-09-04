#ifndef _LCOPENSDK_LOGINLISTENER_H_
#define _LCOPENSDK_LOGINLISTENER_H_

class LCOpenSDK_LoginListener
{
public:
    virtual ~LCOpenSDK_LoginListener(){}

    virtual void onNetSDKDisconnect(const char* deviceId) = 0;
};

#endif /* _LCOPENSDK_LOGINLISTENER_H_ */
