/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_UserDeviceUnbind_H_
#define _HSVIEW_CLIENT_API_deviceManager_UserDeviceUnbind_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
deviceId是需要解绑的设备序列号。注意必须是该用户名下的设备
【需要使用平台账号签名】
 */

typedef struct deviceManager_UserDeviceUnbindRequest 
{
	HsviewRequest base;

	struct deviceManager_UserDeviceUnbindRequestData
	{
		
		/** [O]是否将云存储回用户库存,delete:回库存(默认),retain:保持不变 */
		CSTR deleteCloudStorage;
		/** 是否一起删除该设备的云录像,delete:删除,retain:保留 */
		CSTR deleteCloudRecords;
		/** 是否一起删除该设备的报警消息,delete:删除,retain:保留 */
		CSTR deleteCloudAlarms;
		/** 设备ID */
		CSTR deviceId;

	} data;

} deviceManager_UserDeviceUnbindRequest;

C_API deviceManager_UserDeviceUnbindRequest *HSAPI_INIT(deviceManager_UserDeviceUnbindRequest);

typedef struct deviceManager_UserDeviceUnbindResponse 
{
	HsviewResponse base;

	struct deviceManager_UserDeviceUnbindResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceManager_UserDeviceUnbindResponse;

C_API deviceManager_UserDeviceUnbindResponse *HSAPI_INIT(deviceManager_UserDeviceUnbindResponse);

#endif
