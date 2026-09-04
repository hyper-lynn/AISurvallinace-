/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,报警运营子模块
 *
 * 当前版本：1.0
 * 原作者　：13005
 * 完成日期：
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKALARMBUSINESS_H
#define INCLUDED_DPSDK_DPSDKALARMBUSINESS_H

#include "DPSDK.h"
#include "DPSDKAlarm.h"
#include <string>
#include "DPSDKGeneral.h"   // GeneralJsonTransportMsg

BEGIN_NAMESPACE_DPSDK

//>>> 数据结构定义
// start: add by minjie 2013-11-28
typedef enum
{	// 报警主机布防操作控制类型
	CONTROL_ERROR = 0,			// 控制类型错误
	CONTROL_DEV_ARM,			// 针对设备布防-1
	CONTROL_DEV_DISARM,			// 针对设备撤防-2
	CONTROL_DEV_ARM_HOME,		// 在家布防-3
	CONTROL_DEV_ARM_OUT,		// 外出布防-4
	CONTROL_CHL_BYPASS,			// 针对通道旁路-5
	CONTROL_CHL_DISBYPASS,		// 针对通道取消旁路-6
	CONTROL_CHL_ARM_CLEAR,		// 针对通道消警-7
	CONTROL_DEV_ARM_ALL,		// 全局布防-8（新四路报警主机）
	CONTROL_DEV_ARM_INTIME,		// 立即布防-9（新四路报警主机）
}EnumAlarmhostOperator;
// end: add by minjie

typedef enum
{	// 报警主机状态类型
	ALARMHOSE_STATUS_ERROR = 0,			// 状态类型错误
	ALARMHOSE_STATUS__DEV_ARM,			// 针对设备布防-1
	ALARMHOSE_STATUS__DEV_DISARM,		// 针对设备撤防-2
	ALARMHOSE_STATUS__CHL_BYPASS,		// 针对通道旁路-3
	ALARMHOSE_STATUS__CHL_DISBYPASS,	// 针对通道取消旁路-4
	ALARMHOSE_STATUS__DEV_IN_ARM,		// 针对设备在家布防-5 add by djm 20131219
	ALARMHOSE_STATUS__DEV_OUT_ARM,		// 针对设备外出布防-6 add by djm 20131219
	ALARMHOSE_STATUS__DEV_ALL,			// 全局布防-7（新四路报警主机）
	ALARMHOSE_STATUS__DEV_INTIME,		// 立即布防-8（新四路报警主机）
}alarmhost_status_type_e;

typedef enum
{
	ALARMHOST_STATE_QUERY_REPORT = 0,	// DMS主动查询在线设备回复给CU的状态（客户端登录时上报的布撤防状态）
	ALARMHOST_STATE_DEV_CHANGE_REPORT,	// 中途设备状态变更上报（客户端/demo操作设备以后上报的布撤防状态）
}alarmhost_state_type_e;

// 触发方式
typedef enum
{
	TRIGGER_MODE_UNKNOWN = 0,
	TRIGGER_MODE_NET,            // 网络用户(平台或Web)
	TRIGGER_MODE_KEYBOARD,       // 键盘
	TRIGGER_MODE_REMOTECONTROL,  // 遥控器
}trigger_mode_e;

// 视频报警主机报警查询信息
typedef struct DPSDK_API AlarmBQueryInfo
{
	char					cameraID[DPSDK_CHL_ID_LEN];		// 通道ID
	int64_t					startTime;						// 开始时间
	int64_t					endTime;						// 结束时间
	uint32_t				dealWith;						// 处理意见类型（参见dpsdk_alarm_dealwith_e枚举）
	dpsdk_alarm_source_e	source;							// 报警来源。(参见dpsdk_alarm_source_e枚举)
	dpsdk_alarm_type_e		alarmType;						// 报警类型。(参见dpsdk_alarm_type_e枚举)
	uint32_t				deviceType;						// 设备类型。1 编码器, 2 报警主机, 3 控制器, 4 IVS-B, 5 IVS-V
	int		                channelAlarmType;			    // 报警主机报警查询时查询类型.add by djm 20131028 该类型可能为用户自定义
	//Start extended 
	uint32_t				firstNum;						// 开始序号 
	uint32_t				queryCount;						// 查询数量 
	char					planName[DPSDK_PLAN_NAME_LEN];	// 计划名称（IVS-V）
	uint32_t				nFlag;							// 标识一般查询与登入当日查询  -1为当日、0为一般查询
	std::string				m_devId;		                // 设备ID(ID之间用逗号分隔)
	std::string				m_alarmType;					// 报警类型。(各类型之间用逗号分隔)
	std::string				m_channelAlarmType;				// 报警主机报警查询时查询类型.(各类型之间用逗号分隔)
	int						m_nAlarnLevel;					// 报警等级
	//End extended 
	//报警运营需求，支持多个 
	std::string				m_strHandleUser_n;				// 报警处理人，支持多个，用','分隔 
	std::string				m_strDealState_n;				// 处理状态，支持多个，用','分隔 
	std::string				m_strLevel_n;					// 报警级别，支持多个，用','分隔 
	std::string				m_strChannelId_n;				// 支持多个通道id的查询 
	int						m_nOrderType;					// 0表示按时间升序，1表示按时间倒序
	std::string				handleMode_n;					//处理方式，支持多个，用','分隔


	AlarmBQueryInfo()
	{
		memset(cameraID, 0, sizeof(cameraID));
		startTime = 0;
		endTime = 0;
		dealWith = 0;						// 处理状态
		source = ALARM_SOURCE_ALL;
		alarmType = ALARM_TYPE_Unknown;
		deviceType = 2;						// 设备类型。1 编码器, 2 报警主机, 3 控制器, 4 IVS-B, 5 IVS-V
		channelAlarmType = -1;				// add by djm 20131028 报警运营平台新加 通道报警类型

		//Start extended 
		firstNum = 1;
		queryCount = 0;
		memset(planName, 0, sizeof(planName));
		nFlag = static_cast<uint32_t>(-1);
		m_devId = "";
		m_alarmType = "";
		m_channelAlarmType = "";
		m_nAlarnLevel = -1;
		//End extended 
		m_strHandleUser_n = "";
		m_strDealState_n = "";
		m_strLevel_n = "";
		m_strChannelId_n = "";
		m_nOrderType = -1;
		handleMode_n = "";
	};
}AlarmBQueryInfo_t;

