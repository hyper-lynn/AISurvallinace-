/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteSubUser_H_
#define _HSVIEW_CLIENT_API_DeleteSubUser_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除某个账号下面的一组子账号。
注意，指定的父账号必须是当前账号，或者当前账号的子账号。
【使用平台账号签名认证】
 */

typedef struct DeleteSubUserRequest 
{
	HsviewRequest base;

	struct DeleteSubUserRequestData
	{
		
		/** 父账号用户名 */
		CSTR username;
		/** 子账号用户名 */
		DECLARE_LIST(CSTR) subUsers;

	} data;

} DeleteSubUserRequest;

C_API DeleteSubUserRequest *HSAPI_INIT(DeleteSubUserRequest);

typedef struct DeleteSubUserResponse 
{
	HsviewResponse base;

	struct DeleteSubUserResponseData
	{
		
		/** define a list with struct of DeleteSubUserResponseData_ResultsElement */
		DECLARE_LIST(struct DeleteSubUserResponseData_ResultsElement
		{
			/** 子账号用户名 */
			CSTR subUsername;
			/** [int] 0成功； 1用户不存在；2无权限；待续 */
			int resultCode;
		}) results;
 
	} data;

} DeleteSubUserResponse;

C_API DeleteSubUserResponse *HSAPI_INIT(DeleteSubUserResponse);

#endif
