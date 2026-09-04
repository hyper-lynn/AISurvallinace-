/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetSystemMessage_H_
#define _HSVIEW_CLIENT_API_GetSystemMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询消息列表。
为兼容老版本，如果msgType不存在，则代表默认查询系统消息
返回消息数组，title表示标题，content表示内容，url为系统消息对应网页url,time表示发布时间。
这里的时间格式为UNIX时间戳（1970年开始的秒数）。
【使用平台账号签名】
 */

typedef struct GetSystemMessageRequest 
{
	HsviewRequest base;

	struct GetSystemMessageRequestData
	{
		
		/** [long]从该消息ID开始查询。若要从最新开始查，填-1 */
		int64 msgId;
		/** [int]消息类型：0-系统消息  1-活动消息  4-资讯消息 */
		int msgType;
		/** [int]需要查的最大条数 */
		int count;

	} data;

} GetSystemMessageRequest;

C_API GetSystemMessageRequest *HSAPI_INIT(GetSystemMessageRequest);

typedef struct GetSystemMessageResponse 
{
	HsviewResponse base;

	struct GetSystemMessageResponseData
	{
		
		/** define a list with struct of GetSystemMessageResponseData_MessagesElement */
		DECLARE_LIST(struct GetSystemMessageResponseData_MessagesElement
		{
			/** 标题 */
			CSTR title;
			/** [long]产生时间UNIX时间戳秒 */
			int64 time;
			/** [long]消息ID */
			int64 msgId;
			/** 系统消息对应的网页url */
			CSTR url;
			/** 内容 */
			CSTR content;
			/** 标题图片的url */
			CSTR imgUrl;
		}) messages;
 
	} data;

} GetSystemMessageResponse;

C_API GetSystemMessageResponse *HSAPI_INIT(GetSystemMessageResponse);

#endif
