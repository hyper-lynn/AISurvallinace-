/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_UserDeviceCancel_H_
#define _HSVIEW_CLIENT_API_deviceManager_UserDeviceCancel_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备注销。注意必须是该用户名下的设备

【需要使用平台账号签名】
 */

typedef struct deviceManager_UserDeviceCancelRequest 
{
	HsviewRequest base;

	struct deviceManager_UserDeviceCancelRequestData
	{
		
		/** [O]验证码，如123456；该字段APP必须带，服务做校验；开放平台不用带，服务需识别开放平台 */
		CSTR validCode;
		/** 类型, phone、email */
		CSTR type;
		/** 是否一起删除该设备的报警消息,delete:删除,retain:保留 */
		CSTR deleteCloudAlarms;
		/** 是否一起删除该设备的云录像,delete:删除,retain:保留 */
		CSTR deleteCloudRecords;
		/** 设备ID */
		CSTR deviceId;
		/** 帐号, 手机号码、邮箱 */
		CSTR account;

	} data;

} deviceManager_UserDeviceCancelRequest;

C_API deviceManager_UserDeviceCancelRequest *HSAPI_INIT(deviceManager_UserDeviceCancelRequest);

typedef struct deviceManager_UserDeviceCancelResponse 
{
	HsviewResponse base;

	struct deviceManager_UserDeviceCancelResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceManager_UserDeviceCancelResponse;

C_API deviceManager_UserDeviceCancelResponse *HSAPI_INIT(deviceManager_UserDeviceCancelResponse);

#endif
