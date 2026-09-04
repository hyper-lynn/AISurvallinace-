/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetFriendPlus_H_
#define _HSVIEW_CLIENT_API_GetFriendPlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取橙聊好友信息。
【使用平台账号签名】
 */

typedef struct GetFriendPlusRequest 
{
	HsviewRequest base;

	struct GetFriendPlusRequestData
	{
		
		/** 好友的id */
		CSTR userId;

	} data;

} GetFriendPlusRequest;

C_API GetFriendPlusRequest *HSAPI_INIT(GetFriendPlusRequest);

typedef struct GetFriendPlusResponse 
{
	HsviewResponse base;

	struct GetFriendPlusResponseData
	{
		
		/** 好友自己的昵称 */
		CSTR nickname;
		/** [int]共享给该好友的设备个数，包括分享和授权，针对同一个设备分享和授权只计算一次 */
		int shareDevCount;
		/** 用户ID */
		CSTR userId;
		/** 用户头像 */
		CSTR userIcon;
		/** [int]授权给该好友的设备个数，只包括授权，针对同一个设备授权只计算一次 */
		int authCount;
		/** [int]共享给该好友的设备个数，只包括分享 */
		int shareCount;
		/** 好友备注说明 */
		CSTR remark;
		/** [O]好友分组名称 */
		CSTR groupName;
		/** 好友别名 */
		CSTR alias;
		/** 台账号, 账号中间会有*进行敏感信息加密 */
		CSTR account;
 
	} data;

} GetFriendPlusResponse;

C_API GetFriendPlusResponse *HSAPI_INIT(GetFriendPlusResponse);

#endif
