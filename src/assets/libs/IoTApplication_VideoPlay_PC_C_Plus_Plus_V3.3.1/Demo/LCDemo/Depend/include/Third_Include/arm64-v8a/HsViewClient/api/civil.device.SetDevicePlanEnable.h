/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetDevicePlanEnable_H_
#define _HSVIEW_CLIENT_API_SetDevicePlanEnable_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
通过客户端添加（绑定）设备后，通用设备需要进行动检使能计划的下发。

【需要使用平台账号签名】
 */

typedef struct SetDevicePlanEnableRequest 
{
	HsviewRequest base;

	struct SetDevicePlanEnableRequestData
	{
		
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetDevicePlanEnableRequest;

C_API SetDevicePlanEnableRequest *HSAPI_INIT(SetDevicePlanEnableRequest);

typedef struct SetDevicePlanEnableResponse 
{
	HsviewResponse base;

	struct SetDevicePlanEnableResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetDevicePlanEnableResponse;

C_API SetDevicePlanEnableResponse *HSAPI_INIT(SetDevicePlanEnableResponse);

#endif