// 布撤防客户查询
typedef struct DPSDK_API DefendCustomInfo
{
	int		_defendFlag;								// 1-布防、2-撤防、3-旁路
	char	_orgCode[DPSDK_ALB_USERID_LEN];				// 地区编号(可选）
	char	_customerCode[DPSDK_ALB_USERID_LEN];		// 用户编号(可选）
	int		_customerType;								// 客户类型(可选）
	int64_t	_beginTime;									// 查询开始时间(可选）
	int64_t	_endTime;									// 查询结束时间(可选）
	// 分页
	int		_beginIndex;								// 开始笔数1开始
	int		_endIndex;									// 结束笔数
	bool	_exportFlag;								// 导出标志

	DefendCustomInfo()
	{
		_defendFlag = 1;
		memset(_orgCode, 0, sizeof(_orgCode));
		memset(_customerCode, 0, sizeof(_customerCode));
		_customerType = 1;
		_beginTime	= 0;
		_endTime	= 0;
		_beginIndex = 1;
		_endIndex   = 100;
		_exportFlag = false;
	};
}DefendCustomInfo_t;

// 在线离线客户查询
typedef struct DPSDK_API OnlineCustomInfo
{
	int		_onlineFlag;								// 0-离线 1-在线 2-全部
	char	_orgCode[DPSDK_ALB_USERID_LEN];				// 地区编号(可选）
	char	_customerCode[DPSDK_ALB_USERID_LEN];		// 用户编号(可选）
	int		_customerType;								// 客户类型(可选）
	int64_t	_beginTime;									// 查询开始时间(可选）
	int64_t	_endTime;									// 查询结束时间(可选）
	// 分页
	int		_beginIndex;								// 开始笔数1开始
	int		_endIndex;									// 结束笔数
	bool	_exportFlag;								// 导出标志

	OnlineCustomInfo()
	{
		_onlineFlag = 2;
		memset(_orgCode, 0, sizeof(_orgCode));
		memset(_customerCode, 0, sizeof(_customerCode));
		_customerType = 1;
		_beginTime = 0;
		_endTime   = 0;
		_beginIndex = 1;
		_endIndex   = 100;
		_exportFlag = false;
	};
}OnlineCustomInfo_t;

typedef struct DPSDK_API tagSetPhoneSubscribeAlarm
{
	int	        iUserId;				//用户ID
	char        szPhoneId[256];			//手机ID,手机推送的标志
	int         iAppId;					//应用程序编号
	char        szPush_type[64];		//手机类型
	int         iIs_subscribe;			//是否订阅; 1-订阅, 0-取消订阅
	char        szLanguage[32];			//语言
	char        szTimefmt[32];			//时间格式化

	int         iDbOper;				//db操作类型. 1-插入, 2-更新, 3-查询
	
	tagSetPhoneSubscribeAlarm()
	{
		iUserId = -1;
		iAppId = -1;
		iIs_subscribe = -1;
		memset(szPhoneId, 0, sizeof(szPhoneId));
		memset(szPush_type, 0, sizeof(szPush_type));
		memset(szLanguage, 0, sizeof(szLanguage));
		memset(szTimefmt, 0, sizeof(szTimefmt));
		iDbOper = 0;
	};

}set_phone_subscribe_alarm_t;

// start: 消息定义
// 存放公用数据
class AlarmBusinessBaseMsg : public DPSDKCBMessage
{
public:
	AlarmBusinessBaseMsg( int cmd = DPSDK_CMD_UNKNOWN,int msgType = DPSDK_MSG_RESPONSE);
	virtual ~AlarmBusinessBaseMsg(){}

	char	serverId[SERVER_ID_LEN];		//服务ID
	char	cameraId[DPSDK_CHL_ID_LEN];		//摄像头ID
};

