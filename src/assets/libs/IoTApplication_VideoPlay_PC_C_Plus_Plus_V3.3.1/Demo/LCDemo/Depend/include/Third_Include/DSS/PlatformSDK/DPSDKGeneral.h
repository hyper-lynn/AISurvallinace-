/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,用户配置子模块
 *
 * 当前版本：1.0
 * 原作者　：俞露
 * 完成日期：2012年4月20日
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKGENERAL_H
#define INCLUDED_DPSDK_DPSDKGENERAL_H

#include "DPSDK.h"
#include <jsondsl/json.h>
#include <time.h>
#include <vector>
#include <list>
#include <string>


namespace DGP
{
	class DGroupParser;
}

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

#define MSG_LENGTH					4*1024					// 
#define DEVINFO_SEPARATE			","						// 
#define DEVCODE_SEPARATE			"$"						// 
//////////////////////////////////////////////////////////////////////////
// 权限宏定义 
#define DSL_RIGHT_MONITOR				0x00000001		// 实时监视
#define DSL_RIGHT_PLAYBACK				0x00000002		// 录像回放
#define DSL_RIGHT_DOWNLOAD				0x00000004		// 录像下载
#define DSL_RIGHT_PTZ					0x00000008		// 云台控制
#define DSL_RIGHT_DEV_VISIT				0x00000010		// 设备直连
#define DSL_RIGHT_DEC_OUT				0x00000020		// 解码输出
#define DSL_RIGHT_ALARM_INPUT			0x00000040		// 报警输入
#define DSL_RIGHT_ALARM_OUTPUT			0x00000080		// 报警输出
#define	DSL_RIGHT_MAMUAL_CONTROL		0x00000100		// 手动控制
#define DSL_RIGHT_THIRD_DOOROUT			0x00000200		// 第三方开门
#define DSL_RIGHT_DOOR_MANAGE			0x00000400		// 门禁管理
#define DSL_RIGHT_QUERY_INOUT_REGISTER	0x00000800		// 进出门记录查询
#define DSL_RIGHT_MIKE_USE				0x00001000		// 话筒使用	
#define DSL_RIGHT_PIC_MONITOR			0x00002000		// 图片监控
#define DSL_RIGHT_VOICE_TALK			0x00004000		// 语音对讲
#define DSL_RIGHT_VOICE_ALARMHOST		0x00008000		// 报警主机（设备权限）
#define DSL_RIGHT_PTZ_POINT				0x00010000		// 预置点控制

#define DSL_RIGHT_TVWALL				0x2000000000000	// 电视墙
#define DSL_RIGHT_PLAYBACK_PLATFORM     0x20000000000000       // 录像回放（平台权限）
#define DSL_RIGHT_PLAYBACK_DEVICE       0x40000000000000       // 录像回放(设备权限)
#define DSL_RIGHT_DOWNLOAD_PLATFORM     0x80000000000000       // 录像下载（平台权限）
#define DSL_RIGHT_DOWNLOAD_DEVICE       0x100000000000000      // 录像下载（设备权限）
#define DSL_RIGHT_SD_IDLEACT			0x200000000000000      // 球机空闲动作配置
// 
typedef enum
{
	GEN_GETGROUP_NODE_ALL			= 0,					// 所有节点
	GEN_GETGROUP_NODE_DEPARTMENT    = 1,					// 组织结构
	GEN_GETGROUP_NODE_BUSSINESSUNIT	= 2,					// 部门结构
	GEN_GETGROUP_NODE_ADMAREA		= 3,					// 行政辖区结构
	GEN_GETGROUP_NODE_ENCODER		= 11,					// 编码器设备
	GEN_GETGROUP_NODE_DECODER		= 12,					// 解码器设备
	GEN_GETGROUP_NODE_ENCHANNEL		= 111,					// 编码通道
	GEN_GETGROUP_NODE_DECHANNEL		= 121,					// 解码通道										
	//fixme：需更新更多
}dpsdk_getgroup_node_e;


// 登录信息
typedef struct DPSDK_API tagLoginInfo
{
	char								szIp[DPSDK_IP_LEN];							// 服务IP,或者是域名
	uint32_t							nPort;										// 服务端口
	char								szUsername[DPSDK_USER_NAME_LEN];			// 用户名
	char								szPassword[DPSDK_PASSWORD_LEN_EX];			// 密码
	int									nProtocol;									// 协议类型
	uint32_t							iType;										// 登陆类型，1为PC客户端, 2为手机客户端
	char								szCheckBit[DPSDK_IP_LEN];					// 手机客户端登陆平台时校验码（一般为手机号）
	char								szIMEINo[DPSDK_IP_LEN];						// IMEI号
	char								szPhonetype[DPSDK_IP_LEN];					// 手机型号
	char								szPhoneMac[DPSDK_IP_LEN];					// 手机MAC
	bool								bForced;									// 是否强制登陆，用于非复用账号
	bool								bPasswordPlaintext;							// 加密登陆时是否仍然透传密码明文（默认false）
	char								platformFlag[DPSDK_PASSWORD_LEN];			// 标识位：级联平台的标识位
}Login_Info_t;

//
typedef enum
{
	DPSDK_ORG_NODE_TYPE_ALL				= 0,				// 查询全部（1~4）
	DPSDK_ORG_NODE_TYPE_GROUP			= 1,				// 组织
	DPSDK_ORG_NODE_TYPE_DEPARTMENT		= 2,				// 部门
	DPSDK_ORG_NODE_TYPE_MONITOR_AREA	= 3,				// 监控区域
	DPSDK_ORG_NODE_TYPE_ADM_AREA		= 4,				// 行政辖区

	DPSDK_ORG_NODE_TYPE_PERSION			= 5,				// 人员
	DPSDK_ORG_NODE_TYPE_CHNDEPREL		= 6,				// 通道-部门关联表 
	DPSDK_ORG_NODE_TYPE_DEPAREAREL		= 7,				// 部门-辖区关联表   
}dpsdk_org_node_e;

typedef enum 
{ 
	DPSDK_ORG_NODE_SUB_TYPE_CURR = 0,                       // 查询本级 
	DPSDK_ORG_NODE_SUB_TYPE_RECURSION,                      // 查询本级及下级所有 
}dpsdk_org_node_subtype_e;

// 
typedef enum
{
	GEN_GETGROUP_OPERATION_ALL		= -1,					// 获取子孙
	GEN_GETGROUP_OPERATION_SELF		= 0,					// 获取自身
	GEN_GETGROUP_OPERATION_CHILD	= 1,					// 获取子节点
}dpsdk_getgroup_operation_e;

// 
typedef enum
{
	GEN_GETCONFIG_EMAPADDR			= 0,					// 获取电子地图服务地址
}dpsdk_getconfig_e;

// 操作日志类型值定义，与数据库中定义保持一致
typedef enum
{
	OPTTYPE_UNKOWN						= 0,
	OPTTYPE_LOGIN						= 1,		//登录
	OPTTYPE_LOGOUT						= 2,		//登出
	OPTTYPE_REAL						= 3,		//实时视频
	OPTTYPE_PTZ							= 4,		//云台
	OPTTYPE_PLAYBACK					= 5,		//回放
	OPTTYPE_DOWNLOAD					= 6,		//下载
	OPTTYPE_LOCALRECORD					= 7,		//本地录像
	OPTTYPE_QUERYRECORD					= 8,		//录像查询
	OPTTYPE_SOUNDTALK					= 9,		//语音对讲
	OPTTYPE_DISARM						= 10,		// 报警主机撤防
	OPTTYPE_ARM							= 11,		// 报警主机布防

	OPTTYPE_RECORDLOCK					= 12,		// 录像锁定

	OPTTYPE_ADD							= 13,		// 新增
	OPTTYPE_MODIFY						= 14,		// 修改
	OPTTYPE_DEL							= 15,		// 删除
	OPTTYPE_QUERY						= 16,		// 查询
	OPTTYPE_INSPECT						= 17,		// 查看
	OPTTYPE_EXPORT						= 18,		// 导出
	OPTTYPE_ROLLBACK					= 19,		// 撤销
	OPTTYPE_IMPORT						= 20,		// 导入，add by 21649
	OPTTYPE_SEND_SMS					= 21,		// 短信发送

	OPTTYPE_TASK						= 24,		// 轮巡任务

	OPTTYPE_UNLOCKRECORD				= 22,		// 录像解锁
	OPTTYPE_FORCEUNLOCKRECORD			= 23,		// 录像强制解锁

	OPTTYPE_IPTALK                      = 28,		// IP对讲
	OPTTYPE_BYPASS                      = 29,		// 旁路
	OPTTYPE_CANCELALARM                 = 30,		// 消警
	OPTTYPE_BROADCAST                   = 39,		// 广播
	OPTTYPE_DEVSNAPPIC					= 45,		// 定时抓图

	// 报警运营新增
	OPTTYPE_ARMANDDISARM				= 90,  // 布撤防（布防、撤防、消警、旁路）
	OPTTYPE_VIDEO						= 91,  // 视频预览(打开视频、关闭视频、修改码流类型、云台控制)
	OPRTYPE_PLAYBACKRECODE				= 92,  // 录像回放(中心录像查询、设备录像查询、中心录像回放、设备录像回放、录像下载)
	OPRTYPE_SOUNDANDTALK				= 93,  // 语音对讲（IP对讲、语音对讲、打开音频）
	OPRTYPE_LOCALOPERATOR				= 94,  // 本地操作（本地抓图、本地录像、视频锁定）
	OPRTYPE_OUTCONTROL					= 95,	// 输出控制（设置报警输出通道工作模式打开、关闭、自动）
	OPRTYPE_SHOWINFO					= 96,	// 信息查看(查看客户信息、网点信息、设备信息)
	OPRTYPE_ALARM						= 97,  // 报警处理(停止报警、警情转移)
	OPRTYPE_LOGINANDOUT					= 98,  // 登入登出
	OPRTYPE_OTHER						= 99,  // 其它
	OPRTYPE_OPEN_SOUND					= 114,  // 音频开启
	OPRTYPE_CLOSE_SOUND					= 115,  // 音频关闭
}dpsdk_log_optType_e;

// 设备大类型
typedef enum
{
	// DSS3.0类型定义，需与”cfl_fun_adddvr.h“保持一致
	DEV_ENC					= 1,			// 编码设备
	DEV_DEC,								// 解码设备
	DEV_ALARM,								// 报警设备
	DEV_TVWALL,								// 电视墙
	DEV_BAYONET,							// 卡口设备
	DEV_MARTIX,								// 矩阵设备
	DEV_IVS,								// 智能设备
	DEV_DOORCTRL,							// 门禁设备
	DEV_PE,									// 动环设备(env_gather)
	DEV_VOICE,								// 对讲设备
	DEV_VSC,								// 转发设备
	DEV_IP,									// IP设备（通过网络接入的设备）
	DEV_MULTIFUN_ALARM,						// 多功能的报警设备（如视频报警主机）
	DEV_SLUICE,								// 道闸设备
	DEV_ELECTRIC,							// 电网设备
	DEV_LED,								// LED设备
	DEV_PATROL				= 17,			// 巡更设备
	DEV_VIBRATIONFIBER		= 18,			// 震动光纤设备
	DEV_SENTRY_BOX			= 19,			// 哨位箱设备
	DEV_COURT				= 20,			// 庭审设备
	DEV_VIDEO_TALK			= 21,			// 可视对讲设备
	DEV_BROADCAST			= 22,			// 广播设备
	DEV_VIDEO_RECORD_SERVER	= 23,			// 录播服务器设备
	DEV_PROTECT_CABIN		= 24,			// 防护舱大类
	DEV_MCD_BROADCAST		= 31,			// MCD广播设备大类
	DEV_RFID				= 32,			// RFID大类
	DEV_DISPATCHER			= 33,			// 指挥调度设备
	DEV_ALARM_STUB			= 34,			// 报警柱大类
	DEV_MAC_PICK			= 36,			// MAC采集设备大类
	DEV_UAV					= 38,			// 无人机
	DEV_POS                 = 40,           // POS大类
	DEV_TRANSPORT_TOOL		= 41,			// 交通运输工具
	DEV_TRANSPORT_STANDARD	= 42,			// 交通部标设备
}dev_main_type_e;

/*
该枚举是从CMS同步过来
管理员端中 角色管理中修改， cms转化通知到客户端
角色修改操作，用户cms消息发送（param1）

CFL_Asynch:operation=cuFunMessage&session=1402884261&sequence=1413&unit=BLS&id=1000
code=3&fromtype=3&totype=7&param1=**4**&param2=0&msg2=1&msg1=

1 通道改变
2 设备树展示变更
3 权限及设备树展示变更（现有系统没用）
4 角色等级变更        //建议新定义枚举，不要复用1
*/
typedef enum 
{ 
	kWebModifyGroupDefault = 0, 
	kWebModifyGroupChannleOnly = 1, 
	kWebModifyGroupTreeOnly = 2, 
	kWebModifyGroupTreeAndChnl = 3, 
	kWebModifyGroupLevel = 4, 

}EnumWebModifyGroupParam1; 

// 
typedef enum
{
	GROUP_CHANGE_UNDEFINE			= 0,			// 
	GROUP_CHANGE_ADD_DEV,							// 
	GROUP_CHANGE_MODIFY_DEV,						// 
	GROUP_CHANGE_DEL_DEV,							// 
	GROUP_CHANGE_ADD_ORG,							// 
	GROUP_CHANGE_MODIFY_ORG,						// 
	GROUP_CHANGE_DELETE_ORG,						// 
	GROUP_CHANGE_MODIFY_GROUOP,						// 
	GROUP_CHANGE_DELETE_GROUOP,						// 
	GROUP_CHANGE_MODIFY_USER,						// 
	GROUP_CHANGE_DELETE_USER,						// 
	GROUP_CHANGE_MODIFY_CHANNLE,					// 
	GROUP_CHANGE_LOCK_USER,
	GROUP_CHANGE_BAYDEV_STATUS_CHANGE,				// 针对第一次卡口批量设备状态更新
	GROUP_CHANGE_MODIFY_ORDER_ORG,					// 业务树顺序变更
	GROUP_CHANGE_MODIFY_USER_LEVEL,							//修改用户等级（录像锁定只有等级1的用户能操作）
}group_change_type_e;

// DSST 结构变更通知类型
typedef enum
{
	DSST_GROUP_CHANGE_UNKNOW = 0,
	DSST_GROUP_CHANGE_ORG_ADDED,
	DSST_GROUP_CHANGE_ORG_CHANGED,					// 组织节点变更通知
	DSST_GROUP_CHANGE_ORG_DELETED,
	DSST_GROUP_CHANGE_PERSON_ADDED,
	DSST_GROUP_CHANGE_PERSON_CHANGED,				// 人员信息变更
	DSST_GROUP_CHANGE_PERSON_DELETED,
	DSST_GROUP_CHANGE_CAR_ADDED,
	DSST_GROUP_CHANGE_CAR_CHANGED,					// 车辆信息变更
	DSST_GROUP_CHANGE_CAR_DELETED,
}dsst_change_type_e;

// 
typedef enum
{
	NETWORKRATE_SET					= 0,			// 网络性能配置
	ALARM_LOG_SET,									// 报警日志保存设置
	//DEVICE_TIME_CHECK,							// 设备自动校时
}dpsdk_system_config_e;

typedef enum
{
	SERVER_TYPE_INFO_UNKNOW	= 0,
	SERVER_TYPE_INFO_SS,
	SERVER_TYPE_INFO_MTS,
	SERVER_TYPE_INFO_CMS,
	SERVER_TYPE_INFO_DMS,
	SERVER_TYPE_INFO_VMS		= 6,

	SERVER_TYPE_INFO_PCS		= 12,
	SERVER_TYPE_INFO_PTS,
	SERVER_TYPE_INFO_ADS		= 16
}dpsdk_server_type_info_e;
// 
typedef enum
{
	NETWORKRATE_WAN					= 0,			// 公网
	NETWORKRATE_LAN_10M,							// 10M
	NETWORKRATE_LAN_100M,							// 100M
	NETWORKRATE_LAN_1000M,							// 1000M
}dpsdk_network_rate_e;

// 用户在线状态
typedef enum
{
	USER_STATUS_UNDEFINE = 0,						// 未定义
	USER_STATUS_ONLINE = 1,							// 在线
	USER_STATUS_OFFLINE,							// 离线
}user_status_e;

// JSON 传输类型
typedef enum
{
	GENERALJSON_TRAN_UNKNOW = -1,
	GENERALJSON_TRAN_REQUEST,
	GENERALJSON_TRAN_RESPONSE,
	GENERALJSON_TRAN_NOTIFY,
	GENERALJSON_TRAN_COUNT,
}generaljson_trantype_e;

typedef enum
{
	PARKINGLOT_CHANGE_UNDEFINE			= 0,		// 
	PARKINGLOT_CHANGE_ADD,							// 
	PARKINGLOT_CHANGE_MODIFY,						// 
	PARKINGLOT_CHANGE_DEL  							// 
}parkinglot_change_type_e;

// 安徽朗坤需求，自定义结构体
typedef enum
{
	FTP_PIC_QUERY,									// 查询ftp图片
	FTP_PIC_DEL,									// 删除ftp图片
}dpsdk_ftp_pic_ope_type_e;

// 
typedef union
{
	dpsdk_network_rate_e	networkrate;			// 网络性能设置
	uint32_t				nMonth;					// 报警日志保存时间（月数）,目前无效
	//uint64_t				nTime;					// 设备自动校时时间，目前无效
}dpsdk_system_config_union;

// 通用组织节点信息
typedef struct DPSDK_API tagOrgInfo
{
	char dbId[DPSDK_ORG_DBID_LEN];					// 数据库自增长ID
	char szCode[DPSDK_ORG_CODE_LEN];				// 通用节点编码
	char szName[DPSDK_ORG_NAME_LEN];				// 通用节点名称
	char szSN[DPSDK_ORG_SN_LEN];					// 通用节点唯一码
	char szType[DPSDK_ORG_TYPE_LEN];				// 通用节点类型
	char szGpsX[DPSDK_ORG_GPS_LEN];					// 通用节点经度
	char szGpsY[DPSDK_ORG_GPS_LEN];					// 通用节点纬度
	char szMemo[DPSDK_ORG_MEMO_LEN];				// 通用节点描述
	uint32_t	domainId;		                    // 域ID
	uint32_t	stat;			                    // 状态
	time_t		createDate;		                    // 创建日期
	uint32_t	userId;			                    // 创建用户ID
	time_t		updateDate;		                    // 修改时间
	uint32_t	updateUserId;	                    // 修改用户ID
}Org_Info_t;

// 人员信息
typedef struct DPSDK_API tagPersonInfo
{
	char	dbId[DPSDK_ORG_DBID_LEN];		        // 数据库自增长ID
	char	Id[DPSDK_ORG_IDENTITY_ID_LEN];			// 身份证号码
	char	name[DPSDK_ORG_NAME_LEN];			    // 姓名
	char	coding[DPSDK_ORG_CODE_LEN];		        // 所属部门
	char	sn[DPSDK_ORG_SN_LEN];				    // 编号
	char	type[DPSDK_ORG_TYPE_LEN];			    // 人员类型 关联字典表的人员类型code
	char	office[DPSDK_ORG_OFFICE_LEN];		    // 办公地点
	char	mobile[DPSDK_ORG_MOBILE_LEN];			// 手机号码
	char	virtualNumber[DPSDK_ORG_VIRNUMER_LEN];	// 虚拟号码
	char	stat[DPSDK_ORG_STATE_LEN];	            // 人员状态 关联字典表的人员状态code
}Person_Info_t;

