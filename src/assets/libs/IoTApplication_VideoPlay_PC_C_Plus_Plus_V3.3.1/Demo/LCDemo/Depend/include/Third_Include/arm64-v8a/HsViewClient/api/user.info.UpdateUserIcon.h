/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userInfo_UpdateUserIcon_H_
#define _HSVIEW_CLIENT_API_userInfo_UpdateUserIcon_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
上传并更新用户头像。

【使用平台账号签名】
 */

typedef struct userInfo_UpdateUserIconRequest 
{
	HsviewRequest base;

	struct userInfo_UpdateUserIconRequestData
	{
		
		/** 图片二进制数据的base64编码字符串 */
		CSTR pic;

	} data;

} userInfo_UpdateUserIconRequest;

C_API userInfo_UpdateUserIconRequest *HSAPI_INIT(userInfo_UpdateUserIconRequest);

typedef struct userInfo_UpdateUserIconResponse 
{
	HsviewResponse base;

	struct userInfo_UpdateUserIconResponseData
	{
		
		/** 用户头像URL */
		CSTR avatarUrl;
		/** [O]用户头像的md5值 */
		CSTR avatarMD5;
 
	} data;

} userInfo_UpdateUserIconResponse;

C_API userInfo_UpdateUserIconResponse *HSAPI_INIT(userInfo_UpdateUserIconResponse);

#endif
