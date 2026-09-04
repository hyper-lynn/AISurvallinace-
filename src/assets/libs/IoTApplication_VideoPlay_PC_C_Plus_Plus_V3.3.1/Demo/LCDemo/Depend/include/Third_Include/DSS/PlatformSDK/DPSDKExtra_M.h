/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：电子围栏接口文件
 *
 * 当前版本：1.0
 * 原作者　：15693
 * 完成日期：2013年2月20日
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_AREA_INTERFACE_H
#define INCLUDED_DPSDK_AREA_INTERFACE_H

#include "DPSDK.h"
#include <vector>
#include "DPSDKGeneral.h"
#include "UserXMLParser/XMLArea.h"

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

typedef enum
{
	CAR_RELATION_ADD		= 1,				// 增加
	CAR_RELATION_MOD		= 2,				// 修改
	CAR_RELATION_DEL		= 3,				// 删除
}dpsdk_car_relation_change_type;

// 存放公用数据
class DPSDK_API MServerBaseMsg : public DPSDKCBMessage
{
public:
	MServerBaseMsg(int cmd = DPSDK_CMD_UNKNOWN,int msgType = DPSDK_MSG_RESPONSE);
	~MServerBaseMsg(){}

	char	serverId[SERVER_ID_LEN];		//服务ID
	char	cameraId[DPSDK_CHL_ID_LEN];		//摄像头ID
};

// 电子围栏改变通知消息
class DPSDK_API NotifyAreaChangeMsg : public DPSDKCBMessage
{
public:
	NotifyAreaChangeMsg(void);
	virtual ~NotifyAreaChangeMsg(void){};
};

// 关联关系改变通知消息
class DPSDK_API NotifyRelationChangeMsg : public DPSDKCBMessage
{
public:
	NotifyRelationChangeMsg(void);
	virtual ~NotifyRelationChangeMsg(void){};
};

// 获取电子围栏结果消息
class DPSDK_API AskForAreaInfoMsg : public DPSDKCBMessage
{
public:
	AskForAreaInfoMsg(void);
	virtual ~AskForAreaInfoMsg(void);

public:
	char*	tmpXml;
	int		nLen;
};

// 获取关联关系结果消息
class DPSDK_API AskForDevAreaRelationMsg : public DPSDKCBMessage
{
public:
	AskForDevAreaRelationMsg(void);
	virtual ~AskForDevAreaRelationMsg(void);

public:
	char*	tmpXml;
	int		nLen;
};

// 获取电子围栏GPS点结果消息
class DPSDK_API AskForAreaPointsMsg : public DPSDKCBMessage
{
public:
	AskForAreaPointsMsg(void);
	virtual ~AskForAreaPointsMsg(void);

public:
	dsl::DStr	strAreaId;

	char*		tmpXml;
	int			nLen;
};

// 获取电子围栏权限结果消息
class DPSDK_API AskForAreaRightsMsg : public DPSDKCBMessage
{
public:
	AskForAreaRightsMsg(void);
	virtual ~AskForAreaRightsMsg(void);

public:
	char*	tmpXml;
	int		nLen;
};

// 获取最后一次GPS信息
class DPSDK_API AskForLastGpsStatusMsg : public DPSDKCBMessage
{
public:
	AskForLastGpsStatusMsg(void);
	virtual ~AskForLastGpsStatusMsg(void);

public:
	char*	tmpXml;
	int		nLen;
};
// 获取最后一次油箱信息
class DPSDK_API AskForLastGasStatusMsg : public DPSDKCBMessage
{
public:
	AskForLastGasStatusMsg(void);
	virtual ~AskForLastGasStatusMsg(void);

public:
	char*	tmpXml;
	int		nLen;
};

// 获取最后一次状态信息
class DPSDK_API AskForLastDevStatusMsg : public DPSDKCBMessage
{
public:
	AskForLastDevStatusMsg(void);
	virtual ~AskForLastDevStatusMsg(void);

public:
	char*	tmpXml;
	int		nLen;
};

// 增加电子围栏结果消息
class DPSDK_API AddAreaMsg : public DPSDKCBMessage
{
public:
	AddAreaMsg(void);
	virtual ~AddAreaMsg(void);

public:
	dsl::DStr	strAreaId;
	int			nAreaType;					// 围栏类型
	char		szAreaAttr[32];				// 围栏所属
	char		szAreaName[64];				// 围栏名称
	int			nMaxSpeed;					// 限速
	int			nCarlimit;					// 车辆限速
	char*		pData;						// 经纬度数据
	int			nLen;						// 长度
};

