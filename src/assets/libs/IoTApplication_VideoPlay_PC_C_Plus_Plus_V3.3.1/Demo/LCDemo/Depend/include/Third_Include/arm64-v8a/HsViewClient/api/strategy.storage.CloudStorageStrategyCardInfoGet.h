/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_CloudStorageStrategyCardInfoGet_H_
#define _HSVIEW_CLIENT_API_strategyStorage_CloudStorageStrategyCardInfoGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取点卡详情

【使用平台账号签名】
 */

typedef struct strategyStorage_CloudStorageStrategyCardInfoGetRequest 
{
	HsviewRequest base;

	struct strategyStorage_CloudStorageStrategyCardInfoGetRequestData
	{
		
		/** 点卡卡密 */
		CSTR cardNo;

	} data;

} strategyStorage_CloudStorageStrategyCardInfoGetRequest;

C_API strategyStorage_CloudStorageStrategyCardInfoGetRequest *HSAPI_INIT(strategyStorage_CloudStorageStrategyCardInfoGetRequest);

typedef struct strategyStorage_CloudStorageStrategyCardInfoGetResponse 
{
	HsviewResponse base;

	struct strategyStorage_CloudStorageStrategyCardInfoGetResponseData
	{
		
		/** 码流类型：main：主码流extra1：辅码流 */
		CSTR streamType;
		/** 服务时长(秒) */
		CSTR seviceTime;
		/** cardNotExist:点卡不存在，cardExistCanUse：点卡存在且没有充值，cardExistAlreadyUsed：点卡存在且已经充值 */
		CSTR cardStatus;
		/** 录像保存天数 */
		CSTR recordSaveDays;
 
	} data;

} strategyStorage_CloudStorageStrategyCardInfoGetResponse;

C_API strategyStorage_CloudStorageStrategyCardInfoGetResponse *HSAPI_INIT(strategyStorage_CloudStorageStrategyCardInfoGetResponse);

#endif
