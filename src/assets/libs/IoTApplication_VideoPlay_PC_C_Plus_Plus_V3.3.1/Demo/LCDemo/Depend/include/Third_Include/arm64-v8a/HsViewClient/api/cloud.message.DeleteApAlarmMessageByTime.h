/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_DeleteApAlarmMessageByTime_H_
#define _HSVIEW_CLIENT_API_cloudMessage_DeleteApAlarmMessageByTime_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据设备序列号和配件ID删除指定时间段内的配件报警信息。

【使用平台账号签名】
 */

typedef struct cloudMessage_DeleteApAlarmMessageByTimeRequest 
{
	HsviewRequest base;

	struct cloudMessage_DeleteApAlarmMessageByTimeRequestData
	{
		
		/** 设备本地结束时间,yyyyMMddTHHmmss格式 */
		CSTR endTime;
		/** 配件ID */
		CSTR apId;
		/** 设备本地开始时间,yyyyMMddTHHmmss格式 */
		CSTR beginTime;
		/** 网关设备ID */
		CSTR deviceId;

	} data;

} cloudMessage_DeleteApAlarmMessageByTimeRequest;

C_API cloudMessage_DeleteApAlarmMessageByTimeRequest *HSAPI_INIT(cloudMessage_DeleteApAlarmMessageByTimeRequest);

typedef struct cloudMessage_DeleteApAlarmMessageByTimeResponse 
{
	HsviewResponse base;

	struct cloudMessage_DeleteApAlarmMessageByTimeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} cloudMessage_DeleteApAlarmMessageByTimeResponse;

C_API cloudMessage_DeleteApAlarmMessageByTimeResponse *HSAPI_INIT(cloudMessage_DeleteApAlarmMessageByTimeResponse);

#endif
