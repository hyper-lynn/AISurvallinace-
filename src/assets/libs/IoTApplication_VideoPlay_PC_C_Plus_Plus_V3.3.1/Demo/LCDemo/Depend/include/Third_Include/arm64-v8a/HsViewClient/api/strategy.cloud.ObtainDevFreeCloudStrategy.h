/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyCloud_ObtainDevFreeCloudStrategy_H_
#define _HSVIEW_CLIENT_API_strategyCloud_ObtainDevFreeCloudStrategy_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备通道领取云服务免费套餐
错误码：
13511：免费套餐不存在
【需要使用平台账号签名】
 */

typedef struct strategyCloud_ObtainDevFreeCloudStrategyRequest 
{
	HsviewRequest base;

	struct strategyCloud_ObtainDevFreeCloudStrategyRequestData
	{
		
		/** storage:云存储；wonderful：精彩一天 */
		DECLARE_LIST(CSTR) type;
		/** 通道号 */
		CSTR channelId;
		/** [long]云服务套餐id */
		int64 strategyId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} strategyCloud_ObtainDevFreeCloudStrategyRequest;

C_API strategyCloud_ObtainDevFreeCloudStrategyRequest *HSAPI_INIT(strategyCloud_ObtainDevFreeCloudStrategyRequest);

typedef struct strategyCloud_ObtainDevFreeCloudStrategyResponse 
{
	HsviewResponse base;

	struct strategyCloud_ObtainDevFreeCloudStrategyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} strategyCloud_ObtainDevFreeCloudStrategyResponse;

C_API strategyCloud_ObtainDevFreeCloudStrategyResponse *HSAPI_INIT(strategyCloud_ObtainDevFreeCloudStrategyResponse);

#endif
