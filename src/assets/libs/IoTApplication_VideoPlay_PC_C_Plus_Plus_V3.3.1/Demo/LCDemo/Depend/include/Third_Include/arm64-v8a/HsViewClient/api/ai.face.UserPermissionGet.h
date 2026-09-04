/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_aiFace_UserPermissionGet_H_
#define _HSVIEW_CLIENT_API_aiFace_UserPermissionGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户是否为人脸云公测用户


【使用平台账号签名】
 */

typedef struct aiFace_UserPermissionGetRequest 
{
	HsviewRequest base;

	struct aiFace_UserPermissionGetRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} aiFace_UserPermissionGetRequest;

C_API aiFace_UserPermissionGetRequest *HSAPI_INIT(aiFace_UserPermissionGetRequest);

typedef struct aiFace_UserPermissionGetResponse 
{
	HsviewResponse base;

	struct aiFace_UserPermissionGetResponseData
	{
		
		/** true:具有资格,false:无资格 */
		CSTR result;
 
	} data;

} aiFace_UserPermissionGetResponse;

C_API aiFace_UserPermissionGetResponse *HSAPI_INIT(aiFace_UserPermissionGetResponse);

#endif
