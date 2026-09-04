/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_RestartDevice_H_
#define _HSVIEW_CLIENT_API_transferDevice_RestartDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
收到请求后，设备重启并重新注册

参考PaaS协议：[请求重启设备](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E9%87%8D%E5%90%AF%E8%AE%BE%E5%A4%87.md&s=pd)

权限校验：
1. 国内乐橙，强制校验用户的绑定关系。

【需要使用平台账号签名】
 */

typedef struct transferDevice_RestartDeviceRequest 
{
	HsviewRequest base;

	struct transferDevice_RestartDeviceRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/restart */
		#define _STATIC_transferDevice_RestartDeviceRequestData_url "/device/restart"
		CSTR url;

	} data;

} transferDevice_RestartDeviceRequest;

C_API transferDevice_RestartDeviceRequest *HSAPI_INIT(transferDevice_RestartDeviceRequest);

typedef struct transferDevice_RestartDeviceResponse 
{
	HsviewResponse base;

	struct transferDevice_RestartDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_RestartDeviceResponse;

C_API transferDevice_RestartDeviceResponse *HSAPI_INIT(transferDevice_RestartDeviceResponse);

#endif
