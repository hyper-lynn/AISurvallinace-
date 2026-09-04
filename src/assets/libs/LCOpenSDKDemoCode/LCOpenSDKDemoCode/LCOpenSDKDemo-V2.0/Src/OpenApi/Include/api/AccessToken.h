
 
#ifndef _LCOPENAPI_AccessToken_H_
#define _LCOPENAPI_AccessToken_H_

#include "LCOpenApi_ClientSdk.h"

/** DESCRIPTION: 
如果缓存中已经有该accessToken了，那么直接返回
Openweb中重置appsecret了，需要清除缓�?
错误码：
	10001：手机号码无效（非此应用appId的开发者账号）
 */
namespace LCOpenApi{
typedef struct AccessTokenRequest 
{
	LCOpenApi_LCOpenApiRequest base;

	struct AccessTokenRequestData
	{
		
        /** [int][O]���� */
        int _nouse;

	} data;

} AccessTokenRequest;

AccessTokenRequest *LCOpenApi_LCOPENAPI_INIT(AccessTokenRequest);

typedef struct AccessTokenResponse 
{
	LCOpenApi_LCOpenApiResponse base;

	struct AccessTokenResponseData
	{
		
		/** ********* */
		CSTR accessToken;
 
	} data;

} AccessTokenResponse;

AccessTokenResponse *LCOpenApi_LCOPENAPI_INIT(AccessTokenResponse);

}
#endif
