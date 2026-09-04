/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_GetDeviceLatestAlarmMessage_H_
#define _HSVIEW_CLIENT_API_cloudMessage_GetDeviceLatestAlarmMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
按设备通道、配件获取最近一条消息

备注：
channelIds、apIds为空数组，平台默认不处理，返回的结果中chnAlarms、apAlarms对应为空数组。

报警类型type参考：[设备和配件消息类型定义](http://paas.dahuatech.com/wiki/?p=%2FSaaS%2F%E6%B6%88%E6%81%AF%E7%B1%BB%E5%9E%8B%E5%8F%8A%E6%8E%A8%E9%80%81%E5%8D%8F%E8%AE%AE%2F%E8%AE%BE%E5%A4%87%E5%92%8C%E9%85%8D%E4%BB%B6%E6%B6%88%E6%81%AF%E7%B1%BB%E5%9E%8B%E5%AE%9A%E4%B9%89.md&s=pj)

【使用平台账号签名】
 */

typedef struct cloudMessage_GetDeviceLatestAlarmMessageRequest 
{
	HsviewRequest base;

	struct cloudMessage_GetDeviceLatestAlarmMessageRequestData
	{
		
		/** define a list with struct of cloudMessage_GetDeviceLatestAlarmMessageRequestData_DeviceListElement */
		DECLARE_LIST(struct cloudMessage_GetDeviceLatestAlarmMessageRequestData_DeviceListElement
		{
			/** 配件设备序列号 */
			DECLARE_LIST(CSTR) apIds;
			/** 通道号 */
			DECLARE_LIST(CSTR) channelIds;
			/** 设备序列号 */
			CSTR deviceId;
		}) deviceList;

	} data;

} cloudMessage_GetDeviceLatestAlarmMessageRequest;

C_API cloudMessage_GetDeviceLatestAlarmMessageRequest *HSAPI_INIT(cloudMessage_GetDeviceLatestAlarmMessageRequest);

typedef struct cloudMessage_GetDeviceLatestAlarmMessageResponse 
{
	HsviewResponse base;

	struct cloudMessage_GetDeviceLatestAlarmMessageResponseData
	{
		
		/** define a list with struct of cloudMessage_GetDeviceLatestAlarmMessageResponseData_AlarmListElement */
		DECLARE_LIST(struct cloudMessage_GetDeviceLatestAlarmMessageResponseData_AlarmListElement
		{
			/** define a list with struct of cloudMessage_GetDeviceLatestAlarmMessageResponseData_AlarmListElement_ChnAlarmsElement */
			DECLARE_LIST(struct cloudMessage_GetDeviceLatestAlarmMessageResponseData_AlarmListElement_ChnAlarmsElement
			{
				/** 报警图片url */
				DECLARE_LIST(CSTR) picUrl;
				/** [int]未读消息数量 */
				int unread;
				/** [long]告警消息ID */
				int64 alarmId;
				/** 设备本地报警时间,格式yyyyMMddTHHmmss */
				CSTR time;
				/** define a list with struct of cloudMessage_GetDeviceLatestAlarmMessageResponseData_AlarmListElement_ChnAlarmsElement_DetectElement */
				DECLARE_LIST(struct cloudMessage_GetDeviceLatestAlarmMessageResponseData_AlarmListElement_ChnAlarmsElement_DetectElement
				{
					/** [O]人形结果，0-不准确 1-准确 */
					CSTR result;
					/** 检测类型，1-AI智能检测(人形)；2-物体识别; 3-AI智能检测(车辆)； 4-AI智能检测(宠物) */
					CSTR type;
				}) detect;
				/** 对象类型 */
				CSTR objectType;
				/** struct of cloudMessage_GetDeviceLatestAlarmMessageResponseData_AlarmListElement_ChnAlarmsElement_Skip */
				struct cloudMessage_GetDeviceLatestAlarmMessageResponseData_AlarmListElement_ChnAlarmsElement_Skip {
					/** 跳转界面 */
					CSTR view;
					/** 附加执行动作(若无为空数组) */
					DECLARE_LIST(CSTR) action;
				} skip;
				/** [int]报警类型映射值 */
				int typeInt;
				/** 设备通道或者报警消息的缩略图URL */
				CSTR thumbUrl;
				/** [O]默认本地录像播放时长 */
				CSTR lrecordStopTime;
				/** String类型的告警消息ID,海外pc使用 */
				CSTR alarmIdStr;
				/** 展示文案 */
				CSTR title;
				/** [O]消息唯一标识，用于查询云录像 */
				CSTR token;
				/** 报警类型 */
				CSTR type;
				/** [O]备注字段。如果是低电量，填写电量百分比0-100，如果涉及门锁钥匙，填写钥匙名称。 */
				CSTR remark;
				/** 通道号 */
				CSTR channelId;
				/** [O]检测结果类型定义如下，人形：persons,宠物：pets,车辆：vehicles */
				DECLARE_LIST(CSTR) smartDetectList;
				/** 通道名称 */
				CSTR name;
			}) chnAlarms;
			/** define a list with struct of cloudMessage_GetDeviceLatestAlarmMessageResponseData_AlarmListElement_ApAlarmsElement */
			DECLARE_LIST(struct cloudMessage_GetDeviceLatestAlarmMessageResponseData_AlarmListElement_ApAlarmsElement
			{
				/** [bool]是否存在联动消息 */
				BOOL hasLinkage;
				/** 报警类型 */
				CSTR type;
				/** [int]未读消息数量 */
				int unread;
				/** [long]告警消息ID */
				int64 alarmId;
				/** 配件名称 */
				CSTR name;
				/** 配件类型 */
				CSTR apType;
				/** struct of cloudMessage_GetDeviceLatestAlarmMessageResponseData_AlarmListElement_ApAlarmsElement_Skip */
				struct cloudMessage_GetDeviceLatestAlarmMessageResponseData_AlarmListElement_ApAlarmsElement_Skip {
					/** 跳转界面 */
					CSTR view;
					/** 附加执行动作(若无为空数组) */
					DECLARE_LIST(CSTR) action;
				} skip;
				/** 展示文案 */
				CSTR title;
				/** 配件ID */
				CSTR apId;
				/** 设备本地报警时间,格式yyyyMMddTHHmmss */
				CSTR time;
			}) apAlarms;
			/** 设备序列号 */
			CSTR deviceId;
		}) alarmList;
 
	} data;

} cloudMessage_GetDeviceLatestAlarmMessageResponse;

C_API cloudMessage_GetDeviceLatestAlarmMessageResponse *HSAPI_INIT(cloudMessage_GetDeviceLatestAlarmMessageResponse);

#endif
