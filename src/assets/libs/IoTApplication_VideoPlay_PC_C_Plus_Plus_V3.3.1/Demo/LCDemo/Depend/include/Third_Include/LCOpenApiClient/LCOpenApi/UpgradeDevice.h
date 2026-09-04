/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UpgradeDevice_H_
#define _LC_OPENAPI_CLIENT_UpgradeDevice_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备升级

 */

typedef struct UpgradeDeviceRequest 
{
	LCOpenApiRequest base;

	struct UpgradeDeviceRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} UpgradeDeviceRequest;

C_API UpgradeDeviceRequest *LCOPENAPI_INIT(UpgradeDeviceRequest);

typedef struct UpgradeDeviceResponse 
{
	LCOpenApiResponse base;

	struct UpgradeDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UpgradeDeviceResponse;

C_API UpgradeDeviceResponse *LCOPENAPI_INIT(UpgradeDeviceResponse);

#endif
