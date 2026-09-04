/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_DeviceCloudStorageStrategyTransfer_H_
#define _HSVIEW_CLIENT_API_strategyStorage_DeviceCloudStorageStrategyTransfer_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备转移云存储

【使用平台账号签名】
 */

typedef struct strategyStorage_DeviceCloudStorageStrategyTransferRequest 
{
	HsviewRequest base;

	struct strategyStorage_DeviceCloudStorageStrategyTransferRequestData
	{
		
		/** 设备通道号 */
		CSTR acceptChannelId;
		/** 设备ID */
		CSTR acceptDeviceId;
		/** 设备套餐id */
		CSTR deviceStrategyListId;
		/** 设备通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} strategyStorage_DeviceCloudStorageStrategyTransferRequest;

C_API strategyStorage_DeviceCloudStorageStrategyTransferRequest *HSAPI_INIT(strategyStorage_DeviceCloudStorageStrategyTransferRequest);

typedef struct strategyStorage_DeviceCloudStorageStrategyTransferResponse 
{
	HsviewResponse base;

	struct strategyStorage_DeviceCloudStorageStrategyTransferResponseData
	{
		
		/** success: 操作成功；uptoOperationNumbers:操作失败，操作次数已达上限；freeStrategyNotSupport：操作失败，免费套餐不支持转移；strategyListIdInvalid：操作失败，套餐id无效；acceptDeviceExistAutoRenewal:接受转移的设备存在自动续费套餐 */
		CSTR result;
 
	} data;

} strategyStorage_DeviceCloudStorageStrategyTransferResponse;

C_API strategyStorage_DeviceCloudStorageStrategyTransferResponse *HSAPI_INIT(strategyStorage_DeviceCloudStorageStrategyTransferResponse);

#endif
