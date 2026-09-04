/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetPullRecordPlan_H_
#define _HSVIEW_CLIENT_API_GetPullRecordPlan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备的定时录像计划配置。

	Period：生效的周期
		Monday：每周一
		Tuesday：每周二
		Wednesday：每周三
		Thursday：每周四
		Friday：每周五
		Saturday：每周六
		Sunday：每周日
	可使用“Monday, Wednesday, Friday”的方式多选。		

	beginTime和endTime：生效的起止时间
	  #period时间格式为%H:%M:%S
	注：beginTime必须小于endTime。

【使用平台账号签名】
 */

typedef struct GetPullRecordPlanRequest 
{
	HsviewRequest base;

	struct GetPullRecordPlanRequestData
	{
		
		/** 通道ID */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetPullRecordPlanRequest;

C_API GetPullRecordPlanRequest *HSAPI_INIT(GetPullRecordPlanRequest);

typedef struct GetPullRecordPlanResponse 
{
	HsviewResponse base;

	struct GetPullRecordPlanResponseData
	{
		
		/** define a list with struct of GetPullRecordPlanResponseData_RulesElement */
		DECLARE_LIST(struct GetPullRecordPlanResponseData_RulesElement
		{
			/** [int]拉取方式, 1表示实时拉取，2表示定时拉取 */
			int type;
			/** 重复周期 */
			CSTR period;
			/** 结束时间 */
			CSTR endTime;
			/** 开始时间 */
			CSTR beginTime;
			/** type为2时有效，定时拉取模式下的拉取时间 */
			CSTR pullTime;
			/** [int]type为1时有效，拉取的码流类型，暂时支持stream为0或者1，0表示主码流，1表示辅码流 */
			int stream;
		}) rules;
		/** [int]每天保存的录像时长, 单位：小时，最大24小时 */
		int limitTime;
		/** [int]上行带宽, 单位：M */
		int upstream;
 
	} data;

} GetPullRecordPlanResponse;

C_API GetPullRecordPlanResponse *HSAPI_INIT(GetPullRecordPlanResponse);

#endif
