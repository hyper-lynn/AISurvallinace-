/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_RemoteDeviceUnbind_H_
#define _HSVIEW_CLIENT_API_deviceManager_RemoteDeviceUnbind_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
远程设备解绑

------------请求参数说明------------
channelId：公有云设备通道号，如NVR或者HUB设备通道号
-----------------------------------


------------响应参数说明------------
无
-----------------------------------

参考PaaS协议：[远程设备解绑](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%BF%9C%E7%A8%8B%E8%AE%BE%E5%A4%87%E8%A7%A3%E7%BB%91%2F%E8%BF%9C%E7%A8%8B%E8%AE%BE%E5%A4%87%E8%A7%A3%E7%BB%91.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct deviceManager_RemoteDeviceUnbindRequest 
{
	HsviewRequest base;

	struct deviceManager_RemoteDeviceUnbindRequestData
	{
		
		/** 是否删除该通道的云录像,delete:删除,retain:保留 */
		CSTR deleteCloudRecords;
		/** 公有云设备通道号，如NVR或者HUB设备通道号 */
		CSTR channelId;
		/** 是否删除该通道的报警消息,delete:删除,retain:保留 */
		CSTR deleteCloudAlarms;
		/** 设备ID */
		CSTR deviceId;

	} data;

} deviceManager_RemoteDeviceUnbindRequest;

C_API deviceManager_RemoteDeviceUnbindRequest *HSAPI_INIT(deviceManager_RemoteDeviceUnbindRequest);

typedef struct deviceManager_RemoteDeviceUnbindResponse 
{
	HsviewResponse base;

	struct deviceManager_RemoteDeviceUnbindResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceManager_RemoteDeviceUnbindResponse;

C_API deviceManager_RemoteDeviceUnbindResponse *HSAPI_INIT(deviceManager_RemoteDeviceUnbindResponse);

#endif
