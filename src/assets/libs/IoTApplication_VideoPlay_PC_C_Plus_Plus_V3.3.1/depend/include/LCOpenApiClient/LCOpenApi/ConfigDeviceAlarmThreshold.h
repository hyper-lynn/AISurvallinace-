/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 221362, Author: 21818, Date: 2021-10-20 17:47:22 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ConfigDeviceAlarmThreshold_H_
#define _LC_OPENAPI_CLIENT_ConfigDeviceAlarmThreshold_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
配置设备告警阈值（当前支持温度和湿度）
 */

typedef struct ConfigDeviceAlarmThresholdRequest 
{
	LCOpenApiRequest base;

	struct ConfigDeviceAlarmThresholdRequestData
	{
		
		/** [int]告警阈值 */
		int threshold;
		/** type=temperature 表示温度 type=humidity 表示湿度 */
		CSTR type;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} ConfigDeviceAlarmThresholdRequest;

C_API ConfigDeviceAlarmThresholdRequest *LCOPENAPI_INIT(ConfigDeviceAlarmThresholdRequest);

typedef struct ConfigDeviceAlarmThresholdResponse 
{
	LCOpenApiResponse base;

	struct ConfigDeviceAlarmThresholdResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ConfigDeviceAlarmThresholdResponse;

C_API ConfigDeviceAlarmThresholdResponse *LCOPENAPI_INIT(ConfigDeviceAlarmThresholdResponse);

#endif
