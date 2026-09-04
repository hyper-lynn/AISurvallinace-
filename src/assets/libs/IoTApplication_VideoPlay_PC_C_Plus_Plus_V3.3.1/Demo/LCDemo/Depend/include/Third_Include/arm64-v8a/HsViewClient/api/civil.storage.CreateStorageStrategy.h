/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_CreateStorageStrategy_H_
#define _HSVIEW_CLIENT_API_CreateStorageStrategy_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
开放平台用来为设备通道创建收费云存储。
【使用平台账号和开放平台密钥签名】
 */

typedef struct CreateStorageStrategyRequest 
{
	HsviewRequest base;

	struct CreateStorageStrategyRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** [long]云存储收费套餐ID */
		int64 strategyId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} CreateStorageStrategyRequest;

C_API CreateStorageStrategyRequest *HSAPI_INIT(CreateStorageStrategyRequest);

typedef struct CreateStorageStrategyResponse 
{
	HsviewResponse base;

	struct CreateStorageStrategyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} CreateStorageStrategyResponse;

C_API CreateStorageStrategyResponse *HSAPI_INIT(CreateStorageStrategyResponse);

#endif
