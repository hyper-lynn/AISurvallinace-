/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_VerifyPassword_H_
#define _LC_OPENAPI_CLIENT_VerifyPassword_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
验证设备密码

 */

typedef struct VerifyPasswordRequest 
{
	LCOpenApiRequest base;

	struct VerifyPasswordRequestData
	{
		
		/** [String]用户名 */
		CSTR username;
		/** 设备密码加密后的字符串 */
		CSTR password;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} VerifyPasswordRequest;

C_API VerifyPasswordRequest *LCOPENAPI_INIT(VerifyPasswordRequest);

typedef struct VerifyPasswordResponse 
{
	LCOpenApiResponse base;

	struct VerifyPasswordResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} VerifyPasswordResponse;

C_API VerifyPasswordResponse *LCOPENAPI_INIT(VerifyPasswordResponse);

#endif
