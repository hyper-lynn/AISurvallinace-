/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmPhoneUpdate_H_
#define _HSVIEW_CLIENT_API_strategyPhoneAlarm_PhoneAlarmPhoneUpdate_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改提醒联系人
当oldPhone为空 表示是新增联系人
当oldPhone不为空 表示修改联系人
order:联系人顺序
除了用户第一次设置联系人，oldPhone为空 其他都是有值
错误码：
15000：错误的验证码
15001：无效的验证码
【需要使用平台账号签名】
 */

typedef struct strategyPhoneAlarm_PhoneAlarmPhoneUpdateRequest 
{
	HsviewRequest base;

	struct strategyPhoneAlarm_PhoneAlarmPhoneUpdateRequestData
	{
		
		/** [O]修改之前的联系人电话号码（11位） */
		CSTR oldPhone;
		/** 验证码 */
		CSTR validCode;
		/** 修改之后的联系人电话号码（11位） */
		CSTR newPhone;
		/** [int] 1 */
		int order;

	} data;

} strategyPhoneAlarm_PhoneAlarmPhoneUpdateRequest;

C_API strategyPhoneAlarm_PhoneAlarmPhoneUpdateRequest *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmPhoneUpdateRequest);

typedef struct strategyPhoneAlarm_PhoneAlarmPhoneUpdateResponse 
{
	HsviewResponse base;

	struct strategyPhoneAlarm_PhoneAlarmPhoneUpdateResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} strategyPhoneAlarm_PhoneAlarmPhoneUpdateResponse;

C_API strategyPhoneAlarm_PhoneAlarmPhoneUpdateResponse *HSAPI_INIT(strategyPhoneAlarm_PhoneAlarmPhoneUpdateResponse);

#endif
