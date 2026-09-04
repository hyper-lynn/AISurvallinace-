/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,实时监视子模块
 *
 * 当前版本：1.0
 * 原作者　：俞露
 * 完成日期：2012年4月20日
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKREAL_H
#define INCLUDED_DPSDK_DPSDKREAL_H

#include "DPSDK.h"
#include <string>

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

// 码流类型
typedef enum{
	REAL_MAIN_TYPE			= 1,							// 主码流
	REAL_ASSIST_TYPE,										// 辅码流
	REAL_THIRD_TYPE,										// 三码流
}real_streamtype_e;

// 视频流数据内容
typedef enum{
	MEDIA_DATA_VIDEO		= 1,							// 视频
	MEDIA_DATA_AUDIO,										// 音频
	MEDIA_DATA_ALL,											// 视频+音频
}media_data_type_e;

// 视频流请求协议
typedef enum{
	MEDIA_PROTOCOL_UDP		= 0,							// UDP协议
	MEDIA_PROTOCOL_TCP,										// TCP协议
}media_protocol_type_e;

// 锁定/解锁类型
typedef enum
{
	VIDEO_CMD_LOCK			= 1,							// 锁定当前摄像头
	VIDEO_CMD_UNLOCK_ONE,									// 解锁当前摄像头
}dpsdk_video_locktype_e;

typedef enum
{
	VIDEO_RECORD_START		= 1,							// 开启视频录像
	VIDE0_RECORD_STOP		= 2,							// 停止视频录像

}dpsdk_video_record_e;

// 流输出荷载类型
typedef enum
{
	TRACKIDTYPE_PS			= 501,							// PS包
	TRACKIDTYPE_ORIG	    = 601,							// 第三方原始帧
	TRACKIDTYPE_DH			= 701,							// 大华帧
	TRACKIDTYPE_DHSTD		= 801,							// 大华标准帧
	TRACKIDTYPE_TS			= 901,							// TS包
	TRACKIDTYPE_RTP			= 101,							// RTP标准流
}trackid_type_e;

// 码流的视频分辨率类型
typedef enum
{
	RESOLUTION_1080P		= 1,							// 1080P
	RESOLUTION_130M	        = 2,							// 130M
	RESOLUTION_720P			= 3,							// 720P
	RESOLUTION_D1		    = 4,							// D1
	RESOLUTION_CIF			= 5,							// CIF
	RESOLUTION_QCIF			= 6,							// QCIF
	RESOLUTION_VGA			= 7,							// VGA
	RESOLUTION_QVGA			= 8,							// QVGA
}resolution_type_e;

typedef enum
{
	VIDEOCODEC_H264			= 1,							// h264
	VIDEOCODEC_MPEG4	    = 2,							// mpeg4
	VIDEOCODEC_JPEG			= 3,							// jpeg
}videocodec_type_e;

// 获取对外媒体流URL信息
typedef struct DPSDK_API tagGetExternalRealStreamUrlInfo
{
	char					szCameraId[DPSDK_CHL_ID_LEN];	// 通道ID
	real_streamtype_e		nStreamType;					// 码流类型
	media_data_type_e		nMediaType;						// 媒体类型
	media_protocol_type_e	nTransType;						// 传输类型
	trackid_type_e			nTrackId;						// 轨道ID
	bool					bUsedVCS;						// 需要VCS转码
	videocodec_type_e		nVcsVideocodec;					// 码流转码后的视频编码格式, bUsedVCS为1有效
	resolution_type_e		nVcsResolution;					// 码流的视频分辨率，bUsedVCS为1有效
	uint32_t				nVcsfps;						// 码流的帧率，bUsedVCS为1有效
	uint32_t				nVcsbps;						// 码流的码率，bUsedVCS为1有效

	tagGetExternalRealStreamUrlInfo()
	{
		memset(szCameraId,0x00,sizeof(szCameraId));
		nStreamType = REAL_MAIN_TYPE;
		nMediaType = MEDIA_DATA_VIDEO;
		nTransType = MEDIA_PROTOCOL_TCP;
		nTrackId = TRACKIDTYPE_DHSTD;
		bUsedVCS = false;
		nVcsVideocodec = VIDEOCODEC_H264;
		nVcsResolution = RESOLUTION_D1;
		nVcsfps = 0;
		nVcsbps = 0;
	}
}GetExternalRealStreamUrlInfo_t;

