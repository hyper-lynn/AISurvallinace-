/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,云台控制子模块
 *
 * 当前版本：1.0
 * 原作者　：12928
 * 完成日期：2012年8月24日
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKPTZ_H
#define INCLUDED_DPSDK_DPSDKPTZ_H

#include "DPSDK.h"
#include "libdsl/DStr.h"
#include "DPSDKGeneral.h"

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////
// OSD Text 对齐方式
typedef enum
{
	OSD_TEXT_ALIGN_INVALID		= 0,				// 无效的对齐方式
	OSD_TEXT_ALIGN_LEFT			= 1,				// 左对齐
	OSD_TEXT_ALIGN_XCENTER		= 2,				// X坐标中对齐
	OSD_TEXT_ALIGN_YCENTER		= 3,				// Y坐标中对齐
	OSD_TEXT_ALIGN_CENTER		= 4,				// 居中
	OSD_TEXT_ALIGN_RIGHT			= 5,				// 右对齐
	OSD_TEXT_ALIGN_TOP			= 6,				// 按照顶部对齐
	OSD_TEXT_ALIGN_BOTTOM		= 7,				// 按照底部对齐
	OSD_TEXT_ALIGN_LEFTTOP		= 8,				// 按照左上角对齐
	OSD_TEXT_ALIGN_CHANGELINE	= 9					// 换行对齐
}OSDTextAlign_e;

// 云台控制命令															
typedef enum
{
	PTZ_GO_UP							= 1,								// 上
	PTZ_GO_DOWN,															// 下
	PTZ_GO_LEFT,															// 左
	PTZ_GO_RIGHT,															// 右
	PTZ_GO_LEFTUP,															// 左上
	PTZ_GO_LEFTDOWN,														// 左下
	PTZ_GO_RIGHTUP,															// 右上
	PTZ_GO_RIGHTDOWN,														// 右下
	PTZ_GO_CRUISE						= 35,								// 点间巡航命令
}dpsdk_ptz_direct_e;

// 
typedef enum
{	
	PTZ_ADD_ZOOM,															// 变倍+ 
	PTZ_ADD_FOCUS,															// 变焦+
	PTZ_ADD_APERTURE,														// 光圈+
	PTZ_REDUCE_ZOOM,														// 变倍-
	PTZ_REDUCE_FOCUS,														// 变焦-
	PTZ_REDUCE_APERTURE,													// 光圈-
}dpsdk_camera_operation_e;

// 锁定/解锁类型
typedef enum
{
	PTZ_CMD_LOCK						= 1,								// 锁定当前摄像头
	PTZ_CMD_UNLOCK_ONE,														// 解锁当前摄像头
	PTZ_CMD_UNLOCK_ALL,														// 解锁被该用户锁定的所有摄像头
	PTZ_CMD_LOCK_ALL,														// 锁定所有摄像头
	PTZ_CMD_QUERY_LOCK_STATUS			 = 5,								// 查询锁定状态
}dpsdk_ptz_locktype_e;

// 预置点操作类型
typedef enum
{
	PTZ_PRESET_LOCATION					= 1,								// 预置点定位
	PTZ_PRESET_ADD,															// 预置点增加
	PTZ_PRESET_DEL,															// 预置点删除
}dpsdk_ptz_prepoint_cmd_e;

// 巡航线操作类型
typedef enum
{
	PTZ_CRUISE_SET,															// 巡航线设置
	PTZ_CRUISE_DEL,															// 巡航线删除
	PTZ_CRUISE_OPEN,														// 巡航线开启
	PTZ_CRUISE_CLOSE,														// 巡航线关闭
}dpsdk_ptz_cruise_cmd_e;

//空闲动作类型	1 预置点 2 自动线扫 3 巡航 4 自动巡迹
typedef enum
{
	PTZ_IDLEMOTION_PREPOINT = 1,
	PTZ_IDLEMOTION_AUTO_LINESCAN,
	PTZ_IDLEMOTION_CRUISE,
	PTZ_IDLEMOTION_AUTO_CRUISE,
}dpsdk_ptz_idlemotion_cmd_e;

// 扩展控制命令
typedef enum 
{
	PTZ_NEW_COMMAND_BEGIN				= 35,								// 
	PTZ_ADD_PRESET_TO_TOUR,													// 加入预置点到巡航 巡航线路 预置点值
	PTZ_DEL_PRESET_TO_TOUR,													// 删除巡航中预置点 巡航线路 预置点值
	PTZ_CLEAR_TOUR,															// 清除巡航 巡航线路
	PTZ_START_AUTO_ROUND,													// 开始水平旋转
	PTZ_STOP_AUTO_ROUND,													// 停止水平旋转
	PTZ_SET_LEFT_SCAN_RANGE,												// 设置左边界
	PTZ_SET_RIGHT_SCAN_RANGE,												// 设置右边界
	PTZ_START_SCAN,															// 开始线扫
	PTZ_STOP_SCAN,															// 停止线扫
	PTZ_SET_MODLE_START,													// 设置模式开始 模式线路
	PTZ_SET_MODLE_CANCEL,													// 设置模式结束 模式线路
	PTZ_RUN_MODLE,															// 运行模式 模式线路
	PTZ_STOP_MODLE,															// 停止模式 模式线路
	PTZ_CLEAR_MODLE,														// 清除模式 模式线路
	PTZ_UPDOWN,																// 翻转命令
	PTZ_QUICK_ORIENTATION,													// 快速定位 水平坐标(8192) 垂直坐标(8192) 变倍(4)
	PTZ_OPEN_ASSISTANT_POINT,												// 辅助开关开 辅助点
	PTZ_CLOSE_ASSISTANT_POINT,												// 辅助开关关 辅助点
	PTZ_OPEN_IPC_MENU,														// 打开球机菜单 ww
	PTZ_CLOSE_IPC_MENU,														// 关闭菜单
	PTZ_MENU_ASSURE,														// 菜单确定
	PTZ_MENU_CALCEL,														// 菜单取消
	PTZ_MENU_UP,															// 菜单上
	PTZ_MENU_DOWN,															// 菜单下
	PTZ_MENU_LEFT,															// 菜单左
	PTZ_MENU_RIGHT,															// 菜单右
}dpsdk_ptz_extend_cmd_e;													

// 云台消息通知
typedef enum
{
	PTZ_NOTIFY_UNKNOWN					= 0,								// 
	PTZ_NOTIFY_LOCK_LOST,													// 锁定被抢夺
}dpsdk_ptz_notify_type_e;

