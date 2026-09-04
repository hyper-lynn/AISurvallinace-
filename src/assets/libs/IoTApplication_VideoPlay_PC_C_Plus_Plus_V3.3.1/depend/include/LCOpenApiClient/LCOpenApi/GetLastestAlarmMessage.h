/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetLastestAlarmMessage_H_
#define _LC_OPENAPI_CLIENT_GetLastestAlarmMessage_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
按设备通道、配件获取最近一条消息
 */

typedef struct GetLastestAlarmMessageRequest 
{
	LCOpenApiRequest base;

	struct GetLastestAlarmMessageRequestData
	{
		
		/** 授权token */
		CSTR token;
		/** define a list with struct of GetLastestAlarmMessageRequestData_DeviceListElement */
		DECLARE_LIST(struct GetLastestAlarmMessageRequestData_DeviceListElement
		{
			/** 配件设备序列号1 */
			DECLARE_LIST(CSTR) apIds;
			/** 设备通道号1 */
			DECLARE_LIST(CSTR) channelIds;
			/** 设备序列号 */
			CSTR deviceId;
		}) deviceList;

	} data;

} GetLastestAlarmMessageRequest;

C_API GetLastestAlarmMessageRequest *LCOPENAPI_INIT(GetLastestAlarmMessageRequest);

typedef struct GetLastestAlarmMessageResponse 
{
	LCOpenApiResponse base;

	struct GetLastestAlarmMessageResponseData
	{
		
		/** define a list with struct of GetLastestAlarmMessageResponseData_AlarmListElement */
		DECLARE_LIST(struct GetLastestAlarmMessageResponseData_AlarmListElement
		{
			/** define a list with struct of GetLastestAlarmMessageResponseData_AlarmListElement_ChannelAlarmsElement */
			DECLARE_LIST(struct GetLastestAlarmMessageResponseData_AlarmListElement_ChannelAlarmsElement
			{
				/** 报警类型 */
				CSTR type;
				/** 报警图片url */
				DECLARE_LIST(CSTR) picUrl;
				/** 设备通道或者报警消息的缩略图URL */
				CSTR thumbUrl;
				/** [O]默认本地录像播放时长 */
				CSTR lrecordStopTime;
				/** [O]备注字段。如果是低电量，填写电量百分比0-100，如果涉及门锁钥匙，填写钥匙名称。 */
				CSTR remark;
				/** [long]告警消息ID */
				int64 alarmId;
				/** [O]消息唯一标识，用于查询云录像 */
				CSTR token;
				/** [int]未读消息数量 */
				int unread;
				/** 通道号 */
				CSTR channelId;
				/** 通道名称 */
				CSTR name;
				/** 设备本地报警时间,格式yyyyMMddTHHmmss */
				CSTR time;
			}) channelAlarms;
			/** define a list with struct of GetLastestAlarmMessageResponseData_AlarmListElement_ApAlarmsElement */
			DECLARE_LIST(struct GetLastestAlarmMessageResponseData_AlarmListElement_ApAlarmsElement
			{
				/** [long]告警消息ID */
				int64 alarmId;
				/** 配件ID */
				CSTR apId;
				/** 设备本地报警时间,格式yyyyMMddTHHmmss */
				CSTR time;
				/** 配件类型 */
				CSTR apType;
				/** [bool]是否存在联动消息 */
				BOOL hasLinkage;
				/** [int]未读消息数量 */
				int unread;
				/** 报警类型 */
				CSTR type;
				/** 配件名称 */
				CSTR name;
			}) apAlarms;
			/** 设备序列号 */
			CSTR deviceId;
		}) alarmList;
 
	} data;

} GetLastestAlarmMessageResponse;

C_API GetLastestAlarmMessageResponse *LCOPENAPI_INIT(GetLastestAlarmMessageResponse);

#endif
