/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_BindEmailOrPhone_H_
#define _HSVIEW_CLIENT_API_userAccount_BindEmailOrPhone_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
绑定手机号或绑定邮箱。

【使用平台账号签名】
 */

typedef struct userAccount_BindEmailOrPhoneRequest 
{
	HsviewRequest base;

	struct userAccount_BindEmailOrPhoneRequestData
	{
		
		/** 验证码，如123456 */
		CSTR validCode;
		/** 帐号类型, phone、email */
		CSTR type;
		/** [O]国际区号,海外需要该字段，且type为phone时填写 */
		CSTR areaCode;
		/** 帐号, 手机号码、邮箱 */
		CSTR account;

	} data;

} userAccount_BindEmailOrPhoneRequest;

C_API userAccount_BindEmailOrPhoneRequest *HSAPI_INIT(userAccount_BindEmailOrPhoneRequest);

typedef struct userAccount_BindEmailOrPhoneResponse 
{
	HsviewResponse base;

	struct userAccount_BindEmailOrPhoneResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userAccount_BindEmailOrPhoneResponse;

C_API userAccount_BindEmailOrPhoneResponse *HSAPI_INIT(userAccount_BindEmailOrPhoneResponse);

#endif
