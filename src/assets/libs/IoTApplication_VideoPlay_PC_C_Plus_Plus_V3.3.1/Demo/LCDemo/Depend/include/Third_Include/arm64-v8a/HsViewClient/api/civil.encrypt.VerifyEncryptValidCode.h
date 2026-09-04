/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_VerifyEncryptValidCode_H_
#define _HSVIEW_CLIENT_API_VerifyEncryptValidCode_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
校验视频加密相关的验证码是否正确。
【无需签名认证】
 */

typedef struct VerifyEncryptValidCodeRequest 
{
	HsviewRequest base;

	struct VerifyEncryptValidCodeRequestData
	{
		
		/** 手机号，如13912345678 */
		CSTR phoneNumber;
		/** 验证码，如123456 */
		CSTR validCode;

	} data;

} VerifyEncryptValidCodeRequest;

C_API VerifyEncryptValidCodeRequest *HSAPI_INIT(VerifyEncryptValidCodeRequest);

typedef struct VerifyEncryptValidCodeResponse 
{
	HsviewResponse base;

	struct VerifyEncryptValidCodeResponseData
	{
		
		/** [bool]是否验证成功 */
		BOOL valid;
		/** [O]账号的AccessToken */
		CSTR accessToken;
		/** [long][O]accessToken过期时间，单位秒 */
		int64 expires;
 
	} data;

} VerifyEncryptValidCodeResponse;

C_API VerifyEncryptValidCodeResponse *HSAPI_INIT(VerifyEncryptValidCodeResponse);

#endif
