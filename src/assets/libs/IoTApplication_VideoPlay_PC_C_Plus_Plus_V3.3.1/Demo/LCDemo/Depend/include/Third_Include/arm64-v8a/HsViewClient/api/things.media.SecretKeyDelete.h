/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsMedia_SecretKeyDelete_H_
#define _HSVIEW_CLIENT_API_thingsMedia_SecretKeyDelete_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除用户自定义密钥

错误码：
1、2000 : accessToken无效
【需要使用平台账号签名】
 */

typedef struct thingsMedia_SecretKeyDeleteRequest 
{
	HsviewRequest base;

	struct thingsMedia_SecretKeyDeleteRequestData
	{
		
		/** 校验密码需要的accessToken */
		CSTR accessToken;
		/** 设备ID */
		CSTR deviceId;

	} data;

} thingsMedia_SecretKeyDeleteRequest;

C_API thingsMedia_SecretKeyDeleteRequest *HSAPI_INIT(thingsMedia_SecretKeyDeleteRequest);

typedef struct thingsMedia_SecretKeyDeleteResponse 
{
	HsviewResponse base;

	struct thingsMedia_SecretKeyDeleteResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsMedia_SecretKeyDeleteResponse;

C_API thingsMedia_SecretKeyDeleteResponse *HSAPI_INIT(thingsMedia_SecretKeyDeleteResponse);

#endif
