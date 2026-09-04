/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_DeviceOwnerInfoGetPlus_H_
#define _HSVIEW_CLIENT_API_deviceManager_DeviceOwnerInfoGetPlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备拥有者信息

【使用平台账号签名】
 */

typedef struct deviceManager_DeviceOwnerInfoGetPlusRequest 
{
	HsviewRequest base;

	struct deviceManager_DeviceOwnerInfoGetPlusRequestData
	{
		
		/** [O]通道号，海外分享是按照设备级别的，所以通道号不需要 */
		CSTR channelId;
		/** [O]产品ID */
		CSTR productId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} deviceManager_DeviceOwnerInfoGetPlusRequest;

C_API deviceManager_DeviceOwnerInfoGetPlusRequest *HSAPI_INIT(deviceManager_DeviceOwnerInfoGetPlusRequest);

typedef struct deviceManager_DeviceOwnerInfoGetPlusResponse 
{
	HsviewResponse base;

	struct deviceManager_DeviceOwnerInfoGetPlusResponseData
	{
		
		/** 拥有者用户id */
		CSTR ownerId;
		/** [O]拥有者的账号，加掩 */
		CSTR ownerAccount;
		/** [O]拥有者头像 */
		CSTR ownerUserIcon;
		/** [O]拥有者昵称 */
		CSTR ownerNickname;
		/** [O]请求者给备注名，本人请求无该参数 */
		CSTR ownerComment;
 
	} data;

} deviceManager_DeviceOwnerInfoGetPlusResponse;

C_API deviceManager_DeviceOwnerInfoGetPlusResponse *HSAPI_INIT(deviceManager_DeviceOwnerInfoGetPlusResponse);

#endif
