/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetPullRecordPlan_H_
#define _HSVIEW_CLIENT_API_SetPullRecordPlan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备的定时录像计划配置。

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

typedef struct SetPullRecordPlanRequest 
{
	HsviewRequest base;

	struct SetPullRecordPlanRequestData
	{
		
		/** define a list with struct of SetPullRecordPlanRequestData_RulesElement */
		DECLARE_LIST(struct SetPullRecordPlanRequestData_RulesElement
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
		/** [int]上行带宽, 单位：M */
		int upstream;
		/** 通道ID */
		CSTR channelId;
		/** [int]每天保存的录像时长, 单位：小时，最大24小时 */
		int limitTime;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetPullRecordPlanRequest;

C_API SetPullRecordPlanRequest *HSAPI_INIT(SetPullRecordPlanRequest);

typedef struct SetPullRecordPlanResponse 
{
	HsviewResponse base;

	struct SetPullRecordPlanResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetPullRecordPlanResponse;

C_API SetPullRecordPlanResponse *HSAPI_INIT(SetPullRecordPlanResponse);

#endif
