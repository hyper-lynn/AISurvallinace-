/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetGroupFriendsById_H_
#define _HSVIEW_CLIENT_API_GetGroupFriendsById_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 通过分组id获取分组好友信息

【需要使用平台账号签名】

 */

typedef struct GetGroupFriendsByIdRequest 
{
	HsviewRequest base;

	struct GetGroupFriendsByIdRequestData
	{
		
		/** [long]分组id */
		int64 groupId;

	} data;

} GetGroupFriendsByIdRequest;

C_API GetGroupFriendsByIdRequest *HSAPI_INIT(GetGroupFriendsByIdRequest);

typedef struct GetGroupFriendsByIdResponse 
{
	HsviewResponse base;

	struct GetGroupFriendsByIdResponseData
	{
		
		/** define a list with struct of GetGroupFriendsByIdResponseData_FriendsElement */
		DECLARE_LIST(struct GetGroupFriendsByIdResponseData_FriendsElement
		{
			/** 好友自己的昵称 */
			CSTR nickname;
			/** [bool]是否在线 */
			BOOL isOnline;
			/** 用户ID */
			CSTR userId;
			/** 用户邮箱，为空表示未绑定邮箱 */
			CSTR email;
			/** 用户头像 */
			CSTR userIcon;
			/** [int]共享给该好友的设备个数，只包括分享 */
			int shareCount;
			/** [int]授权给该好友的设备个数，只包括授权，针对同一个设备授权只计算一次 */
			int authCount;
			/** [int]共享给该好友的设备个数，包括分享和授权，针对同一个设备分享和授权只计算一次 */
			int shareDevCount;
			/** 用户手机号码，为空表示未绑定手机号 */
			CSTR phoneNumber;
			/** 好友备注说明 */
			CSTR remark;
			/** 好友别名 */
			CSTR alias;
			/** 平台账号 */
			CSTR username;
		}) friends;
 
	} data;

} GetGroupFriendsByIdResponse;

C_API GetGroupFriendsByIdResponse *HSAPI_INIT(GetGroupFriendsByIdResponse);

#endif
