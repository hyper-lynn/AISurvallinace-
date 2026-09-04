/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_commonValidcode_CheckImageValidCode_H_
#define _HSVIEW_CLIENT_API_commonValidcode_CheckImageValidCode_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
校验图片验证码

usage的枚举值如下
Login：用户登录 
GetValidCodeToPhone：获取短信验证码
GetValidCodeToEmail：获取邮箱验证码

【使用固定密钥校验，无需签名】
 */

typedef struct commonValidcode_CheckImageValidCodeRequest 
{
	HsviewRequest base;

	struct commonValidcode_CheckImageValidCodeRequestData
	{
		
		/** 返回验证码的唯一标识 */
		CSTR codeId;
		/** 限制的功能接口，取值详见下面说明 */
		CSTR usage;
		/** 验证码 */
		CSTR code;

	} data;

} commonValidcode_CheckImageValidCodeRequest;

C_API commonValidcode_CheckImageValidCodeRequest *HSAPI_INIT(commonValidcode_CheckImageValidCodeRequest);

typedef struct commonValidcode_CheckImageValidCodeResponse 
{
	HsviewResponse base;

	struct commonValidcode_CheckImageValidCodeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} commonValidcode_CheckImageValidCodeResponse;

C_API commonValidcode_CheckImageValidCodeResponse *HSAPI_INIT(commonValidcode_CheckImageValidCodeResponse);

#endif
