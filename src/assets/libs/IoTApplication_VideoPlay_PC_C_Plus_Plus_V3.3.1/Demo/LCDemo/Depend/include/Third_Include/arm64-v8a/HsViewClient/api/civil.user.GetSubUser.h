/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetSubUser_H_
#define _HSVIEW_CLIENT_API_GetSubUser_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取某个账号的子账号。
注意，指定的父账号必须是当前账号，或者当前账号的子账号。
【使用平台账号签名认证】
 */

typedef struct GetSubUserRequest 
{
	HsviewRequest base;

	struct GetSubUserRequestData
	{
		
		/** 父账号用户名 */
		CSTR username;

	} data;

} GetSubUserRequest;

C_API GetSubUserRequest *HSAPI_INIT(GetSubUserRequest);

typedef struct GetSubUserResponse 
{
	HsviewResponse base;

	struct GetSubUserResponseData
	{
		
		/** define a list with struct of GetSubUserResponseData_SubUsersElement */
		DECLARE_LIST(struct GetSubUserResponseData_SubUsersElement
		{
			/** 子账号用户名 */
			CSTR username;
		}) subUsers;
 
	} data;

} GetSubUserResponse;

C_API GetSubUserResponse *HSAPI_INIT(GetSubUserResponse);

#endif
