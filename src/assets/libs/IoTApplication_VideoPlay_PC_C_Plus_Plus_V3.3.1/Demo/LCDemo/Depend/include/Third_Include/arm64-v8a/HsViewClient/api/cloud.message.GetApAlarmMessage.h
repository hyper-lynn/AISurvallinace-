/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_GetApAlarmMessage_H_
#define _HSVIEW_CLIENT_API_cloudMessage_GetApAlarmMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
按条件查询报警记录，倒序排序。

消息查询时，以beginTime和endTime为最大限制范围。
beginAlarmId、endAlarmId，在不为-1时，消息alarmId取值范围为：endAlarmId < alarmId < beginAlarmId。

报警类型type参考：[设备和配件消息类型定义](http://paas.dahuatech.com/wiki/?p=%2FSaaS%2F%E6%B6%88%E6%81%AF%E7%B1%BB%E5%9E%8B%E5%8F%8A%E6%8E%A8%E9%80%81%E5%8D%8F%E8%AE%AE%2F%E8%AE%BE%E5%A4%87%E5%92%8C%E9%85%8D%E4%BB%B6%E6%B6%88%E6%81%AF%E7%B1%BB%E5%9E%8B%E5%AE%9A%E4%B9%89.md&s=pj)

【使用平台账号签名】
 */

typedef struct cloudMessage_GetApAlarmMessageRequest 
{
	HsviewRequest base;

	struct cloudMessage_GetApAlarmMessageRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** [long]开始alarmId，-1表示不限制，以startTime时间为准 */
		int64 beginAlarmId;
		/** [int]分页查询的数量，最大128 */
		int count;
		/** 设备本地结束时间，yyyyMMddTHHmmss格式，决定下限 */
		CSTR endTime;
		/** 设备本地开始时间，yyyyMMddTHHmmss格式，决定上限 */
		CSTR beginTime;
		/** [long]结束alarmId，-1表示不限制，以endTime时间为准 */
		int64 endAlarmId;
		/** 网关设备ID */
		CSTR deviceId;

	} data;

} cloudMessage_GetApAlarmMessageRequest;

C_API cloudMessage_GetApAlarmMessageRequest *HSAPI_INIT(cloudMessage_GetApAlarmMessageRequest);

typedef struct cloudMessage_GetApAlarmMessageResponse 
{
	HsviewResponse base;

	struct cloudMessage_GetApAlarmMessageResponseData
	{
		
		/** define a list with struct of cloudMessage_GetApAlarmMessageResponseData_AlarmsElement */
		DECLARE_LIST(struct cloudMessage_GetApAlarmMessageResponseData_AlarmsElement
		{
			/** [bool]是否存在联动消息 */
			BOOL hasLinkage;
			/** 报警类型 */
			CSTR type;
			/** [O]备注字段。如果是低电量，填写电量百分比0-100。 */
			CSTR remark;
			/** [long]消息ID */
			int64 alarmId;
			/** 设备本地时间，yyyyMMddTHHmmss格式 */
			CSTR time;
			/** struct of cloudMessage_GetApAlarmMessageResponseData_AlarmsElement_Skip */
			struct cloudMessage_GetApAlarmMessageResponseData_AlarmsElement_Skip {
				/** 跳转界面 */
				CSTR view;
				/** 附加执行动作(若无为空数组) */
				DECLARE_LIST(CSTR) action;
			} skip;
			/** 展示文案 */
			CSTR title;
			/** [O]mute 代表消音报警类型,存在多个子类型用逗号隔开 */
			CSTR subType;
			/** [O]SOS报警消息，服务器保存时间。UTC时间，yyyyMMddTHHmmssZ格式。 */
			CSTR serverTime;
			/** [bool][O]SOS报警状态，true表示停止 */
			BOOL isStopSosAlarm;
		}) alarms;
		/** 配件名称 */
		CSTR name;
		/** 配件类型 */
		CSTR apType;
 
	} data;

} cloudMessage_GetApAlarmMessageResponse;

C_API cloudMessage_GetApAlarmMessageResponse *HSAPI_INIT(cloudMessage_GetApAlarmMessageResponse);

#endif
