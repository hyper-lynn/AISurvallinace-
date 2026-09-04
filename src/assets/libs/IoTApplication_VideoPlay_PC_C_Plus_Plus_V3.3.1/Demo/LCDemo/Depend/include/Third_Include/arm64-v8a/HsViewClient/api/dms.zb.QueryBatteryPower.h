/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryBatteryPower_H_
#define _HSVIEW_CLIENT_API_QueryBatteryPower_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询指定通道号的配件电池电量。
BatteryPower：电量百分比数
【使用平台账号签名】
 */

typedef struct QueryBatteryPowerRequest 
{
	HsviewRequest base;

	struct QueryBatteryPowerRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 通道号 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_QueryBatteryPowerRequestData_METHOD "GET"
		/** [cstr]ihg-cmd/getZBDeviceBatteryPower */
		#define _STATIC_QueryBatteryPowerRequestData_CMD "ihg-cmd/getZBDeviceBatteryPower"
		/** struct of QueryBatteryPowerRequestData_Body */
		struct QueryBatteryPowerRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} QueryBatteryPowerRequest;

C_API QueryBatteryPowerRequest *HSAPI_INIT(QueryBatteryPowerRequest);

typedef struct QueryBatteryPowerResponse 
{
	HsviewResponse base;

	struct QueryBatteryPowerResponseData
	{
		
		/** [int]剩余电量百分比 */
		int BatteryPower;
 
	} data;

} QueryBatteryPowerResponse;

C_API QueryBatteryPowerResponse *HSAPI_INIT(QueryBatteryPowerResponse);

#endif
