/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_friendManager_FriendUpdate_H_
#define _HSVIEW_CLIENT_API_friendManager_FriendUpdate_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置好友别名


【使用平台账号签名】
 */

typedef struct friendManager_FriendUpdateRequest 
{
	HsviewRequest base;

	struct friendManager_FriendUpdateRequestData
	{
		
		/** [O]好友备注 */
		CSTR remark;
		/** 好友别名 */
		CSTR alias;
		/** [long]好友的用户ID */
		int64 userId;

	} data;

} friendManager_FriendUpdateRequest;

C_API friendManager_FriendUpdateRequest *HSAPI_INIT(friendManager_FriendUpdateRequest);

typedef struct friendManager_FriendUpdateResponse 
{
	HsviewResponse base;

	struct friendManager_FriendUpdateResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} friendManager_FriendUpdateResponse;

C_API friendManager_FriendUpdateResponse *HSAPI_INIT(friendManager_FriendUpdateResponse);

#endif
