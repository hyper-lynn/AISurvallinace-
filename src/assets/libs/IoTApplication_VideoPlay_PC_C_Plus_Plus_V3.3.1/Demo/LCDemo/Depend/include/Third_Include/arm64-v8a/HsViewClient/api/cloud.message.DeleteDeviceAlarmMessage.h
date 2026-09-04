/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_DeleteDeviceAlarmMessage_H_
#define _HSVIEW_CLIENT_API_cloudMessage_DeleteDeviceAlarmMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据设备序列号和通道号删除指定消息id的报警信息。

alarmIds为空数组，表示删除设备序列号和通道号下所有消息。

【使用平台账号签名】
 */

typedef struct cloudMessage_DeleteDeviceAlarmMessageRequest 
{
	HsviewRequest base;

	struct cloudMessage_DeleteDeviceAlarmMessageRequestData
	{
		
		/** [O]需要删除的消息ID,海外pc使用,非必须 */
		DECLARE_LIST(CSTR) alarmIdsStr;
		/** 通道号 */
		CSTR channelId;
		/** [long]需要删除的消息ID */
		DECLARE_LIST(int64) alarmIds;
		/** 设备ID */
		CSTR deviceId;

	} data;

} cloudMessage_DeleteDeviceAlarmMessageRequest;

C_API cloudMessage_DeleteDeviceAlarmMessageRequest *HSAPI_INIT(cloudMessage_DeleteDeviceAlarmMessageRequest);

typedef struct cloudMessage_DeleteDeviceAlarmMessageResponse 
{
	HsviewResponse base;

	struct cloudMessage_DeleteDeviceAlarmMessageResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} cloudMessage_DeleteDeviceAlarmMessageResponse;

C_API cloudMessage_DeleteDeviceAlarmMessageResponse *HSAPI_INIT(cloudMessage_DeleteDeviceAlarmMessageResponse);

#endif
