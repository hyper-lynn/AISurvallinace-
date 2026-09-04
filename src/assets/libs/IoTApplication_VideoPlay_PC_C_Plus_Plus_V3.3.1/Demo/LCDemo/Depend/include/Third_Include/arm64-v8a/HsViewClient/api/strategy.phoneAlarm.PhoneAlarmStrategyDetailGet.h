/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmStrategyDetailGet_H_
#define _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmStrategyDetailGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取电话报警套餐详情

当套餐状态不为using时,switchStatus,remainCounts,endTime可为空
当套餐状态不为using时,免费试听按钮隐藏，其他状态，则显示

【使用平台账号签名】
 */

typedef struct strategyPhoneAlarm_PhoneAlarmStrategyDetailGetRequest 
{
	HsviewRequest base;

	struct strategyPhoneAlarm_PhoneAlarmStrategyDetailGetRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} strategyPhoneAlarm_PhoneAlarmStrategyDetailGetRequest;

C_API strategyPhoneAlarm_PhoneAlarmStrategyDetailGetRequest *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmStrategyDetailGetRequest);

typedef struct strategyPhoneAlarm_PhoneAlarmStrategyDetailGetResponse 
{
	HsviewResponse base;

	struct strategyPhoneAlarm_PhoneAlarmStrategyDetailGetResponseData
	{
		
		/** [O]套餐剩余可用次数 */
		CSTR remainCounts;
		/** 套餐状态 notExist:未开通套餐，using：开通且没有过期， expired：套餐过期 */
		CSTR currentStrategyStatus;
		/** [O]失效时间，yyyyMMddTHHmmssZ格式 */
		CSTR endTime;
		/** [O]点击免费试听弹框提示的电话号码 */
		CSTR phone;
		/** [O]on：开关开启状态，off 开关关闭状态 */
		CSTR switchStatus;
 
	} data;

} strategyPhoneAlarm_PhoneAlarmStrategyDetailGetResponse;

C_API strategyPhoneAlarm_PhoneAlarmStrategyDetailGetResponse *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmStrategyDetailGetResponse);

#endif
