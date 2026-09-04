/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 224629, Author: 233705, Date: 2023-06-27 14:32:39 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DoorbellsTestRing_H_
#define _LC_OPENAPI_CLIENT_DoorbellsTestRing_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
试听铃声
 */

typedef struct DoorbellsTestRingRequest 
{
	LCOpenApiRequest base;

	struct DoorbellsTestRingRequestData
	{
		
		/** [int]响铃次数 */
		int ringTimes;
		/** 试听的铃铛ID */
		DECLARE_LIST(CSTR) bellIds;
		/** 授权的token */
		CSTR token;
		/** 试听的铃声索引号 */
		CSTR index;

	} data;

} DoorbellsTestRingRequest;

C_API DoorbellsTestRingRequest *LCOPENAPI_INIT(DoorbellsTestRingRequest);

typedef struct DoorbellsTestRingResponse 
{
	LCOpenApiResponse base;

	struct DoorbellsTestRingResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DoorbellsTestRingResponse;

C_API DoorbellsTestRingResponse *LCOPENAPI_INIT(DoorbellsTestRingResponse);

#endif
