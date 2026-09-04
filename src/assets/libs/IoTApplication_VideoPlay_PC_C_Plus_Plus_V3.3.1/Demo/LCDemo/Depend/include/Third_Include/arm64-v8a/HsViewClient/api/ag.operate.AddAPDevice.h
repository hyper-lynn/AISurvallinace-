/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_agOperate_AddAPDevice_H_
#define _HSVIEW_CLIENT_API_agOperate_AddAPDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
添加配件。
【需要使用平台账号签名】
 */

typedef struct agOperate_AddAPDeviceRequest 
{
	HsviewRequest base;

	struct agOperate_AddAPDeviceRequestData
	{
		
		/** [O]配件型号 */
		CSTR apModel;
		/** 配件ID */
		CSTR apId;
		/** 配件类型 */
		CSTR apType;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} agOperate_AddAPDeviceRequest;

C_API agOperate_AddAPDeviceRequest *HSAPI_INIT(agOperate_AddAPDeviceRequest);

typedef struct agOperate_AddAPDeviceResponse 
{
	HsviewResponse base;

	struct agOperate_AddAPDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} agOperate_AddAPDeviceResponse;

C_API agOperate_AddAPDeviceResponse *HSAPI_INIT(agOperate_AddAPDeviceResponse);

#endif
