/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddFriend_H_
#define _HSVIEW_CLIENT_API_AddFriend_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
添加橙聊好友。
【使用平台账号签名】
 */

typedef struct AddFriendRequest 
{
	HsviewRequest base;

	struct AddFriendRequestData
	{
		
		/** 需要添加的好友账号 */
		CSTR username;

	} data;

} AddFriendRequest;

C_API AddFriendRequest *HSAPI_INIT(AddFriendRequest);

typedef struct AddFriendResponse 
{
	HsviewResponse base;

	struct AddFriendResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} AddFriendResponse;

C_API AddFriendResponse *HSAPI_INIT(AddFriendResponse);

#endif
