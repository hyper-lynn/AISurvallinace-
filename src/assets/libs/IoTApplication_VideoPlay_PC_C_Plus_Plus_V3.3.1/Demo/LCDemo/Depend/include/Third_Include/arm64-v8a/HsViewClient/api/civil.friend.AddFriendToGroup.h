/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddFriendToGroup_H_
#define _HSVIEW_CLIENT_API_AddFriendToGroup_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
向好友分组中添加好友

【需要使用平台账号签名】
 */

typedef struct AddFriendToGroupRequest 
{
	HsviewRequest base;

	struct AddFriendToGroupRequestData
	{
		
		/** define a list with struct of AddFriendToGroupRequestData_FriendsElement */
		DECLARE_LIST(struct AddFriendToGroupRequestData_FriendsElement
		{
			/** 需要添加的好友账号 */
			CSTR username;
		}) friends;
		/** [long]分组id */
		int64 groupId;

	} data;

} AddFriendToGroupRequest;

C_API AddFriendToGroupRequest *HSAPI_INIT(AddFriendToGroupRequest);

typedef struct AddFriendToGroupResponse 
{
	HsviewResponse base;

	struct AddFriendToGroupResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} AddFriendToGroupResponse;

C_API AddFriendToGroupResponse *HSAPI_INIT(AddFriendToGroupResponse);

#endif
