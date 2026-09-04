/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_VerifyImageValidCode_H_
#define _HSVIEW_CLIENT_API_VerifyImageValidCode_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
校验图片验证码

method的枚举值如下
Login：用户登录 
GetValidCodeToPhone：获取短信验证码
GetValidCodeToEmail：获取邮箱验证码

【使用固定密钥校验，无需签名】
 */

typedef struct VerifyImageValidCodeRequest 
{
	HsviewRequest base;

	struct VerifyImageValidCodeRequestData
	{
		
		/** 返回验证码的唯一标识 */
		CSTR codeId;
		/** 限制的功能接口，取值详见下面说明 */
		CSTR method;
		/** 验证码 */
		CSTR code;

	} data;

} VerifyImageValidCodeRequest;

C_API VerifyImageValidCodeRequest *HSAPI_INIT(VerifyImageValidCodeRequest);

typedef struct VerifyImageValidCodeResponse 
{
	HsviewResponse base;

	struct VerifyImageValidCodeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} VerifyImageValidCodeResponse;

C_API VerifyImageValidCodeResponse *HSAPI_INIT(VerifyImageValidCodeResponse);

#endif
