/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_friendManager_FriendMessageDelete_H_
#define _HSVIEW_CLIENT_API_friendManager_FriendMessageDelete_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除好友申请记录

【使用平台账号签名】
 */

typedef struct friendManager_FriendMessageDeleteRequest 
{
	HsviewRequest base;

	struct friendManager_FriendMessageDeleteRequestData
	{
		
		/** [long]消息ID  */
		int64 msgId;

	} data;

} friendManager_FriendMessageDeleteRequest;

C_API friendManager_FriendMessageDeleteRequest *HSAPI_INIT(friendManager_FriendMessageDeleteRequest);

typedef struct friendManager_FriendMessageDeleteResponse 
{
	HsviewResponse base;

	struct friendManager_FriendMessageDeleteResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} friendManager_FriendMessageDeleteResponse;

C_API friendManager_FriendMessageDeleteResponse *HSAPI_INIT(friendManager_FriendMessageDeleteResponse);

#endif
