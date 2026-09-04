/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 221328, Author: 27665, Date: 2021-10-19 14:35:56 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ConfigDeviceSmokeSensitivity_H_
#define _LC_OPENAPI_CLIENT_ConfigDeviceSmokeSensitivity_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
配置设备烟感灵敏度
 */

typedef struct ConfigDeviceSmokeSensitivityRequest 
{
	LCOpenApiRequest base;

	struct ConfigDeviceSmokeSensitivityRequestData
	{
		
		/** 灵敏度档位 */
		CSTR gear;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} ConfigDeviceSmokeSensitivityRequest;

C_API ConfigDeviceSmokeSensitivityRequest *LCOPENAPI_INIT(ConfigDeviceSmokeSensitivityRequest);

typedef struct ConfigDeviceSmokeSensitivityResponse 
{
	LCOpenApiResponse base;

	struct ConfigDeviceSmokeSensitivityResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ConfigDeviceSmokeSensitivityResponse;

C_API ConfigDeviceSmokeSensitivityResponse *LCOPENAPI_INIT(ConfigDeviceSmokeSensitivityResponse);

#endif
