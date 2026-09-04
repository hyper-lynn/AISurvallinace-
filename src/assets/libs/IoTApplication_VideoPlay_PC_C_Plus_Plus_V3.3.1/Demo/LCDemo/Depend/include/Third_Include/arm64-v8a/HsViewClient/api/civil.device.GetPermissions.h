/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetPermissions_H_
#define _HSVIEW_CLIENT_API_GetPermissions_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取用户授权的结果
type为空或null，则代表获取设备的所有授权；
【使用平台账号签名】
 */

typedef struct GetPermissionsRequest 
{
	HsviewRequest base;

	struct GetPermissionsRequestData
	{
		
		/** 用户允许的类型：LogDebug-日志调试 */
		CSTR type;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetPermissionsRequest;

C_API GetPermissionsRequest *HSAPI_INIT(GetPermissionsRequest);

typedef struct GetPermissionsResponse 
{
	HsviewResponse base;

	struct GetPermissionsResponseData
	{
		
		/** define a list with struct of GetPermissionsResponseData_PermissionsElement */
		DECLARE_LIST(struct GetPermissionsResponseData_PermissionsElement
		{
			/** [bool] true-授权  false-未授权 */
			BOOL flag;
			/** 用户允许的类型：LogDebug-日志调试 */
			CSTR type;
		}) permissions;
 
	} data;

} GetPermissionsResponse;

C_API GetPermissionsResponse *HSAPI_INIT(GetPermissionsResponse);

#endif
