/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteRole_H_
#define _HSVIEW_CLIENT_API_DeleteRole_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   删除用户角色
【需要使用平台账号签名】

 */

typedef struct DeleteRoleRequest 
{
	HsviewRequest base;

	struct DeleteRoleRequestData
	{
		
		/** [long]角色Id */
		int64 roleId;

	} data;

} DeleteRoleRequest;

C_API DeleteRoleRequest *HSAPI_INIT(DeleteRoleRequest);

typedef struct DeleteRoleResponse 
{
	HsviewResponse base;

	struct DeleteRoleResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteRoleResponse;

C_API DeleteRoleResponse *HSAPI_INIT(DeleteRoleResponse);

#endif
