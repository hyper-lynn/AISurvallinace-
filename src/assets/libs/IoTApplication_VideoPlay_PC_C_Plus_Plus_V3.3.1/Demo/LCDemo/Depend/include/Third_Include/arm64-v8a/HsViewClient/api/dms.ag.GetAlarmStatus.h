/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAlarmStatus_H_
#define _HSVIEW_CLIENT_API_GetAlarmStatus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取当前的报警状态
 */

typedef struct GetAlarmStatusRequest 
{
	HsviewRequest base;

	struct GetAlarmStatusRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_GetAlarmStatusRequestData_METHOD "POST"
		/** [cstr]agcmd */
		#define _STATIC_GetAlarmStatusRequestData_CMD "agcmd"
		/** struct of GetAlarmStatusRequestData_Body */
		struct GetAlarmStatusRequestData_Body {
			/** [cstr]get-alarm-status */
			#define _STATIC_GetAlarmStatusRequestData_Body_Action "get-alarm-status"
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetAlarmStatusRequest;

C_API GetAlarmStatusRequest *HSAPI_INIT(GetAlarmStatusRequest);

typedef struct GetAlarmStatusResponse 
{
	HsviewResponse base;

	struct GetAlarmStatusResponseData
	{
		
		/** 当前报警状态  on-开  off-关 */
		CSTR Status;
		/** [int]返回错误码。成功为0，1- 配件不存在；2-其他错误 */
		int Code;
 
	} data;

} GetAlarmStatusResponse;

C_API GetAlarmStatusResponse *HSAPI_INIT(GetAlarmStatusResponse);

#endif
