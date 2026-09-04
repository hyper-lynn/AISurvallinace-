#ifdef DP_REST_PLATFORM_SDK

#ifndef __IRTSPSDK_RTSPVTCALL_H__
#define __IRTSPSDK_RTSPVTCALL_H__

#include "RTSPDefine.h"
#include "ClientPluginAPI/IObserver.h"
#include "Common/CommonGlobal.h"
#include "Common/ErrorCode.h"
#include "RTSPReal.h"

BEGIN_NAMESPACE_RTSPSDK
	
class CRTSPVtCallPrivate;

//开始可视对讲参数
typedef struct tagPreStartVtCallParam
{
	std::string		strUserId;							// 用户ID
	std::string		localIp;

	tagPreStartVtCallParam()
		: strUserId("")
		, localIp("0.0.0.0")
	{
	}

}PreStartVtCallParam_t;

typedef struct tagPreStartVtCallResp
{
	int				iAudioSessionID;					// 音频sessionId
	int				iVideoSessionID;					// 视频sessionId
	int				iAudioPort;							// 音频端口
	int				iVideoPort;							// 视频端口

	tagPreStartVtCallResp()
		: iAudioSessionID(0)
		, iVideoSessionID(0)
		, iAudioPort(0)
		, iVideoPort(0)
	{
	}

}PreStartVtCallResp_t;

// Digits
typedef enum
{
	TALK_AUDIO_BIT_8 = 8,
	TALK_AUDIO_BIT_16 = 16,
}DPSDK_TALK_BIT;

// Precision
typedef enum
{
	TALK_AUDIO_SAM_8K = 8000,
	TALK_AUDIO_SAM_16K = 16000,
	TALK_AUDIO_SAM_32K = 32000,
	TALK_AUDIO_SAM_48K = 48000,
	TALK_AUDIO_SAM_8192 = 8192,
}DPSDK_TALK_SAMPLE_RATE;

//开始可视对讲参数
typedef struct tagStartVtCallParam
{
	int				iCallType;							// 呼叫类型 详见DPSDK_CALL_TYPE定义
	int				audioType;							// 1 PCM，2 G.711，3 G.723，4 G.726，5 G.729
	int				audioBit;							// 用实际的值表示，如8位 则填值为8
	int				sampleRate;							// 采样率，如16k 则填值为16000
	std::string		rtpServIP;							// 远端RTP IP
	int				rtpAPort;							// 远端RTP音频端口
	int				rtpVPort;							// 远端RTP视频端口
	int				callId;
	int				dlgId;

	tagStartVtCallParam()
		: iCallType(2)
		, audioType(AudioPCM)
		, audioBit(TALK_AUDIO_BIT_8)
		, sampleRate(TALK_AUDIO_SAM_8K)
		, rtpServIP("")
		, rtpAPort(0)
		, rtpVPort(0)
		, callId(0)
		, dlgId(0)
	{
	}

}StartVtCallParam_t;

//开始可视对讲参数
typedef struct tagInviteVtCallParam
{
	int				iCallType;							// 呼叫类型 详见DPSDK_CALL_TYPE定义
	int				audioType;							// 1 PCM，2 G.711，3 G.723，4 G.726，5 G.729
	int				audioBit;							// 用实际的值表示，如8位 则填值为8
	int				sampleRate;							// 采样率，如16k 则填值为16000
	std::string		rtpServIP;							// 远端RTP IP
	int				rtpAPort;							// 远端RTP音频端口
	int				rtpVPort;							// 远端RTP视频端口
	int				callId;
	int				dlgId;
	int				tId;
	
	std::string		localIp;

	tagInviteVtCallParam()
		: iCallType(2)
		, audioType(AudioPCM)
		, audioBit(TALK_AUDIO_BIT_8)
		, sampleRate(TALK_AUDIO_SAM_8K)
		, rtpServIP("")
		, rtpAPort(0)
		, rtpVPort(0)
		, callId(0)
		, dlgId(0)
		, tId(0)
		, localIp("")
	{
	}

}InviteVtCallParam_t;

typedef struct tagInviteVtCallResp
{
	int				iAudioSessionID;					// 音频sessionId
	int				iVideoSessionID;					// 视频sessionId
	int				iAudioPort;							// 音频端口
	int				iVideoPort;							// 视频端口

	tagInviteVtCallResp()
		: iAudioSessionID(0)
		, iVideoSessionID(0)
		, iAudioPort(0)
		, iVideoPort(0)
	{
	}

}InviteVtCallResp_t;


END_NAMESPACE_RTSPSDK

#endif

#endif