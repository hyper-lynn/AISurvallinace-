/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteZBDevice_H_
#define _HSVIEW_CLIENT_API_DeleteZBDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除配件。
【需要使用平台账号签名】
 */

typedef struct DeleteZBDeviceRequest 
{
	HsviewRequest base;

	struct DeleteZBDeviceRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 配件ID */
		CSTR zbDeviceId;
		/** 盒子的设备ID */
		CSTR deviceId;

	} data;

} DeleteZBDeviceRequest;

C_API DeleteZBDeviceRequest *HSAPI_INIT(DeleteZBDeviceRequest);

typedef struct DeleteZBDeviceResponse 
{
	HsviewResponse base;

	struct DeleteZBDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteZBDeviceResponse;

C_API DeleteZBDeviceResponse *HSAPI_INIT(DeleteZBDeviceResponse);

#endif
