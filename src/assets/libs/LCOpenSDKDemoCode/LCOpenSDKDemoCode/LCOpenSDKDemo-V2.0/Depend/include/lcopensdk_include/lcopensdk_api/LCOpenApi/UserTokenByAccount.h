/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UserTokenByAccount_H_
#define _LC_OPENAPI_CLIENT_UserTokenByAccount_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
根据账号获取用户token
 */

typedef struct UserTokenByAccountRequest 
{
	LCOpenApiRequest base;

	struct UserTokenByAccountRequestData
	{
		
		/** [String][Not Null]国内 手机号 ，国外输入邮箱 */
		CSTR account;

	} data;

} UserTokenByAccountRequest;

C_API UserTokenByAccountRequest *LCOPENAPI_INIT(UserTokenByAccountRequest);

typedef struct UserTokenByAccountResponse 
{
	LCOpenApiResponse base;

	struct UserTokenByAccountResponseData
	{
		
		/** [String]获取的用户Token */
		CSTR userToken;
		/** 剩余过期时间，单位：秒 */
		CSTR expireTime;
 
	} data;

} UserTokenByAccountResponse;

C_API UserTokenByAccountResponse *LCOPENAPI_INIT(UserTokenByAccountResponse);

#endif