// 删除电子围栏结果消息
class DPSDK_API DelAreaMsg : public DPSDKCBMessage
{
public:
	DelAreaMsg(void);
	virtual ~DelAreaMsg(void){};

public:
	dsl::DStr	strAreaId;
};

// 修改电子围栏结果消息
class DPSDK_API ModAreaMsg : public DPSDKCBMessage
{
public:
	ModAreaMsg(void);
	virtual ~ModAreaMsg(void);

public:
	dsl::DStr	strAreaId;
	int			nAreaType;					// 围栏类型
	char		szAreaAttr[32];				// 围栏所属
	char		szAreaName[64];				// 围栏名称
	int			nMaxSpeed;					// 限速
	int			nCarlimit;					// 车辆限速
	char*		pData;						// 经纬度数据
	int			nLen;						// 长度
};

// 上传关联关系结果消息
class DPSDK_API UploadRelationMsg : public DPSDKCBMessage
{
public:
	UploadRelationMsg(void);
	virtual ~UploadRelationMsg(void);

public:
	char*	pData;
	int		nLen;
};

// 增加关联结果(只增加本地未上传)
class AddAreaInDevMsg : public DPSDKCBMessage
{
public:
	AddAreaInDevMsg(void);
	virtual ~AddAreaInDevMsg(void){};

public:
	dsl::DStr	strDevId;
	dsl::DStr	strAreaId;
	int			nAreaType;
};

// 删除关联结果(只删除本地未上传)
class DPSDK_API DelAreaInDevMsg : public DPSDKCBMessage
{
public:
	DelAreaInDevMsg(void);
	virtual ~DelAreaInDevMsg(void){};

public:
	dsl::DStr	strDevId;
	dsl::DStr	strAreaId;
};

// OSD字幕叠加消息
class DPSDK_API SetDeviceOsdInfoMsg : public MServerBaseMsg
{
public:
	SetDeviceOsdInfoMsg(void);
	virtual ~SetDeviceOsdInfoMsg(void);

public:
	dsl::DStr	strDevId;
	dsl::DStr	strOsdInfo;
	char*		pData;
	int			nLen;
};

// add by lm 南京地铁项目 增加通道序号
class DPSDK_API SetDeviceOsdInfoMsgEx : public MServerBaseMsg
{
public:
	SetDeviceOsdInfoMsgEx(void);
	virtual ~SetDeviceOsdInfoMsgEx(void);

public:
	dsl::DStr	strDevId;
	dsl::DStr	strOsdInfo;
	int			nChnlNo;				// 通道序号	
	char*		pData;
	int			nLen;
	int			nRemainTime;			// osd叠加，叠加持续时间 0：为一直叠加
};

// 开始手动录像
class DPSDK_API StartRecordMsg : public DPSDKCBMessage
{
public:
	StartRecordMsg(void);
	virtual ~StartRecordMsg(void){};

public:
	dsl::DStr	strCamId;
	encdev_stream_e streamType;			// 实时码流类型
	uint64_t	nPlanId;
	time_t		stCurTime;
};

// 结束手动录像
class DPSDK_API StopRecordMsg : public DPSDKCBMessage
{
public:
	StopRecordMsg(void);
	virtual ~StopRecordMsg(void){};

public:
	dsl::DStr	strCamId;
	encdev_stream_e streamType;			// 实时码流类型
	uint64_t	nPlanId;
	time_t		stCurTime;
};

// 文本消息
class DPSDK_API SetDeviceCfgInfoMsg : public MServerBaseMsg
{
public:
	SetDeviceCfgInfoMsg(void);
	virtual ~SetDeviceCfgInfoMsg(void);

public:
	dsl::DStr	strDevId;
	dsl::DStr	strCfgInfo;
	char*		pData;
	int			nLen;
};

// 远程设备抓图
class DPSDK_API RemoteDeviceSnapMsg : public MServerBaseMsg
{
public:
	RemoteDeviceSnapMsg(void);
	virtual ~RemoteDeviceSnapMsg(void){};

public:
	dsl::DStr	strCameraId;
	dsl::DStr	strLocalPath;
};

