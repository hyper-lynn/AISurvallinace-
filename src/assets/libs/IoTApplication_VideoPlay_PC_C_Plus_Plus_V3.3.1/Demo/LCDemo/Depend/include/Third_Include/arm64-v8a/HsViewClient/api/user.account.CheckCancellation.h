/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_CheckCancellation_H_
#define _HSVIEW_CLIENT_API_userAccount_CheckCancellation_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
注销账号时校验用户是否满足注销条件

【使用平台账号签名】
 */

typedef struct userAccount_CheckCancellationRequest 
{
	HsviewRequest base;

	struct userAccount_CheckCancellationRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} userAccount_CheckCancellationRequest;

C_API userAccount_CheckCancellationRequest *HSAPI_INIT(userAccount_CheckCancellationRequest);

typedef struct userAccount_CheckCancellationResponse 
{
	HsviewResponse base;

	struct userAccount_CheckCancellationResponseData
	{
		
		/** [bool]注销用户是否开通开放平台服务，true-开通，false-未开通 */
		BOOL bOpenUser;
		/** [bool][O]注销用户是否存在商城订单，true-存在，false-不存在 */
		BOOL bMallOrder;
		/** [bool]注销的用户是否有共享设备，true-有，false-无 */
		BOOL bHaveShareDev;
		/** [bool]注销的用户是否有绑定设备，true-有，false-无 */
		BOOL bHaveBindDev;
 
	} data;

} userAccount_CheckCancellationResponse;

C_API userAccount_CheckCancellationResponse *HSAPI_INIT(userAccount_CheckCancellationResponse);

#endif
