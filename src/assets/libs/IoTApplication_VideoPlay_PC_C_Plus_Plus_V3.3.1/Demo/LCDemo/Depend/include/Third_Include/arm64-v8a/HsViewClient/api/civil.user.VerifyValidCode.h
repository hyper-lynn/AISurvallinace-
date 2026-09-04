/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_VerifyValidCode_H_
#define _HSVIEW_CLIENT_API_VerifyValidCode_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
校验手机号与对应的验证码。
【无需签名认证】
 */

typedef struct VerifyValidCodeRequest 
{
	HsviewRequest base;

	struct VerifyValidCodeRequestData
	{
		
		/** 手机号，如13912345678；邮箱，如123@qq.com */
		CSTR phoneNumber;
		/** 验证码，如123456 */
		CSTR validCode;

	} data;

} VerifyValidCodeRequest;

C_API VerifyValidCodeRequest *HSAPI_INIT(VerifyValidCodeRequest);

typedef struct VerifyValidCodeResponse 
{
	HsviewResponse base;

	struct VerifyValidCodeResponseData
	{
		
		/** [bool]是否验证成功 */
		BOOL valid;
 
	} data;

} VerifyValidCodeResponse;

C_API VerifyValidCodeResponse *HSAPI_INIT(VerifyValidCodeResponse);

#endif
