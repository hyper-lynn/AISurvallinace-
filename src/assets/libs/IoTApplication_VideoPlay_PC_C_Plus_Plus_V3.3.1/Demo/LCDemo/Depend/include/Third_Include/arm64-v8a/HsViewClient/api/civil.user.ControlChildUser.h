/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ControlChildUser_H_
#define _HSVIEW_CLIENT_API_ControlChildUser_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
控制子账号。
请求消息体JSON的project体现项目名称，如果为乐橙小微，必填LeChange-Pro。
【使用平台账号签名】
 */

typedef struct ControlChildUserRequest 
{
	HsviewRequest base;

	struct ControlChildUserRequestData
	{
		
		/** define a list with struct of ControlChildUserRequestData_ChildUsersElement */
		DECLARE_LIST(struct ControlChildUserRequestData_ChildUsersElement
		{
			/** 账号 */
			CSTR username;
			/** [int] 0冻结；1授权 */
			int mode;
		}) childUsers;

	} data;

} ControlChildUserRequest;

C_API ControlChildUserRequest *HSAPI_INIT(ControlChildUserRequest);

typedef struct ControlChildUserResponse 
{
	HsviewResponse base;

	struct ControlChildUserResponseData
	{
		
		/** define a list with struct of ControlChildUserResponseData_ResultsElement */
		DECLARE_LIST(struct ControlChildUserResponseData_ResultsElement
		{
			/** 账号 */
			CSTR username;
			/** [int]返回码。 0成功； 1用户不存在；2无权限；待续 */
			int resultCode;
		}) results;
 
	} data;

} ControlChildUserResponse;

C_API ControlChildUserResponse *HSAPI_INIT(ControlChildUserResponse);

#endif
