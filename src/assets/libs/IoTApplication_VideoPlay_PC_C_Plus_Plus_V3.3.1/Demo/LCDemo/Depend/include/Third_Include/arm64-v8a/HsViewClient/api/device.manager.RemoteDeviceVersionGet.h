/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_RemoteDeviceVersionGet_H_
#define _HSVIEW_CLIENT_API_deviceManager_RemoteDeviceVersionGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取远程设备版本信息及升级包的版本信息

注：当canBeUpgrade为true时，upgradeVersion字段才有意义

【需要使用平台账号签名】
 */

typedef struct deviceManager_RemoteDeviceVersionGetRequest 
{
	HsviewRequest base;

	struct deviceManager_RemoteDeviceVersionGetRequestData
	{
		
		/** 远程设备序列号 */
		CSTR accessDeviceId;

	} data;

} deviceManager_RemoteDeviceVersionGetRequest;

C_API deviceManager_RemoteDeviceVersionGetRequest *HSAPI_INIT(deviceManager_RemoteDeviceVersionGetRequest);

typedef struct deviceManager_RemoteDeviceVersionGetResponse 
{
	HsviewResponse base;

	struct deviceManager_RemoteDeviceVersionGetResponseData
	{
		
		/** struct of deviceManager_RemoteDeviceVersionGetResponseData_UpgradeInfo */
		struct deviceManager_RemoteDeviceVersionGetResponseData_UpgradeInfo {
			/** [O]升级包url地址 */
			CSTR packageUrl;
			/** [O]升级包描述信息 */
			CSTR description;
			/** [O]允许APP强制升级描述信息 */
			CSTR appForecedDecs;
			/** [O]升级包版本号 */
			CSTR version;
			/** [O]是否需要app进行强制升级，true表示需要强制升级，false表示不需要强制升级 */
			CSTR isAppForced;
		} upgradeInfo;
		/** [bool]是否可以升级 */
		BOOL canBeUpgrade;
		/** 设备当前版本号 */
		CSTR version;
 
	} data;

} deviceManager_RemoteDeviceVersionGetResponse;

C_API deviceManager_RemoteDeviceVersionGetResponse *HSAPI_INIT(deviceManager_RemoteDeviceVersionGetResponse);

#endif
