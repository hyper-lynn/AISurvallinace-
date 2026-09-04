/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddUser_H_
#define _HSVIEW_CLIENT_API_AddUser_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
注册一个新用户。
其中password是用户输入密码的MD5摘要值。
平台需要验证手机号和验证码是否匹配才能允许注册。
【无需签名认证】
 */

typedef struct AddUserRequest 
{
	HsviewRequest base;

	struct AddUserRequestData
	{
		
		/** 账号（可填空，表示由平台自动生成） */
		CSTR username;
		/** 验证码，如123456 */
		CSTR validCode;
		/** 手机号码，如13912345678(邮箱注册时填空) */
		CSTR phoneNumber;
		/** 用户昵称 */
		CSTR nickname;
		/** 密码 */
		CSTR password;
		/** 邮箱，如123456@gmail.com(手机注册时填空) */
		CSTR email;

	} data;

} AddUserRequest;

C_API AddUserRequest *HSAPI_INIT(AddUserRequest);

typedef struct AddUserResponse 
{
	HsviewResponse base;

	struct AddUserResponseData
	{
		
		/** [long]用户的唯一标识 */
		int64 userId;
 
	} data;

} AddUserResponse;

C_API AddUserResponse *HSAPI_INIT(AddUserResponse);

#endif
