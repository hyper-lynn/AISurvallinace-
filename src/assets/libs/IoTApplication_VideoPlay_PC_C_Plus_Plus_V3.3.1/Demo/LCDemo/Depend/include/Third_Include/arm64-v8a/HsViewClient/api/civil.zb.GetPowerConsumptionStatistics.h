/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetPowerConsumptionStatistics_H_
#define _HSVIEW_CLIENT_API_GetPowerConsumptionStatistics_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询名下所有配件耗电量的统计。
【需要使用平台账号签名】
 */

typedef struct GetPowerConsumptionStatisticsRequest 
{
	HsviewRequest base;

	struct GetPowerConsumptionStatisticsRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetPowerConsumptionStatisticsRequest;

C_API GetPowerConsumptionStatisticsRequest *HSAPI_INIT(GetPowerConsumptionStatisticsRequest);

typedef struct GetPowerConsumptionStatisticsResponse 
{
	HsviewResponse base;

	struct GetPowerConsumptionStatisticsResponseData
	{
		
		/** define a list with struct of GetPowerConsumptionStatisticsResponseData_DevicesElement */
		DECLARE_LIST(struct GetPowerConsumptionStatisticsResponseData_DevicesElement
		{
			/** define a list with struct of GetPowerConsumptionStatisticsResponseData_DevicesElement_ChannelsElement */
			DECLARE_LIST(struct GetPowerConsumptionStatisticsResponseData_DevicesElement_ChannelsElement
			{
				/** [double]总耗电量 */
				double total;
				/** 配件名称 */
				CSTR name;
				/** [double]从昨天开始，前一个月每天的耗电量，数组形式表示 */
				DECLARE_LIST(double) month;
				/** 配件ID */
				CSTR zbDeviceId;
				/** 通道号 */
				CSTR channelId;
			}) channels;
			/** 设备ID */
			CSTR deviceId;
		}) devices;
 
	} data;

} GetPowerConsumptionStatisticsResponse;

C_API GetPowerConsumptionStatisticsResponse *HSAPI_INIT(GetPowerConsumptionStatisticsResponse);

#endif
