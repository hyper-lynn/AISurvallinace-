/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_RemoteDeviceUpgrade_H_
#define _LC_OPENAPI_CLIENT_RemoteDeviceUpgrade_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取检测wifi网络的地址
 */

typedef struct RemoteDeviceUpgradeRequest 
{
	LCOpenApiRequest base;

	struct RemoteDeviceUpgradeRequestData
	{
		
		/** xxx */
		CSTR token;

	} data;

} RemoteDeviceUpgradeRequest;

C_API RemoteDeviceUpgradeRequest *LCOPENAPI_INIT(RemoteDeviceUpgradeRequest);

typedef struct RemoteDeviceUpgradeResponse 
{
	LCOpenApiResponse base;

	struct RemoteDeviceUpgradeResponseData
	{
		
		/** 检测wifi服务的地址 */
		CSTR addr;
 
	} data;

} RemoteDeviceUpgradeResponse;

C_API RemoteDeviceUpgradeResponse *LCOPENAPI_INIT(RemoteDeviceUpgradeResponse);

#endif
