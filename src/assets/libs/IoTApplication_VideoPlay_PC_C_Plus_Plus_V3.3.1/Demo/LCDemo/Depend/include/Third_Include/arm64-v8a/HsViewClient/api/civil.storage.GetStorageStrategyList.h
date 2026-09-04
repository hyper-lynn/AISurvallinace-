/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetStorageStrategyList_H_
#define _HSVIEW_CLIENT_API_GetStorageStrategyList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询云存储策略列表。
【使用平台账号签名】
 */

typedef struct GetStorageStrategyListRequest 
{
	HsviewRequest base;

	struct GetStorageStrategyListRequestData
	{
		
		/** [O]设备ID */
		CSTR deviceId;

	} data;

} GetStorageStrategyListRequest;

C_API GetStorageStrategyListRequest *HSAPI_INIT(GetStorageStrategyListRequest);

typedef struct GetStorageStrategyListResponse 
{
	HsviewResponse base;

	struct GetStorageStrategyListResponseData
	{
		
		/** define a list with struct of GetStorageStrategyListResponseData_StrategiesElement */
		DECLARE_LIST(struct GetStorageStrategyListResponseData_StrategiesElement
		{
			/** 上传云存储的码流时段，alarm/always，分别表示报警时上传和全时段上传。 */
			CSTR streamInterval;
			/** [int]录像存储天数 */
			int recordStorageTimeLimit;
			/** [int]报警存储天数 */
			int alarmStorageTimeLimit;
			/** [bool]是否有服务期限，若有，则关注timeLimit字段 */
			BOOL hasTimeLimit;
			/** 费用 */
			CSTR fee;
			/** [long]云存储套餐ID */
			int64 strategyId;
			/** [int]云存储服务期限（天） */
			int timeLimit;
			/** [int]抓图最小间隔，单位秒 */
			int snapInterval;
			/** 套餐名称 */
			CSTR name;
		}) strategies;
 
	} data;

} GetStorageStrategyListResponse;

C_API GetStorageStrategyListResponse *HSAPI_INIT(GetStorageStrategyListResponse);

#endif
