/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAddFriendMessage_H_
#define _HSVIEW_CLIENT_API_GetAddFriendMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取橙聊好友添加消息。
lastTime 为消息最近被处理的时刻，为接受/拒绝的时刻，如果未做任何处理
则为消息产生的时刻。

【使用平台账号签名】
 */

typedef struct GetAddFriendMessageRequest 
{
	HsviewRequest base;

	struct GetAddFriendMessageRequestData
	{
		
		/** [long]从该消息ID开始查询。若要从最新开始查，填-1 */
		int64 msgId;
		/** [int]请求模式：0表示只获取接受方为账号自身的消息；1表示只获取请求方为账号自身的消息；2表示获取接受方或请求方为账号自身的消息 */
		int mode;
		/** [int]需要查的最大条数 */
		int count;

	} data;

} GetAddFriendMessageRequest;

C_API GetAddFriendMessageRequest *HSAPI_INIT(GetAddFriendMessageRequest);

typedef struct GetAddFriendMessageResponse 
{
	HsviewResponse base;

	struct GetAddFriendMessageResponseData
	{
		
		/** define a list with struct of GetAddFriendMessageResponseData_MessagesElement */
		DECLARE_LIST(struct GetAddFriendMessageResponseData_MessagesElement
		{
			/** [long]消息产生时间UNINX时间消息 */
			int64 originalTime;
			/** struct of GetAddFriendMessageResponseData_MessagesElement_InitiatorInfo */
			struct GetAddFriendMessageResponseData_MessagesElement_InitiatorInfo {
				/** 发起方昵称 */
				CSTR nickname;
				/** 发起方头像 */
				CSTR userIcon;
			} initiatorInfo;
			/** [int]消息处理状态码。0未处理；1已接受；2已拒绝；3~9预留 */
			int status;
			/** [long]消息ID  */
			int64 msgId;
			/** [long]消息被处理的最近时间UNINX时间 */
			int64 lastTime;
			/** 接受方用户名 */
			CSTR acceptUsername;
			/** 发起方用户名 */
			CSTR initiatorUsername;
		}) messages;
 
	} data;

} GetAddFriendMessageResponse;

C_API GetAddFriendMessageResponse *HSAPI_INIT(GetAddFriendMessageResponse);

#endif
