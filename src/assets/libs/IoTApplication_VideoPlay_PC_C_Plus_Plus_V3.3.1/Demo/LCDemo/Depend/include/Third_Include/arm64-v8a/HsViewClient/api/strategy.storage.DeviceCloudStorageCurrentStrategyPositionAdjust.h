/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_DeviceCloudStorageCurrentStrategyPositionAdjust_H_
#define _HSVIEW_CLIENT_API_strategyStorage_DeviceCloudStorageCurrentStrategyPositionAdjust_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
更换设备正在使用的云存储套餐

【使用平台账号签名】
 */

typedef struct strategyStorage_DeviceCloudStorageCurrentStrategyPositionAdjustRequest 
{
	HsviewRequest base;

	struct strategyStorage_DeviceCloudStorageCurrentStrategyPositionAdjustRequestData
	{
		
		/** 列队的设备套餐id */
		CSTR waitDeviceStrategyListId;
		/** 设备通道号 */
		CSTR channelId;
		/** 正在使用的设备套餐id */
		CSTR currentDeviceStrategyListId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} strategyStorage_DeviceCloudStorageCurrentStrategyPositionAdjustRequest;

C_API strategyStorage_DeviceCloudStorageCurrentStrategyPositionAdjustRequest *HSAPI_INIT(strategyStorage_DeviceCloudStorageCurrentStrategyPositionAdjustRequest);

typedef struct strategyStorage_DeviceCloudStorageCurrentStrategyPositionAdjustResponse 
{
	HsviewResponse base;

	struct strategyStorage_DeviceCloudStorageCurrentStrategyPositionAdjustResponseData
	{
		
		/** 操作结果， success: 成功; uptoOperationNumbers:操作失败，操作次数已达上限;freeStrategyNotSupport：操作失败，免费套餐不支持更换;strategyListIdInvalid：操作失败，套餐id无效;currentStrategyAutoRenewal:当前正在使用的套餐为自动续费套餐，不支持更换 */
		CSTR result;
 
	} data;

} strategyStorage_DeviceCloudStorageCurrentStrategyPositionAdjustResponse;

C_API strategyStorage_DeviceCloudStorageCurrentStrategyPositionAdjustResponse *HSAPI_INIT(strategyStorage_DeviceCloudStorageCurrentStrategyPositionAdjustResponse);

#endif
