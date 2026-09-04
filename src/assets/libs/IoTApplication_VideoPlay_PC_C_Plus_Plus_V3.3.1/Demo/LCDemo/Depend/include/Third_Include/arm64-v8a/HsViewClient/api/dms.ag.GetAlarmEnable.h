/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAlarmEnable_H_
#define _HSVIEW_CLIENT_API_GetAlarmEnable_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取声光报警的使能
 */

typedef struct GetAlarmEnableRequest 
{
	HsviewRequest base;

	struct GetAlarmEnableRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_GetAlarmEnableRequestData_METHOD "POST"
		/** [cstr]agcmd */
		#define _STATIC_GetAlarmEnableRequestData_CMD "agcmd"
		/** struct of GetAlarmEnableRequestData_Body */
		struct GetAlarmEnableRequestData_Body {
			/** [cstr]get-alarm-enable */
			#define _STATIC_GetAlarmEnableRequestData_Body_Action "get-alarm-enable"
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetAlarmEnableRequest;

C_API GetAlarmEnableRequest *HSAPI_INIT(GetAlarmEnableRequest);

typedef struct GetAlarmEnableResponse 
{
	HsviewResponse base;

	struct GetAlarmEnableResponseData
	{
		
		/** [bool]声光报警使能  true /false */
		BOOL Enable;
		/** [int]返回错误码。成功为0，1- 配件不存在；2-其他错误 */
		int Code;
 
	} data;

} GetAlarmEnableResponse;

C_API GetAlarmEnableResponse *HSAPI_INIT(GetAlarmEnableResponse);

#endif
