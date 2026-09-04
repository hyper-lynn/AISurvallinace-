/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetHeatMapEnable_H_
#define _LC_OPENAPI_CLIENT_SetHeatMapEnable_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置热度分析通道级使能开关

 */

typedef struct SetHeatMapEnableRequest 
{
	LCOpenApiRequest base;

	struct SetHeatMapEnableRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** on打开，off关闭 */
		CSTR enable;
		/** 通道ID */
		CSTR channelId;
		/** [cstr]setHeatMapEnable */
		#define _STATIC_SetHeatMapEnableRequestData_method "setHeatMapEnable"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetHeatMapEnableRequest;

C_API SetHeatMapEnableRequest *LCOPENAPI_INIT(SetHeatMapEnableRequest);

typedef struct SetHeatMapEnableResponse 
{
	LCOpenApiResponse base;

	struct SetHeatMapEnableResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetHeatMapEnableResponse;

C_API SetHeatMapEnableResponse *LCOPENAPI_INIT(SetHeatMapEnableResponse);

#endif
