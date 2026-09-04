/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_BatchModifyLivePlan_H_
#define _LC_OPENAPI_CLIENT_BatchModifyLivePlan_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
批量修改直播计划时间
 */

typedef struct BatchModifyLivePlanRequest 
{
	LCOpenApiRequest base;

	struct BatchModifyLivePlanRequestData
	{
		
		/**  */
		CSTR liveToken;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** define a list with struct of BatchModifyLivePlanRequestData_RulesElement */
		DECLARE_LIST(struct BatchModifyLivePlanRequestData_RulesElement
		{
			/** 结束时间 */
			CSTR endTime;
			/** 开始时间 */
			CSTR beginTime;
			/** 重复周期monday,tuesday,wednesday,thursday,friday,saturday,sunday */
			CSTR period;
		}) rules;

	} data;

} BatchModifyLivePlanRequest;

C_API BatchModifyLivePlanRequest *LCOPENAPI_INIT(BatchModifyLivePlanRequest);

typedef struct BatchModifyLivePlanResponse 
{
	LCOpenApiResponse base;

	struct BatchModifyLivePlanResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} BatchModifyLivePlanResponse;

C_API BatchModifyLivePlanResponse *LCOPENAPI_INIT(BatchModifyLivePlanResponse);

#endif
