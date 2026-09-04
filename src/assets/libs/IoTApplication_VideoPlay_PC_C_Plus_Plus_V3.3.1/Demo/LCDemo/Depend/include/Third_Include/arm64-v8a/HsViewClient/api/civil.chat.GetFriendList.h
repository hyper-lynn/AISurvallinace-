/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetFriendList_H_
#define _HSVIEW_CLIENT_API_GetFriendList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取橙聊好友列表。
【使用平台账号签名】
 */

typedef struct GetFriendListRequest 
{
	HsviewRequest base;

	struct GetFriendListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetFriendListRequest;

C_API GetFriendListRequest *HSAPI_INIT(GetFriendListRequest);

typedef struct GetFriendListResponse 
{
	HsviewResponse base;

	struct GetFriendListResponseData
	{
		
		/** define a list with struct of GetFriendListResponseData_FriendsElement */
		DECLARE_LIST(struct GetFriendListResponseData_FriendsElement
		{
			/** 好友自己的昵称 */
			CSTR nickname;
			/** [bool]是否在线 */
			BOOL isOnline;
			/** [int]共享给该好友的设备个数，包括分享和授权，针对同一个设备分享和授权只计算一次 */
			int shareDevCount;
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
			/** [O]好友分组名称 */
			CSTR groupName;
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

} GetFriendListResponse;

C_API GetFriendListResponse *HSAPI_INIT(GetFriendListResponse);

#endif