// 报警类型查询
class ChnAlarmTypeQueryMsg : public DPSDKCBMessage
{
public:
	ChnAlarmTypeQueryMsg()
	{
		m_cmd = DPSDK_CMD_CHN_ALARMTYPE_QUERY;
		m_chnAlarmTypeStream.clear();
	}
	virtual ~ChnAlarmTypeQueryMsg(){}

public:
	//request

	//response
	std::string		m_chnAlarmTypeStream;	//base64流

};

// 报警主机控制 add by minjie 2013-10-15
class ControlAlarmHostMsg: public AlarmBusinessBaseMsg
{
public:
	ControlAlarmHostMsg();
	virtual ~ControlAlarmHostMsg(){}
public:
	//request
	char					m_deviceId[DPSDK_DEV_ID_LEN];	// 设备ID			
	int						m_channel;						// 通道号(针对设备操作，通道号设置为-1)			
	EnumAlarmhostOperator	m_controlType;					// 控制类型	

	//response
	int						m_nRet;							// 布撤防的返回结果
};


// DMS 报警主机布防、撤防、旁路与取消旁路状态上报 add by zxb 12-4-2013
class DPSDK_API ReportAlarmHostStatusMsg : public DPSDKCBMessage
{
public:
	ReportAlarmHostStatusMsg(void);
	virtual ~ReportAlarmHostStatusMsg(void){}

public:
	char						m_deviceId[DPSDK_CHL_ID_LEN];	// 设备ID
	int							m_nChannelNo;					// 通道号
	alarmhost_status_type_e		m_nStatus;						// 状态 1-布防、2-撤防、3-旁路、4-取消旁路、5-在家布防、6、外出布防
																// 7-全局布防、8-立即布防
	int64_t						time;
	trigger_mode_e				m_triggerMode;					//触发方式
	alarmhost_state_type_e		m_nState;						// 0 DMS主动查询在线设备回复给CU的状态; 1 中途设备状态变更上报
};


// 客户资料(包括联系方式)
class CustomerInfoMsg: public DPSDKCBMessage
{
public:
	CustomerInfoMsg()
	{
		m_cmd = DPSDK_CMD_CUSTOMERINFO_QUERY;
		memset(m_customerId, 0, sizeof(m_customerId));
		m_customInfoXml = "";
		m_contactInfoXml = "";
		m_sender = 0;
	}
	virtual ~CustomerInfoMsg(){}

public:
	//request
	char		m_customerId[DPSDK_ALB_USERID_LEN];		// 用户编号
	int			m_sender;								// 0登陆发起

	//response
	std::string	 m_customInfoXml;						// xml
	std::string	 m_contactInfoXml;						// xml
};

// 客户资料修改通知(联系方式增加删除视为修改操作)
class CustomerInfoNotifyMsg: public DPSDKCBMessage
{
public:
	CustomerInfoNotifyMsg()
	{
		m_cmd = DPSDK_CMD_CUSTOMERINFO_NOTIFY;
		memset(m_id, 0, sizeof(m_id));
		m_customInfoXml  = "";
		m_contactInfoXml = "";
	}
	virtual ~CustomerInfoNotifyMsg(){}

public:
	//response
	char			m_id[DPSDK_ALB_ID_LEN];		// 用户(客户)表数据库ID(删除返回)
	std::string		m_customInfoXml;			// xml(增加修改返回)
	std::string		m_contactInfoXml;			// xml(增加修改返回)
};

// 视频报警主机
class VideoAlarmHostMsg: public DPSDKCBMessage
{
public:
	VideoAlarmHostMsg()
	{
		m_cmd = DPSDK_CMD_VIDEOALARMHOST_QUERY;
		memset(m_id, 0, sizeof(m_id));
		memset(m_devId, 0, sizeof(m_devId));
		// dsl::DStr::strcpy_x(m_id, 3, "-1");
		memcpy( m_id, "-1", 3 );
		m_devXml = "";
		m_sender = 0;
	}
	virtual ~VideoAlarmHostMsg(){}
public:
	//request
	char		m_id[DPSDK_ALB_ID_LEN];			// 设备表数据库ID
	char		m_devId[DPSDK_DEV_ID_LEN];		// 设备ID
	int			m_sender;

	//response
	std::string	m_devXml;						// xml
};

// 查询报警总条数 
class VideoAlarmCountMsg: public DPSDKCBMessage 
{ 
public: 
	VideoAlarmCountMsg() 
	{ 
		m_cmd = DPSDK_CMD_VIDEOALARMCOUNT_QUERY; 
		//AlarmQueryInfo_t初始化
		memset(queryInfo.cameraID, 0, sizeof(queryInfo.cameraID));
		queryInfo.startTime = 0;
		queryInfo.endTime = 0;
		queryInfo.dealWith = 0;					// ALARM_DEALWITH_UNPROCESSED处理状态
		queryInfo.source = ALARM_SOURCE_ALL;
		queryInfo.alarmType = ALARM_TYPE_Unknown;
		queryInfo.deviceType = 2;					// 设备类型。1 编码器, 2 报警主机, 3 控制器, 4 IVS-B, 5 IVS-V
		queryInfo.channelAlarmType = -1;			// add by djm 20131028 报警运营平台新加 通道报警类型
		//end
		firstNum = 0;
		queryCount = 0;
		memset(planName, 0, sizeof(planName));
		//nFlag = -1;
		m_devId = "";
		m_alarmType = "";
		m_channelAlarmType = "";
		m_nAlarnLevel = -1;

		m_strHandleUser = "";
		m_strDealState = "";
		m_strLevel = "";
		m_strChannelId = "";
		m_nOrderType = -1;

		count = 0;
		handleMode_n = "";

	} 
	virtual ~VideoAlarmCountMsg(){} 
public: 
	// request 
	AlarmQueryInfo_t	queryInfo;						// 报警查询信息 
	uint32_t			firstNum;						// 开始序号 
	uint32_t			queryCount;						// 查询数量 
	char				planName[DPSDK_PLAN_NAME_LEN];	// 计划名称（IVS-V） 

