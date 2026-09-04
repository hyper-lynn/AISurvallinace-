/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmTryFreeCall_H_
#define _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmTryFreeCall_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
【需要使用平台账号签名】
 */

typedef struct strategyPhoneAlarm_PhoneAlarmTryFreeCallRequest 
{
	HsviewRequest base;

	struct strategyPhoneAlarm_PhoneAlarmTryFreeCallRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} strategyPhoneAlarm_PhoneAlarmTryFreeCallRequest;

C_API strategyPhoneAlarm_PhoneAlarmTryFreeCallRequest *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmTryFreeCallRequest);

typedef struct strategyPhoneAlarm_PhoneAlarmTryFreeCallResponse 
{
	HsviewResponse base;

	struct strategyPhoneAlarm_PhoneAlarmTryFreeCallResponseData
	{
		
		/** success:成功,frequent:操作过于频繁,upLimit:已达上限 */
		CSTR result;
 
	} data;

} strategyPhoneAlarm_PhoneAlarmTryFreeCallResponse;

C_API strategyPhoneAlarm_PhoneAlarmTryFreeCallResponse *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmTryFreeCallResponse);

#endif
