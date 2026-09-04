/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_RemoteDeviceUpgradeProgressGet_H_
#define _LC_OPENAPI_CLIENT_RemoteDeviceUpgradeProgressGet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
远程设备升级进度查询
 */

typedef struct RemoteDeviceUpgradeProgressGetRequest 
{
	LCOpenApiRequest base;

	struct RemoteDeviceUpgradeProgressGetRequestData
	{
		
		/** 远程设备序列号 */
		CSTR sn;
		/** xxx */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} RemoteDeviceUpgradeProgressGetRequest;

C_API RemoteDeviceUpgradeProgressGetRequest *LCOPENAPI_INIT(RemoteDeviceUpgradeProgressGetRequest);

typedef struct RemoteDeviceUpgradeProgressGetResponse 
{
	LCOpenApiResponse base;

	struct RemoteDeviceUpgradeProgressGetResponseData
	{
		
		/** 升级状态 */
		CSTR status;
		/** 当前版本 */
		CSTR version;
		/** 当前正在进行的百分比 */
		CSTR percent;
 
	} data;

} RemoteDeviceUpgradeProgressGetResponse;

C_API RemoteDeviceUpgradeProgressGetResponse *LCOPENAPI_INIT(RemoteDeviceUpgradeProgressGetResponse);

#endif
