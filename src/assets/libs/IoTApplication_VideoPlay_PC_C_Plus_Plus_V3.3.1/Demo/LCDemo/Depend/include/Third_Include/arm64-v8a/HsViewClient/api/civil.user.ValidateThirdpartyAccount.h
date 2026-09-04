/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ValidateThirdpartyAccount_H_
#define _HSVIEW_CLIENT_API_ValidateThirdpartyAccount_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
验证第三方账号以及token，同时返回是否绑定的乐橙账号的手机号。
若第三方账号验证错误，返回相应的错误码。

accountId：第三方账号ID，移动应用IOS和安卓微信登录、PC扫码登录使用微信的openid。

accountLoginId：第三方账号登录ID,微信登录返回的是开发者账号下应用对应的unionid。

错误码：
1.1105 : 第三方账号校验失败
【无需签名认证】
 */

typedef struct ValidateThirdpartyAccountRequest 
{
	HsviewRequest base;

	struct ValidateThirdpartyAccountRequestData
	{
		
		/** 第三方账号类型，如“taobao”，“weixin” */
		CSTR type;
		/** 第三方平台验证获得的AccessToken */
		CSTR token;
		/** 第三方账号唯一ID */
		CSTR accountId;

	} data;

} ValidateThirdpartyAccountRequest;

C_API ValidateThirdpartyAccountRequest *HSAPI_INIT(ValidateThirdpartyAccountRequest);

typedef struct ValidateThirdpartyAccountResponse 
{
	HsviewResponse base;

	struct ValidateThirdpartyAccountResponseData
	{
		
		/** 昵称 */
		CSTR nickname;
		/** 绑定乐橙账号的手机号，为空表示未绑定手机号 */
		CSTR bindUserPhone;
		/** 第三方账号登录ID, 用于第三方登录乐橙 */
		CSTR accountLoginId;
		/** [long]绑定乐橙账号的id */
		int64 bindUserId;
		/** 用户头像,为空表示不存在 */
		CSTR userIcon;
		/** [bool]是否第一次登录,true表示第一次 */
		BOOL firstLoginFlag;
 
	} data;

} ValidateThirdpartyAccountResponse;

C_API ValidateThirdpartyAccountResponse *HSAPI_INIT(ValidateThirdpartyAccountResponse);

#endif
