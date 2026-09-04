/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ModifyPasswordPlus_H_
#define _HSVIEW_CLIENT_API_ModifyPasswordPlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改密码。

错误码：1109：旧的密码不正确；

计算值的公式为，Base64(AES256_CBC(MD5(密码)))。
加密规则如下：
1. 采用CBC分组加密的方式，且固定的初始化向量（iv）；
2. 密匙（key）为：MD5(toUpperCase(userId) + 'DAHUAKEY')   
   说明:(1) 密匙为（用户Id+固定字符串）后的MD5值;
        (2) MD5后的值为小写
3. 加密算法为：Base64(AES256_CBC(password，key[]，iv[]))    
   说明:(1) password为新、旧密码MD5以后的值，
        (2) key[]为密匙的二进制数组，
        (3) iv[]为初始化向量的二进制数组

加密算法测试用例：
iv=0a52uuEvqTTTTTTT
userId=123456789
password=123456789abc
结果为 W8UNXMWbHHRz2vOaYCpQhw==

【使用平台账号签名】
 */

typedef struct ModifyPasswordPlusRequest 
{
	HsviewRequest base;

	struct ModifyPasswordPlusRequestData
	{
		
		/** 旧密码，计算值的公式为，Base64(AES256_CBC(MD5(oldPassword))) */
		CSTR oldPassword;
		/** 新密码，计算值的公式为，Base64(AES256_CBC(MD5(newPassword))) */
		CSTR newPassword;

	} data;

} ModifyPasswordPlusRequest;

C_API ModifyPasswordPlusRequest *HSAPI_INIT(ModifyPasswordPlusRequest);

typedef struct ModifyPasswordPlusResponse 
{
	HsviewResponse base;

	struct ModifyPasswordPlusResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyPasswordPlusResponse;

C_API ModifyPasswordPlusResponse *HSAPI_INIT(ModifyPasswordPlusResponse);

#endif
