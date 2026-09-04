/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_CloudStorageStrategyCardConsume_H_
#define _HSVIEW_CLIENT_API_strategyStorage_CloudStorageStrategyCardConsume_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
点卡启用云存储

【使用平台账号签名】
 */

typedef struct strategyStorage_CloudStorageStrategyCardConsumeRequest 
{
	HsviewRequest base;

	struct strategyStorage_CloudStorageStrategyCardConsumeRequestData
	{
		
		/** 点卡卡密 */
		CSTR cardNo;
		/** 设备通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} strategyStorage_CloudStorageStrategyCardConsumeRequest;

C_API strategyStorage_CloudStorageStrategyCardConsumeRequest *HSAPI_INIT(strategyStorage_CloudStorageStrategyCardConsumeRequest);

typedef struct strategyStorage_CloudStorageStrategyCardConsumeResponse 
{
	HsviewResponse base;

	struct strategyStorage_CloudStorageStrategyCardConsumeResponseData
	{
		
		/** success:成功，cardNotExist：点卡不存在，cardExistAlreadyUsed：点卡存在且点卡无效，已经被充值了，deviceExistAutoRenewal:当前设备存在自动续费套餐，开通失败 */
		CSTR result;
 
	} data;

} strategyStorage_CloudStorageStrategyCardConsumeResponse;

C_API strategyStorage_CloudStorageStrategyCardConsumeResponse *HSAPI_INIT(strategyStorage_CloudStorageStrategyCardConsumeResponse);

#endif