typedef struct DPSDK_API tagVCSParma
{
	std::string	_vcsvideocodec;		//视频编码格式
	std::string	_vcsresolution;		//视频分辨率
	int					_vcsfps;	//帧率
	int					_vcsbps;	//码率
	int                 _usedvcs;   //是否使用转码 1使用，0不使用，默认为0

	tagVCSParma()
	{
		_vcsvideocodec = "h264";
		_vcsresolution = "CIF";
		_vcsfps = 12;
		_vcsbps = 512;
		_usedvcs = 0;
	}
}VCSParma_t;

// 打开视频回调消息
class DPSDK_API OpenVideoMsg : public DPSDKCBMessage
{
public:
	OpenVideoMsg(void);
	virtual ~OpenVideoMsg(void){}

public:
	uint32_t			sessionId;							// 
	char				cameraId[DPSDK_CHL_ID_LEN];			// 
	dpsdk_check_right_e right;
	int					streamType;							// 
	int					mediaType;							// 
	int					transMode;							// 1 tcp,0 udp;
	dpsdk_tcpmode       tcpmode;                            // 0,默认,1 TCP主动模式,2 TCP被动模式,

	fMediaDataCallback	cbFun;								// 
	void*				pCbParam;							// 
	//dpsdk_trackid_type_e trackId;							// 载荷类型，用于setup组装url时trackid赋值，默认为DPSDK_TRACKID_DHAV

	// for DVR零通道多画面预览
	bool				bPreview;							// 是否多画面预览，如果为true，则streamType为预览分割数
	int					nStartChannelIndex;					// 起始通道号 bPreview为true有效
	
	// for new Protocol:28181
	char				rtpSsrc[DPSDK_RTPCODE_LEN];
	char				srcIp[DPSDK_IP_LEN];
	uint32_t			srcPort;

	bool				bMultiCast;							// 组播标志 true组播，false单播	
	bool				bMulticastToUnicast;				// 组播转单播 true组播转单播，false单播	

	VCSParma_t			stuVCSParma;            //转码相关参数

	std::string			strMulticastIp;						// 组播IP地址
	uint32_t			nMulticastRtpPort;					// 组播RTP端口
	uint32_t			nMulticastRtcpPort;					// 组播RTCP端口
	int			    	IsNewMedia;							//0:不是；1:是； (业务：社会面视频接入需求添加）
};

// 
class DPSDK_API CloseVideoMsg : public DPSDKCBMessage
{
public:
	CloseVideoMsg(void);
	virtual ~CloseVideoMsg(void){}

public:
	uint32_t	sessionId;									// 	
};

// 
class DPSDK_API PauseVideoMsg : public DPSDKCBMessage
{
public:
	PauseVideoMsg(void);
	virtual ~PauseVideoMsg(void){}

public:
	uint32_t	sessionId;									// 
};

// 
class DPSDK_API ResumeVideoMsg : public DPSDKCBMessage
{
public:
	ResumeVideoMsg(void);
	virtual ~ResumeVideoMsg(void){}

public:
	uint32_t	sessionId;									// 
};

// 
class DPSDK_API VideoExpctionMsg : public DPSDKCBMessage
{
public:
	VideoExpctionMsg(void);
	virtual ~VideoExpctionMsg(void){};

	int			nExceptionType;								// 异常类型 参见EnumRealException区分子类型
	char		cameraId[DPSDK_CHL_ID_LEN];					// 摄像头ID
	int			nSessionId;									// 实时视频会话ID
	char		szUrl[1024];								// 
};

// 
class DPSDK_API SessionNotfiyMsg : public DPSDKCBMessage
{
public:
	SessionNotfiyMsg(void);
	virtual ~SessionNotfiyMsg(void){};

public:
	uint32_t			nSessionId;							// 
	dpsdk_media_func_e	nMediaType;							// 
};

