/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_DeviceStrategyUnBind_H_
#define _HSVIEW_CLIENT_API_strategyStorage_DeviceStrategyUnBind_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
停用设备中所有收费套餐至用户库存

【使用平台账号签名】
 */

typedef struct strategyStorage_DeviceStrategyUnBindRequest 
{
	HsviewRequest base;

	struct strategyStorage_DeviceStrategyUnBindRequestData
	{
		
		/** 设备通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} strategyStorage_DeviceStrategyUnBindRequest;

C_API strategyStorage_DeviceStrategyUnBindRequest *HSAPI_INIT(strategyStorage_DeviceStrategyUnBindRequest);

typedef struct strategyStorage_DeviceStrategyUnBindResponse 
{
	HsviewResponse base;

	struct strategyStorage_DeviceStrategyUnBindResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} strategyStorage_DeviceStrategyUnBindResponse;

C_API strategyStorage_DeviceStrategyUnBindResponse *HSAPI_INIT(strategyStorage_DeviceStrategyUnBindResponse);

#endif
