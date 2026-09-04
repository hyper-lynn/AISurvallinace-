/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteDeviceShare_H_
#define _HSVIEW_CLIENT_API_DeleteDeviceShare_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除某台设备（某个通道）对某个用户的共享权限。
【使用平台账号签名】
 */

typedef struct DeleteDeviceShareRequest 
{
	HsviewRequest base;

	struct DeleteDeviceShareRequestData
	{
		
		/** 需要删除共享的用户名 */
		CSTR username;
		/** 通道号，如果为空表示不指定 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} DeleteDeviceShareRequest;

C_API DeleteDeviceShareRequest *HSAPI_INIT(DeleteDeviceShareRequest);

typedef struct DeleteDeviceShareResponse 
{
	HsviewResponse base;

	struct DeleteDeviceShareResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteDeviceShareResponse;

C_API DeleteDeviceShareResponse *HSAPI_INIT(DeleteDeviceShareResponse);

#endif
