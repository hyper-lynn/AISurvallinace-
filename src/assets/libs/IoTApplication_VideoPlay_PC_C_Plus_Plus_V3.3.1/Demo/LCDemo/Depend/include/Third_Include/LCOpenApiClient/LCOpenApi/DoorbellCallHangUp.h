/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DoorbellCallHangUp_H_
#define _LC_OPENAPI_CLIENT_DoorbellCallHangUp_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
挂断门铃呼叫
 */

typedef struct DoorbellCallHangUpRequest 
{
	LCOpenApiRequest base;

	struct DoorbellCallHangUpRequestData
	{
		
		/** 授权的token */
		CSTR token;
		/** 门铃设备序列号 */
		CSTR deviceId ;

	} data;

} DoorbellCallHangUpRequest;

C_API DoorbellCallHangUpRequest *LCOPENAPI_INIT(DoorbellCallHangUpRequest);

typedef struct DoorbellCallHangUpResponse 
{
	LCOpenApiResponse base;

	struct DoorbellCallHangUpResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DoorbellCallHangUpResponse;

C_API DoorbellCallHangUpResponse *LCOPENAPI_INIT(DoorbellCallHangUpResponse);

#endif
