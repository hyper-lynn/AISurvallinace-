/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_DeviceCloudStorageStrategyListGet_H_
#define _HSVIEW_CLIENT_API_strategyStorage_DeviceCloudStorageStrategyListGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备云存储详情

【使用平台账号签名】
 */

typedef struct strategyStorage_DeviceCloudStorageStrategyListGetRequest 
{
	HsviewRequest base;

	struct strategyStorage_DeviceCloudStorageStrategyListGetRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} strategyStorage_DeviceCloudStorageStrategyListGetRequest;

C_API strategyStorage_DeviceCloudStorageStrategyListGetRequest *HSAPI_INIT(strategyStorage_DeviceCloudStorageStrategyListGetRequest);

typedef struct strategyStorage_DeviceCloudStorageStrategyListGetResponse 
{
	HsviewResponse base;

	struct strategyStorage_DeviceCloudStorageStrategyListGetResponseData
	{
		
		/** on：云录像开启，off 云录像关闭 */
		CSTR recordSwitchStatus;
		/** 设备通道名称 */
		CSTR channelName;
		/** 云存储状态 notExist:未开通套餐，using：开通云存储且没有过期， expired：套餐过期 */
		CSTR currentStrategyStatus;
		/** define a list with struct of strategyStorage_DeviceCloudStorageStrategyListGetResponseData_StrategiesElement */
		DECLARE_LIST(struct strategyStorage_DeviceCloudStorageStrategyListGetResponseData_StrategiesElement
		{
			/** 套餐id */
			CSTR strategyId;
			/** charge：收费套餐，normalFree：普通的存在结束时间的免费套餐，foreverFree:永久免费套餐，autoRenewal:自动续费套餐 */
			CSTR strategyType;
			/** 表记录id */
			CSTR deviceStrategyListId;
			/** [int][O]套餐剩余天数，当strategyType为3时，就是永久免费时，remainDays无效，可为空 */
			int remainDays;
			/** [O]失效时间，yyyyMMddTHHmmssZ格式，当strategyType为3时，就是永久免费时，endTime无效，可为空 */
			CSTR endTime;
			/** 生效时间，yyyyMMddTHHmmssZ格式 */
			CSTR startTime;
			/** using：正在使用，waiting：列队状态， expired：套餐过期 */
			CSTR strategyStatus;
			/** 录像保存天数 */
			CSTR recordSaveDays;
		}) strategies;
		/** [O]是否存在待支付订单。1-存在待支付订单 0-不存在待支付订单（amcrest定制） */
		CSTR isExistNoPayOrder;
		/** [O]自动续费状态。on：开启，off：关闭，failBalance：续费失败（amcrest定制） */
		CSTR autoRenewalStatus;
		/** notExist：不存在免费套餐，existNotUsed：存在免费套餐且未使用，expired：已使用过免费套餐，且过期, using:免费套餐已启用，未过期 */
		CSTR freeStrategyStatus;
 
	} data;

} strategyStorage_DeviceCloudStorageStrategyListGetResponse;

C_API strategyStorage_DeviceCloudStorageStrategyListGetResponse *HSAPI_INIT(strategyStorage_DeviceCloudStorageStrategyListGetResponse);

#endif
