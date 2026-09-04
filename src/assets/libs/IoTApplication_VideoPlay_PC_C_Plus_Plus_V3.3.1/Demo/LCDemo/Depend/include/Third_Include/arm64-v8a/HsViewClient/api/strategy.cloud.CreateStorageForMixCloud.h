/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyCloud_CreateStorageForMixCloud_H_
#define _HSVIEW_CLIENT_API_strategyCloud_CreateStorageForMixCloud_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
混合云客户端开通套餐
【需要使用平台账号签名】
 */

typedef struct strategyCloud_CreateStorageForMixCloudRequest 
{
	HsviewRequest base;

	struct strategyCloud_CreateStorageForMixCloudRequestData
	{
		
		/** [O]订单号 */
		CSTR orderNo;
		/** [O]通道号 */
		CSTR channelId;
		/** define a list with struct of strategyCloud_CreateStorageForMixCloudRequestData_StrategyListElement */
		DECLARE_LIST(struct strategyCloud_CreateStorageForMixCloudRequestData_StrategyListElement
		{
			/** 云录像码流类型, main:主码流、extra1：辅码流1 */
			CSTR streamType;
			/** 数量 */
			CSTR num;
			/** 套餐id */
			CSTR strategyId;
			/** 套餐服务时长(秒) */
			CSTR serviceTime;
			/** 录像保存天数(天) */
			CSTR recordSaveDays;
		}) strategyList;
		/** [O]设备序列号 */
		CSTR deviceId;

	} data;

} strategyCloud_CreateStorageForMixCloudRequest;

C_API strategyCloud_CreateStorageForMixCloudRequest *HSAPI_INIT(strategyCloud_CreateStorageForMixCloudRequest);

typedef struct strategyCloud_CreateStorageForMixCloudResponse 
{
	HsviewResponse base;

	struct strategyCloud_CreateStorageForMixCloudResponseData
	{
		
		/** mixedCloudApp*** */
		CSTR operationId;
 
	} data;

} strategyCloud_CreateStorageForMixCloudResponse;

C_API strategyCloud_CreateStorageForMixCloudResponse *HSAPI_INIT(strategyCloud_CreateStorageForMixCloudResponse);

#endif
