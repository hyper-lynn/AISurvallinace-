/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ResetPassword_H_
#define _HSVIEW_CLIENT_API_ResetPassword_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
密码取MD5摘要值。
该接口不需要签名认证，但是需要校验手机号与发给手机的验证码。
 */

typedef struct ResetPasswordRequest 
{
	HsviewRequest base;

	struct ResetPasswordRequestData
	{
		
		/** 验证码，如123456 */
		CSTR validCode;
		/** 新的密码，用MD5计算 */
		CSTR newPassword;
		/** 手机号，如13912345678；邮箱，如123@qq.com */
		CSTR phoneNumber;

	} data;

} ResetPasswordRequest;

C_API ResetPasswordRequest *HSAPI_INIT(ResetPasswordRequest);

typedef struct ResetPasswordResponse 
{
	HsviewResponse base;

	struct ResetPasswordResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ResetPasswordResponse;

C_API ResetPasswordResponse *HSAPI_INIT(ResetPasswordResponse);

#endif
