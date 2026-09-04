/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetLinkageMessage_H_
#define _HSVIEW_CLIENT_API_GetLinkageMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据消息id查询联动的消息列表

报警类型定义：
详见[报警类型说明](../推送/报警类型说明.md)

【使用平台账号签名】
 */

typedef struct GetLinkageMessageRequest 
{
	HsviewRequest base;

	struct GetLinkageMessageRequestData
	{
		
		/** [long]告警消息id */
		int64 alarmId;

	} data;

} GetLinkageMessageRequest;

C_API GetLinkageMessageRequest *HSAPI_INIT(GetLinkageMessageRequest);

typedef struct GetLinkageMessageResponse 
{
	HsviewResponse base;

	struct GetLinkageMessageResponseData
	{
		
		/** define a list with struct of GetLinkageMessageResponseData_AlarmsElement */
		DECLARE_LIST(struct GetLinkageMessageResponseData_AlarmsElement
		{
			/** [int]报警类型 */
			int type;
			/** 缩略图URL */
			CSTR thumbUrl;
			/** 备注字段。如果是低电量，填写电量百分比。 */
			CSTR remark;
			/** 设备ID */
			CSTR deviceId;
			/** [long]联动消息ID */
			int64 alarmId;
			/** 通道所接的设备ID */
			CSTR channelDeviceId;
			/** [long]报警时间UNIX时间戳秒 */
			int64 time;
			/** [int]是否已读。0未读，1已读 */
			int readFlag;
			/** 报警图片url */
			DECLARE_LIST(CSTR) picurlArray;
			/** 通道号 */
			CSTR channelId;
			/** 设备或通道的名称 */
			CSTR name;
			/** 报警时设备本地时间，格式如2014-12-12 12:12:12 */
			CSTR localDate;
		}) alarms;
 
	} data;

} GetLinkageMessageResponse;

C_API GetLinkageMessageResponse *HSAPI_INIT(GetLinkageMessageResponse);

#endif
