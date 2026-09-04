/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_DeleteApAlarmMessage_H_
#define _HSVIEW_CLIENT_API_cloudMessage_DeleteApAlarmMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据设备序列号和配件号删除指定消息id的报警信息。

当alarmIds为空数组，表示删除设备序列号和配件号下所有消息。
当alarmIds为空数组，apId为空字符串时，表示删除网关设备和网关关联的所有配件的报警信息。

【使用平台账号签名】
 */

typedef struct cloudMessage_DeleteApAlarmMessageRequest 
{
	HsviewRequest base;

	struct cloudMessage_DeleteApAlarmMessageRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** [long]告警ID列表 */
		DECLARE_LIST(int64) alarmIds;
		/** 网关设备ID */
		CSTR deviceId;

	} data;

} cloudMessage_DeleteApAlarmMessageRequest;

C_API cloudMessage_DeleteApAlarmMessageRequest *HSAPI_INIT(cloudMessage_DeleteApAlarmMessageRequest);

typedef struct cloudMessage_DeleteApAlarmMessageResponse 
{
	HsviewResponse base;

	struct cloudMessage_DeleteApAlarmMessageResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} cloudMessage_DeleteApAlarmMessageResponse;

C_API cloudMessage_DeleteApAlarmMessageResponse *HSAPI_INIT(cloudMessage_DeleteApAlarmMessageResponse);

#endif
