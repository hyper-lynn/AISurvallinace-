/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_shareAg_ApShareListSet_H_
#define _HSVIEW_CLIENT_API_shareAg_ApShareListSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置配件共享，共享给TA
functions: apAlarmMsg,apConfigure

【需要使用平台账号签名】
 */

typedef struct shareAg_ApShareListSetRequest 
{
	HsviewRequest base;

	struct shareAg_ApShareListSetRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** define a list with struct of shareAg_ApShareListSetRequestData_ShareListElement */
		DECLARE_LIST(struct shareAg_ApShareListSetRequestData_ShareListElement
		{
			/** 用户ID，被共享的用户ID */
			CSTR userId;
			/** 英文逗号分隔 */
			CSTR functions;
		}) shareList;
		/** 设备ID */
		CSTR deviceId;

	} data;

} shareAg_ApShareListSetRequest;

C_API shareAg_ApShareListSetRequest *HSAPI_INIT(shareAg_ApShareListSetRequest);

typedef struct shareAg_ApShareListSetResponse 
{
	HsviewResponse base;

	struct shareAg_ApShareListSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} shareAg_ApShareListSetResponse;

C_API shareAg_ApShareListSetResponse *HSAPI_INIT(shareAg_ApShareListSetResponse);

#endif
