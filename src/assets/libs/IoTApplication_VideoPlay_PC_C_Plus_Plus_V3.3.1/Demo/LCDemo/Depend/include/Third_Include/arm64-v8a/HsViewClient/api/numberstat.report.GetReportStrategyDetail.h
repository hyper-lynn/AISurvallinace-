/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_numberstatReport_GetReportStrategyDetail_H_
#define _HSVIEW_CLIENT_API_numberstatReport_GetReportStrategyDetail_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备报表入口查看客流量统计套餐详情
请求参数：
strategyType:normal普通客流量统计套餐，vip高级客流量统计套餐

【使用平台账号签名】
 */

typedef struct numberstatReport_GetReportStrategyDetailRequest 
{
	HsviewRequest base;

	struct numberstatReport_GetReportStrategyDetailRequestData
	{
		
		/**  [int]报表id */
		CSTR reportId;

	} data;

} numberstatReport_GetReportStrategyDetailRequest;

C_API numberstatReport_GetReportStrategyDetailRequest *HSAPI_INIT(numberstatReport_GetReportStrategyDetailRequest);

typedef struct numberstatReport_GetReportStrategyDetailResponse 
{
	HsviewResponse base;

	struct numberstatReport_GetReportStrategyDetailResponseData
	{
		
		/** [O]报表增值套餐到期时间yyyyMMddTHHmmss,普通报表为空 */
		CSTR endTime;
		/** 报表套餐类型 */
		CSTR strategyType;
		/** [O]报表增值套餐最早购买时间yyyyMMddTHHmmss,普通报表为空 */
		CSTR startTime;
 
	} data;

} numberstatReport_GetReportStrategyDetailResponse;

C_API numberstatReport_GetReportStrategyDetailResponse *HSAPI_INIT(numberstatReport_GetReportStrategyDetailResponse);

#endif
