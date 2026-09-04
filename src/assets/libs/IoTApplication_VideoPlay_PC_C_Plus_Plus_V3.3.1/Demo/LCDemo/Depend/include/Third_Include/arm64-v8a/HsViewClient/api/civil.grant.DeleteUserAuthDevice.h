/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteUserAuthDevice_H_
#define _HSVIEW_CLIENT_API_DeleteUserAuthDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   删除授权设备
【需要使用平台账号签名】

 */

typedef struct DeleteUserAuthDeviceRequest 
{
	HsviewRequest base;

	struct DeleteUserAuthDeviceRequestData
	{
		
		/** [long]授权Id */
		int64 authId;
		/** define a list with struct of DeleteUserAuthDeviceRequestData_AuthDevicesElement */
		DECLARE_LIST(struct DeleteUserAuthDeviceRequestData_AuthDevicesElement
		{
			/** 设备序列号 */
			CSTR deviceCode;
			/** 通道号 */
			CSTR channelId;
		}) authDevices;

	} data;

} DeleteUserAuthDeviceRequest;

C_API DeleteUserAuthDeviceRequest *HSAPI_INIT(DeleteUserAuthDeviceRequest);

typedef struct DeleteUserAuthDeviceResponse 
{
	HsviewResponse base;

	struct DeleteUserAuthDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteUserAuthDeviceResponse;

C_API DeleteUserAuthDeviceResponse *HSAPI_INIT(DeleteUserAuthDeviceResponse);

#endif
