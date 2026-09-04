/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_UnbindThirdAccount_H_
#define _HSVIEW_CLIENT_API_userAccount_UnbindThirdAccount_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
解绑第三方账号。

平台根据type、appid找到相应的第三方应用的appId。

【使用平台账号签名】
 */

typedef struct userAccount_UnbindThirdAccountRequest 
{
	HsviewRequest base;

	struct userAccount_UnbindThirdAccountRequestData
	{
		
		/** [O]第三方请求授权码，apple登陆时选填 */
		CSTR authCode;
		/** 第三方账号类型，如“weixin”、“facebook”、“apple” */
		CSTR type;

	} data;

} userAccount_UnbindThirdAccountRequest;

C_API userAccount_UnbindThirdAccountRequest *HSAPI_INIT(userAccount_UnbindThirdAccountRequest);

typedef struct userAccount_UnbindThirdAccountResponse 
{
	HsviewResponse base;

	struct userAccount_UnbindThirdAccountResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userAccount_UnbindThirdAccountResponse;

C_API userAccount_UnbindThirdAccountResponse *HSAPI_INIT(userAccount_UnbindThirdAccountResponse);

#endif