// 远程设备抓图
class DPSDK_API DeviceSnapNotifyMsg : public MServerBaseMsg
{
public:
	DeviceSnapNotifyMsg(void);
	virtual ~DeviceSnapNotifyMsg(void);

public:
	dsl::DStr	strDevId;
	int			nChnlNo;
	dsl::DStr	strFullPath;

	char*		pData;
	int			nLen;
};

// 设备上传录像到平台，俄罗斯需求引入
class DPSDK_API DeviceRecord2PlatformMsg : public DPSDKCBMessage
{
public:
	DeviceRecord2PlatformMsg();
	virtual ~DeviceRecord2PlatformMsg();

public:
	dsl::DStr	m_strDevId;
	int			m_nChnlNo;
	uint64_t		m_nBeginTime;
	uint64_t		m_nEndTime;
};

// 
class DPSDK_API DeviceGps2CmsMsg : public DPSDKCBMessage
{
public:
	DeviceGps2CmsMsg();
	virtual ~DeviceGps2CmsMsg();
public:
	dsl::DStr	m_strDevId;
	dsl::DStr   m_strXmlGps;
};

// 获取信息统一结构
class DPSDK_API DevConfigInfoMsg : public MServerBaseMsg
{
public:
	DevConfigInfoMsg(void);
	virtual ~DevConfigInfoMsg(void);

public:
	dsl::DStr	devId;
	int			nCofType;	
	int			nIndex;
};

// 版本信息回调
class DPSDK_API DevVersionInfoMsg : public DPSDKCBMessage
{
public:
	DevVersionInfoMsg(void);
	virtual ~DevVersionInfoMsg(void);

public:
	char		devId[DPSDK_DEV_ID_LEN];
	char       strVersionInfo[DPSDK_POINT_COUNT];	// 设备版本号
	char		strTemperature[DPSDK_POINT_COUNT];	// 设备温度
	char		strElectric[DPSDK_POINT_COUNT];		// 设备电压
};

// 硬盘信息回调
class DPSDK_API DevHardDiskInfoMsg : public DPSDKCBMessage
{
public:
	DevHardDiskInfoMsg(void);
	virtual ~DevHardDiskInfoMsg(void);
public:
	char		devId[DPSDK_DEV_ID_LEN];
	int			nDiskCount;
	char		_diskXml[DPSDK_XML_LENGTH];
};

// 码流信息回调
class DPSDK_API DevStreamConfigInfoMsg : public DPSDKCBMessage
{
public:
	DevStreamConfigInfoMsg(void);
	virtual ~DevStreamConfigInfoMsg(void);
public:
	char		devId[DPSDK_DEV_ID_LEN];
	int			nChannelCount;
	char		_StreamXml[DPSDK_XML_LENGTH];	
};

// 设置信息统一结构
class DPSDK_API SaveDevAllConfigInfoMsg : public MServerBaseMsg		
{
public:
	SaveDevAllConfigInfoMsg(void);
	virtual ~SaveDevAllConfigInfoMsg(void);
public:
	dsl::DStr	devId;
	int			nCofType;
	int			nIndex;
	char		_confXML[DPSDK_XML_LENGTH];
};

// 抓图信息配置回调
class DPSDK_API DevSnapPicConfigInfoMsg : public DPSDKCBMessage
{
public:
	DevSnapPicConfigInfoMsg(void);
	virtual ~DevSnapPicConfigInfoMsg(void);
public:
	char		devId[DPSDK_DEV_ID_LEN];
	int			nChannelCount;
	char		_SnapPicXml[DPSDK_XML_LENGTH];		// 信息文件
};

// 设备自检信息配置回调
class DPSDK_API DevAutoCheckInfoMsg : public DPSDKCBMessage
{
public:
	DevAutoCheckInfoMsg(void);
	virtual ~DevAutoCheckInfoMsg(void);
public:
	char		devId[DPSDK_DEV_ID_LEN];
	char		_AutoCheckJson[DPSDK_XML_LENGTH];		// 信息文件
};
//设备录像查询
class DPSDK_API DevRecordTimeRangeMsg : public MServerBaseMsg
{
public:
	DevRecordTimeRangeMsg(void);
	virtual ~DevRecordTimeRangeMsg(void);
public:
	char		devId[DPSDK_DEV_ID_LEN];
	int		nIndex;
	char		_DevRecordJson[DPSDK_XML_LENGTH];		// 信息文件
};

