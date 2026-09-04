/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetStrategies_H_
#define _HSVIEW_CLIENT_API_GetStrategies_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取平台提供的云存储套餐列表
 */

typedef struct GetStrategiesRequest 
{
	HsviewRequest base;

	struct GetStrategiesRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetStrategiesRequest;

C_API GetStrategiesRequest *HSAPI_INIT(GetStrategiesRequest);

typedef struct GetStrategiesResponse 
{
	HsviewResponse base;

	struct GetStrategiesResponseData
	{
		
		/** define a list with struct of GetStrategiesResponseData_StrategiesElement */
		DECLARE_LIST(struct GetStrategiesResponseData_StrategiesElement
		{
			/** [int]录像存储天数 */
			int recordStorageTimeLimit;
			/** 云存储套餐名称 */
			CSTR name;
			/** [long]云存储套餐ID */
			int64 strategyId;
			/** [int]云存储服务期限（天） */
			int timeLimit;
			/** 套餐说明 */
			CSTR description;
			/** 云存储套餐URL,图片内部包含套餐信息 */
			CSTR picUrl;
			/** [double]费用 */
			double fee;
		}) strategies;
 
	} data;

} GetStrategiesResponse;

C_API GetStrategiesResponse *HSAPI_INIT(GetStrategiesResponse);

#endif
