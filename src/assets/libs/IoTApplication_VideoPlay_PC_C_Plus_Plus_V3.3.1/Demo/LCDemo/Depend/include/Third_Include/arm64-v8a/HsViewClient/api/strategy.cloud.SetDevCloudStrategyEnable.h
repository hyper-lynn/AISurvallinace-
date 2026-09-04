/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyCloud_SetDevCloudStrategyEnable_H_
#define _HSVIEW_CLIENT_API_strategyCloud_SetDevCloudStrategyEnable_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备云服务套餐状态，strategy为-1表示暂停套餐，否则为打开套餐
错误码：
13504：操作套餐不存在
【需要使用平台账号签名】
 */

typedef struct strategyCloud_SetDevCloudStrategyEnableRequest 
{
	HsviewRequest base;

	struct strategyCloud_SetDevCloudStrategyEnableRequestData
	{
		
		/** [int]云服务套餐操作。若operation为2表示暂停套餐，1为打开套餐 */
		int operation;
		/** 通道号 */
		CSTR channelId;
		/** storage:云存储；wonderful：精彩一天 */
		DECLARE_LIST(CSTR) type;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} strategyCloud_SetDevCloudStrategyEnableRequest;

C_API strategyCloud_SetDevCloudStrategyEnableRequest *HSAPI_INIT(strategyCloud_SetDevCloudStrategyEnableRequest);

typedef struct strategyCloud_SetDevCloudStrategyEnableResponse 
{
	HsviewResponse base;

	struct strategyCloud_SetDevCloudStrategyEnableResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} strategyCloud_SetDevCloudStrategyEnableResponse;

C_API strategyCloud_SetDevCloudStrategyEnableResponse *HSAPI_INIT(strategyCloud_SetDevCloudStrategyEnableResponse);

#endif
