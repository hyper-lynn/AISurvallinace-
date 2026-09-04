/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AcceptFriend_H_
#define _HSVIEW_CLIENT_API_AcceptFriend_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
接受橙聊好友请求。
【使用平台账号签名】
 */

typedef struct AcceptFriendRequest 
{
	HsviewRequest base;

	struct AcceptFriendRequestData
	{
		
		/** 接受为好友的好友账号 */
		CSTR username;
		/** [bool]是否接受这个好友 */
		BOOL accept;

	} data;

} AcceptFriendRequest;

C_API AcceptFriendRequest *HSAPI_INIT(AcceptFriendRequest);

typedef struct AcceptFriendResponse 
{
	HsviewResponse base;

	struct AcceptFriendResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} AcceptFriendResponse;

C_API AcceptFriendResponse *HSAPI_INIT(AcceptFriendResponse);

#endif
