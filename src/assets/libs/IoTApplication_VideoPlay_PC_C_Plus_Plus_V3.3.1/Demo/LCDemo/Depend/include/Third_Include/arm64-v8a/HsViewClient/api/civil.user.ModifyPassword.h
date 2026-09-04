/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ModifyPassword_H_
#define _HSVIEW_CLIENT_API_ModifyPassword_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改密码。密码取MD5摘要值。
【使用平台账号签名】
 */

typedef struct ModifyPasswordRequest 
{
	HsviewRequest base;

	struct ModifyPasswordRequestData
	{
		
		/** 新密码，用MD5计算后 */
		CSTR newPassword;

	} data;

} ModifyPasswordRequest;

C_API ModifyPasswordRequest *HSAPI_INIT(ModifyPasswordRequest);

typedef struct ModifyPasswordResponse 
{
	HsviewResponse base;

	struct ModifyPasswordResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyPasswordResponse;

C_API ModifyPasswordResponse *HSAPI_INIT(ModifyPasswordResponse);

#endif
