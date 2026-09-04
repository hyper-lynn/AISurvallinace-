/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_devicePassword_VerifyPassword_H_
#define _HSVIEW_CLIENT_API_devicePassword_VerifyPassword_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
校验设备用户名密码。

username和password计算值的公式为，Base64(AES256_CBC(LowerCase(md5(sourceStr))，key[]，iv[]))
加密规则如下：
1. 采用CBC分组加密的方式，且固定的初始化向量（iv）；
2. 密匙（key）为：LowerCase(MD5(UpperCase(deviceId+"DAHUAKEY")))
3. 加密算法说明：
	(1) sourceStr为明文的加密源（设备用户名、设备密码）
	(2) key[]为密匙的二进制数组
	(3) iv[]为初始化向量的二进制数组，iv真实值开发时需要向平台取

【使用平台账号签名】

 */

typedef struct devicePassword_VerifyPasswordRequest 
{
	HsviewRequest base;

	struct devicePassword_VerifyPasswordRequestData
	{
		
		/** 设备用户名（Base64(AES256加密)） */
		CSTR username;
		/** 设备密码（Base64(AES256加密)） */
		CSTR password;
		/** 设备ID */
		CSTR deviceId;

	} data;

} devicePassword_VerifyPasswordRequest;

C_API devicePassword_VerifyPasswordRequest *HSAPI_INIT(devicePassword_VerifyPasswordRequest);

typedef struct devicePassword_VerifyPasswordResponse 
{
	HsviewResponse base;

	struct devicePassword_VerifyPasswordResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} devicePassword_VerifyPasswordResponse;

C_API devicePassword_VerifyPasswordResponse *HSAPI_INIT(devicePassword_VerifyPasswordResponse);

#endif
