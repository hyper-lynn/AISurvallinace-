/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userInfo_GetUserInfo_H_
#define _HSVIEW_CLIENT_API_userInfo_GetUserInfo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取这个用户自己的账号信息。


【使用平台账号签名】
 */

typedef struct userInfo_GetUserInfoRequest 
{
	HsviewRequest base;

	struct userInfo_GetUserInfoRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} userInfo_GetUserInfoRequest;

C_API userInfo_GetUserInfoRequest *HSAPI_INIT(userInfo_GetUserInfoRequest);

typedef struct userInfo_GetUserInfoResponse 
{
	HsviewResponse base;

	struct userInfo_GetUserInfoResponseData
	{
		
		/** [O]用户昵称 */
		CSTR nickname;
		/** define a list with struct of userInfo_GetUserInfoResponseData_ThirdAccountsElement */
		DECLARE_LIST(struct userInfo_GetUserInfoResponseData_ThirdAccountsElement
		{
			/** [O]第三方昵称 */
			CSTR nickname;
			/** [O]微信, 取值为：weixin、facebook、apple */
			CSTR type;
		}) thirdAccounts;
		/** [O]用户头像URL */
		CSTR avatarUrl;
		/** [O]用户国家信息（使用iso-3166-1二字母，eg. 中国对应'CN'） */
		CSTR country;
		/** [O]用户手机号码 */
		CSTR phone;
		/** [O]用户头像的md5值 */
		CSTR avatarMD5;
		/** [long]用户账号ID */
		int64 userId;
		/** [O]用户邮箱 */
		CSTR email;
 
	} data;

} userInfo_GetUserInfoResponse;

C_API userInfo_GetUserInfoResponse *HSAPI_INIT(userInfo_GetUserInfoResponse);

#endif
