/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_UserDeviceTransfer_H_
#define _HSVIEW_CLIENT_API_deviceManager_UserDeviceTransfer_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备转移
deviceId不能为空，最多支持5个设备的同时转移
【需要使用平台账号签名】
 */

typedef struct deviceManager_UserDeviceTransferRequest 
{
	HsviewRequest base;

	struct deviceManager_UserDeviceTransferRequestData
	{
		
		/** 验证码发送到的账号，可能为邮箱或者手机号 */
		CSTR sendCodeAccount;
		/** [O]接收者账号，该字段为老协议独有，后面不再支持，使用acceptUserId */
		CSTR acceptAccount;
		/** 是否一起删除该设备的报警消息,delete:删除,retain:保留 */
		CSTR deleteCloudAlarms;
		/** 验证码 */
		CSTR validCode;
		/** 接收者用户id */
		CSTR acceptUserId;
		/** 是否一起删除该设备的云录像,delete:删除,retain:保留 */
		CSTR deleteCloudRecords;
		/** 转移设备序列号 */
		DECLARE_LIST(CSTR) deviceIds;

	} data;

} deviceManager_UserDeviceTransferRequest;

C_API deviceManager_UserDeviceTransferRequest *HSAPI_INIT(deviceManager_UserDeviceTransferRequest);

typedef struct deviceManager_UserDeviceTransferResponse 
{
	HsviewResponse base;

	struct deviceManager_UserDeviceTransferResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceManager_UserDeviceTransferResponse;

C_API deviceManager_UserDeviceTransferResponse *HSAPI_INIT(deviceManager_UserDeviceTransferResponse);

#endif
