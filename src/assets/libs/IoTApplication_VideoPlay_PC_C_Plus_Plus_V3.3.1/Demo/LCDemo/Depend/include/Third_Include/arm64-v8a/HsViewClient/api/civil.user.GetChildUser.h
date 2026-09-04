/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetChildUser_H_
#define _HSVIEW_CLIENT_API_GetChildUser_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取乐橙账号的子账号
请求消息体JSON的project体现项目，如果为乐橙小微必填LeChange-Pro:乐橙小微。
【使用平台账号签名认证】
 */

typedef struct GetChildUserRequest 
{
	HsviewRequest base;

	struct GetChildUserRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetChildUserRequest;

C_API GetChildUserRequest *HSAPI_INIT(GetChildUserRequest);

typedef struct GetChildUserResponse 
{
	HsviewResponse base;

	struct GetChildUserResponseData
	{
		
		/** define a list with struct of GetChildUserResponseData_ChildUsersElement */
		DECLARE_LIST(struct GetChildUserResponseData_ChildUsersElement
		{
			/** 子账号用户名 */
			CSTR username;
			/** 用来通知的手机号码，如13912345678 */
			CSTR phoneNumber;
			/** [int] 0冻结；1授权 */
			int mode;
			/** 备注信息 */
			CSTR remark;
			/** 用户昵称 */
			CSTR nickname;
		}) childUsers;
 
	} data;

} GetChildUserResponse;

C_API GetChildUserResponse *HSAPI_INIT(GetChildUserResponse);

#endif
