/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetBindingUserInfo_H_
#define _HSVIEW_CLIENT_API_GetBindingUserInfo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询指定设备ID的绑定账户，出于安全性考虑，只能查到绑定账户的用户名。
【无需签名认证】
 */

typedef struct GetBindingUserInfoRequest 
{
	HsviewRequest base;

	struct GetBindingUserInfoRequestData
	{
		
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetBindingUserInfoRequest;

C_API GetBindingUserInfoRequest *HSAPI_INIT(GetBindingUserInfoRequest);

typedef struct GetBindingUserInfoResponse 
{
	HsviewResponse base;

	struct GetBindingUserInfoResponseData
	{
		
		/** 绑定账号的用户名，未绑定则为空 */
		CSTR username;
 
	} data;

} GetBindingUserInfoResponse;

C_API GetBindingUserInfoResponse *HSAPI_INIT(GetBindingUserInfoResponse);

#endif
