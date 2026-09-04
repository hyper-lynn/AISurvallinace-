/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：总后接口文件
 *
 * 当前版本：1.0
 * 原作者　：17026
 * 完成日期：2013年6月21日
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_EXTRA_A_INTERFACE_H
#define INCLUDED_DPSDK_EXTRA_A_INTERFACE_H

#include "DPSDK.h"

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

#define DPSDK_EXTRA_A_DOMAIN_NAME_LEN				64
#define DPSDK_EXTRA_A_OPTION_NAME_LEN				64
#define DPSDK_EXTRA_A_PARAM_NAME_LEN				64
#define DPSDK_EXTRA_A_PARAM_VALUE_LEN				64
#define DPSDK_EXTRA_A_REMARK_LEN					1024
#define DPSDK_EXTRA_A_URL_LEN						1024
#define DPSDK_EXTRA_A_MENU_ID_LEN					64
#define DPSDK_EXTRA_A_MENU_NAME_LEN					128
#define DPSDK_EXTRA_A_NEWS_TITLE_LEN				128
#define DPSDK_EXTRA_A_NEWS_CONTENT_LEN				1024
#define DPSDK_EXTRA_A_NEWS_ACHMENT_NAME_LEN			1024
#define DPSDK_EXTRA_A_NEWS_ATTACHMENT_PATH_LEN		1024
#define DPSDK_EXTRA_A_NEWS_MESSAGE_TYPE_LEN			1024
//////////////////////////////////////////////////////////////////////////

// 获取节点深度类型---在DPSDKDefine.h定义
// typedef enum
// {
// 	GET_ORG_DEPTH_TYPE_ALL			= -1,			// 获取所有子孙节点
// 	GET_ORG_DEPTH_TYPE_SELF			= 0,			// 获取自身
// 	GET_ORG_DEPTH_TYPE_CHILD		= 1,			// 获取子节点
// }dpsdk_get_org_depth_type_e;

// 节点变更类型
typedef enum
{
	ORG_CHANGE_TYPE_UNKNOW			= 0,
	ORG_CHANGE_TYPE_ADD,							// 添加组织
	ORG_CHANGE_TYPE_DEL,							// 删除组织
	ORG_CHANGE_TYPE_MODIFY,							// 修改组织
}dpsdk_org_change_type_e;

// 域状态
typedef enum
{
	DOMAIN_STATUS_OFFLINE			= 0,			// 离线
	DOMAIN_STATUS_ONLINE			= 1,			// 在线
}dpsdk_domain_status_t;

// 域变更类型
typedef enum
{
	DOMAIN_CHANGE_TYPE_UNKNOW		= 0,
	DOMAIN_CHANGE_TYPE_ADD,							// 添加域
	DOMAIN_CHANGE_TYPE_DEL,							// 删除域
	DOMAIN_CHANGE_TYPE_MODIFY,						// 修改域
}dpsdk_domain_change_type_e;

// 视频资源绑定
typedef enum
{
	NOTIFY_RELATION_UNKNOW			= 0,
	NOTIFY_RELATION_ADD,							// 添加关联
	NOTIFY_RELATION_DEL,							// 删除关联
	NOTIFY_RELATION_MODIFY,							// 修改关联			
}dpsdk_notify_relation_e;

// 对讲日志结果
typedef enum
{
	TALK_LOG_RESULT_FAIL			= 0,			// 失败
	TALK_LOG_RESULT_SUCCESS			= 1,			// 成功
}dpsdk_talk_log_result_e;

// 对讲日志类型
typedef enum
{
	TALK_LOG_TYPE_SINGLE			= 1,			// 普通对讲
	TALK_LOG_TYPE_BROADCAST			= 2,			// 普通广播
	TALK_LOG_TYPE_VIDEO_SINGLE		= 3,			// 视频对讲
	TALK_LOG_TYPE_VIDEO_BROADCAST	= 4,			// 视频广播
}dpsdk_talk_log_type_e;

