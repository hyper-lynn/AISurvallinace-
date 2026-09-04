/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetStorageStrategy_H_
#define _HSVIEW_CLIENT_API_SetStorageStrategy_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置云存储策略。
【使用平台账号签名】
 */

typedef struct SetStorageStrategyRequest 
{
	HsviewRequest base;

	struct SetStorageStrategyRequestData
	{
		
		/** [O]卡密（可选项，在购买套餐确认使用时设置） */
		CSTR cardNo;
		/** 通道号 */
		CSTR channelId;
		/** [long]云存储套餐ID。若ID为-1表示取消套餐。 */
		int64 strategyId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetStorageStrategyRequest;

C_API SetStorageStrategyRequest *HSAPI_INIT(SetStorageStrategyRequest);

typedef struct SetStorageStrategyResponse 
{
	HsviewResponse base;

	struct SetStorageStrategyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetStorageStrategyResponse;

C_API SetStorageStrategyResponse *HSAPI_INIT(SetStorageStrategyResponse);

#endif