typedef struct DPSDK_API tagDeptAreaRelation
{
	char	deptCode[DPSDK_ORG_CODE_LEN];	        // 部门编码	PK 关联组织表
	char	areaCode[DPSDK_ORG_CODE_LEN];	        // 辖区编码	 关联地点表
}DeptArea_Relation_t;

typedef struct DPSDK_API tagChannelRelation
{
	char		deviceId[64];						// 设备编码 关联编码通道表的设备编码
	uint32_t	unitSeq;							// 单元序号 关联编码通道表的单元序号
	uint32_t	channel;							// 通道序号 关联编码通道表的通道序号
	char		code[128];							// 编码 关联组织表的部门编码 或者关联地点表的辖区编码
}Channel_Relation_t;

typedef struct DPSDK_API tagServerInfo
{
	char	ip[DPSDK_IP_LEN];
	int		port;
}Server_Base_Info_t;

typedef enum
{
	PC_CLIENT = 1,									//pc客户端
	MOBILE_CLIENT									//手机客户端
}client_login_type_e;

typedef struct DPSDK_API ExcpTime 
{
	int beginHour;									//起始时间：时
	int beginMin;									//起始时间：分

	int endHour;									//停止时间：时
	int endMin;										//停止时间：分

	ExcpTime()
	{
		beginHour = -1;                    
		beginMin = -1;

		endHour = -1;
		endMin = -1;
	}
}ExcpTime_t;

//视频分享结构体
struct ShareVideoInfo
{
	char	szCameraId[DPSDK_CHL_ID_LEN];			//摄像头ID
	int		nType;									//1视频，2音频，3音频＋视频，4报警
	int		nSubStream;								//码流类型。1主码流，2子码流
	int		nIsMobile;								//非零表示手机客户端请求
	uint64_t	nPlanId;								//录像计划ID
	uint64_t	nPlaybacktime;						//回放时间

	ShareVideoInfo(void)
	{
		memset(szCameraId, 0, sizeof(szCameraId));
		nType = 1;
		nSubStream = 1;
		nIsMobile = 0;
		nPlanId = 0;
		nPlaybacktime = 0;
	}
};

//保存图片信息结构体
struct UploadPictureInfo
{
	char		szCameraId[DPSDK_CHL_ID_LEN];		// 摄像头ID
	int64_t		nOptTime;							// 抓图时间
	char		szReason[DPSDK_REMARK_INFO_LEN];	// 抓图原因
	char		szAlarmCode[DPSDK_ALARMCODE_LEN];	// 报警编号
	char		szRemark[DPSDK_REMARK_INFO_LEN];	// 备注
	char		szUrl[DPSDK_TAG_URL_LEN / 2];		// 图片路径,和协议库的长度512保持一致
	//去除组织树缓存修改,新增几个需要客户传入的字段
	int			iChannelNo;							// 通道号
	int			iUnitNO;							// 单元号
	char		szDeviceId[DPSDK_CHL_ID_LEN];		// 设备Id
	char		szChlName[DPSDK_REMARK_INFO_LEN];	// 通道名称
	char		szDeviceName[DPSDK_REMARK_INFO_LEN];// 设备名称

	UploadPictureInfo()
	{
		memset(szCameraId, 0 ,sizeof(szCameraId));
		nOptTime = 0;
		memset(szReason, 0 ,sizeof(szReason));
		memset(szAlarmCode, 0 ,sizeof(szAlarmCode));
		memset(szRemark, 0 ,sizeof(szRemark));
		memset(szUrl, 0 ,sizeof(szUrl));
		iChannelNo = 0;
		iUnitNO = 0;
		memset(szDeviceId, 0 ,sizeof(szDeviceId));
		memset(szChlName, 0 ,sizeof(szChlName));
		memset(szDeviceName, 0 ,sizeof(szDeviceName));
	}
};

// 康特尔需求，自定义结构体
typedef struct DPSDK_API tagIssueInfo
{
	char szStatName[DPSDK_KANGTEER_DATA];
	char szUseClass[DPSDK_KANGTEER_DATA];
	char szContent[DPSDK_KANGTEER_DATA];
	char szIssueName[DPSDK_KANGTEER_DATA];
	char szDeviceID[DPSDK_KANGTEER_DATA];
	char szBeginTime[DPSDK_KANGTEER_DATA];
	char szEndTime[DPSDK_KANGTEER_DATA];
	char szWorkCompany[DPSDK_KANGTEER_DATA];
	char szLinkMan[DPSDK_KANGTEER_DATA];
	char szLinkMethod[DPSDK_KANGTEER_DATA];
	char szAllowJob[DPSDK_KANGTEER_DATA];
}tagIssueInfo_t;

typedef struct DPSDK_API tagChalInfo
{
	char szCameraId[DPSDK_CHL_ID_LEN];			//通道ID
}Chal_Info_t;

//请求查询Ftp图片信息
typedef struct DPSDK_API tagRequFtpPicInfo_t
{
	char szPicPath[DPSDK_FILENAME_LEN];			//图片路径
}Requ_Ftp_Pic_Info_t;

typedef struct DPSDK_API tagRespFtpPicInfo
{
	char szDevId[DPSDK_DEV_ID_LEN];				//摄像头ID
	int  nChlNo;
	char szCapTime[DPSDK_TIMESTR_LEN];
	char szFtpPath[DPSDK_FILENAME_LEN];
}Resp_Ftp_Pic_Info_t;

typedef struct DPSDK_API Social_Pic_Info
{
	std::string strtype;
	std::string strByteStream;
	std::string strUrl;
}Social_Pic_Info_t;

typedef struct DPSDK_API Social_Video_Info
{
	std::string strDeviceID;
	std::string nBeginTime;
	std::string nEndTime;
}Social_Video_Info_t;

typedef struct DPSDK_API Social_Device_Info
{
	std::string strDeviceID;
}Social_Device_Info_t;

// 下级推送上来的记录详细信息
typedef struct DPSDK_API Social_Alarm_Info 
{
	std::string		strReceiptAlarmID;				// 事件ID，唯一，CMS生成
	int				nAlarmStatus;					// 事件状态
	std::string		strDepartCode;					// 下级域ID

	std::string		strVariable;
	std::string		strAlarmType;
	std::string		BeginTime;

	// 下面是详细信息
	std::string		strReporter;					// 报警人
	std::string		strReporterSex;					// 报警人性别
	std::string		strOrganizationOfReporter;		// 报警公司
	std::string		strReportTel;					// 报警人联系电话

	int				nCallPoliceType;				// 报警方式
	int				nCallPoliceSubType;				// 报警方式细类
	std::string		timeAlarmPushTime;				// 报警推送时间
	int				nCallPoliceClass;				// 报警类别
	std::string		timeCaseTime;					// 案发时间
	std::string		strPlace;						// 案发地点

	std::string		strPlatformID;					// 平台编号
	std::string		strPlatformName;				// 平台名称
	std::string		strPlatformPlaceAddress;		// 平台部署地点
	std::string		strPlatformBelongOrganization;	// 平台所属单位
	std::string		strPlatformMaintainDepartment;	// 平台维护单位

	std::string		strDescribe;					// 案情描述
	bool			bHasPicture;					// 是否有监控图片
	bool			bHasVideo;						// 是否有监控视频
	bool			bHasCamera;						// 是否有监控设备
	std::list<Social_Pic_Info_t>		listPictureList;		// 图片列表（RTSP地址）
	std::list<Social_Video_Info_t>		listVideoList;			// 录像列表（设备开始/结束时间）
	std::list<Social_Device_Info_t>		listVideoDeviceList;	// 视频设备列表(设备编码地址)

	Social_Alarm_Info()
	{
		Reset();
	}

	void Reset()
	{
		strReceiptAlarmID = "";						// 事件ID，唯一，CMS生成
		nAlarmStatus = 0;
		strDepartCode = "";

		strVariable = "";
		strAlarmType = "";
		BeginTime = "";

		strReporter = "";
		strReporterSex = "";		
		strOrganizationOfReporter = "";				// 报警公司
		strReportTel = "";							// 报警人联系电话

		nCallPoliceType = 0;						// 报警方式
		nCallPoliceSubType = 0;						// 报警方式细类
		timeAlarmPushTime = "";						// 报警推送时间
		nCallPoliceClass = 0;						// 报警类别
		timeCaseTime = "";							// 案发时间
		strPlace = "";								// 案发地点

		strPlatformID = "";							// 平台编号
		strPlatformName = "";						// 平台名称
		strPlatformPlaceAddress = "";				// 平台部署地点
		strPlatformBelongOrganization = "";			// 平台所属单位
		strPlatformMaintainDepartment = "";			// 平台维护单位

		strDescribe = "";							// 案情描述
		bHasPicture = false;						// 是否有监控图片
		bHasVideo = false;							// 是否有监控视频
		bHasCamera = false;							// 是否有监控设备

		listPictureList.clear();					// 图片列表（RTSP地址）
		listVideoList.clear();						// 录像列表（设备开始/结束时间）
		listVideoDeviceList.clear();				// 视频设备列表(设备编码地址)
	}
}Social_Alarm_Info_t;

//////////////////////////////////////////////////////////////////////////
// 通用消息
class DPSDK_API SendDataToMdlMsg : public DPSDKCBMessage
{
public:
	SendDataToMdlMsg(void);
	virtual ~SendDataToMdlMsg(void){}

	dpsdk_mdl_type_e		mdltype;					// 模块标记
	std::string szSndData;
	std::string szRcvData;
	std::string szCamId;
	BOOL bSave;
	char					serverId[SERVER_ID_LEN];	// 服务ID(DMS增加)
};

// 通用json对象消息
class DPSDK_API GeneralJsonTransportMsg : public DPSDKCBMessage
{
public:
	GeneralJsonTransportMsg(void);
	virtual ~GeneralJsonTransportMsg(void){}

	dpsdk_mdl_type_e		mdltype;					// 模块标记
	generaljson_trantype_e	trantype;					// 传输方式

	dsl::Json::Value		sdata;						// 发出去的数据,一般是客户端填的值
	dsl::Json::Value		rdata;						// 收到的原始数据,一般是服务端填的值

	char					serverId[SERVER_ID_LEN];	// 服务ID(DMS增加)
};

//与cms交互的通用json消息类
class DPSDK_API GeneralJsonSendToCMSMsg: public GeneralJsonTransportMsg
{
public:
	GeneralJsonSendToCMSMsg(void)
	{
		m_cmd = DPSDK_CMD_JSON_SEND_TO_CMS;
		trantype = GENERALJSON_TRAN_REQUEST;
		strJson.clear();
	}
	virtual ~GeneralJsonSendToCMSMsg(void){}

	std::string strJson;
};



// 登录消息
class DPSDK_API LoginMsg : public DPSDKCBMessage
{
public:
	LoginMsg(void);
	virtual ~LoginMsg(void){}

public:
	uint32_t	userId;									// 用户ID
	char		ip[DPSDK_IP_LEN];						// 用户IP
	int			port;									// 端口号
	char		username[DPSDK_USER_NAME_LEN];			// 用户名称
	char		password[DPSDK_PASSWORD_LEN_EX];		// 用户密码
	int			userlevel;
	bool		bOperFlag;								// 操作员标示
	char        clientVersion[DPSDK_VERISON_LEN];       // 客户端版本
	char        platFormVersion[DPSDK_VERISON_LEN];		// 平台版本号
	int			loginType;								// 客户端类型，1为PC客户端, 2为手机客户端
	bool		bHideRecRight;							// true -有隐藏录像权限,用户可以对录像文件进行隐藏，使文件对无该权限用户不可见
	bool		bWhiteListRight;						// true 在白名单中，false 不在白名单中，若不在白名单中则需要验证UKey中的用户名密码
	
	char		webAddrs[DPSDK_WEBADDRS_LEN];			// web服务地址 服务返回的原始IP:Port，格式为【10.10.10.10:80|12.12.12.12:81|...】
	int			webPort;								// web可能配置了外网端口，客户端升级下载时需要使用
	int			nIsLeader;								// 是否组长 1-是; 0-否
	char		szCoding[128];                          // 用户所在组织
	char		szCodeName[256];                        // 用户所在组织名称
	char		szCheckBit[DPSDK_IP_LEN];				// 手机电脑校验位
	int			needAlarmType;							// 接收报警的模式：0-接收所有报警 1-只接收重要报警 2-只接收普通报警 3-停止接收报警
	int			alarmTimeout;							// 报警超时时间
	char		szIMEINo[DPSDK_IP_LEN];					// IMEI号
	char		szPhonetype[DPSDK_IP_LEN];				// 手机型号
	char		szPhoneMac[DPSDK_IP_LEN];				// 手机MAC
	int			nCustomerType;							// 用户类型 企业->1， 教育->2， 银行->3， 其他->4 民警->5 辅警->6
	bool		bForced;								// 是否强制登陆，用于非复用账号
	int			inputPasswordRemainTimes;				// 输入密码剩余次数，默认为-1，表示无限制
	char		szMessage[DPSDK_LOGN_MSG_LEN];			// 登录提示语
	bool		bSingleLogin;							// 是否单点登录，单点登录时密码加密方式不同
	int			iUserLockTime;							// 用户锁定时间
	bool		bPasswordPlaintext;						// 加密登录时，是否仍然透传密码明文，默认false
	std::string m_strPoliceCode;						// 警员编号
	char		platformFlag[DPSDK_PASSWORD_LEN];		// 标识位：级联平台的标识位

	int			bHttps;									//内嵌网页是否开启https，1是，0否
};

// 防瞌睡请求消息
class DPSDK_API SleepMsg:public DPSDKCBMessage
{
public:
	SleepMsg();
	virtual ~SleepMsg(){}

public:
	int32_t	   				iParam1;
	int32_t    				iParam2;
	char       				strMsg1[DPSDK_TIMESTR_LEN];     // 64
	char	   				strMsg2[DPSDK_STRING_LEN];		// 字符参数1,128

	//reponse:
	int32_t					niParam1;						// 报警时间间隔
	int32_t   				niParam2;						// 报警确认超时时间
	int32_t                 niParam3;						// 确认次数
	char    				szstrMsg1[DPSDK_TIMESTR_LEN];	//
	char					szstrMsg2[DPSDK_STRING_LEN];	//
	std::vector<ExcpTime_t> timeVec;						// 时间结构体
};

// 防瞌睡保存违例信息时的请求消息
class DPSDK_API SaveSleepMsg:public DPSDKCBMessage
{
public:
	SaveSleepMsg();
	virtual ~SaveSleepMsg(){}

public:
	int32_t	   				iParam1;						// 用户ID
	int32_t    				iParam2;
	char       				strMsg1[DPSDK_TIMESTR_LEN];		// 用户IP
	char	   				strMsg2[DPSDK_STRING_LEN];		// 违例时间

	//reponse:
	int32_t					niParam1;
	int32_t   				niParam2;
	int32_t                 niParam3;
	char    				szstrMsg1[DPSDK_TIMESTR_LEN];
	char					szstrMsg2[DPSDK_STRING_LEN];
};

// 防瞌睡信息更新的消息
class DPSDK_API UpdataSleepMsg:public DPSDKCBMessage
{
public:
	UpdataSleepMsg();
	virtual ~UpdataSleepMsg(){}

public:
	int32_t	   				iParam1;
	int32_t    				iParam2;
	char       				strMsg1[DPSDK_TIMESTR_LEN];     // 64
	char	   				strMsg2[DPSDK_STRING_LEN];		// 字符参数1,128

	//reponse:
	int32_t					niParam1;
	int32_t   				niParam2;
	int32_t                 niParam3;
	char    				szstrMsg1[DPSDK_TIMESTR_LEN];
	char					szstrMsg2[DPSDK_STRING_LEN];
	std::vector<ExcpTime_t> timeVec;						// 时间结构体
};

// 登出消息
class DPSDK_API LogoutMsg : public DPSDKCBMessage
{
public:
	LogoutMsg(void){ m_cmd = DPSDK_CMD_LOGOUT;}
	virtual ~LogoutMsg(void){}
};

// 获取组织结构消息
class DPSDK_API GetGroupMsg : public DPSDKCBMessage
{
public:
	GetGroupMsg(void);
	virtual ~GetGroupMsg(void){}

public:
	int			nodeType;									// 参见dpsdk_getgroup_node_e
	int			operation;									// 参见dpsdk_getgroup_operation_e
	char		nodeId[DPSDK_ID_LEN];						// 节点ID 
	int			nGetCount;									// 获取次数
	int			reShowGroup;								// 是否重新刷新组织结构0:不需要1:需要
	int         bSimplyDeviceTree;                          // 获取精简版设备树标志位：1 表示获取精简版 0 表示不获取精简版 
};

// 根据类型获取组织结构消息
class DPSDK_API GetGroupByTypeMsg : public DPSDKCBMessage
{
public:
	GetGroupByTypeMsg(void);
	virtual ~GetGroupByTypeMsg(void);

public:
	char					nodeId[DPSDK_ID_LEN];			//节点ID
	int						nodeType;						//参见dpsdk_org_node_e
	int						subType;						//参见dpsdk_org_node_subtype_e


	int						nCount;							// 组织/人员总数
	Org_Info_t*				pOrgInfo;						// 组织信息
	DeptArea_Relation_t*	pDeptAreaRelationInfo;			// 部门辖区关系
	Person_Info_t*			pPersionInfo;					// 人员信息
};

// DSST组织结构变更通知消息
class DPSDK_API DSSTGroupChangedMsg : public DPSDKCBMessage
{
public:
	DSSTGroupChangedMsg(void);
	virtual ~DSSTGroupChangedMsg(void);

public:
	dsst_change_type_e		enType;							// 参见dsst_change_type_e
	char					szMsg[MSG_LENGTH];				// 组织删除时，存储记录dbid     

	int						nCount;							// 组织/人员总数
	Org_Info_t*				pOrgInfo;						// 组织信息
	DeptArea_Relation_t*	pDeptAreaRelationInfo;			// 部门辖区关系
	Person_Info_t*			pPersionInfo;					// 人员信息
};

// CMS关闭消息
class DPSDK_API CmsCloseMsg : public DPSDKCBMessage
{
public:
	CmsCloseMsg(void){ m_cmd = DPSDK_CMD_CMS_CLOSE;} 
	virtual ~CmsCloseMsg(void){}
};

// 获取用户文件消息
class DPSDK_API GetOwnerFileMsg: public DPSDKCBMessage
{
public:
	GetOwnerFileMsg(void);
	virtual ~GetOwnerFileMsg(void);

public:
	char		szFileName[DPSDK_FILENAME_LEN];				// 文件名
	char*		data;										// 数据
	int			nDatalen;									// 
	int			nUserId;
};

// 保存用户文件消息
class DPSDK_API SaveOwnerFileMsg: public DPSDKCBMessage
{
public:
	SaveOwnerFileMsg(void);
	virtual ~SaveOwnerFileMsg(void);

public:
	int			nFileType;									// 保存文件的类型 0 普通文件， 1电视墙任务
	char		szFileName[DPSDK_FILENAME_LEN];				// 文件名
	char*		data;										// 数据
	int			nDatalen;									// 数据长度
	uint32_t	nTvWallID;									// 电视墙ID
	uint32_t	nTaskID;									// 任务ID
	char		szDescription[DPSDK_FILENAME_LEN];			// 任务描述
	int			nUserId;
	int			m_iSortId;									// 任务排序号
};

