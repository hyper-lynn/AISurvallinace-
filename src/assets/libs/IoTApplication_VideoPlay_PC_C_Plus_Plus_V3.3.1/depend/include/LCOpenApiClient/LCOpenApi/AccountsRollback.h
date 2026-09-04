/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_AccountsRollback_H_
#define _LC_OPENAPI_CLIENT_AccountsRollback_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
账户回滚：用于DCloud账户回滚为DMSS账户
 */

typedef struct AccountsRollbackRequest 
{
	LCOpenApiRequest base;

	struct AccountsRollbackRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 必须 DMSS账号，邮箱或手机号(多个账户以英文字符','隔开) */
		CSTR account;

	} data;

} AccountsRollbackRequest;

C_API AccountsRollbackRequest *LCOPENAPI_INIT(AccountsRollbackRequest);

typedef struct AccountsRollbackResponse 
{
	LCOpenApiResponse base;

	struct AccountsRollbackResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} AccountsRollbackResponse;

C_API AccountsRollbackResponse *LCOPENAPI_INIT(AccountsRollbackResponse);

#endif
