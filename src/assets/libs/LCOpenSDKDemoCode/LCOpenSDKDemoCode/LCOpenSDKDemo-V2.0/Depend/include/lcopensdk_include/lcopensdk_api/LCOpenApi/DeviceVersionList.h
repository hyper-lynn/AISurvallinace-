/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceVersionList_H_
#define _LC_OPENAPI_CLIENT_DeviceVersionList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备可升级信息

 */

typedef struct DeviceVersionListRequest 
{
	LCOpenApiRequest base;

	struct DeviceVersionListRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]deviceVersionList */
		#define _STATIC_DeviceVersionListRequestData_method "deviceVersionList"
		CSTR method;
		/** 设备ID */
		CSTR deviceIds;

	} data;

} DeviceVersionListRequest;

C_API DeviceVersionListRequest *LCOPENAPI_INIT(DeviceVersionListRequest);

typedef struct DeviceVersionListResponse 
{
	LCOpenApiResponse base;

	struct DeviceVersionListResponseData
	{
		
		/** [int]返回的设备列表总数 */
		int count;
		/** define a list with struct of DeviceVersionListResponseData_DeviceVersionListElement */
		DECLARE_LIST(struct DeviceVersionListResponseData_DeviceVersionListElement
		{
			/** [bool]是否可以升级true : 有新版本可以升级,返回upgradeInfo字段信息, false : 不可以升级, 不需要返回upgradeInfo字段 */
			BOOL canBeUpgrade;
			/** struct of DeviceVersionListResponseData_DeviceVersionListElement_UpgradeInfo */
			struct DeviceVersionListResponseData_DeviceVersionListElement_UpgradeInfo {
				/** [String]升级包url地址 */
				CSTR packageUrl;
				/** [String]升级包描述信息 */
				CSTR description;
				/** [String]升级包版本号 */
				CSTR version;
			} upgradeInfo;
			/** [String]设备当前版本号 */
			CSTR version;
			/** [String]设备序列号 */
			CSTR deviceId;
		}) deviceVersionList;
 
	} data;

} DeviceVersionListResponse;

C_API DeviceVersionListResponse *LCOPENAPI_INIT(DeviceVersionListResponse);

#endif
