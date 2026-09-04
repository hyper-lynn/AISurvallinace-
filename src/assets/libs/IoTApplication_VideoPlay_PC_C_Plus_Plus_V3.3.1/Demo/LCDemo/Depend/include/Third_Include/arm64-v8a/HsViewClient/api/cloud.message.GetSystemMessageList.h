/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_GetSystemMessageList_H_
#define _HSVIEW_CLIENT_API_cloudMessage_GetSystemMessageList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询消息列表。

返回消息数组，title表示标题, time表示发布时间。
【使用平台账号签名】
 */

typedef struct cloudMessage_GetSystemMessageListRequest 
{
	HsviewRequest base;

	struct cloudMessage_GetSystemMessageListRequestData
	{
		
		/** [long]从该消息ID开始查询。若要从最新开始查，填-1 */
		int64 msgId;
		/** [int]需要查的最大条数，最大128 */
		int count;

	} data;

} cloudMessage_GetSystemMessageListRequest;

C_API cloudMessage_GetSystemMessageListRequest *HSAPI_INIT(cloudMessage_GetSystemMessageListRequest);

typedef struct cloudMessage_GetSystemMessageListResponse 
{
	HsviewResponse base;

	struct cloudMessage_GetSystemMessageListResponseData
	{
		
		/** define a list with struct of cloudMessage_GetSystemMessageListResponseData_MessagesElement */
		DECLARE_LIST(struct cloudMessage_GetSystemMessageListResponseData_MessagesElement
		{
			/** [long]消息ID */
			int64 msgId;
			/** [O]系统消息对应的网页url */
			CSTR url;
			/** 标题 */
			CSTR title;
			/** 产生的UTC时间，yyyyMMddTHHmmssZ格式 */
			CSTR time;
		}) messages;
 
	} data;

} cloudMessage_GetSystemMessageListResponse;

C_API cloudMessage_GetSystemMessageListResponse *HSAPI_INIT(cloudMessage_GetSystemMessageListResponse);

#endif
