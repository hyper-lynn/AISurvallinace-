/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DoorbellLinkageDelete_H_
#define _LC_OPENAPI_CLIENT_DoorbellLinkageDelete_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
解除门铃和铃铛的关联关系
 */

typedef struct DoorbellLinkageDeleteRequest 
{
	LCOpenApiRequest base;

	struct DoorbellLinkageDeleteRequestData
	{
		
		/** 铃铛的ID */
		DECLARE_LIST(CSTR) bellIds;
		/** 门铃的ID */
		CSTR doorId;
		/**  授权的token */
		CSTR token;

	} data;

} DoorbellLinkageDeleteRequest;

C_API DoorbellLinkageDeleteRequest *LCOPENAPI_INIT(DoorbellLinkageDeleteRequest);

typedef struct DoorbellLinkageDeleteResponse 
{
	LCOpenApiResponse base;

	struct DoorbellLinkageDeleteResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DoorbellLinkageDeleteResponse;

C_API DoorbellLinkageDeleteResponse *LCOPENAPI_INIT(DoorbellLinkageDeleteResponse);

#endif