	//uint32_t			nFlag;							// 标识一般查询与登入当日查询  -1为当日、0为一般查询
	std::string			m_devId;		                // 设备ID(ID之间用逗号分隔)
	std::string			m_alarmType;					// 报警类型。(各类型之间用逗号分隔)
	std::string			m_channelAlarmType;				// 报警主机报警查询时查询类型.(各类型之间用逗号分隔)
	int					m_nAlarnLevel;					// 报警等级

	//报警运营需求，支持多个 
	std::string			m_strHandleUser;				// 报警处理人，支持多个，用','分隔 
	std::string			m_strDealState;					// 处理状态，支持多个，用','分隔 
	std::string			m_strLevel;						// 报警级别，支持多个，用','分隔 
	std::string			m_strChannelId;					// 支持多个通道id的查询 
	int					m_nOrderType;					// 0表示按时间升序，1表示按时间倒序
	std::string			handleMode_n;					//处理方式，支持多个，用','分隔

	// response 
	uint32_t			count;							// 返回报警查询总条数 
}; 

// 查询当天报警 
class TodayVideoAlarmMsg: public DPSDKCBMessage 
{ 
public: 
	TodayVideoAlarmMsg() 
	{ 
		m_cmd = DPSDK_CMD_VIDEOALARM_QUERY; 
		//AlarmQueryInfo_t初始化
		memset(queryInfo.cameraID, 0, sizeof(queryInfo.cameraID));
		queryInfo.startTime = 0;
		queryInfo.endTime = 0;
		queryInfo.dealWith = 0;					// ALARM_DEALWITH_UNPROCESSED处理状态
		queryInfo.source = ALARM_SOURCE_ALL;
		queryInfo.alarmType = ALARM_TYPE_Unknown;
		queryInfo.deviceType = 2;					// 设备类型。1 编码器, 2 报警主机, 3 控制器, 4 IVS-B, 5 IVS-V
		queryInfo.channelAlarmType = -1;			// add by djm 20131028 报警运营平台新加 通道报警类型
		//end
		firstNum = 0;
		queryCount = 0;
		memset(planName, 0, sizeof(planName));
		nFlag = static_cast<uint32_t>(-1);
		m_devId = "";
		m_alarmType = "";
		m_channelAlarmType = "";
		m_nAlarnLevel = -1;

		m_strHandleUser = "";
		m_strDealState = "";
		m_strLevel = "";
		m_strChannelId = "";
		m_nOrderType = -1;

		infoCount = 0;
		pAlarmHostInfo = NULL;
		handleMode_n = "";

	} 
	virtual ~TodayVideoAlarmMsg(){} 
public: 
	// request 
	AlarmQueryInfo_t	queryInfo;						// 报警查询信息 
	uint32_t			firstNum;						// 开始序号 
	uint32_t			queryCount;						// 查询数量 
	char				planName[DPSDK_PLAN_NAME_LEN];	// 计划名称（IVS-V） 
	
	uint32_t			nFlag;							// 标识一般查询与登入当日查询  -1为当日、0为一般查询、1为导出查询
	std::string			m_devId;		                // 设备ID(ID之间用逗号分隔)
	std::string			m_alarmType;					// 报警类型。(各类型之间用逗号分隔)
	std::string			m_channelAlarmType;				// 报警主机报警查询时查询类型.(各类型之间用逗号分隔)
	int					m_nAlarnLevel;					// 报警等级
	//报警运营需求，支持多个 
	std::string			m_strHandleUser;				// 报警处理人，支持多个，用','分隔 
	std::string			m_strDealState;					// 处理状态，支持多个，用','分隔 
	std::string			m_strLevel;						// 报警级别，支持多个，用','分隔 
	std::string			m_strChannelId;					// 支持多个通道id的查询 
	int					m_nOrderType;					// 0表示按时间升序，1表示按时间倒序
	std::string			handleMode_n;					//处理方式，支持多个，用','分隔

	// response 
	uint32_t			infoCount;						// 返回实际报警条数 
	ADSAlarmHostInfo_t *pAlarmHostInfo;					// 指向报警主机报警数据add by djm 20131031 
}; 