// 视频巡检消息
class DPSDK_API SaveRoutingFileMsg: public DPSDKCBMessage
{
public:
	SaveRoutingFileMsg(void);
	virtual ~SaveRoutingFileMsg(void);

public:
	unsigned int	userId;									// 用户ID
	int64_t			startTime;								// 开始时间
	int64_t			endTime;								// 结束时间
	unsigned int	totalNum;								// 任务总数
	unsigned int	finishNum;								// 任务完成数
	unsigned int	offlineNum;								// 通道离线数
	uint32_t		nDatalen;								// 长度
	char*			data;									// 通道ID数据
};

//通道权限结构体
typedef struct DPSDK_API RightChan
{
	std::string szCameraID;//通道id
	std::string szRight;//权限信息
}right_chan_t;


// 组织结构变更消息
class DPSDK_API OrgChangeMsg : public DPSDKCBMessage
{
public:
	OrgChangeMsg(void);
	virtual ~OrgChangeMsg(void){};

public:
	group_change_type_e	nChangeCode;						// 变更通知 :
	
	//添加/删除设备 szMsg以设备ID$codeing,ID$codeing
	//修改设备 szMsg以设备ID$新codeing$原codeing,ID$新codeing$原codeing
	//添加/删除/修改组织 szMsg以组织ID,ID
	//修改/删除权限 需要获取所有设备信息（SDK内部已处理）
	char				szMsg[MSG_LENGTH];					//                 

	//内部使用
	bool				bGetAllDev;							// 
	int					nDevGetCount;
	int					nOrgCount;
	int					nOrgGetCount;
	std::string			strCode;		//组织变更，组织coding字段
	std::vector<std::string> m_vecChangeDeviceID;//

	std::vector<right_chan_t> m_vecChannelRight;
};

// 获取配置信息消息
class DPSDK_API GetConfigInfoMsg : public DPSDKCBMessage
{
public:
	GetConfigInfoMsg(void);
	virtual ~GetConfigInfoMsg(void){};

public:
	dpsdk_getconfig_e	nType;								// 
	char				szMsg[MSG_LENGTH];					// 
	uint32_t			nParam;								//
	char				szAddrs[MSG_LENGTH];
	char				szParam[DPSDK_CHAR_LEN_1024];
};

// 全网校时设置消息
class DPSDK_API SetSyncTimeMsg : public DPSDKCBMessage
{
public:
	bool m_bOpen;

	SetSyncTimeMsg();
	virtual ~SetSyncTimeMsg(){}
};

// 保存操作日志消息
class DPSDK_API SaveOptLogMsg : public DPSDKCBMessage
{
public:
	SaveOptLogMsg(void);
	virtual ~SaveOptLogMsg(void){};

public:
	dpsdk_log_optType_e	optType;							// 
	char				cameraId[DPSDK_CHL_ID_LEN];			// 
	int64_t				optTime;							// 
	char				optDesc[DPSDK_OPTLOG_DESC];			// 
};

// 获取模块权限消息
class DPSDK_API GetMenuRightMsg : public DPSDKCBMessage
{
public:
	GetMenuRightMsg(void);
	virtual ~GetMenuRightMsg(void);

public:
	std::string*		strRights;
	int					nCount;
};

// 获取指定功能权限消息
class DPSDK_API GetFunRightMsg : public DPSDKCBMessage
{
public:
	GetFunRightMsg(void);
	virtual ~GetFunRightMsg(void);

public:
	char				userName[DPSDK_USER_NAME_LEN];		// 用户名称
	char				password[DPSDK_PASSWORD_LEN];		// 用户密码
	int					right;
	int					enable;
};

// 获取双目组织节点定位信息
class DPSDK_API LoadMCaliInfoMsg : public DPSDKCBMessage
{
public:
	LoadMCaliInfoMsg(void);
	virtual ~LoadMCaliInfoMsg(void);

public:
	char				szCoding[DPSDK_ID_LEN];				//
	char*				pData;								// 数据
	int					nLen;								// 数据长度
};

// 保存双目组织节点定位信息
class DPSDK_API SaveMCaliInfoMsg : public DPSDKCBMessage
{
public:
	SaveMCaliInfoMsg(void);
	virtual ~SaveMCaliInfoMsg(void);

public:
	char				szCoding[DPSDK_ID_LEN];				// 
	char*				pData;								// 数据
	int					nLen;								// 数据长度
};

// 双目组织节点定位信息变更通知
class DPSDK_API MCaliInfoChangeMsg : public DPSDKCBMessage
{
public:
	MCaliInfoChangeMsg(void);
	virtual ~MCaliInfoChangeMsg(void){};

public:
	char				szCoding[DPSDK_ID_LEN];				// 
};

// FTP操作消息
class DPSDK_API OperatorFtpFileMsg : public DPSDKCBMessage
{
public:
	OperatorFtpFileMsg(void);
	virtual ~OperatorFtpFileMsg(void){};

public:
	dpsdk_operator_ftp_type_e	opType;							// 操作类型 e.g. OP_FTP_TYPE_DOWN 下载 OP_FTP_TYPE_UP 上传 OP_FTP_TYPE_DELETE 删除
	char						szLocalFile[DPSDK_TAG_URL_LEN];	// 本地文件路径
	char						szFtpFile[DPSDK_TAG_PATH_LEN];	// FTP文件路径
	char						szName[DPSDK_ID_LEN];			// FTP用户名
	char						szPwd[DPSDK_ID_LEN];			// FTP用户密码
	dpsdk_ftp_transport_mode_e	mode;							// 文件传输模式
};

////FTP文件传输模式
//class DPSDK_API FtpTansportModeMsg : public DPSDKCBMessage
//{
//public:
//	FtpTansportModeMsg(void);
//	virtual ~FtpTansportModeMsg(void){};
//
//public:
//	dpsdk_ftp_transport_mode_e	mode;							// 传输类型
//};


// 用户组织结构信息
class DPSDK_API UserOrgInfoMsg : public DPSDKCBMessage
{
public:
	UserOrgInfoMsg(void);
	virtual ~UserOrgInfoMsg(void);

public:
	char*				pData;						// 数据
	int					nLen;						// 数据长度
};

// 用户部门组织结构信息
class DPSDK_API UserDepOrgInfoMsg : public DPSDKCBMessage
{
public:
	UserDepOrgInfoMsg(void);
	virtual ~UserDepOrgInfoMsg(void);

public:
	char*				pData;						// 数据
	int					nLen;						// 数据长度
};

// 视频分享消息
class DPSDK_API ShareVideoMsg : public DPSDKCBMessage
{
public:
	ShareVideoMsg(void);
	virtual ~ShareVideoMsg(void);

public:
	ShareVideoInfo*	pVideoInfo;						// 视频信息
	int				nVideoCount;					// 视频个数
	int*			pUserId;						// 用户ID
	int				nUserCount;						// 用户ID个数
	char			szMsg[DPSDK_REMARK_INFO_LEN];	// 描述信息
};

// 视频分享通知消息
class DPSDK_API ShareVideoNotifyMsg : public DPSDKCBMessage
{
public:
	ShareVideoNotifyMsg(void);
	virtual ~ShareVideoNotifyMsg(void);

public:
	ShareVideoInfo*	pVideoInfo;								// 视频信息
	int				nVideoCount;							// 视频个数
	char			szMsg[DPSDK_REMARK_INFO_LEN];			// 描述信息
	int				nSrcUserId;								// 发起通知的用户
	char			szSrcUserName[DPSDK_USER_NAME_LEN];		// 发起通知的用户
};

class DPSDK_API UserStateNotifyMsg : public DPSDKCBMessage
{
public:
	UserStateNotifyMsg(void);
	virtual ~UserStateNotifyMsg(void){};

public:
	int				nUserId;						// 用户ID
	user_status_e	nState;							// 用户状态
};

class DPSDK_API CustomCaseNotifyMsg : public DPSDKCBMessage
{
public:
	CustomCaseNotifyMsg(void);
	virtual ~CustomCaseNotifyMsg(void){};
public:
	char			szMessage[DPSDK_CUSTOM_MSGLENGTH*3];
};

// 保存图片信息消息
class DPSDK_API SaveUploadPictureInfoMsg : public DPSDKCBMessage
{
public:
	SaveUploadPictureInfoMsg(void);
	virtual ~SaveUploadPictureInfoMsg(void){};

public:
	UploadPictureInfo	stuInfo;					// 保存图片信息
	char				szDbId[DPSDK_CHL_ID_LEN];	// 数据库ID
};

// 复用的用户，改变了这个用户的信息	param1=3&param2=0&msg2=&msg1=favorite.xml
class DPSDK_API UserDateChangeMsg : public DPSDKCBMessage
{
public:
	UserDateChangeMsg(void);
	virtual ~UserDateChangeMsg(void){};

public:
	int64_t			nParam1;
	int64_t			nParam2;
	char			szMsg1[DPSDK_MSG_LENGTH];
	char			szMsg2[DPSDK_MSG_LENGTH];
};

class DPSDK_API PollingTaskChangeNotifyMsg : public DPSDKCBMessage
{
public:
	PollingTaskChangeNotifyMsg(void);
	virtual ~PollingTaskChangeNotifyMsg(void){};

public:
	int64_t			nParam1;
	int64_t			nParam2;
	char			szMsg1[DPSDK_MSG_LENGTH];
	char			szMsg2[DPSDK_MSG_LENGTH];
};

class DPSDK_API TaskUserDeleteNotifyMsg : public DPSDKCBMessage
{
public:
	TaskUserDeleteNotifyMsg(void);
	virtual ~TaskUserDeleteNotifyMsg(void){};

public:
	int64_t			nParam1;
	int64_t			nParam2;
	char			szMsg1[DPSDK_MSG_LENGTH];
	char			szMsg2[DPSDK_MSG_LENGTH];
};


//客户端登陆后，用户修改密码
//用户密码修改通知消息
class DPSDK_API UserPswChangeMsg : public DPSDKCBMessage
{
public:
	UserPswChangeMsg(void);
	virtual ~UserPswChangeMsg(void){};

public:
	char		szUserPsw[DPSDK_PASSWORD_LEN];
};

class DPSDK_API ChangeUserPswMsg : public DPSDKCBMessage
{
public:
	ChangeUserPswMsg(void);
	virtual ~ChangeUserPswMsg(void){};

public:
	uint32_t	userId;								// 用户ID
	char		szOldPsw[DPSDK_PASSWORD_LEN];		// 旧密码
	char		szNewPsw[DPSDK_PASSWORD_LEN];		// 新密码
};

// 存放公用数据
class DPSDK_API HDServerBaseMsg : public DPSDKCBMessage
{
public:
	HDServerBaseMsg();
	~HDServerBaseMsg(){}

	char	serverId[SERVER_ID_LEN];				// 服务ID
	char	devId[DPSDK_DEVICE_NAME_LEN];			// 设备ID
};

//华鼎设备信息查询
class DPSDK_API HDDevInfoMsg : public HDServerBaseMsg
{
public:
	HDDevInfoMsg();
	~HDDevInfoMsg(){}

public:
	char		devName[DPSDK_DEVICE_NAME_LEN];		// 设备名称
	char		devType[DPSDK_CHL_ID_LEN];			// 设备类型
	char		firmware[DPSDK_DEVICE_NAME_LEN];	// 固件版本
	char		maxCamera[DPSDK_CHL_ID_LEN];		// 最大支持摄像机个数
	char		manu[DPSDK_DEVICE_NAME_LEN];		// 厂商信息
	char		resultFlag[DPSDK_CHL_ID_LEN];		// 查询结果
};

//华鼎设备状态查询
class DPSDK_API HDDevStatusMsg : public HDServerBaseMsg
{
public:
	HDDevStatusMsg();
	~HDDevStatusMsg(){}

public:
	char		devName[DPSDK_DEVICE_NAME_LEN];				// 摄像机名称(华鼎：下级是海康设备，uas传上来就是按通道传的，在我们这边就是一个设备一个通道)
	char		bonLine[DPSDK_CHL_ID_LEN];					// 是否在线
	char		bworkNormal[DPSDK_CHL_ID_LEN];				// 是否正常工作
	char		brecordNormal[DPSDK_CHL_ID_LEN];			// 是否正常录像
	char		workTime[DPSDK_DEVICE_NAME_LEN];			// 工作时间
	char		unnormalReason[DPSDK_DEVICE_NAME_LEN];		// 不正常原因
	char		resultFlag[DPSDK_CHL_ID_LEN];				// 查询结果
};

//华鼎平台单元流量查询
class DPSDK_API HDPlatformFlowMsg : public DPSDKCBMessage
{
public:
	HDPlatformFlowMsg(void);
	virtual ~HDPlatformFlowMsg(void){};

public:
	char	depId[DPSDK_DEVICE_NAME_LEN];					// 组织结构id
	char	platformName[DPSDK_DEVICE_NAME_LEN];			// 平台名称
	char	totalWB[DPSDK_CHL_ID_LEN];						// 网络总带宽
	char    usedWB[DPSDK_CHL_ID_LEN];						// 占用带宽总量
	char    totalWay[DPSDK_CHL_ID_LEN];						// 总共路数
	char	resultFlag[DPSDK_CHL_ID_LEN];					// 查询结果标志
};
//////////////////////////////////////////////////////////////////////////

// 查询用户权限信息
class DPSDK_API AskForUserAuthorityMsg : public DPSDKCBMessage
{
public:
	AskForUserAuthorityMsg(void);
	virtual ~AskForUserAuthorityMsg(void);

public:
	int		nCount;					// 查看次数  
	int		nTimeInterval;			// 每次查看时间间隔  
	int		nUserType;				// 用户类型 1特权用户 0普通用户
};

// 向服务获取全网校时时间
class DPSDK_API AskForSystemTimeMsg : public DPSDKCBMessage
{
public:
	AskForSystemTimeMsg(void);
	virtual ~AskForSystemTimeMsg(void);

public:
	bool		bCheck;				// 是否校时  
};

// 用户密码修改
class DPSDK_API UserClientChangePswMsg: public DPSDKCBMessage
{
public:
	UserClientChangePswMsg();
	virtual ~UserClientChangePswMsg(){}

public:
	char	m_OldPass[DPSDK_CHAR_LEN_16];	// 旧密码
	char	m_NewPass[DPSDK_CHAR_LEN_16];	// 新密码
};

// 获取组员所属的组长信息列表
class DPSDK_API GetMemberBelogToLeaderMsg: public DPSDKCBMessage
{
public:
	GetMemberBelogToLeaderMsg();
	virtual ~GetMemberBelogToLeaderMsg();

public:
	bool                        m_bIsLeader;		// 标志是否是组长 true 表示组长 false表示组员
	std::vector<int>            m_vectLeaders;		// 组员所属的组长ID
	std::vector<std::string>    m_vectLeadName;		// 组长的名称
};

// 组员所属的组长信息发生变更
class DPSDK_API NoifyModifyLeaderMsg:public DPSDKCBMessage
{
public:
	NoifyModifyLeaderMsg();
	virtual~NoifyModifyLeaderMsg();

public:
	int     m_nType;

};

// 目录检索消息
class DPSDK_API DirSearchMsg : public DPSDKCBMessage
{
public:
	DirSearchMsg(void);
	virtual ~DirSearchMsg(void){};

public:
	char				szCoding[DPSDK_ID_LEN];		// 数据库ID
};

// 获取平台到期时间消息
class DPSDK_API GetLicenseExpireTimeMsg : public DPSDKCBMessage
{
public:
	GetLicenseExpireTimeMsg(void)
	{ 
		m_cmd = DPSDK_CMD_GET_LICENSE_EXPIRE_TIME;
		nRemainTimes = 0;
		nExpireTime  = 0;
	}
	virtual ~GetLicenseExpireTimeMsg(void){}

public:
	int64_t		nRemainTimes;			// 距离到期还剩余的天数
	int64_t		nExpireTime;			// 到期日期
};

// 服务信息
class DPSDK_API GetServerInfoMsg : public DPSDKCBMessage
{
public:
	GetServerInfoMsg(void){ m_cmd = DPSDK_CMD_GET_SERVER_INFO; memset(&m_ServerInfo,0,sizeof(Server_Base_Info_t));nType = SERVER_TYPE_INFO_UNKNOW; }
	virtual ~GetServerInfoMsg(void){}
public:
    dpsdk_server_type_info_e nType;
	Server_Base_Info_t  m_ServerInfo;
};

// 康特尔需求
class DPSDK_API IssueInfoMsg : public DPSDKCBMessage
{
public:
	IssueInfoMsg(void);
	virtual ~IssueInfoMsg(void){};
public:
	//TODO:如果数据有可能超过1024， 则需要将GroupTagIssueInfo定义成指针来动态空间申请
	tagIssueInfo_t GroupTagIssueInfo[DPSDK_KANGTEER_GROUP_DATA];
	int nSize;
};
//end卡特尔需求

class DPSDK_API QueryRequFtpPicMsg : public DPSDKCBMessage
{
public:
	QueryRequFtpPicMsg(void);
	virtual ~QueryRequFtpPicMsg(void){};
public:
	dpsdk_ftp_pic_ope_type_e	nType;
	Chal_Info_t					ChlInfo[DPSDK_QUERY_CHL_COUT];
	Requ_Ftp_Pic_Info_t			requFtpPicInfo[DPSDK_QUERY_PIC_MAXCOUT];
	int							nSize;
	int64_t						nBeginTime;
	int64_t						nEndTime;
};

class DPSDK_API QueryRespFtpPicMsg : public DPSDKCBMessage
{
public:
	QueryRespFtpPicMsg(void);
	virtual ~QueryRespFtpPicMsg(void){};
public:
	Resp_Ftp_Pic_Info_t			respFtpPicInfo[DPSDK_QUERY_PIC_MAXCOUT];
	int							nSize;
};

// 南京地铁3号线 电视墙锁变更通知消息
class DPSDK_API NotifyLockTvwallMsg : public DPSDKCBMessage
{
public:
	NotifyLockTvwallMsg(void);
	virtual ~NotifyLockTvwallMsg(void){};
public:
	int							nTvwallid;							// 电视墙ID
	int							nLockStatus;						// 电视墙锁定状态 0:未加锁 1：锁定
	int							nUserId;							// 用户ID
	char						strClientName[DPSDK_USER_NAME_LEN];	// 用户名
};

// 车场信息变更消息
class DPSDK_API ParkingLotChangeMsg : public DPSDKCBMessage
{
public:
	ParkingLotChangeMsg(void);
	virtual ~ParkingLotChangeMsg(void){};

public:
	parkinglot_change_type_e	nChangeCode;						// 变更通知 : 添加/修改/删除
	char						szMsg[MSG_LENGTH];					//                 
};

class DPSDK_API SocialAlarmMsg : public DPSDKCBMessage
{
public:
	SocialAlarmMsg(void);
	virtual ~SocialAlarmMsg(void){};

public:
	Social_Alarm_Info_t socialAlarmInfo;

};

class DPSDK_API SetPoliceStatusMsg : public DPSDKCBMessage
{
public:
	SetPoliceStatusMsg(void);
	virtual ~SetPoliceStatusMsg(void){};

public:
	std::string		strReceiptAlarmID;
	int				nStatus;
};

class DPSDK_API GetServerSPMConfigMsg : public DPSDKCBMessage
{
public:
	GetServerSPMConfigMsg()
	{
		m_cmd = DPSDK_CMD_GENERAL_GET_SERVER_SPM_CONFIG;
	}
	virtual ~GetServerSPMConfigMsg(){}

public:
	//req

	//resp

	/* SPM_XML
	<?xml version="1.0" encoding="utf-8"?>
	<MCSList>
		<MCS Id="0" TcpListenIp="127.0.0.1" TcpListenPort="8090" />
	</MCSList>
	*/
	std::string		m_xmlSPMCfg;
};

