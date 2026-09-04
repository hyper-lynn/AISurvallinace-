/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ForceBindDevice_H_
#define _HSVIEW_CLIENT_API_ForceBindDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

deviceId是需要绑定的设备ID。
deviceRegCode是该设备的注册码，其定义详见华视微讯设备协议的设备注册。

该接口允许用户在这台设备已绑定的情况下重新绑定，但必须提供该设备的注册码。
只有注册码正确，才允许重新绑定。
	
【需要使用平台账号签名】

 */

typedef struct ForceBindDeviceRequest 
{
	HsviewRequest base;

	struct ForceBindDeviceRequestData
	{
		
		/** 设备注册码 */
		CSTR deviceRegCode;
		/** 设备ID */
		CSTR deviceId;

	} data;

} ForceBindDeviceRequest;

C_API ForceBindDeviceRequest *HSAPI_INIT(ForceBindDeviceRequest);

typedef struct ForceBindDeviceResponse 
{
	HsviewResponse base;

	struct ForceBindDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ForceBindDeviceResponse;

C_API ForceBindDeviceResponse *HSAPI_INIT(ForceBindDeviceResponse);

#endif
