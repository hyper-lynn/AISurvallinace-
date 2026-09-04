/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_clientConfig_DeviceModelImageInfosCheck_H_
#define _HSVIEW_CLIENT_API_clientConfig_DeviceModelImageInfosCheck_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
一键oem协议，设备型号图片配置信息检查更新(使用clientUA内的信息)

【使用平台账号签名】
 */

typedef struct clientConfig_DeviceModelImageInfosCheckRequest 
{
	HsviewRequest base;

	struct clientConfig_DeviceModelImageInfosCheckRequestData
	{
		
		/** APP本地缓存了配置后，请求使用上次请求配置服务返回的时间，检查是否需要更新配置 */
		CSTR updateTime;

	} data;

} clientConfig_DeviceModelImageInfosCheckRequest;

C_API clientConfig_DeviceModelImageInfosCheckRequest *HSAPI_INIT(clientConfig_DeviceModelImageInfosCheckRequest);

typedef struct clientConfig_DeviceModelImageInfosCheckResponse 
{
	HsviewResponse base;

	struct clientConfig_DeviceModelImageInfosCheckResponseData
	{
		
		/** 是否更新，yes, no */
		CSTR isUpdated;
 
	} data;

} clientConfig_DeviceModelImageInfosCheckResponse;

C_API clientConfig_DeviceModelImageInfosCheckResponse *HSAPI_INIT(clientConfig_DeviceModelImageInfosCheckResponse);

#endif
