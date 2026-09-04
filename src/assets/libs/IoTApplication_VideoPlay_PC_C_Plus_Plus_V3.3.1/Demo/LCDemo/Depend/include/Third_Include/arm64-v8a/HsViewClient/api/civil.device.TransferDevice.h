/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferDevice_H_
#define _HSVIEW_CLIENT_API_TransferDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 设备转移

 deviceId不能为空，最多支持5个设备的同时转移
【需要使用平台账号签名】
 */

typedef struct TransferDeviceRequest 
{
	HsviewRequest base;

	struct TransferDeviceRequestData
	{
		
		/** 验证码发送到的账号，可能为邮箱或者手机号 */
		CSTR sendCodeAccount;
		/** [bool]是否一起删除该设备的云存储录像 */
		BOOL deleteCloudRecords;
		/** 转移对象手机号,如13912345678 */
		CSTR phoneNumber;
		/** 验证码 */
		CSTR validCode;
		/** 转移设备ID */
		DECLARE_LIST(CSTR) deviceId;

	} data;

} TransferDeviceRequest;

C_API TransferDeviceRequest *HSAPI_INIT(TransferDeviceRequest);

typedef struct TransferDeviceResponse 
{
	HsviewResponse base;

	struct TransferDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TransferDeviceResponse;

C_API TransferDeviceResponse *HSAPI_INIT(TransferDeviceResponse);

#endif
