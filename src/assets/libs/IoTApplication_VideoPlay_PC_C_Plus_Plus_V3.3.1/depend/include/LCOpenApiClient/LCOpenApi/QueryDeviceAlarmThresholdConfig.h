/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 221328, Author: 27665, Date: 2021-10-19 14:35:56 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryDeviceAlarmThresholdConfig_H_
#define _LC_OPENAPI_CLIENT_QueryDeviceAlarmThresholdConfig_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询设备烟感灵敏度配置
 */

typedef struct QueryDeviceAlarmThresholdConfigRequest 
{
	LCOpenApiRequest base;

	struct QueryDeviceAlarmThresholdConfigRequestData
	{
		
		/** type=temperature 表示温度 type=humidity 表示湿度 */
		CSTR type;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} QueryDeviceAlarmThresholdConfigRequest;

C_API QueryDeviceAlarmThresholdConfigRequest *LCOPENAPI_INIT(QueryDeviceAlarmThresholdConfigRequest);

typedef struct QueryDeviceAlarmThresholdConfigResponse 
{
	LCOpenApiResponse base;

	struct QueryDeviceAlarmThresholdConfigResponseData
	{
		
		/** [int]告警阈值 */
		int threshold;
		/** [int]告警阈值可选范围 */
		DECLARE_LIST(int) range;
 
	} data;

} QueryDeviceAlarmThresholdConfigResponse;

C_API QueryDeviceAlarmThresholdConfigResponse *LCOPENAPI_INIT(QueryDeviceAlarmThresholdConfigResponse);

#endif
