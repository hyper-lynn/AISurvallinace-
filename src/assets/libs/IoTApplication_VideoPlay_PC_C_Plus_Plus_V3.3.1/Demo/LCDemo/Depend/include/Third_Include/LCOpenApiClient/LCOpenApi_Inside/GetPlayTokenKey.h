/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetPlayTokenKey_H_
#define _LC_OPENAPI_CLIENT_GetPlayTokenKey_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备播放码解密秘钥
 */

typedef struct GetPlayTokenKeyRequest 
{
	LCOpenApiRequest base;

	struct GetPlayTokenKeyRequestData
	{
		
		/** [cstr]getPlayTokenKey */
		#define _STATIC_GetPlayTokenKeyRequestData_method "getPlayTokenKey"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;

	} data;

} GetPlayTokenKeyRequest;

C_API GetPlayTokenKeyRequest *LCOPENAPI_INIT(GetPlayTokenKeyRequest);

typedef struct GetPlayTokenKeyResponse 
{
	LCOpenApiResponse base;

	struct GetPlayTokenKeyResponseData
	{
		
		/** 设备播放码秘钥 */
		CSTR playTokenKey;
 
	} data;

} GetPlayTokenKeyResponse;

C_API GetPlayTokenKeyResponse *LCOPENAPI_INIT(GetPlayTokenKeyResponse);

#endif
