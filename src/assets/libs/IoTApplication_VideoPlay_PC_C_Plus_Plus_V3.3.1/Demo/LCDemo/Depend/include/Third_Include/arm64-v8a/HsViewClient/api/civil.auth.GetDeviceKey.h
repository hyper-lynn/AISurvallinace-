/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetDeviceKey_H_
#define _HSVIEW_CLIENT_API_GetDeviceKey_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备Key（对应的Secret）。
注意：该接口只能被乐橙业务系统访问；第三方业务系统访问时返回403 Forbidden。
 */

typedef struct GetDeviceKeyRequest 
{
	HsviewRequest base;

	struct GetDeviceKeyRequestData
	{
		
		/** 设备KEY */
		CSTR key;

	} data;

} GetDeviceKeyRequest;

C_API GetDeviceKeyRequest *HSAPI_INIT(GetDeviceKeyRequest);

typedef struct GetDeviceKeyResponse 
{
	HsviewResponse base;

	struct GetDeviceKeyResponseData
	{
		
		/** 设备secret */
		CSTR secret;
 
	} data;

} GetDeviceKeyResponse;

C_API GetDeviceKeyResponse *HSAPI_INIT(GetDeviceKeyResponse);

#endif
