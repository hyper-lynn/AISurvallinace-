/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetAlarmEnable_H_
#define _HSVIEW_CLIENT_API_SetAlarmEnable_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置当前的声光报警使能
 */

typedef struct SetAlarmEnableRequest 
{
	HsviewRequest base;

	struct SetAlarmEnableRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetAlarmEnableRequestData_METHOD "POST"
		/** [cstr]agcmd */
		#define _STATIC_SetAlarmEnableRequestData_CMD "agcmd"
		/** struct of SetAlarmEnableRequestData_Body */
		struct SetAlarmEnableRequestData_Body {
			/** [cstr]set-alarm-enable */
			#define _STATIC_SetAlarmEnableRequestData_Body_Action "set-alarm-enable"
			/** [bool]声光报警使能  true /false */
			BOOL Enable;
		} body;

	} data;

} SetAlarmEnableRequest;

C_API SetAlarmEnableRequest *HSAPI_INIT(SetAlarmEnableRequest);

typedef struct SetAlarmEnableResponse 
{
	HsviewResponse base;

	struct SetAlarmEnableResponseData
	{
		
		/** [int]返回错误码。成功为0，1- 配件不存在；2-其他错误 */
		int Code;
 
	} data;

} SetAlarmEnableResponse;

C_API SetAlarmEnableResponse *HSAPI_INIT(SetAlarmEnableResponse);

#endif
