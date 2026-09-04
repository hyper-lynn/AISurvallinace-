/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_ForgetPassword_H_
#define _HSVIEW_CLIENT_API_userAccount_ForgetPassword_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
忘记密码、重置新密码。

password计算值的公式为，Base64(AES256_CBC(LowerCase(md5(sourceStr))，key[]，iv[]))
加密规则如下：
1. 采用CBC分组加密的方式，且固定的初始化向量（iv）；
2. 密匙（key）为：LowerCase(MD5("DAHUAKEY"))
3. 加密算法说明：
	(1) sourceStr为明文的加密源
	(2) key[]为密匙（key）的二进制数组
	(3) iv[]为初始化向量的二进制数组，iv真实值开发时需要向平台取

平台需要校验帐号与验证码。
【默认AK、SK签名认证】
 */

typedef struct userAccount_ForgetPasswordRequest 
{
	HsviewRequest base;

	struct userAccount_ForgetPasswordRequestData
	{
		
		/** 验证码，如123456 */
		CSTR validCode;
		/** 帐号类型, phone、email */
		CSTR type;
		/** 新的密码 */
		CSTR password;
		/** 帐号, 手机号码、邮箱 */
		CSTR account;

	} data;

} userAccount_ForgetPasswordRequest;

C_API userAccount_ForgetPasswordRequest *HSAPI_INIT(userAccount_ForgetPasswordRequest);

typedef struct userAccount_ForgetPasswordResponse 
{
	HsviewResponse base;

	struct userAccount_ForgetPasswordResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userAccount_ForgetPasswordResponse;

C_API userAccount_ForgetPasswordResponse *HSAPI_INIT(userAccount_ForgetPasswordResponse);

#endif
