/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UserLogout_H_
#define _HSVIEW_CLIENT_API_UserLogout_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户登出。
【使用平台账号签名】
 */

typedef struct UserLogoutRequest 
{
	HsviewRequest base;

	struct UserLogoutRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} UserLogoutRequest;

C_API UserLogoutRequest *HSAPI_INIT(UserLogoutRequest);

typedef struct UserLogoutResponse 
{
	HsviewResponse base;

	struct UserLogoutResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UserLogoutResponse;

C_API UserLogoutResponse *HSAPI_INIT(UserLogoutResponse);

#endif
