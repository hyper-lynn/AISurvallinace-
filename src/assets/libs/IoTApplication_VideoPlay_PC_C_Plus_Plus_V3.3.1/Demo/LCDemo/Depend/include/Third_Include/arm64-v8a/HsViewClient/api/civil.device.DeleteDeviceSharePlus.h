/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteDeviceSharePlus_H_
#define _HSVIEW_CLIENT_API_DeleteDeviceSharePlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除某台设备（某个通道）对某个用户的共享权限。
【使用平台账号签名】
 */

typedef struct DeleteDeviceSharePlusRequest 
{
	HsviewRequest base;

	struct DeleteDeviceSharePlusRequestData
	{
		
		/** 通道号，如果为空表示不指定 */
		CSTR channelId;
		/** 需要删除共享的用户ID */
		CSTR userId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} DeleteDeviceSharePlusRequest;

C_API DeleteDeviceSharePlusRequest *HSAPI_INIT(DeleteDeviceSharePlusRequest);

typedef struct DeleteDeviceSharePlusResponse 
{
	HsviewResponse base;

	struct DeleteDeviceSharePlusResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteDeviceSharePlusResponse;

C_API DeleteDeviceSharePlusResponse *HSAPI_INIT(DeleteDeviceSharePlusResponse);

#endif
