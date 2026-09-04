/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_UnbindEmailOrPhone_H_
#define _HSVIEW_CLIENT_API_userAccount_UnbindEmailOrPhone_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
解绑手机号或解绑邮箱。
（必须手机号和邮箱都绑定了，才可以解绑其中一个账号）

【使用平台账号签名】
 */

typedef struct userAccount_UnbindEmailOrPhoneRequest 
{
	HsviewRequest base;

	struct userAccount_UnbindEmailOrPhoneRequestData
	{
		
		/** 验证码，如123456 */
		CSTR validCode;
		/** 帐号类型, phone、email */
		CSTR type;
		/** 帐号, 手机号码、邮箱 */
		CSTR account;

	} data;

} userAccount_UnbindEmailOrPhoneRequest;

C_API userAccount_UnbindEmailOrPhoneRequest *HSAPI_INIT(userAccount_UnbindEmailOrPhoneRequest);

typedef struct userAccount_UnbindEmailOrPhoneResponse 
{
	HsviewResponse base;

	struct userAccount_UnbindEmailOrPhoneResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userAccount_UnbindEmailOrPhoneResponse;

C_API userAccount_UnbindEmailOrPhoneResponse *HSAPI_INIT(userAccount_UnbindEmailOrPhoneResponse);

#endif
