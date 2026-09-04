/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteAPDevice_H_
#define _HSVIEW_CLIENT_API_DeleteAPDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除配件。
【需要使用平台账号签名】
 */

typedef struct DeleteAPDeviceRequest 
{
	HsviewRequest base;

	struct DeleteAPDeviceRequestData
	{
		
		/** [O]配件ID,该字段为空或不存在，则代表清空所有配件 */
		CSTR apId;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} DeleteAPDeviceRequest;

C_API DeleteAPDeviceRequest *HSAPI_INIT(DeleteAPDeviceRequest);

typedef struct DeleteAPDeviceResponse 
{
	HsviewResponse base;

	struct DeleteAPDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteAPDeviceResponse;

C_API DeleteAPDeviceResponse *HSAPI_INIT(DeleteAPDeviceResponse);

#endif
