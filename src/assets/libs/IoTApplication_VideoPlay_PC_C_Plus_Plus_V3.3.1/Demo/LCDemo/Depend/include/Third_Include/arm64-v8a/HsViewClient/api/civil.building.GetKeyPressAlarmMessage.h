/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetKeyPressAlarmMessage_H_
#define _HSVIEW_CLIENT_API_GetKeyPressAlarmMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 【按条件查询门禁按键报警消息】

 */

typedef struct GetKeyPressAlarmMessageRequest 
{
	HsviewRequest base;

	struct GetKeyPressAlarmMessageRequestData
	{
		
		/** [long]从该消息ID开始查询。若要从最新开始查，填-1 */
		int64 alarmId;
		/** [int]需要查的最大条数 */
		int count;
		/** [long]结束时间。Unix时间（单位秒），0表示最晚时间 */
		int64 endTime;
		/** [long]开始时间。Unix时间（单位秒），0表示最早时间 */
		int64 beginTime;
		/** 查该设备ID的报警消息。必须 */
		CSTR deviceId;

	} data;

} GetKeyPressAlarmMessageRequest;

C_API GetKeyPressAlarmMessageRequest *HSAPI_INIT(GetKeyPressAlarmMessageRequest);

typedef struct GetKeyPressAlarmMessageResponse 
{
	HsviewResponse base;

	struct GetKeyPressAlarmMessageResponseData
	{
		
		/** define a list with struct of GetKeyPressAlarmMessageResponseData_AlarmsElement */
		DECLARE_LIST(struct GetKeyPressAlarmMessageResponseData_AlarmsElement
		{
			/** [long]消息ID */
			int64 alarmId;
			/** 设备名称 */
			CSTR name;
			/** [long]报警时间UNIX时间戳秒 */
			int64 time;
		}) alarms;
 
	} data;

} GetKeyPressAlarmMessageResponse;

C_API GetKeyPressAlarmMessageResponse *HSAPI_INIT(GetKeyPressAlarmMessageResponse);

#endif
