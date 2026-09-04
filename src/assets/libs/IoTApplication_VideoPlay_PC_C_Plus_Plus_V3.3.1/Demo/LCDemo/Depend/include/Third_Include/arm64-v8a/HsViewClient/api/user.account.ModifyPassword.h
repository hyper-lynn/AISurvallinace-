/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_ModifyPassword_H_
#define _HSVIEW_CLIENT_API_userAccount_ModifyPassword_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改密码。

oldpassword和newPassword计算值的公式为，Base64(AES256_CBC(LowerCase(md5(sourceStr))，key[]，iv[]))
加密规则如下：
1. 采用CBC分组加密的方式，且固定的初始化向量（iv）；
2. 密匙（key）为：LowerCase(MD5("DAHUAKEY"))
3. 加密算法说明：
	(1) sourceStr为明文的加密源
	(2) key[]为密匙（key）的二进制数组
	(3) iv[]为初始化向量的二进制数组，iv真实值开发时需要向平台取

	
language参数从x-pcs-client-ua头域中获取

【使用平台账号签名】
 */

typedef struct userAccount_ModifyPasswordRequest 
{
	HsviewRequest base;

	struct userAccount_ModifyPasswordRequestData
	{
		
		/** 旧密码 */
		CSTR oldPassword;
		/** 新密码 */
		CSTR newPassword;

	} data;

} userAccount_ModifyPasswordRequest;

C_API userAccount_ModifyPasswordRequest *HSAPI_INIT(userAccount_ModifyPasswordRequest);

typedef struct userAccount_ModifyPasswordResponse 
{
	HsviewResponse base;

	struct userAccount_ModifyPasswordResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userAccount_ModifyPasswordResponse;

C_API userAccount_ModifyPasswordResponse *HSAPI_INIT(userAccount_ModifyPasswordResponse);

#endif
