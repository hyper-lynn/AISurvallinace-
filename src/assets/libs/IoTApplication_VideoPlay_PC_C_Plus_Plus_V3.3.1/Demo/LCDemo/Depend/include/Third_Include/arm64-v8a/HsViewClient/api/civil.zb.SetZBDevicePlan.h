/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetZBDevicePlan_H_
#define _HSVIEW_CLIENT_API_SetZBDevicePlan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置配件的开关计划。
【需要使用平台账号签名】
 */

typedef struct SetZBDevicePlanRequest 
{
	HsviewRequest base;

	struct SetZBDevicePlanRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** define a list with struct of SetZBDevicePlanRequestData_ActionsElement */
		DECLARE_LIST(struct SetZBDevicePlanRequestData_ActionsElement
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
		/** 盒子的设备ID */
		CSTR deviceId;

	} data;

} SetZBDevicePlanRequest;

C_API SetZBDevicePlanRequest *HSAPI_INIT(SetZBDevicePlanRequest);

typedef struct SetZBDevicePlanResponse 
{
	HsviewResponse base;

	struct SetZBDevicePlanResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetZBDevicePlanResponse;

C_API SetZBDevicePlanResponse *HSAPI_INIT(SetZBDevicePlanResponse);

#endif
