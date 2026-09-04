/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceAlarmGearSet_H_
#define _LC_OPENAPI_CLIENT_DeviceAlarmGearSet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置动检档位
 */

typedef struct DeviceAlarmGearSetRequest 
{
	LCOpenApiRequest base;

	struct DeviceAlarmGearSetRequestData
	{
		
		/** 表示档位，取值范围为[1, 6] */
		CSTR gear;
		/** [O]通道号 */
		CSTR channelId;
		/** xxx */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} DeviceAlarmGearSetRequest;

C_API DeviceAlarmGearSetRequest *LCOPENAPI_INIT(DeviceAlarmGearSetRequest);

typedef struct DeviceAlarmGearSetResponse 
{
	LCOpenApiResponse base;

	struct DeviceAlarmGearSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeviceAlarmGearSetResponse;

C_API DeviceAlarmGearSetResponse *LCOPENAPI_INIT(DeviceAlarmGearSetResponse);

#endif
