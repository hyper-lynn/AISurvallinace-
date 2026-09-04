/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_CreateCloudStorageStrategy_H_
#define _HSVIEW_CLIENT_API_strategyStorage_CreateCloudStorageStrategy_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
OMS项目的app点击开通云存储功能（目前只为混合云项目开发，后续其他项目待讨论）

【使用平台账号签名】
 */

typedef struct strategyStorage_CreateCloudStorageStrategyRequest 
{
	HsviewRequest base;

	struct strategyStorage_CreateCloudStorageStrategyRequestData
	{
		
		/** 云录像码流类型, main:主码流、extra1：辅码流1 */
		CSTR streamType;
		/** 云存储类型：alarmCloudStorage-普通的动检录像云存储,alwaysCloudStorage-连续录像的云存储 */
		CSTR strategyType;
		/** 套餐id */
		CSTR strategyId;
		/** 云录像保存天数（天） */
		CSTR recordSaveDays;
		/** 通道号 */
		CSTR channelId;
		/** 套餐服务时长（秒） */
		CSTR serviceTime;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} strategyStorage_CreateCloudStorageStrategyRequest;

C_API strategyStorage_CreateCloudStorageStrategyRequest *HSAPI_INIT(strategyStorage_CreateCloudStorageStrategyRequest);

typedef struct strategyStorage_CreateCloudStorageStrategyResponse 
{
	HsviewResponse base;

	struct strategyStorage_CreateCloudStorageStrategyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} strategyStorage_CreateCloudStorageStrategyResponse;

C_API strategyStorage_CreateCloudStorageStrategyResponse *HSAPI_INIT(strategyStorage_CreateCloudStorageStrategyResponse);

#endif
