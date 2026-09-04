/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetZBDeviceList_H_
#define _HSVIEW_CLIENT_API_GetZBDeviceList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取账户下所有配件。
【需要使用平台账号签名】
 */

typedef struct GetZBDeviceListRequest 
{
	HsviewRequest base;

	struct GetZBDeviceListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetZBDeviceListRequest;

C_API GetZBDeviceListRequest *HSAPI_INIT(GetZBDeviceListRequest);

typedef struct GetZBDeviceListResponse 
{
	HsviewResponse base;

	struct GetZBDeviceListResponseData
	{
		
		/** define a list with struct of GetZBDeviceListResponseData_ZbDevicesElement */
		DECLARE_LIST(struct GetZBDeviceListResponseData_ZbDevicesElement
		{
			/** [bool]是否在线 */
			BOOL isOnline;
			/** 配件类型 */
			CSTR type;
			/** 配件名称 */
			CSTR name;
			/** 配件型号 */
			CSTR model;
			/** 配件开关状态on/off */
			CSTR status;
			/** 通道号 */
			CSTR channelId;
			/** 配件ID */
			CSTR zbDeviceId;
			/** 设备ID */
			CSTR deviceId;
		}) zbDevices;
 
	} data;

} GetZBDeviceListResponse;

C_API GetZBDeviceListResponse *HSAPI_INIT(GetZBDeviceListResponse);

#endif
