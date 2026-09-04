/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetAlarmStatus_H_
#define _HSVIEW_CLIENT_API_SetAlarmStatus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置当前的报警状态
 */

typedef struct SetAlarmStatusRequest 
{
	HsviewRequest base;

	struct SetAlarmStatusRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetAlarmStatusRequestData_METHOD "POST"
		/** [cstr]agcmd */
		#define _STATIC_SetAlarmStatusRequestData_CMD "agcmd"
		/** struct of SetAlarmStatusRequestData_Body */
		struct SetAlarmStatusRequestData_Body {
			/** [cstr]set-alarm-status */
			#define _STATIC_SetAlarmStatusRequestData_Body_Action "set-alarm-status"
			/** 当前报警状态  on-开  off-关 */
			CSTR Status;
		} body;

	} data;

} SetAlarmStatusRequest;

C_API SetAlarmStatusRequest *HSAPI_INIT(SetAlarmStatusRequest);

typedef struct SetAlarmStatusResponse 
{
	HsviewResponse base;

	struct SetAlarmStatusResponseData
	{
		
		/** [int]返回错误码。成功为0，1- 配件不存在；2-其他错误 */
		int Code;
 
	} data;

} SetAlarmStatusResponse;

C_API SetAlarmStatusResponse *HSAPI_INIT(SetAlarmStatusResponse);

#endif
