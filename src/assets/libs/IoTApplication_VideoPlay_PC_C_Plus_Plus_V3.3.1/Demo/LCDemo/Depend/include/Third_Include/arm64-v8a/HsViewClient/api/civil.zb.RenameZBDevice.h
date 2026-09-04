/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_RenameZBDevice_H_
#define _HSVIEW_CLIENT_API_RenameZBDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
重命名配件。由【设备序列号+[通道号or配件id]】唯一确定一个配件。
【需要使用平台账号签名】
 */

typedef struct RenameZBDeviceRequest 
{
	HsviewRequest base;

	struct RenameZBDeviceRequestData
	{
		
		/** 配件ID */
		CSTR zbDeviceId;
		/** 通道号 */
		CSTR channelId;
		/** 需要设置的配件名称 */
		CSTR zbDeviceName;
		/** 盒子的设备ID */
		CSTR deviceId;

	} data;

} RenameZBDeviceRequest;

C_API RenameZBDeviceRequest *HSAPI_INIT(RenameZBDeviceRequest);

typedef struct RenameZBDeviceResponse 
{
	HsviewResponse base;

	struct RenameZBDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} RenameZBDeviceResponse;

C_API RenameZBDeviceResponse *HSAPI_INIT(RenameZBDeviceResponse);

#endif
