/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 220387, Author: 21818, Date: 2021-07-14 14:45:20 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_RestartDevice_H_
#define _LC_OPENAPI_CLIENT_RestartDevice_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
重启设备(只支持设备级重启)

 */

typedef struct RestartDeviceRequest 
{
	LCOpenApiRequest base;

	struct RestartDeviceRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} RestartDeviceRequest;

C_API RestartDeviceRequest *LCOPENAPI_INIT(RestartDeviceRequest);

typedef struct RestartDeviceResponse 
{
	LCOpenApiResponse base;

	struct RestartDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} RestartDeviceResponse;

C_API RestartDeviceResponse *LCOPENAPI_INIT(RestartDeviceResponse);

#endif
