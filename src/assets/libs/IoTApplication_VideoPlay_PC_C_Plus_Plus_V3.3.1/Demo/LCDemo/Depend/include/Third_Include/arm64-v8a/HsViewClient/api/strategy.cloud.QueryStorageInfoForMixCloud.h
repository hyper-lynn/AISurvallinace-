/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyCloud_QueryStorageInfoForMixCloud_H_
#define _HSVIEW_CLIENT_API_strategyCloud_QueryStorageInfoForMixCloud_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
混合云后台（Z-OMS）查询套餐信息，deviceIds为JSON数组
storageInfo：通道当前正在使用的套餐相关信息，为空，说明通道当前没有套餐或者通道的套餐全部过期
【需要使用默认ak，sk鉴权】
 */

typedef struct strategyCloud_QueryStorageInfoForMixCloudRequest 
{
	HsviewRequest base;

	struct strategyCloud_QueryStorageInfoForMixCloudRequestData
	{
		
		/** 页数 */
		CSTR pageNum;
		/** 每页的条数 */
		CSTR pageSize;
		/** 设备序列号 */
		DECLARE_LIST(CSTR) deviceIds;

	} data;

} strategyCloud_QueryStorageInfoForMixCloudRequest;

C_API strategyCloud_QueryStorageInfoForMixCloudRequest *HSAPI_INIT(strategyCloud_QueryStorageInfoForMixCloudRequest);

typedef struct strategyCloud_QueryStorageInfoForMixCloudResponse 
{
	HsviewResponse base;

	struct strategyCloud_QueryStorageInfoForMixCloudResponseData
	{
		
		/** [int]套餐总数（只包括使用中） */
		int count;
		/** define a list with struct of strategyCloud_QueryStorageInfoForMixCloudResponseData_StorageInfosElement */
		DECLARE_LIST(struct strategyCloud_QueryStorageInfoForMixCloudResponseData_StorageInfosElement
		{
			/** 套餐Id */
			CSTR storageId;
			/** [long][O]结束时间，精确到ms,如果endTime字段没有，表示为永久免费套餐 */
			int64 endTime;
			/** 通道号 */
			CSTR channelId;
			/** [long]开始时间，精确到ms */
			int64 startTime;
			/** 设备序列号 */
			CSTR deviceId;
		}) storageInfos;
 
	} data;

} strategyCloud_QueryStorageInfoForMixCloudResponse;

C_API strategyCloud_QueryStorageInfoForMixCloudResponse *HSAPI_INIT(strategyCloud_QueryStorageInfoForMixCloudResponse);

#endif
