/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddChildUser_H_
#define _HSVIEW_CLIENT_API_AddChildUser_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
添加乐橙账号子账号。
消息体JSON的 project字段体现是项目，如果为乐橙小微必须填写LeChange-Pro。
phoneNumber 是用来向该手机号发送创建了子账号的通知，该手机号不能用来登陆APP。
异常处理：如果调用者的请求消息不填写username,平台忽略处理，并不在响应消息中体现该条记录的结果。     
【使用用户名签名认证】
 */

typedef struct AddChildUserRequest 
{
	HsviewRequest base;

	struct AddChildUserRequestData
	{
		
		/** define a list with struct of AddChildUserRequestData_ChildUsersElement */
		DECLARE_LIST(struct AddChildUserRequestData_ChildUsersElement
		{
			/** 账号。必填 */
			CSTR username;
			/** 用来通知的手机号码，如13912345678，必填 */
			CSTR phoneNumber;
			/** 子账号的密码，md5后的值 */
			CSTR pwd;
			/** 备注信息。选填 */
			CSTR remark;
			/** 用户昵称。选填 */
			CSTR nickname;
		}) childUsers;

	} data;

} AddChildUserRequest;

C_API AddChildUserRequest *HSAPI_INIT(AddChildUserRequest);

typedef struct AddChildUserResponse 
{
	HsviewResponse base;

	struct AddChildUserResponseData
	{
		
		/** define a list with struct of AddChildUserResponseData_ResultsElement */
		DECLARE_LIST(struct AddChildUserResponseData_ResultsElement
		{
			/** 账号 */
			CSTR username;
			/** [int] 0成功； 1用户已存在；2未填手机号 待续… */
			int resultCode;
		}) results;
 
	} data;

} AddChildUserResponse;

C_API AddChildUserResponse *HSAPI_INIT(AddChildUserResponse);

#endif
