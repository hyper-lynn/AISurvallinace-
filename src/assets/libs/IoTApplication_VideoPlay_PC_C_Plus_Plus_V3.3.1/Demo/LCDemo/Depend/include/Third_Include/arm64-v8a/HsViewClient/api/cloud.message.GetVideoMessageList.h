/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_GetVideoMessageList_H_
#define _HSVIEW_CLIENT_API_cloudMessage_GetVideoMessageList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
按时间倒序分页查询留言消息列表

备注：优先使用recordToken，recordToken不存在或者为空时，再使用recordId。
recordToken调用cloud.record.GetRecordByAlarmId接口。
recordId调用cloud.record.GetRecordByRecordId接口。

【使用平台账号签名】
 */

typedef struct cloudMessage_GetVideoMessageListRequest 
{
	HsviewRequest base;

	struct cloudMessage_GetVideoMessageListRequestData
	{
		
		/** [long]从该消息ID开始查询。若要从最新开始查，填-1 */
		int64 msgId;
		/** [O]通道号 */
		CSTR channelId;
		/** [int]需要查的最大条数，最大128 */
		int count;
		/** [O]设备序列号 */
		CSTR deviceId;

	} data;

} cloudMessage_GetVideoMessageListRequest;

C_API cloudMessage_GetVideoMessageListRequest *HSAPI_INIT(cloudMessage_GetVideoMessageListRequest);

typedef struct cloudMessage_GetVideoMessageListResponse 
{
	HsviewResponse base;

	struct cloudMessage_GetVideoMessageListResponseData
	{
		
		/** define a list with struct of cloudMessage_GetVideoMessageListResponseData_MessagesElement */
		DECLARE_LIST(struct cloudMessage_GetVideoMessageListResponseData_MessagesElement
		{
			/** 留言消息图片URL */
			CSTR picUrl;
			/** 录像区域唯一标识id */
			CSTR region;
			/** [long][O]留言消息对应的录像ID */
			int64 recordId;
			/** [O]录像唯一标识 */
			CSTR recordToken;
			/** 设备ID */
			CSTR deviceId;
			/** 设备通道的名称 */
			CSTR name;
			/** [long]留言消息ID */
			int64 msgId;
			/** 通道号 */
			CSTR channelId;
			/** 展示文案 */
			CSTR title;
			/** 设备本地时间，yyyyMMddTHHmmss格式 */
			CSTR time;
		}) messages;
 
	} data;

} cloudMessage_GetVideoMessageListResponse;

C_API cloudMessage_GetVideoMessageListResponse *HSAPI_INIT(cloudMessage_GetVideoMessageListResponse);

#endif