class DPSDK_API DevConfigRetMsg : public DPSDKCBMessage
{
public:
	DevConfigRetMsg(void);
	virtual ~DevConfigRetMsg(void);
public:
	int m_iCmd;			// 子命令
	int m_iRes;			// 存放DMS返回的操作结果
};

class DPSDK_API ClearDevAlarmMsg : public MServerBaseMsg
{
public:
	ClearDevAlarmMsg(void);
	virtual ~ClearDevAlarmMsg(void){};
public:
	dsl::DStr strDevId;
	int nChnlNo;
	int nType;
};

class DPSDK_API GetAllDevThirdStreamMsg : public MServerBaseMsg
{
public:
	GetAllDevThirdStreamMsg(void);
	virtual ~GetAllDevThirdStreamMsg(void);
public:
	char*				pData;						// 数据
	int					nLen;						// 数据长度
};

class DPSDK_API Dev3GFlowInfoMsg : public DPSDKCBMessage
{
public:
	Dev3GFlowInfoMsg(void);
	virtual ~Dev3GFlowInfoMsg(void);
public:
	char*				pData;						// 数据
	int					nLen;						// 数据长度
};

class DPSDK_API GetDevInfoByRegDevIdMsg : public DPSDKCBMessage
{
public:
	dsl::DStr			regdevid;
	dsl::DStr			devinfo;//xml

	bool				sync;
	void*				msgevent;
public:
	GetDevInfoByRegDevIdMsg(void);
	virtual ~GetDevInfoByRegDevIdMsg(void);
};

class DPSDK_API GetUserInfoListMsg : public DPSDKCBMessage	
{
public:
	GetUserInfoListMsg(void);
	virtual ~GetUserInfoListMsg(void);

public:
	char*	tmpXml;
	int		nLen;
};

class DPSDK_API GetClassChangeInfoMsg : public DPSDKCBMessage
{
public:
	GetClassChangeInfoMsg(void);
	virtual ~GetClassChangeInfoMsg(void);

public:
	char*	tmpXml;
	int		nLen;
};

class DPSDK_API NotifyUserInfoChange : public DPSDKCBMessage
{
public:
	NotifyUserInfoChange(void);
	virtual ~NotifyUserInfoChange(void){};
};

class DPSDK_API SaveClassChangeMsg : public DPSDKCBMessage
{
public:
	SaveClassChangeMsg(void);
	virtual ~SaveClassChangeMsg(void);
public:
	int					nUserId;
	dsl::DStr			strUserName;
	dsl::DStr			strUserNum;
	dsl::DStr			strTime;
	dsl::DStr			strMsg;
};

class DPSDK_API DeviceRecordUploadResultMsg : public DeviceRecord2PlatformMsg
{
public:
	DeviceRecordUploadResultMsg();
	virtual ~DeviceRecordUploadResultMsg();
public:
	int					m_nCode;
	int					m_nResult;
};

class DPSDK_API OperateOSDTemplatMsg : public DPSDKCBMessage
{
public:
	OperateOSDTemplatMsg(void);
	virtual~OperateOSDTemplatMsg(void);
public:
	int					nTemplateId;
	int					nOpeType;				// 操作类型(1add,2modify,3del)
	int					nMsgType;				// (1osd,2sms)
	dsl::DStr			strMessage;
	dsl::DStr			strName;				// 名称
	dsl::DStr			strMemo;				// 备注
};

class DPSDK_API GetOSDTemplatMsg : public DPSDKCBMessage
{
public:
	GetOSDTemplatMsg(void);
	virtual ~GetOSDTemplatMsg(void);

public:
	char*	tmpXml;
	int		nLen;
};

class DPSDK_API GetHistoryOSDInfoMsg : public DPSDKCBMessage
{
public:
	GetHistoryOSDInfoMsg(void);
	virtual ~GetHistoryOSDInfoMsg(void);
public:
	int64_t		nBeginTime;
	int64_t		nEndTime;
	int			nMsgType;
	dsl::DStr	strDevId;
	int			nCount;
	char*		tmpXml;						// CMS返回查询信息
	int			nLen;						// CMS返回查询信息长度
};

