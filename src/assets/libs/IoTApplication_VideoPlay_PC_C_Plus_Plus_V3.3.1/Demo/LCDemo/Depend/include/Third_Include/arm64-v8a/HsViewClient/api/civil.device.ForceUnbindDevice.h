/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ForceUnbindDevice_H_
#define _HSVIEW_CLIENT_API_ForceUnbindDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

deviceId是需要解绑的设备ID。
deviceRegCode是要找回设备的注册码，其定义详见华视微讯设备协议的设备注册。

该接口可以无需认证，但必须填对设备的注册码，才允许解绑设备。

 */

typedef struct ForceUnbindDeviceRequest 
{
	HsviewRequest base;

	struct ForceUnbindDeviceRequestData
	{
		
		/** 设备注册码 */
		CSTR deviceRegCode;
		/** 设备ID */
		CSTR deviceId;

	} data;

} ForceUnbindDeviceRequest;

C_API ForceUnbindDeviceRequest *HSAPI_INIT(ForceUnbindDeviceRequest);

typedef struct ForceUnbindDeviceResponse 
{
	HsviewResponse base;

	struct ForceUnbindDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ForceUnbindDeviceResponse;

C_API ForceUnbindDeviceResponse *HSAPI_INIT(ForceUnbindDeviceResponse);

#endif
