/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_GetDeviceAlarmMessage_H_
#define _HSVIEW_CLIENT_API_cloudMessage_GetDeviceAlarmMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
按设备通道分页查询报警消息。

消息查询时，以beginTime和endTime为最大限制范围。
beginAlarmId、endAlarmId，在不为-1时，消息alarmId取值范围为：endAlarmId < alarmId < beginAlarmId。

报警类型type参考：[设备和配件消息类型定义](http://paas.dahuatech.com/wiki/?p=%2FSaaS%2F%E6%B6%88%E6%81%AF%E7%B1%BB%E5%9E%8B%E5%8F%8A%E6%8E%A8%E9%80%81%E5%8D%8F%E8%AE%AE%2F%E8%AE%BE%E5%A4%87%E5%92%8C%E9%85%8D%E4%BB%B6%E6%B6%88%E6%81%AF%E7%B1%BB%E5%9E%8B%E5%AE%9A%E4%B9%89.md&s=pj)

【使用平台账号签名】
 */

typedef struct cloudMessage_GetDeviceAlarmMessageRequest 
{
	HsviewRequest base;

	struct cloudMessage_GetDeviceAlarmMessageRequestData
	{
		
		/** 设备本地结束时间，yyyyMMddTHHmmss格式，决定下限 */
		CSTR endTime;
		/** [long]结束alarmId，-1表示不限制，以endTime时间为准 */
		int64 endAlarmId;
		/** [O]开始alarmId,-1表示不限制，以startTime时间为准,海外pc客户端使用，若传值已该字段为准 */
		CSTR beginAlarmIdStr;
		/** 设备ID */
		CSTR deviceId;
		/** [long]开始alarmId，-1表示不限制，以startTime时间为准 */
		int64 beginAlarmId;
		/** [O]消息类型 */
		CSTR alarmType;
		/** [int]分页查询的数量，最大128 */
		int count;
		/** 设备本地开始时间，yyyyMMddTHHmmss格式，决定上限 */
		CSTR beginTime;
		/** [O]结束alarmId，-1表示不限制，以endTime时间为准,海外pc客户端使用，若传值已该字段为准 */
		CSTR endAlarmIdStr;
		/** 通道号 */
		CSTR channelId;

	} data;

} cloudMessage_GetDeviceAlarmMessageRequest;

C_API cloudMessage_GetDeviceAlarmMessageRequest *HSAPI_INIT(cloudMessage_GetDeviceAlarmMessageRequest);

typedef struct cloudMessage_GetDeviceAlarmMessageResponse 
{
	HsviewResponse base;

	struct cloudMessage_GetDeviceAlarmMessageResponseData
	{
		
		/** 通道名称 */
		CSTR name;
		/** define a list with struct of cloudMessage_GetDeviceAlarmMessageResponseData_AlarmsElement */
		DECLARE_LIST(struct cloudMessage_GetDeviceAlarmMessageResponseData_AlarmsElement
		{
			/** [bool][O]是否存在设备联动消息 */
			BOOL hasLinkage;
			/** 报警图片url */
			DECLARE_LIST(CSTR) picUrl;
			/** 报警消息筛选大类，一个报警消息属于多种大类时用逗号隔开；人形报警：humanAlarm；人脸报警：faceAlarm；车辆报警：carAlarm；异常音报警：abSoundAlarm;动检：motionAlarm；其他：other */
			CSTR labelType;
			/** [long]告警消息ID */
			int64 alarmId;
			/** 设备本地时间，yyyyMMddTHHmmss格式 */
			CSTR time;
			/** define a list with struct of cloudMessage_GetDeviceAlarmMessageResponseData_AlarmsElement_DetectElement */
			DECLARE_LIST(struct cloudMessage_GetDeviceAlarmMessageResponseData_AlarmsElement_DetectElement
			{
				/** [O]人形结果，0-不准确 1-准确 */
				CSTR result;
				/** 检测类型，1-AI智能检测(人形)；2-物体识别; 3-AI智能检测(车辆)； 4-AI智能检测(宠物) */
				CSTR type;
			}) detect;
			/** 对象类型 */
			CSTR objectType;
			/** struct of cloudMessage_GetDeviceAlarmMessageResponseData_AlarmsElement_Skip */
			struct cloudMessage_GetDeviceAlarmMessageResponseData_AlarmsElement_Skip {
				/** 跳转界面 */
				CSTR view;
				/** 附加执行动作(若无为空数组) */
				DECLARE_LIST(CSTR) action;
			} skip;
			/** 报警类型 */
			CSTR type;
			/** 缩略图URL */
			CSTR thumbUrl;
			/** [O]默认本地录像播放时长 */
			CSTR lrecordStopTime;
			/** [O]备注字段。如果是低电量，填写电量百分比0-100，如果涉及门锁钥匙，填写钥匙名称 */
			CSTR remark;
			/** [int][O]报警类型映射值 */
			int typeInt;
			/** [O]mute 代表消音报警类型,存在多个子类型用逗号隔开 */
			CSTR subType;
			/** [O]消息唯一标识，用于查询云录像 */
			CSTR token;
			/** [bool][O]物体识别-陌生人报警(smartStrangerAppear)的陌生人人脸是否可以加入人脸库 */
			BOOL isVeriFace;
			/** 展示文案 */
			CSTR title;
			/** 通道号 */
			CSTR channelId;
			/** [O]检测结果类型定义如下，人形：persons,宠物：pets,车辆：vehicles */
			DECLARE_LIST(CSTR) smartDetectList;
			/** [O]String类型的告警消息ID，海外pc客户端使用 */
			CSTR alarmIdStr;
		}) alarms;
 
	} data;

} cloudMessage_GetDeviceAlarmMessageResponse;

C_API cloudMessage_GetDeviceAlarmMessageResponse *HSAPI_INIT(cloudMessage_GetDeviceAlarmMessageResponse);

#endif