//鱼眼控制命令
typedef enum
{
	FISHEYE_FUN_UNKONW			= 0,			//未知
	FISHEYE_FUN_ZOOMIN			= 1,			//放大
	FISHEYE_FUN_ZOOMOUT			= 2,			//缩小
	FISHEYE_FUN_UP				= 3,			//向上移动
	FISHEYE_FUN_DOWN			= 4,			//向下移动
	FISHEYE_FUN_LEFT			= 5,			//向左移动
	FISHEYE_FUN_RIGHT			= 6,			//向右移动
	FISHEYE_FUN_ROTATECLOCK		= 7,			//自动顺时针旋转
	FISHEYE_FUN_ROTATEANTICLOCK	= 8,			//自动逆时针旋转
	FISHEYE_FUN_STOP			= 9,			//终止自动旋转
}dpsdk_fisheye_funbtn_e;

//鱼眼安装模式
typedef enum
{
	FISHEYE_FITMODE_UNKNOW	= 0,		//未知
	FISHEYE_FITMODE_TOP		= 1,		//顶装
	FISHEYE_FITMODE_WALL	= 2,		//壁装
	FISHEYE_FITMODE_TERRA	= 3,		//地装
}dpsdk_fisheye_fitmode_e;

//鱼眼展示模式
typedef enum
{
	FISHEYE_DISPLAYMODE_UNKNOW						= 0,	//未知
	FISHEYE_DISPLAYMODE_ORIGIAL						= 1,	//原始图像模式
	FISHEYE_DISPLAYMODE_CONFIG						= 2,	//配置模式
	FISHEYE_DISPLAYMODE_PANORAMA					= 3,	//全景模式
	FISHEYE_DISPLAYMODE_DOUBLEPANORAMA				= 4,	//双全景模式
	FISHEYE_DISPLAYMODE_ORIGIALPLUSTHREEEPTZREGION	= 5,	//1+3模式
	FISHEYE_DISPLAYMODE_SINGLE						= 6,	//单画面EPtz模式
	FISHEYE_DISPLAYMODE_FOUREPTZREGION				= 7,	//4画面模式
	FISHEYE_DISPLAYMODE_NORMAL						= 8,	//普通模式
}dpsdk_fisheye_displaymode_e;

//空闲动作类型
typedef enum
{
	PTZ_IDLETYPE_NONE								= 0,	//没有空闲动作
	PTZ_IDLETYPE_PRESET								= 1,	//预置点
	PTZ_IDLETYPE_TOUR								= 2,	//巡航
	PTZ_IDLETYPE_SCAN								= 3,	//自动线扫
	PTZ_IDLETYPE_PATTERN							= 4		//自动循迹
}dpsdk_ptz_ideltype_e;

// 预置点查询
typedef struct DPSDK_API tagQueryPoint
{
	unsigned char	code;													// 预置点编号
	unsigned char	revered[3];												// revered
	char			name[32];												// 名字
	
	tagQueryPoint(void)
	{
		code = 0;
		memset(revered, 0, sizeof(revered));
		memset(name, 0, sizeof(name));
	}
}dpsdk_ptz_query_point_t;

// 预置点查询(带守望点信息)
typedef struct DPSDK_API tagQueryPointEx
{
	unsigned char	code;													//预置点编号
	unsigned char	revered[3];												//revered
	char			name[32];												// 名字
	int				watchPoint;												// 是否守望点，0：不是，1：是
	int				leisureTime;											// 空闲时间，单位：分
	int				enable;													// 使能开关，0：关，1：开

	tagQueryPointEx(void)
	{
		code = 0;
		memset(revered, 0, sizeof(revered));
		memset(name, 0, sizeof(name));
		watchPoint = 0;
		leisureTime = 0;
		enable = 0;
	}
}dpsdk_ptz_query_point_ex_t;

// 预置点时间段查询
typedef struct DPSDK_API tagQueryTimePoint
{
	unsigned char	code;													// 预置点编号
	unsigned char	revered[3];												// revered
	char			name[32];												// 名字
	char  		    beginTime[32];                          				// 开始时间
	char		    endTime[32];                            				// 结束时间
	tagQueryTimePoint(void)
	{
		code = 0;
		memset(beginTime, 0, sizeof(beginTime));
		memset(endTime, 0, sizeof(endTime));
		memset(revered, 0, sizeof(revered));
		memset(name, 0, sizeof(name));
	}
}dpsdk_ptz_query_time_point_t;

// 云台定位报警信息
typedef struct DPSDK_API tagPtzSitInfo
{
	char                                szDevId[DPSDK_DEV_ID_LEN];          // 设备ID
	int                                 nChannelID;           				// 通道号 
	int                                 nPTZPan;              				// 云台水平运动位置，有效范围：[0,3600] 
	int                                 nPTZTilt;             				// 云台垂直运动位置，有效范围：[-1800,1800] 
	int                                 nPTZZoom;             				// 云台光圈变动位置，有效范围：[0,128] 
	int									bState;               				// 云台运动状态, 0-未知1-运动2-空闲 
	int									bAction;							// 云台动作，-预置点，-线扫，-巡航，-巡迹，-水平旋转 
	int									bFocusState;						// 云台聚焦状态, 0-未知, 1-运动状态, 2-空闲 
	int									bEffectiveInTimeSection;			// 在时间段内预置点状态是否有效 	//如果当前上报的预置点是时间段内的预置点，则为，其他情况为 
	int                                 nPtzActionID;         				// 巡航ID号 
	uint32_t                            dwPresetID;           				// 云台所在预置点编号 
	double                              fFocusPosition;       				// 聚焦位置 
	int									bZoomState;           				// 云台ZOOM状态，-未知，-ZOOM，-空闲 
	tagPtzSitInfo()
	{
		nChannelID = 0;
		nPTZPan = 0;
		nPTZTilt = 0;
		nPTZZoom = 0;
		bState = 0;
		bAction = 0;
		bEffectiveInTimeSection = 0;
		bFocusState = 0;
		nPtzActionID = 0;
		fFocusPosition = 0;
		bZoomState = 0;
		memset(szDevId,0,DPSDK_DEV_ID_LEN);  
		dwPresetID = 0;
	}
}dpsdk_Ptz_Sit_Alarm_Info;

typedef struct DPSDK_API tagSetPtzParamInfo
{
	int									nPositionX;							// 云台水平运动位置,有效范围：[0,3600]
	int									nPositionY;							// 云台垂直运动位置,有效范围：[-1800,1800]
	int									nPositionZoom;						// 云台光圈变动位置,有效范围：[0,128]
	double								fSpeedPositionX;					// 云台水平方向速率,归一化到-1~1			
	double								fSpeedPositionY;					// 云台垂直方向速率,归一化到-1~1
	double								fSpeedZoom;							// 云台光圈放大倍率,归一化到0~1

	tagSetPtzParamInfo()
	{
		nPositionX = 0;
		nPositionY = 0;
		nPositionZoom = 0;
		fSpeedPositionX = 0.0;
		fSpeedPositionY = 0.0;
		fSpeedZoom = 0.0;
	}
}dpsdk_Set_Ptz_Param_Info;
//////////////////////////////////////////////////////////////////////////

class DPSDK_API TimePtzPointQueryMsg : public DPSDKCBMessage
{
public:
	TimePtzPointQueryMsg(void);
	virtual ~TimePtzPointQueryMsg(void){}
public:
	char							cameraId[DPSDK_DEV_ID_LEN];				// 摄像头ID
	unsigned char					icount;									// 预置点数量
	dpsdk_ptz_query_time_point_t	pPoint_t[DPSDK_POINT_COUNT];			// 预置点信息
};

class DPSDK_API PtzPointQueryMsg : public DPSDKCBMessage
{
public:
	PtzPointQueryMsg(void);
	virtual ~PtzPointQueryMsg(void){}

public:
	char						cameraId[DPSDK_DEV_ID_LEN];					// 摄像头ID
	unsigned char				icount;										// 预置点数量
	dpsdk_ptz_query_point_t		pPoint_t[DPSDK_POINT_COUNT];				// 
};

//预置点查询（带守望点信息）
class DPSDK_API PtzPointQueryEXMsg : public DPSDKCBMessage
{
public:
	PtzPointQueryEXMsg(void);
	virtual ~PtzPointQueryEXMsg(void){}

public:
	char						cameraId[DPSDK_DEV_ID_LEN];					// 摄像头ID
	unsigned char				icount;										// 预置点数量
	dpsdk_ptz_query_point_ex_t	pPoint_t[DPSDK_POINT_COUNT];				// 
};

// 巡航查询
class DPSDK_API PtzCruiseQueryMsg : public DPSDKCBMessage
{
public:
	PtzCruiseQueryMsg(void);
	virtual ~PtzCruiseQueryMsg(void){}

public:
	char		cameraId[DPSDK_DEV_ID_LEN];									// 摄像头ID
	char		_xml[DPSDK_XML_LENGTH];										// 巡航线信息文件
	int			clientId;
};

// 
class DPSDK_API PtzNotifyMsg : public DPSDKCBMessage
{
public:
	PtzNotifyMsg(void);
	virtual ~PtzNotifyMsg(void){}

public:
	dpsdk_ptz_notify_type_e	notifyType;										// 通知类型
	char					deviceId[DPSDK_DEV_ID_LEN];						// 设备ID（DVR+通道）
	int						channelNo;										// 通道号
	char					clientName[DPSDK_CLIENT_NAME_LEN];				// 抢夺锁定的用户的名称
	unsigned char			clientLevel;									// 	
};

// 
class DPSDK_API DevStatusNotifyMsg : public DPSDKCBMessage
{
public:
	DevStatusNotifyMsg(void);
	virtual ~DevStatusNotifyMsg(void){}

public:
	char			deviceId[DPSDK_DEV_ID_LEN];								// 设备ID（DVR+通道）
	int				_status;												// 状态。1在线，2断线，3移除, 4对讲
	int				notifytype;												// 通知的来源： 1表示DMS通知，2表示PCS通知
	int				_cuStat;												// 客户端状态。 0 客户端登录， 1 客户端在线上报
};

struct  DPSDK_API ChnlStatus
{
	char			chnlId[DPSDK_DEV_ID_LEN];							// 设备ID
	int				_status;											// 状态。1在线，2断线
};	

// 
class DPSDK_API ChnlStatusNotifyMsg : public DPSDKCBMessage
{
public:
	ChnlStatusNotifyMsg(void);
	virtual ~ChnlStatusNotifyMsg(void){}

public:
	char			chnlId[DPSDK_DEV_ID_LEN];								// 设备ID（DVR+通道）
	int				_status;												// 状态。1在线，2断线

	std::vector<ChnlStatus> vecChnlStatus;
};

// 连接DMS
class DPSDK_API ConnectToDmsMsg : public DPSDKCBMessage
{
public:
	ConnectToDmsMsg(void);
	virtual ~ConnectToDmsMsg(void){}

public:
	char		serverId[SERVER_ID_LEN];									// 
	char		serverip[DPSDK_IP_LEN];										// 
};

// 断开DMS
class DPSDK_API DisConnectToDmsMsg : public DPSDKCBMessage
{
public:
	DisConnectToDmsMsg(void);
	virtual ~DisConnectToDmsMsg(void){}

public:
	char		serverId[SERVER_ID_LEN];									// 
	char		serverip[DPSDK_IP_LEN];										// 
};

//云台锁定状态通知
class DPSDK_API PtzLockStatusMsg : public DPSDKCBMessage
{
public:
	PtzLockStatusMsg(void);
	virtual ~PtzLockStatusMsg(void){}

public:
	char			szDeviceID[DPSDK_DEV_ID_LEN];							//设备ID
	int				iChannelNo;												//通道号
	int				iStatus;												//锁定状态
};

// 存放公用数据
class DPSDK_API ServerBaseMsg : public GeneralJsonTransportMsg
{
public:
	ServerBaseMsg( int cmd = DPSDK_CMD_UNKNOWN,int msgType = DPSDK_MSG_RESPONSE);
	~ServerBaseMsg(){}

	//char	serverId[SERVER_ID_LEN];										// 服务ID
	char	cameraId[DPSDK_CHL_ID_LEN];										// 摄像头ID
	char	deviceId[DPSDK_DEV_ID_LEN];										// 设备ID
};

// 中间父类，用于存放持有锁的用户信息
class DPSDK_API PtzLockUserInfoMsg : public ServerBaseMsg
{
public:
	PtzLockUserInfoMsg(int cmd = DPSDK_CMD_UNKNOWN,int msgType = DPSDK_MSG_RESPONSE);
	~PtzLockUserInfoMsg(){}

public:
	//去除组织树缓存修改
	//request 客户端传这几个值进来
	char	szSN[DPSDK_CLIENT_NAME_LEN];									// 互联网编码SN

	//reponse:
	char	clientName[DPSDK_CLIENT_NAME_LEN];								// 持有锁的用户名称
	int		clientLevel;													// 持有锁的用户级别
	bool	bIsLocked;
};

// 云台锁定/解锁
class DPSDK_API PtzLockCameraMsg : public PtzLockUserInfoMsg
{
public:
	PtzLockCameraMsg();
	~PtzLockCameraMsg(){}

public:
	dpsdk_ptz_locktype_e	lock_e;
	int						nGrade;
	int						nType;
	uint32_t				lockTime;					

	//char					clientName[DPSDK_CLIENT_NAME_LEN];				// DMS锁定失败时候，持有锁的用户名称
	//int					clientLevel;									// DMS锁定失败时候，持有锁的用户级别
};

// 云台状态查询
class DPSDK_API PtzStatusQueryMsg : public ServerBaseMsg
{
public:
	PtzStatusQueryMsg(void);
	virtual ~PtzStatusQueryMsg(void){}
public:
	char		szDevId[DPSDK_CHL_ID_LEN];									// 摄像头ID
};

// 云台方向控制
class DPSDK_API PtzDirectionMsg : public PtzLockUserInfoMsg
{
public:
	unsigned char			direct_e;													// 操作方向
	unsigned char			step;														// 步长
	bool		bstop;														// 停止标志位：默认false, true-停止
	char		szChannelSN[DPSDK_CHL_ID_LEN];								// 通道唯一标识码			

	PtzDirectionMsg();
	~PtzDirectionMsg(){}

	//reponse:
	char	_dmsId[16];														// DMS服务ID，比如3001等
	char	_dmsAddr[512];													// DMS服务地址 协议里面的格式： ip1:port1|ip2:port2|ip3:port3|ip4:port4|ip5:port5|
};

// 云台变焦，变距，光圈操作
class DPSDK_API PtzCameraOperationMsg : public PtzLockUserInfoMsg
{
public:
	unsigned char	clientOperation;										// 操作。1变倍，2变焦，3光圈
	unsigned char	ivalue;													// 值。1增加，2减小
	unsigned char	step;													// 步长
	bool			bstop;													// 停止标志位：默认false, true-停止
	char			szChannelSN[DPSDK_CHL_ID_LEN];							// 通道唯一标识码

	PtzCameraOperationMsg();
	~PtzCameraOperationMsg(){}

	// reponse:
};

// 云台三维定位
class DPSDK_API PtzSitMsg : public PtzLockUserInfoMsg
{
public:
	int32_t			pointX;													// 水平坐标 -8192 ~~ 8192
	int32_t			pointY;													// 垂直坐标 -8192 ~~ 8192
	int32_t			pointZ;													// 变倍数 -4 ~~ 4
	int32_t			type;
	int32_t			pointX_ext;												// hik三维定位扩展
	int32_t			pointY_ext;												// hik三维定位扩展
	char			szChannelSN[DPSDK_CHL_ID_LEN];							// 通道唯一标识码

	PtzSitMsg();
	~PtzSitMsg(){}

	// reponse:
};

// 云台打开
class DPSDK_API PtzOpenOperMsg : public PtzLockUserInfoMsg
{
public:
	typedef enum
	{
		cmd_unknown		= 0,
		cmd_light		= 19,												// 灯光
		cmd_RainBrush	= 20,												// 雨刷
		cmd_Infrared	= 21,												// 红外线
	}Command;

	Command			type_e;
	bool			bopen;													// true打开，false关闭

	PtzOpenOperMsg();
	~PtzOpenOperMsg(){}

	// reponse:
};

// 云台 预置点操作(设置，删除，定位)
class DPSDK_API PtzPrePointOperMsg : public PtzLockUserInfoMsg
{
public:
	PtzPrePointOperMsg();
	~PtzPrePointOperMsg(){}

public:
	unsigned char				prePointId;									// 预置点编号
	char						prePointName[DPSDK_ID_LEN];					// 预置点名字
	dpsdk_ptz_prepoint_cmd_e	type_e;
	char						szNetSN[DPSDK_ID_LEN];						// SN
};

// 云台 预置点操作(设置，删除，定位)（有效期预置点）
class PtzTimePrePointOperMsg : public ServerBaseMsg
{
public:
	PtzTimePrePointOperMsg();
	~PtzTimePrePointOperMsg(){}
public:
	unsigned char				prePointId;									// 预置点编号
	char						prePointName[DPSDK_ID_LEN];					// 预置点名字
	char            			beginTime[DPSDK_TIME_LEN];  
	char						endTime[DPSDK_TIME_LEN];
	dpsdk_ptz_prepoint_cmd_e	type_e;
};

class DPSDK_API PtzTimeTaskSetMsg : public ServerBaseMsg
{
public:
	PtzTimeTaskSetMsg(void);
	virtual ~PtzTimeTaskSetMsg(void){}

public:
	char					szCameraId[DPSDK_DEV_ID_LEN];					// 摄像头ID
	char                    szBuf[DPSDK_PTZTIMETASK_LEN];					// 云台定时任务配置
};

class PtzTimeTaskQueryMsg : public ServerBaseMsg
{
public:
	PtzTimeTaskQueryMsg(void);
	virtual ~PtzTimeTaskQueryMsg(void){}
public:
	char					szCameraId[DPSDK_DEV_ID_LEN];					// 摄像头ID
	char                    szBuf[DPSDK_PTZTIMETASK_LEN];					// 云台定时任务配置
};

// 设置预置点的有效时间段
class DPSDK_API SetPrePointTimeMsg : public ServerBaseMsg
{
public:
	SetPrePointTimeMsg();
	~SetPrePointTimeMsg(){}

public:
	unsigned char	prePointId;												// 预置点编号
	char			prePointName[DPSDK_ID_LEN];								// 预置点名字
	char            beginTime[DPSDK_TIME_LEN];  
	char            endTime[DPSDK_TIME_LEN];
};

// 云台 巡航线保存
class DPSDK_API PtzSaveCruiseMsg : public ServerBaseMsg
{
public:
	PtzSaveCruiseMsg();
	~PtzSaveCruiseMsg();

public:
	char			*pXml;													// 巡航线信息文件
	int				length;													// buffer长度
	int				clientId;												// 用户id
};

// 订阅云台报警
class DPSDK_API SubPtzSitInfoMsg : public ServerBaseMsg
{
public:
	SubPtzSitInfoMsg();
	~SubPtzSitInfoMsg(){};

public:
	int				nSubFlag;
	int             nResult;
};

// 云台定位报警信息
class DPSDK_API PtzSitAlarmInfoMsg : public DPSDKCBMessage
{
public:
	PtzSitAlarmInfoMsg(void);
	virtual ~PtzSitAlarmInfoMsg(void){}

public:
	dpsdk_Ptz_Sit_Alarm_Info  ptzSitAlarInfo;
};

// 查询报警输入通道
class DPSDK_API QueryAlarmInMsg : public ServerBaseMsg
{
public:
	QueryAlarmInMsg();
	~QueryAlarmInMsg(){}
public:
	int nQueryType;															// 查询类型，0：按通道查询，其余按设备查询
	int nChnlNum;															//通道数，按设备设置时有效
};

// 报警输入通道布撤防
class DPSDK_API AlarmInEnableMsg : public ServerBaseMsg
{
public:
	bool			bEnable;												// 启用与否
	int				nSetType;												// 设置类型，0：按通道设置，其余按设备设置
	int				nChnlNum;												//通道数，按设备设置时有效

	//设置的结果返回
	dsl::DStr 		strResult;												//格式按通道状态组合，以逗号隔开：1,0,1....

	AlarmInEnableMsg();
	~AlarmInEnableMsg(){}
};

class DPSDK_API AlarmInReportMsg : public DPSDKCBMessage
{
public:
	AlarmInReportMsg(void);
	virtual ~AlarmInReportMsg(void)
	{
		if(pChnlEnable != NULL)
		{
			delete [] pChnlEnable; 
			pChnlEnable = NULL;
		}
	}

public:
	char			szCameraId[DPSDK_CHL_ID_LEN];
	bool			bEnable;												// 查询通道返回的启用与否结果

	bool			bQueryDev;												// 是否是查询设备，true表示查询设备，false表示查询通道
	char			szDevId[DPSDK_DEV_ID_LEN];								// 设备ID
	int				nChnlNum;												// 通道数量
	bool*			pChnlEnable;											// 查询设备返回的启用与否结果
	int				iChannelNum;											// 通道号
	int				iUnitType;												// 单元类型
};

// 云台三维定位信息
class DPSDK_API QueryPtzSitInfoMsg : public ServerBaseMsg
{
public:
	QueryPtzSitInfoMsg();
	~QueryPtzSitInfoMsg(){};

public:
	int				nX;
	int				nY;
	int				nZoom;
};

// NVR设备通道状态
class DPSDK_API QueryNVRChnlStatusInfoMsg : public ServerBaseMsg
{
public:
	QueryNVRChnlStatusInfoMsg();
	~QueryNVRChnlStatusInfoMsg(){};

	char			deviceId[DPSDK_DEV_ID_LEN];								// 设备ID（NVR+通道）
	int				nChannelNum;											// 要查询的通道数

};

// 电动聚焦设备控制
class DPSDK_API FocuseControlMsg : public ServerBaseMsg
{
public:
	FocuseControlMsg();
	~FocuseControlMsg(){};

	int				controlCmd;
	float			zoom;
	float			focus;
};

// 查询电动聚焦设备状态
class DPSDK_API QueryFocusControlStatue : public ServerBaseMsg
{
public:
	QueryFocusControlStatue();
	~QueryFocusControlStatue(){};

	float			zoom;
	float			focus;
	int				statue;
};

class DPSDK_API QueryDeviceViewInfoMsg : public DPSDKCBMessage
{
public:
	QueryDeviceViewInfoMsg(void);
	virtual ~QueryDeviceViewInfoMsg(void){}
	char			deviceId[DPSDK_DEV_ID_LEN];								// 设备ID
};

class DPSDK_API QueryChannelViewInfoMsg : public ServerBaseMsg
{
public:
	QueryChannelViewInfoMsg(void);
	virtual ~QueryChannelViewInfoMsg(void){}
public:
	int				nDistance;												// 单位米
	int				nViewAngle;												// 视角角度(0-1800)
	int				nViewAzimuth;											// 视角起始角度(0-3600)
	int				nViewInclination;
};

class DPSDK_API ChannelViewInfoReport : public ServerBaseMsg
{
public:
	ChannelViewInfoReport(void);
	virtual ~ChannelViewInfoReport(void){}
public:
	int				nDistance;												// 单位米
	int				nViewAngle;												// 视角角度(0-1800)
	int				nViewAzimuth;											// 视角起始角度(0-3600)
	int				nViewInclination;
};

class DPSDK_API SetChannelViewInfoMsg : public ServerBaseMsg
{
public:
	SetChannelViewInfoMsg(void);
	virtual ~SetChannelViewInfoMsg(void){}
	int				nAzimuthH;												// 起始弧度修改
};

// 查询报警输出通道
class DPSDK_API QueryAlarmOutMsg : public ServerBaseMsg
{
public:
	QueryAlarmOutMsg();
	~QueryAlarmOutMsg(){}
public:
	int				nBroadcast;												// 是否广播，登陆时查询为0，开启关闭之后再查询为1
	int				nChnlNo;												// 通道号，-2表示根据通道ID解析出来的通道号查询通道，-1表示查询设备，大于等于0表示根据传入的通道号查询通道
};

// 查询报警输出模式
class DPSDK_API QueryAlarmOutModleMsg :public QueryAlarmOutMsg
{
public:
	QueryAlarmOutModleMsg();
	~QueryAlarmOutModleMsg(){}
public:
	int				m_nModle;												// 工作模式
	int				m_nChannel;												// 通道号

};
// 报警输出通道状态
class DPSDK_API AlarmOutReportMsg : public DPSDKCBMessage
{
public:
	AlarmOutReportMsg(void);
	virtual ~AlarmOutReportMsg(void){}

public:
	char			szCameraId[DPSDK_CHL_ID_LEN];
	bool			bEnable;												// 启用与否
	char			szDevId[DPSDK_CHL_ID_LEN];								// 设备id
	int				iChannelNum;											// 通道号
	int				iUnitType;												// 单元类型
};

class DPSDK_API LotPointsQueryMsg : public DPSDKCBMessage
{
public:
	LotPointsQueryMsg(void);
	~LotPointsQueryMsg(void);

public:
	char*					szCameraIds;									// 摄像头ID
	int						nIdLen;											// ID长度
	char*					szJsonInfo;										// 预置点Json串
	int						nJsonLen;										// Json长度
};

class DPSDK_API PtzCtrlOutResultMsg : public DPSDKCBMessage
{
public:
	PtzCtrlOutResultMsg();
	~PtzCtrlOutResultMsg();
public:
	char			szCameraId[DPSDK_CHL_ID_LEN];
};

// 主备状态
class DPSDK_API QueryDeviceClusterStatusMsg : public ServerBaseMsg
{
public:
	QueryDeviceClusterStatusMsg();
	virtual ~QueryDeviceClusterStatusMsg() {}
	int status; // 主备状态（0未知，1单机，2主用，3备用）
};

// 鱼眼配置
class DPSDK_API FishEyeSetInfoMsg : public ServerBaseMsg
{
public:
	FishEyeSetInfoMsg();
	virtual ~FishEyeSetInfoMsg() {}
	int								m_nChannelNo;
	dpsdk_fisheye_fitmode_e			m_nFitMode;
	dpsdk_fisheye_displaymode_e		m_nDisplayMode;
};

// 鱼眼控制
class DPSDK_API FishEyeControlMsg : public ServerBaseMsg
{
public:
	FishEyeControlMsg();
	virtual ~FishEyeControlMsg() {}
	int								m_nchannelNo;
	dpsdk_fisheye_funbtn_e			m_nFunBtn;
	int								m_nWindId;
	int								m_nStep;
};

//与DMS交互的通用json消息类
class DPSDK_API GeneralJsonSendToDMSMsg: public ServerBaseMsg
{
public:
	GeneralJsonSendToDMSMsg(void)
	{
		m_cmd = DPSDK_CMD_JSON_SEND_TO_DMS;
		trantype = GENERALJSON_TRAN_REQUEST;
		mdltype = DPSDK_MDL_DMS;
		strJson.clear();
	}
	virtual ~GeneralJsonSendToDMSMsg(void){}

	std::string strJson;
};

typedef DPSDK_API struct OSDInfo
{
	std::string			strDevId;						// 设备id
	int			        channelID;						// 通道
	std::string			strOSDText;						// osd文本
	int					nForeground;					// 前景色
	int					nBackground;					// 背景色
	int					nLeft;							// 显示位置
	int					nTop;
	int					nRight;
	int					nBottom;
	int					nRemainTime;					// osd叠加，叠加持续时间 0：为一直叠加
}OSDInfo_t;

class DPSDK_API OSDNotifyMsg : public ServerBaseMsg
{
public:
	OSDNotifyMsg(void);
	virtual ~OSDNotifyMsg(void);

public:
	dsl::DStr	strDevId;
	char*		pData;
	int			nLen;
	int			nRemainTime;			// osd叠加，叠加持续时间 0：为一直叠加
};

// 查询空闲动作
class DPSDK_API PtzIdleQueryMsg : public ServerBaseMsg
{
public:
	PtzIdleQueryMsg();
	virtual ~PtzIdleQueryMsg() {}

	bool bEnable;							//使能,false 关闭,true 开启
	int nMotionNo;							//空闲动作类型编号,比如空闲动作为预置点，该值为预置点编号
	int nLeasureTime;						//空闲动作的超时时间,单位min,范围1~60分钟
	dpsdk_ptz_ideltype_e eIdleMotionType;	//空闲动作类型
};

// 设置空闲动作
class DPSDK_API PtzIdleSetMsg : public ServerBaseMsg
{
public:
	PtzIdleSetMsg();
	virtual ~PtzIdleSetMsg() {}

	bool bEnable;							//使能,false 关闭,true 开启
	int nMotionNo;							//空闲动作类型编号,比如空闲动作为预置点，该值为预置点编号
	int nLeasureTime;						//空闲动作的超时时间,单位min,范围1~60分钟
	dpsdk_ptz_ideltype_e eIdleMotionType;	//空闲动作类型
};

// 查询前端设备热度图信息
class DPSDK_API QueryHeatMapMsg : public DPSDKCBMessage
{
public:
	QueryHeatMapMsg();
	virtual ~QueryHeatMapMsg() {}

	std::string strDeviceID;				//设备ID
	int iChnlNum;							//通道号
	std::string strStartTime;				//开始时间
	std::string strEndTime;					//结束时间
};

// 前端设备抓图
class DPSDK_API DevSnapPictureMsg : public ServerBaseMsg
{
public:
	DevSnapPictureMsg();
	virtual ~DevSnapPictureMsg() {}

public:
	//request
	int nPicNum;							//图片数量
	int nSnapType;							//抓图类型
	int nCmdSrc;

	//reponse
	std::string strPicInfo;					//返回数据
};

// 开始生产全景图
class DPSDK_API StartGenerateWideViewMsg : public DPSDKCBMessage
{
public:
	StartGenerateWideViewMsg();
	virtual ~StartGenerateWideViewMsg() {}

	std::string strDeviceID;				//设备ID
	int nChnlNum;							//通道号
};

// 停止获取全景云台图片
class DPSDK_API StopGenerateWideViewMsg : public DPSDKCBMessage
{
public:
	StopGenerateWideViewMsg();
	virtual ~StopGenerateWideViewMsg() {}

	std::string strDeviceID;				//设备ID
	int nChnlNum;							//通道号
};

// 获取全景图读取进度
class DPSDK_API GetWideViewStateMsg : public DPSDKCBMessage
{
public:
	GetWideViewStateMsg();
	virtual ~GetWideViewStateMsg() {}

	std::string strDeviceID;				//设备ID
	int nChnlNum;							//通道号
};

// 云台坐标
typedef struct DPSDK_API tagPtzCoordinate
{
	double					fPositionX;
	double					fPositionY;
	double					fZoom;

	tagPtzCoordinate()
	{
		fPositionX = 0.0f;
		fPositionY = 0.0f;
		fZoom = 0.0f;
	}
}dpsdk_ptz_coordinate_t;

// 根据普通云台坐标获取到全景图云台坐标
class DPSDK_API GetWideViewPointsMsg : public DPSDKCBMessage
{
public:
	GetWideViewPointsMsg();
	virtual ~GetWideViewPointsMsg() {}

	std::string strDeviceID;				//设备ID
	int nChnlNum;							//通道号
	unsigned int nPointCount;				//云台坐标数量
	dpsdk_ptz_coordinate_t pPoint[DPSDK_POINT_COUNT];	//云台坐标
};

// 全景云台坐标
typedef struct DPSDK_API tagWideViewPoint
{
	int						iBottom;
	int						iLeft;
	int						iRight;
	int						iTop;

	tagWideViewPoint()
	{
		iBottom = 0;
		iLeft = 0;
		iRight = 0;
		iTop = 0;
	}
}dpsdk_wideview_point_t;

// 根据全景图云台坐标获取到普通云台坐标
class DPSDK_API GetPtzCoordinateMsg : public DPSDKCBMessage
{
public:
	GetPtzCoordinateMsg();
	virtual ~GetPtzCoordinateMsg() {}

	std::string strDeviceID;				//设备ID
	int nChnlNum;							//通道号
	unsigned int nPointCount;				//全景云台坐标数量
	dpsdk_wideview_point_t pPoint[DPSDK_POINT_COUNT];	//全景云台坐标
};

class DPSDK_API GetWideViewImgDataMsg : public DPSDKCBMessage
{
public:
	GetWideViewImgDataMsg();
	virtual ~GetWideViewImgDataMsg() {}

	std::string strDeviceID;				//设备ID
	int nChnlNum;							//通道号
};

class DPSDK_API GetPtzStatusMsg : public DPSDKCBMessage
{
public:
	GetPtzStatusMsg();
	virtual ~GetPtzStatusMsg() {}

	std::string strDeviceID;				//设备ID
	int nChnlNum;							//通道号
};

// 获取球机云台参数
class DPSDK_API QueryPtzParamMsg : public ServerBaseMsg
{
public:
	QueryPtzParamMsg();
	virtual ~QueryPtzParamMsg() {}

public:
	//request
	char			szDevId[DPSDK_CHL_ID_LEN];								// 设备id

	//response
	int				nZoom;													// 云台光圈变动位置,有效范围：[0,128]
	int				nX;														// 云台水平运动位置,有效范围：[0,3600]
	int				nY;														// 云台垂直运动位置,有效范围：[-1800,1800]
};

// 设置球机云台参数
class DPSDK_API SetPtzParamMsg : public ServerBaseMsg
{
public:
	SetPtzParamMsg();
	virtual ~SetPtzParamMsg() {}

public:
	//request
	//char			szDevId[DPSDK_DEV_ID_LEN];								// 设备id
	//int				nChnlNum;												// 通道号
	dpsdk_Set_Ptz_Param_Info	stuSetPtzParamInfo;							// 球机云台参数

	//response
	bool			bResult;												// 返回结果
	int				nErrCode;												// 错误码，bResult为false时有效
	std::string		strErrMsg;												// 错误信息
};

// 连接通道ID对应的DMS服务
class DPSDK_API ConnectDmsByChnlIdMsg : public ServerBaseMsg
{
public:
	ConnectDmsByChnlIdMsg();
	virtual ~ConnectDmsByChnlIdMsg() {}

	//response
	char			szServerAddr[CHAR_LEN_512];								//DMS服务地址 协议里面的格式： ip1:port1|ip2:port2|ip3:port3|ip4:port4|ip5:port5|
};

//////////////////////////////////////////////////////////////////////////

class DPSDK_API IDPSDKPtz : public IDPSDKFuncBase
{
public:
	/** 云台方向控制
	    @param dpsdk_ptz_direct_e direct_e					操作方向
	    @param const char* cameraId							摄像头ID
	    @param int step										步长
		@param bool bstop									停止标志位：默认false, true-停止
		@param const char* strChannelSn						通道唯一标识码
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int PtzDirection(dpsdk_ptz_direct_e direct_e, const char* cameraId, int step, bool bstop = false, const char* szChannelSn = "") = 0;

	/** 变焦，变距，光圈操作
	    @param dpsdk_camera_operation_e cameraOper_e		操作命令
	    @param const char* cameraId							摄像头ID
	    @param int step										步长
		@param bool bstop									停止标志位：默认false, true-停止
		@param const char* strChannelSn						通道唯一标识码
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int PtzCameraOperation(dpsdk_camera_operation_e cameraOper_e, const char* cameraId, int step, bool bstop = false, const char* szChannelSn = "") = 0;

	/** 三维定位
	    @param const char* cameraId							摄像头ID
	    @param int pointX									水平坐标
	    @param int pointY									垂直坐标
		@param int pointZ									变倍数
		@param int type										类型：1-快速定位 2-精确定位
		@param const char* strChannelSn						通道唯一标识码
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int PtzSit(const char* cameraId, int pointX, int pointY, int pointZ, int type = 1, const char* szChannelSn = "", int nWndWidth = 0, int nWndHeight = 0) = 0 ;

	/** 锁定/解锁
	    @param const char* cameraId							摄像头ID
		@param dpsdk_ptz_locktype_e Lock_e					锁定/解锁
		@param int type										类型 : 1-发DMS 2-发CMS
		@param int szNetSN									互联网SN
		@param int lockTime									锁定时间，单位秒,为0的表示一直锁定，直到释放或者被抢夺
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int PtzLockCamera(const char* cameraId, dpsdk_ptz_locktype_e Lock_e, int type = 1, const char* szNetSN = NULL, uint32_t lockTime = 0) = 0;

	/** 灯光
	    @param const char* cameraId							摄像头ID
		@param bool bOpen									true打开/false关闭 
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int PtzLightControl(const char* cameraId, bool bOpen) = 0 ;

	/** 雨刷
	    @param const char* cameraId							摄像头ID
		@param bool bOpen									true打开/false关闭
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int PtzRainBrushControl(const char* cameraId, bool bOpen) = 0;

	/** 红外灯
	    @param const char* cameraId							摄像头ID
		@param bool bOpen									true打开/false关闭
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int PtzInfraredControl(const char* cameraId, bool bOpen) = 0;
	
	/** 查询预置点
	    @param const char* cameraId							摄像头ID
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryPrePoint(const char* cameraId) = 0;

	/** 查询预置点（带预置点信息）
	    @param const char* cameraId							摄像头ID
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryPrePointEx(const char* cameraId) = 0;

	/** 查询时间段内的预置点
	    @param const char* cameraId							摄像头ID
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryTimePrePoint(const char* cameraId) = 0;
	
	/** 预置点操作
	    @param dpsdk_ptz_prepoint_cmd_e oper_e				操作类型(设置，删除，定位)
	    @param const char* cameraId							摄像头ID
	    @param int prePointId								预置点编号
		@param const char* prePointName						预置点名称
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int PtzPrePointOperation(dpsdk_ptz_prepoint_cmd_e oper_e, const char* cameraId, int prePointId, const char* prePointName, const char* pNetSN = NULL) = 0;

	/** 设置云台定时任务配置
	    @param const char* cameraId							摄像头ID
	    @param const char* szBuf							云台定时任务信息
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SetPtzTimeTask(const char* cameraId, const char* szBuf) = 0;

	/** 获取云台定时任务配置
	    @param const char* cameraId							摄像头ID
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryPtzTimeTask(const char* cameraId) = 0;

	/** 预置点操作
	    @param dpsdk_ptz_prepoint_cmd_e oper_e				操作类型(设置，删除，定位)
	    @param const char* cameraId							摄像头ID
	    @param int prePointId								预置点编号
		@param const char* prePointName						预置点名称
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int PtzTimePrePointOperation(dpsdk_ptz_prepoint_cmd_e oper_e, const char* cameraId, int prePointId, const char* beginTime, const char* endTime, const char* prePointName) = 0;
	
	/** 设置预置点有效时间段
	    @param const char* cameraId							摄像头ID
	    @param int prePointId								预置点编号
		@param int beginTime								预置点编号
		@param int endTime   								预置点编号
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SetPrePointTime(const char* cameraId, int prePointId,const char* prePointName, const char* beginTime,const char* endTime) = 0;
	
	/** 查询巡航线
	    @param const char* cameraId							摄像头ID
		@param int clientId									-B需求，设0时表示不区分用户，设-1使用CMS登录后的client id
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryCruise(const char* cameraId, int clientId = -1) = 0;

	/** 保存巡航线到CMS
		@param const char* cameraId							摄像头ID
		@param const char* cruiseXml						巡航线信息文件
		@param uint32_t buffLen								xml长度
		@param int clientId									-B需求，设0时表示不区分用户，设-1使用CMS登录后的client id
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SaveCruise(const char* cameraId, const char* cruiseXml, uint32_t buffLen, int clientId = -1) = 0;

	/** 保存巡航线到设备
		@param const char* cameraId							摄像头ID
		@param const char* cruiseXml						巡航线信息文件
		@param uint32_t buffLen								xml长度
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SaveCruiseToDevice(const char* cameraId, const char* cruiseXml, uint32_t buffLen, int clientId = -1) = 0;

	/** 开始或停止巡航
		@param int cruiseId									巡航线ID
		@param int cmd										0开始，1停止
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int PtzCruiseOperation(const char* cameraId, int cruiseId, int cmd) = 0;

	/** 云台扩展命令控制
	    @param dpsdk_advance_ptz_cmd_e cmd_e				命令
	    @param const char* cameraId							摄像头ID
		@param int param									辅助参数
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int PtzExtendCommand(dpsdk_ptz_extend_cmd_e cmd_e, const char* cameraId, int param = -1) = 0;

	/** 报警动作输出
		@param const char* cameraId							摄像头ID
		@param bool bOpen									打开标志：true-打开, false-关闭
		@param int nCmd										控制命令。状态控制。1=开启，0=关闭     模式控制：0=关闭  1=自动 2=手动 3常闭模式下关闭，4常闭模式手动
		@param int nType									控制类型。1状态控制 2 模式控制
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int PtzCtrlOut(const char* cameraId, bool bOpen , int nCmd=0, int nType=0) = 0;

	/** 报警动作输出
		@param const char* deviceId							设备ID
		@param int chnlNum									报警输出通道号
		@param bool bOpen									打开标志：true-打开, false-关闭
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int PtzCtrlOut( const char* deviceId, int chnlNum, bool bOpen ) = 0;
	
	/** 报警动作输出
		@param const char* cameraId							设备ID
		@param bool bOpen									打开标志：true-打开, false-关闭
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryDevPTZStatusInfo(const char* szDevId) = 0;
	
	/** 查询设备报警输入通道启用状态
		@param const char* cameraId							摄像头ID
		@param int iChnlCount								通道个数
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryAlarmInStatus(const char* cameraId, bool bQueryDev = false, int iChnlCount = 0) = 0;

	/** 报警输入通道是否启用
		@param const char* cameraId							摄像头ID
		@param bool bEnable									是否启用
		@param ,int nSetType								0：按通道查询，其余按设备设置
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SetAlarmInEnable(const char* cameraId, bool bEnable,int nSetType = 0) = 0;

	/** 查询云台三维定位信息
		@param const char* cameraId							摄像头ID
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryPtzSitInfo(const char* cameraId) = 0;

    /** NVR通道状态
		@param const char* 	deviceId						设备ID
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryNVRChnlStatus(const char* deviceId, int nChannelNum = -1) = 0;
	
	/** 云台报警订阅
	    @param uint32_t nSubscribeFlag						订阅标记。0:取消订阅，1：订阅
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SubscribePtzSitAlarm(const char* cameraId,uint32_t nSubscribeFlag) = 0;

	/** 控制电动聚焦设备
		@param const char* deviceId
		@param int cmd										0=重置   1=连续聚焦    2=自动聚焦
		@param float zoom
		@param float foces
		@return
	*/
	virtual int FocuseControl(const char* deviceId, int cmd, float zoom, float focus) = 0;

	/** 查询电动聚焦设备状态
		@param const char* deviceId
		@return
	*/
	virtual int QueryFocseStatue(const char* deviceId) = 0;

	/** 通道可视域信息查询
		@param const char* cameraId							通道ID
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryChannelViewInfo(const char* cameraId) = 0;

    /** 设备可视域信息查询
		@param const char* 	deviceId						设备ID
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryDeviceViewInfo(const char* deviceId) = 0;

    /** 设置通道当前可视域信息
		@param const char* cameraId							通道ID
		@param const int nAzimuthH							起始弧度修改
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SetChannelViewInfo(const char* cameraId,int nAzimuthH) = 0;

	/** 批量获取预置点
		@param const char* cameraIds						通道ID
		@param const int nIdLen								ID长度
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryLotPoints(const char* cameraId, int nIdLen) = 0;

	/** 查询设备报警输出通道启用状态
		@param const char* cameraId							摄像头ID
		@param int nBroadcast								是否广播，客户端登陆时查询设为0，开启关闭输出通道之后再查询设为1
		@param int nChnlNo									通道号，-2表示根据通道ID解析出来的通道号查询通道，-1表示查询设备，大于等于0表示根据传入的通道号查询通道
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryAlarmOutStatus(const char* cameraId, int nBroadcast, int nChnlNo = -2) = 0;
	
	/** 查询主备状态
		@param const char* deviceId
		@return
	*/
	virtual int QueryDeviceClusterStatus(const char* deviceId) = 0;

	/**	鱼眼配置
		@param const char* deviceId							设备ID
		@param int channelNo								通道号
		@param dpsdk_fisheye_fitmode_e nFitMode				安装模式
		@parma dpsdk_fisheye_displaymode_e nDisplayMode		展示模式
		@return
	*/
	virtual int FishEyeSetInfo(const char* deviceId, int channelNo, dpsdk_fisheye_fitmode_e nFitMode, dpsdk_fisheye_displaymode_e nDisplayMode) = 0;

	/** 鱼眼控制
		@param const char* deviceId							设备ID
		@param int channelNo								通道号
		@param dpsdk_fisheye_funbtn_e nFunBtn				控制命令
		@param int nWindId									控制窗口编号
		@param int nStep									步长
	*/
	virtual int FishEyeControl(const char* deviceId, int channelNo, dpsdk_fisheye_funbtn_e nFunBtn, int nWindId, int nStep) = 0;

	virtual int GeneralJsonSendToDMS(const char* strJson, const char* szDeviceId)=0;

	/** 设置OSD叠加数据
	*/
	virtual int SetOSDInfo(const char* szChannelId, const OSDInfo_t struOSDInfo, const OSDTextAlign_e enumAlign) = 0;

	/** 连接通道ID对应的DMS服务
		@param const char* szChannelId						通道id
	*/
	virtual int ConnectDmsByChnlId(const char* szChannelId) = 0;

	/** 查询球机云台参数
 		@param const char* szDevId							设备id
 	*/
 	virtual int QueryPtzParam(const char* szDevId) = 0;
 
 	/** 设置球机云台参数
 		@param const char* szChannelId						通道id
 		@param dpsdk_Set_Ptz_Param_Info stuParam			球机云台参数
 	*/
 	virtual int SetPtzParam(const char* szChannelId, dpsdk_Set_Ptz_Param_Info stuParam) = 0;
protected:
	virtual ~IDPSDKPtz(void){}
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif
