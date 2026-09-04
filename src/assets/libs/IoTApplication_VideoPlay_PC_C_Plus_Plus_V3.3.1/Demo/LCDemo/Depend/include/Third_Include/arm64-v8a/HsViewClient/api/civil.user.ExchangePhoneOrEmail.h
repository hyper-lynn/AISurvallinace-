/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ExchangePhoneOrEmail_H_
#define _HSVIEW_CLIENT_API_ExchangePhoneOrEmail_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
更换手机号或邮箱。
"phoneNum": "手机号，如13912345678；邮箱，如123@qq.com"
"validCode": "验证码，如123456"
"accessToken":"验证码token"

错误码
1、1101 : 更换手机号已被其他账号绑定；
2、1102 : accessToken或validCode验证码失效；
3、1117 ：更换的邮箱已被其他账号绑定；
4、1119 ：手机或邮箱的格式不正确；

【使用平台账号签名】
 */

typedef struct ExchangePhoneOrEmailRequest 
{
	HsviewRequest base;

	struct ExchangePhoneOrEmailRequestData
	{
		
		/** 验证码，如123456 */
		CSTR validCode;
		/** 验证码token */
		CSTR accessToken;
		/** 更换的新手机号或邮箱，如13912345678；邮箱，如123@qq.com */
		CSTR phoneNum;

	} data;

} ExchangePhoneOrEmailRequest;

C_API ExchangePhoneOrEmailRequest *HSAPI_INIT(ExchangePhoneOrEmailRequest);

typedef struct ExchangePhoneOrEmailResponse 
{
	HsviewResponse base;

	struct ExchangePhoneOrEmailResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ExchangePhoneOrEmailResponse;

C_API ExchangePhoneOrEmailResponse *HSAPI_INIT(ExchangePhoneOrEmailResponse);

#endif
