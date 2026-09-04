/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_DeviceVersionBatchGet_H_
#define _HSVIEW_CLIENT_API_deviceManager_DeviceVersionBatchGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
批量获取设备版本信息及升级包的版本信息。

注：当canBeUpgrade为true时，upgradeVersion字段才有意义，才返回upgradeInfo信息。
当请求用户对所有设备有权限时，才正常返回。

【需要使用平台账号签名】
 */

typedef struct deviceManager_DeviceVersionBatchGetRequest 
{
	HsviewRequest base;

	struct deviceManager_DeviceVersionBatchGetRequestData
	{
		
		/** 设备序列号 */
		DECLARE_LIST(CSTR) deviceIds;

	} data;

} deviceManager_DeviceVersionBatchGetRequest;

C_API deviceManager_DeviceVersionBatchGetRequest *HSAPI_INIT(deviceManager_DeviceVersionBatchGetRequest);

typedef struct deviceManager_DeviceVersionBatchGetResponse 
{
	HsviewResponse base;

	struct deviceManager_DeviceVersionBatchGetResponseData
	{
		
		/** define a list with struct of deviceManager_DeviceVersionBatchGetResponseData_DevicesElement */
		DECLARE_LIST(struct deviceManager_DeviceVersionBatchGetResponseData_DevicesElement
		{
			/** [bool]true : 有新版本可以升级,返回upgradeInfo字段信息, false : 不可以升级, 不需要返回upgradeInfo字段 */
			BOOL canBeUpgrade;
			/** struct of deviceManager_DeviceVersionBatchGetResponseData_DevicesElement_UpgradeInfo */
			struct deviceManager_DeviceVersionBatchGetResponseData_DevicesElement_UpgradeInfo {
				/** [O]升级包版本号 */
				CSTR version;
				/** [O]升级包url地址 */
				CSTR packageUrl;
				/** [O]升级包描述信息 */
				CSTR description;
				/** [O]是否需要app进行强制升级，true表示需要强制升级，false表示不需要强制升级 */
				CSTR isAppForced;
			} upgradeInfo;
			/** 设备当前版本号 */
			CSTR version;
			/** 设备序列号 */
			CSTR deviceId;
		}) devices;
 
	} data;

} deviceManager_DeviceVersionBatchGetResponse;

C_API deviceManager_DeviceVersionBatchGetResponse *HSAPI_INIT(deviceManager_DeviceVersionBatchGetResponse);

#endif
