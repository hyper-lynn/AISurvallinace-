/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyCloud_GetDevCloudStrategyList_H_
#define _HSVIEW_CLIENT_API_strategyCloud_GetDevCloudStrategyList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备通道购买的云服务套餐列表
【需要使用平台账号签名】
 */

typedef struct strategyCloud_GetDevCloudStrategyListRequest 
{
	HsviewRequest base;

	struct strategyCloud_GetDevCloudStrategyListRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** storage:云存储；wonderful：精彩一天 */
		DECLARE_LIST(CSTR) type;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} strategyCloud_GetDevCloudStrategyListRequest;

C_API strategyCloud_GetDevCloudStrategyListRequest *HSAPI_INIT(strategyCloud_GetDevCloudStrategyListRequest);

typedef struct strategyCloud_GetDevCloudStrategyListResponse 
{
	HsviewResponse base;

	struct strategyCloud_GetDevCloudStrategyListResponseData
	{
		
		/** define a list with struct of strategyCloud_GetDevCloudStrategyListResponseData_StrategiesElement */
		DECLARE_LIST(struct strategyCloud_GetDevCloudStrategyListResponseData_StrategiesElement
		{
			/** 套餐类型，storage:云存储默认套餐；wonderful：精彩一天套餐; */
			CSTR type;
			/** 套餐名 */
			CSTR name;
			/** [int]套餐状态，0-过期，-1-未使用，1-使用中，2-暂停 */
			int status;
			/** [int]云存储服务期限（天） */
			int timeLimit;
			/** 开始时间，yyyyMMddTHHmmssZ格式 */
			CSTR beginTime;
			/** [int]套餐剩余秒数 */
			int timeLeft;
			/** 结束时间时间，yyyyMMddTHHmmssZ格式 */
			CSTR endTime;
		}) strategies;
 
	} data;

} strategyCloud_GetDevCloudStrategyListResponse;

C_API strategyCloud_GetDevCloudStrategyListResponse *HSAPI_INIT(strategyCloud_GetDevCloudStrategyListResponse);

#endif
