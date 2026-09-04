/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UnbindDevice_H_
#define _HSVIEW_CLIENT_API_UnbindDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

deviceId是需要解绑的设备ID。注意必须是该用户名下的设备。
	
【需要使用平台账号签名】

 */

typedef struct UnbindDeviceRequest 
{
	HsviewRequest base;

	struct UnbindDeviceRequestData
	{
		
		/** [bool]是否一起删除该设备的云存储录像 */
		BOOL deleteCloudRecords;
		/** 设备ID */
		CSTR deviceId;

	} data;

} UnbindDeviceRequest;

C_API UnbindDeviceRequest *HSAPI_INIT(UnbindDeviceRequest);

typedef struct UnbindDeviceResponse 
{
	HsviewResponse base;

	struct UnbindDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UnbindDeviceResponse;

C_API UnbindDeviceResponse *HSAPI_INIT(UnbindDeviceResponse);

#endif
