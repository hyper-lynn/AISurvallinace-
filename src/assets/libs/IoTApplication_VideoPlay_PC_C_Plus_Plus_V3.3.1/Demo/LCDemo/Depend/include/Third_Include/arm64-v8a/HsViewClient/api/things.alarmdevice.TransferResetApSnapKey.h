/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferResetApSnapKey_H_
#define _HSVIEW_CLIENT_API_TransferResetApSnapKey_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
重置报警网关配件临时秘钥

响应内容说明参考PaaS协议：[重置报警网关配件临时秘钥](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%93%8D%E4%BD%9C%E9%85%8D%E4%BB%B6%2F%E4%B8%B4%E6%97%B6%E7%A7%98%E9%92%A5%E9%87%8D%E7%BD%AE.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct TransferResetApSnapKeyRequest 
{
	HsviewRequest base;

	struct TransferResetApSnapKeyRequestData
	{
		
		/** struct of TransferResetApSnapKeyRequestData_TransferContent */
		struct TransferResetApSnapKeyRequestData_TransferContent {
			/** 秘钥唯一id */
			CSTR keyId;
		} transferContent;
		/** 配件id */
		CSTR apId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TransferResetApSnapKeyRequest;

C_API TransferResetApSnapKeyRequest *HSAPI_INIT(TransferResetApSnapKeyRequest);

typedef struct TransferResetApSnapKeyResponse 
{
	HsviewResponse base;

	struct TransferResetApSnapKeyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TransferResetApSnapKeyResponse;

C_API TransferResetApSnapKeyResponse *HSAPI_INIT(TransferResetApSnapKeyResponse);

#endif
