/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyHumanAlarm_HumanAlarmStrategyBatchGet_H_
#define _HSVIEW_CLIENT_API_strategyHumanAlarm_HumanAlarmStrategyBatchGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
批量获取设备云存储详情

【使用平台账号签名】
 */

typedef struct strategyHumanAlarm_HumanAlarmStrategyBatchGetRequest 
{
	HsviewRequest base;

	struct strategyHumanAlarm_HumanAlarmStrategyBatchGetRequestData
	{
		
		/** define a list with struct of strategyHumanAlarm_HumanAlarmStrategyBatchGetRequestData_DeviceListElement */
		DECLARE_LIST(struct strategyHumanAlarm_HumanAlarmStrategyBatchGetRequestData_DeviceListElement
		{
			/** 通道号 设备级 通道号为-1 */
			CSTR channelId;
			/** 设备ID */
			CSTR deviceId;
		}) deviceList;

	} data;

} strategyHumanAlarm_HumanAlarmStrategyBatchGetRequest;

C_API strategyHumanAlarm_HumanAlarmStrategyBatchGetRequest *HSAPI_INIT(strategyHumanAlarm_HumanAlarmStrategyBatchGetRequest);

typedef struct strategyHumanAlarm_HumanAlarmStrategyBatchGetResponse 
{
	HsviewResponse base;

	struct strategyHumanAlarm_HumanAlarmStrategyBatchGetResponseData
	{
		
		/** define a list with struct of strategyHumanAlarm_HumanAlarmStrategyBatchGetResponseData_DeviceStoragesElement */
		DECLARE_LIST(struct strategyHumanAlarm_HumanAlarmStrategyBatchGetResponseData_DeviceStoragesElement
		{
			/** define a list with struct of strategyHumanAlarm_HumanAlarmStrategyBatchGetResponseData_DeviceStoragesElement_SwitchsElement */
			DECLARE_LIST(struct strategyHumanAlarm_HumanAlarmStrategyBatchGetResponseData_DeviceStoragesElement_SwitchsElement
			{
				/** on：开关开启状态，off 开关关闭状态 */
				CSTR status;
				/** human:人形检测; pet:宠物检测；vehicle：车辆检测 */
				CSTR type;
			}) switchs;
			/** [int][O]套餐剩余天数 */
			int remainDays;
			/** [O]on：开关开启状态，off 开关关闭状态 */
			CSTR switchStatus;
			/** [O]失效时间，yyyyMMddTHHmmssZ格式 */
			CSTR endTime;
			/** 通道号 */
			CSTR channelId;
			/** 云存储状态 notExist:未开通套餐，using：开通云存储且没有过期， expired：套餐过期 */
			CSTR currentStrategyStatus;
			/** 设备ID */
			CSTR deviceId;
		}) deviceStorages;
 
	} data;

} strategyHumanAlarm_HumanAlarmStrategyBatchGetResponse;

C_API strategyHumanAlarm_HumanAlarmStrategyBatchGetResponse *HSAPI_INIT(strategyHumanAlarm_HumanAlarmStrategyBatchGetResponse);

#endif
