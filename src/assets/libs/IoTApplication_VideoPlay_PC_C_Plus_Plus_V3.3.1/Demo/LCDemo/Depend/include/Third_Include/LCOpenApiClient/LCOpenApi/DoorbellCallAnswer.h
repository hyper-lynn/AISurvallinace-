/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DoorbellCallAnswer_H_
#define _LC_OPENAPI_CLIENT_DoorbellCallAnswer_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
接听门铃呼叫
 */

typedef struct DoorbellCallAnswerRequest 
{
	LCOpenApiRequest base;

	struct DoorbellCallAnswerRequestData
	{
		
		/** 授权的token */
		CSTR token;
		/** 门铃设备序列号 */
		CSTR deviceId ;

	} data;

} DoorbellCallAnswerRequest;

C_API DoorbellCallAnswerRequest *LCOPENAPI_INIT(DoorbellCallAnswerRequest);

typedef struct DoorbellCallAnswerResponse 
{
	LCOpenApiResponse base;

	struct DoorbellCallAnswerResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DoorbellCallAnswerResponse;

C_API DoorbellCallAnswerResponse *LCOPENAPI_INIT(DoorbellCallAnswerResponse);

#endif
