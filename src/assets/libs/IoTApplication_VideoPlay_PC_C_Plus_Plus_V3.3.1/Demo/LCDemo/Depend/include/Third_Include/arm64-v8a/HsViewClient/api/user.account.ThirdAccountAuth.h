/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_ThirdAccountAuth_H_
#define _HSVIEW_CLIENT_API_userAccount_ThirdAccountAuth_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
第三方账号授权登录乐橙客户端。

平台根据type、appid找到相应的第三方应用的appId。


【默认AK、SK签名认证】
 */

typedef struct userAccount_ThirdAccountAuthRequest 
{
	HsviewRequest base;

	struct userAccount_ThirdAccountAuthRequestData
	{
		
		/** [O]apple登陆时fullName */
		CSTR nickName;
		/** 第三方账号类型，如“weixin”，“facebook”，“apple” */
		CSTR type;
		/** [O]apple登陆时必填 */
		CSTR identityToken;
		/** 授权临时票据，仅在用户确认登录（授权）时有效, */
		CSTR authCode;

	} data;

} userAccount_ThirdAccountAuthRequest;

C_API userAccount_ThirdAccountAuthRequest *HSAPI_INIT(userAccount_ThirdAccountAuthRequest);

typedef struct userAccount_ThirdAccountAuthResponse 
{
	HsviewResponse base;

	struct userAccount_ThirdAccountAuthResponseData
	{
		
		/** 唯一用户id */
		CSTR username;
		/** [O]大华自签发证书SaaS入口地址,使用预埋根证书组件进行接口调用的可用 */
		CSTR entryUrlV2;
		/** 后续用于请求签名的token */
		CSTR token;
		/** true-用户已经设置密码, false-用户未设置密码 */
		CSTR hasPassword;
		/** 客户端第一次登陆时，平台生成的全局唯一标示，后续请求头x-pcs-session-id都必须携带这个值 */
		CSTR sessionId;
 
	} data;

} userAccount_ThirdAccountAuthResponse;

C_API userAccount_ThirdAccountAuthResponse *HSAPI_INIT(userAccount_ThirdAccountAuthResponse);

#endif
