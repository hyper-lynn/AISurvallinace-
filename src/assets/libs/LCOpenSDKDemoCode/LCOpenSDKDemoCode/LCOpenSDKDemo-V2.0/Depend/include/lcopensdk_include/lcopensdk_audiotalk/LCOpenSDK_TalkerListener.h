#ifndef _LCOPENSDK_TALKERLISTENER_H_
#define _LCOPENSDK_TALKERLISTENER_H_

class LCOpenSDK_TalkerListener
{
public:
    virtual ~LCOpenSDK_TalkerListener(){};
    virtual void onTalkResult(const char* error, int type) = 0;
};

#endif /* _LCOPENSDK_TALKERLISTENER_H_ */
