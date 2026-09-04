/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
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
		
		/** [cstr]modifyDeviceName */
		#define _STATIC_ModifyDeviceNameRequestData_method "modifyDeviceName"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 通道ID，留空表示设置设备 */
		CSTR channelId;
		/** 待设置的名称 */
		CSTR name;
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
