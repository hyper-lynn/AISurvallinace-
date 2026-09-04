/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetDeviceUpgradeVersion_H_
#define _HSVIEW_CLIENT_API_GetDeviceUpgradeVersion_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备的最新升级包。
可以同时请求多个设备，返回的是每个设备的升级包信息。
【使用平台账号签名】
 */

typedef struct GetDeviceUpgradeVersionRequest 
{
	HsviewRequest base;

	struct GetDeviceUpgradeVersionRequestData
	{
		
		/** 设备ID */
		DECLARE_LIST(CSTR) deviceIds;

	} data;

} GetDeviceUpgradeVersionRequest;

C_API GetDeviceUpgradeVersionRequest *HSAPI_INIT(GetDeviceUpgradeVersionRequest);

typedef struct GetDeviceUpgradeVersionResponse 
{
	HsviewResponse base;

	struct GetDeviceUpgradeVersionResponseData
	{
		
		/** define a list with struct of GetDeviceUpgradeVersionResponseData_VersionListElement */
		DECLARE_LIST(struct GetDeviceUpgradeVersionResponseData_VersionListElement
		{
			/** 升级描述信息 */
			CSTR description;
			/** 升级包url地址 */
			CSTR url;
			/** 设备版本号 */
			CSTR version;
			/** 设备ID */
			CSTR deviceId;
		}) versionList;
 
	} data;

} GetDeviceUpgradeVersionResponse;

C_API GetDeviceUpgradeVersionResponse *HSAPI_INIT(GetDeviceUpgradeVersionResponse);

#endif
