/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ThirdAccountAuthLogin_H_
#define _HSVIEW_CLIENT_API_ThirdAccountAuthLogin_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
第三方账号授权登录乐橙客户端。


accountLoginId：第三方账号登录ID,微信登录返回的是开发者账号下应用对应的unionid，
accessToken：返回accessToken作微信账号加密签名

错误码：
1.1126 : 临时票据code无效
2.1127 : 第三方账号授权登录失败
【无需签名认证】
 */

typedef struct ThirdAccountAuthLoginRequest 
{
	HsviewRequest base;

	struct ThirdAccountAuthLoginRequestData
	{
		
		/** 第三方账号类型，如“taobao”，“weixin” */
		CSTR type;
		/** 应用唯一标识 */
		CSTR appId;
		/** 授权临时票据，仅在用户确认登录（授权）时有效 */
		CSTR authCode;

	} data;

} ThirdAccountAuthLoginRequest;

C_API ThirdAccountAuthLoginRequest *HSAPI_INIT(ThirdAccountAuthLoginRequest);

typedef struct ThirdAccountAuthLoginResponse 
{
	HsviewResponse base;

	struct ThirdAccountAuthLoginResponseData
	{
		
		/** 昵称 */
		CSTR nickname;
		/** 绑定乐橙账号的手机号，空串表示未绑定 */
		CSTR bindUserPhone;
		/** [bool]是否第一次登录,true表示第一次 */
		BOOL firstLoginFlag;
		/** 用户头像,为空表示不存在 */
		CSTR userIcon;
		/** 第三方账号登录ID, 用于第三方登录乐橙 */
		CSTR accountLoginId;
		/** 绑定乐橙账号的邮箱，空串表示未绑定 */
		CSTR bindUserEmail;
		/** [long]绑定乐橙账号的id */
		int64 bindUserId;
		/** 第三方应用发起接口调用的凭证 */
		CSTR accessToken;
		/** 微信昵称 */
		CSTR wxNickname;
 
	} data;

} ThirdAccountAuthLoginResponse;

C_API ThirdAccountAuthLoginResponse *HSAPI_INIT(ThirdAccountAuthLoginResponse);

#endif
