/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UserBindNoVerify_H_
#define _LC_OPENAPI_CLIENT_UserBindNoVerify_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
账号绑定无验证码
 */

typedef struct UserBindNoVerifyRequest 
{
	LCOpenApiRequest base;

	struct UserBindNoVerifyRequestData
	{
		
		/** [String][Not Null]国内手机号 ，国外输入邮箱 */
		CSTR account;

	} data;

} UserBindNoVerifyRequest;

C_API UserBindNoVerifyRequest *LCOPENAPI_INIT(UserBindNoVerifyRequest);

typedef struct UserBindNoVerifyResponse 
{
	LCOpenApiResponse base;

	struct UserBindNoVerifyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UserBindNoVerifyResponse;

C_API UserBindNoVerifyResponse *LCOPENAPI_INIT(UserBindNoVerifyResponse);

#endif
