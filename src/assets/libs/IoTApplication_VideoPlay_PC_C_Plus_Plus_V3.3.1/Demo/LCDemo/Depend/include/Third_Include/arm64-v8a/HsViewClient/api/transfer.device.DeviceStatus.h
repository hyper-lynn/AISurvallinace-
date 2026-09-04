/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_DeviceStatus_H_
#define _HSVIEW_CLIENT_API_transferDevice_DeviceStatus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
前端串口板在线状态查询


------------请求参数说明------------
deviceId:设备序列号
-----------------------------------

参考PaaS协议：[前端串口板在线状态查询](http://paas.dahuatech.com/wiki/?p=%2F%E5%AE%9A%E5%88%B6%E5%AE%A2%E6%88%B7%2F%E5%85%A8%E7%90%83%E5%AE%89%E9%80%8F%E4%BC%A0%E5%8D%8F%E8%AE%AE%2F%E5%89%8D%E7%AB%AF%E4%B8%B2%E5%8F%A3%E6%9D%BF%E5%9C%A8%E7%BA%BF%E7%8A%B6%E6%80%81%E6%9F%A5%E8%AF%A2.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_DeviceStatusRequest 
{
	HsviewRequest base;

	struct transferDevice_DeviceStatusRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/serialBoard/query */
		#define _STATIC_transferDevice_DeviceStatusRequestData_url "/device/serialBoard/query"
		CSTR url;

	} data;

} transferDevice_DeviceStatusRequest;

C_API transferDevice_DeviceStatusRequest *HSAPI_INIT(transferDevice_DeviceStatusRequest);

typedef struct transferDevice_DeviceStatusResponse 
{
	HsviewResponse base;

	struct transferDevice_DeviceStatusResponseData
	{
		
		/** online:在线,offline:离线 */
		CSTR status;
 
	} data;

} transferDevice_DeviceStatusResponse;

C_API transferDevice_DeviceStatusResponse *HSAPI_INIT(transferDevice_DeviceStatusResponse);

#endif
