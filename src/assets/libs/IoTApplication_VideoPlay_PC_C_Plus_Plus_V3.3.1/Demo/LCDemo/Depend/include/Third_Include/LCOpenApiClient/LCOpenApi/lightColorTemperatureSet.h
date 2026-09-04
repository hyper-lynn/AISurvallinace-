/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 223048, Author: 304780, Date: 2022-07-22 10:29:52 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_lightColorTemperatureSet_H_
#define _LC_OPENAPI_CLIENT_lightColorTemperatureSet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置探照灯的色温
 */

typedef struct lightColorTemperatureSetRequest 
{
	LCOpenApiRequest base;

	struct lightColorTemperatureSetRequestData
	{
		
		/** 色温，cold/warm */
		CSTR colorTemperature;
		/** 通道号 */
		CSTR channelId;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} lightColorTemperatureSetRequest;

C_API lightColorTemperatureSetRequest *LCOPENAPI_INIT(lightColorTemperatureSetRequest);

typedef struct lightColorTemperatureSetResponse 
{
	LCOpenApiResponse base;

	struct lightColorTemperatureSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} lightColorTemperatureSetResponse;

C_API lightColorTemperatureSetResponse *LCOPENAPI_INIT(lightColorTemperatureSetResponse);

#endif
