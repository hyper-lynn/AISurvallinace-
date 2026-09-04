/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GrantPermission_H_
#define _HSVIEW_CLIENT_API_GrantPermission_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户进行设备授权
【使用平台账号签名】
 */

typedef struct GrantPermissionRequest 
{
	HsviewRequest base;

	struct GrantPermissionRequestData
	{
		
		/** [bool] true-授权  false-取消授权 */
		BOOL flag;
		/** 用户允许的类型：LogDebug-日志调试 */
		CSTR type;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GrantPermissionRequest;

C_API GrantPermissionRequest *HSAPI_INIT(GrantPermissionRequest);

typedef struct GrantPermissionResponse 
{
	HsviewResponse base;

	struct GrantPermissionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} GrantPermissionResponse;

C_API GrantPermissionResponse *HSAPI_INIT(GrantPermissionResponse);

#endif
