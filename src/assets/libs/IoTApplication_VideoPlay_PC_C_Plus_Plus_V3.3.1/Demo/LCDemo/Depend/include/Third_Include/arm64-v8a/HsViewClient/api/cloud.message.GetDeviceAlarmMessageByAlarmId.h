/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_GetDeviceAlarmMessageByAlarmId_H_
#define _HSVIEW_CLIENT_API_cloudMessage_GetDeviceAlarmMessageByAlarmId_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
按报警消息Id查询报警消息详情。

报警类型type参考：[设备和配件消息类型定义](http://paas.dahuatech.com/wiki/?p=%2FSaaS%2F%E6%B6%88%E6%81%AF%E7%B1%BB%E5%9E%8B%E5%8F%8A%E6%8E%A8%E9%80%81%E5%8D%8F%E8%AE%AE%2F%E8%AE%BE%E5%A4%87%E5%92%8C%E9%85%8D%E4%BB%B6%E6%B6%88%E6%81%AF%E7%B1%BB%E5%9E%8B%E5%AE%9A%E4%B9%89.md&s=pj)

【使用平台账号签名】
 */

typedef struct cloudMessage_GetDeviceAlarmMessageByAlarmIdRequest 
{
	HsviewRequest base;

	struct cloudMessage_GetDeviceAlarmMessageByAlarmIdRequestData
	{
		
		/** [long]告警消息ID */
		int64 alarmId;
		/** 通道号 */
		CSTR channelId;
		/** 报警类型 */
		CSTR type;
		/** 设备ID */
		CSTR deviceId;

	} data;

} cloudMessage_GetDeviceAlarmMessageByAlarmIdRequest;

C_API cloudMessage_GetDeviceAlarmMessageByAlarmIdRequest *HSAPI_INIT(cloudMessage_GetDeviceAlarmMessageByAlarmIdRequest);

typedef struct cloudMessage_GetDeviceAlarmMessageByAlarmIdResponse 
{
	HsviewResponse base;

	struct cloudMessage_GetDeviceAlarmMessageByAlarmIdResponseData
	{
		
		/** struct of cloudMessage_GetDeviceAlarmMessageByAlarmIdResponseData_Alarm */
		struct cloudMessage_GetDeviceAlarmMessageByAlarmIdResponseData_Alarm {
			/** [bool][O]是否存在设备联动消息 */
			BOOL hasLinkage;
			/** 报警类型 */
			CSTR type;
			/** 报警图片url */
			DECLARE_LIST(CSTR) picUrl;
			/** 缩略图URL */
			CSTR thumbUrl;
			/** 报警消息筛选大类，一个报警消息属于多种大类时用逗号隔开；人形报警：humanAlarm；人脸报警：faceAlarm；车辆报警：carAlarm；异常音报警：abSoundAlarm；动检：motionAlarm；其他：other */
			CSTR labelType;
			/** [O]备注字段。如果是低电量，填写电量百分比0-100，如果涉及门锁钥匙，填写钥匙名称。 */
			CSTR remark;
			/** struct of cloudMessage_GetDeviceAlarmMessageByAlarmIdResponseData_Alarm_Skip */
			struct cloudMessage_GetDeviceAlarmMessageByAlarmIdResponseData_Alarm_Skip {
				/** 跳转界面 */
				CSTR view;
				/** 附加执行动作(若无为空数组) */
				DECLARE_LIST(CSTR) action;
			} skip;
			/** [long]告警消息ID */
			int64 alarmId;
			/** [O]mute 代表消音报警类型,存在多个子类型用逗号隔开 */
			CSTR subType;
			/** 设备本地时间，yyyyMMddTHHmmss格式 */
			CSTR time;
			/** define a list with struct of cloudMessage_GetDeviceAlarmMessageByAlarmIdResponseData_Alarm_DetectElement */
			DECLARE_LIST(struct cloudMessage_GetDeviceAlarmMessageByAlarmIdResponseData_Alarm_DetectElement
			{
				/** [O]人形结果，0-不准确 1-准确 */
				CSTR result;
				/** 检测类型，1-AI智能检测(人形)；2-物体识别; 3-AI智能检测(车辆)； 4-AI智能检测(宠物) */
				CSTR type;
			}) detect;
			/** 展示文案 */
			CSTR title;
			/** [O]消息唯一标识，用于查询云录像 */
			CSTR token;
			/** [O]默认本地录像播放时长 */
			CSTR lrecordStopTime;
			/** [O]检测结果类型定义如下，人形：persons,宠物：pets,车辆：vehicles */
			DECLARE_LIST(CSTR) smartDetectList;
		} alarm;
 
	} data;

} cloudMessage_GetDeviceAlarmMessageByAlarmIdResponse;

C_API cloudMessage_GetDeviceAlarmMessageByAlarmIdResponse *HSAPI_INIT(cloudMessage_GetDeviceAlarmMessageByAlarmIdResponse);

#endif
