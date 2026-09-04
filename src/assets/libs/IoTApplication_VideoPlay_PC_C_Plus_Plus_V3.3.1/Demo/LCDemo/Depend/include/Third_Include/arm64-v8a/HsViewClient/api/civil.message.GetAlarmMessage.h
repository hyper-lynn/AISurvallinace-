/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAlarmMessage_H_
#define _HSVIEW_CLIENT_API_GetAlarmMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
按条件查询报警记录。
报警类型定义：
详见[报警类型说明](../推送/报警类型说明.md)       

【使用平台账号签名】
 */

typedef struct GetAlarmMessageRequest 
{
	HsviewRequest base;

	struct GetAlarmMessageRequestData
	{
		
		/** [long]从该消息ID开始查询。若要从最新开始查，填-1 */
		int64 alarmId;
		/** [int]需要查的最大条数 */
		int count;
		/** [int] 0表示只查未读，1表示只查已读，-1表示查所有 */
		int readFlag;
		/** [long]结束时间。Unix时间（单位秒），0表示最晚时间 */
		int64 endTime;
		/** [long]开始时间。Unix时间（单位秒），0表示最早时间 */
		int64 beginTime;
		/** 查设备下该通道号的报警消息。若为空表示查该设备下所有通道的消息。也可填通道所接的设备ID。 */
		CSTR channelId;
		/** 查该设备ID的报警消息。若为空表示查用户所有设备的消息 */
		CSTR deviceId;

	} data;

} GetAlarmMessageRequest;

C_API GetAlarmMessageRequest *HSAPI_INIT(GetAlarmMessageRequest);

typedef struct GetAlarmMessageResponse 
{
	HsviewResponse base;

	struct GetAlarmMessageResponseData
	{
		
		/** define a list with struct of GetAlarmMessageResponseData_AlarmsElement */
		DECLARE_LIST(struct GetAlarmMessageResponseData_AlarmsElement
		{
			/** [bool]是否有联动告警：true/false */
			BOOL hasLinkage;
			/** [int]报警类型 */
			int type;
			/** [O]报警详情描述 */
			CSTR desc;
			/** 缩略图URL */
			CSTR thumbUrl;
			/** 报警时设备本地时间，格式如2014-12-12 12:12:12 */
			CSTR localDate;
			/** 备注字段。如果是低电量，填写电量百分比。 */
			CSTR remark;
			/** 设备ID */
			CSTR deviceId;
			/** [long]消息ID */
			int64 alarmId;
			/** 通道所接的设备ID */
			CSTR channelDeviceId;
			/** 设备或通道的名称 */
			CSTR name;
			/** [int]是否已读。0未读，1已读 */
			int readFlag;
			/** 报警图片url */
			DECLARE_LIST(CSTR) picurlArray;
			/** 通道号 */
			CSTR channelId;
			/** [O]消息唯一标识，用于查询云录像 */
			CSTR token;
			/** [long]报警时间UNIX时间戳秒 */
			int64 time;
		}) alarms;
		/** [int]返回报警消息数组中的未读数量 */
		int unread;
 
	} data;

} GetAlarmMessageResponse;

C_API GetAlarmMessageResponse *HSAPI_INIT(GetAlarmMessageResponse);

#endif
