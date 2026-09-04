/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QuerySocketPowerConsumption_H_
#define _HSVIEW_CLIENT_API_QuerySocketPowerConsumption_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询指定通道号插座的耗电量。

单位：千瓦时（度）
Daily：日耗电量
Month：月耗电量，节点值包含至少28个数据，用逗号隔开，从左往右分别表示从今天起往前推至少28天的每日用电量。
Total：单个插座累计耗电

如果channel-id为All：
Daily：表示当前所有插座当日耗电量总和；
Month：节点值包含至少28个数据，用逗号隔开，从左往右分别表示从今天起往前推至少28天的当前所有插座的每天的耗电量总和；
Total：当前所有插座的历史总耗电量总和；
此时ZBDeviceID可省略。
 */

typedef struct QuerySocketPowerConsumptionRequest 
{
	HsviewRequest base;

	struct QuerySocketPowerConsumptionRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 通道号 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_QuerySocketPowerConsumptionRequestData_METHOD "POST"
		/** [cstr]ihg-cmd/getZBDevicePowerConsumption */
		#define _STATIC_QuerySocketPowerConsumptionRequestData_CMD "ihg-cmd/getZBDevicePowerConsumption"
		/** struct of QuerySocketPowerConsumptionRequestData_Body */
		struct QuerySocketPowerConsumptionRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} QuerySocketPowerConsumptionRequest;

C_API QuerySocketPowerConsumptionRequest *HSAPI_INIT(QuerySocketPowerConsumptionRequest);

typedef struct QuerySocketPowerConsumptionResponse 
{
	HsviewResponse base;

	struct QuerySocketPowerConsumptionResponseData
	{
		
		/** [double]总计用电量 */
		double Total;
		/** [double]当天用电量 */
		double Daily;
		/** 配件ID */
		CSTR ZBDeviceID;
		/** 本月每天的用电量，如：“0,0,5,10,0,5,…,10,20” */
		CSTR Month;
 
	} data;

} QuerySocketPowerConsumptionResponse;

C_API QuerySocketPowerConsumptionResponse *HSAPI_INIT(QuerySocketPowerConsumptionResponse);

#endif