// OSD字幕叠加消息
class DPSDK_API SendSMSMsg : public MServerBaseMsg
{
public:
	SendSMSMsg(void);
	virtual ~SendSMSMsg(void);

public:
	int			nUserId;
	dsl::DStr	strDevId;
	dsl::DStr	strDevName;
	dsl::DStr	strSMSInfo;
	dsl::DStr	strSMSNo;
	int64_t		nTime;
};

class DPSDK_API AreaTimeRangeMsg : public DPSDKCBMessage
{
public:
	AreaTimeRangeMsg(void);
	virtual ~AreaTimeRangeMsg(void);

public:
	dsl::DStr strAreaId;
	char*	 tmpXml;
	int		 nLen;	
};

class DPSDK_API SetAreaTimeRangeMsg : public DPSDKCBMessage
{
public:
	SetAreaTimeRangeMsg(void);
	virtual ~SetAreaTimeRangeMsg(void);

public:
	dsl::DStr	strAreaId;
	char*	tmpXml;
	int		nLen;	
};

class DPSDK_API GetDataBaseTypeMsg : public DPSDKCBMessage
{
public:
	GetDataBaseTypeMsg(void);
	virtual ~GetDataBaseTypeMsg(void);

public:
	int nType;
};

class DPSDK_API GetOwnLineInfoMsg : public GeneralJsonTransportMsg
{
public:
	GetOwnLineInfoMsg(void)
	{
		m_cmd = DPSDK_CMD_EXTRA_M_GETOWNLINEINFO;
		nUserId = 0;
	}
	virtual ~GetOwnLineInfoMsg(void){return;};
public:
	int nUserId;
	dsl::Json::Value jData; 
};

class DPSDK_API GetBusScheduleMsg : public GeneralJsonTransportMsg
{
public:
	GetBusScheduleMsg(void)
	{
		m_cmd = DPSDK_CMD_EXTRA_M_GETBUSSCHEDULESINFO;
		strBegTime = "";
		strEndTime = "";
		vectLineId.clear();
	}
	virtual ~GetBusScheduleMsg(void){};
public:
	dsl::DStr strBegTime;
	dsl::DStr strEndTime;
	std::vector<int> vectLineId;
	dsl::Json::Value jData; 
};

class DPSDK_API GetLastStationsMsg : public GeneralJsonTransportMsg
{
public:
	GetLastStationsMsg(void)
	{
		m_cmd = DPSDK_CMD_EXTRA_M_GETLASTSTATIONS;
		nLineId = 0;
	}
	virtual ~GetLastStationsMsg(void){};
public:
	int nLineId;
	dsl::Json::Value jData; 
};

class DPSDK_API NotifyScheduleChangeMsg : public DPSDKCBMessage		//排班信息改变
{
public:
	NotifyScheduleChangeMsg(void);
	virtual ~NotifyScheduleChangeMsg(void){};
public:
	int nLineId;
};

class DPSDK_API NotifyScheduleStateChangeMsg : public DPSDKCBMessage
{
public:
	NotifyScheduleStateChangeMsg(void);
	virtual ~NotifyScheduleStateChangeMsg(void){};
public:
	int nLineId;
	dsl::DStr strDevId;
	int nState;
	int nLineType;
	int nPlanId;
	dsl::DStr strTime;
};

class DPSDK_API GetDriverMobileNumberMsg : public DPSDKCBMessage
{
public:
	GetDriverMobileNumberMsg();
	~GetDriverMobileNumberMsg();

public:
	dsl::DStr	m_strDeviceId;
	dsl::Json::Value	m_jsonData;
};

class DPSDK_API NotifyDispatchInfoMsg : public DPSDKCBMessage			//调度结果信息
{
public:
	NotifyDispatchInfoMsg(void);
	virtual ~NotifyDispatchInfoMsg(void){};
public:
	int nPlanId;
	dsl::DStr	strLinName;
	dsl::DStr	strDevName;
	uint32_t	nDisPatchTime;
	uint32_t	nDepartTime;
	int			nState;
};

