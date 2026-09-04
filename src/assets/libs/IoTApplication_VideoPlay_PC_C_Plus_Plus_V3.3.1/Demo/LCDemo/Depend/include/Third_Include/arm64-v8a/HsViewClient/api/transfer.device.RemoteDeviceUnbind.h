/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_RemoteDeviceUnbind_H_
#define _HSVIEW_CLIENT_API_transferDevice_RemoteDeviceUnbind_H_

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

typedef struct transferDevice_RemoteDeviceUnbindRequest 
{
	HsviewRequest base;

	struct transferDevice_RemoteDeviceUnbindRequestData
	{
		
		/** [cstr]/device/access/device/unbind */
		#define _STATIC_transferDevice_RemoteDeviceUnbindRequestData_url "/device/access/device/unbind"
		CSTR url;
		/** struct of transferDevice_RemoteDeviceUnbindRequestData_Content */
		struct transferDevice_RemoteDeviceUnbindRequestData_Content {
			/** [int] 公有云设备通道号，如NVR或者HUB设备通道号 */
			int channelId;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_RemoteDeviceUnbindRequest;

C_API transferDevice_RemoteDeviceUnbindRequest *HSAPI_INIT(transferDevice_RemoteDeviceUnbindRequest);

typedef struct transferDevice_RemoteDeviceUnbindResponse 
{
	HsviewResponse base;

	struct transferDevice_RemoteDeviceUnbindResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_RemoteDeviceUnbindResponse;

C_API transferDevice_RemoteDeviceUnbindResponse *HSAPI_INIT(transferDevice_RemoteDeviceUnbindResponse);

#endif
