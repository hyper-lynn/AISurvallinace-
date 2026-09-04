/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_DeviceCloudStorageFreeStrategySetToDevice_H_
#define _HSVIEW_CLIENT_API_strategyStorage_DeviceCloudStorageFreeStrategySetToDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
试用免费套餐


【使用平台账号签名】
 */

typedef struct strategyStorage_DeviceCloudStorageFreeStrategySetToDeviceRequest 
{
	HsviewRequest base;

	struct strategyStorage_DeviceCloudStorageFreeStrategySetToDeviceRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} strategyStorage_DeviceCloudStorageFreeStrategySetToDeviceRequest;

C_API strategyStorage_DeviceCloudStorageFreeStrategySetToDeviceRequest *HSAPI_INIT(strategyStorage_DeviceCloudStorageFreeStrategySetToDeviceRequest);

typedef struct strategyStorage_DeviceCloudStorageFreeStrategySetToDeviceResponse 
{
	HsviewResponse base;

	struct strategyStorage_DeviceCloudStorageFreeStrategySetToDeviceResponseData
	{
		
		/** success：开通成功， freeStrategyNotExist：开通失败，不存在免费套餐，freeStrategyAlreadyUsed：开通失败，免费套餐已开通（正在用、列队或者已过期，总之已经用了）,deviceExistAutoRenewal:当前设备存在自动续费套餐，开通失败 */
		CSTR result;
 
	} data;

} strategyStorage_DeviceCloudStorageFreeStrategySetToDeviceResponse;

C_API strategyStorage_DeviceCloudStorageFreeStrategySetToDeviceResponse *HSAPI_INIT(strategyStorage_DeviceCloudStorageFreeStrategySetToDeviceResponse);

#endif
