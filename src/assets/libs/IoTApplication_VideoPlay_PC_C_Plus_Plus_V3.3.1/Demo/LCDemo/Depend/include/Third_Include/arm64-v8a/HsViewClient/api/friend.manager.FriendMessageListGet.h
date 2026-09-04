/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_friendManager_FriendMessageListGet_H_
#define _HSVIEW_CLIENT_API_friendManager_FriendMessageListGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取好友添加消息（接受方为账号自身的消息）


【使用平台账号签名】
 */

typedef struct friendManager_FriendMessageListGetRequest 
{
	HsviewRequest base;

	struct friendManager_FriendMessageListGetRequestData
	{
		
		/** [long]从该消息ID开始查询。若要从最新开始查，填-1 */
		int64 msgId;
		/** [int]需要查的最大条数 */
		int count;

	} data;

} friendManager_FriendMessageListGetRequest;

C_API friendManager_FriendMessageListGetRequest *HSAPI_INIT(friendManager_FriendMessageListGetRequest);

typedef struct friendManager_FriendMessageListGetResponse 
{
	HsviewResponse base;

	struct friendManager_FriendMessageListGetResponseData
	{
		
		/** define a list with struct of friendManager_FriendMessageListGetResponseData_MessageListElement */
		DECLARE_LIST(struct friendManager_FriendMessageListGetResponseData_MessageListElement
		{
			/** 发起方用户头像 */
			CSTR userIcon;
			/** [long]请求时间，以秒为单位的unix时间戳 */
			int64 time;
			/** [long]消息ID  */
			int64 msgId;
			/** [int]消息处理状态码。0：未处理，待接受，1：已接受并添加，2：已拒绝，3：已过期 */
			int status;
			/** [long]发起方用户ID */
			int64 userId;
			/** 发起方用户昵称 */
			CSTR nickname;
		}) messageList;
 
	} data;

} friendManager_FriendMessageListGetResponse;

C_API friendManager_FriendMessageListGetResponse *HSAPI_INIT(friendManager_FriendMessageListGetResponse);

#endif
