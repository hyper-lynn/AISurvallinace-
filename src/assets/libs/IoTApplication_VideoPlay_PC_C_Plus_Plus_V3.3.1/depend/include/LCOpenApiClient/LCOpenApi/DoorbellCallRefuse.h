/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DoorbellCallRefuse_H_
#define _LC_OPENAPI_CLIENT_DoorbellCallRefuse_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
拒接门铃呼叫
 */

typedef struct DoorbellCallRefuseRequest 
{
	LCOpenApiRequest base;

	struct DoorbellCallRefuseRequestData
	{
		
		/** 授权的token */
		CSTR token;
		/** 门铃设备序列号 */
		CSTR deviceId ;

	} data;

} DoorbellCallRefuseRequest;

C_API DoorbellCallRefuseRequest *LCOPENAPI_INIT(DoorbellCallRefuseRequest);

typedef struct DoorbellCallRefuseResponse 
{
	LCOpenApiResponse base;

	struct DoorbellCallRefuseResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DoorbellCallRefuseResponse;

C_API DoorbellCallRefuseResponse *LCOPENAPI_INIT(DoorbellCallRefuseResponse);

#endif
