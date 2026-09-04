/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_QueryAlarmMessageBitmap_H_
#define _HSVIEW_CLIENT_API_cloudMessage_QueryAlarmMessageBitmap_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询告警消息7天之内覆盖的掩码。
返回bitmap，表示最近7天每一天是否存在告警消息，1表示有告警消息，0表示没有告警消息。
新增可选字段requestType，支持配件告警消息掩码查询，当走配件消息掩码查询逻辑时，channelId字段需要传配件id，2020年4月26号

【使用平台账号签名】
 */

typedef struct cloudMessage_QueryAlarmMessageBitmapRequest 
{
	HsviewRequest base;

	struct cloudMessage_QueryAlarmMessageBitmapRequestData
	{
		
		/** 客户端本地时间，yyyyMMddTHHmmss格式，决定消息掩码结束日期时间 */
		CSTR endTime;
		/** 通道号 */
		CSTR channelId;
		/** [O]请求类型，该字段传了，并且值为apAlarm，则此接口返回配件消息掩码，否则走原逻辑返回通道告警消息掩码 */
		CSTR requestType;
		/** 设备ID */
		CSTR deviceId;

	} data;

} cloudMessage_QueryAlarmMessageBitmapRequest;

C_API cloudMessage_QueryAlarmMessageBitmapRequest *HSAPI_INIT(cloudMessage_QueryAlarmMessageBitmapRequest);

typedef struct cloudMessage_QueryAlarmMessageBitmapResponse 
{
	HsviewResponse base;

	struct cloudMessage_QueryAlarmMessageBitmapResponseData
	{
		
		/** 日掩码：1000001 */
		CSTR bitmap;
 
	} data;

} cloudMessage_QueryAlarmMessageBitmapResponse;

C_API cloudMessage_QueryAlarmMessageBitmapResponse *HSAPI_INIT(cloudMessage_QueryAlarmMessageBitmapResponse);

#endif
