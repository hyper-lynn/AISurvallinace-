/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_AccountsUpgrade_H_
#define _LC_OPENAPI_CLIENT_AccountsUpgrade_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
用于原DMSS账户升级成DCloud账户使用
 */

typedef struct AccountsUpgradeRequest 
{
	LCOpenApiRequest base;

	struct AccountsUpgradeRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 必须 DMSS账号，邮箱或手机号(多个账户以英文字符','隔开) */
		CSTR account;

	} data;

} AccountsUpgradeRequest;

C_API AccountsUpgradeRequest *LCOPENAPI_INIT(AccountsUpgradeRequest);

typedef struct AccountsUpgradeResponse 
{
	LCOpenApiResponse base;

	struct AccountsUpgradeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} AccountsUpgradeResponse;

C_API AccountsUpgradeResponse *LCOPENAPI_INIT(AccountsUpgradeResponse);

#endif
