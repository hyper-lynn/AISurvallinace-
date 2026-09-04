#ifdef DP_REST_PLATFORM_SDK

/**
* Copyright (c) 2015.浙江大华
* All rights reserved.
*
* 文件名称：RTSPReal.h
* 文件标识：
* 摘　　要：视频播放类
*
* 当前版本：1.0
* 原作者　：27401
* 完成日期：
* 修订记录：
*/

#ifndef __RTSPSDK_RTSPREAL_H__
#define __RTSPSDK_RTSPREAL_H__

#include "RTSPDefine.h"
#include "ClientPluginAPI/IObserver.h"
#include "Common/CommonGlobal.h"
#include "Common/ErrorCode.h"

BEGIN_NAMESPACE_RTSPSDK

class CRTSPRealPrivate;

//打开视频参数
typedef struct tagVideoParam
{
	std::string strURL;				//视频URL,支持多个URL
	std::string strToken;			//视频token
	std::string strCameraId;
	rtsp_streamtype_e streamType;	//码流类型
	rtsp_media_data_e mediaType;	//1视频，2音频，3音频＋视频	
	rtsp_transmode_e transMode;		//一般用TransmodeStdTCP
	std::string strTrackID;
	bool bMulticastToUnicast;
	VCSParam_t stuVCSParma;			//转码相关参数
	std::string strLoginIP;         //登录IP,用于多个URL时对URL进行排序

    bool       isUseSsl;
	tagVideoParam()
		: streamType(StreamMain)
		, mediaType(MediaDataAll)
		, transMode(TransmodeStdTCP)
		, bMulticastToUnicast(false)
        , isUseSsl(false)
	{
	}

}VideoParam_t;

//实时视频相关回调
class IRTSPRealObserver : public DSPluginAPI::IObserver
{
public:
	typedef enum
	{
		StartVideo				= 0,		//打开视频 enumState nResult（0：打开成功；非0：打开失败）
		StopVideo				= 1,		//关闭视频
		MediaFirstReceive		= 2,        //收到第一帧数据
		MTSOffline				= 3,		//mts离线
	}Notify_State_e;

	struct Param
	{
		Notify_State_e		enumState;				// 参考Notify_State_e
		int					iErrorCode;				// 错误码

		Param(Notify_State_e enumStateIn, int iErrorCodeIn = DCM_RET_SUCCESS)
			: enumState(enumStateIn), 
            iErrorCode(iErrorCodeIn)
		{
		}
	};

public:
	virtual void NotifyRTSPRealState(const IRTSPRealObserver::Param& struParam) = 0;
};


END_NAMESPACE_RTSPSDK

#endif  //__RTSPSDK_RTSPREAL_H__

#endif
