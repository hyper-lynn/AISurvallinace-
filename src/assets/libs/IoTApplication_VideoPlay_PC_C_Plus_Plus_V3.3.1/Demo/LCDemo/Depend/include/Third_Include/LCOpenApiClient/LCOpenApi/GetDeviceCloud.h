/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetDeviceCloud_H_
#define _LC_OPENAPI_CLIENT_GetDeviceCloud_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取当前设备的云存储服务信息

 */

typedef struct GetDeviceCloudRequest 
{
	LCOpenApiRequest base;

	struct GetDeviceCloudRequestData
	{
		
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetDeviceCloudRequest;

C_API GetDeviceCloudRequest *LCOPENAPI_INIT(GetDeviceCloudRequest);

typedef struct GetDeviceCloudResponse 
{
	LCOpenApiResponse base;

	struct GetDeviceCloudResponseData
	{
		
		/** 套餐名称 */
		CSTR name;
		/** [bool]是否有默认套餐 */
		BOOL hasDefault;
		/** 套餐结束时间 默认套餐切未开通 此字段为空 */
		CSTR endTime;
		/** 套餐开启时间 默认套餐切未开通 此字段为空 */
		CSTR beginTime;
		/** [int]套餐状态 -1-未开通 0-过期 1-使用中 2-暂停 */
		int strategyStatus;
		/** [long]云存储策略id 默认套餐 此字段为空 */
		int64 strategyId;
 
	} data;

} GetDeviceCloudResponse;

C_API GetDeviceCloudResponse *LCOPENAPI_INIT(GetDeviceCloudResponse);

#endif
