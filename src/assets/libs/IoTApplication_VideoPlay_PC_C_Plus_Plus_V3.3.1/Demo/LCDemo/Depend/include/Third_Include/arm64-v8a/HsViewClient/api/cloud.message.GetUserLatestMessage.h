/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_GetUserLatestMessage_H_
#define _HSVIEW_CLIENT_API_cloudMessage_GetUserLatestMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询最新消息


【使用平台账号签名】
 */

typedef struct cloudMessage_GetUserLatestMessageRequest 
{
	HsviewRequest base;

	struct cloudMessage_GetUserLatestMessageRequestData
	{
		
		/** 消息类型，SystemMessage-系统消息  UserPushMessage-个人消息 VideoMessage-留言消息 */
		DECLARE_LIST(CSTR) msgType;

	} data;

} cloudMessage_GetUserLatestMessageRequest;

C_API cloudMessage_GetUserLatestMessageRequest *HSAPI_INIT(cloudMessage_GetUserLatestMessageRequest);

typedef struct cloudMessage_GetUserLatestMessageResponse 
{
	HsviewResponse base;

	struct cloudMessage_GetUserLatestMessageResponseData
	{
		
		/** define a list with struct of cloudMessage_GetUserLatestMessageResponseData_MessagesElement */
		DECLARE_LIST(struct cloudMessage_GetUserLatestMessageResponseData_MessagesElement
		{
			/** 消息类型，SystemMessage-系统消息  UserPushMessage-个人消息 VideoMessage-留言消息 */
			CSTR msgType;
			/** [long]消息ID */
			int64 msgId;
		}) messages;
 
	} data;

} cloudMessage_GetUserLatestMessageResponse;

C_API cloudMessage_GetUserLatestMessageResponse *HSAPI_INIT(cloudMessage_GetUserLatestMessageResponse);

#endif
