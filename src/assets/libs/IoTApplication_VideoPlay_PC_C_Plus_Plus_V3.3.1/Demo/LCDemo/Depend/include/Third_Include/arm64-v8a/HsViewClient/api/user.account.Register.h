/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_Register_H_
#define _HSVIEW_CLIENT_API_userAccount_Register_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
注册一个新用户。
平台需要验证帐号和验证码是否匹配才能允许注册。

password计算值的公式为，Base64(AES256_CBC(LowerCase(md5(sourceStr))，key[]，iv[]))
加密规则如下：
1. 采用CBC分组加密的方式，且固定的初始化向量（iv）；
2. 密匙（key）为：LowerCase(MD5("DAHUAKEY"))
3. 加密算法说明：
	(1) sourceStr为明文的加密源
	(2) key[]为密匙（key）的二进制数组
	(3) iv[]为初始化向量的二进制数组，iv真实值开发时需要向平台取


【默认AK、SK签名认证】
 */

typedef struct userAccount_RegisterRequest 
{
	HsviewRequest base;

	struct userAccount_RegisterRequestData
	{
		
		/** 密码 */
		CSTR password;
		/** 帐号类型, phone、email */
		CSTR type;
		/** 用户国家信息（使用iso-3166-1二字母，eg. 中国对应'CN'） */
		CSTR country;
		/** [O]国际区号,海外需要该字段，且type为phone时填写 */
		CSTR areaCode;
		/** 验证码，如123456 */
		CSTR validCode;
		/** 帐号, 手机号码、邮箱 */
		CSTR account;

	} data;

} userAccount_RegisterRequest;

C_API userAccount_RegisterRequest *HSAPI_INIT(userAccount_RegisterRequest);

typedef struct userAccount_RegisterResponse 
{
	HsviewResponse base;

	struct userAccount_RegisterResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userAccount_RegisterResponse;

C_API userAccount_RegisterResponse *HSAPI_INIT(userAccount_RegisterResponse);

#endif