// 对讲日志音频类型
typedef enum
{
	TALK_LOG_AUDIO_TYPE_PCTODEV		= 1,			// PC到设备
	TALK_LOG_AUDIO_TYPE_DEVTODEV	= 2,			// 设备到设备
	TALK_LOG_AUDIO_TYPE_SCHEDULER	= 3,			// 调试机
}dpsdk_talk_log_audio_type_e;

//分享
typedef enum
{
	SHARE_RTSP_UNKNOW				= 0,
	SHARE_RTSP_START				= 1,			// 开始分享
	SHARE_RTSP_STOP					= 2,			// 停止分享
}dpsdk_share_rtsp_e;

// 新闻
typedef enum
{
	NOTIFY_NEWS_UNKNOW				= 0,
	NOTIFY_NEWS_ADD,								// 添加新闻
	NOTIFY_NEWS_DEL,								// 删除新闻
	NOTIFY_NEWS_MODIFY,								// 修改新闻
}dpsdk_notify_news_e;

// 域信息
typedef struct DPSDK_API DomainStatusInfo
{
	uint32_t				nDomainId;								// 域ID
	char					szIp[DPSDK_IP_LEN];						// IP地址
	uint32_t				nPort;									// 端口
	char					szName[DPSDK_EXTRA_A_DOMAIN_NAME_LEN];	// 名称
	dpsdk_domain_status_t	nStatus;								// 状态
}DomainStatusInfo_t;

// 视频资源绑定信息
typedef struct DPSDK_API UserCameraIdInfo
{
	uint32_t	nUserId;											// 用户ID
	char		szUsername[DPSDK_USER_NAME_LEN];					// 用户名
	char		szCameraId[DPSDK_CHL_ID_LEN];						// 绑定的通道ID
	char		szPhone[DPSDK_PHONE_LEN];							// 电话号码
	int			nLevel;												// 级别
}UserCameraIdInfo_t;

// 对讲交互参数信息
typedef struct DPSDK_API CUParamInfo
{
	char	szName[DPSDK_EXTRA_A_PARAM_NAME_LEN];					// 参数名称
	char	szValue[DPSDK_EXTRA_A_PARAM_VALUE_LEN];					// 参数值
}CUParamInfo_t;

// 菜单导航信息
typedef struct DPSDK_API MenuToolInfo
{
	char		szMenuId[DPSDK_EXTRA_A_MENU_ID_LEN];				// 菜单ID
	char		szName[DPSDK_EXTRA_A_MENU_NAME_LEN];				// 名称
	int			nOrder;												// 顺序
	int			nIcon;												// 图片序号
}MenuToolInfo_t;

// 新闻信息
typedef struct DPSDK_API NewsInfo
{
	uint32_t	nNewsId;											// 新闻ID
	uint64_t	nUsefulLife;										// 有效期限
	char		szTitle[DPSDK_EXTRA_A_NEWS_TITLE_LEN];				// 标题
	char		szContent[DPSDK_EXTRA_A_NEWS_CONTENT_LEN];			// 内容
	char		szAttachmentName[DPSDK_EXTRA_A_NEWS_ACHMENT_NAME_LEN];	// 附件名字
	char		szAttachmentPath[DPSDK_EXTRA_A_NEWS_ATTACHMENT_PATH_LEN];	//附件路径
	char		szMessageType[DPSDK_EXTRA_A_NEWS_MESSAGE_TYPE_LEN];	//消息类型
	int			nStatus;											//0消息未读，1消息已读
}NewsInfo_t;
//////////////////////////////////////////////////////////////////////////

// 获取业务树消息
class DPSDK_API GetOrgTreeMsg : public DPSDKCBMessage
{
public:
	GetOrgTreeMsg(void);
	virtual ~GetOrgTreeMsg(void);

public:
	char						szCoding[DPSDK_ID_LEN];				// 节点编码
	dpsdk_get_org_depth_type_e	nDepthType;							// 类型

	char*						pszOrgTree;							// 业务树数据
	uint32_t					nLen;								// 数据长度
};

