/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetGroupFriendsByIdPlus_H_
#define _HSVIEW_CLIENT_API_GetGroupFriendsByIdPlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 通过分组id获取分组好友信息

【需要使用平台账号签名】

 */

typedef struct GetGroupFriendsByIdPlusRequest 
{
	HsviewRequest base;

	struct GetGroupFriendsByIdPlusRequestData
	{
		
		/** [long]分组id */
		int64 groupId;

	} data;

} GetGroupFriendsByIdPlusRequest;

C_API GetGroupFriendsByIdPlusRequest *HSAPI_INIT(GetGroupFriendsByIdPlusRequest);

typedef struct GetGroupFriendsByIdPlusResponse 
{
	HsviewResponse base;

	struct GetGroupFriendsByIdPlusResponseData
	{
		
		/** define a list with struct of GetGroupFriendsByIdPlusResponseData_FriendsElement */
		DECLARE_LIST(struct GetGroupFriendsByIdPlusResponseData_FriendsElement
		{
			/** 好友自己的昵称 */
			CSTR nickname;
			/** [int]共享给该好友的设备个数，包括分享和授权，针对同一个设备分享和授权只计算一次 */
			int shareDevCount;
			/** 用户ID */
			CSTR userId;
			/** [int]共享给该好友的设备个数，只包括分享 */
			int shareCount;
			/** [int]授权给该好友的设备个数，只包括授权，针对同一个设备授权只计算一次 */
			int authCount;
			/** 用户头像 */
			CSTR userIcon;
			/** 好友备注说明 */
			CSTR remark;
			/** 好友别名 */
			CSTR alias;
			/** 平台账号，会用*对账号进行敏感信息去除 */
			CSTR account;
		}) friends;
 
	} data;

} GetGroupFriendsByIdPlusResponse;

C_API GetGroupFriendsByIdPlusResponse *HSAPI_INIT(GetGroupFriendsByIdPlusResponse);

#endif
