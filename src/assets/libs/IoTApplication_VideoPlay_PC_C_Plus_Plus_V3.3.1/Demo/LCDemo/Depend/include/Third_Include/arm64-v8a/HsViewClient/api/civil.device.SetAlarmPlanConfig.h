/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetAlarmPlanConfig_H_
#define _HSVIEW_CLIENT_API_SetAlarmPlanConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备的报警计划配置。

	Period：生效的周期
		once：仅一次
		everyday：每天 等价于周一到周日
		workday：每个工作日 可以认为等价于周一到周五
		Monday：每周一
		Tuesday：每周二
		Wednesday：每周三
		Thursday：每周四
		Friday：每周五
		Saturday：每周六
		Sunday：每周日
	可使用“Monday, Wednesday, Friday”的方式多选。
		holiday：每个节假日 包括假日（周末）和节日（元旦等），由于节日的不固定性，非特殊需求不要使用（华视微讯和乐橙暂不支持）

	BeginTime和EndTime：生效的起止时间
	  #当Period为once时，时间格式为%Y-%m-%d %H:%M:%S
	  #当Period为其他时，时间格式为%H:%M:%S
	注：当EndTime <= BeginTime，则认为设置的时间段是跨天的。

【使用平台账号签名】
 */

typedef struct SetAlarmPlanConfigRequest 
{
	HsviewRequest base;

	struct SetAlarmPlanConfigRequestData
	{
		
		/** define a list with struct of SetAlarmPlanConfigRequestData_ChannelsElement */
		DECLARE_LIST(struct SetAlarmPlanConfigRequestData_ChannelsElement
		{
			/** define a list with struct of SetAlarmPlanConfigRequestData_ChannelsElement_RulesElement */
			DECLARE_LIST(struct SetAlarmPlanConfigRequestData_ChannelsElement_RulesElement
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
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetAlarmPlanConfigRequest;

C_API SetAlarmPlanConfigRequest *HSAPI_INIT(SetAlarmPlanConfigRequest);

typedef struct SetAlarmPlanConfigResponse 
{
	HsviewResponse base;

	struct SetAlarmPlanConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetAlarmPlanConfigResponse;

C_API SetAlarmPlanConfigResponse *HSAPI_INIT(SetAlarmPlanConfigResponse);

#endif
