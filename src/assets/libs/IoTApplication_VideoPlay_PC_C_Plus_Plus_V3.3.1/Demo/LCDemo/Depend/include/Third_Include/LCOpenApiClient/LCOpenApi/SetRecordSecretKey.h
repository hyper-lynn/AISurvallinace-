/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetRecordSecretKey_H_
#define _LC_OPENAPI_CLIENT_SetRecordSecretKey_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
云录像加密接口
 */

typedef struct SetRecordSecretKeyRequest 
{
	LCOpenApiRequest base;

	struct SetRecordSecretKeyRequestData
	{
		
		/** [String]若需要删除云录像加密，该字段不传或者传空，然后oldSecretKey字段传待删除的云录像加密秘钥 */
		CSTR secretKey;
		/** [String]若第一次设置加密秘钥，此值设为空或者不传均可。若更新或者删除秘钥，则需要传入更新前旧的秘钥值 */
		CSTR oldSecretKey;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetRecordSecretKeyRequest;

C_API SetRecordSecretKeyRequest *LCOPENAPI_INIT(SetRecordSecretKeyRequest);

typedef struct SetRecordSecretKeyResponse 
{
	LCOpenApiResponse base;

	struct SetRecordSecretKeyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetRecordSecretKeyResponse;

C_API SetRecordSecretKeyResponse *LCOPENAPI_INIT(SetRecordSecretKeyResponse);

#endif
