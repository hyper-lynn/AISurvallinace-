/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_CreateAccount_H_
#define _HSVIEW_CLIENT_API_CreateAccount_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
$$$ 未使用 $$$
新建账号。
 */

typedef struct CreateAccountRequest 
{
	HsviewRequest base;

	struct CreateAccountRequestData
	{
		
		/** 账号对应的密码。业务系统可自行做一些变换，避免出现用户明文密码。 */
		CSTR password;
		/** 用户的乐橙账号 */
		CSTR account;

	} data;

} CreateAccountRequest;

C_API CreateAccountRequest *HSAPI_INIT(CreateAccountRequest);

typedef struct CreateAccountResponse 
{
	HsviewResponse base;

	struct CreateAccountResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} CreateAccountResponse;

C_API CreateAccountResponse *HSAPI_INIT(CreateAccountResponse);

#endif
