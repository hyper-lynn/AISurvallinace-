/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_RestartDevice_H_
#define _HSVIEW_CLIENT_API_thingsControl_RestartDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
重启设备。

注意：此接口只支持设备级的重启

参考PaaS协议：[重启设备](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E9%87%8D%E5%90%AF%E8%AE%BE%E5%A4%87.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_RestartDeviceRequest 
{
	HsviewRequest base;

	struct thingsControl_RestartDeviceRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsControl_RestartDeviceRequest;

C_API thingsControl_RestartDeviceRequest *HSAPI_INIT(thingsControl_RestartDeviceRequest);

typedef struct thingsControl_RestartDeviceResponse 
{
	HsviewResponse base;

	struct thingsControl_RestartDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsControl_RestartDeviceResponse;

C_API thingsControl_RestartDeviceResponse *HSAPI_INIT(thingsControl_RestartDeviceResponse);

#endif
