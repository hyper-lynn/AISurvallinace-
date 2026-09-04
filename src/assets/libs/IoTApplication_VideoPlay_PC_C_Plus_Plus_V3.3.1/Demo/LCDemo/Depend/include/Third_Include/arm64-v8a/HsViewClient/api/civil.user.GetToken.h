/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetToken_H_
#define _HSVIEW_CLIENT_API_GetToken_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取当前账号的AccessToken。
【使用平台账号签名认证】
 */

typedef struct GetTokenRequest 
{
	HsviewRequest base;

	struct GetTokenRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetTokenRequest;

C_API GetTokenRequest *HSAPI_INIT(GetTokenRequest);

typedef struct GetTokenResponse 
{
	HsviewResponse base;

	struct GetTokenResponseData
	{
		
		/** 用户名 */
		CSTR userName;
		/** 账号的AccessToken */
		CSTR token;
 
	} data;

} GetTokenResponse;

C_API GetTokenResponse *HSAPI_INIT(GetTokenResponse);

#endif
