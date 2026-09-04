/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetDiscoveredZBDeviceList_H_
#define _HSVIEW_CLIENT_API_GetDiscoveredZBDeviceList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取订阅配件列表
【需要使用平台账号签名】
 */

typedef struct GetDiscoveredZBDeviceListRequest 
{
	HsviewRequest base;

	struct GetDiscoveredZBDeviceListRequestData
	{
		
		/** 订阅ID，为空表示获取账号下所有订阅配件信息 */
		CSTR subscribeID;
		/** 网关设备ID， 为空表示获取订阅ID下的所有配件列表 */
		CSTR deviceId;

	} data;

} GetDiscoveredZBDeviceListRequest;

C_API GetDiscoveredZBDeviceListRequest *HSAPI_INIT(GetDiscoveredZBDeviceListRequest);

typedef struct GetDiscoveredZBDeviceListResponse 
{
	HsviewResponse base;

	struct GetDiscoveredZBDeviceListResponseData
	{
		
		/** define a list with struct of GetDiscoveredZBDeviceListResponseData_SubscribeZBDevicesElement */
		DECLARE_LIST(struct GetDiscoveredZBDeviceListResponseData_SubscribeZBDevicesElement
		{
			/** 配件类型 */
			CSTR type;
			/** 订阅ID  */
			CSTR subscribeID;
			/** 配件型号 */
			CSTR model;
			/** 配件ID */
			CSTR zbDeviceId;
			/** 配件名称 */
			CSTR zbDeviceName;
			/** 网关设备ID */
			CSTR deviceId;
		}) subscribeZBDevices;
 
	} data;

} GetDiscoveredZBDeviceListResponse;

C_API GetDiscoveredZBDeviceListResponse *HSAPI_INIT(GetDiscoveredZBDeviceListResponse);

#endif
