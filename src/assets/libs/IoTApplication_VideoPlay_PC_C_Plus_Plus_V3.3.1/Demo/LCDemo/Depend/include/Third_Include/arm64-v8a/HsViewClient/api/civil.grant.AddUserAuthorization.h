/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddUserAuthorization_H_
#define _HSVIEW_CLIENT_API_AddUserAuthorization_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   创建授权名称和角色
【需要使用平台账号签名】

 */

typedef struct AddUserAuthorizationRequest 
{
	HsviewRequest base;

	struct AddUserAuthorizationRequestData
	{
		
		/** 授权名称 */
		CSTR authName;
		/** [long]角色Id */
		int64 roleId;

	} data;

} AddUserAuthorizationRequest;

C_API AddUserAuthorizationRequest *HSAPI_INIT(AddUserAuthorizationRequest);

typedef struct AddUserAuthorizationResponse 
{
	HsviewResponse base;

	struct AddUserAuthorizationResponseData
	{
		
		/** [long]授权Id */
		int64 authId;
 
	} data;

} AddUserAuthorizationResponse;

C_API AddUserAuthorizationResponse *HSAPI_INIT(AddUserAuthorizationResponse);

#endif
