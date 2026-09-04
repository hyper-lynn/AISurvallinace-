/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferObtainApSnapKey_H_
#define _HSVIEW_CLIENT_API_TransferObtainApSnapKey_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取报警网关配件临时秘钥【注意：该协议为平台内部使用协议。非客户端协议】

transferContent和响应内容说明参考PaaS协议：[报警网关配件获取临时秘钥](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%93%8D%E4%BD%9C%E9%85%8D%E4%BB%B6%2F%E8%8E%B7%E5%8F%96%E4%B8%B4%E6%97%B6%E7%A7%98%E9%92%A5.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct TransferObtainApSnapKeyRequest 
{
	HsviewRequest base;

	struct TransferObtainApSnapKeyRequestData
	{
		
		/** struct of TransferObtainApSnapKeyRequestData_TransferContent */
		struct TransferObtainApSnapKeyRequestData_TransferContent {
			/** [long]1,临时秘钥的有效次数 */
			int64 number;
			/** 临时秘钥获取模式 */
			CSTR type;
			/** [long]1,获取临时秘钥的有效时常，单位为秒 */
			int64 effectTime;
		} transferContent;
		/** 配件id */
		CSTR apId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TransferObtainApSnapKeyRequest;

C_API TransferObtainApSnapKeyRequest *HSAPI_INIT(TransferObtainApSnapKeyRequest);

typedef struct TransferObtainApSnapKeyResponse 
{
	HsviewResponse base;

	struct TransferObtainApSnapKeyResponseData
	{
		
		/** 123456 */
		CSTR snapKey;
		/** [String]临时秘钥的生成UTC时间，遵循时间格式要求。 yyyyMMdd'T'HHmmss'Z'  */
		CSTR time;
		/** 临时秘钥的唯一标示符 */
		CSTR keyId;
 
	} data;

} TransferObtainApSnapKeyResponse;

C_API TransferObtainApSnapKeyResponse *HSAPI_INIT(TransferObtainApSnapKeyResponse);

#endif
