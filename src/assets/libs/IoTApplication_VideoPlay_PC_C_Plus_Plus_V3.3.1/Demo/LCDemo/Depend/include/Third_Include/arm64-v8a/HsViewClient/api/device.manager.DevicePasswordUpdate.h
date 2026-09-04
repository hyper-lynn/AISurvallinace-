/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_DevicePasswordUpdate_H_
#define _HSVIEW_CLIENT_API_deviceManager_DevicePasswordUpdate_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备用户密码信息上报（平台校验绑定关系，非PaaS设备、不带AUTH能力集的设备才允许调用该接口）

【需要使用平台账号签名】
 */

typedef struct deviceManager_DevicePasswordUpdateRequest 
{
	HsviewRequest base;

	struct deviceManager_DevicePasswordUpdateRequestData
	{
		
		/** 设备密码（Base64(AES256加密)） */
		CSTR devicePassword;
		/** 设备用户名（Base64(AES256加密)） */
		CSTR deviceUsername;
		/** 设备ID */
		CSTR deviceId;

	} data;

} deviceManager_DevicePasswordUpdateRequest;

C_API deviceManager_DevicePasswordUpdateRequest *HSAPI_INIT(deviceManager_DevicePasswordUpdateRequest);

typedef struct deviceManager_DevicePasswordUpdateResponse 
{
	HsviewResponse base;

	struct deviceManager_DevicePasswordUpdateResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceManager_DevicePasswordUpdateResponse;

C_API deviceManager_DevicePasswordUpdateResponse *HSAPI_INIT(deviceManager_DevicePasswordUpdateResponse);

#endif
