/**
 * Copyright (c) 2013, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,PEC子模块
 *
 * 当前版本：1.0
 * 原作者　：12760
 * 完成日期：
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKPEC_H
#define INCLUDED_DPSDK_DPSDKPEC_H

#include "DPSDK.h"
// #include <map>
#include <vector>
#include <list>
#include <string>

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

typedef enum
{	
	PE_DOORCTRL = 1,		
	PE_ALARMHOST,
	PE_PEDEVICE,
	PE_POWERGRID,			// 4电网
	PE_DISPACHER = 10,		// 10指挥调度
	PE_BROADCAST = 12,		// 12广播
}dpsdk_pedev_type_e;

typedef enum
{
	DEFENCE_ALL,
	DEFENCE_ONE,
}dpsdk_alarmhost_defence_e;

typedef enum
{
	AHOST_OPERATE_DEVICE			= 1,		// 设备 布/撤防
	AHOST_OPERATE_CHANNEL			= 2,		// 通道 布/撤防
	AHOST_OPERATE_CHANNEL_ALARMOUT	= 3,		// 报警输出通道操作
	AHOST_OPERATE_CHANNEL_DOOR		= 4,		// 门禁通道操作
}dpsdk_alarmhost_opttype_e;

//报警配置命令类型,与协议定义相同
typedef enum
{
	AHOST_CMD_TYPE,
	AHOST_CMD_ENABLE = 1,						// 报警主机布防
	AHOST_CMD_DISABLE,							// 报警主机撤防
	AHOST_CMD_BYPASS,							// 报警主机旁路
	AHOST_CMD_CANCELKBLIGHT,					// 取消键盘指示灯显示
	AHOST_CMD_ALARMMODE,						// 设置报警主机取消报警是自动的还是客户端手动取消
	AHOST_CMD_CANCELALARM,						// 取消报警上报
	AHOST_CMD_ALARMOUT_ON,						// 报警主机输出通道打开
	AHOST_CMD_ALARMOUT_OFF,						// 报警主机输出通道关闭
	AHOST_CMD_DOOR_OPEN,						// 门禁通道开启
	AHOST_CMD_DOOR_CLOSE,						// 门禁通道关闭
	AHOST_CMD_DOOR_AUTO,						// 门禁通道自动
	AHOST_CMD_DOOR_ALWAYS_OPEN,					// 门禁通道常开
	AHOST_CMD_DOOR_ALWAYS_CLOSE,				// 门禁通道常关
}dpsdk_alarmhost_cmd_e;

typedef enum
{  
	AHOST_TYPE_NONE			= 0,
	AHOST_TYPE_STAY			= 1,				// 留守布防
	AHOST_TYPE_BYPASS,							// 防区旁路
	AHOST_TYPE_DOOR_AUTO,						// 门禁通道自动
	AHOST_TYPE_DOOR_ALWAYS_OPEN,				// 门禁通道常开
	AHOST_TYPE_DOOR_ALWAYS_CLOSE,				// 门禁通道常关
	AHOST_TYPE_ALARMOUT_CLOSE,					// 报警输出通道关闭
	AHOST_TYPE_ALARMOUT_OPEN,					// 报警输出通道打开
	AHOST_TYPE_ALARM,							// 报警输入报警
	AHOST_TYPE_ALARMIN_STATUS,					// 报警输入通道状态
}dpsdk_alarmhost_report_type_e;

typedef enum
{  
	BROADCAST_TYPE_BREAKDOWN	= 1500,			// 业翔广播故障消息
	BROADCAST_TYPE_PLAY_STATUS	= 1501,			// 业翔广播播放状态消息
}dpsdk_broadcast_report_type_e;

//门禁编程命令类型,与协议定义相同
typedef enum 
{
	DOOR_CMD_PROGARM,
	DOOR_CMD_OPEN			= 5,				// 开门
	DOOR_CMD_CLOSE			= 6,				// 关门
	DOOR_CMD_ALWAYS_OPEN,						// 门常开
	DOOR_CMD_ALWAYS_CLOSE,						// 门常关
	DOOR_CMD_HOLIDAY_MAG_OPEN,					// 假日管理门常开
	DOOR_CMD_HOLIDAY_MAG_CLOSE,					// 假日管理门常关
	DOOR_CMD_RESET,								// 复位
	DOOR_CMD_HOST_ALWAYS_OPEN,					// 报警主机下的门禁通道，常开
	DOOR_CMD_HOST_ALWAYS_CLOSE,					// 报警主机下的门禁通道，常关
}dpsdk_door_cmd_e;	

typedef enum
{
	Door_Close,
	Door_Open,
	Door_DisConn,
	Door_Auto,						// 门禁通道自动
	Door_Always_Open,				// 门禁通道常开
	Door_Always_Close,				// 门禁通道常关
}dpsdk_door_status_e;

typedef enum
{
	LINKRES_ADD				= 1,				// 增加
	LINKRES_MOD				= 2,				// 修改
	LINKRES_DEL				= 3,				// 删除
	LINKRES_REGET			= 4,				// 重新获取
}dpsdk_linkres_change_type;

//道闸编程命令类型,与协议定义相同  暂定与门禁值控制一样
typedef enum 
{
	ROADGATE_CMD_PROGARM,
	ROADGATE_CMD_OPEN			= 5,			// 开闸
	ROADGATE_CMD_CLOSE			= 6,			// 关闸
	
}dpsdk_roadgate_cmd_e;

typedef enum
{
	Dispacher_Chnl_Offline		= 0,			// 离线
	Dispacher_Chnl_Online		= 1,			// 在线（已注册，空闲）
	Dispacher_Chnl_Call_Invite	= 2,			// 呼叫请求中
	Dispacher_Chnl_Ring_Invite	= 3,			// 振铃请求中
	Dispacher_Chnl_Ring			= 4,			// 振铃
	Dispacher_Chnl_Ring_Back	= 5,			// 回铃音
	Dispacher_Chnl_Calling		= 6,			// 主叫通话
	Dispacher_Chnl_Called		= 7,			// 被叫通话
	Dispacher_Chnl_HoldOn		= 8,			// 保持
	Dispacher_Chnl_Busy			= 9,			// 忙碌
	Dispacher_Chnl_Monitor		= 10,			// 监听
}dpsdk_dispacher_chnl_status_e;

//存放公用数据
class DPSDK_API PesBaseMsg : public DPSDKCBMessage
{
public:
	PesBaseMsg( int cmd = DPSDK_CMD_UNKNOWN,int msgType = DPSDK_MSG_REQUEST);
	~PesBaseMsg(){}

	char	szId[DPSDK_CHL_ID_LEN];				// 设备/通道ID
};

class DPSDK_API SetDoorCmdMsg : public PesBaseMsg
{
public:
	SetDoorCmdMsg(void);
	virtual ~SetDoorCmdMsg(void){}

public:
	dpsdk_door_cmd_e cmd;
	int64_t startTime;
	int64_t endTime;
};

class DPSDK_API SetAHostMsg : public PesBaseMsg
{
public:
	SetAHostMsg(void);
	virtual ~SetAHostMsg(void){}

public:
	dpsdk_alarmhost_opttype_e type;
	dpsdk_alarmhost_cmd_e cmd;
	int64_t startTime;
	int64_t endTime;
};

typedef struct DPSDK_API tagAHostDefenceStatus
{
	char szNodeID[DPSDK_CHL_ID_LEN];			// 防区节点ID
	int  nAlarm;								// 0表示未报警 1104表示报警 1105表示火警 1106表示防
	int  nUndefendAlarm;						// 0表示没有未布防报警 83表示未布防报警（由于24小时防区会出现布防报警和未布防报警并发的情况 所以需要区分一下）
	bool bByPass;								// true=旁路, false=未旁路
	bool bDefend;								// true=布防, false=撤防
	tagAHostDefenceStatus()
	{
		memset(szNodeID, 0, sizeof(szNodeID));
		nAlarm =  0;
		nUndefendAlarm = 0;
		bByPass = false;
		bDefend = false;
	}
}AHostDefenceStatus_t;

class DPSDK_API QueryDefInfoMsg : public PesBaseMsg
{
public:
	QueryDefInfoMsg(void);
	virtual ~QueryDefInfoMsg(void);

public:
	dpsdk_alarmhost_defence_e	deftype;
	
	//respone
	AHostDefenceStatus_t*		pDefence;
	int							defenceNum;
};

typedef struct DPSDK_API tagAHostDevInfo
{    
	char	szId[DPSDK_CHL_ID_LEN];				// 报警主机设备ID
	int		nOptType;							// dpsdk_alarmhost_opttype_e
	bool	bBypassEnable;						// 是否支持旁路
	int		nReserved;							// 保留

	tagAHostDevInfo()
	{
		memset(szId,0,DPSDK_CHL_ID_LEN);
		nOptType = AHOST_OPERATE_DEVICE;
		bBypassEnable = true;
		nReserved = 0;
	}
}AHostDevInfo_t;

class DPSDK_API QueryAHostAbilityMsg : public PesBaseMsg
{
public:
	QueryAHostAbilityMsg(void);
	virtual ~QueryAHostAbilityMsg(void){}

	//respone
	AHostDevInfo_t aHostInfo;
};

typedef struct DPSDK_API tagDoorInfo
{    
	char	szChnId[DPSDK_CHL_ID_LEN];	
	int		doorStatus;

	tagDoorInfo()
	{
		memset(szChnId,0,DPSDK_CHL_ID_LEN);
		doorStatus = Door_Close;
	}
}DoorInfo_t;

class DPSDK_API QueryDoorInfoMsg : public PesBaseMsg
{
public:
	QueryDoorInfoMsg(void);
	virtual ~QueryDoorInfoMsg(void);

	//respone
	DoorInfo_t*		pDoorInfo;
	int				nDoorNum;
};

struct  DPSDK_API EnvInfo
{
	EnvInfo()
	{
		dataType = 1;
		dataLen = 0;
		memset(data, 0, DPSDK_CHAR_LEN_1024);
	}
	int		dataType;					// 数据类型，1-int，2-double，3-string
	int		dataLen;					// 数据实际长度
	char	data[DPSDK_CHAR_LEN_1024];	// 环境量数据
										// "%s^%d^%d^%d" channelID alrmType byPass defend (通道 报警 旁路? 布防?)
										// "%d^%d^%d^%d" deviceID alrmType bypassEnable reserved (设备 报警 支持旁路? 保留)
										// "%s^%d" channelID doorState (通道 状态)
};

class DPSDK_API EnvQueryMsg : public PesBaseMsg
{
public:
	EnvQueryMsg(void);
	virtual ~EnvQueryMsg(void);

	//request
	int			devType;					// 设备类型：1-门禁 2-报警主机 3-采集器 101-门禁信息 102-卡信息 103-报警信息
	int			subType;					// 环境量类型：
											// _devType=103时： 1-查询所有通道 2-查询单一通道 3-查询设备状态
											// _devType=103时： 1-查询所有通道 2-查询单一通道 
											// _subType=10, 查询所有通道
											// _subType=11, 查询单一通道

	uint32_t	startTime;					// 开始时间
	uint32_t	endTime;					// 结束时间

	//respone
	std::list<EnvInfo>	envList;
};


class DPSDK_API PecDevStatusNotifyMsg : public DPSDKCBMessage
{
public:
	PecDevStatusNotifyMsg(void);
	virtual ~PecDevStatusNotifyMsg(void){}

public:
	char			szDevId[DPSDK_DEV_ID_LEN];		// 设备ID
	int				status;							// 状态。1在线，2断线 ,256电网供电,512电网断电
	int				cuStat;							// 客户端状态。 0 客户端登录， 1 客户端在线上报
};

class DPSDK_API DCtrlReportMsg : public DPSDKCBMessage
{
public:
	DCtrlReportMsg(void);
	virtual ~DCtrlReportMsg(void){}

public:
	char				szCameraId[DPSDK_CHL_ID_LEN];
	dpsdk_door_status_e doorStatus;
	int64_t				time;

};

class DPSDK_API AHostReportMsg : public DPSDKCBMessage
{
public:
	AHostReportMsg(void);
	virtual ~AHostReportMsg(void){}

public:
	char							szId[DPSDK_CHL_ID_LEN];
	dpsdk_alarmhost_report_type_e	rType;
	dpsdk_alarmhost_opttype_e		optType;		// 对于报警主机状态上报可能是设备id或cameraid
	int								status;			// 对于防区状态1布防2撤防 对于旁路状态1旁路2未旁路
	int64_t							time;
};

//业翔广播状态上报
class DPSDK_API BroadCastReportMsg : public DPSDKCBMessage
{
public:
	BroadCastReportMsg(void);
	virtual ~BroadCastReportMsg(void){}

public:
	char							szCameraId[DPSDK_CHL_ID_LEN];
	dpsdk_broadcast_report_type_e	rType;
	int								status;			// 对于业翔对讲通道故障消息 1产生 2消失；对于业翔对讲通道播放状态 1播放 2停止
	int64_t							time;
};

typedef struct DPSDK_API realDataInfo
{
	char        chnId[DPSDK_CHL_ID_LEN];
	char        time[DPSDK_CHL_ID_LEN];
	int         isAlarm;							// 0实时数据，1告警
	int         dataVal;  
}RealDataInfo_t;

class DPSDK_API SCSDataReportMsg : public DPSDKCBMessage
{
public:
	SCSDataReportMsg(void);
	virtual ~SCSDataReportMsg(void){}

public:

	//std::string		_devId;								// 设备类型
	int				_devTypeId;							// 资产类型
	char			szId[DPSDK_CHL_ID_LEN];				// 可以暂时不用

	std::vector<RealDataInfo_t>	vecRealdata;
};

typedef struct DPSDK_API tagSaveDoorInfo
{    
	char	doorId[DPSDK_CHL_ID_LEN];				// 门ID 设备号$单元类型$单元号$通道号
	char    doorName[DPSDK_DEVICE_NAME_LEN];		// 门名称 (通道名称)
	char    orgCode[DPSDK_CODING_LEN];				// 组织码
	char    orgName[DPSDK_CODING_LEN];				// 组织名称
	char	cardId[DPSDK_CHL_ID_LEN];				// 卡号
	char    swipeName[DPSDK_SWIPENAME_LEN];			// 刷卡人名称
	int64_t	time;									// 刷卡时间
	char	username[DPSDK_CLIENT_NAME_LEN];		// 值班人信息（登录客户端的用户名）
	int		open;									// 是否开门
	int64_t	operateTime;							// 操作时间
	char	picUrl[DPSDK_TAG_URL_LEN];				// 图片1
	char	picUrl2[DPSDK_TAG_URL_LEN];				// 图片2
	char	picUrl3[DPSDK_TAG_URL_LEN];				// 图片3
	char	picUrl4[DPSDK_TAG_URL_LEN];				// 图片4
	char	remark[DPSDK_REMARK_INFO_LEN];			// 备注

	tagSaveDoorInfo()
	{
		memset(doorId, 0 ,sizeof(doorId));
		memset(doorName, 0 ,sizeof(doorName));
		memset(orgCode, 0 ,sizeof(orgCode));
		memset(orgName, 0 ,sizeof(orgName));
		memset(cardId, 0 ,sizeof(cardId));
		memset(swipeName, 0 ,sizeof(swipeName));
		time = 0;
		memset(username, 0 ,sizeof(username));
		open = 0;
		operateTime = 0;
		memset(picUrl, 0 ,sizeof(picUrl));
		memset(picUrl2, 0 ,sizeof(picUrl2));
		memset(picUrl3, 0 ,sizeof(picUrl3));
		memset(picUrl4, 0 ,sizeof(picUrl4));
		memset(remark, 0 ,sizeof(remark));
	}
}SaveDoorInfo_t;

class DPSDK_API SaveDoorInfoMsg : public DPSDKCBMessage
{
public:
	SaveDoorInfoMsg(void);
	virtual ~SaveDoorInfoMsg(void){}

public:
	SaveDoorInfo_t doorInfo;
};

typedef struct DPSDK_API tagCardInfo
{    
	char	name[DPSDK_SWIPENAME_LEN];				// 姓名
	int		gender;									// 性别
	char	department[DPSDK_CODING_LEN];			// 所属部门
	char	mobile[DPSDK_PHONE_LEN];				// 手机
	char	phone[DPSDK_PHONE_LEN];					// 电话
	char	remark[DPSDK_REMARK_INFO_LEN];			// 备注
	char	photoUrl[DPSDK_TAG_URL_LEN];			// 照片
}CardInfo_t;

class DPSDK_API QueryCardInfoMsg : public DPSDKCBMessage
{
public:
	QueryCardInfoMsg(void);
	virtual ~QueryCardInfoMsg(void){}

public:
	char		szCardId[DPSDK_CHL_ID_LEN];

	//response
	CardInfo_t  cardInfo;
};

class DPSDK_API SavePicUrlMsg : public DPSDKCBMessage
{
public:
	SavePicUrlMsg(void);
	virtual ~SavePicUrlMsg(void){}

	dpsdk_operator_ftp_type_e	opType;				// 操作类型，请参考dpsdk_operator_ftp_type_e
	char				url[DPSDK_TAG_URL_LEN];		// ftp服务器存储数据的相对url
	char				path[DPSDK_TAG_PATH_LEN];	// 本地上传或者下载后的图片的地址
	dpsdk_ftp_transport_mode_e  mode;				// 文件传输模式
};
class DPSDK_API SaveAlarmPicUrlMsg : public DPSDKCBMessage
{
public:
	SaveAlarmPicUrlMsg(void);
	virtual ~SaveAlarmPicUrlMsg(void){}

	dpsdk_operator_ftp_type_e	opType;				// 操作类型，请参考dpsdk_operator_ftp_type_e
	char				url[DPSDK_TAG_URL_LEN];		// ftp服务器存储数据的相对url
	char				path[DPSDK_TAG_PATH_LEN];	// 本地上传或者下载后的图片的地址
	dpsdk_ftp_transport_mode_e  mode;				// 文件传输模式
};

class DPSDK_API GetLinkResourceMsg : public DPSDKCBMessage
{
public:
	GetLinkResourceMsg(void);
	virtual ~GetLinkResourceMsg(void);

	//response
	char*		pXmlData;
	uint32_t	nLen;
};

class DPSDK_API GetLinkChangeResourceMsg : public DPSDKCBMessage
{
public:
	GetLinkChangeResourceMsg(void);
	virtual ~GetLinkChangeResourceMsg(void);

	//response
	char*		pXmlData;
	uint32_t	nLen;
};

class DPSDK_API LinkResNotifyMsg : public DPSDKCBMessage
{
public:
	LinkResNotifyMsg(void);
	virtual ~LinkResNotifyMsg(void){};

	dpsdk_linkres_change_type	changeType;
	char						szIds[DPSDK_LINKRES_CHANGEID];
};

typedef struct DPSDK_API tagSaveRoadGateInfo
{    
	char	 roadGateId[DPSDK_CHL_ID_LEN];			// 道闸通道ID 设备号$单元类型$单元号$通道号
	char     roadGateName[DPSDK_CHANL_NAME_LEN];    // 道闸名称 (通道名称)
	int64_t	 time;									// 抓拍时间
	char	 username[DPSDK_CLIENT_NAME_LEN];		// 值班人信息（登录客户端的用户名）
	int		 open;									// 是否自动开闸【1是0否】
	int64_t	 dealTime;								// 处理时间
	char	 remark[DPSDK_REMARK_INFO_LEN];			// 备注
	int      subType;								// 默认0,重用该协议，以subtype做区分,见 ENUM_SAVE_CAR_SUBTYPE
	char     itcId[DPSDK_CHL_ID_LEN];				// 卡口设备id
	char     carNumber[SERVER_ID_LEN];				// 车牌号
	char     carColor[SERVER_ID_LEN];				// 车牌颜色
	char     state[SERVER_ID_LEN];					// 处理状态

}SaveRoadGateInfo_t;

class DPSDK_API SaveRoadGateInfoMsg : public DPSDKCBMessage
{
public:
	SaveRoadGateInfoMsg(void);
	virtual ~SaveRoadGateInfoMsg(void){}

public:
	SaveRoadGateInfo_t roadGateInfo;
};

class DPSDK_API QueryCarInfoMsg :public DPSDKCBMessage
{
public: 
	QueryCarInfoMsg(void);
	virtual ~QueryCarInfoMsg(void){}

public:
	char    strMsg1[DPSDK_CHL_ID_LEN];				// 车牌号
	int     nParam1;								// 车牌的名单类型，1 - 白  2 - 红2， 3 - 黑
};

class DPSDK_API SetRoadGateCmdMsg : public PesBaseMsg
{
public:
	SetRoadGateCmdMsg(void);
	virtual ~SetRoadGateCmdMsg(void){}

public:
	dpsdk_roadgate_cmd_e cmd;
	int64_t startTime;
	int64_t endTime;
};

//电网控制
class DPSDK_API PowerGridControlMsg : public PesBaseMsg
{
public:
	PowerGridControlMsg(void);
	virtual ~PowerGridControlMsg(void){}

public:
	dpsdk_powergrid_cmd_e cmd;
};

//电网信息上报
class DPSDK_API PowerGridReportMsg : public DPSDKCBMessage
{
public:
	PowerGridReportMsg(void);
	virtual ~PowerGridReportMsg(void){}

public:
	char	szId[DPSDK_CHL_ID_LEN];					// szReportType为1,2时为设备id；3时为通道id
	int     szReportType;							// 1、电网供电  2、电网断电 3、电压电流状态
	char	szData[DPSDK_CHL_ID_LEN];				// szReportType为3时使用，szData格式为 “电压值-电流值”					
};

typedef struct FtpFileInfo
{
	char filename[DPSDK_FTP_FILENAME_LEN];
	char nsize[DPSDK_FTP_FILESIZE_LEN];

	FtpFileInfo()
	{
		memset(filename,0,sizeof(filename));
		memset(nsize,0,sizeof(nsize));
	}
}FtpFileInfo;

class QueryFtpFileList : public DPSDKCBMessage
{
public:
	QueryFtpFileList();
	~QueryFtpFileList(){}
	char url[DPSDK_TAG_URL_LEN];		// ftp服务器存储数据的相对url
	std::list<FtpFileInfo>   FileInfoList;

	char    ftpurl[DPSDK_TAG_URL_LEN*2];  // ftp的全路径
};

class NotifyFtpFileModify : public  DPSDKCBMessage
{
public:
	NotifyFtpFileModify();
	~NotifyFtpFileModify(){}

	std::list<std::string>   m_listFileName;
	int ntype;
};

typedef struct DPSDK_API tagDispacherInfo
{    
	char	szChnId[DPSDK_CHL_ID_LEN];	
	int		chnlStatus;

	tagDispacherInfo()
	{
		memset(szChnId,0,DPSDK_CHL_ID_LEN);
		chnlStatus = Dispacher_Chnl_Offline;
	}
}DispacherInfo_t;

class DPSDK_API QueryDispacherInfoMsg : public PesBaseMsg
{
public:
	QueryDispacherInfoMsg(void);
	virtual ~QueryDispacherInfoMsg(void);

	//respone
	DispacherInfo_t*		pChnlInfo;
	int						nChnlNum;
};

class DPSDK_API DispacherReportMsg : public DPSDKCBMessage
{
public:
	DispacherReportMsg(void);
	virtual ~DispacherReportMsg(void){}

public:
	char							szCameraId[DPSDK_CHL_ID_LEN];
	dpsdk_dispacher_chnl_status_e	status;
	int64_t							time;
};

typedef struct DPSDK_API tagAlarmOutStatusInfo
{    
	char	szChnId[DPSDK_CHL_ID_LEN];	
	int		nChnlStatus;			// 0表示离线，1表示在线

	tagAlarmOutStatusInfo()
	{
		memset(szChnId, 0, DPSDK_CHL_ID_LEN);
		nChnlStatus = 0;
	}
}AlarmOutStatusInfo_t;

class DPSDK_API QueryAHostAlarmOutStatusMsg : public PesBaseMsg
{
public:
	QueryAHostAlarmOutStatusMsg(void);
	virtual ~QueryAHostAlarmOutStatusMsg(void);

	//respone
	AlarmOutStatusInfo_t*	pChnlInfo;
	int						nChnlNum;
};

class DPSDK_API IDPSDKPec : public IDPSDKFuncBase
{
public:

	//PES交互部分
	virtual int SetDoorCmd( const char* cameraId, dpsdk_door_cmd_e cmd, int64_t start, int64_t end ) = 0;

	virtual int SetAlarmHostCmd( const char* szId, dpsdk_alarmhost_opttype_e opttype, dpsdk_alarmhost_cmd_e cmd, int64_t start, int64_t end ) = 0;

	virtual int QueryAHostDefenceInfo( const char* szId, dpsdk_alarmhost_defence_e deftype ) = 0;

	virtual int QueryAHostAbility( const char* szId ) = 0;
		
	virtual int QueryDoorStatus( const char* szDev ) = 0;

	virtual int SetRoadGateCmd( const char* cameraId, dpsdk_roadgate_cmd_e cmd, int64_t start, int64_t end ) = 0;
	//电网操作
	virtual int ControlPowerGrid( const char* szId, dpsdk_powergrid_cmd_e cmd ) = 0;

	virtual int QueryDispacherChannelStatus(const char* szDev) = 0;

	//CMS交互部分
	virtual int SaveDoorInfo( SaveDoorInfo_t &doorInfo ) = 0;

	virtual int QueryCardInfo(const char* szCardId) = 0;

	virtual int GetLinkResource() = 0;

	virtual int GetLinkChangeResource(const char* pData, int nLen) = 0;

	virtual int SaveRoadGateInfo(SaveRoadGateInfo_t &roadGateInfo ) = 0;

	virtual int QueryCarInfo(const char* szCarNum) = 0;

	//Ftp
	virtual int SavePicUrl( dpsdk_operator_ftp_type_e optype, const char* url, const char* path ,dpsdk_ftp_up_e eftpType = DPSDK_DEFAULT_FTP_UP, dpsdk_ftp_transport_mode_e mode = MODE_EPSV) = 0;

	virtual int GetFtpFileList(const char* url) = 0;

	virtual int UpdateToSever(DPSdk::dpsdk_operator_ftp_type_e optype,std::list<std::string>& FileNameList) = 0;

	virtual int QueryAHostAlarmOutStatus( const char* szDevId ) = 0;

	/** CFLCUEnvQueryRequest协议透传接口.
		@param const char* szDev						设备ID/通道ID
		@param int devType								设备类型：1-门禁 2-报警主机 3-采集器 101-门禁信息 102-卡信息 103-报警信息
		@param int subType								环境量类型：// _devType=103时： 1-查询所有通道 2-查询单一通道 3-查询设备状态
																	// _devType=103时： 1-查询所有通道 2-查询单一通道 
																	// _subType=10, 查询所有通道
																	// _subType=11, 查询单一通道
		@param uint32_t begintime						开始时间
		@param uint32_t endtime							结束时间
		@return											异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int EnvQuery( const char* szDev, int devType, int subType, uint32_t begintime, uint32_t endtime ) = 0;
protected:
	virtual ~IDPSDKPec(void){};
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif
