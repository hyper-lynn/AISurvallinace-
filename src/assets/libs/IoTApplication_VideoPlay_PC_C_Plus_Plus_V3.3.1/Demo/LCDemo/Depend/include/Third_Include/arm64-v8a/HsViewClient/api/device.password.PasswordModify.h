/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_devicePassword_PasswordModify_H_
#define _HSVIEW_CLIENT_API_devicePassword_PasswordModify_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改设备密码。

username/oldPassword/newPassword需进行传输加密
加密计算公式为：Base64(AES256_CBC(LowerCase(md5(明文)),key[],iv[]))
加密规则如下：
1.采用CBC分组加密的方式，且固定的初始化向量（iv）；
2. 密匙（key）为：LowerCase(MD5(UpperCase(设备ID)+"DAHUAKEY"))
3. 加密算法说明：
	(2) key[]为密匙的二进制数组
	(3) iv[]为初始化向量的二进制数组，iv真实值开发时需要向平台取

参考PaaS协议：[设备密码修改](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E5%AF%86%E7%A0%81%E4%BF%AE%E6%94%B9%E5%8F%8A%E6%A0%A1%E9%AA%8C%2F%E8%AE%BE%E5%A4%87%E5%AF%86%E7%A0%81%E4%BF%AE%E6%94%B9.md&s=pd)

【使用平台账号签名】

 */

typedef struct devicePassword_PasswordModifyRequest 
{
	HsviewRequest base;

	struct devicePassword_PasswordModifyRequestData
	{
		
		/** 设备用户名(Base64(AES256加密)) */
		CSTR username;
		/** 设备新密码(Base64(AES256加密)) */
		CSTR newPassword;
		/** 设备原密码(Base64(AES256加密)) */
		CSTR oldPassword;
		/** 设备ID */
		CSTR deviceId;

	} data;

} devicePassword_PasswordModifyRequest;

C_API devicePassword_PasswordModifyRequest *HSAPI_INIT(devicePassword_PasswordModifyRequest);

typedef struct devicePassword_PasswordModifyResponse 
{
	HsviewResponse base;

	struct devicePassword_PasswordModifyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} devicePassword_PasswordModifyResponse;

C_API devicePassword_PasswordModifyResponse *HSAPI_INIT(devicePassword_PasswordModifyResponse);

#endif
