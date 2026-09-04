/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_VerifyAccessToken_H_
#define _HSVIEW_CLIENT_API_VerifyAccessToken_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
验证AccessToken。
RESTAPI返回值如下：
1000：验证通过。
其他：验证失败，具体看原因。
 */

typedef struct VerifyAccessTokenRequest 
{
	HsviewRequest base;

	struct VerifyAccessTokenRequestData
	{
		
		/** 对应的AccessToken */
		CSTR accessToken;
		/** 用户的乐橙账号 */
		CSTR account;

	} data;

} VerifyAccessTokenRequest;

C_API VerifyAccessTokenRequest *HSAPI_INIT(VerifyAccessTokenRequest);

typedef struct VerifyAccessTokenResponse 
{
	HsviewResponse base;

	struct VerifyAccessTokenResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} VerifyAccessTokenResponse;

C_API VerifyAccessTokenResponse *HSAPI_INIT(VerifyAccessTokenResponse);

#endif
