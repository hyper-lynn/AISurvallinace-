/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmStrategySwitchSet_H_
#define _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmStrategySwitchSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
开启暂停套餐对应的开关

【使用平台账号签名】
 */

typedef struct strategyPhoneAlarm_PhoneAlarmStrategySwitchSetRequest 
{
	HsviewRequest base;

	struct strategyPhoneAlarm_PhoneAlarmStrategySwitchSetRequestData
	{
		
		/** on：电话报警提醒开关开启，off 电话报警提醒开关关闭 */
		CSTR switchStatus;

	} data;

} strategyPhoneAlarm_PhoneAlarmStrategySwitchSetRequest;

C_API strategyPhoneAlarm_PhoneAlarmStrategySwitchSetRequest *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmStrategySwitchSetRequest);

typedef struct strategyPhoneAlarm_PhoneAlarmStrategySwitchSetResponse 
{
	HsviewResponse base;

	struct strategyPhoneAlarm_PhoneAlarmStrategySwitchSetResponseData
	{
		
		/** success: 操作成功， notExist：操作失败，未开通套餐，expired：操作失败，套餐已经过期 */
		CSTR result;
 
	} data;

} strategyPhoneAlarm_PhoneAlarmStrategySwitchSetResponse;

C_API strategyPhoneAlarm_PhoneAlarmStrategySwitchSetResponse *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmStrategySwitchSetResponse);

#endif
