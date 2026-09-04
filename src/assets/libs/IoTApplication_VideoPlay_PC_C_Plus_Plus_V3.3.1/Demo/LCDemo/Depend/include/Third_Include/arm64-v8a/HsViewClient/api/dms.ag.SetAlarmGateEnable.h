/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetAlarmGateEnable_H_
#define _HSVIEW_CLIENT_API_SetAlarmGateEnable_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置网关的报警开关
 */

typedef struct SetAlarmGateEnableRequest 
{
	HsviewRequest base;

	struct SetAlarmGateEnableRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetAlarmGateEnableRequestData_METHOD "POST"
		/** [cstr]agcmd */
		#define _STATIC_SetAlarmGateEnableRequestData_CMD "agcmd"
		/** struct of SetAlarmGateEnableRequestData_Body */
		struct SetAlarmGateEnableRequestData_Body {
			/** [cstr]set-alarm-gate-enable */
			#define _STATIC_SetAlarmGateEnableRequestData_Body_Action "set-alarm-gate-enable"
			/** [bool]网关总体的报警开关  true /false */
			BOOL Enable;
		} body;

	} data;

} SetAlarmGateEnableRequest;

C_API SetAlarmGateEnableRequest *HSAPI_INIT(SetAlarmGateEnableRequest);

typedef struct SetAlarmGateEnableResponse 
{
	HsviewResponse base;

	struct SetAlarmGateEnableResponseData
	{
		
		/** [int]返回错误码。成功为0 */
		int Code;
 
	} data;

} SetAlarmGateEnableResponse;

C_API SetAlarmGateEnableResponse *HSAPI_INIT(SetAlarmGateEnableResponse);

#endif
