/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DelFriendFromGroup_H_
#define _HSVIEW_CLIENT_API_DelFriendFromGroup_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除好友分组中的好友

【需要使用平台账号签名】
 */

typedef struct DelFriendFromGroupRequest 
{
	HsviewRequest base;

	struct DelFriendFromGroupRequestData
	{
		
		/** define a list with struct of DelFriendFromGroupRequestData_FriendsElement */
		DECLARE_LIST(struct DelFriendFromGroupRequestData_FriendsElement
		{
			/** 需要添加的好友账号 */
			CSTR username;
		}) friends;
		/** [long]分组id */
		int64 groupId;

	} data;

} DelFriendFromGroupRequest;

C_API DelFriendFromGroupRequest *HSAPI_INIT(DelFriendFromGroupRequest);

typedef struct DelFriendFromGroupResponse 
{
	HsviewResponse base;

	struct DelFriendFromGroupResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DelFriendFromGroupResponse;

C_API DelFriendFromGroupResponse *HSAPI_INIT(DelFriendFromGroupResponse);

#endif
