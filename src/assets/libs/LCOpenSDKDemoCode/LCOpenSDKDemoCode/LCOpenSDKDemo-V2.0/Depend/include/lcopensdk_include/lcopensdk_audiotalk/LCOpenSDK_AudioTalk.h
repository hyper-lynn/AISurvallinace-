#ifndef _LCOPENSDK_AUDIOTALK_H_
#define _LCOPENSDK_AUDIOTALK_H_

#include "lcopensdk_global.h"
#include "lcopensdk_videoplay/LCOpenSDK_Param.h"
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

	/*****************************************************************************
	* @函数功能： playTalk 支持设备级对讲
	* @返 回 值:  成功：0，失败：-1
	*****************************************************************************/
    int playTalk(const char* token, const char* deviceID, const char* decryptKey, bool isTls);

	/*****************************************************************************
	* @函数功能： playTalkEx 通道级对讲，也支持设备级对讲，设备级对讲需要将通道设置为-1
	* @返 回 值: 成功：0，失败：-1
	*****************************************************************************/
	int playTalkEx(LCOpenSDK_ParamTalk *paramTalk);

    int stopTalk();

	 /**
    * 设置播放（对讲）码流保存路径
    * @param   [in] const char * saveStreamPath     默认为空
     * @return  int                                  0/非0 成功/失败
    */
    int setSaveStreamPath(const char* saveStreamPath=NULL);

private:
    void* m_hLCOpenSDK_AudioTalk_Inside;
    static LCOpenSDK_AudioTalk* sm_instance;
};

#endif /* _LCOPENSDK_AUDIOTALK_H_ */
