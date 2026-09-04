/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUserPushMessage_H_
#define _HSVIEW_CLIENT_API_GetUserPushMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询个人推送消息列表。
type的枚举值：
11：上线
12：下线
17：套餐到期提醒
37：提醒计划变更
38：录像计划变更
40：添加橙聊好友请求
41：添加橙聊好友结果
70： 设备分享
110：设备转移

【使用平台账号签名】
 */

typedef struct GetUserPushMessageRequest 
{
	HsviewRequest base;

	struct GetUserPushMessageRequestData
	{
		
		/** [long]从该消息ID开始查询。若要从最新开始查，填-1 */
		int64 msgId;
		/** [int]需要查的最大条数 */
		int count;

	} data;

} GetUserPushMessageRequest;

C_API GetUserPushMessageRequest *HSAPI_INIT(GetUserPushMessageRequest);

typedef struct GetUserPushMessageResponse 
{
	HsviewResponse base;

	struct GetUserPushMessageResponseData
	{
		
		/** define a list with struct of GetUserPushMessageResponseData_MessagesElement */
		DECLARE_LIST(struct GetUserPushMessageResponseData_MessagesElement
		{
			/** [O]通道的ID */
			CSTR channelId;
			/** [int]消息类型 */
			int type;
			/** 标题 */
			CSTR title;
			/** [long]产生时间UNIX时间戳秒 */
			int64 time;
			/** [long]消息ID */
			int64 msgId;
			/** 个人推送消息的网页Url地址 */
			CSTR url;
			/** 内容 */
			CSTR content;
			/** [O]设备ID */
			CSTR deviceId;
		}) messages;
 
	} data;

} GetUserPushMessageResponse;

C_API GetUserPushMessageResponse *HSAPI_INIT(GetUserPushMessageResponse);

#endif
