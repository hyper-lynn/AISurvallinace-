/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddRole_H_
#define _HSVIEW_CLIENT_API_AddRole_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   创建用户角色，权限列表以逗号分隔,如：videoMonitor,videoRecord
【需要使用平台账号签名】

 */

typedef struct AddRoleRequest 
{
	HsviewRequest base;

	struct AddRoleRequestData
	{
		
		/** 授权名称 */
		CSTR roleName;
		/** 权限列表，以逗号分隔 */
		CSTR authFunctions;

	} data;

} AddRoleRequest;

C_API AddRoleRequest *HSAPI_INIT(AddRoleRequest);

typedef struct AddRoleResponse 
{
	HsviewResponse base;

	struct AddRoleResponseData
	{
		
		/** [long]角色Id */
		int64 roleId;
 
	} data;

} AddRoleResponse;

C_API AddRoleResponse *HSAPI_INIT(AddRoleResponse);

#endif
