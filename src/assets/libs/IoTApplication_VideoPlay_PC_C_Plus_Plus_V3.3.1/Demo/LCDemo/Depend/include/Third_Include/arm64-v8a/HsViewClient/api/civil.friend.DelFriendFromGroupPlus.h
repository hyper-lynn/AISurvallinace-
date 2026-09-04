/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DelFriendFromGroupPlus_H_
#define _HSVIEW_CLIENT_API_DelFriendFromGroupPlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除好友分组中的好友

【需要使用平台账号签名】
 */

typedef struct DelFriendFromGroupPlusRequest 
{
	HsviewRequest base;

	struct DelFriendFromGroupPlusRequestData
	{
		
		/** define a list with struct of DelFriendFromGroupPlusRequestData_FriendsElement */
		DECLARE_LIST(struct DelFriendFromGroupPlusRequestData_FriendsElement
		{
			/** 需要添加的好友的用户ID */
			CSTR userId;
		}) friends;
		/** [long]分组id */
		int64 groupId;

	} data;

} DelFriendFromGroupPlusRequest;

C_API DelFriendFromGroupPlusRequest *HSAPI_INIT(DelFriendFromGroupPlusRequest);

typedef struct DelFriendFromGroupPlusResponse 
{
	HsviewResponse base;

	struct DelFriendFromGroupPlusResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DelFriendFromGroupPlusResponse;

C_API DelFriendFromGroupPlusResponse *HSAPI_INIT(DelFriendFromGroupPlusResponse);

#endif
