/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetHeatMapEnable_H_
#define _LC_OPENAPI_CLIENT_GetHeatMapEnable_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置热度分析通道级使能开关

 */

typedef struct GetHeatMapEnableRequest 
{
	LCOpenApiRequest base;

	struct GetHeatMapEnableRequestData
	{
		
		/** [cstr]getHeatMapEnable */
		#define _STATIC_GetHeatMapEnableRequestData_method "getHeatMapEnable"
		CSTR method;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetHeatMapEnableRequest;

C_API GetHeatMapEnableRequest *LCOPENAPI_INIT(GetHeatMapEnableRequest);

typedef struct GetHeatMapEnableResponse 
{
	LCOpenApiResponse base;

	struct GetHeatMapEnableResponseData
	{
		
		/** on打开，off关闭 */
		CSTR enable;
 
	} data;

} GetHeatMapEnableResponse;

C_API GetHeatMapEnableResponse *LCOPENAPI_INIT(GetHeatMapEnableResponse);

#endif
