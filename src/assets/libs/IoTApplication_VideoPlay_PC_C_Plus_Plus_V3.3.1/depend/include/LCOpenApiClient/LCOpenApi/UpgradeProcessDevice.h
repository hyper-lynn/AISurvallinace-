/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UpgradeProcessDevice_H_
#define _LC_OPENAPI_CLIENT_UpgradeProcessDevice_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询设备升级状态和进度

 */

typedef struct UpgradeProcessDeviceRequest 
{
	LCOpenApiRequest base;

	struct UpgradeProcessDeviceRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} UpgradeProcessDeviceRequest;

C_API UpgradeProcessDeviceRequest *LCOPENAPI_INIT(UpgradeProcessDeviceRequest);

typedef struct UpgradeProcessDeviceResponse 
{
	LCOpenApiResponse base;

	struct UpgradeProcessDeviceResponseData
	{
		
		/** 升级状态，idle:没有升级,downloading:正在下载升级包,upgrading:升级中 */
		CSTR status;
		/** 版本号 */
		CSTR version;
		/** 百分比 */
		CSTR percent;
 
	} data;

} UpgradeProcessDeviceResponse;

C_API UpgradeProcessDeviceResponse *LCOPENAPI_INIT(UpgradeProcessDeviceResponse);

#endif
