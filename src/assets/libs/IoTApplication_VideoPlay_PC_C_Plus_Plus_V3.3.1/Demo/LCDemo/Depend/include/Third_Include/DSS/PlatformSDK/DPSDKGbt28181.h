/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,28181模块
 *
 * 当前版本：1.0
 * 原作者　：13031
 * 完成日期：2012年8月24日
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKGBT28181_H
#define INCLUDED_DPSDK_DPSDKGBT28181_H

#include "DPSDK.h"

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

// 存放公用数据
class DPSDK_API GBTBaseMsg : public DPSDKCBMessage
{
public:
	GBTBaseMsg();
	~GBTBaseMsg(){}

	char		message[DPSDK_28181_MSG_LENGTH];
	char		serverId[SERVER_ID_LEN];			// 服务ID
	char		deviceId[DPSDK_CHL_ID_LEN];			// 摄像头ID
};

// 获取前端设备状态通知消息
class DPSDK_API GetDeviceStatusInfoMsg : public GBTBaseMsg
{
public:
	GetDeviceStatusInfoMsg(void);  
	virtual ~GetDeviceStatusInfoMsg(void){}

public:
	char sn[DPSDK_28181_CHL_COUNT];
	char encode[DPSDK_28181_CHL_COUNT];
	char record[DPSDK_28181_CHL_COUNT];
	char deviceTime[DPSDK_TIMESTR_LEN];
	char devId[DPSDK_28181_CHL_COUNT];
	char status[DPSDK_28181_CHL_COUNT];
	char alarmNum[DPSDK_28181_CHL_COUNT];
	char online[DPSDK_28181_CHL_COUNT];

	char alarmId1[DPSDK_28181_CHL_COUNT];
	char alarmStatus1[DPSDK_28181_CHL_COUNT];
	char alarmId2[DPSDK_28181_CHL_COUNT];
	char alarmStatus2[DPSDK_28181_CHL_COUNT];		// 0不在线 1重登陆ADS成功 2断线
};

// ADS获取前端设备状态通知消息
class DPSDK_API GetDeviceInfoMsg : public GBTBaseMsg
{
public:
	GetDeviceInfoMsg(void);  
	virtual ~GetDeviceInfoMsg(void){}

public:
	char devId[DPSDK_28181_CHL_COUNT];
	char sn[DPSDK_28181_CHL_COUNT];
	char devType[DPSDK_28181_CHL_COUNT];
	char manu[DPSDK_28181_CHL_COUNT];
	char model[DPSDK_28181_CHL_COUNT];
	char firmware[DPSDK_28181_CHL_COUNT];
	char maxCamera[DPSDK_28181_CHL_COUNT];
	char maxAlarm[DPSDK_28181_CHL_COUNT];
	char diskNum[DPSDK_28181_CHL_COUNT];
	char diskTotal[DPSDK_28181_CHL_COUNT];
	char diskUsed[DPSDK_28181_CHL_COUNT];
	char diskRemained[DPSDK_28181_CHL_COUNT];

	/*** 以下参数, 可选. ***/
	char encode[DPSDK_28181_CHL_COUNT];
	char record[DPSDK_28181_CHL_COUNT];
};

// 
class DPSDK_API GbtDeviceAlarmNotifyMsg : public DPSDKCBMessage
{
public:
	GbtDeviceAlarmNotifyMsg(void);
	virtual ~GbtDeviceAlarmNotifyMsg(void){}

public:

	char devId[DPSDK_28181_CHL_COUNT];
	char alarmPriority[DPSDK_28181_CHL_COUNT];
	char time[DPSDK_TIMESTR_LEN];
	char alarmMethod[DPSDK_28181_CHL_COUNT];
	char alarmDescription[DPSDK_28181_ALARM_DES_LEN];
	char longitude[DPSDK_28181_CHL_COUNT];
	char latitude[DPSDK_28181_CHL_COUNT];
};


//////////////////////////////////////////////////////////////////////////

class DPSDK_API IDPSDKGbt28181 : public IDPSDKFuncBase
{
public:


	/** 前端校时
		@param const char* szDevId							设备ID
		@param const char* szTime							时间
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int AdjustTime(const char* szDevId, const char* szTime) = 0;

	/** 获取前端设备状态信息
		@param const char* szDevId							设备ID
		@param const char* szSN							    互联编码
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetDeviceStatusInfo(const char* szDevId, const char* szSN) = 0;

	/** 获取前端设备信息
		@param const char* szDevId							设备ID
		@param const char* szSN							    互联编码
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetDeviceInfo(const char* szDevId, const char* szSN) = 0;

	/** 手动启动前端录像
		@param const char* szDevId							设备ID
		@param const char* szSN							    互联编码
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int StartManualRecording(const char* szDevId, const char* szSN) = 0;

	/** 手动停止前端录像
		@param const char* szDevId							设备ID
		@param const char* szSN							    互联编码
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int StopManualRecording(const char* szDevId, const char* szSN) = 0;

	/** 设备恢复
		@param const char* szDevId							设备ID
		@param const char* szSN							    互联编码
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int DeviceRecovery(const char* szDevId, const char* szSN,int bChannel = 0,int chnlID = 0) = 0;

	/** 停止恢复
		@param const char* szDevId							设备ID
		@param const char* szSN							    互联编码
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int StopRecovery(const char* szDevId, const char* szSN,int bChannel = 0,int chnlID = 0) = 0;
	
	/** 设备报警重置
		@param const char* szDevId							设备ID
		@param const char* szSN							    互联编码
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int DeviceAlarmReset(const char* szDevId, const char* szSN,int bChannel = 0,int chnlID = 0) = 0;
	
	/** 设备重启
		@param const char* szDevId							设备ID
		@param const char* szSN							    互联编码
		@param const int type								0:DMS;1:PES
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int DeviceReboot(const char* szDevId, const char* szSN) = 0;

	/** 获取解码器设备状态信息
		@param const char* szDevId							设备ID
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetDecoderDeviceStatusInfo(const char* szDevId) = 0;

	/** 获取解码器设备信息
		@param const char* szDevId							设备ID
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetDecoderDeviceInfo(const char* szDevId) = 0;

	/** 解码器设备重启
		@param const char* szDevId							设备ID
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int DecoderDeviceReboot(const char* szDevId) = 0;

protected:
	virtual ~IDPSDKGbt28181(void){}
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif
