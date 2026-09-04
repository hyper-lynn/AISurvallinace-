/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteFriend_H_
#define _HSVIEW_CLIENT_API_DeleteFriend_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除橙聊好友。
【使用平台账号签名】
 */

typedef struct DeleteFriendRequest 
{
	HsviewRequest base;

	struct DeleteFriendRequestData
	{
		
		/** 需要删除的好友账号 */
		CSTR username;

	} data;

} DeleteFriendRequest;

C_API DeleteFriendRequest *HSAPI_INIT(DeleteFriendRequest);

typedef struct DeleteFriendResponse 
{
	HsviewResponse base;

	struct DeleteFriendResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteFriendResponse;

C_API DeleteFriendResponse *HSAPI_INIT(DeleteFriendResponse);

#endif
