/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUserPowerConsumptionStatistics_H_
#define _HSVIEW_CLIENT_API_GetUserPowerConsumptionStatistics_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询当前用户耗电量的统计。
【需要使用平台账号签名】
 */

typedef struct GetUserPowerConsumptionStatisticsRequest 
{
	HsviewRequest base;

	struct GetUserPowerConsumptionStatisticsRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetUserPowerConsumptionStatisticsRequest;

C_API GetUserPowerConsumptionStatisticsRequest *HSAPI_INIT(GetUserPowerConsumptionStatisticsRequest);

typedef struct GetUserPowerConsumptionStatisticsResponse 
{
	HsviewResponse base;

	struct GetUserPowerConsumptionStatisticsResponseData
	{
		
		/** [double]从昨天开始，前一个月每天的耗电量，数组形式表示 */
		DECLARE_LIST(double) month;
		/** [double]总耗电量 */
		double total;
 
	} data;

} GetUserPowerConsumptionStatisticsResponse;

C_API GetUserPowerConsumptionStatisticsResponse *HSAPI_INIT(GetUserPowerConsumptionStatisticsResponse);

#endif
