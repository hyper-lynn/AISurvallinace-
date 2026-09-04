/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyHumanAlarm_HumanAlarmStrategySwitchSet_H_
#define _HSVIEW_CLIENT_API_strategyHumanAlarm_HumanAlarmStrategySwitchSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
开启暂停套餐对应的开关

【使用平台账号签名】
 */

typedef struct strategyHumanAlarm_HumanAlarmStrategySwitchSetRequest 
{
	HsviewRequest base;

	struct strategyHumanAlarm_HumanAlarmStrategySwitchSetRequestData
	{
		
		/** on：智能人形检测套餐开关开启，off 智能人形检测套餐关闭 */
		CSTR switchStatus;
		/** 通道号 */
		CSTR channelId;
		/** [O]human:人形检测; pet:宠物检测；vehicle：车辆检测 */
		CSTR switchType;
		/** 设备ID */
		CSTR deviceId;

	} data;

} strategyHumanAlarm_HumanAlarmStrategySwitchSetRequest;

C_API strategyHumanAlarm_HumanAlarmStrategySwitchSetRequest *HSAPI_INIT(strategyHumanAlarm_HumanAlarmStrategySwitchSetRequest);

typedef struct strategyHumanAlarm_HumanAlarmStrategySwitchSetResponse 
{
	HsviewResponse base;

	struct strategyHumanAlarm_HumanAlarmStrategySwitchSetResponseData
	{
		
		/** success: 操作成功， notExist：操作失败，未开通套餐，expired：操作失败，套餐已经过期 */
		CSTR result;
 
	} data;

} strategyHumanAlarm_HumanAlarmStrategySwitchSetResponse;

C_API strategyHumanAlarm_HumanAlarmStrategySwitchSetResponse *HSAPI_INIT(strategyHumanAlarm_HumanAlarmStrategySwitchSetResponse);

#endif
