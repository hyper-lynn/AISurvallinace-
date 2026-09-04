/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UserBind_H_
#define _LC_OPENAPI_CLIENT_UserBind_H_

#include "LCOpenApi_ClientSdk.h"

/** DESCRIPTION: 
错误码：
	10003：开发模式下,此接口一天只能调5�?
	其他的一些CIVIL返回的错误码的封�?
 */
namespace LCOpenApi{
typedef struct UserBindRequest 
{
	LCOpenApi_LCOpenApiRequest base;

	struct UserBindRequestData
	{
		
		/** 18888888888//用户手机号码 */
		CSTR phone;
		/** 1234验证�?*/
		CSTR smsCode;

	} data;

} UserBindRequest;

UserBindRequest *LCOpenApi_LCOPENAPI_INIT(UserBindRequest);

typedef struct UserBindResponse 
{
	LCOpenApi_LCOpenApiResponse base;

	struct UserBindResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UserBindResponse;

UserBindResponse *LCOpenApi_LCOPENAPI_INIT(UserBindResponse);

}
#endif