class DPSDK_API NotifyCUStartPatrolMsg : public DPSDKCBMessage			//开始巡更任务信息
{
public:
	NotifyCUStartPatrolMsg(void);
	virtual ~NotifyCUStartPatrolMsg(void){};
public:
	uint64_t	_param1;							//参数1
	uint64_t	_param2;							//参数2
	char	_strMsg1[1024*3];		//字符参数1
	char	_strMsg2[1024*3];		//字符参数2
};

class DPSDK_API ReloadVidelPatrolPlanlMsg : public DPSDKCBMessage			//重新加载巡更计划信息
{
public:
	ReloadVidelPatrolPlanlMsg(void);
	virtual ~ReloadVidelPatrolPlanlMsg(void){};
};

class DPSDK_API NotifyCUUpdateReplyFast : public DPSDKCBMessage			//开始巡更任务信息
{
public:
	NotifyCUUpdateReplyFast(void);
	virtual ~NotifyCUUpdateReplyFast(void){};
public:
	uint64_t	_param1;							//参数1
	uint64_t	_param2;							//参数2
	char	_strMsg1[1024*3];		//字符参数1
	char	_strMsg2[1024*3];		//字符参数2
};

//车辆关联关系改变通知
class DPSDK_API CarRelationNotifyMsg : public DPSDKCBMessage
{
public:
	CarRelationNotifyMsg(void);
	virtual ~CarRelationNotifyMsg(void){};

	dpsdk_car_relation_change_type	nChangeType;
	char							szIds[DPSDK_LINKRES_CHANGEID];
};
//////////////////////////////////////////////////////////////////////////
class DPSDK_API IDPSDKExtra_M : public IDPSDKFuncBase
{
public:
	/** 获取电子围栏信息
	    @return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int AskForAreaInfo(void) = 0;
	
	/** 获取设备围栏关系
	    @return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int AskForDevAreaRelation(void) = 0;
	
	/** 获取电子围栏点位信息
		@param dsl::DStr strAreaId			围栏ID
	    @return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int AskForAreaPoints(dsl::DStr strAreaId) = 0;
	
	/** 获取围栏权限
	    @return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int AskForAreaRight(void) = 0;
	
	/** 获取最后一次GPS信息
	    @return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int AskForLastGpsStatus(void) = 0;

	/** 获取最后一次油耗信息
	    @return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int AskForLastGasStatus(void) = 0;

	/** 获取最后一次设备信息
	    @return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int AskForLastDevStatus(void) = 0;

	/** 获取解析出的电子围栏信息
	    @return								解析出的电子围栏信息
	*/
	virtual DPSdkToolKit::AreaInfo_Map GetAreaInfoMap() = 0;
	
	/** 获取解析出的设备围栏关系
	    @return								解析出的设备围栏关系
	*/
	virtual DPSdkToolKit::DevAreaRelation_Map GetDevAreaRelationMap() = 0;

	/** 获取围栏权限
	    @return								是否有权限
	*/
 	virtual bool GetRightByType(int nRightType) = 0;
	
	/** 根据围栏ID 获取围栏信息权限
		@param dsl::DStr strAreaId			围栏ID
		@param AreaInfo_t* areaInfo			围栏信息 外部创建 内部赋值 外部使用、释放
	    @return								是否存在 成功返回0
	*/
	virtual int GetAreaInfo(dsl::DStr strAreaId, DPSdkToolKit::AreaInfo_t* areaInfo) = 0;
	
	/** 根据围栏类型 获取围栏个数
		@param int nAreaType				围栏类型
	    @return								个数
	*/
	virtual int GetAreaCountByType(int nAreaType) = 0;
	
	/** 获取设备关联的围栏个数
		@param dsl::DStr strDevId				设备ID
	    @return								个数
	*/
	virtual int GetAreaCountByDev(dsl::DStr strDevId) = 0;
	
	/** 检验电子围栏名称是否重复
		@param dsl::DStr strAreaName		电子围栏名称
	    @return								true：存在  false：不存在
	*/
	virtual bool IsAreaNameUsed(dsl::DStr strAreaName) = 0;

