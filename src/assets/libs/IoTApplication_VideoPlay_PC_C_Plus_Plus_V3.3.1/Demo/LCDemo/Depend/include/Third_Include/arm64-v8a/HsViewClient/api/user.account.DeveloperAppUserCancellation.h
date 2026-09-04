/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_DeveloperAppUserCancellation_H_
#define _HSVIEW_CLIENT_API_userAccount_DeveloperAppUserCancellation_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
注销账号

【使用平台账号签名】
 */

typedef struct userAccount_DeveloperAppUserCancellationRequest 
{
	HsviewRequest base;

	struct userAccount_DeveloperAppUserCancellationRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} userAccount_DeveloperAppUserCancellationRequest;

C_API userAccount_DeveloperAppUserCancellationRequest *HSAPI_INIT(userAccount_DeveloperAppUserCancellationRequest);

typedef struct userAccount_DeveloperAppUserCancellationResponse 
{
	HsviewResponse base;

	struct userAccount_DeveloperAppUserCancellationResponseData
	{
		
		/** [bool]注销的用户是否有绑定设备，true-有，false-无 */
		BOOL bHaveBindDev;
		/** [bool]注销的用户是否有共享设备，true-有，false-无 */
		BOOL bHaveShareDev;
 
	} data;

} userAccount_DeveloperAppUserCancellationResponse;

C_API userAccount_DeveloperAppUserCancellationResponse *HSAPI_INIT(userAccount_DeveloperAppUserCancellationResponse);

#endif
