/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UserBindNoVerify_H_
#define _LC_OPENAPI_CLIENT_UserBindNoVerify_H_

#include "LCOpenApi_ClientSdk.h"

/** DESCRIPTION: 
账号绑定无验证码
 */

namespace LCOpenApi{
typedef struct UserBindNoVerifyRequest 
{
	LCOpenApi_LCOpenApiRequest base;

	struct UserBindNoVerifyRequestData
	{
		
		/** [String][Not Null]国内手机号 ，国外输入邮箱 */
		CSTR account;

	} data;

} UserBindNoVerifyRequest;

UserBindNoVerifyRequest *LCOpenApi_LCOPENAPI_INIT(UserBindNoVerifyRequest);

typedef struct UserBindNoVerifyResponse 
{
	LCOpenApi_LCOpenApiResponse base;

	struct UserBindNoVerifyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UserBindNoVerifyResponse;

UserBindNoVerifyResponse *LCOpenApi_LCOPENAPI_INIT(UserBindNoVerifyResponse);

}
#endif
