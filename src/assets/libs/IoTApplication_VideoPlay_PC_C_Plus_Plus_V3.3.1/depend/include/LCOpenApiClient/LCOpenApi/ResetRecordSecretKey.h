/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ResetRecordSecretKey_H_
#define _LC_OPENAPI_CLIENT_ResetRecordSecretKey_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
重置设备云录像秘钥
 */

typedef struct ResetRecordSecretKeyRequest 
{
	LCOpenApiRequest base;

	struct ResetRecordSecretKeyRequestData
	{
		
		/** 重置后的新秘钥 */
		CSTR secretKey;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} ResetRecordSecretKeyRequest;

C_API ResetRecordSecretKeyRequest *LCOPENAPI_INIT(ResetRecordSecretKeyRequest);

typedef struct ResetRecordSecretKeyResponse 
{
	LCOpenApiResponse base;

	struct ResetRecordSecretKeyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ResetRecordSecretKeyResponse;

C_API ResetRecordSecretKeyResponse *LCOPENAPI_INIT(ResetRecordSecretKeyResponse);

#endif
