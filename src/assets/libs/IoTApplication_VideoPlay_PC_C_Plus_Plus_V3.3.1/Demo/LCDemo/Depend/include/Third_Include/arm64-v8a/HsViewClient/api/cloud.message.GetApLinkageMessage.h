/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_GetApLinkageMessage_H_
#define _HSVIEW_CLIENT_API_cloudMessage_GetApLinkageMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据消息id查询联动的消息列表

报警类型type参考：[设备和配件消息类型定义](http://paas.dahuatech.com/wiki/?p=%2FSaaS%2F%E6%B6%88%E6%81%AF%E7%B1%BB%E5%9E%8B%E5%8F%8A%E6%8E%A8%E9%80%81%E5%8D%8F%E8%AE%AE%2F%E8%AE%BE%E5%A4%87%E5%92%8C%E9%85%8D%E4%BB%B6%E6%B6%88%E6%81%AF%E7%B1%BB%E5%9E%8B%E5%AE%9A%E4%B9%89.md&s=pj)

【使用平台账号签名】
 */

typedef struct cloudMessage_GetApLinkageMessageRequest 
{
	HsviewRequest base;

	struct cloudMessage_GetApLinkageMessageRequestData
	{
		
		/** [long]配件告警消息id */
		int64 alarmId;
		/** 配件ID */
		CSTR apId;
		/** 网关设备序列号 */
		CSTR deviceId;

	} data;

} cloudMessage_GetApLinkageMessageRequest;

C_API cloudMessage_GetApLinkageMessageRequest *HSAPI_INIT(cloudMessage_GetApLinkageMessageRequest);

typedef struct cloudMessage_GetApLinkageMessageResponse 
{
	HsviewResponse base;

	struct cloudMessage_GetApLinkageMessageResponseData
	{
		
		/** define a list with struct of cloudMessage_GetApLinkageMessageResponseData_AlarmsElement */
		DECLARE_LIST(struct cloudMessage_GetApLinkageMessageResponseData_AlarmsElement
		{
			/** 报警类型 */
			CSTR type;
			/** 报警图片url */
			DECLARE_LIST(CSTR) picUrl;
			/** 缩略图URL */
			CSTR thumbUrl;
			/** 联动设备ID */
			CSTR deviceId;
			/** [long]联动消息ID */
			int64 alarmId;
			/** 通道名称 */
			CSTR name;
			/** 展示文案 */
			CSTR title;
			/** 联动设备通道号 */
			CSTR channelId;
			/** [O]消息唯一标识，用于查询云录像 */
			CSTR token;
			/** 设备本地时间，yyyyMMddTHHmmss格式 */
			CSTR time;
		}) alarms;
 
	} data;

} cloudMessage_GetApLinkageMessageResponse;

C_API cloudMessage_GetApLinkageMessageResponse *HSAPI_INIT(cloudMessage_GetApLinkageMessageResponse);

#endif
