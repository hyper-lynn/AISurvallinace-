/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 223439, Author: 304780, Date: 2022-10-12 16:27:55 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetDeviceSensitivity_H_
#define _LC_OPENAPI_CLIENT_GetDeviceSensitivity_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取火情灵敏度
 */

typedef struct GetDeviceSensitivityRequest 
{
	LCOpenApiRequest base;

	struct GetDeviceSensitivityRequestData
	{
		
		/** 灵敏度类型,type = fwSens火灾预警灵敏度 */
		CSTR type;
		/** 通道,不存在默认为设备 */
		CSTR channelId;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} GetDeviceSensitivityRequest;

C_API GetDeviceSensitivityRequest *LCOPENAPI_INIT(GetDeviceSensitivityRequest);

typedef struct GetDeviceSensitivityResponse 
{
	LCOpenApiResponse base;

	struct GetDeviceSensitivityResponseData
	{
		
		/** 可选，挡位 */
		CSTR gear;
		/** 可选, 按档位选取时 支持的档位集合，当gear存在时，grears必选 */
		DECLARE_LIST(CSTR) grears;
		/** 可选， 按范围选取时 取值范围 */
		DECLARE_LIST(CSTR) senRange;
		/** 当前灵敏度 */
		CSTR sensitivity;
 
	} data;

} GetDeviceSensitivityResponse;

C_API GetDeviceSensitivityResponse *LCOPENAPI_INIT(GetDeviceSensitivityResponse);

#endif
