/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_DeleteDeviceAlarmMessageByTime_H_
#define _HSVIEW_CLIENT_API_cloudMessage_DeleteDeviceAlarmMessageByTime_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据设备序列号和通道号删除指定时间段内的报警信息。

【使用平台账号签名】
 */

typedef struct cloudMessage_DeleteDeviceAlarmMessageByTimeRequest 
{
	HsviewRequest base;

	struct cloudMessage_DeleteDeviceAlarmMessageByTimeRequestData
	{
		
		/** 设备本地结束时间,yyyyMMddTHHmmss格式 */
		CSTR endTime;
		/** 删除设备下该通道号的报警消息 */
		CSTR channelId;
		/** 设备本地开始时间,yyyyMMddTHHmmss格式 */
		CSTR beginTime;
		/** 删除该设备ID的报警消息 */
		CSTR deviceId;

	} data;

} cloudMessage_DeleteDeviceAlarmMessageByTimeRequest;

C_API cloudMessage_DeleteDeviceAlarmMessageByTimeRequest *HSAPI_INIT(cloudMessage_DeleteDeviceAlarmMessageByTimeRequest);

typedef struct cloudMessage_DeleteDeviceAlarmMessageByTimeResponse 
{
	HsviewResponse base;

	struct cloudMessage_DeleteDeviceAlarmMessageByTimeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} cloudMessage_DeleteDeviceAlarmMessageByTimeResponse;

C_API cloudMessage_DeleteDeviceAlarmMessageByTimeResponse *HSAPI_INIT(cloudMessage_DeleteDeviceAlarmMessageByTimeResponse);

#endif
