/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteSecretKey_H_
#define _HSVIEW_CLIENT_API_DeleteSecretKey_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除用户自定义密钥

错误码：
1、2000 : accessToken无效
【无需签名认证】
 */

typedef struct DeleteSecretKeyRequest 
{
	HsviewRequest base;

	struct DeleteSecretKeyRequestData
	{
		
		/** 校验密码需要的accessToken */
		CSTR accessToken;
		/** 设备ID */
		CSTR deviceId;

	} data;

} DeleteSecretKeyRequest;

C_API DeleteSecretKeyRequest *HSAPI_INIT(DeleteSecretKeyRequest);

typedef struct DeleteSecretKeyResponse 
{
	HsviewResponse base;

	struct DeleteSecretKeyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteSecretKeyResponse;

C_API DeleteSecretKeyResponse *HSAPI_INIT(DeleteSecretKeyResponse);

#endif
