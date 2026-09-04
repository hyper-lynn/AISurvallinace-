/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddFriendToGroupPlus_H_
#define _HSVIEW_CLIENT_API_AddFriendToGroupPlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
向好友分组中添加好友

【需要使用平台账号签名】
 */

typedef struct AddFriendToGroupPlusRequest 
{
	HsviewRequest base;

	struct AddFriendToGroupPlusRequestData
	{
		
		/** define a list with struct of AddFriendToGroupPlusRequestData_FriendsElement */
		DECLARE_LIST(struct AddFriendToGroupPlusRequestData_FriendsElement
		{
			/** 需要添加的好友用户ID */
			CSTR userId;
		}) friends;
		/** [long]分组id */
		int64 groupId;

	} data;

} AddFriendToGroupPlusRequest;

C_API AddFriendToGroupPlusRequest *HSAPI_INIT(AddFriendToGroupPlusRequest);

typedef struct AddFriendToGroupPlusResponse 
{
	HsviewResponse base;

	struct AddFriendToGroupPlusResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} AddFriendToGroupPlusResponse;

C_API AddFriendToGroupPlusResponse *HSAPI_INIT(AddFriendToGroupPlusResponse);

#endif
