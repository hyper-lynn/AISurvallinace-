/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 221783, Author: 21818, Date: 2021-11-22 15:39:41 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_AccessToken_H_
#define _LC_OPENAPI_CLIENT_AccessToken_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
如果缓存中已经有该accessToken了，那么直接返回
Openweb中重置appsecret了，需要清除缓存 
错误码：
	10001：手机号码无效（非此应用appId的开发者账号）
 */

typedef struct AccessTokenRequest 
{
	LCOpenApiRequest base;

	struct AccessTokenRequestData
	{
		
		/** 用户手机号码,例18888888888 */
		CSTR phone;

	} data;

} AccessTokenRequest;

C_API AccessTokenRequest *LCOPENAPI_INIT(AccessTokenRequest);

typedef struct AccessTokenResponse 
{
	LCOpenApiResponse base;

	struct AccessTokenResponseData
	{
		
		/** 管理员账号accessToken */
		CSTR accessToken;
		/** [long]管理员账号accessToken过期时间，单位秒 */
		int64 expireTime;
 
	} data;

} AccessTokenResponse;

C_API AccessTokenResponse *LCOPENAPI_INIT(AccessTokenResponse);

#endif
