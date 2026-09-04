/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_BindPhoneOrEmail_H_
#define _HSVIEW_CLIENT_API_BindPhoneOrEmail_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
绑定手机号或绑定邮箱。

绑定手机号时，phoneNumber作为请求必须字段；
绑定邮箱时，email作为请求必须字段；

错误码
1.1101 : 手机号已存在
2.1102 : 验证码错误
3.1117 : 邮箱已存在

【使用平台账号签名】
 */

typedef struct BindPhoneOrEmailRequest 
{
	HsviewRequest base;

	struct BindPhoneOrEmailRequestData
	{
		
		/** [O]手机号，如13912345678 */
		CSTR phoneNumber;
		/** 验证码，如123456 */
		CSTR validCode;
		/** [O]邮箱，如123456@gmail.com */
		CSTR email;

	} data;

} BindPhoneOrEmailRequest;

C_API BindPhoneOrEmailRequest *HSAPI_INIT(BindPhoneOrEmailRequest);

typedef struct BindPhoneOrEmailResponse 
{
	HsviewResponse base;

	struct BindPhoneOrEmailResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} BindPhoneOrEmailResponse;

C_API BindPhoneOrEmailResponse *HSAPI_INIT(BindPhoneOrEmailResponse);

#endif
