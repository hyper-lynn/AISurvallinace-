/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UnBindDeviceCloud_H_
#define _LC_OPENAPI_CLIENT_UnBindDeviceCloud_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
解绑设备云存储

 */

typedef struct UnBindDeviceCloudRequest 
{
	LCOpenApiRequest base;

	struct UnBindDeviceCloudRequestData
	{
		
		/** 云存储唯一Id */
		CSTR deviceCloudId;
		/** [cstr]unBindDeviceCloud */
		#define _STATIC_UnBindDeviceCloudRequestData_method "unBindDeviceCloud"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;

	} data;

} UnBindDeviceCloudRequest;

C_API UnBindDeviceCloudRequest *LCOPENAPI_INIT(UnBindDeviceCloudRequest);

typedef struct UnBindDeviceCloudResponse 
{
	LCOpenApiResponse base;

	struct UnBindDeviceCloudResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UnBindDeviceCloudResponse;

C_API UnBindDeviceCloudResponse *LCOPENAPI_INIT(UnBindDeviceCloudResponse);

#endif
