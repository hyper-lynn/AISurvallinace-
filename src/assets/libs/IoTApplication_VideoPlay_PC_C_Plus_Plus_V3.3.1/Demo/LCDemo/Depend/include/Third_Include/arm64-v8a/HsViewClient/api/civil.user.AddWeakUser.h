/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddWeakUser_H_
#define _HSVIEW_CLIENT_API_AddWeakUser_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
注册一个新的弱用户。
只提供给开放平台调用
【需开放平台签名认证】
 */

typedef struct AddWeakUserRequest 
{
	HsviewRequest base;

	struct AddWeakUserRequestData
	{
		
		/** 用户昵称 */
		CSTR nickname;
		/** 手机号码，如13912345678 */
		CSTR phoneNumber;
		/** 账号（可填空，表示由平台自动生成） */
		CSTR username;

	} data;

} AddWeakUserRequest;

C_API AddWeakUserRequest *HSAPI_INIT(AddWeakUserRequest);

typedef struct AddWeakUserResponse 
{
	HsviewResponse base;

	struct AddWeakUserResponseData
	{
		
		/** [long]用户的唯一标识 */
		int64 userId;
		/** [bool]用户是否已经存在，false-新创建，true-已经存在 */
		BOOL isExists;
 
	} data;

} AddWeakUserResponse;

C_API AddWeakUserResponse *HSAPI_INIT(AddWeakUserResponse);

#endif
