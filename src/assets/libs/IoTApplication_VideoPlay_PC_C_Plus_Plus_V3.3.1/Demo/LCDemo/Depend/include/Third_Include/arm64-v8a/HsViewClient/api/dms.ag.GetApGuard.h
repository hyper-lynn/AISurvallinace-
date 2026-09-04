/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetApGuard_H_
#define _HSVIEW_CLIENT_API_GetApGuard_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取配件的布防
 */

typedef struct GetApGuardRequest 
{
	HsviewRequest base;

	struct GetApGuardRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_GetApGuardRequestData_METHOD "POST"
		/** [cstr]agcmd */
		#define _STATIC_GetApGuardRequestData_CMD "agcmd"
		/** struct of GetApGuardRequestData_Body */
		struct GetApGuardRequestData_Body {
			/** [cstr]get-guard */
			#define _STATIC_GetApGuardRequestData_Body_Action "get-guard"
			/** 配件的id */
			CSTR ID;
		} body;

	} data;

} GetApGuardRequest;

C_API GetApGuardRequest *HSAPI_INIT(GetApGuardRequest);

typedef struct GetApGuardResponse 
{
	HsviewResponse base;

	struct GetApGuardResponseData
	{
		
		/** [bool]true:布防，false: 撤防 */
		BOOL Enable;
		/** [int]返回错误码。成功为0，1- 配件不存在；2-其他错误 */
		int Code;
 
	} data;

} GetApGuardResponse;

C_API GetApGuardResponse *HSAPI_INIT(GetApGuardResponse);

#endif