class DPSDK_API IMRefChangeNotifyMsg : public DPSDKCBMessage
{
public:
	IMRefChangeNotifyMsg()
	{
		m_cmd = DPSDK_CMD_GENERAL_IM_REF_CHANGE_NOTIFY;
		m_param1 = 0;
		m_param2 = 0;
	}
	virtual ~IMRefChangeNotifyMsg(){}

public:
	//resp
	uint64_t				m_param1;
	uint64_t				m_param2;
	std::string				m_strMsg1;
	std::string				m_strMsg2;
};

class DPSDK_API UserOrgChangedNotifyMsg : public DPSDKCBMessage
{
public:
	UserOrgChangedNotifyMsg()
	{
		m_cmd = DPSDK_CMD_GENERAL_USER_ORG_CHANGED_NOTIFY;
		m_param1 = 0;
		m_param2 = 0;
		m_strMsg1 = "";
		m_strMsg2 = "";
	}
	virtual ~UserOrgChangedNotifyMsg(){}

public:
	//resp
	uint64_t				m_param1;
	uint64_t				m_param2;
	std::string				m_strMsg1;			//org-coding
	std::string				m_strMsg2;			//org-name
};

class DPSDK_API HttpsNotifyMsg : public DPSDKCBMessage
{
public:
	HttpsNotifyMsg()
	{
		m_cmd = DPSDK_CMD_HTTPS_NOTIFY;
		m_https = 0;
	}
	virtual ~HttpsNotifyMsg(){}

public:
	//resp
	int m_https;//https开启标志
};

class DPSDK_API WebPortChangeNotifyMsg : public DPSDKCBMessage
{
public:
	WebPortChangeNotifyMsg()
	{
		m_cmd = DPSDK_CMD_WEB_PORT_CHANGE_NOTIFY;
	}
	virtual ~WebPortChangeNotifyMsg(){}
};

// 修改用户密码
class DPSDK_API ChangeUserPwdMsg : public DPSDKCBMessage
{
public:
	ChangeUserPwdMsg();
	virtual ~ChangeUserPwdMsg(){};

public:
	int			nUserId;
	char		oldPassword[DPSDK_PASSWORD_LEN];			// 旧密码
	char		newPassword[DPSDK_PASSWORD_LEN];			// 新密码
};
//////////////////////////////////////////////////////////////////////////

// 获取设备列表消息
class DPSDK_API GetDeviceListMsg : public DPSDKCBMessage
{
public:
	GetDeviceListMsg(void);
	virtual ~GetDeviceListMsg(void);

public:
	int			nodeType;					                  // 参见dpsdk_getgroup_node_e
	int			operation;					                  // 参见dpsdk_getgroup_operation_e
	char		nodeId[DPSDK_ID_LEN];		                  // 节点ID
	int         nDevListLen;                                  // 设备列表字符串长度
	char*       szDevList;                                    // 设备列表xml字符串
};

// 获取多个设备的详细消息
class DPSDK_API GetDevicesInfoMsg : public DPSDKCBMessage
{
public:
	GetDevicesInfoMsg(void);
	virtual ~GetDevicesInfoMsg(void);

public:
	char**      szDevicesId;                                  // 多个设备ID
	int         nDevicesCount;                                // 设备ID的数量
	int         nDevInfoLen;                                  // 设备列表字符串长度
	char*       szDevInfo;                                    // 设备列表xml字符串
};

// 保存上传文件信息
class DPSDK_API SaveUploadFileInfoMsg : public DPSDKCBMessage
{
public:
	SaveUploadFileInfoMsg(void);
	virtual ~SaveUploadFileInfoMsg(void){}

public:
	dsl::Json::Value				sdata;

};

// 
class DPSDK_API OperatorRemoteFileMsg : public DPSDKCBMessage
{
public:
	OperatorRemoteFileMsg(void);
	virtual ~OperatorRemoteFileMsg(void){};

public:
	char		url[DPSDK_TAG_URL_LEN];						// ftp服务器存储数据的相对url
	char		path[DPSDK_TAG_PATH_LEN];					// 本地上传或者下载后的图片的地址
};

// DPSDK_CMD_SYNC_TIME_TOCMS
class DPSDK_API SyncTimeToCmsMsg : public DPSDKCBMessage
{
public:
	SyncTimeToCmsMsg(void);
	virtual ~SyncTimeToCmsMsg(void){};
};

//获取超级市场服务列表--江苏高院
typedef struct DPSDK_API server_info
{
	char	ip[DPSDK_IP_LEN];
	int		port;
}Server_Info_t;
typedef std::list<Server_Info_t>	ServerInfoList;
typedef std::map<std::string, ServerInfoList>	ServerInfoMap;
typedef std::map<int,Server_Info_t>  ServerMap;
typedef std::map<std::string, std::string>		ServerCodesMap;//char    code[256];南京高院需求
typedef std::map<int, ServerInfoMap> ServerListMap;  //<unit, <serverId, std::list<Server_Info_t>>>

class DPSDK_API GetSPMServerListMsg : public DPSDKCBMessage
{
public:
	GetSPMServerListMsg();
	~GetSPMServerListMsg(){}

	uint64_t		unit;		//服务类型 1:SS 2:MTS 4:DMS 具体见CFL_UNIT_TYPE定义
	//reponse:
	ServerInfoMap	serverMap;
	ServerCodesMap	codesMap;	//"OrgCode"
};

//应到人数/实到人数 数据上报消息
class DPSDK_API ReportPeopleNumMsg : public DPSDKCBMessage
{
public:
	ReportPeopleNumMsg(void);
	virtual ~ReportPeopleNumMsg(void){};

public:
	//request
	char	m_UserId[DPSDK_USER_NAME_LEN];		//用户ID
	char    m_PlanNum[DPSDK_CHAR_LEN_16];		//应到人数
	char	m_RealNum[DPSDK_CHAR_LEN_16];		//实到人数
	int64_t		upOptTime;						//上报时间
	//response
	uint32_t	nstatus;							//上报成功与否___________ 0失败 1成功;
};

// 获取电子地图车辆图标配置
class DPSDK_API GetEmapCarIconTypeMSg : public DPSDKCBMessage
{
public:
	GetEmapCarIconTypeMSg();
	~GetEmapCarIconTypeMSg(){};

public:
	int		m_nType;							// 电子地图车辆图标类型
};

//新组织结构需要的结构体

// 组织类型 <中行项目>
typedef enum
{
	DEP_TYPE_EX_UNKNOW				= 0,						
	DEP_TYPE_EX_DEP,											// 1-机构
	DEP_TYPE_EX_PLACE,											// 2-场所
	DEP_TYPE_EX_AREA,											// 3-区域

	DEP_TYPE_EX_COUNT				= DEP_TYPE_EX_AREA
}dep_type_ex_e;

// 设备类型，需要和web统一
typedef enum
{
	DEV_TYPE_ENC_BEGIN			= 0,		// 编码设备
	DEV_TYPE_DVR				= DEV_TYPE_ENC_BEGIN + 1,			// DVR
	DEV_TYPE_IPC				= DEV_TYPE_ENC_BEGIN + 2,			// IPC
	DEV_TYPE_NVS				= DEV_TYPE_ENC_BEGIN + 3,			// NVS
	DEV_TYPE_MCD				= DEV_TYPE_ENC_BEGIN + 4,			// MCD
	DEV_TYPE_MDVR				= DEV_TYPE_ENC_BEGIN + 5,			// MDVR
	DEV_TYPE_NVR				= DEV_TYPE_ENC_BEGIN + 6,			// NVR
	DEV_TYPE_SVR				= DEV_TYPE_ENC_BEGIN + 7,			// SVR
	DEV_TYPE_PCNVR				= DEV_TYPE_ENC_BEGIN + 8,			// PCNVR，PSS自带的一个小型服务
	DEV_TYPE_PVR				= DEV_TYPE_ENC_BEGIN + 9,			// PVR
	DEV_TYPE_EVS				= DEV_TYPE_ENC_BEGIN + 10,			// EVS
	DEV_TYPE_MPGS				= DEV_TYPE_ENC_BEGIN + 11,			// MPGS
	DEV_TYPE_SMART_IPC			= DEV_TYPE_ENC_BEGIN + 12,			// SMART_IPC
	DEV_TYPE_SMART_TINGSHEN		= DEV_TYPE_ENC_BEGIN + 13,			// 庭审主机
	DEV_TYPE_SMART_NVR			= DEV_TYPE_ENC_BEGIN + 14,			// SMART_NVR
	DEV_TYPE_PRC				= DEV_TYPE_ENC_BEGIN + 15,			// 防护舱
	DEV_TYPE_JT808				= DEV_TYPE_ENC_BEGIN + 18,			// 部标JT808
	DEV_TYPE_FISH_EYE			= DEV_TYPE_ENC_BEGIN + 19,			// 鱼眼设备
	DEV_TYPE_VTS				= DEV_TYPE_ENC_BEGIN + 20,			// VTS
	DEV_TYPE_VTT				= DEV_TYPE_ENC_BEGIN + 21,			// VTT
	DEV_TYPE_HCVR				= DEV_TYPE_ENC_BEGIN + 22,			// 海康CVR
	DEV_TYPE_IF					= DEV_TYPE_ENC_BEGIN + 23,			// 智能ATM
	DEV_TYPE_VTO				= DEV_TYPE_ENC_BEGIN + 24,			// 金融VTO
	DEV_TYPE_VTA				= DEV_TYPE_ENC_BEGIN + 25,			// VTA
	DEV_TYPE_TC					= DEV_TYPE_ENC_BEGIN + 26,			// 热成像设备
	DEV_TYPE_DSJ				= DEV_TYPE_ENC_BEGIN + 27,			// DSJ
	DEV_TYPE_GLASSES			= DEV_TYPE_ENC_BEGIN + 28,			// 眼镜设备 
	DEV_TYPE_VTT2610C			= DEV_TYPE_ENC_BEGIN + 29,			// VTT2610C
	DEV_TYPE_APP				= DEV_TYPE_ENC_BEGIN + 30,			// -F保险项目新增APP编码小类
	DEV_TYPE_ENCRYPT_IPC		= DEV_TYPE_ENC_BEGIN + 31,			// 加密IPC
	DEV_TYPE_ENCRYPT_NVR		= DEV_TYPE_ENC_BEGIN + 32,			// 加密NVR
	DEV_TYPE_LECHENG_CLOUD		= DEV_TYPE_ENC_BEGIN + 33,			// 乐橙云
	DEV_TYPE_WATCHER			= DEV_TYPE_ENC_BEGIN + 39,			// 守望者设备
	DEV_TYPE_UAV				= DEV_TYPE_ENC_BEGIN + 47,			// 无人机设备
	DEV_TYPE_HS 				= DEV_TYPE_ENC_BEGIN + 48,          // 环视摄像机
	DEV_TYPE_HXIPC 				= DEV_TYPE_ENC_BEGIN + 50,          // 华消烟感IPC
	DEV_TYPE_RADAR_PTZ			= DEV_TYPE_ENC_BEGIN + 51,			// 雷球设备
	DEV_TYPE_ENC_END,

	DEV_TYPE_TVWALL_BEGIN		= 100,
	DEV_TYPE_BIGSCREEN			= DEV_TYPE_TVWALL_BEGIN + 1,		// 大屏
	DEV_TYPE_TVWALL_END,

	DEV_TYPE_DEC_BEGIN			= 200,		// 解码设备
	DEV_TYPE_NVD				= DEV_TYPE_DEC_BEGIN + 1,			// NVD
	DEV_TYPE_SNVD				= DEV_TYPE_DEC_BEGIN + 2,			// SNVD
	DEV_TYPE_UDS				= DEV_TYPE_DEC_BEGIN + 5,			// UDS
	DEV_TYPE_DS_6304D_T			= DEV_TYPE_DEC_BEGIN + 6,			// DS_6304D_T
	DEV_TYPE_AB80				= DEV_TYPE_DEC_BEGIN + 8,			// AB80
	DEV_TYPE_DEC_END,

	DEV_TYPE_MATRIX_BEGIN		= 300,		// 矩阵设备
	DEV_MATRIX_M60				= DEV_TYPE_MATRIX_BEGIN	+ 1,		// M60
	DEV_MATRIX_NVR6000			= DEV_TYPE_MATRIX_BEGIN + 2,		// NVR6000
	DEV_MATRIX_B10_INTEGRATION	= DEV_TYPE_MATRIX_BEGIN + 3,		// 海康B10一体机
	DEV_MATRIX_B10_PLATFORM		= DEV_TYPE_MATRIX_BEGIN + 4,		// 海康B10视频综合平台
	DEV_MATRIX_REDAPPLE			= DEV_TYPE_MATRIX_BEGIN + 5,		// 红苹果设备
	//DEV_MATRIX_PEARMAIN			= DEV_TYPE_MATRIX_BEGIN + 5,
	DEV_MATRIX_MAX1000			= DEV_TYPE_MATRIX_BEGIN + 6,
	DEV_MATRIX_B20_INTEGRATION	= DEV_TYPE_MATRIX_BEGIN + 7,		// 海康B20一体机
	DEV_MATRIX_B20_PLATFORM		= DEV_TYPE_MATRIX_BEGIN + 8,		// 海康B20视频综合平台
	DEV_MATRIX_M70				= DEV_TYPE_MATRIX_BEGIN	+ 9,		// M70
	DEV_MATRIX_NVD0405			= DEV_TYPE_MATRIX_BEGIN	+ 10,		// NVD0405以矩阵方式接入，处理流程同NVD
	DEV_MATRIX_L80				= DEV_TYPE_MATRIX_BEGIN + 11,
	DEV_MATRIX_H265				= DEV_TYPE_MATRIX_BEGIN + 12,       // 新型审讯主机：DH-HVR0404FE-S-H
	DEV_TYPE_MATRIX_END,

	DEV_TYPE_IVS_BEGIN			= 400,		// 智能设备
	DEV_TYPE_ISD				= DEV_TYPE_IVS_BEGIN + 1,			// ISD 智能球
	DEV_TYPE_IVS_B				= DEV_TYPE_IVS_BEGIN + 2,			// IVS-B 行为分析服务
	DEV_TYPE_IVS_V				= DEV_TYPE_IVS_BEGIN + 3,			// IVS-V 视频质量诊断服务
	DEV_TYPE_IVS_FR				= DEV_TYPE_IVS_BEGIN + 4,			// IVS-FR 人脸识别服务
	DEV_TYPE_IVS_PC				= DEV_TYPE_IVS_BEGIN + 5,			// IVS-PC 人流量统计服务
	DEV_TYPE_IVS_M				= DEV_TYPE_IVS_BEGIN + 6,			// IVS_M 主从跟踪智能盒
	DEV_TYPE_IVS_PC_BOX			= DEV_TYPE_IVS_BEGIN + 7,			// IVS-PC 智能盒 
	DEV_TYPE_IVS_B_BOX			= DEV_TYPE_IVS_BEGIN + 8,			// IVS-B 智能盒
	DEV_TYPE_IVS_M_BOX			= DEV_TYPE_IVS_BEGIN + 9,			// IVS-M 盒子
	DEV_TYPE_IVS_PRC			= DEV_TYPE_IVS_BEGIN + 10,			// 防护舱	
	DEV_TYPE_IVS_IF				= DEV_TYPE_IVS_BEGIN + 11,			// IVF-IF -F特制
	DEV_TYPE_IVS_IPC			= DEV_TYPE_IVS_BEGIN + 12,			// IVS-IPC
	DEV_TYPE_IVS_SmartIPC		= DEV_TYPE_IVS_BEGIN + 13,			// IVF-SmartIPC -F用
	DEV_TYPE_IVS_FVM			= DEV_TYPE_IVS_BEGIN + 14,			// 全景拼接
	DEV_TYPE_IVS_IVSS			= DEV_TYPE_IVS_BEGIN + 15,			// IVSS人脸服务器
	DEV_TYPE_IVS_IPC8249		= DEV_TYPE_IVS_BEGIN + 16,			// 8249FR  IPC
	DEV_TYPE_IVS_NVR			= DEV_TYPE_IVS_BEGIN + 17,			// 人脸NVR
	DEV_TYPE_IVS_FD			    = DEV_TYPE_IVS_BEGIN + 18,			// 7200人脸检测服务器
	DEV_TYPE_IVS_CS				= DEV_TYPE_IVS_BEGIN + 19,			// 客流统计
	DEV_TYPE_IVS_LINGTONG		= DEV_TYPE_IVS_BEGIN + 20,			// 灵瞳设备
	DEV_TYPE_IVS_NVR5X_I		= DEV_TYPE_IVS_BEGIN + 21,			// NVR5X-I人脸设备
	DEV_TYPE_IVS_HFS			= DEV_TYPE_IVS_BEGIN + 22,			// IPC达芬奇
	DEV_TYPE_IVS_IVSS_EX		= DEV_TYPE_IVS_BEGIN + 23,			// 用于视频分析的IVSS
	DEV_TYPE_IVS_END,

	DEV_TYPE_BAYONET_BEGIN		= 500,		// -C相关设备
	DEV_TYPE_CAPTURE			= DEV_TYPE_BAYONET_BEGIN + 1,		// 卡口设备
	DEV_TYPE_SPEED				= DEV_TYPE_BAYONET_BEGIN + 2,		// 测速设备
	DEV_TYPE_TRAFFIC_LIGHT		= DEV_TYPE_BAYONET_BEGIN + 3,		// 闯红灯设备
	DEV_TYPE_INCORPORATE		= DEV_TYPE_BAYONET_BEGIN + 4,		// 一体化设备
	DEV_TYPE_PLATEDISTINGUISH	= DEV_TYPE_BAYONET_BEGIN + 5,		// 车牌识别设备
	DEV_TYPE_VIOLATESNAPPIC		= DEV_TYPE_BAYONET_BEGIN + 6,		// 违停检测设备
	DEV_TYPE_PARKINGSTATUSDEV	= DEV_TYPE_BAYONET_BEGIN + 7,		// 车位检测设备
	DEV_TYPE_ENTRANCE			= DEV_TYPE_BAYONET_BEGIN + 8,		// 出入口设备
	DEV_TYPE_VIOLATESNAPBALL	= DEV_TYPE_BAYONET_BEGIN + 9,		// 违停抓拍球机
	DEV_TYPE_THIRDBAYONET		= DEV_TYPE_BAYONET_BEGIN + 10,		// 第三方卡口设备
	DEV_TYPE_ULTRASONIC			= DEV_TYPE_BAYONET_BEGIN + 11,		// 超声波车位检测器
	DEV_TYPE_FACE_CAPTURE		= DEV_TYPE_BAYONET_BEGIN + 12,		// 人脸抓拍设备
	DEV_TYPE_ITC_SMART_NVR		= DEV_TYPE_BAYONET_BEGIN + 13,		// 卡口智能NVR设备
	DEV_TYPE_PARKINGAREASNAP	= DEV_TYPE_BAYONET_BEGIN + 14,		// 停车场区域抓拍设备
	DEV_TYPE_ITC_EVS			= DEV_TYPE_BAYONET_BEGIN + 15,		// EVS
	DEV_TYPE_FACE_RECOGNISE		= DEV_TYPE_BAYONET_BEGIN + 16,		// 人脸识别系统设备
	DEV_TYPE_IPC_CAPTURE		= DEV_TYPE_BAYONET_BEGIN + 17,		// 球机卡口设备
	DEV_TYPE_BAYONET_END,

	DEV_TYPE_ALARM_BEGIN		= 600,		// 报警设备
	DEV_TYPE_ALARMHOST			= DEV_TYPE_ALARM_BEGIN + 1,			// 报警主机
	DEV_TYPE_ALARMSTB			= DEV_TYPE_ALARM_BEGIN + 2,			// 机顶盒
	DEV_TYPE_ALARMSEQUENCE		= DEV_TYPE_ALARM_BEGIN + 4,			// 时序器
	DEV_TYPE_ALARM_END,

	DEV_TYPE_DOORCTRL_BEGIN		= 700,
	DEV_TYPE_DOORCTRL_DOOR		= DEV_TYPE_DOORCTRL_BEGIN + 1,		// 门禁
	DEV_TYPE_DOORCTRL_RFID		= DEV_TYPE_DOORCTRL_BEGIN + 8,		//RFID作为门禁接入(易亿项目)
	DEV_TYPE_DOORCTRL_END,

	DEV_TYPE_PE_BEGIN			= 800,
	DEV_TYPE_PE_PE				= DEV_TYPE_PE_BEGIN + 1,			// 动环
	DEV_TYPE_PE_AE6016			= DEV_TYPE_PE_BEGIN + 2,			// AE6016设备
	DEV_TYPE_PE_NVS				= DEV_TYPE_PE_BEGIN + 3,			// 带动环功能的NVS设备
	DEV_TYPE_PE_END,

	DEV_TYPE_VOICE_BEGIN		= 900,		// ip对讲
	DEV_TYPE_VOICE_MIKE			= DEV_TYPE_VOICE_BEGIN + 1,
	DEV_TYPE_VOICE_NET			= DEV_TYPE_VOICE_BEGIN + 2,
	DEV_TYPE_VOICE_END,

	DEV_TYPE_IP_BEGIN			= 1000,		// IP设备（通过网络接入的设备）
	DEV_TYPE_IP_SCNNER			= DEV_TYPE_IP_BEGIN + 1,			// 扫描枪
	DEV_TYPE_IP_SWEEP			= DEV_TYPE_IP_BEGIN + 2,			// 地磅
	DEV_TYPE_IP_POWERCONTROL	= DEV_TYPE_IP_BEGIN + 3,			// 电源控制器
	DEV_TYPE_IP_END,

	DEV_TYPE_MULTIFUNALARM_BEGIN= 1100,		// 多功能报警主机
	DEV_TYPE_VEDIO_ALARMHOST	= DEV_TYPE_MULTIFUNALARM_BEGIN + 1,	// 视频报警主机
	DEV_TYPE_MULTIFUNALARM_END,

	DEV_TYPE_SLUICE_BEGIN		= 1200,
	DEV_TYPE_SLUICE_DEV			= DEV_TYPE_SLUICE_BEGIN + 1,		// 出入口道闸设备
	DEV_TYPE_SLUICE_PARKING		= DEV_TYPE_SLUICE_BEGIN + 2,		// 停车场道闸设备
	DEV_TYPE_SLUICE_STOPBUFFER	= DEV_TYPE_SLUICE_BEGIN + 3,		// 视频档车器
	DEV_TYPE_SLUICE_END,

	DEV_TYPE_ELECTRIC_BEGIN		= 1300,
	DEV_TYPE_ELECTRIC_DEV		= DEV_TYPE_ELECTRIC_BEGIN + 1,		// 电网设备
	DEV_TYPE_ELECTRIC_END,

	DEV_TYPE_LED_BEGIN			= 1400,
	DEV_TYPE_LED_DEV			= DEV_TYPE_LED_BEGIN+1,			//LED屏设备(诱导)
	DEV_TYPE_LED_DEV_REMAIN		= DEV_TYPE_LED_BEGIN+2,			//LED屏设备（余位）
	DEV_TYPE_LED_DEV_GENERAL	= DEV_TYPE_LED_BEGIN+3,			//LED屏设备（通用）
	DEV_TYPE_LED_END,

	DEV_TYPE_VIBRATIONFIBER_BEGIN	= 1500,		
	DEV_TYPE_VIBRATIONFIBER_DEV	= DEV_TYPE_VIBRATIONFIBER_BEGIN + 1,// 震动光纤设备 
	DEV_TYPE_VIBRATIONFIBER_END,

	DEV_TYPE_PATROL_BEGIN		= 1600,		
	DEV_TYPE_PATROL_DEV			= DEV_TYPE_PATROL_BEGIN + 1,		// 巡更棒设备
	DEV_TYPE_PATROL_SPOT		= DEV_TYPE_PATROL_BEGIN + 2,		// 巡更点设备
	DEV_TYPE_PATROL_END,

	DEV_TYPE_SENTRY_BOX_BEGIN	= 1700,		
	DEV_TYPE_SENTRY_BOX_DEV		= DEV_TYPE_SENTRY_BOX_BEGIN + 1,	// 哨位箱设备
	DEV_TYPE_SENTRY_BOX_END,

	DEV_TYPE_COURT_BEGIN		= 1800,		
	DEV_TYPE_COURT_DEV			= DEV_TYPE_COURT_BEGIN + 1,			// 庭审设备
	DEV_TYPE_COURT_END,

	DEV_TYPE_VIDEO_TALK_BEGIN	= 1900,
	DEV_TYPE_VIDEO_TALK_VTNC	= DEV_TYPE_VIDEO_TALK_BEGIN + 1, 
	DEV_TYPE_VIDEO_TALK_VTO		= DEV_TYPE_VIDEO_TALK_BEGIN + 2,  
	DEV_TYPE_VIDEO_TALK_VTH		= DEV_TYPE_VIDEO_TALK_BEGIN + 3,  
	DEV_TYPE_VIDEO_TALK_ANALOG_VTH		= DEV_TYPE_VIDEO_TALK_BEGIN + 4, 
	DEV_TYPE_VIDEO_TALK_FENCE_VTO		= DEV_TYPE_VIDEO_TALK_BEGIN + 5,
	DEV_TYPE_VIDEO_TALK_DOORLOCK_VTH= DEV_TYPE_VIDEO_TALK_BEGIN + 6, 
	DEV_TYPE_VIDEO_TALK_ANALOG_VTO		= DEV_TYPE_VIDEO_TALK_BEGIN + 7,	// 半数字门口机 
	DEV_TYPE_VIDEO_TALK_VTS				= DEV_TYPE_VIDEO_TALK_BEGIN + 8,	// VTS管理机  
	DEV_TYPE_VIDEO_TALK_SIP_PHONE		= DEV_TYPE_VIDEO_TALK_BEGIN + 10,	// 第三方厂家Sip话机  
	DEV_TYPE_VIDEO_TALK_END,

	DEV_TYPE_BROADCAST_BEGIN	= 2000,
	DEV_TYPE_BROADCAST_ITC_T6700R = DEV_TYPE_BROADCAST_BEGIN + 1,	// ITC_T6700R广播设备
	DEV_TYPE_BROADCAST_END,

	DEV_TYPE_VIDEO_RECORD_SERVER_BEGIN	= 2100,
	DEV_TYPE_VIDEO_RECORD_SERVER_BNVR	= DEV_TYPE_VIDEO_RECORD_SERVER_BEGIN + 1, // BNVR设备
	DEV_TYPE_VIDEO_RECORD_SERVER_OE	= DEV_TYPE_VIDEO_RECORD_SERVER_BEGIN + 2, // 手术设备(operation equipment)
	DEV_TYPE_VIDEO_RECORD_SERVER_END,

	DEV_TYPE_PROTECT_CABIN_BEGIN		= 2200,
	DEV_TYPE_PROTECT_CABIN				= DEV_TYPE_PROTECT_CABIN_BEGIN + 1,		// -F,防护舱
	DEV_TYPE_PROTECT_CABIN_END,

	DEV_TYPE_RFID_BEGIN					= 2300,
	DEV_TYPE_RFID_CARDDISPENSERR		= DEV_TYPE_RFID_BEGIN + 1,			//发卡器
	DEV_TYPE_RFID_RECRIVER				= DEV_TYPE_RFID_BEGIN + 2,			//接收器
	DEV_TYPE_RFID_WRISTBAND				= DEV_TYPE_RFID_BEGIN + 3,			//手环
	DEV_TYPE_RFID_LOCATOR				= DEV_TYPE_RFID_BEGIN + 4,			//定位器
	DEV_TYPE_RFID_READER				= DEV_TYPE_RFID_BEGIN + 5,			//读卡器
	DEV_TYPE_RFID_ALARM					= DEV_TYPE_RFID_BEGIN + 6,			//报警器
	DEV_TYPE_RFID_INTERCOM				= DEV_TYPE_RFID_BEGIN + 7,			//对讲机
	DEV_TYPE_RFID_GPSTRACKER			= DEV_TYPE_RFID_BEGIN + 8,			//GPS跟踪器
	DEV_TYPE_RFID_VEHICLEGPS			= DEV_TYPE_RFID_BEGIN + 9,			//车载GPS
	DEV_TYPE_RFID_TALKGPS				= DEV_TYPE_RFID_BEGIN + 10,			//对讲GPS
	DEV_TYPE_RFID_ELEC_FETTERS			= DEV_TYPE_RFID_BEGIN + 11,			//电子脚镣
	DEV_TYPE_RFID_END,

	DEV_TYPE_ALARM_STUB_BEGIN			= 3400,								// 报警柱设备类
	DEV_TYPE_ALARM_STUB_VTA				= DEV_TYPE_ALARM_STUB_BEGIN + 1,
	DEV_TYPE_ALARM_STUB_END,

	DEV_TYPE_MAC_PICK_BEGIN				= 3600,								// MAC地址采集设备类
	DEV_TYPE_MAC_PICK					= DEV_TYPE_MAC_PICK_BEGIN + 1,		
	DEV_TYPE_MAC_PICK_END,


	DEV_TYPE_POS_BEGIN		= 4000,
	DEV_TYPE_POS_BOX		= DEV_TYPE_POS_BEGIN + 1,		// POS盒子
	DEV_TYPE_POS_END,

	DEV_TYPE_UAV_BEGIN			= 4200,								// 无人机设备大类
	DEV_TYPE_UAV_DEV			= DEV_TYPE_UAV_BEGIN + 1,			// 无人机设备
	DEV_TYPE_UAV_END,

	DEV_TYPE_TRANSPORT_TOOL_BEGIN = 4500,								// 交通运输工具设备大类
	DEV_TYPE_TRANSPORT_TOOL_DEV	= DEV_TYPE_TRANSPORT_TOOL_BEGIN + 1,// 车辆
	DEV_TYPE_TRANSPORT_TOOL_END,

	DEVTYPE_TRANSPORT_STANDARD_BEGIN = 4800,							// 交通部标设备大类
	DEVTYPE_TRANSPORT_STANDARD_DEV = DEVTYPE_TRANSPORT_STANDARD_BEGIN + 1,	//808设备
	DEVTYPE_TRANSPORT_STANDARD_END,

	DEV_TYPE_DISPATCHER_BEGIN	= 5000,
	DEV_TYPE_DISPATCHER			= DEV_TYPE_DISPATCHER_BEGIN + 1,	//指挥调度设备
	DEV_TYPE_DISPATCHER_END,

}dev_type_e;

