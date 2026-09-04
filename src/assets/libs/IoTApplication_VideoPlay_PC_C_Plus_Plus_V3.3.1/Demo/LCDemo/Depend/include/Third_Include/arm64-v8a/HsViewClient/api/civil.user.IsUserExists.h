/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_IsUserExists_H_
#define _HSVIEW_CLIENT_API_IsUserExists_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据用户名或手机号或邮箱判断用户是否已经存在，返回用户名和ID。
请求中是需要判断的用户名（也可以是手机号码），返回结果true/false。
【无需签名认证】
 */

typedef struct IsUserExistsRequest 
{
	HsviewRequest base;

	struct IsUserExistsRequestData
	{
		
		/** 用户名或者手机号或邮箱，如xuping或18969120926或123456@gmail.com */
		CSTR usernameOrPhoneNumber;

	} data;

} IsUserExistsRequest;

C_API IsUserExistsRequest *HSAPI_INIT(IsUserExistsRequest);

typedef struct IsUserExistsResponse 
{
	HsviewResponse base;

	struct IsUserExistsResponseData
	{
		
		/** 用户昵称 */
		CSTR nickname;
		/** 用户头像 */
		CSTR userIcon;
		/** [bool]是否绑定 */
		BOOL isBind;
		/** [bool]是否存在 */
		BOOL isExists;
		/** [long]平台标识用户的唯一ID */
		int64 userId;
		/** 平台账号用户名 */
		CSTR username;
 
	} data;

} IsUserExistsResponse;

C_API IsUserExistsResponse *HSAPI_INIT(IsUserExistsResponse);

#endif
