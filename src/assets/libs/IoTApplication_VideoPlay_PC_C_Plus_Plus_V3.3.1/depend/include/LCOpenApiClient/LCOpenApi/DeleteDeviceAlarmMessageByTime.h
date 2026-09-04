/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeleteDeviceAlarmMessageByTime_H_
#define _LC_OPENAPI_CLIENT_DeleteDeviceAlarmMessageByTime_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
根据时间段批量删除设备通道报警消息
 */

typedef struct DeleteDeviceAlarmMessageByTimeRequest 
{
	LCOpenApiRequest base;

	struct DeleteDeviceAlarmMessageByTimeRequestData
	{
		
		/** 授权token */
		CSTR token;
		/** 设备本地结束时间 */
		CSTR endTime;
		/** 通道序列号 */
		CSTR channelId;
		/** 设备本地开始时间 */
		CSTR beginTime;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} DeleteDeviceAlarmMessageByTimeRequest;

C_API DeleteDeviceAlarmMessageByTimeRequest *LCOPENAPI_INIT(DeleteDeviceAlarmMessageByTimeRequest);

typedef struct DeleteDeviceAlarmMessageByTimeResponse 
{
	LCOpenApiResponse base;

	struct DeleteDeviceAlarmMessageByTimeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteDeviceAlarmMessageByTimeResponse;

C_API DeleteDeviceAlarmMessageByTimeResponse *LCOPENAPI_INIT(DeleteDeviceAlarmMessageByTimeResponse);

#endif
