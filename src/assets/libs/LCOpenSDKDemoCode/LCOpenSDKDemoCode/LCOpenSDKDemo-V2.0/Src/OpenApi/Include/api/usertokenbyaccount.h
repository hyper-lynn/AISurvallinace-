/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UserTokenByAccount_H_
#define _LC_OPENAPI_CLIENT_UserTokenByAccount_H_

#include "LCOpenApi_ClientSdk.h"

/** DESCRIPTION: 
根据账号获取用户token
 */

namespace LCOpenApi{
typedef struct UserTokenByAccountRequest 
{
	LCOpenApi_LCOpenApiRequest base;

	struct UserTokenByAccountRequestData
	{
		
		/** [String][Not Null]国内 手机号 ，国外输入邮箱 */
		CSTR account;

	} data;

} UserTokenByAccountRequest;

UserTokenByAccountRequest *LCOpenApi_LCOPENAPI_INIT(UserTokenByAccountRequest);

typedef struct UserTokenByAccountResponse 
{
	LCOpenApi_LCOpenApiResponse base;

	struct UserTokenByAccountResponseData
	{
		
		/** [String]获取的用户Token */
		CSTR userToken;
		/** 剩余过期时间，单位：秒 */
		CSTR expireTime;
 
	} data;

} UserTokenByAccountResponse;

UserTokenByAccountResponse *LCOpenApi_LCOPENAPI_INIT(UserTokenByAccountResponse);

}
#endif
