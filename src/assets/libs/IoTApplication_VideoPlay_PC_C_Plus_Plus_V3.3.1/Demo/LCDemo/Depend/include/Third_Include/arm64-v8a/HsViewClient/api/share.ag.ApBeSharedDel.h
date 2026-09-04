/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_shareAg_ApBeSharedDel_H_
#define _HSVIEW_CLIENT_API_shareAg_ApBeSharedDel_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除配件共享，删除TA分享给我的


【需要使用平台账号签名】
 */

typedef struct shareAg_ApBeSharedDelRequest 
{
	HsviewRequest base;

	struct shareAg_ApBeSharedDelRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} shareAg_ApBeSharedDelRequest;

C_API shareAg_ApBeSharedDelRequest *HSAPI_INIT(shareAg_ApBeSharedDelRequest);

typedef struct shareAg_ApBeSharedDelResponse 
{
	HsviewResponse base;

	struct shareAg_ApBeSharedDelResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} shareAg_ApBeSharedDelResponse;

C_API shareAg_ApBeSharedDelResponse *HSAPI_INIT(shareAg_ApBeSharedDelResponse);

#endif
