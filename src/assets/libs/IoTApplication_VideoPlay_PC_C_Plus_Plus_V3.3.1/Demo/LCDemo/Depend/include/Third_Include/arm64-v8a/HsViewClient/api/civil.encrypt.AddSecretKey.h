/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddSecretKey_H_
#define _HSVIEW_CLIENT_API_AddSecretKey_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
添加用户自定义密钥。

错误码：
1、2000 : accessToken无效
2、1309 : 设备离线
3、1501 ：设备存在视频直播分享
【平台账号签名认证】
 */

typedef struct AddSecretKeyRequest 
{
	HsviewRequest base;

	struct AddSecretKeyRequestData
	{
		
		/** 密钥，如abc123456 */
		CSTR secretKey;
		/** 校验密码或者校验验证码产生的accessToken */
		CSTR accessToken;
		/** 设备ID */
		CSTR deviceId;

	} data;

} AddSecretKeyRequest;

C_API AddSecretKeyRequest *HSAPI_INIT(AddSecretKeyRequest);

typedef struct AddSecretKeyResponse 
{
	HsviewResponse base;

	struct AddSecretKeyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} AddSecretKeyResponse;

C_API AddSecretKeyResponse *HSAPI_INIT(AddSecretKeyResponse);

#endif
