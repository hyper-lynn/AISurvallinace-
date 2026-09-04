/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,语音对讲子模块
 *
 * 当前版本：1.0
 * 原作者　：12928
 * 完成日期：2012年9月11日
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKTALK_H
#define INCLUDED_DPSDK_DPSDKTALK_H

#include "DPSDK.h"
#include <string>
#include <list>
#include "DPSDKGeneral.h"   // GeneralJsonTransportMsg

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

// 
typedef struct DPSDK_API tagAudioUserParam
{
	void* objectPoint;										// 

	tagAudioUserParam(void)
	{
		objectPoint = 0;
	}
}AudioUserParam_t;

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
}dpsdk_talk_coding_type_e;
//////////////////////////////////////////////////////////////////////////

// 开始对讲消息回调（CMD=DPSDK_CMD_START_TALK）
class DPSDK_API StartTalkMsg : public DPSDKCBMessage
{
public:
	StartTalkMsg(void);
	virtual ~StartTalkMsg(void){}

public:
	uint32_t			sessionId;							// 语音对讲会话Id
	char				szId[DPSDK_CHL_ID_LEN];				// 设备ID或通道ID
	int					talkType;							// 对讲类型 1设备 2通道
	int					audioType;							// 1 PCM，2 G.711，3 G.723，4 G.726，5 G.729
	int					audioBit;							// 用实际的值表示，如8位 则填值为8
	uint32_t			sampleRate;							// 采样率，如16k 则填值为16000	
	int					transMode;							// 1 tcp,2 udp;

	fMediaDataCallback	cbFun;								// 回调函数
	void*				pCbParam;							// 回调参数

    bool                bLocalDev;                          // 设备与设备对讲 表示该设备是本地设备的ID
    bool                bBroadCast;                         // true 表示广播  false表示对讲
	
	// for new Protocol:28181 ---request
	int					nRtpHeadType;
	char				szSrcId[DPSDK_CHL_ID_LEN];			// 客户端标记：18位国标编码
	char				szDstId[DPSDK_CHL_ID_LEN];			// 目标广播设备的18位国标编码

	// for new Protocol:28181 ---response
	char				szReceiveIP[DPSDK_IP_LEN];			// 接收ip
	uint32_t			nReceivePort;						// 接收端口

	//cms返回，报错时候使用
	uint32_t			cmsaudioType;						// 1 PCM，2 G.711，3 G.723，4 G.726，5 G.729
	uint32_t			cmsaudioBit;						// 用实际的值表示，如8位 则填值为8
	uint32_t			cmssampleRate;						// 采样率，如16k 则填值为16000	
};

// 停止对讲消息回调（CMD=DPSDK_CMD_STOP_TALK）
class DPSDK_API StopTalkMsg : public DPSDKCBMessage
{
public:
	StopTalkMsg(void);
	virtual ~StopTalkMsg(void){}

public:
	char		szId[DPSDK_CHL_ID_LEN];						// 设备ID或通道ID
	int			talkType;									// 对讲类型 1设备 2通道
	uint32_t	sessionId;									// 语音对讲会话Id
};

// 暂定对讲消息回调（CMD=DPSDK_CMD_PAUSE_TALK）
class DPSDK_API PauseTalkMsg : public DPSDKCBMessage
{
public:
	PauseTalkMsg(void);
	virtual ~PauseTalkMsg(void){}

public:
	uint32_t	sessionId;									// 对讲会话ID
};

// 恢复对讲消息回调（CMD=DPSDK_CMD_RESUME_TALK）
class DPSDK_API ResumeTalkMsg : public DPSDKCBMessage
{
public:
	ResumeTalkMsg(void);
	virtual ~ResumeTalkMsg(void){}

public:
	uint32_t	sessionId;									// 对讲会话ID
};

// 对讲异常通知消息（CMD=DPSDK_CMD_TALK_EXPECTION）
class DPSDK_API TalkExpctionMsg : public DPSDKCBMessage
{
public:
	TalkExpctionMsg(void);
	virtual ~TalkExpctionMsg(void){};

	int			nExceptionType;								// 异常类型 参见EnumRealException区分子类型
	char		cameraId[DPSDK_CHL_ID_LEN];					// 摄像头ID

	int			nSessionId;									// 对讲会话ID
	int			nTalkType;									// 对讲类型 1设备 2通道
	char		szUrl[1024];								// 
};

class DPSDK_API OperTalkFileMsg : public DPSDKCBMessage
{
public:
	OperTalkFileMsg(void);
	virtual ~OperTalkFileMsg(void){}

	dpsdk_operator_ftp_type_e	opType;						// 操作类型，请参考dpsdk_operator_ftp_type_e
	char		url[DPSDK_TAG_URL_LEN];						// ftp服务器存储数据的相对url
	char		path[DPSDK_TAG_PATH_LEN];					// 本地上传或者下载后的对讲文件的地址
	dpsdk_ftp_transport_mode_e  mode;						// 文件传输模式
};

typedef struct DPSDK_API tagTalkFileInfo
{    
	std::string			strTalkFileId;						// 唯一标志位
	std::string			strChnlId;							// 通道id
	std::string			strAlarmId;							// 报警id
	std::string			strFileName;						// 对讲录像文件名称
	std::string			strFileFtpPath;						// 对讲录像文件ftp路径
	int					nProvider;							// 设备厂商类型，0：未知  1：大华  2：海康
	int					nRecLength;							// 录像文件大小
	int64_t				nRecStartTime;						// 录像开始时间
	int64_t				nRecEndTime;						// 录像结束时间
	std::string			strDeptId;							// 组织ID
	std::string			strDevId;							// 设备ID
	std::string			strAudioFile;						// IP对讲录像文件名称
	int					nRecType;							// 0:语音对讲录像 1：IP对讲录像
	std::string			strRemark;							// 备注
	uint32_t			nUserId;							// 上传用户id
	int64_t				nUploadTime;						// 上传时间
	std::string			strChnlName;						// 通道名称
	std::string			strDevName;							// 设备名称

	tagTalkFileInfo& operator = (const tagTalkFileInfo& other)
	{
		if (this == &other)
		{
			return *this;
		}
		strTalkFileId = other.strTalkFileId;				// 唯一标志位
		strChnlId = other.strChnlId;						// 通道id
		strAlarmId = other.strAlarmId;						// 报警id
		strFileName = other.strFileName;					// 对讲录像文件名称
		strFileFtpPath = other.strFileFtpPath;				// 对讲录像文件ftp路径
		nProvider = other.nProvider;						// 设备厂商类型，0：未知  1：大华  2：海康
		nRecLength = other.nRecLength;						// 录像文件大小
		nRecStartTime = other.nRecStartTime;				// 录像开始时间
		nRecEndTime = other.nRecEndTime;					// 录像结束时间
		strDeptId = other.strDeptId;						// 组织ID
		strDevId = other.strDevId;							// 设备ID
		strAudioFile = other.strAudioFile;					// IP对讲录像文件名称
		nRecType = other.nRecType;							// 0:语音对讲录像 1：IP对讲录像
		strRemark = other.strRemark;						// 备注
		nUserId = other.nUserId;							// 上传用户id
		nUploadTime = other.nUploadTime;					// 上传时间
		strChnlName = other.strChnlName;					// 通道名称
		strDevName = other.strDevName;						// 设备名称
		return *this;
	}
	void Reset()
	{
		strTalkFileId = "";									// 唯一标志位
		strChnlId = "";										// 通道id
		strAlarmId = "";									// 报警id
		strFileName = "";									// 对讲录像文件名称
		strFileFtpPath = "";								// 对讲录像文件ftp路径
		nProvider = 0;										// 设备厂商类型，0：未知  1：大华  2：海康
		nRecLength = 0;										// 录像文件大小
		nRecStartTime = 0;									// 录像开始时间
		nRecEndTime = 0;									// 录像结束时间
		strDeptId = "";										// 组织ID
		strDevId = "";										// 设备ID
		strAudioFile = "";									// IP对讲录像文件名称
		nRecType = 0;										// 0:语音对讲录像 1：IP对讲录像
		strRemark = "";										// 备注
		nUserId = 0;										// 上传用户id
		nUploadTime = 0;									// 上传时间
		strChnlName = "";									// 通道名称
		strDevName = "";									// 设备名称
	}

}TalkFileInfo_t;
typedef std::list<TalkFileInfo_t>TalkFileInfoList;

class DPSDK_API SaveTalkFileInfoMsg : public DPSDKCBMessage
{
public:
	SaveTalkFileInfoMsg(void);
	virtual ~SaveTalkFileInfoMsg(void){}

public:
	TalkFileInfo_t talkFileInfo;
};

// 向CMS查询对讲录像信息
class DPSDK_API QueryTalkFileInfoMsg : public DPSDKCBMessage
{
public:
	QueryTalkFileInfoMsg(void);  
	virtual ~QueryTalkFileInfoMsg(void){};

public:
	// request
	int64_t					nRecStartTime;					// 录像开始时间
	int64_t					nRecEndTime;					// 录像结束时间
	std::string				strChnlId;						// 通道id
	std::string				strAlarmId;						// 报警id（为空时，仅根据其他四个字段）

	// response
	uint32_t				infoCount;						// 返回实际对讲录像条数
	TalkFileInfoList		listTalkFileInfo;				// 指向对讲录像信息数据
};

//广播对讲设备信息
class DPSDK_API BroadcastDev
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
	dpsdk_talk_coding_type_e	m_nAudioType;				// 设备返回的音频编码类型
	uint32_t				m_nAudioBit;					// 音频码率
	uint32_t				m_nSampleRate;					// 音频采样率
	int32_t					m_nResult;						// 单个设备操作的返回值
	std::string				m_strDesc;						// 操作返回描述
};
//广播对讲MTS信息
class DPSDK_API BroadcastMTS
{
public:
	BroadcastMTS():	m_strRtspUrl(""),		
					m_nSessionForCMS(0),
					m_nToken(0),
					m_nAudioType(TALK_DEFAULT),
					m_nAudioBit(0),
					m_nSampleRate(0),
					m_bPlayResp(false){}
	std::string				m_strRtspUrl;
	uint32_t				m_nSessionForCMS;
	uint32_t				m_nToken;
	dpsdk_talk_coding_type_e	m_nAudioType;				// 音频编码类型
	uint32_t				m_nAudioBit;					// 音频码率
	uint32_t				m_nSampleRate;					// 音频采样率
	bool					m_bPlayResp;					// 是否播放开始			

};
// 向CMS请求广播
class DPSDK_API StartBroadcastMsg: public GeneralJsonTransportMsg
{
public:
	StartBroadcastMsg(void)
	{
		m_cmd = DPSDK_CMD_START_BROADCAST;
		trantype = GENERALJSON_TRAN_REQUEST;
		strJson.clear();
		m_vecBroadcastDev.clear();
		m_mapBroadcastMTS.clear();
		m_fun = NULL;
		sessionId = 0;
		m_pParam = NULL;
	}
	virtual ~StartBroadcastMsg(void){}
	fMediaDataCallback m_fun;
	void* m_pParam;
	std::string strJson;
	uint32_t			sessionId;							// 语音对讲会话Id

	std::vector<BroadcastDev> m_vecBroadcastDev;
	std::map<std::string, BroadcastMTS> m_mapBroadcastMTS;
};

// 向CMS请求关闭广播
class DPSDK_API StopBroadcastMsg: public GeneralJsonTransportMsg
{
public:
	StopBroadcastMsg(void)
	{
		m_cmd = DPSDK_CMD_STOP_BROADCAST;
		trantype = GENERALJSON_TRAN_REQUEST;
		strJson.clear();
		sessionId = 0;
	}
	virtual ~StopBroadcastMsg(void){}
	std::string strJson;
	uint32_t			sessionId;							// 语音对讲会话Id
};

typedef struct TalkPutInInfo
{
	std::list<std::string> channlList;
	std::string       VioceFile;

}TalkPutInInfo;

class DPSDKVoicePutInInfo : public DPSDKCBMessage
{   

public:
	TalkPutInInfo  m_VoicePutInInfo;

public:
	DPSDKVoicePutInInfo();
	virtual ~DPSDKVoicePutInInfo(){}

};

class DPSDKStopPutIn : public DPSDKCBMessage
{
public:
	std::list<std::string> channlList;
public:
	DPSDKStopPutIn();
	virtual ~DPSDKStopPutIn(){}
};

//////////////////////////////////////////////////////////////////////////

class DPSDK_API IDPSDKTalk : public IDPSDKFuncBase
{
public:
	/** 打开语音对讲
	    @param const char* szId								设备ID或通道ID
	    @param int talkType									对讲类型 1设备 2通道
		@param int audioType								0 default, 1 PCM，2 G.711a，3 amr，4 G.711u，5 G.726 8 aac, 101 G722, 102 G711_MU
		@param int audioBit;								用实际的值表示，如8位 则填值为8
		@param uint32_t	sampleRate;							采样率，如16k 则填值为16000	
		@param int transMode								1 tcp,0 udp;
		@param fMediaDataCallback funCB						回调函数
		@param void* pCBParam								回调参数
		@param bool bLocalDev                               设备与设备对讲 标志是本地设备
		@param bool bBroadCast                              表示当前要开启的是对讲 还是广播
		@return												异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int StartTalk(const char* szId, int talkType, int audioType, int audioBit, uint32_t sampleRate, int transMode, fMediaDataCallback funCB, void* pCBParam,bool bLocalDev = false,bool bBroadCast = false) = 0 ;
	
	/** 打开国标广播-for new Protocol:28181
	    @param const char* szId								通道ID
		@param int audioType								0 default, 1 PCM，2 G.711a，3 amr，4 G.711u，5 G.726 8 aac, 101 G722, 102 G711_MU
		@param int audioBit;								用实际的值表示，如8位 则填值为8
		@param uint32_t	sampleRate;							采样率，如16k 则填值为16000	
		@param int transMode								1 tcp,0 udp;
		@param const char* szSrcID							28181要求携带的18位客户端标记码
		@param const char* szDstID							28181要求携带的18位设备的国标编码
		@return												异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int StartTalkEx(const char* szId, int audioType, int audioBit, uint32_t sampleRate, int transMode, const char* szSrcID, const char* szDstID, const char* dstIp, uint16_t dstPort, const char* szTrackID, int rtpHeadType = 1) = 0;

	/** 关闭语音对讲
		@param const char* szId								设备ID或通道ID
		@param int talkType									对讲类型 1设备 2通道
		@param uint32_t sessionId							语音对讲会话Id
		@return												异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int StopTalk(const char* szId, int talkType, uint32_t sessionId) = 0;

		/** 关闭语音对讲，不产生sequence
		@param const char* szId								设备ID或通道ID
		@param int talkType									对讲类型 1设备 2通道
		@param uint32_t sessionId							语音对讲会话Id
		@return												异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int StopTalk(const char* szId, int talkType, uint32_t sessionId, int seq) = 0;


	/** 暂停语音对讲
		@param uint32_t sessionId							语音对讲会话Id
		@return												异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int PauseTalk(uint32_t sessionId) = 0;
	
	/** 继续语音对讲
		@param uint32_t sessionId							语音对讲会话Id
		@return												异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int ResumeTalk(uint32_t sessionId) = 0;
	
	/** 获取音频发送函数指针
		@param fAudioDataCallback& audioCb					函数地址
		@param void* userParam								用户参数
		@return												是否成功			
	*/
	virtual int GetAudioFunCallBack(fAudioDataCallback& audioCb, void* userParam) = 0;

	/** 获取音频发送函数指针，可指定对讲sessionID
		@param fAudioDataCallback& audioCb				函数地址
		@param void* userParam							用户参数
		@return											是否成功			
	*/
	virtual int GetAudioFunCallBackEx(fAudioDataCallbackEx& audioCb, void* userParam) = 0;
	
	/** 上传下载对讲录像文件
		@param dpsdk_operator_ftp_type_e optype				操作类型
		@param const char* url								ftp服务器存储数据的相对url
		@param const const char* path						本地上传或者下载后的图片的地址
		@return												是否成功			
	*/
	virtual int OperTalkFile( dpsdk_operator_ftp_type_e optype, const char* url, const char* path , dpsdk_ftp_transport_mode_e mode = MODE_EPSV) = 0;

	/** 保存对讲录像文件信息
		@param TalkFileInfo_t talkFileInfo					对讲录像信息
		@return												是否成功			
	*/
	virtual int SaveTalkRecordInfo(TalkFileInfo_t &talkFileInfo) = 0;
	
	/** 查询对讲录像文件信息
		@param int64_t startTime							开始时间
		@param int64_t endTime								结束时间
		@param std::string strChnlId						通道id
		@param std::string strAlarmId						报警id
		@return												是否成功			
	*/
	virtual int QueryTalkRecordInfo(int64_t startTime, int64_t endTime,std::string strChnlId, std::string strAlarmId = "") = 0;

	/** 打开语音对讲
	    @param std::string& strJsonToCMS					与cms模块交互的json通用协议
		@param fMediaDataCallback funCB						回调函数
		@param void* pCBParam								回调参数
		@return												异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int StartBroadcast(const std::string& strJsonToCMS, fMediaDataCallback funCB, void* pCBParam) = 0 ;
	
	/** 关闭语音对讲
	    @param std::string& strJsonToCMS					与cms模块交互的json通用协议
		@return												异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int StopBroadcast(const std::string& strJsonToCMS, uint32_t sessionId) = 0 ;

	/**
	 语音投放信息
	*/
	virtual int SetVoicePutInInfo(TalkPutInInfo* pVoicePutInInfo) = 0;

	/**
	语音投放 停止
	*/
	virtual int StopVoicePutIn(std::list<std::string>& channlList) = 0;

protected:
	virtual ~IDPSDKTalk(void){}
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif
