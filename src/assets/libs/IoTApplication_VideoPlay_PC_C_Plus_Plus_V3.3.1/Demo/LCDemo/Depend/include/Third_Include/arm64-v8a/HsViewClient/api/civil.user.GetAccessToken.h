/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAccessToken_H_
#define _HSVIEW_CLIENT_API_GetAccessToken_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取或更新当前账号或者某个子账号的AccessToken。
【使用平台账号签名认证】
 */

typedef struct GetAccessTokenRequest 
{
	HsviewRequest base;

	struct GetAccessTokenRequestData
	{
		
		/** 必须是当前账号或者当前账号下的子账号 */
		CSTR username;
		/** [int] 0表示获取AccessToken，1表示更新AccessToken后获取 */
		int needUpdate;

	} data;

} GetAccessTokenRequest;

C_API GetAccessTokenRequest *HSAPI_INIT(GetAccessTokenRequest);

typedef struct GetAccessTokenResponse 
{
	HsviewResponse base;

	struct GetAccessTokenResponseData
	{
		
		/** 账号的AccessToken */
		CSTR accessToken;
		/** [long]过期时间，单位秒 */
		int64 expires;
 
	} data;

} GetAccessTokenResponse;

C_API GetAccessTokenResponse *HSAPI_INIT(GetAccessTokenResponse);

#endif
