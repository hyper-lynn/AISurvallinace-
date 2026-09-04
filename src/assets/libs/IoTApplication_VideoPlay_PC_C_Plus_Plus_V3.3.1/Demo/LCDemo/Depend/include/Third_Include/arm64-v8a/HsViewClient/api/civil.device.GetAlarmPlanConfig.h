/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAlarmPlanConfig_H_
#define _HSVIEW_CLIENT_API_GetAlarmPlanConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备的报警计划配置。

period：生效的周期
		Monday：每周一
		Tuesday：每周二
		Wednesday：每周三
		Thursday：每周四
		Friday：每周五
		Saturday：每周六
		Sunday：每周日

	beginTime和endTime：生效的起止时间,时间格式为%H:%M:%S，endTime必须小于beginTime。
	
[更新记录] 2017.4.5 修改协议备注, period不支持once、workday、holiday。

【使用平台账号签名】
 */

typedef struct GetAlarmPlanConfigRequest 
{
	HsviewRequest base;

	struct GetAlarmPlanConfigRequestData
	{
		
		/** 通道号，如果不填，则获取该设备所有通道的报警计划配置。 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetAlarmPlanConfigRequest;

C_API GetAlarmPlanConfigRequest *HSAPI_INIT(GetAlarmPlanConfigRequest);

typedef struct GetAlarmPlanConfigResponse 
{
	HsviewResponse base;

	struct GetAlarmPlanConfigResponseData
	{
		
		/** define a list with struct of GetAlarmPlanConfigResponseData_ChannelsElement */
		DECLARE_LIST(struct GetAlarmPlanConfigResponseData_ChannelsElement
		{
			/** define a list with struct of GetAlarmPlanConfigResponseData_ChannelsElement_RulesElement */
			DECLARE_LIST(struct GetAlarmPlanConfigResponseData_ChannelsElement_RulesElement
			{
				/** 结束时间 */
				CSTR endTime;
				/** 开始时间 */
				CSTR beginTime;
				/** 重复周期 */
				CSTR period;
				/** [bool]是否有效 */
				BOOL enable;
			}) rules;
			/** 通道ID */
			CSTR channelId;
		}) channels;
 
	} data;

} GetAlarmPlanConfigResponse;

C_API GetAlarmPlanConfigResponse *HSAPI_INIT(GetAlarmPlanConfigResponse);

#endif
