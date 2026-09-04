/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_agOperate_DeleteAPDevice_H_
#define _HSVIEW_CLIENT_API_agOperate_DeleteAPDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除配件。

【需要使用平台账号签名】
 */

typedef struct agOperate_DeleteAPDeviceRequest 
{
	HsviewRequest base;

	struct agOperate_DeleteAPDeviceRequestData
	{
		
		/** [O]配件ID,该字段为空或不存在，则代表清空所有配件 */
		CSTR apId;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} agOperate_DeleteAPDeviceRequest;

C_API agOperate_DeleteAPDeviceRequest *HSAPI_INIT(agOperate_DeleteAPDeviceRequest);

typedef struct agOperate_DeleteAPDeviceResponse 
{
	HsviewResponse base;

	struct agOperate_DeleteAPDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} agOperate_DeleteAPDeviceResponse;

C_API agOperate_DeleteAPDeviceResponse *HSAPI_INIT(agOperate_DeleteAPDeviceResponse);

#endif
