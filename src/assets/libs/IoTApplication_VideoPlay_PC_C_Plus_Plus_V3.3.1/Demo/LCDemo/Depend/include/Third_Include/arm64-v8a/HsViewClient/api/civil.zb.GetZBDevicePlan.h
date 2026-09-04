/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetZBDevicePlan_H_
#define _HSVIEW_CLIENT_API_GetZBDevicePlan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取配件开关计划。
【需要使用平台账号签名】
 */

typedef struct GetZBDevicePlanRequest 
{
	HsviewRequest base;

	struct GetZBDevicePlanRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 盒子的设备ID */
		CSTR deviceId;

	} data;

} GetZBDevicePlanRequest;

C_API GetZBDevicePlanRequest *HSAPI_INIT(GetZBDevicePlanRequest);

typedef struct GetZBDevicePlanResponse 
{
	HsviewResponse base;

	struct GetZBDevicePlanResponseData
	{
		
		/** define a list with struct of GetZBDevicePlanResponseData_ActionsElement */
		DECLARE_LIST(struct GetZBDevicePlanResponseData_ActionsElement
		{
			/** 切换为什么状态，on或off */
			CSTR operation;
			/** 该条action是否开启，on或off */
			CSTR state;
			/** 重复周期 */
			CSTR period;
			/** 切换时间点 */
			CSTR time;
		}) actions;
 
	} data;

} GetZBDevicePlanResponse;

C_API GetZBDevicePlanResponse *HSAPI_INIT(GetZBDevicePlanResponse);

#endif
