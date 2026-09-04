/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_UserCloudStorageStrategyRepositorySetToDevice_H_
#define _HSVIEW_CLIENT_API_strategyStorage_UserCloudStorageStrategyRepositorySetToDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

库存套餐启用到设备上

【使用平台账号签名】
 */

typedef struct strategyStorage_UserCloudStorageStrategyRepositorySetToDeviceRequest 
{
	HsviewRequest base;

	struct strategyStorage_UserCloudStorageStrategyRepositorySetToDeviceRequestData
	{
		
		/** define a list with struct of strategyStorage_UserCloudStorageStrategyRepositorySetToDeviceRequestData_RepositoryListElement */
		DECLARE_LIST(struct strategyStorage_UserCloudStorageStrategyRepositorySetToDeviceRequestData_RepositoryListElement
		{
			/** 库存id */
			CSTR repositoryId;
		}) repositoryList;
		/** define a list with struct of strategyStorage_UserCloudStorageStrategyRepositorySetToDeviceRequestData_DevicesElement */
		DECLARE_LIST(struct strategyStorage_UserCloudStorageStrategyRepositorySetToDeviceRequestData_DevicesElement
		{
			/** 设备通道号 */
			CSTR channelId;
			/** 设备序列号 */
			CSTR deviceId;
		}) devices;

	} data;

} strategyStorage_UserCloudStorageStrategyRepositorySetToDeviceRequest;

C_API strategyStorage_UserCloudStorageStrategyRepositorySetToDeviceRequest *HSAPI_INIT(strategyStorage_UserCloudStorageStrategyRepositorySetToDeviceRequest);

typedef struct strategyStorage_UserCloudStorageStrategyRepositorySetToDeviceResponse 
{
	HsviewResponse base;

	struct strategyStorage_UserCloudStorageStrategyRepositorySetToDeviceResponseData
	{
		
		/** success: 操作成功， fail：操作失败，不满足操作条件；currentStrategyAutoRenewal:有设备存在正在使用的套餐为自动续费套餐，不支持下发 */
		CSTR result;
 
	} data;

} strategyStorage_UserCloudStorageStrategyRepositorySetToDeviceResponse;

C_API strategyStorage_UserCloudStorageStrategyRepositorySetToDeviceResponse *HSAPI_INIT(strategyStorage_UserCloudStorageStrategyRepositorySetToDeviceResponse);

#endif
