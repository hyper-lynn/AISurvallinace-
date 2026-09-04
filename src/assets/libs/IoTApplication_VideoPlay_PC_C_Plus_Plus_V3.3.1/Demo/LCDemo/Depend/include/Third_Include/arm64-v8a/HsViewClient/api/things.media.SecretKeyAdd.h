/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsMedia_SecretKeyAdd_H_
#define _HSVIEW_CLIENT_API_thingsMedia_SecretKeyAdd_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
添加用户自定义密钥。

secretKey需进行传输加密
加密计算公式为：Base64(AES256_CBC(LowerCase(md5(明文)),key[],iv[]))
加密规则如下：
1.采用CBC分组加密的方式，且固定的初始化向量（iv）；
2. 密匙（key）为：LowerCase(MD5(UpperCase(设备ID)+"DAHUAKEY"))
3. 加密算法说明：
	(2) key[]为密匙的二进制数组
	(3) iv[]为初始化向量的二进制数组，iv真实值开发时需要向平台取
加密算法测试用例：
iv=0a52uuEvqTTTTTTT
deviceCode=123456789
password=123456789abc
结果为 W8UNXMWbHHRz2vOaYCpQhw==

【需要使用平台账号签名】
 */

typedef struct thingsMedia_SecretKeyAddRequest 
{
	HsviewRequest base;

	struct thingsMedia_SecretKeyAddRequestData
	{
		
		/** 密钥,(Base64(AES256加密)) */
		CSTR secretKey;
		/** [O]校验密码或者校验验证码产生的accessToken,注：非开放平台客户端请求为必传字段，开放平台进行自定义密码重置时，可不传此参数，添加自定义秘钥时，如果传了，平台会进行校验 */
		CSTR accessToken;
		/** 设备ID */
		CSTR deviceId;

	} data;

} thingsMedia_SecretKeyAddRequest;

C_API thingsMedia_SecretKeyAddRequest *HSAPI_INIT(thingsMedia_SecretKeyAddRequest);

typedef struct thingsMedia_SecretKeyAddResponse 
{
	HsviewResponse base;

	struct thingsMedia_SecretKeyAddResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsMedia_SecretKeyAddResponse;

C_API thingsMedia_SecretKeyAddResponse *HSAPI_INIT(thingsMedia_SecretKeyAddResponse);

#endif
