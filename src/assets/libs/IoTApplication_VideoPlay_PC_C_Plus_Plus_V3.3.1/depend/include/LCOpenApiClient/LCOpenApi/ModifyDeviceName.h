/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227741, Author: 251672, Date: 2024-11-25 19:29:19 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ModifyDeviceName_H_
#define _LC_OPENAPI_CLIENT_ModifyDeviceName_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
修改设备/通道名称

 */

typedef struct ModifyDeviceNameRequest 
{
	LCOpenApiRequest base;

	struct ModifyDeviceNameRequestData
	{
		
		/** 待设置的名称 */
		CSTR name;
		/** [bool]是否透传设备，false不透传 */
		BOOL setToDevice;
		/** 通道ID，留空表示设置设备 */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} ModifyDeviceNameRequest;

C_API ModifyDeviceNameRequest *LCOPENAPI_INIT(ModifyDeviceNameRequest);

typedef struct ModifyDeviceNameResponse 
{
	LCOpenApiResponse base;

	struct ModifyDeviceNameResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyDeviceNameResponse;

C_API ModifyDeviceNameResponse *LCOPENAPI_INIT(ModifyDeviceNameResponse);

#endif
