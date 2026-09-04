/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetVideoMessage_H_
#define _HSVIEW_CLIENT_API_GetVideoMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
按时间倒序分页查询留言消息

msgId ：留言消息ID
msgRecord表示留言消息对应的留言录像信息，在留言消息对应的留言录像不存在时，这个字段不会返回
msgRecordId：留言视频，删除时使用DeleteCloudRecord删除。

【使用平台账号签名】
 */

typedef struct GetVideoMessageRequest 
{
	HsviewRequest base;

	struct GetVideoMessageRequestData
	{
		
		/** 设备编号，为空代表查询用户所有的留言消息 */
		CSTR deviceCode;
		/** 查设备下该通道号的留言消息。若为空表示查该设备下所有通道的留言消息 */
		CSTR channelId;
		/** [int]需要查的最大条数，最大100 */
		int count;
		/** [long]从该消息ID开始查询。若要从最新开始查，填-1 */
		int64 msgId;

	} data;

} GetVideoMessageRequest;

C_API GetVideoMessageRequest *HSAPI_INIT(GetVideoMessageRequest);

typedef struct GetVideoMessageResponse 
{
	HsviewResponse base;

	struct GetVideoMessageResponseData
	{
		
		/** define a list with struct of GetVideoMessageResponseData_MessagesElement */
		DECLARE_LIST(struct GetVideoMessageResponseData_MessagesElement
		{
			/** [long]报警时间UNIX时间戳秒 */
			int64 time;
			/** 设备通道的名称 */
			CSTR name;
			/** 留言消息图片URL */
			CSTR picUrl;
			/** [long]留言消息ID */
			int64 msgId;
			/** 通道号 */
			CSTR channelId;
			/** struct of GetVideoMessageResponseData_MessagesElement_MsgRecord */
			struct GetVideoMessageResponseData_MessagesElement_MsgRecord {
				/** [long][O]留言消息对应的录像ID */
				int64 msgRecordId;
				/** [O]录像文件路径 */
				CSTR recordPath;
				/** [int][O]加密模式, 0表示默认加密模式, 1表示用户加密模式 */
				int encryptMode;
				/** [O]区域 */
				CSTR region;
				/** [long][O]结束时间，Unix时间戳，1970年秒数 */
				int64 endTime;
				/** [long][O]开始时间，Unix时间戳，1970年秒数 */
				int64 beginTime;
				/** [O]缩略图URL */
				CSTR thumbUrl;
				/** [long][O]云录像的大小，单位byte */
				int64 size;
			} msgRecord;
			/** 设备ID */
			CSTR deviceId;
		}) messages;
 
	} data;

} GetVideoMessageResponse;

C_API GetVideoMessageResponse *HSAPI_INIT(GetVideoMessageResponse);

#endif
