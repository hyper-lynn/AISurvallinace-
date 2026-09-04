/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,视频上墙子模块
 *
 * 当前版本：1.0
 * 原作者　：12760
 * 完成日期：
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKTVWALL_H
#define INCLUDED_DPSDK_DPSDKTVWALL_H

#include "DPSDK.h"
#include "DPSDKGeneral.h"

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

// 电视墙控制命令
typedef enum
{
	TVWALL_PLAN_TASK					= 0,					// 任务上墙/任务切换 
	TVWALL_ONESCREEN_SHOW				= 1,					// 绑定视频源
	TVWALL_ONESCREEN_CLOSE				= 2,					// 取消视频源
	TVWALL_SCREEN_SPLIT					= 3,					// 画面分割
	TVWALL_WINDOW_OPEN					= 4,					// 开窗
	TVWALL_WINDOW_CLOSE					= 5,					// 关窗
	TVWALL_WINDOW_MOVING				= 6,					// 窗口移动
	TVWALL_WINDOW_ZCONTROL				= 7,					// 置顶
	TVWALL_POWER_CTRL					= 8,					// 屏幕开关

	TVWALL_ONESCREEN_CLOSE_ALL			= 9,					// smartpss使用：关闭单屏(单屏的所有窗口)
	TVWALL_CLOSE_PROJECT,										// 关闭计划
	//9,  // 开启计划任务
	//10,  // 报警任务
	//11,  // 关闭计划任务
	TVWALL_ONESCREEN_CLEAR				= 12,					// 清理单屏,此时只需要对应的_tvIndex、_screenId、_tvType以及_tvWallDBId
	TVWALL_SPLITWIN_MAX					= 14,					// 分割单屏放大
	TVWALL_TOUR_PAUSE					= 15,					// 上墙通道轮巡暂停，此时_screenId若为-1则对整个墙有效；_subTvIndex为-1则对整个屏有效（但_screenId必须是一个有效值）
	TVWALL_TOUR_RESUME					= 16,					// 上墙通道轮巡恢复，同15
	TVWALL_SINGLEWINDOW_CHANGE_SOURCE	= 17,					// 单窗口切换视频源到前一个上墙，_screenId、_subTvIndex都必须有效
	TVWALL_SINGLEWINDOW_SOUND_SWITCH	= 18,					// 单窗口音频开关控制, 此时只需要对应的_tvIndex、_screenId、_subTvIndex、_tvType以及_tvWallDBId，这里用splitNum表示开启（1）或者关闭（0）
	TVWALL_OPENWINDOW_SPLIT				= 22,					//开窗窗口中分割
}dpsdk_tvwall_control_e;

// CMS给的电视墙通知消息
typedef enum
{
	TVWALL_NOTIFY_ADD					= 0,					// 新增
	TVWALL_NOTIFY_MOD,											// 修改，本修改通知消息权限字段无效，请勿使用
	TVWALL_NOTIFY_DEL,											// 删除
	TVWALL_NOTIFY_MOD_RIGHT,									// 权限修改
	TVWALL_NOTIFY_MOD_CFG,										// 生效修改
}dpsdk_tvwall_notify_e;

// 上墙模式,安徽三联项目
typedef enum
{
	TVWALL_GENERAL						= 0,					// 普通模式
	TVWALL_PIP,													// 画中画模式
}dpsdk_tvwall_pip_e;

// 电视墙锁定/解锁类型
typedef enum
{
	TVWALL_CMD_UNKNOWN					= -1,
	TVWALL_CMD_UNLOCK_ONE				= 0,					// 解锁当前电视墙
	TVWALL_CMD_LOCK_ONE					= 1,					// 锁定当前电视墙
	
}dpsdk_tvwall_locktype_e;

// 屏幕位置
struct screenPos  
{
	float left;													// 屏幕左边距
	float top;													// 屏幕上边距
	float width;												// 屏幕宽度
	float height;												// 屏幕高度
	
	screenPos(void)
	{
		left	= 0;
		top		= 0;
		width	= 0;
		height	= 0;
	}
};

struct PicInPicInfo
{
	int							nScreenID;
	int							nLeft;
	int							nTop;
	int							nRight;
	int							nBottom;
	int							nBigChnNum;
	int							nSmallChnNum;
	dpsdk_tvwall_pip_e          enPIP;               

	PicInPicInfo()
	{
		nScreenID		= 0;
		nLeft			= 0;
		nTop			= 0;
		nRight			= 0;
		nBottom			= 0;
		nBigChnNum		= 0;
		nSmallChnNum	= 0;
		enPIP			= TVWALL_GENERAL;
	}
};

// 上墙控制操作
typedef struct DPSDK_API tagTvWallControl
{
	tagTvWallControl(void);
	~tagTvWallControl(void);

	dpsdk_tvwall_control_e	controlType;						// 控制命令
	char					matrixId[DPSDK_MATRIXID_LEN];		// 解码器、矩阵等解码设备ID
	uint32_t				tvIndex;							// 屏号，普通屏为解码通道号，融合屏为屏ID
	uint32_t				subTvIndex;							// 子屏号（融合屏有效）
	uint32_t				tvType;								// 屏类型：0-非融合屏，1-融合屏
	uint32_t				splitNum;							// 屏分割或开窗数
	char*					taskData;							// xml数据（参见xml格式）
	uint32_t				taskLen;							// xml数据长度
	screenPos				scrPos;								// 屏位置
	uint32_t				tvWallDBId;							// 电视墙配置方案DBId
	uint32_t				tvWallVersion;						// 电视墙版本号
	uint32_t				screenId;							// 屏ID	适用于即时模式对单屏时的操作，任务模式无效
	int32_t                 zoder;                              // Z序，-1 置底，0置顶
	int32_t					subWindNo;							//开窗窗口中选中的分割屏号
}TvWallControl_t;

