/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_VerifySecretKey_H_
#define _HSVIEW_CLIENT_API_VerifySecretKey_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
校验密钥是否与设备上保存的密码致。

设备默认序列号为密钥时，secretKey可以不带或者为""。

错误码：
1、1309 : 设备离线

【无需签名认证】
 */

typedef struct VerifySecretKeyRequest 
{
	HsviewRequest base;

	struct VerifySecretKeyRequestData
	{
		
		/** [O]密钥，如13912345678, 第一次添加后默认为空串 */
		CSTR secretKey;
		/** 设备ID */
		CSTR deviceId;

	} data;

} VerifySecretKeyRequest;

C_API VerifySecretKeyRequest *HSAPI_INIT(VerifySecretKeyRequest);

typedef struct VerifySecretKeyResponse 
{
	HsviewResponse base;

	struct VerifySecretKeyResponseData
	{
		
		/** [bool]是否验证成功 */
		BOOL valid;
		/** [O]校验密码需要的accessToken */
		CSTR accessToken;
		/** [long][O]accessToken过期时间，单位秒 */
		int64 expires;
 
	} data;

} VerifySecretKeyResponse;

C_API VerifySecretKeyResponse *HSAPI_INIT(VerifySecretKeyResponse);

#endif
