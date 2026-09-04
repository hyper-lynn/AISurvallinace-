/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ModifyLivePlan_H_
#define _LC_OPENAPI_CLIENT_ModifyLivePlan_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
修改直播计划时间
 */

typedef struct ModifyLivePlanRequest 
{
	LCOpenApiRequest base;

	struct ModifyLivePlanRequestData
	{
		
		/**  */
		CSTR liveToken;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 结束时间 */
		CSTR endTime;
		/** 开始时间 */
		CSTR beginTime;
		/** 直播周期,always：永久,once：仅一次,everyday：每天 */
		CSTR period;

	} data;

} ModifyLivePlanRequest;

C_API ModifyLivePlanRequest *LCOPENAPI_INIT(ModifyLivePlanRequest);

typedef struct ModifyLivePlanResponse 
{
	LCOpenApiResponse base;

	struct ModifyLivePlanResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyLivePlanResponse;

C_API ModifyLivePlanResponse *LCOPENAPI_INIT(ModifyLivePlanResponse);

#endif
