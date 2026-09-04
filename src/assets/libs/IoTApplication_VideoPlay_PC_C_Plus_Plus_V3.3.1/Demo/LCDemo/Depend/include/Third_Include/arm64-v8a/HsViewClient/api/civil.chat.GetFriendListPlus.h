/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetFriendListPlus_H_
#define _HSVIEW_CLIENT_API_GetFriendListPlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取好友列表。
【使用平台账号签名】
 */

typedef struct GetFriendListPlusRequest 
{
	HsviewRequest base;

	struct GetFriendListPlusRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetFriendListPlusRequest;

C_API GetFriendListPlusRequest *HSAPI_INIT(GetFriendListPlusRequest);

typedef struct GetFriendListPlusResponse 
{
	HsviewResponse base;

	struct GetFriendListPlusResponseData
	{
		
		/** define a list with struct of GetFriendListPlusResponseData_FriendsElement */
		DECLARE_LIST(struct GetFriendListPlusResponseData_FriendsElement
		{
			/** [O]好友自己的昵称 */
			CSTR nickname;
			/** [int]共享给该好友的设备个数，包括分享和授权，针对同一个设备分享和授权只计算一次 */
			int shareDevCount;
			/** 用户ID */
			CSTR userId;
			/** [O]用户头像 */
			CSTR userIcon;
			/** [int]授权给该好友的设备个数，只包括授权，针对同一个设备授权只计算一次 */
			int authCount;
			/** [int]共享给该好友的设备个数，只包括分享 */
			int shareCount;
			/** [O]好友备注说明 */
			CSTR remark;
			/** [O]好友分组名称 */
			CSTR groupName;
			/** [O]好友别名 */
			CSTR alias;
			/** 平台账号, 账号中间会有*进行敏感信息加密 */
			CSTR account;
		}) friends;
 
	} data;

} GetFriendListPlusResponse;

C_API GetFriendListPlusResponse *HSAPI_INIT(GetFriendListPlusResponse);

#endif
