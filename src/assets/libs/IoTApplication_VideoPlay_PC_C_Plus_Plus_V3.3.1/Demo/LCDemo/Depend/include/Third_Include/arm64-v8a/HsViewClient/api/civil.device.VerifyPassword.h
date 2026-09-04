/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_VerifyPassword_H_
#define _HSVIEW_CLIENT_API_VerifyPassword_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
校验设备用户名密码。


错误码补充：
9050:"device auth failed"
 
【使用平台账号签名】

 */

typedef struct VerifyPasswordRequest 
{
	HsviewRequest base;

	struct VerifyPasswordRequestData
	{
		
		/** 设备用户名（Base64(AES256加密)） */
		CSTR username;
		/** 设备密码（Base64(AES256加密)） */
		CSTR password;
		/** 设备ID */
		CSTR deviceId;

	} data;

} VerifyPasswordRequest;

C_API VerifyPasswordRequest *HSAPI_INIT(VerifyPasswordRequest);

typedef struct VerifyPasswordResponse 
{
	HsviewResponse base;

	struct VerifyPasswordResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} VerifyPasswordResponse;

C_API VerifyPasswordResponse *HSAPI_INIT(VerifyPasswordResponse);

#endif