// 
class DPSDK_API VideoReceiveFirstDataMsg : public SessionNotfiyMsg
{
public:
	VideoReceiveFirstDataMsg(void){ m_cmd = DPSDK_CMD_VIDEO_RECEIVE_FIRST_DATA; }
	virtual ~VideoReceiveFirstDataMsg(void){};
};

// 
class DPSDK_API GetStreamUrlMsg : public DPSDKCBMessage
{
public:
	GetStreamUrlMsg(void);
	virtual ~GetStreamUrlMsg(void){};

public:
	// request
	char				cameraId[DPSDK_CHL_ID_LEN];			// 
	int					streamType;							// 
	int					mediaType;							// 
	int					transMode;							// 1 tcp,0 udp;

	// response
	char				szUrl[DPSDK_TAG_URL_LEN];
	uint32_t			nSessionId;							// cms sessionid
	int 				token;
	int					nTrackId;
};

class DPSDK_API CloseStreamUrlMsg : public DPSDKCBMessage
{
public:
	CloseStreamUrlMsg(void);
	virtual ~CloseStreamUrlMsg(void){};

public:
	uint32_t			nSessionId;
};

// 
class DPSDK_API GetExternalStreamUrlMsg : public DPSDKCBMessage
{
public:
	GetExternalStreamUrlMsg(void);
	virtual ~GetExternalStreamUrlMsg(void){};

public:
	// request
	char				cameraId[DPSDK_CHL_ID_LEN];			// 
	int					streamType;							// 码流类型 
	int					mediaType;							// 媒体类型
	int					transMode;							// 1 tcp,0 udp;
	int					trackId;							// 轨道ID
	bool				bUsedVCS;							// 需要VCS转码
	int					vcsVideocodec;						// 码流转码后的视频编码格式, bUsedVCS为1有效
	int					vcsResolution;						// 码流的视频分辨率，bUsedVCS为1有效
	uint32_t			vcsfps;								// 码流的帧率，bUsedVCS为1有效
	uint32_t			vcsbps;								// 码流的码率，bUsedVCS为1有效

	// response
	char				szUrl[DPSDK_TAG_URL_LEN];
};

// 
class DPSDK_API VideoRtspDisconnectMsg : public SessionNotfiyMsg
{
public:
	VideoRtspDisconnectMsg(void){ m_cmd = DPSDK_CMD_VIDEO_RTSP_DISCONNECT; }
	virtual ~VideoRtspDisconnectMsg(void){};
};

class DPSDK_API LockVideoMsg : public DPSDKCBMessage
{
public:
	LockVideoMsg(void);
	virtual ~LockVideoMsg(void){};

public:
	char					cameraId[DPSDK_CHL_ID_LEN];		// 摄像头ID
	dpsdk_video_locktype_e	lockType;						// 锁定/解锁
};

class DPSDK_API LockVideoNotifyMsg : public DPSDKCBMessage
{
public:
	LockVideoNotifyMsg(void);
	virtual ~LockVideoNotifyMsg(void){};

public:
	char					cameraId[DPSDK_CHL_ID_LEN];		// 摄像头ID
	dpsdk_video_locktype_e	lockType;						// 锁定/解锁
};

class DPSDK_API VideoRecordMsg : public DPSDKCBMessage
{
public:
	VideoRecordMsg(void);
	virtual ~VideoRecordMsg(void){};

public:
	dpsdk_video_record_e  operType;							// 开始视频录像、停止视频录像
	char                  cameraId[DPSDK_CHL_ID_LEN];		// 摄像头ID
	int				      streamType;						// 主辅码流类型
};

class DPSDK_API OpenVideoByUrlMsg : public DPSDKCBMessage
{
public:
	OpenVideoByUrlMsg(void);
	virtual ~OpenVideoByUrlMsg(void){};

public:
	uint32_t			sessionId;							// GetStreamUrl()返回的session
	char				cameraId[DPSDK_CHL_ID_LEN];			// 
	dpsdk_check_right_e right;
	int					transMode;							// 1 tcp,0 udp;
	fMediaDataCallback	cbFun;								// 
	void*				pCbParam;							// 
	char				szRtspUrl[DPSDK_TAG_URL_LEN];
	uint32_t			nSessionForCMS;						// cms sessionid
	int					nToken;

	//扩展字段，为了向指定地址发送视频流
	bool				enableEx;
	std::string			dstIp;
	uint32_t			dstPort;
	std::string			trackID;
	int					rtpHeadType;

	//response
	char				rtpSsrc[DPSDK_RTPCODE_LEN];
	char				srcIp[DPSDK_IP_LEN];
	uint32_t			srcPort;
};

class DPSDK_API RealPlayDescribeMsgEx : public DPSDKCBMessage
{
public:
	RealPlayDescribeMsgEx(void);
	virtual ~RealPlayDescribeMsgEx(void);

public:
	int					sessionId;
	char				cameraId[DPSDK_CHL_ID_LEN];		
	dpsdk_check_right_e right;							// 是否检查权限，DPSDK_NOT_CHECK_RIGHT，不会检查cameraId在组织树缓存中是否存在
	int					transMode;						// 1 tcp,0 udp;
	int				    streamType;						// 主辅码流类型
	int					mediaType;						// 1视频，2音频，3音频＋视频
	bool				enableEx;
	std::string			trackID;
	bool				bMultiCast;
	std::string			rtspUrl;
	uint32_t			sessionForCMS;
	uint32_t			token;

	//response
	char*				sdp;
	int					sdpLength;
};

//for new Protocol:28181
class OpenVideoExWithDescribeMsg : public OpenVideoMsg //remark:为了对外隐藏内部字段 多一重继承
{
public:
	OpenVideoExWithDescribeMsg(void);
	virtual ~OpenVideoExWithDescribeMsg(void);

	//reponse:
	std::string	rtspUrl;
	uint32_t	sessionForCMS;
	uint32_t	token;

	//扩展字段，为了向指定地址发送视频流
	bool		enableEx;
	std::string dstIp;
	uint32_t	dstPort;
	std::string	trackID;
	int			rtpHeadType;
	std::string strDeviceDomainId;

	//Describe response
	char*				sdp;
	int					sdpLength;
};

//////////////////////////////////////////////////////////////////////////

class DPSDK_API IDPSDKReal : public IDPSDKFuncBase
{
public:
	/** 打开视频
	    @param const char* cameraId							
	    @param int streamType 					1主码流，2子码流					
	    @param int mediaTyp						1视频，2音频，3音频＋视频								
	    @param int transMode								
		@param fMediaDataCallback funCB								
		@param void* pCBParam	
		@param dpsdk_tcpmode tcpmode			tcp链接方式 DPSDK_TCPMODE_ACTIVE 主动连接，DPSDK_TCPMODE_PASSIVE 被动连接
	    @return												
	*/
	virtual int OpenVideo(const char* cameraId, int streamType, int mediaType, int transMode, fMediaDataCallback funCB, void* pCBParam, dpsdk_check_right_e right = DPSDK_CHECK_RIGHT, const char* trackID = "", bool bMulticastToUnicast = false, VCSParma_t stuVCSParma = VCSParma_t(), int IsNewMedia = 1, dpsdk_tcpmode tcpmode = DPSDK_TCPMODE_DEFAULT ) = 0 ;
	
	/** 打开视频-for new Protocol:28181
	    @param const char* cameraId							
		@param int streamType 					1主码流，2子码流					
		@param int mediaTyp						1视频，2音频，3音频＋视频							
	    @param int transMode								
		@param const char* dstIp
		@param uint16_t dstPort
		@param const char* trackID	
		@param int rtpHeadType					1RTP,2NONE	
		@param dpsdk_tcpmode tcpmode			tcp链接方式 DPSDK_TCPMODE_ACTIVE 主动连接，DPSDK_TCPMODE_PASSIVE 被动连接
	    @return												
	*/
	virtual int OpenVideoEx( const char* cameraId, int streamType, int mediaType, int transMode, const char* dstIp, uint16_t dstPort, const char* trackID, int rtpHeadType = 1, const char* deviceCode = "", dpsdk_tcpmode tcpmode = DPSDK_TCPMODE_DEFAULT ) = 0;

	/** 打开视频-for new Protocol:28181（网关使用）
	    @param const char* cameraId							
		@param int streamType 					1主码流，2子码流					
		@param int mediaTyp						1视频，2音频，3音频＋视频							
	    @param int transMode								
		@param const char* dstIp
		@param uint16_t dstPort
		@param const char* trackID	
		@param int rtpHeadType					1RTP,2NONE	
		@param dpsdk_tcpmode tcpmode			tcp链接方式 DPSDK_TCPMODE_ACTIVE 主动连接，DPSDK_TCPMODE_PASSIVE 被动连接
	    @return												
	*/
	virtual int OpenVideoExWithDescribe( const char* cameraId, int streamType, int mediaType, int transMode, const char* dstIp, uint16_t dstPort, const char* trackID, int rtpHeadType = 1, const char* deviceCode = "", dpsdk_tcpmode tcpmode = DPSDK_TCPMODE_DEFAULT ) = 0;

	/** 打开零通道多画面预览视频
		@param const char* cameraId				摄像头ID						
		@param int streamType					预览画面分割数					
		@param int mediaTyp						1视频，2音频，3音频＋视频								
		@param int transMode					tcp/udp
		@param int nStartChannelIndex			预览起始通道
		@param fMediaDataCallback funCB								
		@param void* pCBParam								
		@return												
	*/
	virtual int OpenVideoPreview( const char* cameraId, int streamType, int mediaType, int transMode, int nStartChannelIndex, fMediaDataCallback funCB, void* pCBParam, dpsdk_check_right_e right = DPSDK_CHECK_RIGHT ) = 0;

	/** 组播方式打开视频
	    @param const char* cameraId							
	    @param int streamType 	 				1主码流，2子码流					
	    @param int mediaTyp      				1视频，2音频，3音频＋视频																
		@param fMediaDataCallback funCB								
		@param void* pCBParam		
		@param dpsdk_trackid_type_e trackId		载荷类型
		@param const char* szMultiIp			组播地址
		@param int nMultiPort					组播端口
		@param bool bDecouple					解耦标志
	    @return												
	*/
	virtual int MulticastVideo(const char* cameraId, int streamType, int mediaType, fMediaDataCallback funCB, void* pCBParam, dpsdk_trackid_type_e trackId = DPSDK_TRACKID_DHAV,  const char* szMultiIp = "", int nMultiPort = 0, bool bDecouple = false) = 0 ;

	/** 组播方式打开视频，消息回调组播IP和端口给上层
	    @param const char* cameraId							
	    @param int streamType 	 				1主码流，2子码流					
	    @param int mediaTyp      				1视频，2音频，3音频＋视频																	
		@param const char* trackID				载荷类型
	    @return												
	*/
	virtual int MulticastVideoEx(const char* cameraId, int streamType, int mediaType, const char* trackID) = 0 ;

	/** 组播方式打开零通道多画面预览视频
		@param const char* cameraId				摄像头ID						
		@param int streamType					预览画面分割数					
		@param int mediaTyp						1视频，2音频，3音频＋视频								
		@param int nStartChannelIndex			预览起始通道
		@param fMediaDataCallback funCB			
		@param void* pCBParam				
		@param dpsdk_trackid_type_e trackId		载荷类型
		@return												
	*/
	virtual int MulticastVideoPreview( const char* cameraId, int streamType, int mediaType, int nStartChannelIndex, fMediaDataCallback funCB, void* pCBParam, dpsdk_trackid_type_e trackId = DPSDK_TRACKID_DHAV) = 0;

	/** 关闭视频
	    @param uint32_t sessionId							
	    @return												
	*/
	virtual int CloseVideo(uint32_t sessionId) = 0;
	
	/** 关闭视频，不产生sequence
	    @param uint32_t sessionId
		@param int      seq
	    @return												
	*/
	virtual int CloseVideo(uint32_t sessionId, int seq) = 0;

	/** 暂停播放视频
	    @param uint32_t sessionId							
	    @return												
	*/
	virtual int PauseVideo(uint32_t sessionId) = 0;
	
	/** 继续播放视频
	    @param uint32_t sessionId							
	    @return												
	*/
	virtual int ResumeVideo(uint32_t sessionId) = 0;

	/** 获取播放视频的URL路径
		@param const char* cameraId							
		@param int streamType 					1主码流，2子码流					
		@param int mediaTyp						1视频，2音频，3音频＋视频								
		@param int transMode
	    @return												
	*/
	virtual int GetStreamUrl(const char* cameraId, int streamType, int mediaType, int transMode) = 0;

	/** 释放播放视频的URL路径
		@param uint32_t nSessionId				
	    @return												
	*/
	virtual int CloseStreamUrl(uint32_t nSessionId) = 0;

	/** 锁定/解锁
		@param const char* cameraId				摄像头ID
		@param dpsdk_video_locktype_e Lock_e	锁定/解锁
		@return									异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int LockVideo(const char* cameraId, dpsdk_video_locktype_e lockType) = 0;

	/** 获取播放视频的外部URL路径
		@param const GetExternalRealStreamUrlInfo_t* pExternalRealStreamUrlInfo 获取外部URL信息				
		@return												
	*/
	virtual int GetExternalStreamUrl(const GetExternalRealStreamUrlInfo_t* pExternalRealStreamUrlInfo) = 0;
	
	/** 打开视频 for MGW
	    @param const char* cameraId							
	    @param int streamType 					1主码流，2子码流					
	    @param int usedvcs						VCS转码标志
		@param Open_video_Re_Direct reDriectParam
		@param fMediaDataCallback funCB								
		@param void* pCBParam								
	    @return												
	*/
	virtual int OpenVideoReDirect(const char* cameraId, int streamType, fMediaDataCallback funCB, void* pCBParam, int usedvcs, Open_video_Re_Direct reDriectParam) = 0 ;

	/** 操作视频录像（主要针对摄像头）发送给服务进行中心录像
		@param dpsdk_video_record_e nOperType	1开启视频录像或者2停止视频录像
		@param const char* cameraId				摄像头ID
		@param int streamType					1主码流，2子码流
		@return	
	*/
	virtual int VideoRecord(dpsdk_video_record_e nOperType,const char* cameraID,int nStreamType) = 0;

	/** 根据URL播放实时视频
		@param const char* cameraId				通道ID
		@param uint32_t nSessionId				GetStreamUrl()返回的SessionId
		@param const char* szRtspUrl 			URL
		@param int nSessionForCMS
		@param int nToken
		@param const char* dstIp
		@param uint16_t dstPort
		@param const char* trackID
		@param int nTranMode					传输模式，1：TCP 0：UDP
		@param int 	rtpHeadType	 1RTP,2NONE	
	    @return												
	*/
	virtual int OpenVideoByUrl(const char* cameraId, uint32_t nSessionId, const char* szRtspUrl, int nSessionForCMS, int nToken, const char* dstIp, uint16_t dstPort, const char* trackID, int nTranMode = 1, int rtpHeadType = 1) = 0;

	/** 获取实时视频Describe应答信息（平台网关使用）
		@param const char* cameraId							
		@param int streamType 					1主码流，2子码流					
		@param int mediaTyp						1视频，2音频，3音频＋视频								
		@param int transMode					传输模式，1：TCP 0：UDP
		@param int right						是否检查权限，DPSDK_NOT_CHECK_RIGHT，不会检查cameraId在组织树缓存中是否存在
		@param const char* trackID
	    @return
		@remark 
	*/
	virtual int RealPlayDescribeEx( const char* cameraId, int streamType, int mediaType, int transMode, dpsdk_check_right_e right = DPSDK_CHECK_RIGHT, const char* trackID = "701") = 0;

protected:
	virtual ~IDPSDKReal(void){}
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif
