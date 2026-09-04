/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAddFriendMessagePlus_H_
#define _HSVIEW_CLIENT_API_GetAddFriendMessagePlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取橙聊好友添加消息。
lastTime 为消息最近被处理的时刻，为接受/拒绝的时刻，如果未做任何处理
则为消息产生的时刻。

【使用平台账号签名】
 */

typedef struct GetAddFriendMessagePlusRequest 
{
	HsviewRequest base;

	struct GetAddFriendMessagePlusRequestData
	{
		
		/** [long]从该消息ID开始查询。若要从最新开始查，填-1 */
		int64 msgId;
		/** [int]请求模式：0表示只获取接受方为账号自身的消息；1表示只获取请求方为账号自身的消息；2表示获取接受方或请求方为账号自身的消息 */
		int mode;
		/** [int]需要查的最大条数 */
		int count;

	} data;

} GetAddFriendMessagePlusRequest;

C_API GetAddFriendMessagePlusRequest *HSAPI_INIT(GetAddFriendMessagePlusRequest);

typedef struct GetAddFriendMessagePlusResponse 
{
	HsviewResponse base;

	struct GetAddFriendMessagePlusResponseData
	{
		
		/** define a list with struct of GetAddFriendMessagePlusResponseData_MessagesElement */
		DECLARE_LIST(struct GetAddFriendMessagePlusResponseData_MessagesElement
		{
			/** [long]消息产生时间UNINX时间消息 */
			int64 originalTime;
			/** struct of GetAddFriendMessagePlusResponseData_MessagesElement_InitiatorInfo */
			struct GetAddFriendMessagePlusResponseData_MessagesElement_InitiatorInfo {
				/** 发起方昵称 */
				CSTR nickname;
				/** 发起方头像 */
				CSTR userIcon;
			} initiatorInfo;
			/** [long]消息被处理的最近时间UNINX时间 */
			int64 lastTime;
			/** [long]消息ID  */
			int64 msgId;
			/** 接受方用户ID */
			CSTR acceptUserId;
			/** [int]消息处理状态码。0未处理；1已接受；2已拒绝；3~9预留 */
			int status;
			/** 发起方用户ID */
			CSTR initiatorUserId;
		}) messages;
 
	} data;

} GetAddFriendMessagePlusResponse;

C_API GetAddFriendMessagePlusResponse *HSAPI_INIT(GetAddFriendMessagePlusResponse);

#endif
