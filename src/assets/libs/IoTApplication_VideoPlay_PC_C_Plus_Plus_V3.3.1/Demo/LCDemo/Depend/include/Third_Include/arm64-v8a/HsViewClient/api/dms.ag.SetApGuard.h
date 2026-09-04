/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetApGuard_H_
#define _HSVIEW_CLIENT_API_SetApGuard_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置配件的布防
 */

typedef struct SetApGuardRequest 
{
	HsviewRequest base;

	struct SetApGuardRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetApGuardRequestData_METHOD "POST"
		/** [cstr]agcmd */
		#define _STATIC_SetApGuardRequestData_CMD "agcmd"
		/** struct of SetApGuardRequestData_Body */
		struct SetApGuardRequestData_Body {
			/** 配件的id */
			CSTR ID;
			/** [cstr]set-guard */
			#define _STATIC_SetApGuardRequestData_Body_Action "set-guard"
			/** [bool]使能类型 */
			BOOL Enable;
		} body;

	} data;

} SetApGuardRequest;

C_API SetApGuardRequest *HSAPI_INIT(SetApGuardRequest);

typedef struct SetApGuardResponse 
{
	HsviewResponse base;

	struct SetApGuardResponseData
	{
		
		/** [int]返回错误码。成功为0，1- 配件不存在；2-其他错误 */
		int Code;
 
	} data;

} SetApGuardResponse;

C_API SetApGuardResponse *HSAPI_INIT(SetApGuardResponse);

#endif
