/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAlarmStatistics_H_
#define _HSVIEW_CLIENT_API_GetAlarmStatistics_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询设备报警统计数据

typs报警类型：
	0：人体红外
	1：动态检测
	2：未知告警
	3：低电压告警
	4：配件人体红外检测
	5：移动感应器发生移动事件
	6：移动感应器长时间未发生移动事件
	
	types是个int类型数组，比如如果打算一次性统计移动感应器报警事件（移动感应和长时间未移动感应相加数据），则可以types[0u] =5;types[1u]= 6

alarmStatistics：报警次数统计数据。
period: 当前仅支持 “24h”, 表示统计最近24小时的数据
unit:   当前仅支持”1h”,   表示一个小时为单位的统计。
【需要使用平台账号签名】
 */

typedef struct GetAlarmStatisticsRequest 
{
	HsviewRequest base;

	struct GetAlarmStatisticsRequestData
	{
		
		/** struct of GetAlarmStatisticsRequestData_StatisticsMode */
		struct GetAlarmStatisticsRequestData_StatisticsMode {
			/** 统计周期，24h表示是最近24小时的 */
			CSTR period;
			/** 统计单位，1h 表示每个小时为统计单位 */
			CSTR unit;
		} statisticsMode;
		/** 通道号（可填通道所接设备ID），留空表示查询设备 */
		CSTR channelId;
		/** [int]类型，每个元素表示一种报警类型 */
		DECLARE_LIST(int) types;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetAlarmStatisticsRequest;

C_API GetAlarmStatisticsRequest *HSAPI_INIT(GetAlarmStatisticsRequest);

typedef struct GetAlarmStatisticsResponse 
{
	HsviewResponse base;

	struct GetAlarmStatisticsResponseData
	{
		
		/** [int] 每个元素代表每个统计单位的次数 */
		DECLARE_LIST(int) alarmStatistics;
 
	} data;

} GetAlarmStatisticsResponse;

C_API GetAlarmStatisticsResponse *HSAPI_INIT(GetAlarmStatisticsResponse);

#endif