// 通道类型
typedef enum
{
	CHNL_TYPE_ENC_BEGIN,					// 编码通道
	CHNL_TYPE_STREAM		= 1,			// 视频
	CHNL_TYPE_PIC,							// 图片
	CHNL_TYPE_MIX,							// 双码流
	CHNL_TYPE_REMOTE,						// 远程通道
	CHNL_TYPE_ENC_END		= 10,

	CHNL_TYPE_DEC_BEGIN,					// 解码通道
	CHNL_TYPE_DEC,
	CHNL_TYPE_DEC_END		= 20,

	CHNL_TYPE_ALARMIN_BEGIN,				// 报警输入通道
	CHNL_TYPE_ALARMIN,
	CHNL_TYPE_ALARMIN_END	= 30,

	CHNL_TYPE_ALARMOUT_BEGIN,				// 报警输出通道
	CHNL_TYPE_ALARMOUT,
	CHNL_TYPE_ALARMOUT_END	= 40,

	CHNL_TYPE_LED_BEGIN,					// LED通道
	CHNL_TYPE_LED,
	CHNL_TYPE_LED_END		= 50,	

	//动环NVS
	CHNL_TYPE_PE_POWER_INTERRUPT			= 1700,					// 市电中断报警 
	CHNL_TYPE_PE_POWER_ENABLED				= 1701,					// 市电启用报警 
	CHNL_TYPE_PE_INFRARED_DETECT			= 1702,					// 红外探测报警 
	CHNL_TYPE_PE_GAS_OVER_SECTION			= 1703,					// 燃气浓度
	CHNL_TYPE_PE_FLOW_OVER_SECTION			= 1704,					// 瞬时流量
	CHNL_TYPE_PE_TEMPERATURE_SECTION		= 1705,					// 管道温度超过阀值 
	CHNL_TYPE_PE_PRESSURE_SECTION			= 1706,					// 管道压力超过阀值

	//动环通道//开关量，不可控
	CHNL_TYPE_PE_SWITCH_START				=1800,
	CHNL_TYPE_PE_INFRARED,											// 红外对射告警
	CHNL_TYPE_PE_SMOKE,												// 烟感告警
	CHNL_TYPE_PE_WATER,												// 水浸告警
	CHNL_TYPE_PE_COMPRESSOR,										// 压缩机故障告警
	CHNL_TYPE_PE_OVERLOAD,											// 过载告警
	CHNL_TYPE_PE_BUS_ANOMALY,										// 母线异常
	CHNL_TYPE_PE_LIFE,												// 寿命告警
	CHNL_TYPE_PE_SOUND,												// 声音告警
	CHNL_TYPE_PE_TIME,												// 时钟告警
	CHNL_TYPE_PE_FLOW_LOSS,											// 气流丢失告警
	CHNL_TYPE_PE_FUSING,											// 熔断告警
	CHNL_TYPE_PE_BROWN_OUT,											// 掉电告警
	CHNL_TYPE_PE_LEAKING,											// 漏水告警
	CHNL_TYPE_PE_JAM_UP,											// 堵塞告警
	CHNL_TYPE_PE_TIME_OUT,											// 超时告警
	CHNL_TYPE_PE_REVERSE_ORDER,										// 反序告警
	CHNL_TYPE_PE_NETWROK_FAILURE,									// 组网失败告警
	CHNL_TYPE_PE_UNIT_CODE_LOSE,									// 机组码丢失告警
	CHNL_TYPE_PE_UNIT_CODE_DISMATCH,								// 机组码不匹配告警
	CHNL_TYPE_PE_FAULT,												// 故障告警
	CHNL_TYPE_PE_UNKNOWN,											// 未知告警
	CHNL_TYPE_PE_CUSTOM,											// 自定义告警
	CHNL_TYPE_PE_NOPERMISSION,										// 无权限告警
	CHNL_TYPE_PE_INFRARED_DOUBLE,									// 红外双鉴告警
	CHNL_TYPE_PE_ELECTRONIC_FENCE,									// 电子围栏告警
	CHNL_TYPE_PE_UPS_MAINS,											// 市电正常市电异常
	CHNL_TYPE_PE_UPS_BATTERY,										// 电池正常电池异常
	CHNL_TYPE_PE_UPS_POWER_SUPPLY,									// UPS正常输出旁路供电
	CHNL_TYPE_PE_UPS_RUN_STATE,										// UPS正常UPS故障
	CHNL_TYPE_PE_UPS_LINE_STYLE,									// UPS类型为在线式UPS类型为后备式
	CHNL_TYPE_PE_XC,												// 小车
	CHNL_TYPE_PE_DRQ,												// 断路器
	CHNL_TYPE_PE_GLDZ,												// 隔离刀闸
	CHNL_TYPE_PE_JDDZ,												// 接地刀闸
	CHNL_TYPE_PE_IN_END,

	//动环通道//开关量，可控
	CHNL_TYPE_PE_DOOR_SWITCH				=1850,					// 门禁控制器开关告警
	CHNL_TYPE_PE_UPS_SWITCH,										// UPS开关告警,
	CHNL_TYPE_PE_DBCB_SWITCH,										// 配电柜开关告警
	CHNL_TYPE_PE_ACDT_SWITCH,										// 空调开关告警
	CHNL_TYPE_PE_DTPW_SWITCH,										// 直流电源开关告警
	CHNL_TYPE_PE_LIGHT_SWITCH,										// 灯光控制器开关告警
	CHNL_TYPE_PE_FAN_SWITCH,										// 风扇控制器开关告警
	CHNL_TYPE_PE_PUMP_SWITCH,										// 水泵开关告警
	CHNL_TYPE_PE_BREAKER_SWITCH,									// 刀闸开关告警
	CHNL_TYPE_PE_RELAY_SWITCH,										// 继电器开关告警
	CHNL_TYPE_PE_METER_SWITCH,										// 电表开关告警
	CHNL_TYPE_PE_TRANSFORMER_SWITCH,								// 变压器开关告警
	CHNL_TYPE_PE_SENSOR_SWITCH,										// 传感器开关告警
	CHNL_TYPE_PE_RECTIFIER_SWITCH,									// 整流器告警
	CHNL_TYPE_PE_INVERTER_SWITCH,									// 逆变器告警
	CHNL_TYPE_PE_PRESSURE_SWITCH,									// 压力开关告警
	CHNL_TYPE_PE_SHUTDOWN_SWITCH,									// 关机告警
	CHNL_TYPE_PE_WHISTLE_SWITCH,									// 警笛告警
	CHNL_TYPE_PE_SWITCH_END,

	//动环通道//模拟量
	CHNL_TYPE_PE_ANALOG_START				=1880,
	CHNL_TYPE_PE_TEMPERATURE,										// 温度告警
	CHNL_TYPE_PE_HUMIDITY,											// 湿度告警
	CHNL_TYPE_PE_CONCENTRATION,										// 浓度告警
	CHNL_TYPE_PE_WIND,												// 风速告警
	CHNL_TYPE_PE_VOLUME,											// 容量告警
	CHNL_TYPE_PE_VOLTAGE,											// 电压告警
	CHNL_TYPE_PE_ELECTRICITY,										// 电流告警
	CHNL_TYPE_PE_CAPACITANCE,										// 电容告警
	CHNL_TYPE_PE_RESISTANCE,										// 电阻告警
	CHNL_TYPE_PE_CONDUCTANCE,										// 电导告警
	CHNL_TYPE_PE_INDUCTANCE,										// 电感告警
	CHNL_TYPE_PE_CHARGE,											// 电荷量告警
	CHNL_TYPE_PE_FREQUENCY,											// 频率告警
	CHNL_TYPE_PE_LIGHT_INTENSITY,									// 发光强度告警(坎)
	CHNL_TYPE_PE_PRESS,												// 力告警（如牛顿，千克力）
	CHNL_TYPE_PE_PRESSURE,											// 压强告警（帕，大气压）
	CHNL_TYPE_PE_HEAT_TRANSFER,										// 导热告警（瓦每平米）
	CHNL_TYPE_PE_THERMAL_CONDUCTIVITY,								// 热导告警（kcal/(m*h*℃)）
	CHNL_TYPE_PE_VOLUME_HEAT,										// 比容热告（kcal/(kg*℃)）
	CHNL_TYPE_PE_HOT_WORK,											// 热功告警（焦耳）
	CHNL_TYPE_PE_POWER,												// 功率告警（瓦）
	CHNL_TYPE_PE_PERMEABILITY,										// 渗透率告警（达西）
	CHNL_TYPE_PE_PROPERTION,										// 比例（包括电压电流变比，功率因素，负载单位为%） 
	CHNL_TYPE_PE_ENERGY,											// 电能（单位为J）
	CHNL_TYPE_PE_TIME_EX,											// 时间(文档中定义枚举时重名了，后缀加EX区分)
	CHNL_TYPE_PE_ANALOG_END,
	//动环通道=end

	CHNL_TYPE_AE_BEGIN						= 2000,
	CHNL_TYPE_AE_DOOR_MAGNETISM				= 2200,
	CHNL_TYPE_AE_PASSIVE_INFRARED			= 2201,					// 被动红外
	CHNL_TYPE_AE_GAS						= 2202,					// 气感
	CHNL_TYPE_AE_INITIATIVE_INFRARED		= 2203,					// 主动红外
	CHNL_TYPE_AE_GLASS_CRASH				= 2204,					// 玻璃破碎
	CHNL_TYPE_AE_EXIGENCY_SWITCH			= 2205,					// 紧急开关
	CHNL_TYPE_AE_SHAKE						= 2206,					// 震动
	CHNL_TYPE_AE_BOTH_JUDGE					= 2207,					// 双鉴（红外+微波）
	CHNL_TYPE_AE_THREE_TECHNIC				= 2208,					// 三技术
	CHNL_TYPE_AE_CALL_BUTTON				= 2209,					// 呼叫按钮
	CHNL_TYPE_AE_SENSE_OTHER				= 2210,					// 其他
	CHNL_TYPE_AE_END						= 2300,

}chnl_type_e;//"channelType"

