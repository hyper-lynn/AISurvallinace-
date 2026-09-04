/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAlarmGateEnable_H_
#define _HSVIEW_CLIENT_API_GetAlarmGateEnable_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取网关的报警的开关
 */

typedef struct GetAlarmGateEnableRequest 
{
	HsviewRequest base;

	struct GetAlarmGateEnableRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_GetAlarmGateEnableRequestData_METHOD "POST"
		/** [cstr]agcmd */
		#define _STATIC_GetAlarmGateEnableRequestData_CMD "agcmd"
		/** struct of GetAlarmGateEnableRequestData_Body */
		struct GetAlarmGateEnableRequestData_Body {
			/** [cstr]get-alarm-gate-enable */
			#define _STATIC_GetAlarmGateEnableRequestData_Body_Action "get-alarm-gate-enable"
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetAlarmGateEnableRequest;

C_API GetAlarmGateEnableRequest *HSAPI_INIT(GetAlarmGateEnableRequest);

typedef struct GetAlarmGateEnableResponse 
{
	HsviewResponse base;

	struct GetAlarmGateEnableResponseData
	{
		
		/** [bool]网关的报警开关  true /false */
		BOOL Enable;
		/** [int]返回错误码。成功为0 */
		int Code;
 
	} data;

} GetAlarmGateEnableResponse;

C_API GetAlarmGateEnableResponse *HSAPI_INIT(GetAlarmGateEnableResponse);

#endif
