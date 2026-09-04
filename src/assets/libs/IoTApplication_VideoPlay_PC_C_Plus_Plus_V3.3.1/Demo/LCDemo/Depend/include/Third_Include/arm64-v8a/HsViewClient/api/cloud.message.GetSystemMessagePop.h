/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_GetSystemMessagePop_H_
#define _HSVIEW_CLIENT_API_cloudMessage_GetSystemMessagePop_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询消息列表。

返回消息数组，title表示标题, time表示发布时间。
【使用平台账号签名】
 */

typedef struct cloudMessage_GetSystemMessagePopRequest 
{
	HsviewRequest base;

	struct cloudMessage_GetSystemMessagePopRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} cloudMessage_GetSystemMessagePopRequest;

C_API cloudMessage_GetSystemMessagePopRequest *HSAPI_INIT(cloudMessage_GetSystemMessagePopRequest);

typedef struct cloudMessage_GetSystemMessagePopResponse 
{
	HsviewResponse base;

	struct cloudMessage_GetSystemMessagePopResponseData
	{
		
		/** define a list with struct of cloudMessage_GetSystemMessagePopResponseData_MessagesElement */
		DECLARE_LIST(struct cloudMessage_GetSystemMessagePopResponseData_MessagesElement
		{
			/** [long]消息ID */
			int64 msgId;
			/** 系统消息的url */
			CSTR url;
			/** 标题 */
			CSTR title;
			/** 产生的UTC时间，yyyyMMddTHHmmssZ格式 */
			CSTR time;
		}) messages;
 
	} data;

} cloudMessage_GetSystemMessagePopResponse;

C_API cloudMessage_GetSystemMessagePopResponse *HSAPI_INIT(cloudMessage_GetSystemMessagePopResponse);

#endif
