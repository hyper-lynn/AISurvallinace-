/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyHumanAlarm_HumanAlarmStrategyDetailGet_H_
#define _HSVIEW_CLIENT_API_strategyHumanAlarm_HumanAlarmStrategyDetailGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取智能人形检测套餐详情

【使用平台账号签名】
 */

typedef struct strategyHumanAlarm_HumanAlarmStrategyDetailGetRequest 
{
	HsviewRequest base;

	struct strategyHumanAlarm_HumanAlarmStrategyDetailGetRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} strategyHumanAlarm_HumanAlarmStrategyDetailGetRequest;

C_API strategyHumanAlarm_HumanAlarmStrategyDetailGetRequest *HSAPI_INIT(strategyHumanAlarm_HumanAlarmStrategyDetailGetRequest);

typedef struct strategyHumanAlarm_HumanAlarmStrategyDetailGetResponse 
{
	HsviewResponse base;

	struct strategyHumanAlarm_HumanAlarmStrategyDetailGetResponseData
	{
		
		/** define a list with struct of strategyHumanAlarm_HumanAlarmStrategyDetailGetResponseData_SwitchsElement */
		DECLARE_LIST(struct strategyHumanAlarm_HumanAlarmStrategyDetailGetResponseData_SwitchsElement
		{
			/** on：开关开启状态，off 开关关闭状态 */
			CSTR status;
			/** human:人形检测; pet:宠物检测；vehicle：车辆检测 */
			CSTR type;
		}) switchs;
		/** 套餐状态 notExist:未开通套餐，using：开通且没有过期， expired：套餐过期 */
		CSTR currentStrategyStatus;
		/** [O]失效时间，yyyyMMddTHHmmssZ格式 */
		CSTR endTime;
		/** [int][O]套餐剩余天数 */
		int remainDays;
		/** [O]是否是自动续费套餐，true：时，false：否 */
		CSTR isAutoRenew;
		/** [O]on：开关开启状态，off 开关关闭状态 */
		CSTR switchStatus;
 
	} data;

} strategyHumanAlarm_HumanAlarmStrategyDetailGetResponse;

C_API strategyHumanAlarm_HumanAlarmStrategyDetailGetResponse *HSAPI_INIT(strategyHumanAlarm_HumanAlarmStrategyDetailGetResponse);

#endif
