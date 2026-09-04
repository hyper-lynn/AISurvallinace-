/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAccessAlarmMessage_H_
#define _HSVIEW_CLIENT_API_GetAccessAlarmMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 【按条件查询门禁开门报警消息】
  method是开门方式 0：密码开门 1：刷卡开门 4远程开锁5开锁键开锁13胁迫密码开门
 */

typedef struct GetAccessAlarmMessageRequest 
{
	HsviewRequest base;

	struct GetAccessAlarmMessageRequestData
	{
		
		/** [long]从该消息ID开始查询。若要从最新开始查，填-1 */
		int64 alarmId;
		/** [int]需要查的最大条数 */
		int count;
		/** [int]开门方式，-1表示所有开门方式 */
		int method;
		/** [long]结束时间。Unix时间（单位秒），0表示最晚时间 */
		int64 endTime;
		/** [long]开始时间。Unix时间（单位秒），0表示最早时间 */
		int64 beginTime;
		/** 开门结果，Success成功，Fail失败，All所有 */
		CSTR result;
		/** 查该设备Id的报警消息。必须 */
		CSTR deviceId;

	} data;

} GetAccessAlarmMessageRequest;

C_API GetAccessAlarmMessageRequest *HSAPI_INIT(GetAccessAlarmMessageRequest);

typedef struct GetAccessAlarmMessageResponse 
{
	HsviewResponse base;

	struct GetAccessAlarmMessageResponseData
	{
		
		/** define a list with struct of GetAccessAlarmMessageResponseData_AlarmsElement */
		DECLARE_LIST(struct GetAccessAlarmMessageResponseData_AlarmsElement
		{
			/** [long]消息ID */
			int64 alarmId;
			/** [long]报警时间UNIX时间戳秒 */
			int64 time;
			/** [int]开门方式，-1表示所有开门方式,0密码开锁1刷卡开锁4远程开锁5开锁键开锁13胁迫密码开门 */
			int method;
			/** 开门结果，Success成功，Fail失败 */
			CSTR result;
			/** 设备或通道的名称 */
			CSTR name;
		}) alarms;
 
	} data;

} GetAccessAlarmMessageResponse;

C_API GetAccessAlarmMessageResponse *HSAPI_INIT(GetAccessAlarmMessageResponse);

#endif
