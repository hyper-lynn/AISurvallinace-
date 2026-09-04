/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetVideoMessageById_H_
#define _HSVIEW_CLIENT_API_GetVideoMessageById_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据留言消息id查询留言消息

【使用平台账号签名】
 */

typedef struct GetVideoMessageByIdRequest 
{
	HsviewRequest base;

	struct GetVideoMessageByIdRequestData
	{
		
		/** [long]留言消息id */
		int64 msgId;

	} data;

} GetVideoMessageByIdRequest;

C_API GetVideoMessageByIdRequest *HSAPI_INIT(GetVideoMessageByIdRequest);

typedef struct GetVideoMessageByIdResponse 
{
	HsviewResponse base;

	struct GetVideoMessageByIdResponseData
	{
		
		/** 设备通道的名称 */
		CSTR name;
		/** [long]报警时间UNIX时间戳秒 */
		int64 time;
		/** 留言消息图片URL */
		CSTR picUrl;
		/** 通道号 */
		CSTR channelId;
		/** struct of GetVideoMessageByIdResponseData_MsgRecord */
		struct GetVideoMessageByIdResponseData_MsgRecord {
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
 
	} data;

} GetVideoMessageByIdResponse;

C_API GetVideoMessageByIdResponse *HSAPI_INIT(GetVideoMessageByIdResponse);

#endif
