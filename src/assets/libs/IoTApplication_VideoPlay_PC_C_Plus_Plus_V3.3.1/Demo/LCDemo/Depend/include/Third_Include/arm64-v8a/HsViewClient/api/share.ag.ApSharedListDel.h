/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_shareAg_ApSharedListDel_H_
#define _HSVIEW_CLIENT_API_shareAg_ApSharedListDel_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除配件共享，删除分享给TA的
如果列表userIdList为空，则删除所有分享的配件

【需要使用平台账号签名】
 */

typedef struct shareAg_ApSharedListDelRequest 
{
	HsviewRequest base;

	struct shareAg_ApSharedListDelRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** [O]用户ID，已共享的用户ID */
		DECLARE_LIST(CSTR) userIdList;
		/** 设备ID */
		CSTR deviceId;

	} data;

} shareAg_ApSharedListDelRequest;

C_API shareAg_ApSharedListDelRequest *HSAPI_INIT(shareAg_ApSharedListDelRequest);

typedef struct shareAg_ApSharedListDelResponse 
{
	HsviewResponse base;

	struct shareAg_ApSharedListDelResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} shareAg_ApSharedListDelResponse;

C_API shareAg_ApSharedListDelResponse *HSAPI_INIT(shareAg_ApSharedListDelResponse);

#endif
