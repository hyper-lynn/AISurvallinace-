/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_friendManager_FriendMessageUpdate_H_
#define _HSVIEW_CLIENT_API_friendManager_FriendMessageUpdate_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
接受好友请求。

【使用平台账号签名】
 */

typedef struct friendManager_FriendMessageUpdateRequest 
{
	HsviewRequest base;

	struct friendManager_FriendMessageUpdateRequestData
	{
		
		/** [long]消息ID */
		int64 msgId;
		/** 对请求的处理动作,可选值:accept(接受)/reject(拒绝) */
		CSTR action;

	} data;

} friendManager_FriendMessageUpdateRequest;

C_API friendManager_FriendMessageUpdateRequest *HSAPI_INIT(friendManager_FriendMessageUpdateRequest);

typedef struct friendManager_FriendMessageUpdateResponse 
{
	HsviewResponse base;

	struct friendManager_FriendMessageUpdateResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} friendManager_FriendMessageUpdateResponse;

C_API friendManager_FriendMessageUpdateResponse *HSAPI_INIT(friendManager_FriendMessageUpdateResponse);

#endif
