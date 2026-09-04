/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyCloud_GetFreeCloudStrategy_H_
#define _HSVIEW_CLIENT_API_strategyCloud_GetFreeCloudStrategy_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备通道的默认套餐，包括精彩一天和云存储套餐
【需要使用平台账号签名】
 */

typedef struct strategyCloud_GetFreeCloudStrategyRequest 
{
	HsviewRequest base;

	struct strategyCloud_GetFreeCloudStrategyRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** storage:云存储；wonderful：精彩一天 */
		DECLARE_LIST(CSTR) type;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} strategyCloud_GetFreeCloudStrategyRequest;

C_API strategyCloud_GetFreeCloudStrategyRequest *HSAPI_INIT(strategyCloud_GetFreeCloudStrategyRequest);

typedef struct strategyCloud_GetFreeCloudStrategyResponse 
{
	HsviewResponse base;

	struct strategyCloud_GetFreeCloudStrategyResponseData
	{
		
		/** define a list with struct of strategyCloud_GetFreeCloudStrategyResponseData_StrategiesElement */
		DECLARE_LIST(struct strategyCloud_GetFreeCloudStrategyResponseData_StrategiesElement
		{
			/** [bool]是否永久免费,如果永久免费，则endTime为空 */
			BOOL hasTimeLimit;
			/** 套餐类型，storage:云存储默认套餐; wonderful：精彩一天套餐,此时，开始和结束时间为固定值，从平台获取 */
			CSTR type;
			/** 套餐名称 */
			CSTR name;
			/** [long]套餐id */
			int64 strategyId;
			/** [int]-1-未领取 ，1-已经领取，0-没资格领取 */
			int status;
			/** 开始时间，yyyyMMddTHHmmssZ格式 */
			CSTR beginTime;
			/** [O]结束时间，yyyyMMddTHHmmssZ格式 */
			CSTR endTime;
		}) strategies;
 
	} data;

} strategyCloud_GetFreeCloudStrategyResponse;

C_API strategyCloud_GetFreeCloudStrategyResponse *HSAPI_INIT(strategyCloud_GetFreeCloudStrategyResponse);

#endif
