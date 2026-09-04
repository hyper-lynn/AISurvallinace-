/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_ExchangeEmailOrPhone_H_
#define _HSVIEW_CLIENT_API_userAccount_ExchangeEmailOrPhone_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
更换手机号或邮箱。

【使用平台账号签名】
 */

typedef struct userAccount_ExchangeEmailOrPhoneRequest 
{
	HsviewRequest base;

	struct userAccount_ExchangeEmailOrPhoneRequestData
	{
		
		/** 发验证码，如123456 */
		CSTR newValidCode;
		/** 新帐号, 手机号码、邮箱 */
		CSTR newAccount;
		/** 验证码token */
		CSTR accessToken;
		/** 老帐号的类型, phone、email */
		CSTR oldType;
		/** 老帐号, 手机号码、邮箱 */
		CSTR oldAccount;
		/** 新帐号的类型, phone、email */
		CSTR newType;

	} data;

} userAccount_ExchangeEmailOrPhoneRequest;

C_API userAccount_ExchangeEmailOrPhoneRequest *HSAPI_INIT(userAccount_ExchangeEmailOrPhoneRequest);

typedef struct userAccount_ExchangeEmailOrPhoneResponse 
{
	HsviewResponse base;

	struct userAccount_ExchangeEmailOrPhoneResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userAccount_ExchangeEmailOrPhoneResponse;

C_API userAccount_ExchangeEmailOrPhoneResponse *HSAPI_INIT(userAccount_ExchangeEmailOrPhoneResponse);

#endif
