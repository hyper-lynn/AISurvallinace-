/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_squareVideo_GetH5Permission_H_
#define _HSVIEW_CLIENT_API_squareVideo_GetH5Permission_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询视频广场是否需要显示评论点赞举报功能。
是否显示视频广场评论点赞举报H5PermissionType传H5Permission
【使用平台账号签名】
 */

typedef struct squareVideo_GetH5PermissionRequest 
{
	HsviewRequest base;

	struct squareVideo_GetH5PermissionRequestData
	{
		
		/** H5权限 */
		CSTR accessKey;

	} data;

} squareVideo_GetH5PermissionRequest;

C_API squareVideo_GetH5PermissionRequest *HSAPI_INIT(squareVideo_GetH5PermissionRequest);

typedef struct squareVideo_GetH5PermissionResponse 
{
	HsviewResponse base;

	struct squareVideo_GetH5PermissionResponseData
	{
		
		/** [int]是否显示视频广场评论点赞举报，0-显示，1-不显示 */
		int h5Permission;
 
	} data;

} squareVideo_GetH5PermissionResponse;

C_API squareVideo_GetH5PermissionResponse *HSAPI_INIT(squareVideo_GetH5PermissionResponse);

#endif
