/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_DeviceNameModify_H_
#define _HSVIEW_CLIENT_API_deviceManager_DeviceNameModify_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备或者通道重命名，channelId为空则为设备重命名，不为空为通道重命名
【需要使用平台账号签名】
 */

typedef struct deviceManager_DeviceNameModifyRequest 
{
	HsviewRequest base;

	struct deviceManager_DeviceNameModifyRequestData
	{
		
		/** [O]是否下发到设备，为空和'false'表示不下发，'true'表示下发设备，注：只有PAAS设备可以成功下发到设备,海外不受此参数控制，PAAS设备都会下发设备 */
		CSTR setToDevice;
		/** [O]通道号，为空表示设置设备 */
		CSTR channelId;
		/** 名称 */
		CSTR name;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} deviceManager_DeviceNameModifyRequest;

C_API deviceManager_DeviceNameModifyRequest *HSAPI_INIT(deviceManager_DeviceNameModifyRequest);

typedef struct deviceManager_DeviceNameModifyResponse 
{
	HsviewResponse base;

	struct deviceManager_DeviceNameModifyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceManager_DeviceNameModifyResponse;

C_API deviceManager_DeviceNameModifyResponse *HSAPI_INIT(deviceManager_DeviceNameModifyResponse);

#endif
