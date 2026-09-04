/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_DeviceCloudStorageStrategyBatchGet_H_
#define _HSVIEW_CLIENT_API_strategyStorage_DeviceCloudStorageStrategyBatchGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
批量获取设备云存储详情

【使用平台账号签名】
 */

typedef struct strategyStorage_DeviceCloudStorageStrategyBatchGetRequest 
{
	HsviewRequest base;

	struct strategyStorage_DeviceCloudStorageStrategyBatchGetRequestData
	{
		
		/** define a list with struct of strategyStorage_DeviceCloudStorageStrategyBatchGetRequestData_DeviceListElement */
		DECLARE_LIST(struct strategyStorage_DeviceCloudStorageStrategyBatchGetRequestData_DeviceListElement
		{
			/** 通道号 */
			CSTR channelId;
			/** 设备ID */
			CSTR deviceId;
		}) deviceList;

	} data;

} strategyStorage_DeviceCloudStorageStrategyBatchGetRequest;

C_API strategyStorage_DeviceCloudStorageStrategyBatchGetRequest *HSAPI_INIT(strategyStorage_DeviceCloudStorageStrategyBatchGetRequest);

typedef struct strategyStorage_DeviceCloudStorageStrategyBatchGetResponse 
{
	HsviewResponse base;

	struct strategyStorage_DeviceCloudStorageStrategyBatchGetResponseData
	{
		
		/** define a list with struct of strategyStorage_DeviceCloudStorageStrategyBatchGetResponseData_DeviceStoragesElement */
		DECLARE_LIST(struct strategyStorage_DeviceCloudStorageStrategyBatchGetResponseData_DeviceStoragesElement
		{
			/** on：云录像开启，off 云录像关闭 */
			CSTR recordSwitchStatus;
			/** 云存储状态 notExist:未开通套餐，using：开通云存储且没有过期， expired：套餐过期 */
			CSTR currentStrategyStatus;
			/** define a list with struct of strategyStorage_DeviceCloudStorageStrategyBatchGetResponseData_DeviceStoragesElement_StrategiesElement */
			DECLARE_LIST(struct strategyStorage_DeviceCloudStorageStrategyBatchGetResponseData_DeviceStoragesElement_StrategiesElement
			{
				/** charge：收费套餐，normalFree：普通的存在结束时间的免费套餐，foreverFree:永久免费套餐，autoRenewal:自动续费套餐 */
				CSTR strategyType;
				/** 表记录id */
				CSTR deviceStrategyListId;
				/** [O]失效时间，yyyyMMddTHHmmssZ格式，当strategyType为3时，就是永久免费时，endTime无效，可为空 */
				CSTR endTime;
				/** 生效时间，yyyyMMddTHHmmssZ格式 */
				CSTR startTime;
				/** using：正在使用，waiting：列队状态， expired：套餐过期 */
				CSTR strategyStatus;
				/** 录像保存天数 */
				CSTR recordSaveDays;
			}) strategies;
			/** 通道号 */
			CSTR channelId;
			/** notExist：不存在免费套餐，existNotUsed：存在免费套餐且未使用，expired：已使用过免费套餐，且过期, using:免费套餐已启用，未过期 */
			CSTR freeStrategyStatus;
			/** 设备ID */
			CSTR deviceId;
		}) deviceStorages;
 
	} data;

} strategyStorage_DeviceCloudStorageStrategyBatchGetResponse;

C_API strategyStorage_DeviceCloudStorageStrategyBatchGetResponse *HSAPI_INIT(strategyStorage_DeviceCloudStorageStrategyBatchGetResponse);

#endif
