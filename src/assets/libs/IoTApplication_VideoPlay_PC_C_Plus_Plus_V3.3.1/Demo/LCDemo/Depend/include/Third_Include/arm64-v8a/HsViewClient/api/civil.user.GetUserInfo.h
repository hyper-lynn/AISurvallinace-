/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUserInfo_H_
#define _HSVIEW_CLIENT_API_GetUserInfo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取这个用户自己的账号信息。

当userType为0时，phoneNumber必须非空返回；
当userType为2时，email必须非空返回；
当用户没有绑定微信，则wxNickname 为空，否则不为空

【使用平台账号签名】
 */

typedef struct GetUserInfoRequest 
{
	HsviewRequest base;

	struct GetUserInfoRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetUserInfoRequest;

C_API GetUserInfoRequest *HSAPI_INIT(GetUserInfoRequest);

typedef struct GetUserInfoResponse 
{
	HsviewResponse base;

	struct GetUserInfoResponseData
	{
		
		/** 平台账号用户名 */
		CSTR username;
		/** 用户头像URL */
		CSTR userIcon;
		/** 微信昵称 */
		CSTR wxNickname;
		/** 用户昵称 */
		CSTR nickname;
		/** 用户手机号码，为空表示未绑定手机号 */
		CSTR phoneNumber;
		/** 用户邮箱，为空表示未绑定邮箱 */
		CSTR email;
		/** [long]平台账号ID */
		int64 userId;
		/** [int]主用户类型：0-手机号，1-微信，2-邮箱 */
		int userType;
 
	} data;

} GetUserInfoResponse;

C_API GetUserInfoResponse *HSAPI_INIT(GetUserInfoResponse);

#endif
