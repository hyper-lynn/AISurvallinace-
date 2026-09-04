/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ThirdAccountBindPhone_H_
#define _HSVIEW_CLIENT_API_ThirdAccountBindPhone_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
第三方账号绑定乐橙用户。
乐橙用户不存在，那么password必须是新的MD5后的密码。
乐橙用户存在，那么password无效。

错误码
1.1102 : 验证码错误
2.1116 : 手机号用户已经被其他第三方用户绑定
3.1118 : 邮箱用户已经被其他第三方用户绑定

【使用第三方账号签名】
 */

typedef struct ThirdAccountBindPhoneRequest 
{
	HsviewRequest base;

	struct ThirdAccountBindPhoneRequestData
	{
		
		/** 验证码，如123456 */
		CSTR validCode;
		/** [O]新的乐橙用户密码的MD5值 */
		CSTR password;
		/** 手机号或邮箱，如13912345678(或123456@gmail.com) */
		CSTR phoneNumber;

	} data;

} ThirdAccountBindPhoneRequest;

C_API ThirdAccountBindPhoneRequest *HSAPI_INIT(ThirdAccountBindPhoneRequest);

typedef struct ThirdAccountBindPhoneResponse 
{
	HsviewResponse base;

	struct ThirdAccountBindPhoneResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ThirdAccountBindPhoneResponse;

C_API ThirdAccountBindPhoneResponse *HSAPI_INIT(ThirdAccountBindPhoneResponse);

#endif
