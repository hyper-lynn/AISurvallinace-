/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddSubUser_H_
#define _HSVIEW_CLIENT_API_AddSubUser_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
添加一组子账号。
注意，指定的父账号必须是当前账号，或者当前账号的子账号。
【使用平台账号签名认证】
 */

typedef struct AddSubUserRequest 
{
	HsviewRequest base;

	struct AddSubUserRequestData
	{
		
		/** 父账号用户名，表示子账号都添加在这个账号下面 */
		CSTR username;
		/** define a list with struct of AddSubUserRequestData_SubUsersElement */
		DECLARE_LIST(struct AddSubUserRequestData_SubUsersElement
		{
			/** 子账号用户名 */
			CSTR username;
		}) subUsers;

	} data;

} AddSubUserRequest;

C_API AddSubUserRequest *HSAPI_INIT(AddSubUserRequest);

typedef struct AddSubUserResponse 
{
	HsviewResponse base;

	struct AddSubUserResponseData
	{
		
		/** define a list with struct of AddSubUserResponseData_ResultsElement */
		DECLARE_LIST(struct AddSubUserResponseData_ResultsElement
		{
			/** 子账号用户名 */
			CSTR username;
			/** [int] 0成功； 1用户已存在；未完待续… */
			int resultCode;
		}) results;
 
	} data;

} AddSubUserResponse;

C_API AddSubUserResponse *HSAPI_INIT(AddSubUserResponse);

#endif
