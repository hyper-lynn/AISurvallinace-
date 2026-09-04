/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_DeviceOwnerInfoGet_H_
#define _HSVIEW_CLIENT_API_deviceManager_DeviceOwnerInfoGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备拥有者信息

【使用平台账号签名】
 */

typedef struct deviceManager_DeviceOwnerInfoGetRequest 
{
	HsviewRequest base;

	struct deviceManager_DeviceOwnerInfoGetRequestData
	{
		
		/** [O]通道号，海外分享是按照设备级别的，所以通道号不需要 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} deviceManager_DeviceOwnerInfoGetRequest;

C_API deviceManager_DeviceOwnerInfoGetRequest *HSAPI_INIT(deviceManager_DeviceOwnerInfoGetRequest);

typedef struct deviceManager_DeviceOwnerInfoGetResponse 
{
	HsviewResponse base;

	struct deviceManager_DeviceOwnerInfoGetResponseData
	{
		
		/** 拥有者用户id */
		CSTR ownerId;
		/** [O]拥有者头像 */
		CSTR ownerUserIcon;
		/** [O]拥有者昵称 */
		CSTR ownerNickname;
		/** [O]拥有者的账号 */
		CSTR ownerAccount;
 
	} data;

} deviceManager_DeviceOwnerInfoGetResponse;

C_API deviceManager_DeviceOwnerInfoGetResponse *HSAPI_INIT(deviceManager_DeviceOwnerInfoGetResponse);

#endif
