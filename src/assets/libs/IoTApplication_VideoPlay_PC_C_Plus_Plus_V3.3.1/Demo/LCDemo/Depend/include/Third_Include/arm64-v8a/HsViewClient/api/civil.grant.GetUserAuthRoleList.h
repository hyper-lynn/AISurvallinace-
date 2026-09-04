/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUserAuthRoleList_H_
#define _HSVIEW_CLIENT_API_GetUserAuthRoleList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   获取角色列表
【需要使用平台账号签名】

 */

typedef struct GetUserAuthRoleListRequest 
{
	HsviewRequest base;

	struct GetUserAuthRoleListRequestData
	{
		
		/** [int]需要查的最大条数 */
		int count;
		/** [long]从该角色ID开始查询。若要从最新开始查，填-1 */
		int64 roleId;

	} data;

} GetUserAuthRoleListRequest;

C_API GetUserAuthRoleListRequest *HSAPI_INIT(GetUserAuthRoleListRequest);

typedef struct GetUserAuthRoleListResponse 
{
	HsviewResponse base;

	struct GetUserAuthRoleListResponseData
	{
		
		/** define a list with struct of GetUserAuthRoleListResponseData_RolesElement */
		DECLARE_LIST(struct GetUserAuthRoleListResponseData_RolesElement
		{
			/** [int]是否为默认角色：0 - 普通角色，1 - 默认角色 */
			int isDefault;
			/** [long]角色Id */
			int64 roleId;
			/** 角色名称 */
			CSTR roleName;
			/** 权限列表 */
			CSTR authFunctions;
		}) roles;
 
	} data;

} GetUserAuthRoleListResponse;

C_API GetUserAuthRoleListResponse *HSAPI_INIT(GetUserAuthRoleListResponse);

#endif
