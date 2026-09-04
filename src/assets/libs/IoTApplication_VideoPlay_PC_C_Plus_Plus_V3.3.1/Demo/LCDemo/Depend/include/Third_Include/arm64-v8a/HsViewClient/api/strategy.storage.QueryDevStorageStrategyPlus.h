/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_QueryDevStorageStrategyPlus_H_
#define _HSVIEW_CLIENT_API_strategyStorage_QueryDevStorageStrategyPlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
通过设备序列号、通道号查询全球安云存储套餐详情
【需要使用平台账号签名】
 */

typedef struct strategyStorage_QueryDevStorageStrategyPlusRequest 
{
	HsviewRequest base;

	struct strategyStorage_QueryDevStorageStrategyPlusRequestData
	{
		
		/** 通道id */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} strategyStorage_QueryDevStorageStrategyPlusRequest;

C_API strategyStorage_QueryDevStorageStrategyPlusRequest *HSAPI_INIT(strategyStorage_QueryDevStorageStrategyPlusRequest);

typedef struct strategyStorage_QueryDevStorageStrategyPlusResponse 
{
	HsviewResponse base;

	struct strategyStorage_QueryDevStorageStrategyPlusResponseData
	{
		
		/** 过期时间，yyyyMMddTHHmmssZ格式 */
		CSTR endTime;
		/** 开始时间，yyyyMMddTHHmmssZ格式 */
		CSTR beginTime;
		/** 套餐状态，-1:未开通，1:使用中 */
		CSTR strategyStatus;
 
	} data;

} strategyStorage_QueryDevStorageStrategyPlusResponse;

C_API strategyStorage_QueryDevStorageStrategyPlusResponse *HSAPI_INIT(strategyStorage_QueryDevStorageStrategyPlusResponse);

#endif