// 设备协议类型，NetSDK适配过来
typedef enum tagDGP_DEVICE_PROTOCOL
{
	DPSDK_PROTOCOL_DAHUA2,						// 大华2代协议
	DPSDK_PROTOCOL_DAHUA3,						// 大华3代协议
}dgp_dev_protocol_e;


// 单元类型
typedef enum
{
	DEV_UNIT_UNKOWN,												// 未知
	DEV_UNIT_ENC,													// 编码
	DEV_UNIT_DEC,													// 解码
	DEV_UNIT_ALARMIN,												// 报警输入
	DEV_UNIT_ALARMOUT,												// 报警输出
	DEV_UNIT_TVWALLIN,												// TvWall输入
	DEV_UNIT_TVWALLOUT,												// TvWall输出
	DEV_UNIT_DOORCTRL,												// 门禁
	DEV_UNIT_VOICE,													// 对讲
	DEV_UNIT_PE								= 10,					// 动环PE,原来叫做PE=>power environment(动力环境)
	DEV_UNIT_ROADGATE						= 14,					// 道闸
	DEV_UNIT_LED							= 15,					// LED
	DEV_UNIT_DISPATCHER						= 33,					// 调度机
	DEV_UNIT_MACPICK						= 36,					// MAC地址采集设备类
}Dev_Unit_Type_e;

// 设备状态，跟协议栈的定义匹配
typedef enum
{
	DEV_STATUS_UNDEFINE		= 0,
	DEV_STATUS_ONLINE		= 1,			// 在线
	DEV_STATUS_OFFLINE,						// 离线
	DEV_STATUS_FORBID,						// 停用

}dev_status_e;


typedef struct tagUnitNodesInfo
{
	int						m_nUnitNo;					//单元序号，TODO:要和web一致 一般设备都是0，解码器从0开始   
	int						m_nChnlTotalNum;
	int						m_nTrackID;
	encdev_stream_e         m_nAssistStream;			//码流类型
	int						m_nZeroEncode;				//是否支持0通道多画面编码
	std::string				m_strAssosiatedDevId;		//卡口设备关联的MDVR设备ID
	decode_mode_e			m_nDecMode;					//解码模式
	int						m_nThirdControl;			//是否允许第三方控制 0否 1是
	int						m_nFingerPrintValidate;		//是否需要指纹验证 0否 1是
	std::string				m_strVoiceIp;
	std::string				m_strClientIp;
	int						m_nVoicePort;
	int						m_nStatusPort;
	int						m_nVoiceMainSN;				//主机序列号
	int						m_nDynType;
	std::string				m_sName;
	std::string				m_sDesc;
	std::string				m_sCode;

	uint64_t    				m_nUintCapability;				// 能力集


	tagUnitNodesInfo()
	{
		m_nUnitNo = 0;		
		m_nChnlTotalNum = 0;		
		m_nTrackID = 0;
		m_nAssistStream = (encdev_stream_e)0;
		m_nZeroEncode = 0;
		m_strAssosiatedDevId = "";
		m_nDecMode = (decode_mode_e)0;
		m_nThirdControl = 0;
		m_nFingerPrintValidate = 0;
		m_strVoiceIp = "";
		m_strClientIp = "";
		m_nVoicePort = 0;
		m_nStatusPort = 0;
		m_nVoiceMainSN = 0;
		m_nDynType = 0;
		m_sName = "";
		m_sDesc = "";
		m_sCode = "";		
		m_nUintCapability = 0;
	}
}UnitNodes_t;

//组织节点信息
typedef struct DPSDK_API tagSigOrgInfo
{
	std::string					szCoding;						// 节点code
	std::string					szDepName;						// 节点名称
	std::string					szModifyTime;					// 节点修改时间
	std::string					szSN;							// 唯一标识码
	std::string					szMemo;							// 备注信息 -->报警运营平台
	int							nDepType;						// 组织节点类型 -->报警运营平台
	int							nDepSort;						// 组织排序
	int							nChargebooth;					// 收费亭标志
	int							nDepExtType;					// 组织节点扩展类型
	dep_type_ex_e				nDepTypeEx;						// 组织节点类型 <中国银行>
	int							nplaceType;						// 场所类型 <中国银行>
	std::string					szOrgUUID;						// <中国银行>
	std::string					szProvince;						// 省<中国银行>
	std::string					szOrgID;						// 组织结点唯一ID<海南省透明厨房项目>

	tagSigOrgInfo()
	{
		szCoding = "";
		szDepName = "";
		szModifyTime = "";
		szSN = "";
		szMemo = "";
		nDepType = 0;
		nDepSort = 0;
		nChargebooth = 0;
		nDepExtType = 0;
		nDepTypeEx = (dep_type_ex_e)0;
		nplaceType = 0;
		szOrgUUID = "";
		szProvince = "";
		szOrgID = "";
	}
}SigOrg_Info_t;

typedef std::map<std::string, int> SortInfoMap;

//组织节点结构体
typedef struct DPSDK_API tagAllOrgInfo
{
	SigOrg_Info_t					struSigOrgInfo;			//本级组织信息
	std::vector<tagAllOrgInfo>		vecAllOrgInfo;			//子组织信息数组
	std::vector<std::string>		vecOwnerDeviceId;		//本级设备id
	std::vector<std::string>		vecOwnerChannelId;		//本级通道id
	SortInfoMap						mapSort;				//本组织下的排序信息
	
	tagAllOrgInfo()
	{
		tagSigOrgInfo();
		vecAllOrgInfo.clear();
		vecOwnerDeviceId.clear();
		vecOwnerChannelId.clear();
		mapSort.clear();
	}
}AllOrg_Info_t;

//删除组织节点上抛结构体(支持批量)
typedef struct DPSDK_API tagDeleteOrg
{
	std::vector<std::string>		vecDeleteOrgId;				//节点Id数组

	tagDeleteOrg()
	{
		vecDeleteOrgId.clear();
	}
}DeleteOrg_t;

//通道基类
typedef struct DPSDK_API tagChannelInfo
{
	std::string   				sChnlID;						// 通道编号
	std::string   				m_strChnlName;					// 通道名称
	std::string   				m_strChnlDesc;					// 通道信息描述
	std::string   				m_strDevID;						// 设备ID
	uint64_t    				m_nRight;						// 权限信息
	int         				m_nChnlNum;						// 通道号
	int							m_nUnitNo;						// 单元号
	Dev_Unit_Type_e				enumUnitType;					// 单元类型
	chnl_type_e 				m_nChnlType;					// 通道类型
	int         				m_nStatus;						// 通道状态
	std::string					m_strChnlSN;					// 互联编码SN
	std::string					m_strExtension;					// 扩展字段（内容为xml）
	std::string					m_strExpiredDate;				// 过期时间，<中行项目>
	SortInfoMap					m_sortMap;						// 排序信息
	std::string                 m_strCode;
	std::string					m_strChnlDB33;					// DB33编码

	int							m_nUAVSystemStat;				// 系统状态
	int							m_nUAVFlyModel;					// 飞行模式
	int							m_nUAVCloudModel;				// 云台模式
	int							m_nUAVLockModel;				// 锁定模式
	std::string					m_strUAVHomeGpsX;				// HOME点经度
	std::string					m_strUAVHomeGpsY;				// HOME点纬度
	std::string					m_strUAVHomeGpsZ;				// HOME点高度

	tagChannelInfo()
	{
		sChnlID = "";
		m_strChnlName = "";
		m_strChnlDesc ="";
		m_strDevID = "";
		m_nRight = 0;
		m_nChnlNum = 0;
		m_nUnitNo = 0;
		enumUnitType = (Dev_Unit_Type_e)0;
		m_nChnlType = (chnl_type_e)0;
		m_nStatus = 0;
		m_strChnlSN = "";
		m_strExtension = "";
		m_strExpiredDate = "";
		m_sortMap.clear();
		m_nUAVSystemStat = 0;
		m_nUAVFlyModel = 0;
		m_nUAVCloudModel = 0;
		m_nUAVLockModel = 0;
		m_strUAVHomeGpsX = "";
		m_strUAVHomeGpsY = "";
		m_strUAVHomeGpsZ = "";
		m_strChnlDB33 = "";

	}
}ChannelInfo_t;
// 编码通道
typedef struct DPSDK_API  tagEncChannelInfo:public ChannelInfo_t
{
	camera_type_e				m_nCameraType;					// 类型，参见CameraType_e
	std::string					m_strCtrlId;					// 键盘控制id
	std::string					m_strLatitude;					// 纬度
	std::string					m_strLongitude;					// 经度
	std::string					m_strViewDomain;				// 是否支持可视域
	std::string					m_cameraFunction;				// 0:无任何支持功能 1:支持鱼眼 2:支持电动聚焦
	std::string					m_strMulticastIp;				// 组播IP
	int							m_nMulticastPort;				// 组播端口
	std::string					m_strNvrIp;						// NVR 通道IP 
	std::string					m_strChannelRemoteType;			// 远程通道类型， 范围是 本地编码通道，远程通道，级联通道，模拟矩阵通道 (值分别为1,2,3,4)
	std::string					m_subMulticastIp;				// 辅码流IP
	int							m_subMulticastPort;				// 辅码流端口
	int							m_nHasPickup;					// 通道是否有拾音器，参见chnl_haspicup_e
	uint64_t    				m_nCapability;					// 能力集

	std::string					m_strArchivesNumber;			// 档案编号
	std::string					m_strMonitorTarget;				// 监控目标
	std::string					m_strRoutingInspection;			// 市局巡检点位
	std::string					m_strMatrixNumber;				// 矩阵编号
	std::string					m_strInstallAddress;			// 安装位置(闵行导入用) 

	//通道所属的单元属性
	int							iTrackID;						// 取流类型
	int							enumEncdevStream;				// 码流类型
	int							iZeroEncode;					// 是否支持0通道多画面编码
	std::string					strAssosiatedDevId;				// 卡口设备关联的MDVR设备ID
	uint64_t    				m_nUintCapability;				// 能力集

	std::string					m_strShineAngle;				// 可视域角度
	std::string					m_strShineRange;				// 可视域范围
	std::string					m_strShineDistance;				// 可视域距离

	tagEncChannelInfo()
	{
		m_nCameraType = (camera_type_e)0;
		m_strCtrlId = "";	
		m_strLatitude = "";	
		m_strLongitude = "";	
		m_strViewDomain = "";
		m_cameraFunction = "";
		m_strMulticastIp = "";		
		m_nMulticastPort = 0;
		m_strNvrIp = "";					
		m_strChannelRemoteType = "";		
		m_subMulticastIp = "";		
		m_subMulticastPort = 0;
		m_nHasPickup = 0;
		m_nCapability = 0;

		m_strArchivesNumber = "";
		m_strMonitorTarget = "";
		m_strRoutingInspection = "";
		m_strMatrixNumber = "";
		m_strInstallAddress = "";

		iTrackID = 0;			
		enumEncdevStream = 0;	
		iZeroEncode = 0;		
		strAssosiatedDevId = "";	

		m_nUintCapability = 0;

		m_strShineAngle = "";
		m_strShineRange = "";
		m_strShineDistance = "";

	}
}EncChannelInfo_t;

//远程通道信息
typedef struct DPSDK_API tagRemoteChannelInfo: public EncChannelInfo_t
{
	std::string					szName;	                	    // 设备ID
	std::string					szIP;	                	    // 设备IP
	int      					nPort;							// 端口
	int							nChnlNum;						// 通道号
	std::string					szUser;	                	    // 用户名
	std::string					szPassword;             	    // 密码
	dgp_dev_protocol_e			emProtocol;						// 协议类型
	int     					nDefinition;					// 清晰度, 0-标清, 1-高清
	int     					nVideoChannel;					// 视频输入通道数
	int     					nAudioChannel;					// 音频输入通道数

	tagRemoteChannelInfo()
	{
		szName = "";	   
		szIP = "";		
		nPort = 0;
		nChnlNum = 0;
		szUser = "";	   
		szPassword = "";		
		emProtocol = (dgp_dev_protocol_e)0;
		nDefinition = 0;
		nVideoChannel = 0;
		nAudioChannel = 0;

	}
}RemoteChannelInfo_t;

//卡口通道
typedef struct DPSDK_API tagBayChannelInfo:public EncChannelInfo_t
{
	std::vector<std::string>				m_vecLinkChl;
	std::string								m_strDirect;
	std::string								m_strRecLocation;				// 录像存储位置

	tagBayChannelInfo()
	{
		m_vecLinkChl.clear();
		m_strDirect = "";
		m_strRecLocation = "";
	}

}BayChannelInfo_t;

// 解码输出通道
typedef struct DPSDK_API  tagDecChannelInfo:public ChannelInfo_t
{
	int							nMaxSplitNum;					// 最大分割数，设备相关

	//通道所属的单元属性
	int							enumDecodeMode;					// 解码模式
	uint64_t    				m_nUintCapability;				// 能力集

	tagDecChannelInfo()
	{
		nMaxSplitNum = 0;
		enumDecodeMode = 0;
		m_nUintCapability = 0;
	}
}DecChannelInfo_t;

// 报警输入通道
typedef struct DPSDK_API tagAlarmInChannelInfo:public ChannelInfo_t
{
	int							nAlarmType;                      // 报警类型 参见数据字典表定义
	int							nAlarmLevel;                     // 报警等级 参见数据字典表定义
	
	tagAlarmInChannelInfo()
	{
		nAlarmLevel = 0;
		nAlarmType = 0;
	}
}AlarmInChannelInfo_t;
// 报警输出通道
typedef struct DPSDK_API tagAlarmOutChannelInfo:public ChannelInfo_t
{
	int							nAlarmType;                      // 报警类型 参见数据字典表定义Chnl_AlarmType_e
	
	tagAlarmOutChannelInfo()
	{
		nAlarmType = 0;
	}
}AlarmOutChannelInfo_t; 
// TvWall输入通道
typedef struct DPSDK_API tagTvWallInChannelInfo:public ChannelInfo_t
{
	std::string						m_strCtrlId;					// 键盘控制id
	camera_type_e	    			m_nCameraType;					// 类型，参见CameraType_e
	std::string						m_strChannelRemoteType;			// 远程通道类型， 范围是 本地编码通道，远程通道，级联通道，模拟矩阵通道 (值分别为1,2,3,4)

	tagTvWallInChannelInfo()
	{
		m_strCtrlId = "";
		m_nCameraType = (camera_type_e)0;
		m_strChannelRemoteType = "";
	}
}TvWallInChannelInfo_t;

// TvWall输出通道数据
typedef struct DPSDK_API tagTvWallOutChannelInfo : public ChannelInfo_t
{
	//通道所属的单元属性
	int          enumDecodeMode;  //解码模式

	tagTvWallOutChannelInfo()
	{
		enumDecodeMode = 0;
	}

}TvWallOutChannelInfo_t; 

// 门禁通道数据
typedef struct DPSDK_API tagDoorCtrlChannelInfo : public ChannelInfo_t
{
	std::string			strDoorType;
	//通道所属的单元属性
	int					iThirdControl;          //是否允许第三方控制 0否 1是
	int					iFingerPrintValidate;   //是否需要指纹验证 0否 1是
	uint64_t    		m_nUintCapability;				// 能力集


	tagDoorCtrlChannelInfo()
	{
		strDoorType = "";
		iThirdControl = 0;
		iFingerPrintValidate = 0;
		m_nUintCapability = 0;
	}

}DoorCtrlChannelInfo_t;

// 对讲通道数据
typedef struct DPSDK_API tagVoiceChannelInfo : public ChannelInfo_t
{
	std::string			strChnlCN;
	//通道所属的单元属性
	std::string			strVoiceIp;
	std::string			strClientIp;
	int					iVoicePort;
	int					iStatusPort;
	int					iVoiceMainSN;
	tagVoiceChannelInfo()
	{
		strChnlCN = "";
		strVoiceIp = "";
		strClientIp = "";
		iVoicePort = 0;
		iStatusPort = 0;
		iVoiceMainSN = 0;

	}
}VoiceChannelInfo_t;

//道闸设备通道数据
typedef struct DPSDK_API tagRoadGateChannelInfo : public ChannelInfo_t
{
	std::string			strSluiceType;

	tagRoadGateChannelInfo()
	{
		strSluiceType = "";
	}
}RoadGateChannelInfo_t;

//动环设备通道数据，又名PE
typedef struct DPSDK_API tagDynChannelInfo : public ChannelInfo_t
{
	std::string			strCode;
	std::string			strMapID;
	std::string			strLatitude;
	std::string			strLongitude;

	//所属的单元属性
	int					iDynType;
	std::string			strName;
	std::string			strDesc;
	std::string			strUnitCode;

	tagDynChannelInfo()
	{
		strCode = "";
		strMapID = "";
		strLatitude = "";
		strLongitude = "";
		iDynType = 0;
		strName = "";
		strDesc = "";
		strUnitCode = "";
		
	}

}DynChannelInfo_t;

// LED通道数据
typedef struct DPSDK_API tagLEDChannelInfo : public ChannelInfo_t
{
	int					iFreeParkingSpace;		// 剩余车位
	std::string			strLEDChnlDesc;			// 描述信息
	
	tagLEDChannelInfo()
	{
		iFreeParkingSpace = 0;
		strLEDChnlDesc = "";
	}

}LEDChannelInfo_t;

// 调度机通道数据 DISPATCHER
typedef struct DPSDK_API tagDispatcherChannelInfo : public ChannelInfo_t
{
	std::string			strCallNum;				// 话机号码

	tagDispatcherChannelInfo()
	{
		strCallNum = "";
	}

}DispatcherChannelInfo_t;

// MAC地址采集设备通道数据(预留) MACPICK
typedef struct DPSDK_API tagMacPickChannelInfo : public EncChannelInfo_t
{

}MacPickChannelInfo_t;

//通道信息集合
typedef struct DPSDK_API tagGroupChannelInfo
{
	std::vector<EncChannelInfo_t>		vec_EncChannelInfo;
	std::vector<RemoteChannelInfo_t>	vec_RemoteChannelInfo;
	std::vector<BayChannelInfo_t>		vec_BayChannelInfo;
	std::vector<DecChannelInfo_t>		vec_DecChannelInfo;
	std::vector<AlarmInChannelInfo_t>	vec_AlarmInChannelInfo;
	std::vector<AlarmOutChannelInfo_t>	vec_AlarmOutChannelInfo;
	std::vector<TvWallInChannelInfo_t>	vec_TvWallInChannelInfo;
	std::vector<TvWallOutChannelInfo_t>	vec_TvWallOutChannelInfo;
	std::vector<DoorCtrlChannelInfo_t>	vec_DoorCtrlChannelInfo;
	std::vector<VoiceChannelInfo_t>		vec_VoiceChannelInfo;
	std::vector<RoadGateChannelInfo_t>	vec_RoadGateChannelInfo;
	std::vector<DynChannelInfo_t>		vec_DynChannelInfo;
	std::vector<LEDChannelInfo_t>		vec_LEDChannelInfo;
	std::vector<DispatcherChannelInfo_t>	vec_DispatcherChannelInfo;
	std::vector<MacPickChannelInfo_t>	vec_MacPickChannelInfo;

	std::map<Dev_Unit_Type_e, int> mapChnlCount;			//每一单元下的所有通道总数 <单元类型, 单元下的通道总数>

	tagGroupChannelInfo()
	{
		vec_EncChannelInfo.clear();
		vec_RemoteChannelInfo.clear();
		vec_BayChannelInfo.clear();
		vec_DecChannelInfo.clear();
		vec_DecChannelInfo.clear();
		vec_AlarmInChannelInfo.clear();
		vec_AlarmOutChannelInfo.clear();
		vec_TvWallInChannelInfo.clear();
		vec_TvWallOutChannelInfo.clear();
		vec_DoorCtrlChannelInfo.clear();
		vec_VoiceChannelInfo.clear();
		vec_RoadGateChannelInfo.clear();
		vec_DynChannelInfo.clear();
		vec_LEDChannelInfo.clear();
		vec_DispatcherChannelInfo.clear();
		vec_MacPickChannelInfo.clear();
		mapChnlCount.clear();
	}
}GroupChannelInfo_t;
//设备信息
typedef struct DPSDK_API tagDeviceInfo
{
	std::string					szID;							// 设备ID
	std::string					szName;							// 名称
	std::string				    szManfac;						// 生产商
	std::string				    szModel;						// 模式
	std::string				    szUser;							// 用户名
	std::string				    szPassword;						// 密码
	std::string				    szIP;							// IP
	dev_type_e					nType;							// type
	int      				    nPort;							// port
	std::string					szLoginType;					// 登陆类型
	std::string					szLoginTypeEx;					// 登陆类型  <中行>
	std::string					szRegID;						// 主动注册设备ID
	int							nProxyPort;						// 代理端口
	int							nUnitNum;						// 单元数目--对于矩阵设备代表卡槽数
	int							m_nStatus;						// 设备状态
	std::string					szCN;							// 设备序列号
	std::string					szSN;							// 互联编码SN
	uint64_t 					nRight;							// 权限信息(只有IP对讲设备中的话筒才有)
	std::string					szDevIP;						// 设备真实IP
	int      					nDevPort;						// 设备真实port
	std::string					dev_Maintainer;         		// 设备联系人
	std::string					dev_MaintainerPh;       		// 设备联系人号码
	std::string					dev_Location;           		// 设备所在位置
	std::string					dev_LocalPolice;        		// 设备所在的派出所
	std::string					dev_baudRate;           		// 波特率
	std::string					dev_comCode;            		// com口序号
	std::string					desc;                   		// 设备描述
	std::string					szShopName;						// 店名
	std::string					szAddress;						// 店的地址
    std::string					szFirstOwner;					// 第一联系人姓名
	std::string					szFirstPosition;				// 第一联系人职务
	std::string					szFirstPhone;					// 第一联系人电话
	std::string					szFirstTel;						// 第一联系人座机
	int		 					nServiceType;					// 服务状态
	std::string					szOwnerGroup;					// 所属组织 
	std::string					szVideoType;					// 视频类型，南京高院需求
	std::string					szExpiredDate;					// 过期时间，<中行项目>
	std::string					szBelong;						//
	int							nRole;
	std::string					szDevModel;						// 设备型号
	std::string					szDevVersion;					// 固件版本
	std::string					szCallNum;						// 设备呼叫号码

	SortInfoMap					m_sortMap;						// 排序信息
	uint64_t					nModifyTime;					// 设备最后一次修改时间

	tagDeviceInfo()
	{
		szID = "";		
		szName = "";		
		szManfac = "";	
		szModel = "";	
		szUser = "";		
		szPassword = "";	
		szIP = "";				
		nType = (dev_type_e)0;	
		nPort = 0;							
		szLoginType = "";	
		szLoginTypeEx = "";	
		szRegID = "";
		nProxyPort = 0;						
		nUnitNum = 0;						
		m_nStatus = 0;	
		szCN = "";
		szSN = "";
		nRight = 0;				
		szDevIP = "";
		nDevPort = 0;	
		dev_Maintainer = ""; 
		dev_MaintainerPh = "";
		dev_Location = "";   
		dev_LocalPolice = "";
		dev_baudRate = "";   
		dev_comCode = "";    
		desc = "";           
		szShopName = "";		
		szAddress = "";		
		szFirstOwner = "";	
		szFirstPosition = "";
		szFirstPhone = "";	
		szFirstTel = "";		
		nServiceType = 0;
		szOwnerGroup = "";	
		szVideoType = "";	
		szExpiredDate = "";	
		szBelong = "";
		nRole = 0;
		szDevModel = "";		
		szDevVersion = "";	
		szCallNum = "";	

		m_sortMap.clear();
		nModifyTime = 0;
	
	}
}DeviceInfo_t;

typedef struct DPSDK_API tagAllDeviceInfo
{
	DeviceInfo_t	struDeviceInfo;				// 设备信息
	GroupChannelInfo_t struAllChannelInfo;		// 不同通道类型的通道信息

	tagAllDeviceInfo()
	{
		tagDeviceInfo();
		tagGroupChannelInfo();
	}

}AllDeviceInfo_t;

//加载组织组织上抛结构体
typedef struct DPSDK_API tagLoadOrgGroupInfo
{
	std::vector<AllOrg_Info_t>				vecOrgGroupInfo;		// 组织信息包含基本组织和多个逻辑组织
	std::map<std::string, AllDeviceInfo_t>	mapDevIdToDevInfo;		// 设备ID对应设备通道信息
	
	tagLoadOrgGroupInfo()
	{
		vecOrgGroupInfo.clear();
		mapDevIdToDevInfo.clear();
	}
}LoadOrgGroupInfo_t;

//增加组织上抛结构体
typedef struct DPSDK_API tagAddOrgGroupInfo
{
	std::vector<std::string>				vecOrgCodeId;		// 上抛组织节点ID数组

	tagAddOrgGroupInfo()
	{
		vecOrgCodeId.clear();
	}
}AddOrgGroupInfo_t;

//修改组织上抛结构体
typedef struct DPSDK_API tagModifyOrgGroupInfo
{
	std::vector<std::string>				vecOrgCodeId;		// 上抛组织节点ID数组

	tagModifyOrgGroupInfo()
	{
		vecOrgCodeId.clear();
	}
}ModifyOrgGroupInfo_t;

//获取设备信息上抛结构体
typedef struct DPSDK_API tagGetDeviceInfo
{
	std::vector<AllDeviceInfo_t> vecGetDeviceInfo;				// 设备信息数组
	
	tagGetDeviceInfo()
	{
		vecGetDeviceInfo.clear();
	}
}GetDeviceInfo_t;

//修改设备结构体
typedef struct tagModifyDeviceEx
{
	std::string			strDeviceId;							// 设备Id
	std::string			szOldCodeId;							// 原组织id 
	std::string			szNewCodeId;							// 新组织id 

	tagModifyDeviceEx()
	{
		strDeviceId = "";
		szOldCodeId = "";
		szNewCodeId = "";		
	}

}ModifyDeviceEx_t;

//修改设备 上抛结构体
typedef struct DPSDK_API tagModifyDevice
{
	std::vector<ModifyDeviceEx_t> vec_ModifyDevice;

	tagModifyDevice()
	{
		vec_ModifyDevice.clear();
	}

}ModifyDevice_t;

//增加/删除设备 上抛结构体(支持批量操作)
typedef struct DPSDK_API tagOperatorDevice
{
	std::map<std::string, std::vector<std::string> >	mapDeviceIdToOrgId;				// <组织ID, 设备ID>

	tagOperatorDevice()
	{
		mapDeviceIdToOrgId.clear();
	}
}OperatorDevice_t;

//通道权限变更上抛结构体
typedef struct DPSDK_API tagChannelRights 
{
	std::map<std::string, std::string> mapChlIdToChlRight;				// <通道ID, 通道权限>

	tagChannelRights()
	{
		mapChlIdToChlRight.clear();
	}
}ChannelRight_t;

// 加载组织树 DPSDK_CMD_MESSAGE_GET_ALL_ORG_TREE
class DPSDK_API GetAllOrgMsg : public DPSDKCBMessage
{
public:
	GetAllOrgMsg(void);
	virtual ~GetAllOrgMsg(void){}

public:
	//request
	int			nodeType;									// 参见dpsdk_getgroup_node_e
	int			operation;									// 参见dpsdk_getgroup_operation_e
	char		nodeId[DPSDK_ID_LEN];						// 节点ID 
	int         bSimplyDeviceTree;                          // 获取精简版设备树标志位：1 表示获取精简版 0 表示不获取精简版 
	LoadOrgGroupInfo_t m_struLoadOrgGroup;		// 组织节点信息

};

// 增加组织节点 DPSDK_CMD_MESSAGE_ADD_ORG
class DPSDK_API AddOrgMsg : public DPSDKCBMessage
{
public:
	AddOrgMsg(void);
	virtual ~AddOrgMsg(void){}

	AddOrgGroupInfo_t m_struAddOrg;		// 增加的组织节点信息

};


// 修改组织节点 DPSDK_CMD_MESSAGE_MODIFY_ORG
class DPSDK_API ModifyOrgMsg : public DPSDKCBMessage
{
public:
	ModifyOrgMsg(void);
	virtual ~ModifyOrgMsg(void){}

	ModifyOrgGroupInfo_t m_struModifyOrg;		// 组织节点信息

};

// 删除组织节点 DPSDK_CMD_MESSAGE_DELETE_ORG
class DPSDK_API DeleteOrgMsg : public DPSDKCBMessage
{
public:
	DeleteOrgMsg(void);
	virtual ~DeleteOrgMsg(void){}

	DeleteOrg_t m_struDeleteOrg;		// 组织节点信息

};

// 获取设备信息 DPSDK_CMD_MESSAGE_GET_DEVICE_INFO
class DPSDK_API GetAllDeviceInfoMsg : public DPSDKCBMessage
{
public:
	GetAllDeviceInfoMsg(void);
	virtual ~GetAllDeviceInfoMsg(void){}
public:
	//request
	std::vector<std::string> m_vecDeviceId;
	
	//response
	GetDeviceInfo_t m_struDeviceInfo;	// 设备信息

};

// 增加设备 DPSDK_CMD_MESSAGE_ADD_DEVICE
class DPSDK_API AddDeviceMsg : public DPSDKCBMessage
{
public:
	AddDeviceMsg(void);
	virtual ~AddDeviceMsg(void){}

	OperatorDevice_t m_struAddDevice;	// 

};

// 修改设备 DPSDK_CMD_MESSAGE_MODIFY_DEVICE
class DPSDK_API ModifyDeviceMsg : public DPSDKCBMessage
{
public:
	ModifyDeviceMsg(void);
	virtual ~ModifyDeviceMsg(void){}

	ModifyDevice_t m_struModifyDevice;	// 

};

// 删除设备 DPSDK_CMD_MESSAGE_DELETE_DEVICE
class DPSDK_API DeleteDeviceMsg : public DPSDKCBMessage
{
public:
	DeleteDeviceMsg(void);
	virtual ~DeleteDeviceMsg(void){}

	OperatorDevice_t m_struDeleteDevice;	// 

};

// 用户角色变更 DPSDK_CMD_MESSAGE_USER_ROLE_CHANGED
class DPSDK_API UserRoleChangedMsg : public DPSDKCBMessage
{
public:
	UserRoleChangedMsg(void);
	virtual ~UserRoleChangedMsg(void){}
};

// 角色组织变更 DPSDK_CMD_MESSAGE_ROLE_ORG_CHANGED
class DPSDK_API RoleOrgChangedMsg : public DPSDKCBMessage
{
public:
	RoleOrgChangedMsg(void);
	virtual ~RoleOrgChangedMsg(void){}
};

// 逻辑组织变更 DPSDK_CMD_MESSAGE_LOGIC_ORG_CHANGED
class DPSDK_API LogicOrgChangedMsg : public DPSDKCBMessage
{
public:
	LogicOrgChangedMsg(void);
	virtual ~LogicOrgChangedMsg(void){}
};

// 通道权限变更 DPSDK_CMD_MESSAGE_CHANNEL_RIGHT_CHANGED
class DPSDK_API ChannelRightChangedMsg : public DPSDKCBMessage
{
public:
	ChannelRightChangedMsg(void);
	virtual ~ChannelRightChangedMsg(void){}

	ChannelRight_t m_struChannelRightChanged;	// 

};


// 组织下挂节点变更 DPSDK_CMD_MESSAGE_CODEINFO_CHANGED
class DPSDK_API CodeInfoChangeMsg : public DPSDKCBMessage
{
public:
	// 组织下挂节点变更 DPSDK_CMD_MESSAGE_CODEINFO_CHANGED上抛的结构体
	typedef struct tagCodeInfoChange
	{
		std::string	strCodeId;			// <设备或通道>节点Id
		std::string	strNewOrgId;		// 节点所在的新组织Id
		std::string	strOldOrgId;		// 节点所在的旧组织Id	如果新旧组织Id一致，说明节点只是变更排序，未变换组织
		int			iNewSort;			// 节点在新的排序
		int			iOldSort;			// 节点在旧的排序
	}CodeInfoChange_t;

	CodeInfoChangeMsg(void);
	virtual ~CodeInfoChangeMsg(void){}

	std::vector<CodeInfoChange_t> m_vecCodeInfoChange;
};

class DPSDK_API GetGroupSnapshotMsg : public DPSDKCBMessage
{
public:
	GetGroupSnapshotMsg(void);
	virtual ~GetGroupSnapshotMsg(void){}

public:
	//request
	int			nodeType;									// 参见dpsdk_getgroup_node_e
	int			operation;									// 参见dpsdk_getgroup_operation_e
	char		nodeId[DPSDK_ID_LEN];						// 节点ID 
	//response
	std::string    orgData;									// 原始xml数据

};

class DPSDK_API GetDeviceDetailMsg : public DPSDKCBMessage
{
public:
	GetDeviceDetailMsg(void);
	virtual ~GetDeviceDetailMsg(void){}

public:
	//request
	std::vector<std::string> vecDeviceId;
	//response
	std::string   orgData;									// 原始xml数据

};

// 获取业务树消息
class DPSDK_API GetOrgDetailMsg : public DPSDKCBMessage
{
public:
	GetOrgDetailMsg(void);
	virtual ~GetOrgDetailMsg(void);

public:
	char						szCoding[DPSDK_ID_LEN];				// 节点编码
	int                         nNodeType;                          //
	dpsdk_get_org_depth_type_e	nDepthType;							// 类型

	char*						pszOrgTree;							// 业务树数据
	uint32_t					nLen;								// 数据长度
};
//end 新组织结构

enum FtpServer_ModuleType
{
	FTPSERVER_MODULETYPE_UNKNOW,
	FTPSERVER_MODULETYPE_ALARM_IMAGE,
	FTPSERVER_MODULETYPE_TAG_IMAGE,
	FTPSERVER_MODULETYPE_DOOR_IMAGE,
	FTPSERVER_MODULETYPE_TALK_FILE = 6,		//与协议保持一致，4,5被其他占用了
	FTPSERVER_MODULETYPE_FTP_SX,			//卷宗相关FTP服务,协议库中为FTPTYPE_CASE_FILE
	FTPSERVER_MODULETYPE_FTP_SX_P = 47,		//卷宗相关FTP服务,协议库中为FTPTYPE_CASE_FILE_P
	FTPTYPE_AUDIO_FILE	 =    62,
};

class DPSDK_API FtpServerInfoMsg : public DPSDKCBMessage
{
public:
	FtpServer_ModuleType ftpType;
	char url[DPSDK_TAG_URL_LEN];
	char user[DPSDK_USER_NAME_LEN];
	char pwd[DPSDK_PASSWORD_LEN];

	FtpServerInfoMsg ();
	~FtpServerInfoMsg (){}
};

//服务登录成功通知
class DPSDK_API ServerLoginNotifyMsg : public DPSDKCBMessage
{
public:
	int				m_nServerType; //DMS 4, ADS 16详细请参见协议库CFL_UNIT_TYPE（CFL_MsgDefine.h）
	char			m_szServerIP[DPSDK_IP_LEN];
	int				m_nServerPort;

	ServerLoginNotifyMsg();
	virtual ~ServerLoginNotifyMsg(){}
};

class DPSDK_API SetMaxPlayWndNumMsg : public DPSDKCBMessage
{
public:
	SetMaxPlayWndNumMsg(void);
	virtual ~SetMaxPlayWndNumMsg(void){};

public:
	uint64_t nMaxPlayWnd;
};

class DPSDK_API MessageRequestMsg : public DPSDKCBMessage
{
public:
	MessageRequestMsg(void);
	virtual ~MessageRequestMsg(void){};

public:
	int				iCode;								//见CFL_CU_MSG_TYPE
	uint64_t		uParam1;								
	uint64_t		uParam2;								
	char			szStrMsg1[DPSDK_CHAR_LEN_1024*3];		
	char			szStrMsg2[DPSDK_CHAR_LEN_1024*3];		
};

// 用户被强制登陆通知消息
class DPSDK_API LoginForcedNotifyMsg : public DPSDKCBMessage
{
public:
	LoginForcedNotifyMsg(void){ m_cmd = DPSDK_CMD_NOTIFY_LOGIN_FORCED;}
	virtual ~LoginForcedNotifyMsg(void){}
};

// 执法监督时间到，cms通知客户端
class DPSDK_API SuerviseNotifyMsg : public DPSDKCBMessage
{
public:
	SuerviseNotifyMsg(void);
	virtual ~SuerviseNotifyMsg(void){};

public:
	uint64_t		uId;								//ID
	uint64_t		uTime;								//时间
	char			szDeviceId[DPSDK_DEV_ID_LEN];		//设备ID
};

// 重连CMS
class DPSDK_API ReconnnectToCMSMsg : public DPSDKCBMessage
{
public:
	ReconnnectToCMSMsg(void);
	virtual ~ReconnnectToCMSMsg(void){};
};

class DPSDK_API ModifyLogoMsg : public DPSDKCBMessage
{
public:
	ModifyLogoMsg(void);
	virtual ~ModifyLogoMsg(void){};				                 
};

class DPSDK_API ModifyMenuRightMsg : public DPSDKCBMessage
{
public:
	ModifyMenuRightMsg(void);
	virtual ~ModifyMenuRightMsg(){};
};

class DPSDK_API ConnectToSCSMsg : public DPSDKCBMessage
{
public:
	ConnectToSCSMsg(void);
	virtual ~ConnectToSCSMsg(void){}

	char	szScsIp[DPSDK_IP_LEN];						//SC服务IP
	int		nScsPort;									//SC服务端口
	char	szCallNumber[DPSDK_PHONE_LEN];				//呼叫号码
};

// 根据工地号获取通道ID列表
class GetChnlIdBySiteCodeMsg : public DPSDKCBMessage
{
public:
	GetChnlIdBySiteCodeMsg(void);
	virtual ~GetChnlIdBySiteCodeMsg(void);
public:
	int							nSiteCode;

	int							nChnlIdCount;
	std::string*				pStrChnlId;
};

//////////////////////////////////////////////////////////////////////////

class DPSDK_API IDPSDKGeneral : public IDPSDKFuncBase
{
public:

	/*
	\brief: 向某个模块发送一个通用的json串
	\param[in] jdata       需要发送出去的json串
	\param[in] mdltype     模块的id,用来指明消息是发给哪个服务,e.g.:cms, dms等
	*/
	virtual int GeneralJsonTransport( dsl::Json::Value& jdata, dpsdk_mdl_type_e mdltype, generaljson_trantype_e trantype ) = 0;

	/** 发送登陆请求，判断是否需要加密认证
	    @param const char* remoteIp							服务IP
	    @param int remotePort								服务端口
	    @param const char* username							用户名
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	//virtual int PreLogin(const char* remoteIp, int remotePort, const char* username, const char* password) = 0;
	
	/** 手机或者电脑登录平台
	    @param Login_Info_t* LoginInfo						用户登录信息
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int Login(const Login_Info_t &LoginInfo) = 0;

	/** 手机或者电脑单点登录平台
	    @param Login_Info_t* LoginInfo						用户登录信息
		@param bSingleLogin									是否单点登录
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int Login(const Login_Info_t& LoginInfo, bool bSingleLogin) = 0;

	/** 电脑登录平台
	    @param const char* remoteIp							服务IP
	    @param int remotePort								服务端口
	    @param const char* username							用户名
	    @param const char* password							用户密码
		@paramclient_login_type_e loginType					登录类型，默认为PC客户端
		@param  bool bPasswordPlaintext						加密登录时，是否仍然透传密码明文，默认false
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int Login(const char* remoteIp, int remotePort, const char* username, const char* password, client_login_type_e loginType = PC_CLIENT, bool bPasswordPlaintext = false, bool bSingleLogin = false) = 0;

	/** 加密方式登录平台
	    @param const char* remoteIp							服务IP
	    @param int remotePort								服务端口
	    @param const char* username							用户名
	    @param const char* password							用户密码
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	//virtual int LoginWithEncryption(const char* remoteIp, int remotePort, const char* username, const char* password) = 0;


	/** 登出平台
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int Logout(void) = 0;

	/** 登出平台,配合优化后的异步转同步机制接口，内部不产生sequence
	    @return												执行结果
	*/
	virtual int Logout( int nSeq ) = 0;


	/** 获取组织/设备信息
	    @param const char* nodeId							设备ID或组织coding(根节点为001)
		@param dpsdk_getgroup_node_e nodeType				
		@dpsdk_getgroup_operation_e operation				
		@int bSimplyDeviceTree                              获取精简版设备树标志位：1 表示获取精简版 0 表示不获取精简版     
		@return												异步顺序码,用于事件回调时,与应答事件匹配
		@remark												此接口支持上层“增量式”获取信息,故将此接口暴露而未隐藏。获取到的信息暂存于SDK，需调用GetGroupInfo访问。
	*/
	virtual int GetGroup(const char* nodeId, dpsdk_getgroup_node_e nodeType, dpsdk_getgroup_operation_e operation, int bSimplyDeviceTree = 0 ) = 0;

	/** 获取组织/设备 数据信息
	    @return												组织/设备的数据结构封装						
	    @see												DGroupParser / GetGroup
		@remark												此方法为同步过程；数据的内容依赖于SDK底层对“设备/组织”信息的累积；累积过程主要是由 上层主动的"GetGroup"调用和来自远端的被动通知 触发的。									
	*/
	virtual DGP::DGroupParser* GetGroupInfo(void) = 0;

	/** 获取设备信息(支持批量获取)
	    @param const char* nodeId							设备ID
		@return												异步顺序码,用于事件回调时,与应答事件匹配
		@remark												此接口支持上层“增量式”获取信息,故将此接口暴露而未隐藏。获取到的信息暂存于SDK，需调用GetGroupInfo访问。
	*/
	virtual int GetDeviceInfo(std::vector<std::string> vecDeviceId) = 0;

	/** 获取组织快照
	    @param const char* nodeId							设备ID或组织coding(根节点为001)
		@param dpsdk_getgroup_node_e nodeType				
		@dpsdk_getgroup_operation_e operation				
		@return												异步顺序码,用于事件回调时,与应答事件匹配
		@remark												此接口支持上层分层获取组织信息
	*/
	virtual int GetGroupSnapshot(const char* nodeId, dpsdk_getgroup_node_e nodeType, dpsdk_getgroup_operation_e operation) = 0;

	/** 获取设备详细信息
	    @param std::vector<std::string> vecDeviceId			设备ID
		@return												异步顺序码,用于事件回调时,与应答事件匹配
		@remark												此接口支持上层分层获取组织信息
	*/
	virtual int GetDeviceDetail(std::vector<std::string> vecDeviceId) = 0;

	/** 获取组织/设备 数据信息
	    @return												组织/设备的数据结构封装						
	    @see												DGroupParser / GetDeviceList
		@remark												此方法为同步过程；数据的内容依赖于SDK底层对“设备/组织”信息的累积；累积过程主要是由 上层主动的"GetGroup"调用和来自远端的被动通知 触发的。									
	*/
	virtual DGP::DGroupParser* GetDeviceListInfo(void) = 0;

	/** 获取组织/设备 数据信息
	    @return												组织/设备的数据结构封装						
	    @see												DGroupParser / GetDevicesInfo
		@remark												此方法为同步过程；数据的内容依赖于SDK底层对“设备/组织”信息的累积；累积过程主要是由 上层主动的"GetGroup"调用和来自远端的被动通知 触发的。									
	*/
	virtual DGP::DGroupParser* GetDevicesDetailInfo(void) = 0;

	/** 获取用户文件
		@param const char* szFileName						
	    @return												
	*/
	virtual int GetOwnerFile(const char* szFileName, int nUserId = -1) = 0;

	/** 保存用户文件
		@param const char* szFileName						
		@param const char* pData							
		@param int nLen		
		@param int nFileType								保存文件的类型 0 普通文件， 1电视墙任务
		@param int nTvWallID								当nFileType=1时有效，为电视墙ID
		@param int nTaskId									当nFileType=1时有效，为任务ID
		@param char* szDesc									当nFileType=1时有效，为任务描述
		@param int iSortId									任务排序号
	    @return												
	*/
	virtual int SaveOwnerFile(const char* szFileName, const char* pData, int nLen, int nFileType = 0, uint32_t nTvWallID = 0, uint32_t nTaskId = 0, char* szDesc = 0, int nUserId = -1, int iSortId = -1) = 0;

	/** 上传巡检任务
		@param uint32_t userId								用户ID					
		@param char* startTime								巡检任务开始时间					
		@param char* endTime								巡检任务结束时间
		@param unsigned int totalNum						巡检总数
		@param unsigned int finishNum						已经完成数
		@param unsigned int offlineNum						通道离线数
		@param const char* pData							通道ID记录
		@param const int nLen								data的长度
	    @return												
	*/
	virtual int SaveRoutingFile(uint32_t userId, int64_t startTime, int64_t endTime, unsigned int totalNum,
		unsigned int finishNum,unsigned int offlineNum,const char* pData, int nLen) = 0;

	/** 获取配置信息或平台版本等
		@param dpsdk_getconfig_e type												
	    @return												
	*/
	virtual int GetConfigInfo(dpsdk_getconfig_e type) = 0;

	/** 配置全网校时开关
		@param bool bOpen	true:开启校时功能；false:关闭校时功能
	    @return												
	*/
	virtual int SetSyncTimeOpen(bool bOpen) = 0;

	/** 保存操作员日志
	    @param const char* cameraId							相机id
		@param int64_t optTime								操作时间
		@param dpsdk_log_optType_e optType					操作类型
		@param const char* optDesc							操作描述
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SaveOptLog(const char* cameraId, int64_t optTime, dpsdk_log_optType_e optType, const char* optDesc) = 0;

	/** 系统配置信息（网络配置、报警日志保存时间配置）
	    @param dpsdk_system_config_e type					
		@param dpsdk_system_config_union configInfo			
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
		@remark												m_pPSDK->Init();之前设置网络参数
	*/
	virtual int SetSystemConfig(dpsdk_system_config_e type, dpsdk_system_config_union configInfo) = 0;
	
	/** 获取模块权限
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetMenuRight(void) = 0;

	/** 获取指定用户指定模块权限
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetFunRight(const char *userName, const char *password, int right) = 0; //EnumMenuRight

	/** 读取双目组织节点定位信息
	    @param const char* szCoding							组织结构ID					
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
		@remark												m_pPSDK->Init();之前设置网络参数
	*/
	virtual int LoadMCailInfo(const char* szCoding) = 0;

	/** 保存双目组织节点定位信息
	    @param const char* szCoding							组织结构ID	
		@param const char* pData
		@param int nLen
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
		@remark												m_pPSDK->Init();之前设置网络参数
	*/
	virtual int SaveMCailInfo(const char* szCoding, const char* pData, int nLen) = 0;
	
	/** Ftp操作函数
	    @param const char* szLocalFile						本地文件路径	
		@param const char* szFtpFile						FTP文件路径
		@param const char* szName							FTP用户名
		@param const char* szPwd							FTP操作类型
		@param dpsdk_operator_ftp_type_e optype				操作类型
		@param dpsdk_ftp_transport_mode_e mode				文件传输模式
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int OperatorFtpFile(const char* szLocalFile, const char* szFtpFile, const char* szName, const char *szPwd, dpsdk_operator_ftp_type_e optype, dpsdk_ftp_transport_mode_e mode = MODE_EPSV) = 0;

	///** 设置FTP文件传输模式
	//	
	//	@param dpsdk_ftp_transport_mode_e mode				文件传输模式
	//    @return												异步顺序码,用于事件回调时,与应答事件匹配
	//*/
	//virtual int SetFtpTransportMode(dpsdk_ftp_transport_mode_e mode = MODE_EPSV) = 0;

	/** 获取用户组织结构											
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetUserOrgInfo(void) = 0;

	/** 获取用户部门组织结构											
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetUserDepOrgInfo(void) = 0;

	/** 视频分享			
	    @param ShareVideoInfo* pVideoInfo					视频信息	
		@param int nVideoCount								视频个数
		@param int* pUserId									用户ID
		@param int nUserCount								用户ID个数	
		@param const char* szMsg							描述信息				
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int ShareVideo(ShareVideoInfo* pVideoInfo, int nVideoCount, int* pUserId, int nUserCount, const char* szMsg) = 0;

	/** 保存图片信息			
	    @param const char* szCamId							通道ID
		@param int64_t	nOptTime							抓图时间
		@param const char* szReason							抓图原因
		@param const char* szAlarmCode						报警编号
		@param const char* szRemark							备注	
		@param const char* szUrl							图片路径				
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SaveUploadPictureInfo(UploadPictureInfo& stuInfo) = 0;

	/** 获取用户权限
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int AskForUserAuthority() = 0;

	/*获取全网校时时间*/
	virtual int AskForSystemTime() = 0;
	
	/** 修改用户密码			
	    @param const uint32_t nUserId						用户ID
		@param const char* szOldPsw							原有密码
		@param const char* szNewPsw							新密码
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int ChangeUserPassword(const uint32_t nUserId, const char* szOldPsw, const char* szNewPsw) = 0;

	virtual int MakeSequence(void) = 0;

	virtual int GetSleepInfo() = 0;

	virtual int SaveSleepInfo(int32_t iParam1, int32_t iParam2,const char* strMsg1, const char* strMsg2) = 0;
	
	/** 客户密码修改
		@return												异步顺序码,用于事件回调时,与应答事件匹配
		@remark
		*/
	virtual int ChangeUserPassword(const char* oldPass, const char* newPass) = 0;
    
	/**获取组员所属的组长信息列表
	*/
	virtual int GetGroupLeadersInfo() = 0;

	/** 目录检索			
	    @param const char* szCamId							域ID		
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int DirSearch(const char* szCoding) = 0;

	/** 获取平台使用到期时间				
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetLicenseExpireTime() = 0;

	/** 获取本地IP
	    @return												本地IP					
		@remark												此方法为同步过程；数据的内容依赖于SDK底层对CMS的登陆									
	*/
	virtual void GetLocalIp(char* szLocalIP, int nLen) = 0;

	/** 获取组织/设备信息
		@param dpsdk_org_node_e    nodeType					查询节点类型
		@param dpsdk_org_node_subtype_e subType				查询节点子类型
		@return												异步顺序码,用于事件回调时,与应答事件匹配
		@remark												此接口支持上层“增量式”获取信息,故将此接口暴露而未隐藏。获取到的信息暂存于SDK，需调用GetGroupInfo访问。
	*/
	virtual int GetGroupByType(const char* szCode, dpsdk_org_node_e type, dpsdk_org_node_subtype_e subType) = 0;

	/** 获取服务信息
     	@param dpsdk_server_type_info_e						查询类型
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetServerInfo(dpsdk_server_type_info_e type) = 0;
	
	/** 华鼎项目：查询设备信息
	    @param const char* devId							设备ID							
	    @return												
	*/
	virtual int QueryHDDeviceInfo(const char* devId) = 0;

	/** 华鼎项目：查询设备状态
	    @param const char* devId							设备ID							
	    @return												
	*/
	virtual int QueryHDDeviceStatus(const char* devId) = 0;

	/** 华鼎项目：查询平台单元流量
	    @param const char* depId							组织结构ID							
	    @return												
	*/
	virtual int QueryHDPlatformFlow(const char* depId) = 0;

	//**安徽朗坤
	
	/** 查询ftp默认路径下的图片			
	    @param ChalInfo_t* pChlInfo							通道列表
		@param int size										通道数量
		@param int64_t nBeginTime							开始时间
		@param int64_t nEndTime								结束时间				
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryFtpPic(Chal_Info_t* pChlInfo, int size, int64_t nBeginTime, int64_t nEndTime) = 0;

	/** 删除ftp图片			
	    @param FtpPicInfo_t* pPicInfo						图片路径列表
		@param int size										图片列表大小
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int DelFtpPic(Requ_Ftp_Pic_Info_t* pPicInfo, int size) = 0;

	/** 获取设备列表信息
	    @param const char* nodeId							设备ID或组织coding(根节点为001)
		@param dpsdk_getgroup_node_e nodeType				
		@dpsdk_getgroup_operation_e operation				
		@return												异步顺序码,用于事件回调时,与应答事件匹配
		@remark												此接口支持上层“增量式”获取信息,故将此接口暴露而未隐藏。获取到的信息暂存于SDK，需调用GetGroupInfo访问。
	*/
	virtual int GetDeviceList(const char* nodeId /*= "001"*/,dpsdk_getgroup_node_e nodeType /*= DPSDK_GEN_GETGROUP_NODE_ALL*/, dpsdk_getgroup_operation_e operation /*= DPSDK_GEN_GETGROUP_OPERATION_ALL*/) = 0;

	/** 获取设备列表
	    @param char[][DPSDK_DEV_ID_LEN] szDevicesId 		多个设备ID的数组
		@param int nDevicesCount                    		设备ID数组的大小
	*/
	virtual int GetDevicesInfo(const char szDevicesId[][DPSDK_DEV_ID_LEN], int nDevicesCount) = 0;

	/** 获取服务器Ip列表
		@param void* pServerIpList							服务器列表信息
	*/
	virtual int GetServerIpList(void* pServerIpList) = 0;
	
	/** 社会报警平台，向CMS发起改变处警状态			
		@param std::string* strReceiptAlarmID				事件编号
		@param int nStatus									事件状态
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SetPoliceStatus(std::string strReceiptAlarmID, int nStatus) = 0;

	/** 获取超级市场配置信息SPM
	 * @para: 
	 * @return:
	 */
	virtual int GetServerSPMConfig() = 0;

	/** 修改用户密码
		@param int nUserId									用户ID
		@param const char* szOldPwd							旧密码
		@param const char* szNewPwd							新密码
		@return
	*/
	virtual int ChangeUserPassword(int nUserId, const char* szOldPwd, const char* szNewPwd) = 0;
	
	/** 保存上传文件信息
		@param const char* szJson							文件信息Json串
		@param int	nLen									Json串长度		
		@return												异步顺序码,用于事件回调时,与应答事件匹配	
	*/
	virtual int SaveUploadFileInfo(const char* szJson, int nLen) = 0;

	/** 上传文件		
		@param const char* url								
		@param const char* path						
		@return												异步顺序码,用于事件回调时,与应答事件匹配	
	*/
	virtual int UploadRemoteFile(const char* url, const char* path) = 0;

	/** 给CMS校时		
		@return												异步顺序码,用于事件回调时,与应答事件匹配	
	*/
	virtual int SyncTimeToCms(void) = 0;
	
	/** 获取FTP用户名&密码	
		@param char* szUser									输出用户名
		@param int nUserLen									用户名长度	
		@param char* szPwd									输出密码	
		@param int nPwdLen									密码长度		
		@remark												此方法为同步过程；数据的内容依赖于SDK底层对CMS的登陆									
	*/
	virtual int GetFtpUserInfo(char* szUser, int nUserLen, char* szPwd, int nPwdLen) = 0;

	/** 应到人数/实到人数 数据上报消息
	    @param const char* nUserId							用户ID
	    @param const char* nPlanNum							应到人数
	    @param const char* nRealNum							实到人数
	    @param int64_t upOptTime							上报时间
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int UploadPeopleNum(const char* nUserId, const char* nPlanNum, const char* nRealNum, int64_t upOptTime) = 0;

	/** 获取电子地图车辆图标配置
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetEmapCarIconType() = 0;

	/** 与cms模块交互的json通用协议
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GeneralJsonSendToCMS(std::string& strJsonToCMS) = 0;

	/*可视对讲获取电话号码*/
	virtual void GetCallNum(char* szCallNum, int nLen) = 0;

	/*
	\brief: 向某个模块发送一个透传数据
	\param[in] szData		需要发送出去的数据
	\param[in] mdltype		模块的id,用来指明消息是发给哪个服务,e.g.:cms, dms等
	\param[in] szCamId		对应通道号
	\param[in] bSave		是否保存msg,目前不支持保存msg
	*/
	virtual int SendDataToMdl( const std::string szData, const dpsdk_mdl_type_e mdltype, const BOOL bSave = FALSE , const std::string szCamId = "" ) = 0;

	/** 获取ftp相对路径
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetFtpRelativePath(FtpServer_ModuleType ftpType = FTPSERVER_MODULETYPE_ALARM_IMAGE) = 0;

	/** 重连CMS
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int ReconnectToCMS() = 0;

	/** 向CMS查询服务列表(宁波公安项目定制，不加载组织结构，控制云台)
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryServerList() = 0;

	/**	主动连接SCS服务，如果DPSDK已经连接上SCS服务，该接口无效
		@param const char* szScsIp							SCS服务IP
		@param int nScsPort									SCS服务端口
		@param const char* szCallNumber						呼叫号码
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int ConnectToSCS(const char* szScsIp, int nScsPort, const char* szCallNumber = NULL) = 0;

	virtual int GetOrgTree(const char* szCoding, int nNodeType, int nDepthType) = 0;

	/** 通过工地号获取通道ID
	    @param int nSiteCode								工地号
	    @return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetChnlIdBySiteCode(int nSiteCode) = 0;

	virtual int SetSaveGroupFilePath(const char* szFilePath) = 0;

	//************************************
	// Method:    GetHttpsConfig
	// FullName:  DPSdk::IDPSDKGeneral::GetHttpsConfig
	// Access:    virtual public 
	// Returns:   -1未配置,0http,1https
	//************************************
	virtual int GetHttpsConfig() = 0;
protected:
	virtual ~IDPSDKGeneral(void){}
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif

