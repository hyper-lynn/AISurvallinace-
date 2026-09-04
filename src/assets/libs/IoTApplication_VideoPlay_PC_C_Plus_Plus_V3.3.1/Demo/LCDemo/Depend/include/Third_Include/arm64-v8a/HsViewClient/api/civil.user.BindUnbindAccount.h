/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_BindUnbindAccount_H_
#define _HSVIEW_CLIENT_API_BindUnbindAccount_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
邮箱或手机号的绑定/解绑
平台需要验证手机号、邮箱号和验证码是否匹配才能允许绑定/解绑。
错误码统一返回，有验证码错误、账号错误等
【使用平台账号签名】
 */

typedef struct BindUnbindAccountRequest 
{
	HsviewRequest base;

	struct BindUnbindAccountRequestData
	{
		
		/** 验证码，绑定需要验证，如123456 */
		CSTR validCode;
		/** [bool] 0-bind, 1-unbind */
		BOOL optType;
		/** 邮箱号或者手机号 */
		CSTR account;

	} data;

} BindUnbindAccountRequest;

C_API BindUnbindAccountRequest *HSAPI_INIT(BindUnbindAccountRequest);

typedef struct BindUnbindAccountResponse 
{
	HsviewResponse base;

	struct BindUnbindAccountResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} BindUnbindAccountResponse;

C_API BindUnbindAccountResponse *HSAPI_INIT(BindUnbindAccountResponse);

#endif
