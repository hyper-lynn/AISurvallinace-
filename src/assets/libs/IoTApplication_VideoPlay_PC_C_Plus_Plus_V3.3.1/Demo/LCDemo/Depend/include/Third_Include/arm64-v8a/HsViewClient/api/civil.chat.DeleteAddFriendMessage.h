/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteAddFriendMessage_H_
#define _HSVIEW_CLIENT_API_DeleteAddFriendMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除申请记录

【使用平台账号签名】
 */

typedef struct DeleteAddFriendMessageRequest 
{
	HsviewRequest base;

	struct DeleteAddFriendMessageRequestData
	{
		
		/** [long]消息ID  */
		int64 msgId;

	} data;

} DeleteAddFriendMessageRequest;

C_API DeleteAddFriendMessageRequest *HSAPI_INIT(DeleteAddFriendMessageRequest);

typedef struct DeleteAddFriendMessageResponse 
{
	HsviewResponse base;

	struct DeleteAddFriendMessageResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteAddFriendMessageResponse;

C_API DeleteAddFriendMessageResponse *HSAPI_INIT(DeleteAddFriendMessageResponse);

#endif
