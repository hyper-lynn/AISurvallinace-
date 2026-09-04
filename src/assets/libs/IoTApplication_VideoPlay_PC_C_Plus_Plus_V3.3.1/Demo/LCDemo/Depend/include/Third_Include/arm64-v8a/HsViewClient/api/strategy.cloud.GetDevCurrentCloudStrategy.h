/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyCloud_GetDevCurrentCloudStrategy_H_
#define _HSVIEW_CLIENT_API_strategyCloud_GetDevCurrentCloudStrategy_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备通道当前云服务套餐
【需要使用平台账号签名】
 */

typedef struct strategyCloud_GetDevCurrentCloudStrategyRequest 
{
	HsviewRequest base;

	struct strategyCloud_GetDevCurrentCloudStrategyRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** storage:云存储；wonderful：精彩一天 */
		DECLARE_LIST(CSTR) type;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} strategyCloud_GetDevCurrentCloudStrategyRequest;

C_API strategyCloud_GetDevCurrentCloudStrategyRequest *HSAPI_INIT(strategyCloud_GetDevCurrentCloudStrategyRequest);

typedef struct strategyCloud_GetDevCurrentCloudStrategyResponse 
{
	HsviewResponse base;

	struct strategyCloud_GetDevCurrentCloudStrategyResponseData
	{
		
		/** define a list with struct of strategyCloud_GetDevCurrentCloudStrategyResponseData_StrategiesElement */
		DECLARE_LIST(struct strategyCloud_GetDevCurrentCloudStrategyResponseData_StrategiesElement
		{
			/** storage:云存储；wonderful：精彩一天 */
			CSTR type;
			/** [O]套餐名 */
			CSTR name;
			/** [O]结束时间时间，yyyyMMddTHHmmssZ格式 */
			CSTR endTime;
			/** [O]开始时间，yyyyMMddTHHmmssZ格式 */
			CSTR beginTime;
			/** [int]套餐状态，0-过期；1-使用中；2-暂停；-1-没有开通套餐，此时beginTime、endTime和name为空 */
			int status;
		}) strategies;
 
	} data;

} strategyCloud_GetDevCurrentCloudStrategyResponse;

C_API strategyCloud_GetDevCurrentCloudStrategyResponse *HSAPI_INIT(strategyCloud_GetDevCurrentCloudStrategyResponse);

#endif
