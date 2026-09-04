/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：卡口接口文件
 *
 * 当前版本：1.0
 * 原作者　：12928
 * 完成日期：2012年10月15日
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_BAY_INTERFACE_H
#define INCLUDED_DPSDK_BAY_INTERFACE_H

#include "DPSDK.h"
#include "DPSDKAlarm.h"
#include <jsondsl/json.h>

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

#define DPSDK_BAY_IP_LEN				64					// 	
#define DPSDK_CAR_NUM_LENGTH			32					// 车牌号
#define DPSDK_CAPTURE_DATE_LENGTH		128					// 抓拍时间
#define DPSDK_CAPTURE_ORG_LENGTH		128					// 通缉机构
#define DPSDK_WANTED_CAR_NUM_LENGTH		128					// 布控车牌号
#define DPSDK_OPT_ORG_LENGTH			256					// 布控机构
#define DPSDK_OPTE_USER_LENGTH			128					// 布控人员
#define DPSDK_OPT_NOTE_LENGTH			128					// 备注信息
#define DPSDK_IMG_PATH_LENGTH			256					// 图片路径
#define DPSDK_BAY_IMG_NUM				6					// 图片数目
#define DPSDK_BAY_SURVERY_LENGTH		128					// 布控信息
#define DPSDK_ORDERLYPHONE_LENGTH		32					// 布控联系人单位电话
#define DPSDK_LINKMAN_LENGTH			16					// 布控联系人
#define DPSDK_LINKMAN_PHONE_LENGTH		32					// 布控联系人电话
#define DPSDK_BAY_URL_LEN				1024				// 客户端http请求的URL 的长度
#define DPSDK_BAY_CARINFO_LEN			128
#define DPSDK_BAY_NAME_LEN              256                 // 名称长度
#define DPSDK_PARK_LANEID_LEN			32					// 车位号长度
#define DPSDK_MAPID_LEN					32					// 图层mapId
#define DPSDK_BAY_AREA_ID_LEN           50                  // 区间长度
#define DPSDK_BAY_PLATE_LEN             4                   // 坐标点长度
#define DPSDK_BAY_ADR_LEN               50                  // 地点长度
#define DPSDK_BAY_MSG_LEN				4*1024				// 报警数据长度
#define DH_MAX_LANE_NUM                 8 

//////////////////////////////////////////////////////////////////////////

// 
typedef enum
{
	BAY_PICINFO_RECIVE,										// 收到图片信息
	BAY_PICDATA_RECIVE,										// 图片数据接收
	BAY_PICDATA_OVER,										// 一组图片数据结束
}dpsdk_picdata_notify_e;

enum MfAlarmType 
{ 
	MFALARM_WINGDING = 200,									// 线圈/车检器故障报警 
	MFALARM_REMOTE,											// 远程主机报警 
	MFALARM_FLASHLIGHT,										// 闪光灯报警 
	MFALARM_REDGREEN,										// 红绿灯故障 
	MFALARM_TRAFFIC_CROWD,									// 交通拥堵 
	MFALARM_TRAFFIC_HALT,									// 交通中断      

	MFALARM_DBERROR = 220,									// 数据库错误 
	MFALARM_DISKFULL,										// 磁盘满 
};

enum FaceDataOptType
{
	FACEDATA_OPT_UNDEFINE =0,			//
	FACEDATA_OPT_REGLIB_QUERY,			//人脸库信息查询
	FACEDATA_OPT_REGLIB_ADD,					//添加人脸库
	FACEDATA_OPT_REGLIB_DEL,					//删除人脸库
	FACEDATA_OPT_REGLIB_MODIFY,					//修改人脸库信息

	FACEDATA_OPT_REGFACE_ADD,					//添加注册人员
	FACEDATA_OPT_REGFACE_DEL,					//删除注册人员
	FACEDATA_OPT_REGFACE_MODIFY,					//修改注册人员信息

	FACEDATA_OPT_REGDATA_QUERY_START, //注册人员数据查询，会话开启
	FACEDATA_OPT_REGDATA_QUERY_GET, //注册人员数据获取，查询会话已开启
	FACEDATA_OPT_REGDATA_QUERY_STOP, //注册人员查询会话关闭

	FACEDATA_OPT_CAPTURE_QUERY_START, //抓拍数据查询，会话开启
	FACEDATA_OPT_CAPTURE_QUERY_GET, //抓拍数据获取，查询会话已开启
	FACEDATA_OPT_CAPTURE_QUERY_STOP, //抓拍查询会话关闭

	FACEDATA_OPT_FACEALARM_QUERY_START, //识别报警数据查询，会话开启
	FACEDATA_OPT_FACEALARM_QUERY_GET, //识别报警数据获取，查询会话已开启
	FACEDATA_OPT_FACEALARM_QUERY_STOP, //识别报警查询会话关闭

	FACEDATA_OPT_REGDATA_CHECK_START, //注册人员数据查重，会话开启
	FACEDATA_OPT_REGDATA_CHECK_GET, //注册人员查重数据获取，查重会话已开启
	FACEDATA_OPT_REGDATA_CHECK_STOP, //注册人员查重会话关闭

	FACEDATA_OPT_GET_CHNLSETTING,			// 获取通道配置
	FACEDATA_OPT_SET_CHNLSETTING,			// 设置通道配置
};

// 人脸识别报警
typedef struct DPSDK_API tagFaceRecognition_Alarm
{
	char			_cameraId[DPSDK_CHL_ID_LEN];			// 通道ID
	char			_ptsIp[DPSDK_BAY_IP_LEN];				// pts内网
	char			_ptsIpy[DPSDK_BAY_IP_LEN];				// pts外网
	int				_picPort;								// pic内网port
	int				_picPorty;								// pic外网port

	char*		_faceAlarmData;						//人脸识别报警数据(Json)
	long			_faceAlarmDataLength;			//报警数据长度

	tagFaceRecognition_Alarm()
	{
		memset(_cameraId, 0, sizeof(_cameraId));
		memset(_ptsIp, 0, sizeof(_ptsIp));
		memset(_ptsIpy,0,sizeof(_ptsIpy));
		_picPort = 0;
		_picPorty = 0;

		_faceAlarmDataLength = 0;
		_faceAlarmData = NULL;
	}

	~tagFaceRecognition_Alarm()
	{
		if(_faceAlarmData)
		{
			delete [] _faceAlarmData; 
			_faceAlarmData = NULL;
		}
	}
}FaceAlarm_Struct;

// 布控报警
typedef struct DPSDK_API tagWanted_CarAlarm
{	
	char				_cameraId[DPSDK_CHL_ID_LEN];					// 通道ID
	char				_ptsIp[DPSDK_BAY_IP_LEN];						// pts内网
	char				_ptsIpy[DPSDK_BAY_IP_LEN];						// pts外网
	int					_picPort;										// pic内网port
	int					_picPorty;										// pic外网port
	
	//以下字段为web配置,PCS下发给PTS
	char				_surveryOrg[DPSDK_OPT_ORG_LENGTH];				// 布控机构
	char				_arrestOrg[DPSDK_CAPTURE_ORG_LENGTH];			// 通缉机构
	char				_username[DPSDK_OPTE_USER_LENGTH];				// 当前布控的操作员
	int					_nalart;										// 报警类型
	int					_nsurlevel;										// 布控等级,110802，2.2新增
	int					_nState;										// 布控状态
	int					_nSurType;										// 布控类型,2.2新增
	unsigned long long	_begindate;										// 
	unsigned long long	_enddate;										// 
	int					_nCartype;										// 车辆类型
	char				_cartypename[DPSDK_BAY_CARINFO_LEN];			// 车辆类型名称
	char				_carnum[DPSDK_WANTED_CAR_NUM_LENGTH];			// 布控车牌
	int					_nlicentype;									// 车牌颜色类型
	char				_carlicenname[DPSDK_BAY_CARINFO_LEN];			// 车牌颜色名称
	int					_nCarnotype;									// 车牌类型
	char				_carnotypename[DPSDK_BAY_CARINFO_LEN];			// 车牌类型名称
	int					_carcolor;										// 车身颜色
	char				_carpower[DPSDK_BAY_CARINFO_LEN];				// 发动机号
	int					_carlen;										// 车长：厘米
	char				_frameno[DPSDK_BAY_CARINFO_LEN];				// 车架号
	int					_nbckcolor;										// 车牌颜色
	char				_Identify[DPSDK_BAY_SURVERY_LENGTH];			// 车主身份证
	char				_ownname[DPSDK_BAY_SURVERY_LENGTH];				// 车主姓名
	char				_ownaddr[DPSDK_BAY_SURVERY_LENGTH];				// 车主地址
	char				_ownphone[DPSDK_BAY_SURVERY_LENGTH];			// 车主电话
	char				_descirbe[DPSDK_OPT_NOTE_LENGTH];				// 描述
	char				_orderlyphone[DPSDK_ORDERLYPHONE_LENGTH];		// 布控单位值班电话，2.2新增
	char				_linkman[DPSDK_LINKMAN_LENGTH];					// 布控联系人，2.2新增
	char				_linkmanphone[DPSDK_LINKMAN_PHONE_LENGTH];		// 布控联系人电话，2.2新增
	char				_oriUrl[DPSDK_BAY_URL_LEN];						// 车辆原始图片， 2.2

	//以下字段为PTS生成
	char				_picUrl[DPSDK_BAY_IMG_NUM][DPSDK_BAY_URL_LEN];	// 图片URL
	uint32_t			_ulPicGroupStoreID;								// 图片组存储ID
	int					_bNeedStore;									// 是否需存盘 0：不需存盘 1：需存盘
	int					_bStored;										// 是否已存盘 0：未存盘 1：已存盘
	int					_nCarLogo;										// 车标类型
	int					_alarmLevel;									// 布控报警级别
	uint32_t			_alarmTime;										// 布控报警时间,精度为秒，值为time(NULL)值
	int                 _LightColor;                                    // 红绿灯状态，0 未知,1 绿灯,2 红灯,3 黄灯

	int				_channel;										// 通道
	char			_deviceId[DPSDK_CHL_ID_LEN];					// 设备ID（DVR+通道）
	
	tagWanted_CarAlarm(void)
	{
		memset(_cameraId, 0, sizeof(_cameraId));
		memset(_ptsIp, 0, sizeof(_ptsIp));
		memset(_ptsIpy,0,sizeof(_ptsIpy));
		_picPort = 0;
		_picPorty = 0;
		memset(_surveryOrg, 0, sizeof(_surveryOrg));
		memset(_arrestOrg, 0, sizeof(_arrestOrg));
		memset(_username, 0, sizeof(_username));
		_nalart = 0;
		_nsurlevel = 0;
		_nState = 0;
		_nCartype = 0;
		memset(_cartypename, 0, sizeof(_cartypename));
		memset(_carnum, 0, sizeof(_carnum));
		_nlicentype = 0;
		memset(_carlicenname, 0, sizeof(_carlicenname));
		_nCarnotype = 0;
		memset(_carnotypename, 0, sizeof(_carnotypename));
		_carcolor = 0;
		memset(_carpower, 0, sizeof(_carpower));
		_carlen = 0;
		memset(_frameno, 0, sizeof(_frameno));
		_nbckcolor = 0;
		_nSurType = 0;
		_begindate = 0;
		_enddate = 0;
		memset(_Identify, 0, sizeof(_Identify));
		memset(_ownname, 0, sizeof(_ownname));
		memset(_ownaddr, 0, sizeof(_ownaddr));
		memset(_ownphone, 0, sizeof(_ownphone));
		memset(_descirbe, 0, sizeof(_descirbe));
		memset(_orderlyphone, 0, sizeof(_orderlyphone));
		memset(_linkman, 0, sizeof(_linkman));
		memset(_linkmanphone, 0, sizeof(_linkmanphone));
		memset(_oriUrl, 0, sizeof(_oriUrl));
		memset(_picUrl, 0, sizeof(_picUrl));
		_ulPicGroupStoreID = 0;
		_bNeedStore = 0;
		_bStored = 0;
		_alarmLevel = 0;
		_nCarLogo=0;
		_alarmTime = 0;
		_LightColor = 0;

		_channel = 0;
		memset(_deviceId, 0, sizeof(_deviceId));
	}
}WantedCarAlarm_Struct;

//违章报警
typedef struct DPSDK_API tagAlarm_4JT_PictureLink
{
	char			_cameraId[DPSDK_CHL_ID_LEN];					// 通道ID
	int				_alarmTime;
	char			_ptsIp[DPSDK_BAY_IP_LEN];						// pts内网
	char			_ptsIpy[DPSDK_BAY_IP_LEN];						// pts外网
	int				_picPort;										// pic内网port
	int				_picPorty;										// pic外网port
	dpsdk_alarm_type_e	_type;										// 违章类型
	char			_carnum[DPSDK_CAR_NUM_LENGTH];					// 车牌
	int				_nlicentype;									// 车牌颜色类型
	int				_carcolor;										// 车身颜色
	int				_nCarLogo;										// 车标类型
	int				_nWay;											// 车道号
	char			_picUrl[DPSDK_BAY_IMG_NUM][DPSDK_BAY_URL_LEN];	// 图片URL
	uint32_t		_ulPicGroupStoreID;								// 图片组存储ID
	int				_bNeedStore;									// 是否需存盘 0：不需存盘 1：需存盘
	int				_bStored;										// 是否已存盘 0：未存盘 1：已存盘int	
	int				_alarmLevel;									// 报警级别

	//新增
	int				_channel;										// 通道
	char			_deviceId[DPSDK_CHL_ID_LEN];					// 设备ID（DVR+通道）
	char            _szDeviceName[DPSDK_BAY_NAME_LEN];				// 设备名称 
	char            _szDeviceChnName[DPSDK_BAY_NAME_LEN];			// 通道名称
	int				_nCarType;										// 车类型
	int				_nCarSpeed;										// 车速
	int				_nCarLen;										// 车身长度单位
	int				_nCardirect;									// 行车方向
	int				_nMaxSpeed;										// 限制速度
	int				_nMinSpeed;										// 最低限制速度
	int				_nRtPlate[DPSDK_BAY_PLATE_LEN];					// 车牌坐标
	char			_message[DPSDK_BAY_MSG_LEN];					// 报警信息
	char			_szViolationCode[32];							// 违章代码

	//超重信息
	int				_nAxleNum;										// 轴数
	int				_nTotalWeight;									// 总重
	int				_nOverWeight;									// 超重
	int				_nLimitWeight;									// 限重
	
	tagAlarm_4JT_PictureLink(void)
	{
		memset(_cameraId, 0, sizeof(_cameraId));
		_alarmTime = 0;
		_type=ALARM_TRAFFIC_RUNREDLIGHT;
		memset(_ptsIp, 0, sizeof(_ptsIp));
		memset(_ptsIpy,0,sizeof(_ptsIpy));
		_picPort = 0;
		_picPorty = 0;
		memset(_carnum,0,sizeof(_carnum));
		_nlicentype = 0;
		_carcolor = 0;
		_nCarLogo = 0;
		_nWay = 0;
		memset(_picUrl, 0, sizeof(_picUrl));
		_ulPicGroupStoreID = 0;
		_bNeedStore = 0;
		_bStored = 0;
		_alarmLevel = 0;

		_channel = 0;
		memset(_deviceId, 0, sizeof(_deviceId));
		memset(_szDeviceName, 0, sizeof(_szDeviceName));
		memset(_szDeviceChnName, 0, sizeof(_szDeviceChnName));
		memset(_nRtPlate, 0, sizeof(_nRtPlate));
		memset(_message, 0, sizeof(_message));
		memset(_szViolationCode,0,sizeof(_szViolationCode));

		_nCarType = 0;
		_nCarSpeed = 0;
		_nCarLen = 0;
		_nCardirect = 0;
		_nMaxSpeed = 0;
		_nMinSpeed = 0;

		_nAxleNum = 0;
		_nTotalWeight = 0;
		_nOverWeight = 0;
		_nLimitWeight = 0;
	}
}Alarm_4JT_PictureLink_Struct;


//区间测速信息
typedef struct DPSDK_API tagReportSpanTestInfo
{
	char			_areaId[DPSDK_BAY_AREA_ID_LEN];					// 区间ID
	char			_areaName[DPSDK_BAY_NAME_LEN];					// 区间名称
	char            _startDevId[DPSDK_CHL_ID_LEN];					// 起始设备ID
	int   			_startChnNum;									// 起始点通道号
	char			_startChnId[DPSDK_CHL_ID_LEN];					// 起始点通道ID 
	char			_startDevName[DPSDK_BAY_NAME_LEN];				// 起始点设备名,UTF8编码
	char			_startDevChnName[DPSDK_BAY_NAME_LEN];			// 起始点通道名,UTF8编码
	unsigned long long _startCapTime;								// 起始点通过时间
	int 			_startCarSpeed;									// 起始点通过速度
	char			_startPosId[DPSDK_BAY_ADR_LEN];					// 起始点卡点ID
	char			_startPosName[DPSDK_BAY_NAME_LEN];				// 起始点卡点名
	char			_endDevId[DPSDK_CHL_ID_LEN];					// 终止点设备ID
	int 			_endChnNum;										// 终止点通道号
	char			_endChnId[DPSDK_CHL_ID_LEN];					// 终止点通道ID 
	char			_endDevName[DPSDK_BAY_NAME_LEN];				// 终止点设备名,UTF8编码
	char			_endDevChnName[DPSDK_BAY_NAME_LEN];				// 终止点通道名,UTF8编码
	unsigned long long	_endCapTime;								// 终止点通过时间
	int 			_endCarSpeed;									// 终止点通过速度
	char			_endPosId[DPSDK_BAY_ADR_LEN];					// 终止点卡点ID
	char			_endPosName[DPSDK_BAY_NAME_LEN];				// 终止点卡点名
	int 			_areaRange;										// 区间距离
	int 			_minSpeed;										// 路段限速下限 
	int 			_maxSpeed;										// 路段限速上限 
	char			_carNum[DPSDK_CAR_NUM_LENGTH];					// 车牌号码，UTF8编码
	int 			_carNumType;									// 车牌类型
	int 			_carNumColor;									// 车牌颜色
	int 			_carColor;										// 车身颜色
	int 			_carType;										// 车类型
	int 			_carLogo;										// 车标类型
	int 			_carAvgSpeed;									// 车辆平均速度
	int 			_isIllegalSpeed;								// 是否超速或低速
	int 			_picNum;										// 图片张数，最大支持6张
	char			_picURL[DPSDK_BAY_IMG_NUM][DPSDK_BAY_URL_LEN];  // 图片文件命名，最大支持6张。
	int 			_rtPlate[DPSDK_BAY_PLATE_LEN];					// 车牌坐标,left,top, right, bottom,不能超过4位
	char			_carPlatePicURL[DPSDK_BAY_URL_LEN];				// 车牌小图片URL


	tagReportSpanTestInfo()
	{
		memset(_areaId,0,sizeof(_areaId));
		memset(_areaName,0,sizeof(_areaName));
		memset(_startDevId,0,sizeof(_startDevId));
		_startChnNum = 0;

		memset(_startChnId,0,sizeof(_startChnId));
		memset(_startDevName,0,sizeof(_startDevName));
		memset(_startDevChnName,0,sizeof(_startDevChnName));
		_startCapTime = 0;
		_startCarSpeed = 0;

		memset(_startPosId,0,sizeof(_startPosId));
		memset(_startPosName,0,sizeof(_startPosName));
		memset(_startDevChnName,0,sizeof(_startDevChnName));
		_endChnNum = 0;

		memset(_endChnId,0,sizeof(_endChnId));
		memset(_endDevName,0,sizeof(_endDevName));
		memset(_endDevChnName,0,sizeof(_endDevChnName));
		_endCapTime = 0;
		_endCarSpeed = 0;

		memset(_endPosId,0,sizeof(_endPosId));
		memset(_endPosName,0,sizeof(_endPosName));
		_areaRange = 0;
		_minSpeed = 0;
		_maxSpeed = 0;

		memset(_carNum,0,sizeof(_carNum));
		_carNumType = 0;
		_carNumColor = 0;
		_carColor = 0;
		_carType = 0;
		_carLogo = 0;
		_carAvgSpeed = 0;
		_isIllegalSpeed = 0;
		_picNum = 0;

		memset(_rtPlate,0,sizeof(_rtPlate));
		memset(_rtPlate,0,sizeof(_rtPlate));
		memset(_carPlatePicURL,0,sizeof(_carPlatePicURL));

	}
}Report_Span_Test_Sturct;

//第三方布控
typedef struct DPSDK_API tagPoliceSurvey_Struct
{
	char		_carnum[DPSDK_CAR_NUM_LENGTH];
	int			_carNumcolor;
	int64_t		_beginTime;
	int64_t		_endTime;

	tagPoliceSurvey_Struct()
	{
		memset(_carnum, 0, sizeof(_carnum));
		_carNumcolor = 0;
		_beginTime = 0;
		_endTime = 0;
	}

}PoliceSurvey_Struct;

// 交通流量上报数据结构
typedef struct DPSDK_API tagReportTrafficFlow
{
	char            szChannelId[64];	                 // 通道编号
	char            szDirect[4];		                 // 方向编号，见字典表
	uint16_t        nInterval;                           // 上报间隔，单位秒
	uint16_t        nTrafficFlow;		                 // 交通流量（包括从设备接收到的所有数据，违章也包括在内）	
	uint64_t        nTime;                               // 上报时间，1970的秒数

	tagReportTrafficFlow(void)
	{
		memset(szChannelId, 0, 64);
		memset(szDirect, 0, 4);
		nInterval = 0;
		nTrafficFlow = 0;
		nTime = 0;
	}
}Report_Traffic_Flow_t;
//每个车道的交通流量状态
typedef struct DPSDK_API tagDevTrafficFlowLaneState{
	uint64_t        nDateTime;                           // 数据上报时间 UTC时间
	uint32_t        nDetectorID;                         // 检测车道编号
	uint32_t        nVolume;                             // 交通量（辆/单位时间）小车当量
	uint32_t        nFlowRate;                           // 流率（辆/小时）小车当量
	float           nAverageSpeed;                       // 平均速度（公里/小时）
	float           fTimeOccupancy;                      // 平均时间占有率（%）
	float           nTimeHeadway;                        // 车头时距（秒）
	float           nLength;                             // 平均车长（米）
	float           nBackOfQueue;                        // 排队长度（米）
	float           nTravelTime;                         // 旅行时间（秒）
	float           nDelay;                              // 延误（秒），##
	uint32_t        nMotoVehicles;                       // 微型车交通量（辆/单位时间）
	uint32_t        nSmallVehicles;                      // 小车交通量（辆/单位时间）
	uint32_t        nMediumVehicles;                     // 中车交通量（辆/单位时间）
	uint32_t        nLargeVehicles;                      // 大车交通量（辆/单位时间）
	uint32_t        nLongVehicles;                       // 特大车交通量（辆/单位时间）
	uint32_t        nState;                              // 状态值：1-流量过大,2-流量过大恢复,3-正常,4-流量过小,5-流量过小恢复
	uint32_t        nFlow;                               // 流量值，单位：辆
	uint32_t        nPeriod;                             // 流量值对应的统计时间
	uint32_t        nDrivingDir;                         // 行驶方向，上行下行。上行，即车辆离设备部署点越来越近 /下行，即车辆离设备部署点越来越远
	int32_t         nDirection;                          // 车道方向
	int32_t         nPeriodBySeconds;                    // 以秒为单位的周期
}Dev_Traffic_Flow_Lane_State_t; 
// 交通设备流量上报数据结构
typedef struct DPSDK_API tagReportDevTrafficFlow
{
	char							szChannelId[DPSDK_CHL_ID_LEN];		// 通道编号
	char							szDirect[4];						// 方向编号，见字典表
	int								nTrafficLaneNum;					// 交通流量数量
	Dev_Traffic_Flow_Lane_State_t	StuTrafficLane[DH_MAX_LANE_NUM];	//交通流量状态，最大支持8车道
	
	tagReportDevTrafficFlow(void)
	{
		memset(StuTrafficLane, 0, DH_MAX_LANE_NUM*sizeof(Dev_Traffic_Flow_Lane_State_t));
		memset(szChannelId, 0, 64);
		memset(szDirect, 0, 4);
		nTrafficLaneNum = 0;
	}
}Report_Dev_Traffic_Flow_t;

typedef struct DPSDK_API tagParkStatus_Struct
{
	char				_chnlNo[DPSDK_CHL_ID_LEN];					// 通道号
	char				_laneID[DPSDK_PARK_LANEID_LEN];				// 车位区号+自定义车位号
	char				_carnum[DPSDK_CAR_NUM_LENGTH];				// 车牌号码
	char				_mapId[DPSDK_MAPID_LEN];					// 地图图层ID
	char				_carUrl[DPSDK_BAY_URL_LEN];					// 图片url路径
	int					_nlicentype;								// 车牌颜色类型
	int					_nCarnotype;								// 车牌类型
	int					_carcolor;									// 车身颜色
	int					_nCartype;									// 车辆类型
	int					_nParkingStatus;							// 停车状态 1对应有车 2对应无车
	int					_nCarLogo;									// 车标
	int					_nParkingAlarmStatus;						// 停车报警状态 1合法 2非法
	int					_nParkTime;									// 停车时间
	tagParkStatus_Struct()
	{
		memset(_chnlNo,0,DPSDK_CHL_ID_LEN);
		memset(_laneID,0,DPSDK_PARK_LANEID_LEN);
		memset(_carnum,0,DPSDK_CAR_NUM_LENGTH);
		memset(_mapId,0,DPSDK_MAPID_LEN);
		memset(_carUrl,0,DPSDK_BAY_URL_LEN);
		_nlicentype			= 0;		
		_nCarnotype			= 0;		
		_carcolor			= 0;			
		_nCartype			= 0;			
		_nParkingStatus		= 0;	
		_nCarLogo			= 0;			
		_nParkingAlarmStatus= 0;
		_nParkTime			= 0;
	}
}ParkStatus_Struct;

// 线圈/车检器报警
typedef struct DPSDK_API tagWinding_Info
{
	char				szCameraId[DPSDK_CHL_ID_LEN];	// 通道ID
	int                 nDriveWayID;					// 车道号
	int                 nWindingID;						// 线圈ID
	char				szAlarmTime[DPSDK_TIME_LEN];	// 报警时间 格式2014-02-15 11:30:00
	int                 nState;							// 设备状态，1故障产生，2故障消失/正常
}Winding_Info;

/** 图片数据回调函数定义
    @param int session												对应请求时返回的session
    @param const char* nodeId										数据对应的通道/设备ID
    @param char* pData												图片流数据
    @param int dataLen												数据长度 
	@param void* pUserParam											用户参数,见AddCallbackInfo
	@param dpsdk_picdata_notify_e notify_e							图片数据类型
*/
typedef int (DPSDK_CALLTYPE *fPicDataCallback)(int session, const char* nodeId, char* pData, int dataLen, void* pUserParam, dpsdk_picdata_notify_e notify_e);
//////////////////////////////////////////////////////////////////////////

// 开始图片监控消息
class DPSDK_API StartPicMonitorMsg : public DPSDKCBMessage
{
public:
	StartPicMonitorMsg(void);
	virtual ~StartPicMonitorMsg(void){}

public:
	uint32_t			sessionId;									// 会话Id
	char				cameraId[DPSDK_CHL_ID_LEN];					// 通道Id

	fPicDataCallback	cbFun;										// 图片数据回调函数指针
	void*				pCbParam;									// 用户参数
	dpsdk_bay_monitor_e	eBayType;				//监控类别
};

// 停止图片监控消息
class DPSDK_API StopPicMonitorMsg : public DPSDKCBMessage
{
public:
	StopPicMonitorMsg(void);
	virtual ~StopPicMonitorMsg(void){}

public:
	uint32_t	sessionId;									// 会话Id
};

// 
class DPSDK_API PcsCloseMsg : public DPSDKCBMessage
{
public:
	PcsCloseMsg(void){ m_cmd = DPSDK_CMD_PCS_CLOSE; m_msgType = DPSDK_MSG_NOTIFY;} 
	virtual ~PcsCloseMsg(void){}
};

// 
class DPSDK_API PicRtpCloseMsg : public DPSDKCBMessage
{
public:
	PicRtpCloseMsg(void);
	virtual ~PicRtpCloseMsg(void){};

public:
	uint32_t	nSessionId;									// 
};

//人脸数据操作
class DPSDK_API FaceDataOptMsg : public DPSDKCBMessage
{
public:
	FaceDataOptMsg();
	virtual ~FaceDataOptMsg();

public:
	// request
	long requestFlag;		//请求标记，一般为请求源的指针
	FaceDataOptType		optType;				//操作类型，用于返回时的json解析方式判断，而非通过解析头判断具体解析方式
	dsl::Json::Value			sendJson;		// 发出去的数据,一般是客户端填的值

	dsl::Json::Value			recJson;		// 收到的原始数据,一般是服务端填的值
};

//通用Json进行消息上报
class DPSDK_API BayGeneralJsonNotifyMsg : public DPSDKCBMessage
{
public:
	BayGeneralJsonNotifyMsg();
	virtual ~BayGeneralJsonNotifyMsg();

public:
	dsl::Json::Value			recJson;		// 上层再解析
};

//人脸识别报警
class DPSDK_API FaceAlarmMsg : public DPSDKCBMessage
{
public:
	FaceAlarmMsg();
	virtual ~FaceAlarmMsg();

public:
	FaceAlarm_Struct*	pFaceAlarm;
};

// 违章报警
class DPSDK_API PicDpAlarmMsg : public DPSDKCBMessage
{
public:
	PicDpAlarmMsg(void);
	virtual ~PicDpAlarmMsg(void);

public:
	Alarm_4JT_PictureLink_Struct*	pPicLink_Alarm;			// 
};

// 区间测速
class DPSDK_API ReportSpanTestMsg : public DPSDKCBMessage
{
public:
	ReportSpanTestMsg(void);
	virtual ~ReportSpanTestMsg(void);

public:
	Report_Span_Test_Sturct*	pSpan_Test;			 
};


// 布控报警
class DPSDK_API PicWantedAlarmMsg : public DPSDKCBMessage
{
public:
	PicWantedAlarmMsg(void);
	virtual ~PicWantedAlarmMsg(void);

public:
	WantedCarAlarm_Struct*	pPicWanted_Alarm;				// 
};

class DPSDK_API PoliceSurveyMsg : public DPSDKCBMessage
{
public:
	PoliceSurveyMsg(void);
	virtual ~PoliceSurveyMsg(void);

public:
	PoliceSurvey_Struct*	pPoliceSurvey;				// 
	int						nCount;
	int						operateType;				//0添加 1删出
};

class DPSDK_API ParkingStatusQueryMsg : public DPSDKCBMessage
{
public:
	ParkingStatusQueryMsg(void);
	virtual ~ParkingStatusQueryMsg(void);
public:
	char					deviceId[DPSDK_DEV_ID_LEN];		//设备ID
	tagParkStatus_Struct*	pParkStatus;
	int						nCount;
};

class DPSDK_API ParkingStatusNotifyMsg : public DPSDKCBMessage
{
public:
	ParkingStatusNotifyMsg(void);
	virtual ~ParkingStatusNotifyMsg(void);
public:
	tagParkStatus_Struct*	pParkStatus;
	char					deviceId[DPSDK_DEV_ID_LEN];		//设备ID
	int						nCount;
};


class DPSDK_API BayCarInfoNotifyMsg : public DPSDKCBMessage
{
public:
	BayCarInfoNotifyMsg(void);
	virtual ~BayCarInfoNotifyMsg(void);
public:
	char				_chnlNo[DPSDK_CHL_ID_LEN];					// 通道号
	char				_plateNum[DPSDK_CAR_NUM_LENGTH];			// 车牌号
	int					_carNoType;									// 车牌类型
	int					_licenType;									// 车牌颜色
	int					_carColor;									// 车身颜色
	int					_carType;									// 车辆类型
	int					_carDirect;									// 行车方向
	int					_carLogo;									// 车标
	int64_t				_capTime;									// 抓拍时间
	int					_alarmType;									// 报警类型 0内部车 1外部车
	char				_ownerName[DPSDK_PERSON_NAME_LEN];			// 车主名字
	char				_ownerTel[DPSDK_PHONE_LEN];					// 车主电话
	char				_cardId[DPSDK_CHL_ID_LEN];					// 卡号
	char				_carImgUrl[DPSDK_BAY_URL_LEN];				// 车辆图片URL
	char				_carImgUrl1[DPSDK_BAY_URL_LEN];
	char				_carImgUrl2[DPSDK_BAY_URL_LEN];
	char				_ptsIp[DPSDK_IP_LEN];						// pts服务内网IP
	char				_ptsIpY[DPSDK_IP_LEN];						// pts服务外网IP
	int					_picPort;									// picServer内网端口
	int					_picPortY;									// picServer外网端口
};

// 交通流量订阅
class DPSDK_API SubscribeTrafficFlowMsg : public DPSDKCBMessage
{
public:
	SubscribeTrafficFlowMsg(void);
	virtual ~SubscribeTrafficFlowMsg(void){}

public:
	uint32_t	nSubscribeFlag;			// 订阅标记。0:取消订阅，1：订阅
};

class DPSDK_API SubscribeAreaSpeedDetectMsg : public DPSDKCBMessage
{
public:
	SubscribeAreaSpeedDetectMsg(void);
	virtual ~SubscribeAreaSpeedDetectMsg(void){}

public:
	uint32_t	nSubscribeFlag;			// 订阅标记。0:取消订阅，1：订阅
};
// 交通流量上报
class DPSDK_API ReportTrafficFlowMsg : public DPSDKCBMessage
{
public:
	ReportTrafficFlowMsg(void);
	virtual ~ReportTrafficFlowMsg(void);

public:
	Report_Traffic_Flow_t *pTracfficFlow;
};

// 交通设备流量上报
class DPSDK_API ReportDevTrafficFlowMsg : public DPSDKCBMessage
{
public:
	ReportDevTrafficFlowMsg(void);
	virtual ~ReportDevTrafficFlowMsg(void);

public:
	Report_Dev_Traffic_Flow_t *pDevTracfficFlow;
};

//////////////////////////////////////////////////////////////////////////

// 违章信息数据结构，写入时对数据有严格规定，凡是整数型的备注中为明确注释的都不能超过3位
typedef struct DPSDK_API tagTrafficViolation
{
	char	        szRecordId[128];				     // 记录ID
	char	        szDeviceId[DPSDK_DEV_ID_LEN];        // 设备ID
	int		        nChannel;					         // 通道
	char            szChannelId[64];     		         // 通道编号
	dpsdk_alarm_type_e		nType;		                 // 违章报警类型
	char	        szDeviceName[256];			         // 设备名称,UTF8编码
	char	        szDeviceChnName[256];		         // 通道名称,UTF8编码	
	char	        szCarNum[32];				         // 车牌号码，UTF8编码
	int		        nCarNumType;				         // 车牌类型
	int		        nCarNumColor;				         // 车牌颜色
	int		        nCarColor;					         // 车身颜色
	int             nCarType;					         // 车类型
	int		        nCarLogo;					         // 车标类型
	int		        nWay;						         // 车道号
	int		        nCarSpeed;					         // 车速
	int		        nCarLen;					         // 车身长度，单位cm,不能超过4位
	int		        nCardirect;					         // 行车方向
	int		        nMaxSpeed;					         // 限制速度,用于超速判断
	int		        nMinSpeed;					         // 最低限制速度,用于超速判断
	char   	        szCapturedate[128];			         // 精确到秒,如 2013-09-25 12:04:08
	char	        szOptNote[255];				         // 备注信息
	int    	        nPicNum;                             // 图片张数，最大支持6张
	char            szPicName[6][256];                   // 图片文件命名，最大支持6张。如果为空，则由PTS生成。
	int 	        nRtPlate[4];				         // 车牌坐标,left,top, right, bottom,不能超过4位
	int             nDataSource;			             // 数据来源,不能超过2位

	tagTrafficViolation(void)
	{
		memset(szRecordId, 0, 128);
		memset(szDeviceId, 0, DPSDK_DEV_ID_LEN);
		nChannel = 0;
		memset(szChannelId, 0, 64);
		nType = ALARM_TYPE_Unknown;
		memset(szDeviceName, 0, 256);
		memset(szDeviceChnName, 0, 256);
		memset(szCarNum, 0, 32);
		nCarNumType = 0;
		nCarNumColor = 0;
		nCarColor = 0;
		nCarType = 0;
		nCarLogo = 0;
		nWay = 0;
		nCarSpeed = 0;
		nCarLen = 0;
		nCardirect = 0;
		nMaxSpeed = 0;
		nMinSpeed = 0;
		memset(szCapturedate, 0, 128);
		memset(szOptNote, 0, 255);
		nPicNum = 0;
		memset(szPicName, 0, 6*256);
		for (int i = 0; i < 4; i++)
		{
			nRtPlate[i] = 0;
		}
		nDataSource = 0;
	}
}Traffic_Violation_t;

// 违章信息写入
class DPSDK_API WriteTrafficViolationMsg : public DPSDKCBMessage
{
public:
	WriteTrafficViolationMsg(void);
	virtual ~WriteTrafficViolationMsg(void){}

public:
	// request
	Traffic_Violation_t stuTracfficViolation;

	// response
	char    szRecordId[128];			// 记录id
	char    szPicName[6][256];			// ftp全路径，UTF8编码
	int     nPicNum;
};

// 违章信息查询
class DPSDK_API QueryTrafficViolationMsg : public DPSDKCBMessage
{
public:
	QueryTrafficViolationMsg(void);
	virtual ~QueryTrafficViolationMsg(void);

public:
	// request
	char    szRecordId[128];			// 记录ID

	// response
	Traffic_Violation_t* pTrafficViolationResult;
};

class DPSDK_API QueryAllWindingMsg : public DPSDKCBMessage
{
public:
	QueryAllWindingMsg(void);
	virtual ~QueryAllWindingMsg(void);

public:
	Winding_Info*			pWindingInfo;
	int						nCount;
};

class DPSDK_API MfAlarmMsg : public DPSDKCBMessage
{
public:
	MfAlarmMsg(void);
	virtual ~MfAlarmMsg(void);

public:
	char					szCameraId[DPSDK_CHL_ID_LEN];		// 通道ID
	MfAlarmType				eType;								// 故障类型
	int						nState;								// 设备状态，1故障产生，2故障消失
	int						nDriveWayID;						// 车道号
	int						nParam;								// 线圈id(ALARM_WINGDING) or 流量值(ALARM_TRAFFIC_CROWD)
	char					szAlarmTime[DPSDK_TIME_LEN];		// 报警时间 格式2014-02-15 11:30:00
	int						nOmType;							// 0-设备通道 1-PTS/EAS等服务
};

class DPSDK_API PicAbnormalNotifyMsg : public DPSDKCBMessage
{
public:
	PicAbnormalNotifyMsg(void);
	virtual ~PicAbnormalNotifyMsg(void){};
public:
	char					szCameraId[DPSDK_CHL_ID_LEN];		// 通道ID
	int						nAlarmInteval;						// 上报间隔
	int						nCount;								// 异常次数
	char					szReportTime[DPSDK_TIME_LEN];		// 上报时间
	int						nStatus;							// 上报状态  nStat   0表示异常消失，1表示异常发生， 2表示设备离线（在线异常设备断线情况） 
};

struct  DPSDK_API BayStatus
{
	char					id[DPSDK_DEV_ID_LEN];				// ID
	int						status;								// 状态。1在线，2断线

	BayStatus()
	{
		memset(id, 0, sizeof(id));
		status = 2;
	}
};	
//获取卡口设备状态
class DPSDK_API GetBarStatusMsg : public DPSDKCBMessage
{
public:
	GetBarStatusMsg();
	virtual ~GetBarStatusMsg();

public:
	// request
	std::vector<std::string> vecDevId;

	// response
	std::vector<BayStatus> vecBayStatus;
};

//卡口相关
class DPSDK_API PcsLoginMsg : public DPSDKCBMessage
{
public:
	char			ip[DPSDK_IP_LEN];
	int				port;
	char			username[DPSDK_USER_NAME_LEN];
	char			password[DPSDK_PASSWORD_LEN_EX];
	int             logintype; //1-断线重连，其他-正常连接

	uint32_t		userId;

	PcsLoginMsg();
	~PcsLoginMsg(){}
};
//////////////////////////////////////////////////////////////////////////

class DPSDK_API IDPSDKBay : public IDPSDKFuncBase
{
public:
	/** 图片监控
	    @param const char * cameraId						通道ID
		@param fPicDataCallback funCB						图片数据回调函数指针
		@param void* pCBParam								用户参数
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int StartPicMonitor(const char* cameraId, fPicDataCallback funCB, void* pCBParam, dpsdk_bay_monitor_e eBayType = BAY_MONITOR_CAR) = 0;

	/** 停止图片监控
	    @param uint32_t sessionId							会话Id
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int StopPicMonitor(uint32_t sessionId) = 0;

	/** 查询设备车位状态信息
	    @param uint32_t sessionId							会话Id
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryParkingStatus(const char* deviceId) = 0;

	/** 交通流量订阅
    @param uint32_t nSubscribeFlag						订阅标记。0:取消订阅，1：订阅
	@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SubscribeTrafficFlow(uint32_t nSubscribeFlag) = 0;

	/** 区间测速订阅
	    @param uint32_t nSubscribeFlag						订阅标记。0:取消订阅，1：订阅
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SubscribeAreaSpeedDetect(uint32_t nSubscribeFlag) = 0;

	/** 车辆违章图片信息写入
	    @param Write_Traffic_Violation_t& stuWriteTrafficViolationInfo	违章信息数据
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int WriteTrafficViolation(Traffic_Violation_t& stuWriteTrafficViolationInfo) = 0;

	/** 车辆违章图片信息查询
	    @param const char* recordId							记录ID
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryTrafficViolation(const char* recordId) = 0;
	
	/** 查询所有线圈状态信息
	    @param uint32_t sessionId							会话Id
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryAllWindingInfo() = 0;

	/** 人脸卡口操作
		@ param long requestFlag	用户自定义请求标记
		@ param jsonData	 请求数据的json包，人脸卡口相关操作采用通用json协议
		@ param eOptType	 操作类型，非必须
	*/
	virtual int FaceDataOpt(long requestFlag, const dsl::Json::Value& jsonData, FaceDataOptType eOptType = FACEDATA_OPT_UNDEFINE) = 0;

	/* 发送短信激活MTP300设备，使用SendAppAlarmMsg，且要用AppAlarmHepler打包组XML，所以外面传参数串进来
	@ const char* szInfo	 字符串格式：接收者,正文  
	*/
	virtual int SendMsgToWakeUpDev(const char* szInfo) = 0;

	/** 获取卡口设备状态
	    @param const char * cameraId						通道ID
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetBatchStatus(const std::vector<std::string>* vecDevId) = 0;

protected:
	virtual ~IDPSDKBay(void){}
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif

