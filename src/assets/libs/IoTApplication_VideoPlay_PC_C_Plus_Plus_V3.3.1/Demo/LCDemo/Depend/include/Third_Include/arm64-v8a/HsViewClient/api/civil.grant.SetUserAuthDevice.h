/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetUserAuthDevice_H_
#define _HSVIEW_CLIENT_API_SetUserAuthDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   设置授权设备
【需要使用平台账号签名】

 */

typedef struct SetUserAuthDeviceRequest 
{
	HsviewRequest base;

	struct SetUserAuthDeviceRequestData
	{
		
		/** [long]授权Id */
		int64 authId;
		/** define a list with struct of SetUserAuthDeviceRequestData_AuthDevicesElement */
		DECLARE_LIST(struct SetUserAuthDeviceRequestData_AuthDevicesElement
		{
			/** 设备序列号 */
			CSTR deviceCode;
			/** 通道号 */
			CSTR channelId;
		}) authDevices;

	} data;

} SetUserAuthDeviceRequest;

C_API SetUserAuthDeviceRequest *HSAPI_INIT(SetUserAuthDeviceRequest);

typedef struct SetUserAuthDeviceResponse 
{
	HsviewResponse base;

	struct SetUserAuthDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetUserAuthDeviceResponse;

C_API SetUserAuthDeviceResponse *HSAPI_INIT(SetUserAuthDeviceResponse);

#endif
