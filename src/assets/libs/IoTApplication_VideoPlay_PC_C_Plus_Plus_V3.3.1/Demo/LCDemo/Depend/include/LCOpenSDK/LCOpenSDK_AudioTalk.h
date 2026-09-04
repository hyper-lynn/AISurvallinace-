#ifndef _LCOPENSDK_AUDIOTALK_H_
#define _LCOPENSDK_AUDIOTALK_H_

#include "lcopensdk_global.h"
#include "LCOpenSDK_TalkerListener.h"

class LCOPENSDK_EXPORT LCOpenSDK_AudioTalk
{
private:
    LCOpenSDK_AudioTalk();
    ~LCOpenSDK_AudioTalk();

public:
    static LCOpenSDK_AudioTalk* GetInstance();
    void setTalkerListener(LCOpenSDK_TalkerListener* talkerListener);
    LCOpenSDK_TalkerListener* getTalkerListener();
    int playTalk(const char* token, const char* deviceID, int channelID, const char* decryptKey, bool isOpt, const char* playInfo, bool isTryP2P);
	int playTalkEX(const char* token, const char* deviceID, int channelID, const char* decryptKey, bool isOpt, const char* playInfo, bool isTryP2P);
    int stopTalk();

	int playTalkWithJsonString(const char* jsonString);
	int playSound();
	int stopSound();
	int startSampleAudio();
	int stopSampleAudio();
	bool isOptHandleOK(const char* handleKey);
	bool setSpeakerAutoEnable(bool bEnable);

private:
    void* m_hLCOpenSDK_AudioTalk_Inside;
    static LCOpenSDK_AudioTalk* sm_instance;
};

#endif /* _LCOPENSDK_AUDIOTALK_H_ */
