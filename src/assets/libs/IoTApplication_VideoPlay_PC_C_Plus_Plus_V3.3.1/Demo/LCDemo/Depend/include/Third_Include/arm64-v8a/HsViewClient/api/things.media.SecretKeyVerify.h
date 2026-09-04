/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsMedia_SecretKeyVerify_H_
#define _HSVIEW_CLIENT_API_thingsMedia_SecretKeyVerify_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
deviceId是需要解绑的设备序列号。注意必须是该用户名下的设备

计算值的公式为，Base64(AES256_CBC(MD5(密码)))。
加密规则如下：
采用CBC分组加密的方式，且固定的初始化向量（iv）；
密匙（key）为：MD5(toUpperCase(deviceCode) + 'DAHUAKEY') 
说明：(1) 密匙为（设备Id+固定字符串）后的MD5值;
 (2) MD5后的值为小写
加密算法为：Base64(AES256_CBC(password，key[]，iv[])) 
说明：(1) password为新、旧密码，
 (2) key[]为密匙的二进制数组，
(3) iv[]为初始化向量的二进制数组
加密算法测试用例：
iv=0a52uuEvqTTTTTTT
deviceCode=123456789
password=123456789abc
结果为 W8UNXMWbHHRz2vOaYCpQhw==

【需要使用平台账号签名】
 */

typedef struct thingsMedia_SecretKeyVerifyRequest 
{
	HsviewRequest base;

	struct thingsMedia_SecretKeyVerifyRequestData
	{
		
		/** [O]密钥，（Base64(AES256加密)）,  未开启自定加密不传该字段 */
		CSTR secretKey;
		/** 设备ID */
		CSTR deviceId;

	} data;

} thingsMedia_SecretKeyVerifyRequest;

C_API thingsMedia_SecretKeyVerifyRequest *HSAPI_INIT(thingsMedia_SecretKeyVerifyRequest);

typedef struct thingsMedia_SecretKeyVerifyResponse 
{
	HsviewResponse base;

	struct thingsMedia_SecretKeyVerifyResponseData
	{
		
		/** [bool]是否验证成功 */
		BOOL valid;
		/** [O]校验密码需要的accessToken */
		CSTR accessToken;
		/** [int][O]视频加密token的有效期(秒) */
		int expires;
 
	} data;

} thingsMedia_SecretKeyVerifyResponse;

C_API thingsMedia_SecretKeyVerifyResponse *HSAPI_INIT(thingsMedia_SecretKeyVerifyResponse);

#endif
