/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ModifyAPDevice_H_
#define _HSVIEW_CLIENT_API_ModifyAPDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改配件名称。
【需要使用平台账号签名】
 */

typedef struct ModifyAPDeviceRequest 
{
	HsviewRequest base;

	struct ModifyAPDeviceRequestData
	{
		
		/** [O]配件ID,该字段为空或不存在，则代表清空所有配件 */
		CSTR apId;
		/** 配件名称 */
		CSTR apName;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} ModifyAPDeviceRequest;

C_API ModifyAPDeviceRequest *HSAPI_INIT(ModifyAPDeviceRequest);

typedef struct ModifyAPDeviceResponse 
{
	HsviewResponse base;

	struct ModifyAPDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyAPDeviceResponse;

C_API ModifyAPDeviceResponse *HSAPI_INIT(ModifyAPDeviceResponse);

#endif
