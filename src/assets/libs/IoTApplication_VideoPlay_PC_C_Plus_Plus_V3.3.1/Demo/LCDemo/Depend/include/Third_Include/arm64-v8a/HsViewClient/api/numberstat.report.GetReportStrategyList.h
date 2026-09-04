/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_numberstatReport_GetReportStrategyList_H_
#define _HSVIEW_CLIENT_API_numberstatReport_GetReportStrategyList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取客流量统计套餐列表
请求参数：
strategyType：套餐类型，1收费套餐，0免费试用套餐， 2所有
响应参数：
type：套餐类型，1收费套餐，0免费试用套餐

【使用平台账号签名】
 */

typedef struct numberstatReport_GetReportStrategyListRequest 
{
	HsviewRequest base;

	struct numberstatReport_GetReportStrategyListRequestData
	{
		
		/** [int]套餐类型 */
		int strategyType;

	} data;

} numberstatReport_GetReportStrategyListRequest;

C_API numberstatReport_GetReportStrategyListRequest *HSAPI_INIT(numberstatReport_GetReportStrategyListRequest);

typedef struct numberstatReport_GetReportStrategyListResponse 
{
	HsviewResponse base;

	struct numberstatReport_GetReportStrategyListResponseData
	{
		
		/** define a list with struct of numberstatReport_GetReportStrategyListResponseData_ReportStrategyListElement */
		DECLARE_LIST(struct numberstatReport_GetReportStrategyListResponseData_ReportStrategyListElement
		{
			/** [int]套餐类型 */
			int type;
			/** 套餐名称 */
			CSTR name;
			/** [long]套餐id */
			int64 strategyId;
			/** [double]套餐价格 */
			double price;
			/** 套餐图片地址 */
			CSTR picUrl;
			/** 套餐描述 */
			CSTR describe;
			/** [int]有效时间 */
			int validTime;
		}) reportStrategyList;
 
	} data;

} numberstatReport_GetReportStrategyListResponse;

C_API numberstatReport_GetReportStrategyListResponse *HSAPI_INIT(numberstatReport_GetReportStrategyListResponse);

#endif
