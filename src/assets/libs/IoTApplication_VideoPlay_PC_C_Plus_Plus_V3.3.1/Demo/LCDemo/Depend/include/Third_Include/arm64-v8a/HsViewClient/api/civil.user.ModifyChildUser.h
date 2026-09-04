/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ModifyChildUser_H_
#define _HSVIEW_CLIENT_API_ModifyChildUser_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改乐橙账号子用户信息。
请求消息体JSON的project体现项目名称，如果为乐橙小微，必填LeChange-Pro。
异常处理：需包含 password,nickname,phonenumber,remark的一个或者多个，如果不包含任何一个，表示不修改任何信息，返回成功。
【使用平台账号签名认证】
 */

typedef struct ModifyChildUserRequest 
{
	HsviewRequest base;

	struct ModifyChildUserRequestData
	{
		
		/** 子账号用户名,标识子账号，必填 */
		CSTR username;
		/** 用来通知的手机号码，如13912345678，选填 */
		CSTR phoneNumber;
		/** 密码，MD5（明文）,选填 */
		CSTR password;
		/** 备注信息，选填 */
		CSTR remark;
		/** 用户昵称，选填 */
		CSTR nickname;

	} data;

} ModifyChildUserRequest;

C_API ModifyChildUserRequest *HSAPI_INIT(ModifyChildUserRequest);

typedef struct ModifyChildUserResponse 
{
	HsviewResponse base;

	struct ModifyChildUserResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyChildUserResponse;

C_API ModifyChildUserResponse *HSAPI_INIT(ModifyChildUserResponse);

#endif
