/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_VerifyPasswordInner_H_
#define _LC_OPENAPI_CLIENT_VerifyPasswordInner_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
验证设备密码

 */

typedef struct VerifyPasswordInnerRequest 
{
	LCOpenApiRequest base;

	struct VerifyPasswordInnerRequestData
	{
		
		/** 设备密码 */
		CSTR password;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} VerifyPasswordInnerRequest;

C_API VerifyPasswordInnerRequest *LCOPENAPI_INIT(VerifyPasswordInnerRequest);

typedef struct VerifyPasswordInnerResponse 
{
	LCOpenApiResponse base;

	struct VerifyPasswordInnerResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} VerifyPasswordInnerResponse;

C_API VerifyPasswordInnerResponse *LCOPENAPI_INIT(VerifyPasswordInnerResponse);

#endif
