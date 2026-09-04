/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ModifyDeviceName_H_
#define _HSVIEW_CLIENT_API_ModifyDeviceName_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改设备或者通道的名称。通道号由channelId表示。channelId不填代表修改的是设备名称。
【需要使用平台账号签名】
 */

typedef struct ModifyDeviceNameRequest 
{
	HsviewRequest base;

	struct ModifyDeviceNameRequestData
	{
		
		/** 通道号，留空表示设置设备 */
		CSTR channelId;
		/** 要设置的名称 */
		CSTR name;
		/** 设备ID */
		CSTR deviceId;

	} data;

} ModifyDeviceNameRequest;

C_API ModifyDeviceNameRequest *HSAPI_INIT(ModifyDeviceNameRequest);

typedef struct ModifyDeviceNameResponse 
{
	HsviewResponse base;

	struct ModifyDeviceNameResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyDeviceNameResponse;

C_API ModifyDeviceNameResponse *HSAPI_INIT(ModifyDeviceNameResponse);

#endif
