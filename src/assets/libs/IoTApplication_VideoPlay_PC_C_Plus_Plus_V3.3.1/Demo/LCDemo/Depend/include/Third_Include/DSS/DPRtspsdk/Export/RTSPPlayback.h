#ifdef DP_REST_PLATFORM_SDK

#ifndef __IRTSPSDK_RTSPPLAYBACK_H__
#define __IRTSPSDK_RTSPPLAYBACK_H__

#include "RTSPDefine.h"
#include "ClientPluginAPI/IObserver.h"
#include "Common/CommonGlobal.h"

BEGIN_NAMESPACE_RTSPSDK

class CRTSPPlaybackPrivate;

//开始回放
typedef struct tagStartPBParma
{
	std::string			strURL;				//视频URL,不支持多个URL
	std::string			strToken;			//视频token
	rtsp_transmode_e nTransMode;			//1 tcp,0 udp;
	rtsp_pb_type_e		ePBType;
	std::string			strCameraId;		// 摄像头ID
	time_t				beginTime;			//单位秒
	time_t				endTime;			//单位秒
	rtsp_pb_mode_e		mode;
	std::string			trackID;			//码流类型,'trackID=501'=PS, 'trackID=601'= 原始帧, 'trackID=701' = '大华帧', 
											//'trackID=801'=大华标准帧, 'trackID=901'=TS帧, 101(300以下)=rtp标准流(ONVIF协议标准)
	bool				bBack;				//是否倒放
	rtsp_speed_mode_e	eSpeedMode;

	bool				bUseRelativeTime;   //是否使用相对文件时间。false时，beginTime和endTime为时间戳，单位秒；
										    //true时，beginTime和endTime为时间戳与录像文件起始时间的差值，单位秒。
	std::string strLoginIP;					//登录IP,用于多个URL时对URL进行排序

    bool       isUseSsl;
    float 	   fSpeed;
	tagStartPBParma()
		: nTransMode(TransmodeStdTCP)
		, ePBType(PlaybackByFile)
		, beginTime(0)
		, endTime(0)
		, mode(PBModeNormal)
		, bBack(false)
		, eSpeedMode(SpeedModeSpeed)
		, bUseRelativeTime(false)
        , isUseSsl(false)
        , fSpeed(1.0)
	{
	}

}StartPBParma_t;

//暂停回放
typedef struct tagPausePBParma
{
	int nProvider;					//设备厂商类型
	tagPausePBParma()
		: nProvider(DevProviderUnknown)
	{
	}
}PausePBParma_t;

//继续回放
typedef struct tagResumePBParma
{
	float		fSpeed;					//播放速率 1/2等
	int			nProvider;				//设备厂商类型
	tagResumePBParma()
		: fSpeed(1)
		, nProvider(DevProviderUnknown)
	{
	}
}ResumePBParma_t;

//seek
typedef struct tagSeekPBParma
{
	time_t nSeekBegin;			//定位起始值.文件模式时,是定位处的文件大小值;时间模式时,是定位处的时间值;						
	time_t nSeekEnd;			//定位结束值.文件模式时,无意义;时间模式时,是期待的结束时间.

	bool   bUseRelativeTime;    //是否使用相对文件时间。false时，beginTime和endTime为时间戳，单位秒；
							    //true时，beginTime和endTime为时间戳与录像文件起始时间的差值，单位秒。
	tagSeekPBParma()
		: nSeekBegin(0)
		, nSeekEnd(0)
		, bUseRelativeTime(false)
	{
	}
}SeekPBParma_t;

//set speed
typedef struct tagSetSpeedPBParma
{
	float		fSpeed;					//播放速率 1/2等
	int			nProvider;				//设备厂商类型
	tagSetSpeedPBParma()
		: fSpeed(1)
		, nProvider(DevProviderUnknown)
	{
	}
}SetSpeedPBParma_t;

class IRTSPPlaybackObserver : public DSPluginAPI::IObserver
{
public:
	typedef enum
	{
		StartPlayBack				= 0,		//开始回放结果 enumState nResult（0：打开成功；非0：打开失败）
		StopPlayBack				= 1,		//关闭回放
		PausePlayBack				= 2,		//暂停
		ResumePlayBack				= 3,		//恢复
		SeekPlayBack				= 4,		//定位
		SetSpeedPlayBack			= 5,		//设置速度
		MediaFirstReceive			= 6,        //收到第一帧数据
		ReceiveDataOver				= 7,		//收到0包后的通知
		MTSOffline					= 8,		//mts离线
	}Notify_State_e;

	struct Param
	{
		Notify_State_e		enumState;				//参考Notify_State_e
		int					nResult;				//结果

		Param() 
			: nResult(0)
		{
		}
	};
public:
	virtual void NotifyRTSPPlaybackState(const IRTSPPlaybackObserver::Param& struParam) = 0;
};


END_NAMESPACE_RTSPSDK

#endif  //__IRTSPSDK_RTSPPLAYBACK_H__

#endif
