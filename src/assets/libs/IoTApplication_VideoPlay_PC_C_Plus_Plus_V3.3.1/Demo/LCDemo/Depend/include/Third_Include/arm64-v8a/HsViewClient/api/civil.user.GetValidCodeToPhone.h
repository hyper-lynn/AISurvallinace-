/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetValidCodeToPhone_H_
#define _HSVIEW_CLIENT_API_GetValidCodeToPhone_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
请求平台给指定接收者发送验证码,支持手机或者邮箱。
【无需签名认证】
 */

typedef struct GetValidCodeToPhoneRequest 
{
	HsviewRequest base;

	struct GetValidCodeToPhoneRequestData
	{
		
		/** 手机号，如13912345678；邮箱，如123@qq.com */
		CSTR phoneNumber;

	} data;

} GetValidCodeToPhoneRequest;

C_API GetValidCodeToPhoneRequest *HSAPI_INIT(GetValidCodeToPhoneRequest);

typedef struct GetValidCodeToPhoneResponse 
{
	HsviewResponse base;

	struct GetValidCodeToPhoneResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} GetValidCodeToPhoneResponse;

C_API GetValidCodeToPhoneResponse *HSAPI_INIT(GetValidCodeToPhoneResponse);

#endif
