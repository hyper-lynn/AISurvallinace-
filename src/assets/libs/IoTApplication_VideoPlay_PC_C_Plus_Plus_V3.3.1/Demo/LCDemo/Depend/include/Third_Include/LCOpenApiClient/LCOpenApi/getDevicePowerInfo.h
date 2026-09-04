/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 222586, Author: 27665, Date: 2022-04-22 15:26:02 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_getDevicePowerInfo_H_
#define _LC_OPENAPI_CLIENT_getDevicePowerInfo_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备锁电量信息
 */

typedef struct getDevicePowerInfoRequest 
{
	LCOpenApiRequest base;

	struct getDevicePowerInfoRequestData
	{
		
		/** xxx */
		CSTR token;
		/**  */
		CSTR deviceId;

	} data;

} getDevicePowerInfoRequest;

C_API getDevicePowerInfoRequest *LCOPENAPI_INIT(getDevicePowerInfoRequest);

typedef struct getDevicePowerInfoResponse 
{
	LCOpenApiResponse base;

	struct getDevicePowerInfoResponseData
	{
		
		/** define a list with struct of getDevicePowerInfoResponseData_ElectricitysElement */
		DECLARE_LIST(struct getDevicePowerInfoResponseData_ElectricitysElement
		{
			/** 碱性电量百分比，取值范围0~100 */
			CSTR alkElec;
			/** 电量百分比，设备锁电池有两部分，所以该字段默认返回0 */
			CSTR electric;
			/** 锂电池电量百分比，取值范围0~100 */
			CSTR litElec;
			/** 供电类型，battery：电池；adapter：适配器；batteryAdapter：电池+适配器 */
			CSTR type;
		}) electricitys;
 
	} data;

} getDevicePowerInfoResponse;

C_API getDevicePowerInfoResponse *LCOPENAPI_INIT(getDevicePowerInfoResponse);

#endif
