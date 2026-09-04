/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeviceRegionGetByDeviceIds_H_
#define _HSVIEW_CLIENT_API_DeviceRegionGetByDeviceIds_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
通过设备序列号获取多个设备的区域

【使用平台账号签名】

 */

typedef struct DeviceRegionGetByDeviceIdsRequest 
{
	HsviewRequest base;

	struct DeviceRegionGetByDeviceIdsRequestData
	{
		
		/** 设备序列号 */
		DECLARE_LIST(CSTR) deviceIds;

	} data;

} DeviceRegionGetByDeviceIdsRequest;

C_API DeviceRegionGetByDeviceIdsRequest *HSAPI_INIT(DeviceRegionGetByDeviceIdsRequest);

typedef struct DeviceRegionGetByDeviceIdsResponse 
{
	HsviewResponse base;

	struct DeviceRegionGetByDeviceIdsResponseData
	{
		
		/** define a list with struct of DeviceRegionGetByDeviceIdsResponseData_DevicesElement */
		DECLARE_LIST(struct DeviceRegionGetByDeviceIdsResponseData_DevicesElement
		{
			/** 区域id */
			CSTR regionId;
			/** 设备序列号 */
			CSTR deviceId;
		}) devices;
 
	} data;

} DeviceRegionGetByDeviceIdsResponse;

C_API DeviceRegionGetByDeviceIdsResponse *HSAPI_INIT(DeviceRegionGetByDeviceIdsResponse);

#endif
