/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227286, Author: 251672, Date: 2024-09-02 17:23:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetDeviceAlarmRegion_H_
#define _LC_OPENAPI_CLIENT_SetDeviceAlarmRegion_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置动检区域
 */

typedef struct SetDeviceAlarmRegionRequest 
{
	LCOpenApiRequest base;

	struct SetDeviceAlarmRegionRequestData
	{
		
		/** 设备来源，lc：乐橙设备，paas：大华设备 */
		CSTR sourceType;
		/** 授权Token */
		CSTR token;
		/** 通道号 */
		CSTR channelId;
		/** 动检区域 */
		CSTR region ;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} SetDeviceAlarmRegionRequest;

C_API SetDeviceAlarmRegionRequest *LCOPENAPI_INIT(SetDeviceAlarmRegionRequest);

typedef struct SetDeviceAlarmRegionResponse 
{
	LCOpenApiResponse base;

	struct SetDeviceAlarmRegionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetDeviceAlarmRegionResponse;

C_API SetDeviceAlarmRegionResponse *LCOPENAPI_INIT(SetDeviceAlarmRegionResponse);

#endif
