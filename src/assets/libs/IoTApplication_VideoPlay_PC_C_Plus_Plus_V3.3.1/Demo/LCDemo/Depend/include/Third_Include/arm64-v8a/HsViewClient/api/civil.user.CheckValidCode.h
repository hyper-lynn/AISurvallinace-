/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_CheckValidCode_H_
#define _HSVIEW_CLIENT_API_CheckValidCode_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
校验手机号与对应的验证码。
效验成功，生成token，token存缓存，设置有效期
【使用平台账号签名】
 */

typedef struct CheckValidCodeRequest 
{
	HsviewRequest base;

	struct CheckValidCodeRequestData
	{
		
		/** 手机号，如13912345678；邮箱，如123@qq.com */
		CSTR phoneNumber;
		/** 验证码，如123456 */
		CSTR validCode;

	} data;

} CheckValidCodeRequest;

C_API CheckValidCodeRequest *HSAPI_INIT(CheckValidCodeRequest);

typedef struct CheckValidCodeResponse 
{
	HsviewResponse base;

	struct CheckValidCodeResponseData
	{
		
		/** [bool]是否验证成功 */
		BOOL valid;
		/** 验证码token */
		CSTR accessToken;
 
	} data;

} CheckValidCodeResponse;

C_API CheckValidCodeResponse *HSAPI_INIT(CheckValidCodeResponse);

#endif
