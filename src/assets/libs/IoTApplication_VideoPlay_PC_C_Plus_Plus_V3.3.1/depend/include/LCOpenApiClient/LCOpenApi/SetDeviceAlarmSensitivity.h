/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetDeviceAlarmSensitivity_H_
#define _LC_OPENAPI_CLIENT_SetDeviceAlarmSensitivity_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置动检灵敏度
 */

typedef struct SetDeviceAlarmSensitivityRequest 
{
	LCOpenApiRequest base;

	struct SetDeviceAlarmSensitivityRequestData
	{
		
		/** [int][Not Null]面积阈值,取值范围0-100 */
		int threshold;
		/** 授权Token */
		CSTR token;
		/** 通道号，为空表示设置设备名称 */
		CSTR channelId;
		/** [int][Not Null]灵敏度,目前支持5个档位 1灵敏度最低 5灵敏度最高 */
		int sensitive;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} SetDeviceAlarmSensitivityRequest;

C_API SetDeviceAlarmSensitivityRequest *LCOPENAPI_INIT(SetDeviceAlarmSensitivityRequest);

typedef struct SetDeviceAlarmSensitivityResponse 
{
	LCOpenApiResponse base;

	struct SetDeviceAlarmSensitivityResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetDeviceAlarmSensitivityResponse;

C_API SetDeviceAlarmSensitivityResponse *LCOPENAPI_INIT(SetDeviceAlarmSensitivityResponse);

#endif
