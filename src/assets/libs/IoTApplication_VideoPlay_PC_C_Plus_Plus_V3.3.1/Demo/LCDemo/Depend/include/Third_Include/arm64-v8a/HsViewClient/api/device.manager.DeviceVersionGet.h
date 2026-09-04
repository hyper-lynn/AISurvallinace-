/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_DeviceVersionGet_H_
#define _HSVIEW_CLIENT_API_deviceManager_DeviceVersionGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备版本信息及升级包的版本信息

注：当canBeUpgrade为true时，upgradeVersion字段才有意义

【需要使用平台账号签名】
 */

typedef struct deviceManager_DeviceVersionGetRequest 
{
	HsviewRequest base;

	struct deviceManager_DeviceVersionGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} deviceManager_DeviceVersionGetRequest;

C_API deviceManager_DeviceVersionGetRequest *HSAPI_INIT(deviceManager_DeviceVersionGetRequest);

typedef struct deviceManager_DeviceVersionGetResponse 
{
	HsviewResponse base;

	struct deviceManager_DeviceVersionGetResponseData
	{
		
		/** struct of deviceManager_DeviceVersionGetResponseData_UpgradeInfo */
		struct deviceManager_DeviceVersionGetResponseData_UpgradeInfo {
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

} deviceManager_DeviceVersionGetResponse;

C_API deviceManager_DeviceVersionGetResponse *HSAPI_INIT(deviceManager_DeviceVersionGetResponse);

#endif