// 电视墙列表信息
typedef struct DPSDK_API tagTvWallListInfo
{
	uint32_t	id;												// 电视墙ID
	char		name[DPSDK_FILENAME_LEN];						// 电视墙名称
	char		coding[DPSDK_CODING_LEN];						// 
	uint32_t	state;											// 启用状态
	uint32_t	right;											// 权限
	uint32_t	version;										// 电视墙版本号

	tagTvWallListInfo(void);
}TvWallListInfo_t;

// 电视墙预案信息
typedef struct DPSDK_API tagTvWallSchemeInfo
{
	tagTvWallSchemeInfo(void);
	~tagTvWallSchemeInfo(void);

	char		szName[64];										// 
	char*		pLayoutData;									// 
	int			nLayoutDataLen;									// 
	char*		pTaskData;										// 
	int			nTaskDataLen;									// 
	int			nTaskCount;										// 
}TvWallSchemeInfo_t;

// 边界信息
typedef struct DPSDK_API tagTvWallBoundary
{
	int			nLeft;											// 左边距
	int			nTop;											// 上边距
	int			nRight;											// 右边距
	int			nBottom;										// 下边距

	tagTvWallBoundary()
	{
		nLeft = 0;
		nTop = 0;
		nRight = 0;
		nBottom = 0;
	}
}TvWallBoundary_t;

// 色调信息
typedef struct DPSDK_API tagTvWallVideoColor
{
	int			nBeginHour;										// 开始时间（时）
	int			nBeginMinute;									// 开始时间（分）
	int			nBeginSecond;									// 开始时间（秒）
	int			nEndHour;										// 结束时间（时）
	int			nEndMinute;										// 结束时间（分）
	int			nEndSecond;										// 结束时间（秒）
																
	int			nBrightness;									// 亮度, 1~100
	int			nContrast;										// 对比度, 1~100
	int			nSaturation;									// 饱和度, 1~100
	int			nHue;											// 色调, 1~100

	tagTvWallVideoColor()
	{
		nBeginHour = 0;
		nEndMinute = 0;
		nBeginSecond = 0;
		nEndHour = 0;
		nEndMinute = 0;
		nEndSecond = 0;

		nBrightness = 0;
		nContrast = 0;
		nSaturation = 0;
		nHue = 0;
	}
}TvWallVideoColor_t;

// 安徽三联项目画中画上墙控制操作
typedef struct DPSDK_API tagPIPTvWallControl
{
	tagPIPTvWallControl(void);
	~tagPIPTvWallControl(void);

	char			matrixId[DPSDK_MATRIXID_LEN];				// 解码器、矩阵等解码设备ID
	PicInPicInfo	picInPicInfo[DPSDK_PIP_SCREEN_NUM];			// 画中画上墙信息
}PIPTvWallControl_t;

typedef struct DPSDK_API tagTvWallRunInfo
{
	int		nTVWallId;
	char	chPorjectName[DPSDK_FILENAME_LEN];
	char	chTaskId[DPSDK_FILENAME_LEN];
	tagTvWallRunInfo()
	{
		nTVWallId = 0;
		memset(chPorjectName,0,DPSDK_FILENAME_LEN);
		memset(chTaskId,0,DPSDK_FILENAME_LEN);
	}
}TvWallRunInfo_t;

//屏幕加框需要的信息
typedef struct DPSDK_API TvWallScreenAddFrame
{
	char		szDevId[DPSDK_MATRIXID_LEN];				// 设备Id
	int			nTvWallId;									// 电视墙Id
	int			nTvScreenId;								// 屏幕Id
	int			nSubTvId;									// 窗口Id
	int			nTvIndex;									// 如果是融合屏 和screenId一致,	非融合屏 传的是通道号
	int			nTvType;									// 0 非融合屏， 1 融合屏
	bool		bAddFrame;									// 是否加框使用false：不加，true：加

	TvWallScreenAddFrame()
	{
		memset(szDevId, 0 , sizeof(szDevId));
		nTvWallId	 = 0;
		nTvScreenId	 = 0;
		nSubTvId	 = 0;
		nTvIndex	 = 0;
		nTvType		 = 0;
		bAddFrame	 = false;
	}

}TvWallScreenAddFrame_t;
//////////////////////////////////////////////////////////////////////////

// 获取电视墙列表消息
class DPSDK_API GetTvWallListMsg: public DPSDKCBMessage
{
public:
	GetTvWallListMsg(void);
	virtual ~GetTvWallListMsg(void);

public:
	uint32_t			count;									// 电视墙个数
	TvWallListInfo_t*	pInfo;									// 列表信息
};

// 获取电视墙详细信息消息（列表获取之后根据电视墙ID获取详细信息）
class DPSDK_API GetTvWallInfoMsg: public DPSDKCBMessage
{
public:
	GetTvWallInfoMsg(void);
	virtual ~GetTvWallInfoMsg(void);

public:
	// request
	uint32_t	id;												// 电视墙ID
	int			getType;										// 获取电视墙配置的类型，0：用于获取普通电视墙任务或计划配置，1：用于获取报警联动电视墙配置

	// response
	char*		data;											// 电视墙信息xml数据
	uint32_t	len;											// 数据长度
};

// 获取电视墙的预案列表
class DPSDK_API GetTvWallSchemeListMsg: public DPSDKCBMessage
{
public:
	GetTvWallSchemeListMsg(void);
	virtual ~GetTvWallSchemeListMsg(void);

public:
	// request
	uint32_t	id;												// 电视墙ID

	// response
	struct SchemeInfo
	{
		int id;													// 预案id
		char name[64];											// 预案名称
		char dec[256];											// 预案描述信息:todo::根据协议定义大小
		int sortID;												// 预案的排序号
	}*schemeinfos;
	uint32_t	schemeNum;
};

// 获取电视墙预案详细信息消息（或者当前场景）
class DPSDK_API GetTvWallSchemeInfoMsg: public DPSDKCBMessage
{
public:
	GetTvWallSchemeInfoMsg(void);
	virtual ~GetTvWallSchemeInfoMsg(void);

public:
	// request
	uint32_t	tvwallid;										// 电视墙ID
	uint32_t	schemeid;										// 任务ID
	char		decoderid[64];									// 解码器ID
	uint32_t	type;											// 获取内容类型, 1 电视墙任务xml， 2 当前场景

	// response
	char*		data;											// 电视墙信息xml数据
	uint32_t	len;											// 数据长度
};

class DPSDK_API ModifySchemeBaseInfoMsg: public DPSDKCBMessage
{
public:
	ModifySchemeBaseInfoMsg(void);
	virtual ~ModifySchemeBaseInfoMsg(void){}

public:
	// request
	uint32_t	tvwallid;										// 电视墙ID
	uint32_t	schemeid;										// 任务ID
	char		schemename[64];									// 任务名称
	char		schemedesc[256];								// 任务描述
	uint32_t	sortID;											// 任务排序号
};

// 删除电视墙任务
class DPSDK_API DelTvWallTaskMsg: public DPSDKCBMessage
{
public:
	DelTvWallTaskMsg(void);
	virtual ~DelTvWallTaskMsg(void){}

public:
	// request
	uint32_t	tvwallid;										// 电视墙ID
	uint32_t	taskid;											// 任务ID
	char		fileName[256];									// 任务名称
};

// 客户端上墙控制（注意区分控制类型）
class DPSDK_API MapToTvWallMsg: public DPSDKCBMessage
{
public:
	MapToTvWallMsg(void);
	virtual ~MapToTvWallMsg(void);

public:
	TvWallControl_t	control;									// 控制结构体

	//response
	std::string strBody;
};

// 电视墙布局配置消息【PSS专用】
class DPSDK_API DecoderConfigMsg : public DPSDKCBMessage
{
public:
	DecoderConfigMsg(void);
	virtual ~DecoderConfigMsg(void);

public:
	char*		pXmlData;										// 布局xml数据
	int			nLen;											// 数据长度
};

// 电视墙变更通知消息
class DPSDK_API TvWallNotifyMsg : public DPSDKCBMessage
{
public:
	TvWallNotifyMsg(void);
	virtual ~TvWallNotifyMsg(void) {};

public:
	dpsdk_tvwall_notify_e	notifyType;							// 消息通知类型
	TvWallListInfo_t		notifyInfo;							// 电视墙变更后的数据信息
	char					szDevIds[DPSDK_CFGCHANGE_DEVIDS];	// 涉及设备编号
};

// 预案配置消息
class DPSDK_API TvWallSchemeConfigMsg : public DPSDKCBMessage
{
public:
	TvWallSchemeConfigMsg(void);
	virtual ~TvWallSchemeConfigMsg(void);

public:
	char				szDevId[DPSDK_MATRIXID_LEN];			// 设备ID
	int					nSchemeCount;							// 预案个数
	TvWallSchemeInfo_t*	pSchemeInfo;							// 预案
};

// 获取设备当前任务信息
class DPSDK_API TvWallGetRunTaskMsg : public DPSDKCBMessage
{
public:
	TvWallGetRunTaskMsg(void);
	virtual ~TvWallGetRunTaskMsg(void);

public:
	// request
	char		szDevId[DPSDK_MATRIXID_LEN];					// 设备ID

	// response
	char*		pTaskData;										// 
	int			nDataLen;										// 
};

// 电源控制消息
class DPSDK_API TvWallPowerControlMsg : public DPSDKCBMessage
{
public:
	TvWallPowerControlMsg(void);
	virtual ~TvWallPowerControlMsg(void);

public:
	char		szDevId[DPSDK_MATRIXID_LEN];					// 设备Id
	int			nTvWallId;										// 电视墙Id
	int			nTvScreenId;									// 屏幕Id
	bool		bPowerOn;										// 是否打开电源
	//int32_t     channelNum;                                     // 物理通道号,-1 无效
};

// 信号调节消息
class DPSDK_API TvWallSignalAdjustMsg : public DPSDKCBMessage
{
public:
	TvWallSignalAdjustMsg(dpsdk_cmd_e cmd);
	virtual ~TvWallSignalAdjustMsg(void);

public:
	char						szDevId[DPSDK_MATRIXID_LEN];	// 
	TvWallBoundary_t			stuBoundary;					// 
	int							nColorCount;					// 
	const TvWallVideoColor_t*	pVideoColor;					// 
};

// 电视墙布局
class DPSDK_API TvWallLayoutCfgMsg : public DPSDKCBMessage
{
public:
	TvWallLayoutCfgMsg(void);
	virtual ~TvWallLayoutCfgMsg(void){};

public:
	int							nDbId;							// 
};

// 安徽三联项目画中画上墙控制（注意区分控制类型）
class DPSDK_API PIPMapToTvWallMsg: public DPSDKCBMessage
{
public:
	PIPMapToTvWallMsg(void);
	virtual ~PIPMapToTvWallMsg(void);

public:
	PIPTvWallControl_t			pipControl;						// 画中画上墙控制结构体
};

// SNVD端口上墙播放速度设置
class DPSDK_API TvWallSNVDPlayPortMsg : public DPSDKCBMessage
{
public:
	TvWallSNVDPlayPortMsg(void);
	virtual ~TvWallSNVDPlayPortMsg(void){};

public:
	char						szDevId[DPSDK_MATRIXID_LEN];
	int							nPort;
	float						fSpeed;
};

// 电视墙锁定/解锁
class DPSDK_API TvWallLockMsg : public DPSDKCBMessage
{
public:
	TvWallLockMsg(void);
	virtual ~TvWallLockMsg(void){};

public:
	int						nTvWallId;
	int						nUserId;							// 用户id
	char					clientName[DPSDK_CLIENT_NAME_LEN];	// 持有锁的用户名称
	int						clientLevel;						// 持有锁的用户级别
	dpsdk_tvwall_locktype_e	nLock_e;							// 0：解锁 1：加锁
	int						nRetainTime;						// 持锁时间
};

// 电视墙计划运行信息查询
class DPSDK_API TvWallProjRunInfoMsg:public DPSDKCBMessage
{
public:
	TvWallProjRunInfoMsg(void);
	virtual ~TvWallProjRunInfoMsg(void);

public:
	int					nTVWallId;
	TvWallRunInfo_t*	tvWallRunInfo;
	int					nWallRunInfoNum;
};

class DPSDK_API TvWallRunInfoNotify:public DPSDKCBMessage
{
public:
	TvWallRunInfoNotify(void);
	virtual ~TvWallRunInfoNotify(void);

public:
	TvWallRunInfo_t*	tvWallRunInfo;
	int					nWallRunInfoNum;
};

 //屏幕加框消息
class DPSDK_API TvWallScreenAddFrameMsg : public DPSDKCBMessage
{
public:
	TvWallScreenAddFrameMsg(void);
	virtual ~TvWallScreenAddFrameMsg(void);

public:
	TvWallScreenAddFrame_t	addFrameInfo;
};

//当前电视墙正执行的任务或计划 

class DPSDK_API TvWallCurrentTaskMsg: public GeneralJsonTransportMsg
{
public:
	TvWallCurrentTaskMsg(void)
	{
		m_cmd = DPSDK_CMD_TVWALL_CURRENT_TASK;
		trantype = GENERALJSON_TRAN_REQUEST;
// 		m_nTvwallID = -1;
// 		m_nType = -1;
	}
	virtual ~TvWallCurrentTaskMsg(void){}

public:
// 	int		m_nTvwallID;		// 电视墙编号
// 	int		m_nType;			// 查询类型0-任务;1-计划

};

class DPSDK_API TvWallInfoBySNMsg: public GeneralJsonTransportMsg
{
public:
	TvWallInfoBySNMsg(void)
	{
		m_cmd = DPSDK_CMD_TVWALL_TVWALLINFO_BY_SN;
		trantype = GENERALJSON_TRAN_REQUEST;
		memset(pSN, 0, DPSDK_CHAR_LEN_64);
	}
	virtual ~TvWallInfoBySNMsg(void){}

public:
	char		pSN[DPSDK_CHAR_LEN_64];		// 编号

};

//////////////////////////////////////////////////////////////////////////
//接口统一的定义开始

#define DPSDK_TVWALL_MAX_LAYOUT_COUNT						16
#define DPSDK_TVWALL_MAX_SCREEN_COUNT						80
#define DPSDK_TVWALL_MAX_SCHEME_COUNT						64
#define DPSDK_TVWALL_MAX_WINDOW_COUNT						(DPSDK_TVWALL_MAX_SCREEN_COUNT * 16)
#define DPSDK_TVWALL_MAX_SOURCE_COUNT						1024

#define DPSDK_TVWALL_MAX_LEN_256							256
#define DPSDK_TVWALL_MAX_LEN_128							128
#define DPSDK_TVWALL_MAX_LEN_64								64
#define DPSDK_TVWALL_MAX_LEN_8								8
#define DPSDK_TVWALL_SCHEDULE_DAY_COUNT						8
#define DPSDK_TVWALL_TIME_SECTION_COUNT						6

#define DPSDK_TVWALL_WIDTH									8192
#define DPSDK_TVWALL_HEIGHT									8192

// 窗口坐标
typedef struct DPSDK_API tagTvWallRect
{
	float nLeft;																				// 左坐标
	float nTop;																				// 上坐标
	float nRight;																				// 右坐标
	float nBottom;																			// 下坐标
}TvWallRect_t;

// 输出屏
typedef struct DPSDK_API tagTvWallOutputScreen
{
	char				szName[DPSDK_TVWALL_MAX_LEN_128];														// 名称
	int					nChannel;																				// 通道号
}TvWallOutputScreen_t;

// 融合屏
typedef struct DPSDK_API tagTvWallScreen
{
	char                    szCompositeID[DPSDK_TVWALL_MAX_LEN_128];											// 融合屏ID(同一设备不能重复)
	char					szName[DPSDK_TVWALL_MAX_LEN_128];													// 名称
	TvWallRect_t			stuRect;																			// 坐标

	int						nOutputScreenCount;																	// 物理屏数量
	TvWallOutputScreen_t	stuOutputScreen[DPSDK_TVWALL_MAX_SCREEN_COUNT];										// 物理屏信息
}TvWallScreen_t;

// 布局
typedef struct DPSDK_API tagTvWallLayout
{
	int						nLayout;																			// 布局序号(AddLayout时无效)
	bool					bEnable;																			// 启用状态
	char					szName[DPSDK_TVWALL_MAX_LEN_64];													// 名称
	char					szDescribe[DPSDK_TVWALL_MAX_LEN_256];												// 描述
	int						nGridRow;																			// 网格行数
	int						nGridCol;																			// 网格列数

	int						nScreenCount;																		// 融合屏数量
	TvWallScreen_t			stuScreen[DPSDK_TVWALL_MAX_SCREEN_COUNT];											// 融合屏信息
}TvWallLayout_t;

// 布局状态
typedef struct DPSDK_API tagTvWallLayoutStatus
{
	char					szName[DPSDK_TVWALL_MAX_LEN_128];													// 名称
	bool					bEnable;																			// 启用状态
}TvWallLayoutStatus_t;

// 设备
typedef struct DPSDK_API tagTvWallDevice
{
	char					szDomain[DPSDK_TVWALL_MAX_LEN_64];													// IP/域名	
	int						nPort;																				// 端口
	char					szUsername[DPSDK_TVWALL_MAX_LEN_8];													// 用户名
	char					szPassword[DPSDK_TVWALL_MAX_LEN_8];													// 密码
}TvWallDevice_t;

// 视频源
typedef struct DPSDK_API tagTvWallSource
{
	TvWallDevice_t			stuDevice;																			// 设备信息
	int						nStreamType;																		// 码流类型，参见TvWallStreamType_e
	int						nChannelCount;																		// 通道总数(设置时有效)
	int						nChannel;																			// 通道号
}TvWallSource_t;

// 窗口轮巡
typedef struct DPSDK_API tagTvWallWindowTour
{
	int						nSourceCount;																		// 视频源数量
	TvWallSource_t			stuSource[DPSDK_TVWALL_MAX_SOURCE_COUNT];											// 视频源信息
}TvWallWindowTour_t;

// 时间段结构
typedef struct DPSDK_API tagTimeSection
{
	bool					bEnable;																			// 使能

	int						nBeginHour;																			// 开始时间（时）
	int						nBeginMinute;																		// 开始时间（分）
	int						nBeginSecond;																		// 开始时间（秒）
	int						nEndHour;																			// 结束时间（时）
	int						nEndMinute;																			// 结束时间（分）
	int						nEndSecond;																			// 结束时间（秒）
}TimeSection_t;

// 预案时间表
typedef struct DPSDK_API tagTvWallSchemeSchedule
{
	char					szName[DPSDK_TVWALL_MAX_LEN_64];													// 预案名称
	TimeSection_t			stuSection[DPSDK_TVWALL_SCHEDULE_DAY_COUNT][DPSDK_TVWALL_TIME_SECTION_COUNT];		// 时间表
}TvWallSchemeSchedule_t;

// 预案轮巡
typedef struct DPSDK_API tagTvWallSchemeTour
{
	int						nInterval;																			// 间隔时间
	int						nSchemeCount;																		// 预案数量
	char					szName[DPSDK_TVWALL_MAX_SCHEME_COUNT][DPSDK_TVWALL_MAX_LEN_64];						// 预案名称
}TvWallSchemeTour_t;

// 屏幕电源时间表
typedef struct DPSDK_API tagTvWallPowerSchedule
{
	char					szCompositeID[DPSDK_TVWALL_MAX_LEN_128];											// 融合屏ID
	TimeSection_t			stuSection[DPSDK_TVWALL_SCHEDULE_DAY_COUNT][DPSDK_TVWALL_TIME_SECTION_COUNT];		// 时间表
}TvWallPowerSchedule_t;

// 屏幕底图
typedef struct DPSDK_API tagTvWallBackground
{
	bool					bEnable;																			// 使能
	char					szName[DPSDK_TVWALL_MAX_LEN_256];													// 名称
}TvWallBackground_t;
//////////////////////////////////////////////////////////////////////////
//接口统一的定义结束


//////////////////////////////////////////////////////////////////////////

class DPSDK_API IDPSDKTvWall : public IDPSDKFuncBase
{
public:
	/** 取得上墙方案列表
	    @return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetTvWallList(void) = 0;

	/** 取得电视墙布局信息
	    @param uint32_t id										电视墙id
	    @return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetTvWallInfo(uint32_t id,int nGetType = 0) = 0;

	/** 取得电视墙任务列表
	    @param uint32_t id										电视墙id
	    @return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetTvWallSchemeList(uint32_t id) = 0;

	/** 取得电视墙任务或者场景信息
	    @param uint32_t tvwallid								电视墙id
		@param uint32_t type									标识是获取任务还是场景 1 电视墙任务xml， 2 当前场景
		@param char* decoderid									编码器id
		@param uint32_t schemeid								预案id
	    @return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetTvWallSchemeInfo(uint32_t tvwallid, uint32_t type, char* decoderid, uint32_t schemeid) = 0;

	/** 修改电视墙任务基本信息
	    @param uint32_t tvwallid								电视墙id
		@param uint32_t schemeid								任务id
		@param char*	schemename								任务名称
		@param char*	schemedesc								任务描述
		@remake 只可根据电视墙id与任务id修改任务名称(maxlen=64)和描述信息(maxlen=256)
	    @return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int ModifySchemeBaseInfo(uint32_t tvwallid, uint32_t schemeid, const char* schemename, const char* schemedesc, int schemesort = -1) = 0;

	/** 删除电视墙中的一个任务
	    @param uint32_t tvwallid								电视墙id
		@param uint32_t taskid									任务id
	    @return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int DelTvWallTask(uint32_t tvwallid, uint32_t taskid) = 0;
	
	/** 发送上墙命令 
	    @param TvWallControl_t& control							上墙命令结构体
	    @return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int MapToTvWall(TvWallControl_t& control) = 0;

	/** 布局配置【PSS专用】
	    @param const char* pXmlData								布局XML信息
	    @param int nLen											XML数据长度
		@return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int TvWallSetConfig(const char* pXmlData, int nLen) = 0;

	/** 预案配置
	    @param const char* szDevId								设备ID
	    @param const TvWallSchemeInfo_t* pSchemeInfo			预案信息结构
		@return	int nSchemeCount								预案个数
		@return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SchemeConfig(const char* szDevId, const TvWallSchemeInfo_t* pSchemeInfo, int nSchemeCount) = 0;

	/** 获取当前运行任务
	    @param const char* szDevId								设备ID
		@return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetRunTask(const char* szDevId) = 0;

	/** 屏幕电源控制
	    @param int szDevId										设备ID
		@param int nTvWallId									电视墙ID
		@param int nTvScreenId									屏幕ID
		@param bool bPowerOn									电源开关
		@return													异步顺序码,用于事件回调时,与应答事件匹配
		@remark													屏幕Id如果是融合屏，会控制该融合屏下的所有单屏
	*/
	virtual int PowerControl(const char* szDevId, int nTvWallId, int nTvScreenId, bool bPowerOn) = 0;

	/** 设置信号
	    @param 								
	    @param 											
		@return													
	*/
	virtual int SetSignal(const char* szDevId, int nChannel, const TvWallBoundary_t* pBoundary, const TvWallVideoColor_t* pColor, int nColorCount) = 0;

	/** 获取信号
	    @param 								
	    @param 											
		@return													
	*/
	virtual int GetSignal(const char* szDevId, int nChannel) = 0;

	/** 融合屏ID转虚拟通道号【PSS专用】
	    @param const char* szDevId								
		@param int nCompositeId									
		@return													
	*/
	virtual int CompositeIdToVirtualChannelId(const char* szDevId, int nCompositeId) = 0;

	/** 设置电视墙布局
		@param int nDbId									
		@return													
	*/
	virtual int SetTvWallLayoutCfg(int nDbId) = 0;
	
	/** 安徽三联项目定制画中画上墙功能
		@param PIPTvWallControl_t& pipControl					画中画上墙命令结构体
		@return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int PipMapToTvWall(PIPTvWallControl_t& pipControl) = 0;

	/** 设置SNVD端口上墙端口播放速度
		@param const char* szDevId								SNVD设备ID
		@param float fSpeed										播放速度				
		@param int nPort										连接端口
		@return													
	*/
	virtual int SetSNVDPlayPortSpeed(const char* szDevId, float fSpeed, int nPort) = 0;

	/** 电视墙锁定/解锁
	    @param int nTvwallId									电视墙ID
		@param dpsdk_tvwall_locktype_e Lock_e					锁定/解锁
		@param int nRetainTime									用户持锁时间 单位：秒
		@param int nUserId										用户ID
		@param char* clientName									用户名
		@param int clientlevel									用户级别
		@return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int TvwallLock(int nTvwallId, dpsdk_tvwall_locktype_e Lock_e, int nRetainTime, int nUserId, char* clientName, int clientlevel ) = 0;
	
		/** 屏幕加框控制
	    @param srcAddFrameInfo									加框所需要的信息，参见TvWallScreenAddFrame_t
		@return													异步顺序码,用于事件回调时,与应答事件匹配
		@remark													
	*/
	virtual int SetTvWallScreenAddFrame(const TvWallScreenAddFrame_t& srcAddFrameInfo) = 0;

	/** 查询当前电视墙运行的计划
		@param int nTVWallId									-1:查询所有
		@return
	*/
	virtual int QueryTVWallTaskRunInfo(int nTVWallId) = 0;

	/** 查询当前正在运行的任务ID和当前正在运行的电视墙计划
		@return
	*/
	virtual int QueryTVWallCurrentTask() = 0;

	/** 通过SN号来查询电视墙信息
		@param strSN											屏幕唯一SN码
		@return
	*/
	virtual int QueryTVWallInfobySN(const char* strSN) = 0;


//////////////////////////////////////////////////////////////////////////
//Dss与pss业务统一的接口,下列接口暂不实现，目前是梳理业务过程

//第一期实现开始

	/** 获取场景，即某个设备的当前正在上墙的布局信息
		@param const char* szDevId								设备ID		
		@param const int nLayoutId								布局	
		@return													
	*/
	virtual int GetScene(const char* szDevId, const int nLayoutId) = 0;

	/** 设置分割
		@param const char* szDevId								设备ID		
		@param int nLayoutId									布局	
		@param int nCompositeID                                 屏ID
		@param int nSplitnum                                    分割数,1=分割成1个窗口，2=分割成4个窗口，3=分割成9个窗口，4=分割成16个窗口
		@return													
	*/
	virtual int SetSplit(const char* szDevId, const int nLayoutId, const int nCompositeID, const int nSplitnum ) = 0;

	/** 开窗
		@param const char* szDevId								设备ID	
		@param const int nLayoutId								布局
		@param const int nCompositeID						    融合屏ID
		@param const TvWallRect_t* pRect						窗口信息
		@return													
	*/
	virtual int OpenWindow(const char* szDevId, const int nLayoutId, const int nCompositeID, const TvWallRect_t* pRect) = 0;

	/** 关闭窗
		@param const char* szDevId								设备ID		
		@param const int nLayoutId								布局
		@param const int nCompositeID						    融合屏ID
		@param const int nWnd									窗口号
		@return													
	*/
	virtual int CloseWindow(const char* szDevId, const int nLayoutId, const int nCompositeID, const int nWnd) = 0;
	
	/** 移动窗
		@param const char* szDevId								设备ID		
		@param const int nCompositeID						    融合屏ID
		@param const int nWnd								    窗口号
		@param const TvWallRect_t* pRect						窗口信息
		@return													
	*/
	virtual int MoveWindow(const char* szDevId, const int nLayoutId, const int nCompositeID, const int nWnd, const TvWallRect_t* pRect) = 0;
	
	/** 设置窗Z序
		@param const char* szDevId								设备ID		
		@param const int nCompositeID						    融合屏ID
		@param const int nWnd									窗口号
		@param const int nZOrder								Z序，-1置底，0置顶
		@return													
	*/
	virtual int SetWindowZOrder(const char* szDevId, const int nLayoutId, const int nCompositeID, const int nWnd, const int nZOrder) = 0;


	/** 启用电源
		@param const char* szDevId								设备ID		
		@param const int nLayout								布局id
		@param const int nCompositeID						    融合屏ID
		@param const bool bEnable								是否启用
		@param const int nChannelNum                            物理通道号，-1无效
		@return													
	*/
	virtual int EnablePower(const char* szDevId, const int nLayoutId, const int nCompositeID, const bool bEnable) = 0;

	/** 获取布局，
		@param const int  nLayoutId								布局id									
		@return													
	*/
	virtual int GetLayout(const int nLayoutId) = 0;

    /** 获取布局，目前已废弃
		@param const char* szDevId								设备ID									
		@return													
	*/
	virtual int GetLayout(const char* szDevId) = 0;

	/** 获取预案名称	
		@param const int nLayout								布局id
		@return													
	*/
	virtual int GetSchemeNames(const int nLayoutId) = 0;

	/** 加载预案	
		@param const int nLayout								布局id
		@param const int nSchemeId                              预案id
		@param const char * szSchemeName                        预案名称
		@return													
	*/
	virtual int LoadScheme(const int nLayoutId, const int nSchemeId, const char * szSchemeName) = 0;
	
	/** 保存预案	
		@param const int nLayout								布局id
		@param const int nSchemeId                              预案id
		@param const char * szSchemeName                        预案名称
		@param const char *szData                               预案内容
		@param const int nLen                                   预案长度
		@return													
	*/
	virtual int SaveScheme(const int nLayoutId, const int nSchemeId, const char * szSchemeName, const char *szData, const int nLen) = 0;

	
	/** 删除预案	
		@param const int nLayout								布局id
		@param const int nSchemeId                              预案id
		@param const char * szSchemeName                        预案名称
		@return													
	*/
	virtual int DelScheme(const int nLayoutId, const int nSchemeId, const char * szSchemeName) = 0;
//第一期实现结束

	/** 预案另命名	
		@param const int nLayout								布局
		@param const int nSchemeId                              预案id
		@param const char* szName								预案名称
		@param const char* szNewName							新预案名称
		@return													
	*/
	virtual int RenameScheme(const char* szDevId, const int nLayout, const char* szName, const char* szNewName) = 0;

	/** 添加布局
		@param const char* szDevId								设备ID		
		@param const TvWallLayout_t* pLayout					布局信息	
		@return													
	*/
	virtual int AddLayout(const char* szDevId, const TvWallLayout_t* pLayout) = 0;

	/** 修改布局
		@param const char* szDevId								设备ID		
		@param const TvWallLayout_t* pLayout					布局信息	
		@return													
	*/
	virtual int ModLayout(const char* szDevId, const TvWallLayout_t* pLayout) = 0;

	/** 删除布局
		@param const char* szDevId								设备ID		
		@param const char* szName								布局名称	
		@return													
	*/
	virtual int DelLayout(const char* szDevId, const char* szName) = 0;

	/** 获取布局状态
		@param const char* szDevId								设备ID									
		@return													
	*/
	virtual int GetLayoutStatus(const char* szDevId) = 0;

	/** 设置布局状态
		@param const char* szDevId								设备ID
		@param const TvWallLayoutStatus_t* pStatus				状态信息
		@param int nCount										个数
		@return													
	*/
	virtual int SetLayoutStatus(const char* szDevId, const TvWallLayoutStatus_t* pStatus, int nCount) = 0;

	/** 清屏
		@param const char* szDevId								设备ID		
		@param int nLayout										布局
		@param const char* szCompositeID						融合屏ID		
		@return													
	*/
	virtual int ClearScene(const char* szDevId, int nLayout, const char* szCompositeID) = 0;


	
	/** 清窗口轮巡
		@param const char* szDevId								设备ID		
		@param const char* szCompositeID						融合屏ID
		@param int nWnd											窗口号								
		@return													
	*/
	virtual int ClearWindowTour(const char* szDevId, const char* szCompositeID, int nWnd) = 0;
	
	/** 获取窗口轮巡
		@param const char* szDevId								设备ID		
		@param const char* szCompositeID						融合屏ID
		@param int nWnd											窗口号								
		@return													
	*/
	virtual int GetWindowTour(const char* szDevId, const char* szCompositeID, int nWnd) = 0;

	/** 设置窗口轮巡
		@param const char* szDevId								设备ID		
		@param const char* szCompositeID						融合屏ID
		@param int nWnd											窗口号		
		@param const TvWallWindowTour_t* pTour                  窗口轮巡信息
		@return													
	*/
	virtual int SetWindowTour(const char* szDevId, const char* szCompositeID, int nWnd, const TvWallWindowTour_t* pTour) = 0;
	
	/** 启用窗口轮巡
		@param const char* szDevId								设备ID		
		@param const char* szCompositeID						融合屏ID
		@param int nWnd											窗口号		
		@bool bEnable											是否启用
		@return													
	*/
	virtual int EnableWindowTour(const char* szDevId, const char* szCompositeID, int nWnd, bool bEnable) = 0;
	
	/** 获取窗口轮巡状态
		@param const char* szDevId								设备ID		
		@param const char* szCompositeID						融合屏ID
		@param int nWnd											窗口号		
		@return													
	*/
	virtual int GetWindowTourStatus(const char* szDevId, const char* szCompositeID, int nWnd) = 0;

	/** 关联窗口轮巡
		@param const char* szDevId								设备ID		
		@param const char* szCompositeID						融合屏ID	
		@return													
	*/
	virtual int AttachWindowTour(const char* szDevId, const char* szCompositeID) = 0;

	/** 取消关联窗口轮巡
		@param int64_t nHandle									注册句柄
		@return													
	*/
	virtual int DetachWindowTour(int64_t nHandle) = 0;

	
	/** 获取电视墙预案时间表
		@param const char* szDevId								设备ID		
		@param int nLayout										布局
		@return													
	*/
	virtual int GetSchemeSchedule(const char* szDevId, int nLayout) = 0;
	
	/** 设置电视墙预案时间表
		@param const char* szDevId								设备ID		
		@param int nLayout										布局
		@param const TvWallSchemeSchedule_t* pSchedule			电视墙预案时间表
		@param int nCount										时间表个数
		@return													
	*/
	virtual int SetSchemeSchedule(const char* szDevId, int nLayout, const TvWallSchemeSchedule_t* pSchedule, int nCount) = 0;
	
	/** 获取预案轮巡
		@param const char* szDevId								设备ID		
		@param int nLayout										布局
		@return													
	*/
	virtual int GetSchemeTour(const char* szDevId, int nLayout) = 0;
	
	/** 设置预案轮巡
		@param const char* szDevId								设备ID		
		@param int nLayout										布局
		@param const TvWallSchemeTour_t* pTour					预案轮巡
		@return													
	*/
	virtual int SetSchemeTour(const char* szDevId, int nLayout, const TvWallSchemeTour_t* pTour) = 0;

	/** 启用预案轮巡
		@param const char* szDevId								设备ID		
		@param int nLayout										布局
		@param bool bEnable										是否启用
		@return													
	*/
	virtual int EnableSchemeTour(const char* szDevId, int nLayout, bool bEnable) = 0;

	/** 获取预案轮巡状态
		@param const char* szDevId								设备ID		
		@param int nLayout										布局
		@return													
	*/
	virtual int GetSchemeTourStatus(const char* szDevId, int nLayout) = 0;

	/** 关联预案轮巡
		@param const char* szDevId								设备ID		
		@param int nLayout										布局
		@return													
	*/
	virtual int AttachSchemeTour(const char* szDevId, int nLayout) = 0;

	/** 取消关联预案轮巡
		@param int64_t nHandle									注册句柄
		@return													
	*/
	virtual int DetachSchemeTour(int64_t nHandle) = 0;

	/** 获取屏幕电源时间表
		@param const char* szDevId								设备ID		
		@param int nLayout										布局
		@param const char* szCompositeID						融合屏ID
		@return													
	*/
	virtual int GetPowerSchedule(const char* szDevId, int nLayout, const char* szCompositeID) = 0;
	
	/** 设置屏幕电源时间表
		@param const char* szDevId								设备ID		
		@param int nLayout										布局
		@param const TvWallPowerSchedule_t* pSchedule			屏幕电源时间表
		@return													
	*/
	virtual int SetPowerSchedule(const char* szDevId, int nLayout, const TvWallPowerSchedule_t* pSchedule) = 0;


	
	/** 获取背景
		@param const char* szDevId								设备ID		
		@param const char* szCompositeID						融合屏ID
		@return													
	*/
	virtual int GetBackground(const char* szDevId, const char* szCompositeID) = 0;
	
	/** 设置屏幕底图
		@param const char* szDevId								设备ID		
		@param const char* szCompositeID						融合屏ID
		@param const TvWallBackground_t* pBackground			屏幕底图
		@return													
	*/
	virtual int SetBackground(const char* szDevId, const char* szCompositeID, const TvWallBackground_t* pBackground) = 0;

//////////////////////////////////////////////////////////////////////////
//统一接口结束

protected:
	virtual ~IDPSDKTvWall(void){}
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif
