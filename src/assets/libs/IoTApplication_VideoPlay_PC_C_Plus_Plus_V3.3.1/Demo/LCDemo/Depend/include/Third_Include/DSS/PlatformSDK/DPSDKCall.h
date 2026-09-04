/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,Sip子模块
 *
 * 当前版本：1.0
 * 原作者　：12852
 * 完成日期：
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKCALL_H
#define INCLUDED_DPSDK_DPSDKCALL_H

#include "DPSDK.h"
#include "DPSDKGeneral.h"   // GeneralJsonTransportMsg
#include <jsondsl/json.h>
#include <string>


BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

#define JSON_METHOD_BYE_NOTIFY		"Scs.NotifyBye"
#define JSON_METHOD_UTXDEMAND		"CallManager.uTxDemand"
#define JSON_METHOD_UTXCEASED		"CallManager.uTxCeased"
#define JSON_METHOD_UTXGRANTED		"CallManager.uTxGranted"
#define JSON_METHOD_UTXINTERRUPT	"CallManager.uTxInterrupt"
#define JSON_METHOD_DTXCEASED		"CallManager.dTxCeased"
#define JSON_METHOD_DTXGRANTED		"CallManager.dTxGranted"
#define JSON_METHOD_DTXINTERRUPT	"CallManager.dTxInterrupt"
#define JSON_METHOD_SENDTEXT		"CallManager.SendText"
#define JSON_METHOD_SENDPIC			"CallManager.SendPicture"
#define JSON_METHOD_SENDCASE		"CallManager.SendCase"
#define JSON_METHOD_SENDPOINT		"CallManager.SendPoint"
#define JSON_METHOD_MEETINGMSG		"CallManager.MeetingMsg"
#define JSON_METHOD_SCGENERALTRANSPORT		"CallManager.SCGeneralTransport"
#define JSON_METHOD_CLIENT_BYE		"Client.bye"
#define JSON_METHOD_APP_NOTIFY		"Scs.NotifyAPP"

// 呼叫业务状态
typedef enum
{
	CALL_STATUS_PREPARED,			//准备
	CALL_STATUS_REQTOSCS,			//向SCS请求
	CALL_STATUS_CALLING,			//呼叫中
	CALL_STATUS_RECVING,			//接收中
	CALL_STATUS_CEASED,				//呼叫释放
}dpsdk_call_status_e;

typedef enum
{
	CALL_TYPE_SINGLE_CALL,			// 单呼
	CALL_TYPE_GROUP_CALL,			// 组呼
	CALL_TYPE_VT_CALL,				// 可视对讲
}dpsdk_call_type_e;

#ifdef DPSDK_FUNC_ENABLE_CALL
// 还未解析的SIP协议数据
class DPSDK_API NetSipPduMsg : public DPSDKCBMessage
{
public:
	NetSipPduMsg();
	virtual ~NetSipPduMsg();
	void CopyData(const char* pData, int nMethod, int nType);

	char*		data;
	char		serverId[SERVER_ID_LEN];
	int			m_nMethod;
	int			m_nType;
};

#endif

class DPSDK_API ScsLoginMsg : public DPSDKCBMessage
{
public:
	char			ip[DPSDK_IP_LEN];
	int				port;

	ScsLoginMsg();
	virtual ~ScsLoginMsg(){}
};

class DPSDK_API ScsLogoutMsg : public DPSDKCBMessage
{
public:
	char			ip[DPSDK_IP_LEN];
	int				port;

	ScsLogoutMsg();
	virtual ~ScsLogoutMsg(){}
};
class DPSDK_API StartCallMsg : public DPSDKCBMessage
{
public:
	StartCallMsg();
	virtual ~StartCallMsg(){}

public:
	uint32_t			sessionId;						// 语音对讲会话Id
	char				szGroupId[DPSDK_CHL_ID_LEN];	// 设备ID或通道ID
	std::string			strSendChnlID;					// 发送通道ID
	std::string			strRecvChnlID;					// 接收通道ID
	//std::string		rtspUrl;
	std::string			rtpServIP;						// 远端RTP IP
	int					rtpPort;						// 远端RTP端口
	int					talkMode;						// 对讲模式 0对讲 1广播（喊话）
	int					audioType;						// 1 PCM，2 G.711，3 G.723，4 G.726，5 G.729
	int					audioBit;						// 用实际的值表示，如8位 则填值为8
	uint32_t			sampleRate;						// 采样率，如16k 则填值为16000	
	int					transMode;						// 1 tcp,2 udp;

	fMediaDataCallback	cbFun;							// 回调函数
	void*				pCbParam;						// 回调参数

	//SCS返回，报错时候使用
	int					cmsaudioType;					// 1 PCM，2 G.711，3 G.723，4 G.726，5 G.729
	int					cmsaudioBit;					// 用实际的值表示，如8位 则填值为8
	uint32_t			cmssampleRate;					// 采样率，如16k 则填值为16000
	uint32_t			sessionForSCS;

	int					callId;
	int					dlgId;

	dpsdk_call_type_e	nCallType;						// 呼叫类型，单呼还是组呼
};

class DPSDK_API SendTextMsg : public GeneralJsonTransportMsg
{
public:
	SendTextMsg(void);
	virtual ~SendTextMsg(void){}

public:
	char		szGroupId[DPSDK_CHL_ID_LEN];			// 设备ID或通道ID
	uint32_t	sessionId;								// 语音对讲会话Id
	char		textLength[DPSDK_SCS_TEXTLEN];			// 发送文本长度
};
class DPSDK_API StopCallMsg : public DPSDKCBMessage
{
public:
	StopCallMsg(void);
	virtual ~StopCallMsg(void){}

public:
	char		szGroupId[DPSDK_CHL_ID_LEN];			// 设备ID或通道ID
	uint32_t	sessionId;								// 语音对讲会话Id
	int			callId;
	int			dlgId;
};

class DPSDK_API InviteCallMsg : public DPSDKCBMessage
{
public:
	InviteCallMsg(void);
	virtual ~InviteCallMsg(void){}

public:
	char				szSendChnlId[DPSDK_CHL_ID_LEN];		// 接收通道
	char				szRecvChnlId[DPSDK_CHL_ID_LEN];		// 发送通道
	std::string			rtpServIP;							// 远端RTP IP
	int					rtpPort;							// 远端RTP端口
	dpsdk_call_type_e	nCallType;							// 呼叫类型，单呼还是组呼
	uint32_t			sessionId;							// 语音对讲会话Id
	fMediaDataCallback	cbFun;								// 回调函数
	void*				pCbParam;							// 回调参数
	char				szGroupId[DPSDK_CHL_ID_LEN];		// 设备ID或通道ID
	int					callId;
	int					dlgId;
	int					tid;
};

class DPSDK_API ByeCallMsg : public DPSDKCBMessage
{
public:
	ByeCallMsg(void);
	virtual ~ByeCallMsg(void){}

public:
	char		szGroupId[DPSDK_CHL_ID_LEN];				// 设备ID或通道ID
	uint32_t	sessionId;									// 语音对讲会话Id
	int			callId;
	int			dlgId;
	int			tid;				
};

class DPSDK_API ModifyCallStatusMsg : public DPSDKCBMessage
{
public:
	ModifyCallStatusMsg(void);
	virtual ~ModifyCallStatusMsg(void){}

public:
	uint32_t				sessionId;						// 语音对讲会话Id
	dpsdk_call_status_e		nCallStatus;					//呼叫状态
};

class DPSDK_API CallInviteNotifyMsg : public DPSDKCBMessage
{
public:
	CallInviteNotifyMsg();
	virtual ~CallInviteNotifyMsg(){}

public:
	int					audioType;					// 1 PCM，2 G.711，3 G.723，4 G.726，5 G.729
	int					audioBit;					// 用实际的值表示，如8位 则填值为8
	uint32_t			sampleRate;					// 采样率，如16k 则填值为16000	
	std::string			rtpServIP;
	int					rtpPort;
	dpsdk_call_type_e	nCallType;					//呼叫类型，单呼还是组呼
	std::string			groupID;					//呼叫者ID，组呼时为组ID，单呼时为ID#IP
	std::string			callerID;					//讲话者ID
	std::string			sendChnlID;					//发送通道，单呼时才会用到
	std::string			recvChnlID;					//接收通道，穿网包需要带上
	int					callId;
	int					dlgId;
	int                 tid;
};

class DPSDK_API VtCallInviteNotifyMsg : public DPSDKCBMessage
{
public:
	VtCallInviteNotifyMsg();
	virtual ~VtCallInviteNotifyMsg(){}

public:
	int					audioType;					// 1 PCM，2 G.711，3 G.723，4 G.726，5 G.729
	int					audioBit;					// 用实际的值表示，如8位 则填值为8
	uint32_t			sampleRate;					// 采样率，如16k 则填值为16000	
	std::string			rtpServIP;
	int					rtpAPort;					// 音频端口
	int					rtpVPort;					// 视频端口
	dpsdk_call_type_e	nCallType;					// 呼叫类型，单呼还是组呼
	std::string			szUserId;					// 呼叫者ID
	int					callId;
	int					dlgId;
	int                 tid;
	std::string			strDevId;
	int					nDevType;
};
class DPSDK_API VtCallInfoMsg : public DPSDKCBMessage
{
public:
	VtCallInfoMsg();
	virtual ~VtCallInfoMsg(){}

public:
	dsl::Json::Value	rdata;						// 收到的原始数据,一般是服务端填的值	
};
//vtcall end

class DPSDK_API RingCallMsg : public DPSDKCBMessage
{
public:
	RingCallMsg(void);
	virtual ~RingCallMsg(void){}

public:
	char		szUserId[DPSDK_CHL_ID_LEN];				// 设备ID或通道ID
	uint32_t	audioSessionId;								// 语音会话Id
	uint32_t	videoSessionId;								// 视频会话Id
	int			callId;
	int			dlgId;
	int			tid;				
};

class DPSDK_API RingResponseMsg : public DPSDKCBMessage
{
public:
	RingResponseMsg(void);
	virtual ~RingResponseMsg(void){}

public:
	char		szUserId[DPSDK_CHL_ID_LEN];				// 设备ID或通道ID
	int			callId;
	int			dlgId;
	int			tid;				
};
class DPSDK_API ByeVtCallMsg : public DPSDKCBMessage
{
public:
	ByeVtCallMsg(void);
	virtual ~ByeVtCallMsg(void){}

public:
	char		szUserId[DPSDK_CHL_ID_LEN];				// 设备ID或通道ID
	uint32_t	audioSessionId;								// 语音会话Id
	uint32_t	videoSessionId;								// 视频会话Id
	int			callId;
	int			dlgId;
	int			tid;				
};
class DPSDK_API  ModifyVtCallStatusMsg : public DPSDKCBMessage
{
public:
	ModifyVtCallStatusMsg(void);
	virtual ~ModifyVtCallStatusMsg(void){}

public:
	uint32_t				sessionId;						// 语音对讲会话Id
	uint32_t				audioSessionId;					// 语音会话Id
	uint32_t				videoSessionId;					// 视频会话Id
	dpsdk_call_status_e		nCallStatus;					// 呼叫状态

};


//vtcall start
class DPSDK_API StartVtCallMsg : public DPSDKCBMessage
{
public:
	StartVtCallMsg();
	virtual ~StartVtCallMsg(){}

public:
	uint32_t			videoSessionId;					// 视频sessionId
	uint32_t			audioSessionid;					// 音频sessionId
	int					videoPort;						// 视频端口
	int					audioPort;						// 音频端口
	char				szUserId[DPSDK_CHL_ID_LEN];	// 设备ID或通道ID
	//std::string		rtspUrl;
	std::string			rtpServIP;						// 远端RTP IP
	int					rtpAPort;						// 远端RTP音频端口
	int					rtpVPort;						// 远端RTP视频端口
	int					talkMode;						// 对讲模式 0对讲 1广播（喊话）
	int					audioType;						// 1 PCM，2 G.711，3 G.723，4 G.726，5 G.729
	int					audioBit;						// 用实际的值表示，如8位 则填值为8
	uint32_t			sampleRate;						// 采样率，如16k 则填值为16000	
	int					transMode;						// 1 tcp,2 udp;

	fMediaDataCallback	cbFun;							// 回调函数
	void*				pCbParam;						// 回调参数

	//SCS返回，报错时候使用
	int					cmsaudioType;					// 1 PCM，2 G.711，3 G.723，4 G.726，5 G.729
	int					cmsaudioBit;					// 用实际的值表示，如8位 则填值为8
	uint32_t			cmssampleRate;					// 采样率，如16k 则填值为16000
	uint32_t			sessionForSCS;

	int					callId;
	int					dlgId;

	dpsdk_call_type_e	nCallType;						// 呼叫类型，单呼还是组呼
	std::string			strDevId;
	int					nDevType;
};

class DPSDK_API StopVtCallMsg : public DPSDKCBMessage
{
public:
	StopVtCallMsg(void);
	virtual ~StopVtCallMsg(void){}

public:
	char		szUserId[DPSDK_CHL_ID_LEN];			// 设备ID或通道ID
	uint32_t	audioSessionId;							// 语音会话Id
	uint32_t	videoSessionId;							// 视频会话Id
	int			callId;
	int			dlgId;
};
class DPSDK_API BusyVtCallMsg : public DPSDKCBMessage			// 呼叫繁忙
{
public:
	BusyVtCallMsg(void);
	virtual ~BusyVtCallMsg(void){}
public:
	char szUserId[DPSDK_CHL_ID_LEN];
	int callId;
	int dlgId;
};
class DPSDK_API CancelVtCallMsg : public DPSDKCBMessage		//主叫方取消呼叫
{
public:
	CancelVtCallMsg(void);
	virtual ~CancelVtCallMsg(void){}

public:
	char		szUserId[DPSDK_CHL_ID_LEN];			// 设备ID或通道ID
	uint32_t	audioSessionId;						// 音频会话Id
	uint32_t	videoSessionId;						// 视频会话Id
	int			callId;
	int			dlgId;
};

class DPSDK_API RejectVtCallMsg : public DPSDKCBMessage		//主叫方取消呼叫
{
public:
	RejectVtCallMsg(void);
	virtual ~RejectVtCallMsg(void){}

public:
	char		szUserId[DPSDK_CHL_ID_LEN];			// 设备ID或通道ID
	int			callId;
	int			dlgId;
	int         tId;
};


class DPSDK_API InviteVtCallMsg : public DPSDKCBMessage
{
public:
	InviteVtCallMsg(void);
	virtual ~InviteVtCallMsg(void){}

public:
	std::string			rtpServIP;							// 远端RTP IP
	int					rtpAPort;							// 远端RTP音频端口
	int					rtpVPort;							// 远端RTP视频端口
	dpsdk_call_type_e	nCallType;							// 呼叫类型，单呼还是组呼
	uint32_t			videoSessionId;						// 视频sessionId
	uint32_t			audioSessionid;						// 音频sessionId
	fMediaDataCallback	cbFun;								// 回调函数
	void*				pCbParam;							// 回调参数
	char				szUserId[DPSDK_CHL_ID_LEN];		// 设备ID或通道ID
	int					callId;
	int					dlgId;
	int					tid;
	int                 nAudioType;
	int                 nAduioBits;
	int                 nSampleRate;
};

class DPSDK_API SCSMessageNotifyMsg : public DPSDKCBMessage
{
public:
	SCSMessageNotifyMsg();
	virtual ~SCSMessageNotifyMsg(){}

public:
	dsl::Json::Value	rdata;						// 收到的原始数据,一般是服务端填的值
};

class DPSDK_API SCSTextNotifyMsg : public DPSDKCBMessage
{
public:
	SCSTextNotifyMsg();
	virtual ~SCSTextNotifyMsg(){}
	
public:
	dsl::Json::Value	rdata;						// 收到的文本数据
};

class DPSDK_API SCSAPPNotifyMsg : public DPSDKCBMessage
{
public:
	SCSAPPNotifyMsg();
	virtual ~SCSAPPNotifyMsg(){}

public:
	dsl::Json::Value	rdata;						// 收到的文本数据
};
//////////////////////////////////////////////////////////////////////////
class DPSDK_API IDPSDKCall : public IDPSDKFuncBase
{
public:
	/** 打开呼叫
	    @param const char* szGroupId					呼叫组ID
		@param fMediaDataCallback funCB					回调函数
		@param void* pCBParam							回调参数
		@return											异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int StartCall(dpsdk_call_type_e	nCallType, const char* szGroupId, fMediaDataCallback funCB, void* pCBParam) = 0 ;
	virtual int StartVtCall(dpsdk_call_type_e nCallType, uint32_t &audioSessionId, uint32_t &videoSessionId, const char* szUserId, fMediaDataCallback funCB, void* pCBParam) = 0;
	/** 拒绝接听来电
	    @param const char* szUserId						对方用户ID
		@param int nCallId							呼叫时的ID
		@param int dlgId							呼叫时的参数Id
		@return											异步顺序码,用于事件回调时,与应答事件匹配	
	*/
	virtual int sendRejectVtCall(const char* szUserId, int nCallId, int dlgId, int nTid)=0;
	/** 关闭呼叫
		@param const char* szGroupId					呼叫组ID
		@param uint32_t sessionId						呼叫会话Id
		@return											异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int StopCall(const char* szGroupId, uint32_t sessionId) = 0;

	/** 关闭可视对讲呼叫
		@param const char* szUserId						对方用户ID
		@param uint32_t audioSessionId					音频会话Id
		@param uint32_t videoSessionId					视频会话Id
		@return											异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int StopVtCall(const char* szUserId, uint32_t audioSessionId, uint32_t videoSessionId,int m_callId = 0, int m_dlgId = 0) = 0;

	/** 发送文本
		@param const char* szGroupId					呼叫组ID
		@param szStrText								发送的文本内容					
		@return											异步顺序码,用于事件回调时,与应答事件匹配
		@remark                                         此接口写死参数，调用者慎用！
	*/
	virtual int SendScsMsg(const char* szGroupId, const char* szStrText) = 0;

	/** 呼叫邀请
	    @param const char* szChnlId						通道ID
		@param fMediaDataCallback funCB					回调函数
		@param void* pCBParam							回调参数
		@return											异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int InviteCall(dpsdk_call_type_e nCallType, const char* szSendChnlId, const char* szRecvChnlId, const char* szRtpServIP, int nRtpPort, int nCallID, int nDlgID, int nTid, fMediaDataCallback funCB, void* pCBParam) = 0 ;
			
	/** 可视对讲呼叫邀请
		@param cosnt char* szRtpServIP					rtp服务IP
		@param int nRtpAPort							rtp服务音频端口
		@param int nRtpVPort							rtp服务视频端口
		@param fMediaDataCallback funCB					回调函数
		@param void* pCBParam							回调参数
		@return											异步顺序码,用于事件回调时,与应答事件匹配			
	*/	
	virtual int InviteVtCall(InviteVtCallMsg* pVtCallMsg) = 0;

	/** 呼叫被挂断，释放链接
		@param const char* szGroupId					呼叫组ID
		@param uint32_t sessionId						呼叫会话Id
		@return											异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int ByeCall(const char* szGroupId, uint32_t sessionId, int nTid) = 0;

	/** 可视对讲呼叫被挂断，释放链接
		@param const char* szUserId						用户Id
		@param uint32_t audioSessionId					音频会话Id
		@param uint32_t videoSessionId					视频会话Id
		@return											异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int ByeVtCall(const char* szUserId, uint32_t audioSessionId, uint32_t videoSessionId, int nTid) = 0;
	
	/**可视对讲信息分发和快递通知
		Json::Value cData 消息体
	*/
	virtual int sendVtCallInfo(dsl::Json::Value cData) = 0;

	/** 中断呼叫
		@param const char* szGroupId					呼叫组ID
		@param uint32_t sessionId						呼叫会话Id
		@return											异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int ModifyCallStatus(const char* szGroupId, DPSdk::dpsdk_call_status_e nCallStatus, uint32_t sessionId) = 0;

	/** 中断呼叫
		@param const char* szGroupId					呼叫组ID
		@param uint32_t audioSessionId					音频会话Id
		@param uint32_t videoSessionId					视频会话Id
		@return											异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int ModifyVtCallStatus(const char* szUserId, dpsdk_call_status_e nCallStatus, uint32_t audioSessionId, uint32_t videoSessionId) = 0;

	
	virtual int sendCancelVtCall(const char* szUserId, uint32_t audioSessionId, uint32_t videoSessionId, int callId, int dlgId) = 0;
	/** 获取音频发送函数指针
		@param fAudioDataCallback& audioCb				函数地址
		@param void* userParam							用户参数
		@return											是否成功			
	*/
	virtual int GetAudioSendFunCallBack(fAudioDataCallback& audioCb, void* userParam) = 0;

	/** 获取可视对讲音频发送函数指针
		@param fAudioDataCallback& audioCb				函数地址
		@param void* userParam							用户参数
		@return											是否成功			
	*/
	virtual int GetIntercomAudioSendFunCallBack(fAudioDataCallback& audioCb, void* userParam) = 0;
protected:
	virtual ~IDPSDKCall(void){}
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif

