/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UpdateUserIcon_H_
#define _HSVIEW_CLIENT_API_UpdateUserIcon_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
上传并更新用户头像。
请求中，pic是图片二进制数据的base64编码。
【使用平台账号签名】
 */

typedef struct UpdateUserIconRequest 
{
	HsviewRequest base;

	struct UpdateUserIconRequestData
	{
		
		/** 图片二进制数据的base64编码字符串 */
		CSTR pic;

	} data;

} UpdateUserIconRequest;

C_API UpdateUserIconRequest *HSAPI_INIT(UpdateUserIconRequest);

typedef struct UpdateUserIconResponse 
{
	HsviewResponse base;

	struct UpdateUserIconResponseData
	{
		
		/** 头像图片保存在平台的URL */
		CSTR url;
 
	} data;

} UpdateUserIconResponse;

C_API UpdateUserIconResponse *HSAPI_INIT(UpdateUserIconResponse);

#endif
