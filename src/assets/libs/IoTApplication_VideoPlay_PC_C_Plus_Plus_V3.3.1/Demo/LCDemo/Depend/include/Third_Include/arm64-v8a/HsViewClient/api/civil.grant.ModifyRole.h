/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ModifyRole_H_
#define _HSVIEW_CLIENT_API_ModifyRole_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   修改授权角色
【需要使用平台账号签名】

 */

typedef struct ModifyRoleRequest 
{
	HsviewRequest base;

	struct ModifyRoleRequestData
	{
		
		/** [long]角色Id */
		int64 roleId;
		/** 授权名称 */
		CSTR roleName;
		/** 权限列表，以逗号分隔 */
		CSTR authFunctions;

	} data;

} ModifyRoleRequest;

C_API ModifyRoleRequest *HSAPI_INIT(ModifyRoleRequest);

typedef struct ModifyRoleResponse 
{
	HsviewResponse base;

	struct ModifyRoleResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyRoleResponse;

C_API ModifyRoleResponse *HSAPI_INIT(ModifyRoleResponse);

#endif