// 查询当天报警 新增字段add by 21548
class TodayVideoAlarmMsgNew: public DPSDKCBMessage 
{ 
public: 
	TodayVideoAlarmMsgNew() 
	{ 
		m_cmd = DPSDK_CMD_VIDEOALARM_QUERY_NEW; 
		//AlarmQueryInfo_t初始化
		memset(queryInfo.cameraID, 0, sizeof(queryInfo.cameraID));
		queryInfo.startTime = 0;
		queryInfo.endTime = 0;
		queryInfo.dealWith = 0;						//ALARM_DEALWITH_UNPROCESSED处理状态
		queryInfo.source = ALARM_SOURCE_ALL;
		queryInfo.alarmType = ALARM_TYPE_Unknown;
		queryInfo.deviceType = 2;					// 设备类型。1 编码器, 2 报警主机, 3 控制器, 4 IVS-B, 5 IVS-V
		queryInfo.channelAlarmType = -1;			//add by djm 20131028 报警运营平台新加 通道报警类型
		//end
		firstNum = 0;
		queryCount = 0;
		memset(planName, 0, sizeof(planName));
		nFlag = static_cast<uint32_t>(-1);
		m_devId = "";
		m_alarmType = "";
		m_channelAlarmType = "";
		m_nAlarnLevel = -1;
		m_sender = 0;
		m_orderType = 0;

		m_strHandleUser = "";
		m_strDealState = "";
		m_strLevel = "";
		m_strChannelId = "";
		m_nOrderType = -1;

		infoCount = 0;
		pAlarmHostInfo = NULL;
		m_nStructType = -1;
		handleMode_n = "";

	} 
	virtual ~TodayVideoAlarmMsgNew(){} 
public: 
	// request 
	AlarmQueryInfo_t	queryInfo;				// 报警查询信息 
	uint32_t			firstNum;				// 开始序号 
	uint32_t			queryCount;				// 查询数量 
	char				planName[DPSDK_PLAN_NAME_LEN];		// 计划名称（IVS-V） 

	uint32_t			nFlag;							// 标识一般查询与登入当日查询  -1为当日、0为一般查询、1为导出查询
	std::string			m_devId;		                // 设备ID(ID之间用逗号分隔)
	std::string			m_alarmType;					// 报警类型。(各类型之间用逗号分隔)
	std::string			m_channelAlarmType;				// 报警主机报警查询时查询类型.(各类型之间用逗号分隔)
	int					m_nAlarnLevel;					// 报警等级
	int		m_sender;  //add by zhang_yunxia 20140617
	int		m_orderType;
	//报警运营需求，支持多个 
	std::string			m_strHandleUser;				// 报警处理人，支持多个，用','分隔 
	std::string			m_strDealState;					// 处理状态，支持多个，用','分隔 
	std::string			m_strLevel;						// 报警级别，支持多个，用','分隔 
	std::string			m_strChannelId;					// 支持多个通道id的查询 
	int					m_nOrderType;					// 0表示按时间升序，1表示按时间倒序
	int					m_nStructType;					// 报警运营查询报警返回的结构体类型，默认为0表示旧的结构体ADSAlarmHostInfo_t，1表示新的结构体ADSAlarmHostInfo_t_New
	std::string			handleMode_n;					//处理方式，支持多个，用','分隔
	
	// response 
	uint32_t		infoCount;							// 返回实际报警条数 
	ADSAlarmHostInfo_t_New *pAlarmHostInfo;				// 指向报警主机报警数据有新增字段
}; 


class DefendCustomerInfoMsg: public DPSDKCBMessage
{
public:
	DefendCustomerInfoMsg()
	{
		m_cmd = DPSDK_CMD_DEFENDCUSTOMER_QUERY;
		memset(&m_queryInfo, 0, sizeof(m_queryInfo));
		m_customXml = "";
	}
	virtual ~DefendCustomerInfoMsg(){}
public:
	//request
	DefendCustomInfo_t	m_queryInfo;
	//response
	std::string			m_customXml;  // xml
};

class OnlineCustomerInfoMsg: public DPSDKCBMessage
{
public:
	OnlineCustomerInfoMsg()
	{
		m_cmd = DPSDK_CMD_ONLINECUSTOMER_QUERY;
		memset(&m_queryInfo, 0, sizeof(m_queryInfo));
		m_customXml = "";
	}
	virtual ~OnlineCustomerInfoMsg(){}
public:
	//request
	OnlineCustomInfo_t	m_queryInfo;
	//response
	std::string			m_customXml;  // xml
};

//保险-服务到期通知消息
class ServiceTimeOutNotifyMsg: public DPSDKCBMessage
{
public:
	ServiceTimeOutNotifyMsg()
	{
		m_cmd = DPSDK_CMD_SERVICETIMEOUT_NOTIFY;
		memset(m_Userid, 0, sizeof(m_Userid));
		memset(m_Devid, 0, sizeof(m_Devid));
		m_flag = -1;
		m_nDay = -1;
	}
	virtual ~ServiceTimeOutNotifyMsg(){}

public:
	//response
	char		m_Userid[DPSDK_ALB_USERID_LEN];	// 用户(客户)ID
	char		m_Devid[DPSDK_DEV_ID_LEN];		// 设备ID
	int64_t		m_flag;							// 保险还是服务到期标识位  0-保险、1-服务
	int64_t		m_nDay;							// 到期天数
};

class GetAlarmReDealTimeMsg: public DPSDKCBMessage
{
public:
	GetAlarmReDealTimeMsg()
	{
		m_cmd = DPSDK_CMD_QUERY_ALARMREDEAL_TIME;
		m_timespace = 30;
	}
	virtual ~GetAlarmReDealTimeMsg(){}
public:
	//response
	int			m_timespace;	//min
};

#define DPSDK_APPALARM_MSG_LEN 1024 * 2
class SmSSendMessageMsg: public DPSDKCBMessage
{
public:
	SmSSendMessageMsg();
	virtual ~SmSSendMessageMsg();
public:
	char*		m_AppSmSXml;

};

class OnlineUsersByRoleMsg : public GeneralJsonTransportMsg
{
public:
	OnlineUsersByRoleMsg()
	{
		m_cmd = DPSDK_CMD_QUERY_ONLNEUSER_BY_ROLE;
		memset(m_pUserID,0,sizeof(m_pUserID));
	}
	virtual ~OnlineUsersByRoleMsg(){};

public:
	char	m_pUserID[DPSDK_CHAR_LEN_32];	//用户ID
};
class WriteCaseInfoMsg : public GeneralJsonTransportMsg
{
public:
	WriteCaseInfoMsg()
	{
		m_cmd = DPSDK_CMD_WRITE_CASE_INFO;
		memset(m_pCaseObject,0,sizeof(m_pCaseObject));
		memset(m_pCaseName,0,sizeof(m_pCaseName));
		memset(m_pCaseDesc,0,sizeof(m_pCaseDesc));
		memset(m_pCaseTime,0,sizeof(m_pCaseTime));
		m_nCaseLevel = -1;
		m_nCaseType = -1;
		m_bCaseClosed = false;
	}
	virtual ~WriteCaseInfoMsg(){};
public:
	char	m_pCaseObject[DPSDK_CHAR_LEN_32];			//案件对象
	char	m_pCaseName[DPSDK_CHAR_LEN_32];				//案件名称
	char	m_pCaseDesc[DPSDK_CHAR_LEN_128];			//简要案情
	char	m_pCaseTime[DPSDK_CHAR_LEN_32];				//案发时间
	int		m_nCaseLevel;								//案件等级
	int		m_nCaseType;								//案件类型	
	bool	m_bCaseClosed;								//是否结案

};

class Get110OnlineUserRole : public GeneralJsonTransportMsg
{
public:
	Get110OnlineUserRole()
	{
		m_cmd = DPSDK_CMD_QUERY_110_ONLINEUSER_ROLE;
		trantype = GENERALJSON_TRAN_REQUEST;
	}
	virtual ~Get110OnlineUserRole(){};

};

class GetAllUsers : public GeneralJsonTransportMsg
{
public:
	GetAllUsers()
	{
		m_cmd = DPSDK_CMD_QUERY_ALL_USERS;
		trantype = GENERALJSON_TRAN_REQUEST;
	}
	virtual ~GetAllUsers(){};

};
// 新增/更新值班日志记录
class UploadLogofOndutyMsg : public GeneralJsonTransportMsg
{
public:
	UploadLogofOndutyMsg()
	{
		m_cmd = DPSDK_CMD_UPLOAD_LOG_ONDUTY;
		trantype = GENERALJSON_TRAN_REQUEST;
		memset(m_szDBID,0,sizeof(m_szDBID));
		m_nSubmiterID = -1;
		memset(m_pLogInfo,0,sizeof(m_pLogInfo));
		m_nSubmitTime = 0;
		m_nOperType = static_cast<uint32_t>(-1);
		m_nDealUserID = 0;							// 处理人用户ID
		m_nDealTime = 0;							// 处理时间
		m_nDealState = -1;							// 处理状态  1处理中 2已处理
	}
	virtual ~UploadLogofOndutyMsg(){};
public:
	char		m_szDBID[DPSDK_CHAR_LEN_32];			// 数据库ID
	int			m_nSubmiterID;							// 值班人用户ID
	char		m_pLogInfo[DPSDK_CHAR_LEN_1024];		// 日志信息
	uint64_t	m_nSubmitTime;							// 提交时间
	uint32_t	m_nOperType;							// 操作类型：1签入 2签出 0上传日志 3更新日志
	uint32_t	m_nDealUserID;							// 处理人用户ID
	uint64_t	m_nDealTime;							// 处理时间
	int			m_nDealState;							// 处理状态  1处理中 2已处理
};

// 查询值班人值班信息
class QuerryLogInofOndutyMsg : public GeneralJsonTransportMsg
{
public:
	QuerryLogInofOndutyMsg()
	{
		m_cmd = DPSDK_CMD_UPLOAD_LOG_QUERRY;
		trantype = GENERALJSON_TRAN_REQUEST;		
		m_nUserID = 0;			// 值班人用户ID		
	}
	virtual ~QuerryLogInofOndutyMsg(){};
public:	
	uint32_t	m_nUserID;		// 值班人用户ID	
};

class QueryUserDutyLoginInfoMsg : public GeneralJsonTransportMsg
{
public:
	QueryUserDutyLoginInfoMsg()	
	{
		m_cmd = DPSDK_CMD_QUERY_USER_DUTY_LOGIN;
		trantype = GENERALJSON_TRAN_REQUEST;
	}
	virtual ~QueryUserDutyLoginInfoMsg(){};
};

class SetPhoneSubscribeMsg: public DPSDKCBMessage
{
public:
	SetPhoneSubscribeMsg()
	{
		m_cmd = DPSDK_CMD_PHONE_SUBSCRIBE_ALARM;
		memset(&m_PhoneParam, 0, sizeof(set_phone_subscribe_alarm_t));
	}
	virtual ~SetPhoneSubscribeMsg(){}
public:

	set_phone_subscribe_alarm_t			m_PhoneParam;	//参数
};


/////////////////////////////重点区域进出记录-START/////////////////////////////////////////////
// 新增/更新
class UploadSensitiveRecMsg : public GeneralJsonTransportMsg
{
public:
	UploadSensitiveRecMsg()
	{
		m_cmd = DPSDK_CMD_SENSITIVE_REC_UPLOAD;
		trantype = GENERALJSON_TRAN_REQUEST;
		nDBID = 0;
		nRecDate = 0;
		nRecPeople = 0;
		memset(szRegionName,0,sizeof(szRegionName));
		memset(szOrgCode,0,sizeof(szOrgCode));
		nInvadeDate = 0;
		memset(szCompanyName,0,sizeof(szCompanyName));
		memset(szExcuse,0,sizeof(szExcuse));
		nLeaveDate = 0;
		nOptType = -1;
	}
	virtual ~UploadSensitiveRecMsg(){};
public:
	int			nDBID;								// 数据库记录ID,新增不用填写,更新必填
	int64_t		nRecDate;							// 提交日期
	int			nRecPeople;							// 提交人用户ID
	char		szRegionName[DPSDK_CHAR_LEN_128];	// 区域名称(网点/客户/组织结构)
	char		szOrgCode[DPSDK_ORG_CODE_LEN];		// 区域所在组织结构
	int64_t		nInvadeDate;						// 进入时间
	char		szCompanyName[DPSDK_CHAR_LEN_64];	// 进入人员所属单位
	char		szExcuse[DPSDK_CHAR_LEN_32];		// 进入事由
	int64_t		nLeaveDate;							// 离开时间
	int			nOptType;							// 操作类型 0 新增,1 更新
};

// 查询
class QuerrySensitiveRecMsg : public GeneralJsonTransportMsg
{
public:
	QuerrySensitiveRecMsg()
	{
		m_cmd = DPSDK_CMD_SENSITIVE_REC_QUERRY;
		trantype = GENERALJSON_TRAN_REQUEST;
		nUserID = 0;			
	}
	virtual ~QuerrySensitiveRecMsg(){};
public:	
	uint32_t	nUserID;		// 用户ID	
};
/////////////////////////////重点区域进出记录-END/////////////////////////////////////////////

// end: 消息定义

class DPSDK_API IDPSDKAlarmBusiness : public IDPSDKFuncBase
{
public:
	// 报警类型查询
	virtual int QueryChnAlarmType() = 0;

	// 报警主机控制,针对设备操作，通道号设置为-1 add by minjie 2013-11-28
	virtual	int ControlAlarmHost(std::string& deviceId, int channelId = -1, EnumAlarmhostOperator controlType = CONTROL_ERROR) = 0;

	// 查询客户资料(联系方式)
	// 默认参数表示查询所有
	virtual int QueryCustomerInfo(std::string customId = "", int sender = 0) = 0;

	// 查询视频报警主机
	// 默认参数表示查询所有sender 0登陆模块
	virtual int QueryVideoAlarmHost(std::string devId = "", int sender = 0) = 0;

	/** 查询当天报警.
		@return												异步顺序码,用于事件回调时,与应答事件匹配
		@remark 走新协议 CFLCUQueryAlarmForAlarmBRequest
	*/
	virtual int QueryTodayAlarm() = 0;

	/** 查询报警.
		@param int nQueryType								查询类型，0是老流程，1是新流程，新结构体增加字段。
		@return												异步顺序码,用于事件回调时,与应答事件匹配
		@remark
	*/
	virtual int QueryVideoAlarmHostAlarm(AlarmBQueryInfo_t& queryInfo, int nQueryType=0) = 0;

	/** 查询报警-导出到excel
		@param int nQueryType								查询类型，0是老流程，1是新流程，新结构体增加字段。
		@return												异步顺序码,用于事件回调时,与应答事件匹配
		@remark
	*/
	virtual int QueryVideoAlarmHostAlarmExport(AlarmBQueryInfo_t& queryInfo, int nQueryType=0) = 0;

	/** 查询报警总数.
		@return												异步顺序码,用于事件回调时,与应答事件匹配
		@remark
	*/
	virtual int QueryVideoAlarmHostAlarmCount(AlarmBQueryInfo_t& queryInfo) = 0;

	/** 查询布撤防客户
		@return												异步顺序码,用于事件回调时,与应答事件匹配
		@remark
	*/
	virtual int QueryDefendCustom(DefendCustomInfo_t& queryInfo) = 0;

	/** 查询在线离线客户
		@return												异步顺序码,用于事件回调时,与应答事件匹配
		@remark
		*/
	virtual int QueryOnlineCustom(OnlineCustomInfo_t& queryInfo) = 0;

	/**	获取二次报警处理时间间隔**/
	virtual int QueryAlarmReDealTime(void) = 0;

	/**	短信发送**/
	virtual int SendSMSMessage(const char* pSmsXml) = 0;

	/** 查询同角色在线用户 
		@return												// 异步顺序码,用于事件回调时,与应答事件匹配
		@remark 
	**/
	virtual int QueryOnlineUserByRole() = 0;

	/** 立案信息写入 
		@param const char* strCaseObject					// 案件对象，案件发生的地方
		@param int nCaseLevel								// 案件等级 等级1-4,1最高
		@param int nCaseType								// 案件类型
		@param const char* strCaseTime						// 案发时间 yyyy-mm-dd hh:mm:ss
		@param const char* strCaseName						// 案件名称
		@param const char* strCaseDesc						// 简要案情
		@param bool bCaseClosed								// 是否结案 true: 结案 false:未结案
		@return												// 异步顺序码,用于事件回调时,与应答事件匹配
		@remark 
	**/
	virtual int WriteCaseInfo(	const char* strCaseObject, 
								int nCaseLevel, 
								int nCaseType, 
								const char* strCaseTime, 
								const char* strCaseName, 
								const char* strCaseDesc, 
								bool bCaseClosed ) = 0;

	/** 查询110用户列表
		@return												// 异步顺序码,用于事件回调时,与应答事件匹配
		@remark 
	**/
	virtual int Get110OnlineRoleUsers() = 0;

	/** 查询所有用户列表
		@return												// 异步顺序码,用于事件回调时,与应答事件匹配
		@remark 
	**/
	virtual int QueryAllUsers() = 0;
	
	/** 上传值班日志
		@param const char *strDBID		// 数据库记录ID,新增不用填写,更新必填
		@param int nSubmitUserID		// 提交人用户ID
		@param const char* strLogInfo	// 事件内容
		@param int64_t nSubmitTime		// 提交时间
		@param int nOperType			// 操作类型：1签入 2签出 0上传日志 3更新记录
		@param int nDealUserID			// 处理人用户ID
		@param uint64_t nDealTime		// 处理时间
		@param uint32 nDealState		// 处理状态
		@return												// 异步顺序码,用于事件回调时,与应答事件匹配
		@remark 
	**/
	virtual int UploadLogofOnDuty(const char *strDBID, int nSubmitUserID, const char* strLogInfo, int64_t nSubmitTime, int nOperType,
		int nDealUserID,uint64_t nDealTime,int nDealState) = 0;

	/** 查询交接班日志信息
		@param const char* strName							// 值班人用户ID
		@return												// 异步顺序码,用于事件回调时,与应答事件匹配
		@remark 
	**/
	virtual int QuerryLogInofOnDuty(int nUserID) = 0;

	/** 查询用户签入or签出
		@return												// 异步顺序码,用于事件回调时,与应答事件匹配
		@remark 
	**/
	virtual int QueryUserDutyLoginInfo() = 0;

	/** 手机订阅报警
		@param	phoneParam									// 手机相关参数
		@return												// 异步顺序码,用于事件回调时,与应答事件匹配
		@remark 
	**/
	virtual int SetPhoneSubscribeAlarm(set_phone_subscribe_alarm_t& phoneParam) = 0;

	/////////////////////////////重点区域进出记录-START/////////////////////////////////////////////
	/** 上传重点区域进出记录
		@param int			nDBID			// 数据库记录ID,新增不用填写,更新必填
		@param int64_t		nRecDate		// 提交日期
		@param int			nRecPeople		// 提交人用户ID
		@param const char	*szRegionName	// 区域名称(网点/客户/组织结构)
		@param const char	*szOrgCode		// 区域所在组织结构
		@param int			nInvadeDate		// 进入时间
		@param const char	*szCompanyName	// 进入人员所属单位
		@param const char	*szExcuse		// 进入事由
		@param int64_t		nLeaveDate		// 离开时间
		@param int			nOptType;		// 操作类型 0 新增,1 更新
		@return	int							// 异步顺序码,用于事件回调时,与应答事件匹配
		@remark 
	**/
	virtual int UploadSensitiveRec(int nDBID, int64_t nRecDate, int nRecPeople, const char *szRegionName, const char *szOrgCode,uint64_t nInvadeDate,
		const char *szCompanyName,const char *szExcuse,uint64_t nLeaveDate,int nOptType) = 0;

	/** 查询值班时间内的重点区域进出记录
		@param const char* strName							// 值班人用户ID
		@return												// 异步顺序码,用于事件回调时,与应答事件匹配
		@remark 
	**/
	virtual int QuerrySensitiveRec(int nUserID) = 0;
	/////////////////////////////重点区域进出记录-END///////////////////////////////////////////////

protected:
	virtual ~IDPSDKAlarmBusiness(void){}

};

//////////////////////////////////////////////////////////////////////////
END_NAMESPACE_DPSDK

#endif
