#ifdef DP_REST_PLATFORM_SDK

#ifndef INCLUDED_DEFINE_H
#define INCLUDED_DEFINE_H

#include "Export/RTSPDefine.h"

#ifdef WIN32
	#ifndef __int8_t_defined
		#define __int8_t_defined
		typedef signed char			int8_t;
		typedef unsigned char		uint8_t;
		typedef short int			int16_t;
		typedef unsigned short int	uint16_t;
		typedef int					int32_t;
		typedef unsigned int		uint32_t;
		typedef __int64				int64_t;
		typedef unsigned __int64	uint64_t;
	#endif
#endif

const int RTSP_IP_LEN = 46;
#define CFL_URL_LEN				1024         //客户端RTSP请求的URL 的长度
#define CFL_IP_LEN				64	        //存储介质访问地址的长度  0515 改 原来是IP长度
#define CHAR_LEN_64				64

BEGIN_NAMESPACE_RTSPSDK

//媒体会话状态
typedef enum
{
	MEDIA_STATUS_NORMAL,		//正常状态，也许还在请求过程/也许已经收取数据
	//fixme:要考虑命令连续追加的情形，如打开过程中，进行暂停或关闭
	MEDIA_STATUS_PAUSE,			//暂停状态
	MEDIA_STATUS_DYING,			//濒死状态，可能上层已经废弃了会话

}rtsp_media_status_e;

//媒体流请求状态机
typedef enum
{
	MEDIA_STEP_PREPARED,		//准备
//	MEDIA_STEP_REQTOCMS,		//向CMS请求
	MEDIA_STEP_SETUP,			//向MTS/SS发送Setup
	MEDIA_STEP_PLAY,			//Setup应答之后，发送Play
	MEDIA_STEP_OK,				//Play应答成功，整体流程认为成功
	MEDIA_STEP_BROADCAST_OK,

}rtsp_media_step_e;

// fixme::后续的audioType 可采用该枚举
// 语音编码类型---DH_TALK_CODING_TYPE
typedef enum
{
	TALK_DEFAULT	= 0,									// 无头PCM
	TALK_PCM		= 1,									// 带头PCM
	TALK_G711a,												// G711a
	TALK_AMR,												// AMR
	TALK_G711u,												// G711u
	TALK_G726,												// G726
	TALK_G723_53,											// G723_53
	TALK_G723_63,											// G723_63
	TALK_AAC,												// AAC
}rtsp_talk_coding_type_e;

//广播对讲设备信息
class BroadcastDev
{
public:
	BroadcastDev(): m_strDevId(""),
		m_nChannelId(0), 
		m_strRtspUrl(""),
		m_nSessionId(0),
		m_nToken(0),
		m_nAudioType(TALK_DEFAULT),
		m_nAudioBit(0),
		m_nSampleRate(0),
		m_nResult(0),
		m_strDesc(""){}
	std::string				m_strDevId;						// 设备id
	uint32_t				m_nChannelId;					// 设备通道
	std::string				m_strRtspUrl;
	uint32_t				m_nSessionId;
	uint32_t				m_nToken;
	rtsp_talk_coding_type_e	m_nAudioType;				// 设备返回的音频编码类型
	uint32_t				m_nAudioBit;					// 音频码率
	uint32_t				m_nSampleRate;					// 音频采样率
	int32_t					m_nResult;						// 单个设备操作的返回值
	std::string				m_strDesc;						// 操作返回描述
};

typedef enum
{
	BAY_PICINFO_RECIVE,										// 收到图片信息
	BAY_PICDATA_RECIVE,										// 图片数据接收
	BAY_PICDATA_OVER,										// 一组图片数据结束
}rtsp_picdata_notify_e;

/** 图片数据回调函数定义
    @param int session												对应请求时返回的session
    @param const char* nodeId										数据对应的通道/设备ID
    @param char* pData												图片流数据
    @param int dataLen												数据长度 
	@param void* pUserParam											用户参数,见AddCallbackInfo
	@param dpsdk_picdata_notify_e notify_e							图片数据类型
*/
typedef int (RTSP_CALLTYPE *fPicDataCallback)(int session, const char* nodeId, char* pData, int dataLen, void* pUserParam, rtsp_picdata_notify_e notify_e);


//数据传输通知
typedef enum
{
	MEDIA_FIRST_RECEIVE,				// 打开视频首次收到码流
	DATA_RECIVE_OVER,                   // 收到0包后的通知
	BAY_RTP_CLOSE,						// rtp连接断开
}rtsp_media_notify_e;

// 呼叫业务状态
typedef enum
{
	CALL_STATUS_PREPARED,			//准备
	CALL_STATUS_REQTOSCS,			//向SCS请求
	CALL_STATUS_CALLING,			//呼叫中
	CALL_STATUS_RECVING,			//接收中
	CALL_STATUS_CEASED,				//呼叫释放
}rtsp_call_status_e;

typedef enum
{
	CALL_TYPE_SINGLE_CALL,			// 单呼
	CALL_TYPE_GROUP_CALL,			// 组呼
	CALL_TYPE_VT_CALL,				// 可视对讲
}dpsdk_call_type_e;

//载荷类型，俗称trackid
typedef enum
{
	DPSDK_TRACKID_ES = 101,		// ES包
	DPSDK_TRACKID_PS = 501,		// PS包
	DPSDK_TRACKID_DHAV = 701,	// 大华帧
	DPSDK_TRACKID_TS = 901,		// TS包
}rtsp_trackid_type_e;

//tcp 连接方式
typedef enum
{
	DPSDK_TCPMODE_DEFAULT = 0,	//默认连接方式
	DPSDK_TCPMODE_ACTIVE = 1,	//tcp 主动连接方式
	DPSDK_TCPMODE_PASSIVE = 2	//tcp 被动连接方式
}rtsp_tcp_mode_e;

END_NAMESPACE_RTSPSDK

#endif
#endif