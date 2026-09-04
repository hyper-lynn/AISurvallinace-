/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_friendManager_FriendDelete_H_
#define _HSVIEW_CLIENT_API_friendManager_FriendDelete_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除好友。

【使用平台账号签名】
 */

typedef struct friendManager_FriendDeleteRequest 
{
	HsviewRequest base;

	struct friendManager_FriendDeleteRequestData
	{
		
		/** [long]需要删除的好友用户ID */
		int64 userId;

	} data;

} friendManager_FriendDeleteRequest;

C_API friendManager_FriendDeleteRequest *HSAPI_INIT(friendManager_FriendDeleteRequest);

typedef struct friendManager_FriendDeleteResponse 
{
	HsviewResponse base;

	struct friendManager_FriendDeleteResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} friendManager_FriendDeleteResponse;

C_API friendManager_FriendDeleteResponse *HSAPI_INIT(friendManager_FriendDeleteResponse);

#endif