	/** 增加电子围栏
		@param AreaInfo_t areaInfo			电子围栏信息
		@param dsl::DStr* strDevId			关联的设备ID
		@param int nCount					关联的设备ID个数
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int AddAreaInfo( DPSdkToolKit::AreaInfo_t &areaInfo, dsl::DStr* strDevId, int nCount) = 0;
	
	/** 删除电子围栏
		@param dsl::DStr strAreaId			电子围栏ID
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int DelAreaInfo(dsl::DStr strAreaId) = 0;
	
	/** 修改电子围栏
		@param dsl::DStr strAreaId			电子围栏ID
		@param AreaInfo_t areaInfo			新的电子围栏信息
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int ModAreaInfo(dsl::DStr strAreaId, DPSdkToolKit::AreaInfo_t &areaInfo) = 0;

	/** 增加设备与电子围栏的关联（只修改了本地内存中的，需要Upload才上传服务）
		@param dsl::DStr strDevId			设备ID
		@param dsl::DStr strAreaId			电子围栏ID
		@param int nAreaType				电子围栏类型
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int AddAreaInDev(dsl::DStr strDevId, dsl::DStr strAreaId, int nAreaType) = 0;
	
	/** 删除设备与电子围栏的关联（只修改了本地内存中的，需要Upload才上传服务）
		@param dsl::DStr strDevId			设备ID
		@param dsl::DStr strAreaId			电子围栏ID
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int DelAreaInDev(dsl::DStr strDevId, dsl::DStr strAreaId) = 0;
	
	/** 上传设备与围栏关系给服务
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int UploadRelationChange(void) = 0;
	
	/** 设置设备Osd叠加信息
		@param dsl::DStr strDevId			设备ID
		@param dsl::DStr strOsdInfo			Osd内容
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SetDeviceOsdInfo(dsl::DStr strDevId, dsl::DStr strOsdInfo) = 0;

	/** 设置设备Osd叠加信息,南京地铁项目比SetDeviceOsdInfo多一个通道号
		@param dsl::DStr strDevId			设备ID
		@param int nChnlNo					通道号
		@param dsl::DStr strOsdInfo			Osd内容
		@param int nRemainTime				osd叠加持续时间， 0：一直叠加，不取消
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SetDeviceOsdInfoEX(dsl::DStr strDevId, int nChnlNo, dsl::DStr strOsdInfo, int nRemainTime = 0) = 0;
	
	/** 开始手动录像
		@param dsl::DStr strCameraId		通道ID
		@param encdev_stream_e streamType	手动录像的码流类型,加默认参数，兼容
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int StartRecord(dsl::DStr strCameraId, encdev_stream_e streamType = STREAM_MAIN) = 0;
	
	/** 关闭手动录像
		@param dsl::DStr strCameraId		通道ID
		@param encdev_stream_e streamType	手动录像的码流类型,加默认参数，兼容
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int StopRecord(dsl::DStr strCameraId, encdev_stream_e streamType = STREAM_MAIN) = 0;

	/** 设置设备文本信息
		@param dsl::DStr strDevId			设备ID
		@param dsl::DStr strCfgInfo			文本内容
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SetDeviceCfgInfo(dsl::DStr strDevId, dsl::DStr strCfgInfo) = 0;
	
	/** 远程设备抓图
		@param dsl::DStr strCameraId		设备ID
		@param dsl::DStr strLocalPath		本地路径
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int RemoteDeviceSnap(dsl::DStr strCameraId, dsl::DStr strLocalPath) = 0;
	
	/*清除设备报警消息
		@param dsl::DStr strDevId			设备ID
		@param int nIndex					通道号
		@param int nType					报警类型
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int ClearDevAlarm(dsl::DStr strDevId, int nIndex, int nType) = 0;

	/**@brief 请求把本地设备硬盘录像上传到平台
	 * @param dsl::DStr strDevId			设备ID
	 * @param int nChnlNo					通道号
	 * @param int nBeginTime				开始时间
	 * @param int nEndTime					结束时间
	 */
	virtual int DeviceRecord2Platform(dsl::DStr strDevId, int nChnlNo, uint64_t nBeginTime, uint64_t nEndTime) = 0;

	/** @brief 设备GPS上传到CMS
	 *  @param dsl::DStr strDevId			设备ID
	 *  @param char * xmlGps				指向存放需要上传的GPS的xml
	 */
	virtual int DeviceGps2Cms(dsl::DStr strDevId, char * xmlGps) = 0;

	/**获取设备版本等配置信息
		@param dsl::DStr strDevId			设备ID
		@param int nType					查找类型
		@param int nIndex					通道号	-1表示不使用该参数
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetDeviceAllConfigInfo(dsl::DStr strDevId, int nType, int nIndex = -1) = 0;

	/*设置设备配置信息*/
	/*  @param dsl::DStr strDevId			设备ID
	    @param int nType					查找类型
		@param char* chCofXml				设备属性xml
		@param int nIndex					通道号，-1表示不使用该参数
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SaveDeviceAllConfigInfo(dsl::DStr strDevId,  int nType, char* chCofXml, int nIndex=-1) = 0;

	/*获取设备三码流信息
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetAllDevThirdStream( void ) = 0;

	/*
	\brief 通过设备注册ID获取设备信息
	*/
	virtual int GetDevInfoByRegDevId(const char* regdevid, dsl::DStr& devinfo, bool bSync=true) = 0;

	/*获取用户信息列表*/
	/*  
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetUserInfoList(void) = 0;

	/*获取交接班信息列表*/
	/*  
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetClassChangeInfo(void) = 0;

	/*客户端保存交接班信息*/
	/*  @param int nUserId					用户id
	    @param dsl::DStr chName				用户名称
		@param dsl::DStr chNum				用户工号
		@param dsl::DStr chTime				时间
		@param dsl::DStr chMsg				信息
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SaveClassChangeMessage(int nUserId, dsl::DStr chName, dsl::DStr chNum, dsl::DStr chTime, dsl::DStr chMsg) = 0;

	/*客户端操作OSD信息模板*/
	/*  @param int nTemplatID				模板id
	    @param int nOpeType					操作类型
		@param int nMsgType					信息类型
		@param dsl::DStr chMessage			信息内容
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int OperateOSDTemplet(int nTemplatID, int nOpeType, int nMsgType, dsl::DStr chMessage, dsl::DStr chName, dsl::DStr chMemo) = 0;

	/*获取OSD信息模板列表*/
	/*  
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetOSDTemplatInfo(void) = 0;

	/*客户端查询历史OSD/SMS信息*/
	/*  @param int nBeginTime				开始时间
	    @param int nEndTime					结束时间
		@param int nMsgType					信息类型
		@param dsl::DStr chDevId			车辆id
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetHistoryOSDInfo(int64_t nBeginTime, int64_t nEndTime, int nMsgType, dsl::DStr chDevId, int nCount = 500) = 0;

	/*设置Sms信息*/
	/*  @param dsl::DStr strDevId			设备id
	    @param dsl::DStr strSMSInfo			信息内容
		@param dsl::DStr strSMSNo			发送号码
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SetDeviceSMSInfo( int UserId, dsl::DStr strDevId, dsl::DStr strDevName, dsl::DStr strSMSInfo, dsl::DStr strSMSNo, int64_t nTime) = 0;
	
	/*获取所有围栏时间属性*/
	/*  
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetAreaTimeRangeInfo(dsl::DStr strAreaId) = 0;

	/*设置围栏信息的时间段*/
	/*  @param dsl::DStr nAreaId			围栏id
	    @param char* pTimeXml				时间xml
		@param int nLen						xml字符长度
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SetAreaTimeRangeInfo( dsl::DStr strAreaId, const char* pTimeXml, int nLen) = 0;

	/*获取数据库类型（Oracle、mysql）*/
	/* 
		@return								异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetDataBaseType( ) = 0;

	/*获取自己权限下的线路信息 */
	/*
		@return								
	*/
	virtual int GetOwnLineInfo() = 0;

	/*获取排班信息 */
	/*@dsl::DStr strBeginTime, 开始时间
		@dsl::DStr strEndTime,结束时间
		@dsl::DStr strLineId线路id
		@return
	*/
	virtual int GetBusScheduleInfo(dsl::DStr strBeginTime, dsl::DStr strEndTime, std::vector<int>& listLineId) = 0;

	/*获取最新站点信息
	@dsl::DStr strLineId  线路id
	@reture；
	*/
	virtual int GetLastStationsInfo( int nLineId ) = 0;

	/*
	 *@brief 获取设备绑定的司机的手机号码
	 *@param szDeviceId 设备ID
	 *@return 
	 */
	virtual int GetDriverMobileNumberByDevId(dsl::DStr strDeviceId) = 0;
	
protected:
	virtual ~IDPSDKExtra_M(void){}
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif
