/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteUserAuthorization_H_
#define _HSVIEW_CLIENT_API_DeleteUserAuthorization_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   根据ID删除用户授权
【需要使用平台账号签名】

 */

typedef struct DeleteUserAuthorizationRequest 
{
	HsviewRequest base;

	struct DeleteUserAuthorizationRequestData
	{
		
		/** [long]需要删除的授权ID */
		DECLARE_LIST(int64) authIds;

	} data;

} DeleteUserAuthorizationRequest;

C_API DeleteUserAuthorizationRequest *HSAPI_INIT(DeleteUserAuthorizationRequest);

typedef struct DeleteUserAuthorizationResponse 
{
	HsviewResponse base;

	struct DeleteUserAuthorizationResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteUserAuthorizationResponse;

C_API DeleteUserAuthorizationResponse *HSAPI_INIT(DeleteUserAuthorizationResponse);

#endif
