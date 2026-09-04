/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_Cancellation_H_
#define _HSVIEW_CLIENT_API_userAccount_Cancellation_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
注销账号

【使用平台账号签名】
 */

typedef struct userAccount_CancellationRequest 
{
	HsviewRequest base;

	struct userAccount_CancellationRequestData
	{
		
		/** 验证码，如123456 */
		CSTR validCode;
		/** 帐号类型, phone、email */
		CSTR type;
		/** 帐号, 手机号码、邮箱 */
		CSTR account;

	} data;

} userAccount_CancellationRequest;

C_API userAccount_CancellationRequest *HSAPI_INIT(userAccount_CancellationRequest);

typedef struct userAccount_CancellationResponse 
{
	HsviewResponse base;

	struct userAccount_CancellationResponseData
	{
		
		/** [bool]注销用户是否开通开放平台服务，true-开通，false-未开通 */
		BOOL bOpenUser;
		/** [bool][O]注销用户是否存在商城订单，true-存在，false-不存在 */
		BOOL bMallOrder;
		/** [bool]注销的用户是否有绑定或共享设备，true-有，false-无 */
		BOOL bHaveBindDev;
 
	} data;

} userAccount_CancellationResponse;

C_API userAccount_CancellationResponse *HSAPI_INIT(userAccount_CancellationResponse);

#endif
