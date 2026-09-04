/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ObtainApSnapKey_H_
#define _HSVIEW_CLIENT_API_ObtainApSnapKey_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取报警网关配件临时秘钥

错误码：
1、5001 ：获取秘钥次数超限

transferContent和响应内容说明参考PaaS协议：[获取报警网关配件临时秘钥](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%93%8D%E4%BD%9C%E9%85%8D%E4%BB%B6%2F%E8%8E%B7%E5%8F%96%E4%B8%B4%E6%97%B6%E7%A7%98%E9%92%A5.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct ObtainApSnapKeyRequest 
{
	HsviewRequest base;

	struct ObtainApSnapKeyRequestData
	{
		
		/** [O]验证码 */
		CSTR validCode;
		/** 配件id */
		CSTR apId;
		/** [O]发送验证码的账户, 手机或者邮箱 */
		CSTR sendValidCodeAccount;
		/** struct of ObtainApSnapKeyRequestData_TransferContent */
		struct ObtainApSnapKeyRequestData_TransferContent {
			/** [long]1,临时秘钥的有效次数 */
			int64 number;
			/** 临时秘钥获取模式 */
			CSTR type;
			/** [long]1,获取临时秘钥的有效时常，单位为秒 */
			int64 effectTime;
		} transferContent;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} ObtainApSnapKeyRequest;

C_API ObtainApSnapKeyRequest *HSAPI_INIT(ObtainApSnapKeyRequest);

typedef struct ObtainApSnapKeyResponse 
{
	HsviewResponse base;

	struct ObtainApSnapKeyResponseData
	{
		
		/** 123456 */
		CSTR snapKey;
		/** [long]生成临时秘钥的时间，unix时间戳 */
		int64 time;
		/** 临时秘钥的唯一标示符 */
		CSTR keyId;
 
	} data;

} ObtainApSnapKeyResponse;

C_API ObtainApSnapKeyResponse *HSAPI_INIT(ObtainApSnapKeyResponse);

#endif
