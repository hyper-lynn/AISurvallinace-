/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UnbindPhoneOrEmail_H_
#define _HSVIEW_CLIENT_API_UnbindPhoneOrEmail_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
解绑手机号或解绑邮箱。
（必须手机号和邮箱都绑定了，才可以解绑其中一个账号）
"accessToken":"验证码token"

错误码
1、1102 : accessToken验证码失效；
2、1119 ：手机或邮箱的格式不正确；
3、1130 : 手机或邮箱是唯一的登录方式，不可解绑；
【使用平台账号签名】
 */

typedef struct UnbindPhoneOrEmailRequest 
{
	HsviewRequest base;

	struct UnbindPhoneOrEmailRequestData
	{
		
		/** 验证码token */
		CSTR accessToken;

	} data;

} UnbindPhoneOrEmailRequest;

C_API UnbindPhoneOrEmailRequest *HSAPI_INIT(UnbindPhoneOrEmailRequest);

typedef struct UnbindPhoneOrEmailResponse 
{
	HsviewResponse base;

	struct UnbindPhoneOrEmailResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UnbindPhoneOrEmailResponse;

C_API UnbindPhoneOrEmailResponse *HSAPI_INIT(UnbindPhoneOrEmailResponse);

#endif
