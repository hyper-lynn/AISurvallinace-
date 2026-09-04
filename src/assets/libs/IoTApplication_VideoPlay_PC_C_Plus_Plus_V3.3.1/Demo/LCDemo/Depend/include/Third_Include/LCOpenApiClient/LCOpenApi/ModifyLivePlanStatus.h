/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ModifyLivePlanStatus_H_
#define _LC_OPENAPI_CLIENT_ModifyLivePlanStatus_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置直播计划开关
 */

typedef struct ModifyLivePlanStatusRequest 
{
	LCOpenApiRequest base;

	struct ModifyLivePlanStatusRequestData
	{
		
		/** 状态（on:开；off:关） */
		CSTR status;
		/**  */
		CSTR liveToken;
		/** 授权的管理员token(accessToken) */
		CSTR token;

	} data;

} ModifyLivePlanStatusRequest;

C_API ModifyLivePlanStatusRequest *LCOPENAPI_INIT(ModifyLivePlanStatusRequest);

typedef struct ModifyLivePlanStatusResponse 
{
	LCOpenApiResponse base;

	struct ModifyLivePlanStatusResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyLivePlanStatusResponse;

C_API ModifyLivePlanStatusResponse *LCOPENAPI_INIT(ModifyLivePlanStatusResponse);

#endif
