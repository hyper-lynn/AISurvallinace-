/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_GetDeviceLinkageMessage_H_
#define _HSVIEW_CLIENT_API_cloudMessage_GetDeviceLinkageMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据消息id查询联动的消息列表

报警类型type参考：[设备和配件消息类型定义](http://paas.dahuatech.com/wiki/?p=%2FSaaS%2F%E6%B6%88%E6%81%AF%E7%B1%BB%E5%9E%8B%E5%8F%8A%E6%8E%A8%E9%80%81%E5%8D%8F%E8%AE%AE%2F%E8%AE%BE%E5%A4%87%E5%92%8C%E9%85%8D%E4%BB%B6%E6%B6%88%E6%81%AF%E7%B1%BB%E5%9E%8B%E5%AE%9A%E4%B9%89.md&s=pj)

【使用平台账号签名】
 */

typedef struct cloudMessage_GetDeviceLinkageMessageRequest 
{
	HsviewRequest base;

	struct cloudMessage_GetDeviceLinkageMessageRequestData
	{
		
		/** [long]配件告警消息id */
		int64 alarmId;
		/** 设备通道号 当设备级  无通道号 为-1 */
		CSTR channelId;
		/** 网关设备序列号 */
		CSTR deviceId;

	} data;

} cloudMessage_GetDeviceLinkageMessageRequest;

C_API cloudMessage_GetDeviceLinkageMessageRequest *HSAPI_INIT(cloudMessage_GetDeviceLinkageMessageRequest);

typedef struct cloudMessage_GetDeviceLinkageMessageResponse 
{
	HsviewResponse base;

	struct cloudMessage_GetDeviceLinkageMessageResponseData
	{
		
		/** define a list with struct of cloudMessage_GetDeviceLinkageMessageResponseData_AlarmsElement */
		DECLARE_LIST(struct cloudMessage_GetDeviceLinkageMessageResponseData_AlarmsElement
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

} cloudMessage_GetDeviceLinkageMessageResponse;

C_API cloudMessage_GetDeviceLinkageMessageResponse *HSAPI_INIT(cloudMessage_GetDeviceLinkageMessageResponse);

#endif
