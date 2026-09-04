/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_DeviceCloudStorageStrategyStopToUserRepository_H_
#define _HSVIEW_CLIENT_API_strategyStorage_DeviceCloudStorageStrategyStopToUserRepository_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
停用设备中列队的套餐至用户库存

【使用平台账号签名】
 */

typedef struct strategyStorage_DeviceCloudStorageStrategyStopToUserRepositoryRequest 
{
	HsviewRequest base;

	struct strategyStorage_DeviceCloudStorageStrategyStopToUserRepositoryRequestData
	{
		
		/** 设备通道号 */
		CSTR channelId;
		/** 设备套餐id */
		CSTR deviceStrategyListId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} strategyStorage_DeviceCloudStorageStrategyStopToUserRepositoryRequest;

C_API strategyStorage_DeviceCloudStorageStrategyStopToUserRepositoryRequest *HSAPI_INIT(strategyStorage_DeviceCloudStorageStrategyStopToUserRepositoryRequest);

typedef struct strategyStorage_DeviceCloudStorageStrategyStopToUserRepositoryResponse 
{
	HsviewResponse base;

	struct strategyStorage_DeviceCloudStorageStrategyStopToUserRepositoryResponseData
	{
		
		/** success: 操作成功， uptoOperationNumbers:操作失败，操作次数已达上限 freeStrategyNotSupport：操作失败，免费套餐不支持停用， strategyListIdInvalid：操作失败，套餐id无效 */
		CSTR result;
 
	} data;

} strategyStorage_DeviceCloudStorageStrategyStopToUserRepositoryResponse;

C_API strategyStorage_DeviceCloudStorageStrategyStopToUserRepositoryResponse *HSAPI_INIT(strategyStorage_DeviceCloudStorageStrategyStopToUserRepositoryResponse);

#endif
