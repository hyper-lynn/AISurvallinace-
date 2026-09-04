/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_AlarmMessageList_H_
#define _LC_OPENAPI_CLIENT_AlarmMessageList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
按设备通道分页查询报警消息
 */

typedef struct AlarmMessageListRequest 
{
	LCOpenApiRequest base;

	struct AlarmMessageListRequestData
	{
		
		/** 设备本地结束时间 */
		CSTR endTime;
		/** [long]结束alarmId，-1表示不限制，以endTime时间为准 */
		int64 endAlarmId;
		/** 设备序列号 */
		CSTR deviceId;
		/** [long]开始alarmId，-1表示不限制，以beginTime时间为准 */
		int64 beginAlarmId;
		/** 消息类型 */
		CSTR alarmType;
		/** [int]分页查询的数量，最大128 */
		int count;
		/** 设备本地开始时间 */
		CSTR beginTime;
		/** 授权token */
		CSTR token;
		/** 设备通道号 */
		CSTR channelId;

	} data;

} AlarmMessageListRequest;

C_API AlarmMessageListRequest *LCOPENAPI_INIT(AlarmMessageListRequest);

typedef struct AlarmMessageListResponse 
{
	LCOpenApiResponse base;

	struct AlarmMessageListResponseData
	{
		
		/** 通道名称 */
		CSTR name;
		/** define a list with struct of AlarmMessageListResponseData_AlarmsElement */
		DECLARE_LIST(struct AlarmMessageListResponseData_AlarmsElement
		{
			/** [bool][O]是否存在设备联动消息 */
			BOOL hasLinkage;
			/** 报警类型 */
			CSTR type;
			/** 报警图片url */
			DECLARE_LIST(CSTR) picUrl;
			/** 缩略图URL */
			CSTR thumbUrl;
			/** [O]默认本地录像播放时长 */
			CSTR lrecordStopTime;
			/** [O]备注字段。如果是低电量，填写电量百分比0-100，如果涉及门锁钥匙，填写钥匙名称 */
			CSTR remark;
			/** [long]告警消息ID */
			int64 alarmId;
			/** [O]消息唯一标识，用于查询云录像 */
			CSTR token;
			/** 设备本地时间，yyyyMMddTHHmmss格式 */
			CSTR time;
		}) alarms;
 
	} data;

} AlarmMessageListResponse;

C_API AlarmMessageListResponse *LCOPENAPI_INIT(AlarmMessageListResponse);

#endif
