/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceCloudList_H_
#define _LC_OPENAPI_CLIENT_DeviceCloudList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询设备通道下所有云存储服务
 */

typedef struct DeviceCloudListRequest 
{
	LCOpenApiRequest base;

	struct DeviceCloudListRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} DeviceCloudListRequest;

C_API DeviceCloudListRequest *LCOPENAPI_INIT(DeviceCloudListRequest);

typedef struct DeviceCloudListResponse 
{
	LCOpenApiResponse base;

	struct DeviceCloudListResponseData
	{
		
		/** define a list with struct of DeviceCloudListResponseData_StrategiesElement */
		DECLARE_LIST(struct DeviceCloudListResponseData_StrategiesElement
		{
			/** 云存储套餐结束时间，格式2020/05/09，永久免费套餐endTime时间可为空 */
			CSTR endTime;
			/** 录像保存天数 */
			CSTR recordSaveDays;
			/** 云存储唯一id */
			CSTR deviceCloudId;
			/** [int] 套餐收费类型，1-收费套餐，2-普通的存在结束时间的免费套餐，3-永久免费套餐 */
			int cloudType;
			/** 云存储策略id */
			CSTR strategyId;
			/** [int] 云存储套餐使用状态，1-正在使用，2-列队状态， 3-套餐过期 */
			int cloudStatus;
			/** [int] 当前使用的云存储状态，1-云存储开启，0-云存储关闭 */
			int useStatus;
			/** 云存储套餐开始时间，格式2019/05/10 */
			CSTR startTime;
			/** [int]剩余有效天数，永久套餐为-1 */
			int validDays;
		}) strategies;
 
	} data;

} DeviceCloudListResponse;

C_API DeviceCloudListResponse *LCOPENAPI_INIT(DeviceCloudListResponse);

#endif
