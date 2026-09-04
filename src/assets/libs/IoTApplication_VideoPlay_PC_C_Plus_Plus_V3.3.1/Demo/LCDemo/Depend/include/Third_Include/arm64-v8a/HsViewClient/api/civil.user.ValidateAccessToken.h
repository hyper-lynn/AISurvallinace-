/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ValidateAccessToken_H_
#define _HSVIEW_CLIENT_API_ValidateAccessToken_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
校验用户的授权是否有效
用户信息，只在校验结果为true时有效
【使用平台账号签名认证】
 */

typedef struct ValidateAccessTokenRequest 
{
	HsviewRequest base;

	struct ValidateAccessTokenRequestData
	{
		
		/** token的类型 */
		CSTR tokenType;
		/** 账号的AccessToken */
		CSTR token;
		/** 账户名 */
		CSTR username;

	} data;

} ValidateAccessTokenRequest;

C_API ValidateAccessTokenRequest *HSAPI_INIT(ValidateAccessTokenRequest);

typedef struct ValidateAccessTokenResponse 
{
	HsviewResponse base;

	struct ValidateAccessTokenResponseData
	{
		
		/** 平台账号用户名 */
		CSTR username;
		/** 用户头像URL */
		CSTR userIcon;
		/** 用户昵称 */
		CSTR nickname;
		/** 用户手机号码 */
		CSTR phoneNumber;
		/** [long]用户的唯一id */
		int64 userId;
		/** [bool]校验结果 true-有效  false-无效 */
		BOOL result;
		/** [O]用户邮箱 */
		CSTR email;
 
	} data;

} ValidateAccessTokenResponse;

C_API ValidateAccessTokenResponse *HSAPI_INIT(ValidateAccessTokenResponse);

#endif
