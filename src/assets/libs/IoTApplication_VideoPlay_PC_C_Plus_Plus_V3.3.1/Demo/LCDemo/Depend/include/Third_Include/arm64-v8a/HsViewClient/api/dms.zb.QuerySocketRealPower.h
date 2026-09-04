/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QuerySocketRealPower_H_
#define _HSVIEW_CLIENT_API_QuerySocketRealPower_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询指定通道号插座的当前功率。
RealPower：瓦
如果channel-id为All，表示获取当前所有Zigbee设备功率总和。此时回复内容中不需要ZBDeviceID字段。
 */

typedef struct QuerySocketRealPowerRequest 
{
	HsviewRequest base;

	struct QuerySocketRealPowerRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 通道号 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_QuerySocketRealPowerRequestData_METHOD "GET"
		/** [cstr]ihg-cmd/getZBDeviceRealPower */
		#define _STATIC_QuerySocketRealPowerRequestData_CMD "ihg-cmd/getZBDeviceRealPower"
		/** struct of QuerySocketRealPowerRequestData_Body */
		struct QuerySocketRealPowerRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} QuerySocketRealPowerRequest;

C_API QuerySocketRealPowerRequest *HSAPI_INIT(QuerySocketRealPowerRequest);

typedef struct QuerySocketRealPowerResponse 
{
	HsviewResponse base;

	struct QuerySocketRealPowerResponseData
	{
		
		/** 配件ID */
		CSTR ZBDeviceID;
		/** [double]瓦数 */
		double RealPower;
 
	} data;

} QuerySocketRealPowerResponse;

C_API QuerySocketRealPowerResponse *HSAPI_INIT(QuerySocketRealPowerResponse);

#endif
