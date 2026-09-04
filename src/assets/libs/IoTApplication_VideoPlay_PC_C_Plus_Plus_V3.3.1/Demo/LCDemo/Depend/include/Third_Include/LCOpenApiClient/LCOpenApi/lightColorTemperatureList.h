/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 223048, Author: 304780, Date: 2022-07-22 10:29:52 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_lightColorTemperatureList_H_
#define _LC_OPENAPI_CLIENT_lightColorTemperatureList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取探照灯的色温
 */

typedef struct lightColorTemperatureListRequest 
{
	LCOpenApiRequest base;

	struct lightColorTemperatureListRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} lightColorTemperatureListRequest;

C_API lightColorTemperatureListRequest *LCOPENAPI_INIT(lightColorTemperatureListRequest);

typedef struct lightColorTemperatureListResponse 
{
	LCOpenApiResponse base;

	struct lightColorTemperatureListResponseData
	{
		
		/** 色温 cold/warm */
		CSTR colorTemperature;
		/** 支持的色温列表 */
		DECLARE_LIST(CSTR) supports;
 
	} data;

} lightColorTemperatureListResponse;

C_API lightColorTemperatureListResponse *LCOPENAPI_INIT(lightColorTemperatureListResponse);

#endif