// 业务树变更消息
class DPSDK_API NotifyOrgTreeMsg : public DPSDKCBMessage
{
public:
	NotifyOrgTreeMsg(void);
	virtual ~NotifyOrgTreeMsg(void);

public:
	dpsdk_org_change_type_e	nType;									// 变更类型
	int						nCount;									// 节点数量
	char					(*pszCoding)[DPSDK_ID_LEN];				// 节点编码
};

// 获取全部域信息消息
class DPSDK_API GetAllDomainInfoMsg : public DPSDKCBMessage
{
public:
	GetAllDomainInfoMsg(void);
	virtual ~GetAllDomainInfoMsg(void);

public:
	int					nCount;										// 域数量
	DomainStatusInfo_t*	pstuDomainInfo;								// 域信息
};

// 域信息变更消息
class DPSDK_API NotifyAllDomainInfoMsg : public DPSDKCBMessage
{
public:
	NotifyAllDomainInfoMsg(void);
	virtual ~NotifyAllDomainInfoMsg(void);

public:
	dpsdk_domain_change_type_e	nType;								// 变更类型 
	int							nCount;								// 域ID数量
	uint32_t*					pDomainIdList;						// 域ID列表
};

// 域状态变更消息
class DPSDK_API NotifyDomainStatusMsg : public DPSDKCBMessage
{
public:
	NotifyDomainStatusMsg(void);
	virtual ~NotifyDomainStatusMsg(void);

public:
	uint32_t				nDomainId;								// 域ID
	dpsdk_domain_status_t	nStatus;								// 域状态
	char m_StrDomainSN[DPSDK_CHAR_LEN_64];								// 域唯一标识码
};

// 获取视频资源绑定消息
class DPSDK_API GetUserCameraIdMsg : public DPSDKCBMessage
{
public:
	GetUserCameraIdMsg(void);
	virtual ~GetUserCameraIdMsg(void);

public:
	uint32_t			nUserId;									// 用户ID

	int					nCount;										// 绑定的个数
	UserCameraIdInfo_t*	pstuUserCameraIdInfo;						// 视频资源绑定信息
};

// 视频资源绑定变更消息
class DPSDK_API NotifyRelationMsg : public DPSDKCBMessage
{
public:
	NotifyRelationMsg(void);
	virtual ~NotifyRelationMsg(void);

public:
	dpsdk_notify_relation_e		nType;								// 通知类型
	int							nCount;								// 用户ID数量
	uint32_t*					pUserIdList;						// 用户ID列表
};

// 对讲交互消息
class DPSDK_API ToCUMsg : public DPSDKCBMessage
{
public:
	ToCUMsg(void);
	virtual ~ToCUMsg(void);

public:
	dpsdk_msg_type_e	nMsgType;									// 消息类型
	int					nResponseSeq;								// 应答消息序号
	int					nGrade;										// 用户等级
	char				szSrcCameraId[DPSDK_CHL_ID_LEN];			// 源视频通道
	char				szDstCameraId[DPSDK_CHL_ID_LEN];			// 目的视频通道
	char				szOption[DPSDK_EXTRA_A_OPTION_NAME_LEN];	// 操作类型
	int					nParamCount;								// 参数数量
	CUParamInfo_t*		pstuParam;									// 参数信息
};

// 对讲日志
class DPSDK_API TalkLogMsg : public DPSDKCBMessage
{
public:
	TalkLogMsg(void);
	virtual ~TalkLogMsg(void);

public:
	uint32_t					nUserId;							// 用户ID
	dpsdk_talk_log_result_e		nResult;							// 结果
	dpsdk_talk_log_type_e		nType;								// 类型
	dpsdk_talk_log_audio_type_e	nAudioType;							// 音频类型
	uint64_t					nBeginTime;							// 开始时间
	uint64_t					nEndTime;							// 结束时间
	char						szCameraId[DPSDK_CHL_ID_LEN];		// 通道ID
	char						szRemark[DPSDK_EXTRA_A_REMARK_LEN];	// 备注
};

// 分享RtspURL消息
class DPSDK_API ShareRtspUrlMsg : public DPSDKCBMessage
{
public:
	ShareRtspUrlMsg(void);
	virtual ~ShareRtspUrlMsg(void);

public:
	dpsdk_share_rtsp_e	nOper;										// 分享操作
	uint32_t			nSessionId;									// 会话ID
	int					nGrade;										// 用户等级
	char				szSrcCameraId[DPSDK_CHL_ID_LEN];			// 源视频通道
	char				szDstCameraId[DPSDK_CHL_ID_LEN];			// 目的视频通道
	char				szShareCameraId[DPSDK_CHL_ID_LEN];			// 分享视频通道
};

// 通知RtspURL消息
class DPSDK_API NotifyRtspUrlMsg : public DPSDKCBMessage
{
public:
	NotifyRtspUrlMsg(void);
	virtual ~NotifyRtspUrlMsg(void);

public:
	dpsdk_share_rtsp_e	nOper;										// 分享操作
	int					nResponseSeq;								// 应答消息序号
	uint32_t			nShareId;									// 分享ID
	char				szRtspUrl[DPSDK_EXTRA_A_URL_LEN];			// RtspUrl地址
	uint32_t			nToken;										// 令牌
};

// 播放RtspURL消息
class DPSDK_API PlayRtspUrlMsg : public DPSDKCBMessage
{
public:
	PlayRtspUrlMsg(void);
	virtual ~PlayRtspUrlMsg(void);

public:
	int					nResponseSeq;								// 应答消息序号
	uint32_t			nShareId;									// 分享ID
	char				szRtspUrl[DPSDK_EXTRA_A_URL_LEN];			// RtspUrl地址
	uint32_t			nToken;										// 令牌
	fMediaDataCallback	pCBFun;										// 回调接口
	void*				pCBParam;									// 回调参数

	uint32_t			nSessionId;									// 会话ID
};

// 停止RtspURL消息
class DPSDK_API TeardownRtspUrlMsg : public DPSDKCBMessage
{
public:
	TeardownRtspUrlMsg(void);
	virtual ~TeardownRtspUrlMsg(void);

public:
	int					nResponseSeq;								// 应答消息序号
	uint32_t			nShareId;									// 分享ID
};

// 获取菜单导航消息
class DPSDK_API GetMenuToolMsg : public DPSDKCBMessage
{
public:
	GetMenuToolMsg(void);
	virtual ~GetMenuToolMsg(void);

public:
	int				nMenuCount;										// 菜单数量
	int				nNavigateCount;									// 菜单信息
	MenuToolInfo_t*	pstuMenuInfo;									// 导航数量
	MenuToolInfo_t*	pstuNavigateInfo;								// 导航信息
};

// 获取新闻消息
class DPSDK_API GetNewsMsg : public DPSDKCBMessage
{
public:
	GetNewsMsg(void);
	virtual ~GetNewsMsg(void);

public:
	int				nNewsId;										// 新闻ID

	int				nCount;											// 新闻数量
	NewsInfo_t*		pstuNewsInfo;									// 新闻信息
};

// 新闻变更消息
class DPSDK_API NotifyNewsMsg : public DPSDKCBMessage
{
public:
	NotifyNewsMsg(void);
	virtual ~NotifyNewsMsg(void);

public:
	dpsdk_notify_news_e		nType;									// 通知类型
	int						nCount;									// 新闻ID数量
	uint32_t*				pNewsIdList;							// 新闻ID列表
};

//通知客户端导航栏被修改了
class DPSDK_API NotifyModNavigation : public DPSDKCBMessage
{
public: 
	NotifyModNavigation(void);
	virtual ~NotifyModNavigation(void){};
};
//////////////////////////////////////////////////////////////////////////

class DPSDK_API IDPSDKExtra_A : public IDPSDKFuncBase
{
public:
	/** 获取业务组织
	    @param const char* szCoding							节点编码
		@param int nDepthType								类型，参见dpsdk_get_org_depth_type_e
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetOrgTree(const char* szCoding, int nDepthType) = 0;

	/** 获取域信息
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetAllDomainInfo(void) = 0;

	/** 获取视频资源绑定
	    @param uint32_t nUserId								用户ID	
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetUserCameraId(uint32_t nUserId) = 0;

	/** 对讲交互请求
		@param int nGrade									用户等级
		@param const char* szSrcCameraId					源通道ID
		@param const char* szDstCameraId					目的通道ID
		@param const char* szOption							操作类型
		@param const CUParamInfo_t* pstuParam				参数信息
		@param int nParamCount								参数数量
		@return												异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int ToCURequest(int nGrade, const char* szSrcCameraId, const char* szDstCameraId, const char* szOption, const CUParamInfo_t* pstuParam, int nParamCount) = 0;

	/** 对讲交互应答
		@param int nSeq										应答消息序号
		@param const char* szSrcCameraId					源通道ID
		@param const char* szDstCameraId					目的通道ID
		@param const char* szOption							操作类型
		@param const CUParamInfo_t* pstuParam				参数信息
		@param int nParamCount								参数数量
		@return												异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int ToCUResponse(int nSeq, const char* szSrcCameraId, const char* szDstCameraId, const char* szOption, const CUParamInfo_t* pstuParam, int nParamCount) = 0;

	/** 对讲日志
		@param int nUserId									用户ID
		@param int nResult									结果，参见dpsdk_talk_log_result_e
		@param int nType									类型，参见dpsdk_talk_log_type_e
		@param int nAudioType								音频类型，参见dpsdk_talk_log_audio_type_e
		@param uint64_t nBeginTime							开始时间
		@param uint64_t nEndTime							结束时间
		@param const char* szCameraId						通道ID
		@param const char* szRemark							备注
		@return												异步顺序码,用于事件回调时,与应答事件匹配			
	*/
	virtual int TalkLog(int nUserId, int nResult, int nType, int nAudioType, uint64_t nBeginTime, uint64_t nEndTime, const char* szCameraId, const char* szRemark) = 0;

	/** 开始分享RtspURL
		@param int nGrade									用户等级
		@param const char* szSrcCameraId					源通道ID
		@param const char* szDstCameraId					目的通道ID
		@param const char* szShareCameraId					分享通道ID
	    @return												异步顺序码,用于事件回调时,与应答事件匹配	
	*/
	virtual int StartShareRtspUrl(int nGrade, const char* szSrcCameraId, const char* szDstCameraId, const char* szShareCameraId) = 0;

	/** 停止分享RtspURL
		@param int nSessionId								会话ID
		@param int nGrade									用户等级
		@param const char* szSrcCameraId					源通道ID
		@param const char* szDstCameraId					目的通道ID
		@param const char* szShareCameraId					分享通道ID
	    @return												异步顺序码,用于事件回调时,与应答事件匹配	
	*/
	virtual int StopShareRtspUrl(int nSessionId, int nGrade, const char* szSrcCameraId, const char* szDstCameraId, const char* szShareCameraId) = 0;

	/** 播放RtspURL
		@param int nSeq										应答消息序号
		@param int nShareId									分享ID
		@param const char* szRtspUrl						RtspUrl地址
		@param uint32_t nToken								令牌
		@param fMediaDataCallback pCBFun					回调指针
		@param void* pCBParam								回调参数
	    @return												异步顺序码,用于事件回调时,与应答事件匹配	
	*/
	virtual int PlayRtspUrl(int nSeq, uint32_t nShareId, const char* szRtspUrl, uint32_t nToken, fMediaDataCallback pCBFun, void* pCBParam) = 0;

	/** 断开RtspURL
		@param int nSeq										应答消息序号
		@param int nShareId									分享ID
	    @return												异步顺序码,用于事件回调时,与应答事件匹配	
	*/
	virtual int TeardownRtspUrl(int nSeq, uint32_t nShareId) = 0;

	/** 获取菜单导航
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetMenuTool(void) = 0;

	/** 获取新闻
	    @param int nNewsId									新闻ID，-1代表全部	
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetNews(int nNewsId) = 0;

protected:
	virtual ~IDPSDKExtra_A(void){}
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif
