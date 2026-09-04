#ifdef DP_REST_PLATFORM_SDK

#ifndef __IRTSPSDK_RTSPTALK_H__
#define __IRTSPSDK_RTSPTALK_H__

#include "RTSPDefine.h"
#include "ClientPluginAPI/IObserver.h"
#include "Common/CommonGlobal.h"

BEGIN_NAMESPACE_RTSPSDK
	
class CRTSPTalkPrivate;

//打开对讲参数
typedef struct tagTalkParam
{
	std::string strURL;				//视频URL,支持多个URL
	std::string strToken;			//视频token
	std::string strId;				//设备ID或通道ID
	rtsp_talk_type_e nTalkType;		//对讲类型
	rtsp_audio_type_e nAudioType;	//语音编码类型
	int nAudioBit;					//用实际的值表示，如8位 则填值为8
	int nSampleRate;				//采样率，如16k 则填值为16000	
	rtsp_transmode_e nTransMode;	//传输方式
	bool bLocalDev;					//设备与设备对讲 标志是本地设备
	bool bBroadCast;				//表示当前要开启的是对讲 还是广播
	std::string strLoginIP;         //登录IP,用于多个URL时对URL进行排序

    bool isUseSsl;
	tagTalkParam()
		: nTalkType(DeviceTalk)
		, nAudioType(AudioPCM)
		, nAudioBit(8)
		, nSampleRate(16000)
		, nTransMode(TransmodeStdTCP)
		, bLocalDev(false)
		, bBroadCast(false)
        , isUseSsl(false)
	{
	}

}TalkParam_t;

class IRTSPTalkObserver : public DSPluginAPI::IObserver
{
public:
	typedef enum
	{
		StartTalk				= 0,		//打开对讲结果 enumState nResult（0：打开成功；非0：打开失败）
		StopTalk				= 1,		//关闭对讲
		MediaFirstReceive		= 2,        //收到第一帧数据
		MTSOffline				= 3,		//mts离线
	}Notify_State_e;

	struct Param
	{
		Notify_State_e		enumState;				//参考Notify_State_e
		int					nResult;				//结果
		int					nId;					//唯一标识

		Param()
			: nResult(0)
		{
		}
	};
public:
	virtual void NotifyRTSPTalkState(const IRTSPTalkObserver::Param& struParam) = 0;
};

END_NAMESPACE_RTSPSDK

#endif

#endif
