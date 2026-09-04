/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DoorbellLinkageModify_H_
#define _LC_OPENAPI_CLIENT_DoorbellLinkageModify_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
解除门铃和铃铛的关联关系
 */

typedef struct DoorbellLinkageModifyRequest 
{
	LCOpenApiRequest base;

	struct DoorbellLinkageModifyRequestData
	{
		
		/** 旧的铃铛ID */
		CSTR oldBellId;
		/** 新的铃铛ID */
		CSTR newBellId;
		/** 门铃的ID */
		CSTR doorId;
		/** 授权的token */
		CSTR token;

	} data;

} DoorbellLinkageModifyRequest;

C_API DoorbellLinkageModifyRequest *LCOPENAPI_INIT(DoorbellLinkageModifyRequest);

typedef struct DoorbellLinkageModifyResponse 
{
	LCOpenApiResponse base;

	struct DoorbellLinkageModifyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DoorbellLinkageModifyResponse;

C_API DoorbellLinkageModifyResponse *LCOPENAPI_INIT(DoorbellLinkageModifyResponse);

#endif
