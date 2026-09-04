/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ModifyAccountPassword_H_
#define _HSVIEW_CLIENT_API_ModifyAccountPassword_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改账号密码。
注意：修改密码必须要求先拿到AccessToken。本接口会对AccessToken做认证，认证通过才能修改密码。
 */

typedef struct ModifyAccountPasswordRequest 
{
	HsviewRequest base;

	struct ModifyAccountPasswordRequestData
	{
		
		/** 需要修改的密码 */
		CSTR password;
		/** 对应的AccessToken */
		CSTR accessToken;
		/** 用户的乐橙账号 */
		CSTR account;

	} data;

} ModifyAccountPasswordRequest;

C_API ModifyAccountPasswordRequest *HSAPI_INIT(ModifyAccountPasswordRequest);

typedef struct ModifyAccountPasswordResponse 
{
	HsviewResponse base;

	struct ModifyAccountPasswordResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyAccountPasswordResponse;

C_API ModifyAccountPasswordResponse *HSAPI_INIT(ModifyAccountPasswordResponse);

#endif
