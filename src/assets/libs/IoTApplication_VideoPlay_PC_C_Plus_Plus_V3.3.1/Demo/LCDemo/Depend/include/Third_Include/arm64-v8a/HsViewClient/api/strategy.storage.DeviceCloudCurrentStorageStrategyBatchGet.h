/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_DeviceCloudCurrentStorageStrategyBatchGet_H_
#define _HSVIEW_CLIENT_API_strategyStorage_DeviceCloudCurrentStorageStrategyBatchGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
批量获取设备云存储详情
废弃协议
【使用平台账号签名】
 */

typedef struct strategyStorage_DeviceCloudCurrentStorageStrategyBatchGetRequest 
{
	HsviewRequest base;

	struct strategyStorage_DeviceCloudCurrentStorageStrategyBatchGetRequestData
	{
		
		/** define a list with struct of strategyStorage_DeviceCloudCurrentStorageStrategyBatchGetRequestData_DeviceListElement */
		DECLARE_LIST(struct strategyStorage_DeviceCloudCurrentStorageStrategyBatchGetRequestData_DeviceListElement
		{
			/** 通道号 */
			CSTR channelId;
			/** 设备ID */
			CSTR deviceId;
		}) deviceList;

	} data;

} strategyStorage_DeviceCloudCurrentStorageStrategyBatchGetRequest;

C_API strategyStorage_DeviceCloudCurrentStorageStrategyBatchGetRequest *HSAPI_INIT(strategyStorage_DeviceCloudCurrentStorageStrategyBatchGetRequest);

typedef struct strategyStorage_DeviceCloudCurrentStorageStrategyBatchGetResponse 
{
	HsviewResponse base;

	struct strategyStorage_DeviceCloudCurrentStorageStrategyBatchGetResponseData
	{
		
		/** define a list with struct of strategyStorage_DeviceCloudCurrentStorageStrategyBatchGetResponseData_DeviceStoragesElement */
		DECLARE_LIST(struct strategyStorage_DeviceCloudCurrentStorageStrategyBatchGetResponseData_DeviceStoragesElement
		{
			/** 当前正在使用的云存储状态 notExist:未开通套餐，using：开通云存储且没有过期， expired：套餐过期 */
			CSTR storageStrategyStatus;
			/** on：云录像开启，off 云录像关闭 */
			CSTR recordSwitchStatus;
			/** 列表中最后一个套餐过期时间，当storageStrategyStatus=using时，storageStrategyExpireTime为空：表明永久，不为空表明:套餐总过期时间，套餐过期时间yyyyMMddTHHmmssZ格式 */
			CSTR storageStrategyExpireTime;
			/** 通道号 */
			CSTR channelId;
			/** [O]自动续费状态，on:表示当前正在使用的是自动续费套餐，off：表示为普通套餐。只有在storageStrategyStatus为using状态下才有效。intelbras需求新增字段 */
			CSTR autoRenewalStatus;
			/** 设备ID */
			CSTR deviceId;
		}) deviceStorages;
 
	} data;

} strategyStorage_DeviceCloudCurrentStorageStrategyBatchGetResponse;

C_API strategyStorage_DeviceCloudCurrentStorageStrategyBatchGetResponse *HSAPI_INIT(strategyStorage_DeviceCloudCurrentStorageStrategyBatchGetResponse);

#endif
