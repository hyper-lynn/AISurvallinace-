/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_IsFriendOnline_H_
#define _HSVIEW_CLIENT_API_IsFriendOnline_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
橙聊好友是否在线。
【使用平台账号签名】
 */

typedef struct IsFriendOnlineRequest 
{
	HsviewRequest base;

	struct IsFriendOnlineRequestData
	{
		
		/** 好友账号 */
		CSTR username;

	} data;

} IsFriendOnlineRequest;

C_API IsFriendOnlineRequest *HSAPI_INIT(IsFriendOnlineRequest);

typedef struct IsFriendOnlineResponse 
{
	HsviewResponse base;

	struct IsFriendOnlineResponseData
	{
		
		/** 用户头像图片URL */
		CSTR userIcon;
		/** [bool]是否在线 */
		BOOL isOnline;
 
	} data;

} IsFriendOnlineResponse;

C_API IsFriendOnlineResponse *HSAPI_INIT(IsFriendOnlineResponse);

#endif
