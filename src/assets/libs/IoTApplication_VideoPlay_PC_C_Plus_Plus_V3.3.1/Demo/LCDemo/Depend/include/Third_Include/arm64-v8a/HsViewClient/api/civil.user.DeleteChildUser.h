/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteChildUser_H_
#define _HSVIEW_CLIENT_API_DeleteChildUser_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除乐橙账号下的子账号
请求消息体JSON的project体现项目名称，如果为乐橙小微，必填LeChange-Pro。
【使用平台账号签名认证】
 */

typedef struct DeleteChildUserRequest 
{
	HsviewRequest base;

	struct DeleteChildUserRequestData
	{
		
		/** 子账号用户名 */
		DECLARE_LIST(CSTR) childUsers;

	} data;

} DeleteChildUserRequest;

C_API DeleteChildUserRequest *HSAPI_INIT(DeleteChildUserRequest);

typedef struct DeleteChildUserResponse 
{
	HsviewResponse base;

	struct DeleteChildUserResponseData
	{
		
		/** define a list with struct of DeleteChildUserResponseData_ResultsElement */
		DECLARE_LIST(struct DeleteChildUserResponseData_ResultsElement
		{
			/** 子账号用户名 */
			CSTR username;
			/** [int]返回码。 0成功； 1用户不存在；2无权限；待续 */
			int resultCode;
		}) results;
 
	} data;

} DeleteChildUserResponse;

C_API DeleteChildUserResponse *HSAPI_INIT(DeleteChildUserResponse);

#endif
