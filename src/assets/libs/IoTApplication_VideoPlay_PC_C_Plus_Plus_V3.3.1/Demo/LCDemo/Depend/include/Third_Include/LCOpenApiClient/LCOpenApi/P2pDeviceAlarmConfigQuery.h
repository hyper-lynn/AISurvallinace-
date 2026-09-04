/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_P2pDeviceAlarmConfigQuery_H_
#define _LC_OPENAPI_CLIENT_P2pDeviceAlarmConfigQuery_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取P2P设备告警订阅信息
 */

typedef struct P2pDeviceAlarmConfigQueryRequest 
{
	LCOpenApiRequest base;

	struct P2pDeviceAlarmConfigQueryRequestData
	{
		
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		DECLARE_LIST(CSTR) deviceIds;

	} data;

} P2pDeviceAlarmConfigQueryRequest;

C_API P2pDeviceAlarmConfigQueryRequest *LCOPENAPI_INIT(P2pDeviceAlarmConfigQueryRequest);

typedef struct P2pDeviceAlarmConfigQueryResponse 
{
	LCOpenApiResponse base;

	struct P2pDeviceAlarmConfigQueryResponseData
	{
		
		/** define a list with struct of P2pDeviceAlarmConfigQueryResponseData_DeviceListElement */
		DECLARE_LIST(struct P2pDeviceAlarmConfigQueryResponseData_DeviceListElement
		{
			/** define a list with struct of P2pDeviceAlarmConfigQueryResponseData_DeviceListElement_ConfigsElement */
			DECLARE_LIST(struct P2pDeviceAlarmConfigQueryResponseData_DeviceListElement_ConfigsElement
			{
				/** [int]索引号 */
				DECLARE_LIST(int) Indexs;
				/** 告警类型，如Motion Detection */
				CSTR code;
			}) configs;
			/** 设备id */
			CSTR deviceId;
		}) deviceList;
 
	} data;

} P2pDeviceAlarmConfigQueryResponse;

C_API P2pDeviceAlarmConfigQueryResponse *LCOPENAPI_INIT(P2pDeviceAlarmConfigQueryResponse);

#endif
