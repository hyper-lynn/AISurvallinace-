/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UnBindDevice_H_
#define _LC_OPENAPI_CLIENT_UnBindDevice_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
解绑设备

 */

typedef struct UnBindDeviceRequest 
{
	LCOpenApiRequest base;

	struct UnBindDeviceRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]unBindDevice */
		#define _STATIC_UnBindDeviceRequestData_method "unBindDevice"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} UnBindDeviceRequest;

C_API UnBindDeviceRequest *LCOPENAPI_INIT(UnBindDeviceRequest);

typedef struct UnBindDeviceResponse 
{
	LCOpenApiResponse base;

	struct UnBindDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UnBindDeviceResponse;

C_API UnBindDeviceResponse *LCOPENAPI_INIT(UnBindDeviceResponse);

#endif
