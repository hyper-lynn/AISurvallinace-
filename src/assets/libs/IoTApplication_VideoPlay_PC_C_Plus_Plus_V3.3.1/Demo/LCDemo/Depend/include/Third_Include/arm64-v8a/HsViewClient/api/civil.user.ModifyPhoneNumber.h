/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ModifyPhoneNumber_H_
#define _HSVIEW_CLIENT_API_ModifyPhoneNumber_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改绑定的手机号码。需要使用验证码进行校验。
【使用平台账号签名】
 */

typedef struct ModifyPhoneNumberRequest 
{
	HsviewRequest base;

	struct ModifyPhoneNumberRequestData
	{
		
		/** 手机号，如13912345678 */
		CSTR phoneNumber;
		/** 旧手机号验证码，如654321 */
		CSTR validCodeOld;
		/** 新手机号验证码，如123456 */
		CSTR validCode;

	} data;

} ModifyPhoneNumberRequest;

C_API ModifyPhoneNumberRequest *HSAPI_INIT(ModifyPhoneNumberRequest);

typedef struct ModifyPhoneNumberResponse 
{
	HsviewResponse base;

	struct ModifyPhoneNumberResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyPhoneNumberResponse;

C_API ModifyPhoneNumberResponse *HSAPI_INIT(ModifyPhoneNumberResponse);

#endif
