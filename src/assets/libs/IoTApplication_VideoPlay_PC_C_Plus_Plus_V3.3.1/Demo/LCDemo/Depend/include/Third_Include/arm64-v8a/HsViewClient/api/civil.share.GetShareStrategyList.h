/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetShareStrategyList_H_
#define _HSVIEW_CLIENT_API_GetShareStrategyList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取平台中设备的分享、授权套餐列表。
【使用平台账号签名】
 */

typedef struct GetShareStrategyListRequest 
{
	HsviewRequest base;

	struct GetShareStrategyListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetShareStrategyListRequest;

C_API GetShareStrategyListRequest *HSAPI_INIT(GetShareStrategyListRequest);

typedef struct GetShareStrategyListResponse 
{
	HsviewResponse base;

	struct GetShareStrategyListResponseData
	{
		
		/** define a list with struct of GetShareStrategyListResponseData_StrategiesElement */
		DECLARE_LIST(struct GetShareStrategyListResponseData_StrategiesElement
		{
			/** 套餐名称 */
			CSTR name;
			/** [long]套餐id */
			int64 strategyId;
			/** 套餐图片url */
			CSTR picUrl;
			/** 套餐描述 */
			CSTR description;
			/** [double]套餐单价 */
			double fee;
			/** [int]套餐有效期（单位日） */
			int validTime;
		}) strategies;
 
	} data;

} GetShareStrategyListResponse;

C_API GetShareStrategyListResponse *HSAPI_INIT(GetShareStrategyListResponse);

#endif
