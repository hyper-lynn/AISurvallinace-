/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DoorbellLinkageAdd_H_
#define _LC_OPENAPI_CLIENT_DoorbellLinkageAdd_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
门铃关联铃铛
 */

typedef struct DoorbellLinkageAddRequest 
{
	LCOpenApiRequest base;

	struct DoorbellLinkageAddRequestData
	{
		
		/** 铃铛的ID */
		DECLARE_LIST(CSTR) bellIds;
		/** 门铃的ID */
		CSTR doorId;
		/** 授权的token */
		CSTR token;

	} data;

} DoorbellLinkageAddRequest;

C_API DoorbellLinkageAddRequest *LCOPENAPI_INIT(DoorbellLinkageAddRequest);

typedef struct DoorbellLinkageAddResponse 
{
	LCOpenApiResponse base;

	struct DoorbellLinkageAddResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DoorbellLinkageAddResponse;

C_API DoorbellLinkageAddResponse *LCOPENAPI_INIT(DoorbellLinkageAddResponse);

#endif
