#ifdef DP_REST_PLATFORM_SDK
/**
* Copyright (c) 2015.浙江大华
* All rights reserved.
*
* 文件名称：RTSPDefine.h
* 文件标识：
* 摘　　要：RTSP对外的结构体与枚举值定义
*
* 当前版本：1.0
* 原作者　：27401
* 完成日期：
* 修订记录：
*/

#ifndef RTSPSDK_RTSPDEFINE_H
#define RTSPSDK_RTSPDEFINE_H

#include "RTSPGlobal.h"
#include <string>


BEGIN_NAMESPACE_RTSPSDK

#define RTSP_CONNECT_TIME_OUT		10			//RTSP超期等待时间
#define RTSP_TALK_AUDIO_BIT			8			//对讲bit
#define RTSP_TALK_SAMPLE_RATE		16000		//对讲音频采样率

// 媒体流按业务分类 
typedef enum
{
	RTSP_MEDIA_INVALID,
	RTSP_MEDIA_REAL,		//实时
	RTSP_MEDIA_PLAYBACK,	//回放
	RTSP_MEDIA_TALK,		//对讲
	RTSP_MEDIA_BAY,			//卡口
	RTSP_MEDIA_CALL,		//呼叫
	RTSP_MEDIA_BROADCAST,	//广播
	RTSP_MEDIA_VTCALL,		//可视对讲
}rtsp_media_func_e;

//转码参数
typedef struct tagVCSParma
{
	std::string	 strVideoCodec;		//视频编码格式
	std::string	 strResolution;		//视频分辨率
	int			 nFPS;				//帧率
	int			 nBPS;				//码率
	int          bUsedVCS;			//是否使用转码 1使用，0不使用，默认为0

	tagVCSParma()
		: strVideoCodec("h264")
		, strResolution("CIF")
		, nFPS(12)
		, nBPS(512)
		, bUsedVCS(0)
	{
	}
    tagVCSParma(const tagVCSParma& vcsParam)
    {
        this->strVideoCodec = vcsParam.strVideoCodec;
        this->strResolution = vcsParam.strResolution;
        this->nFPS = vcsParam.nFPS;
        this->nBPS = vcsParam.nBPS;
        this->bUsedVCS = vcsParam.bUsedVCS;
    }
    tagVCSParma operator =(const tagVCSParma& vcsParam)
    {
        this->strVideoCodec = vcsParam.strVideoCodec;
        this->strResolution = vcsParam.strResolution;
        this->nFPS = vcsParam.nFPS;
        this->nBPS = vcsParam.nBPS;
        this->bUsedVCS = vcsParam.bUsedVCS;
        return (*this);
    }
}VCSParam_t;

/** 视频回调函数定义. 
	@param rtsp_media_func_e mediaType		媒体流对应的业务
	@param const char * nodeId				数据对应的通道/设备ID
	@param int paramVal						扩展值;mediaType为real时，为streamType;
	@param char * pData						媒体流数据
	@param int dataLen						数据长度 
	@param void * pUserParam				用户参数,见addCallbackInfo
*/
typedef int ( RTSP_CALLTYPE *fMediaDataCallback )(rtsp_media_func_e mediaType, const char* nodeId, int paramVal, char* pData, int dataLen, void* pUserParam);

//视频传输方式
typedef enum 
{
	TransmodeUDP = 0,	//UDP连接方式,创建两条链路
	TransmodeTCP,		//TCP连接方式,创建两条链路
	TransmodeStdTCP,	//标准TCP连接方式,创建一条链路
}rtsp_transmode_e;

//码流类型
typedef enum 
{
	StreamMain = 1,		//主码流
	StreamAssist,		//辅码流
}rtsp_streamtype_e;

// 视频流数据内容
typedef enum{
	MediaDataVideo		= 1,	// 视频
	MediaDataAudio,				// 音频
	MediaDataAll,				// 视频+音频
}rtsp_media_data_e;

//对讲类型
typedef enum{
	DeviceTalk		= 1,	// 设备对讲
	ChannelTalk,			// 通道对讲
}rtsp_talk_type_e;

// 语音编码类型---DH_TALK_CODING_TYPE
typedef enum
{
	AudioDefault	= 0,									// 无头PCM
	AudioPCM		= 1,									// 带头PCM
	AudioG711a		= 2,									// G711a
	AudioAMR		= 3,									// AMR
	AudioG711u      = 4,									// G711u
	AudioG726		= 5,									// G726
	AudioG723_53	= 6,									// G723_53
	AudioG723_63	= 7,									// G723_63
	AudioAAC		= 8,									// AAC
	TAudioG722		= 101,									// G722
	AudioG711_MU	= 102,									// G711_MU
}rtsp_audio_type_e;

//回放定义
typedef enum 
{
	PlaybackByFile,										   //按文件回放
	PlaybackByTime,										   //按时间回放
}rtsp_pb_type_e;

typedef enum
{
	PBModeNormal				= 1,						// 普通录像
	PBModeDownload,											// 下载
}rtsp_pb_mode_e;

typedef enum
{
	SpeedModeDefault				= 0,					// 默认方式
	SpeedModeSpeed,											// 全帧
	SpeedModeScale                                          // 抽帧
}rtsp_speed_mode_e;

//设备厂家类型
typedef enum
{
	DevProviderUnknown		= 0,
	DevProviderDAHUA,										// 大华
	DevProviderHIK,											// 海康：回放设置码流速度时，海康设备要传full
}dev_provider_e;



class ISendAudioAble
{
public:

	/** 
	* @brief	发送频数据
	@param   pData						媒体流数据
	@param   dataLen					数据长度
	@return								是否成功
	*/
	virtual int SendAudioData(char* pData, int dataLen) = 0;
};

END_NAMESPACE_RTSPSDK

#endif  //RTSPSDK_RTSPDEFINE_H

#endif
