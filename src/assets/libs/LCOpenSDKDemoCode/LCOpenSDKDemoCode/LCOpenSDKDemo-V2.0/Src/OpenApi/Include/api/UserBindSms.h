/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_userBindSms_H_
#define _LC_OPENAPI_CLIENT_userBindSms_H_

#include "LCOpenApi_ClientSdk.h"

/** DESCRIPTION: 
需要遵守短信发送的限制要求.
错误码：
	10003：开发模式下,此接口一天只能调5�?
	以及其他的一些CIVIL返回的错误码的封�?
 */
namespace LCOpenApi{
typedef struct userBindSmsRequest 
{
	LCOpenApi_LCOpenApiRequest base;

	struct userBindSmsRequestData
	{
		
		/** 18888888888//用户手机号码 */
		CSTR phone;

	} data;

} userBindSmsRequest;

userBindSmsRequest *LCOpenApi_LCOPENAPI_INIT(userBindSmsRequest);

typedef struct userBindSmsResponse 
{
	LCOpenApi_LCOpenApiResponse base;

	struct userBindSmsResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userBindSmsResponse;

userBindSmsResponse *LCOpenApi_LCOPENAPI_INIT(userBindSmsResponse);

}
#endif
