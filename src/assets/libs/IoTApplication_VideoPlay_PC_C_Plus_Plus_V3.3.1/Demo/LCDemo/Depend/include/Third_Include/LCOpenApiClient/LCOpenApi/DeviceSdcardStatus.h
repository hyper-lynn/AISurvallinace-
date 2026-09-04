/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 222696, Author: 21818, Date: 2022-05-20 10:27:42 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceSdcardStatus_H_
#define _LC_OPENAPI_CLIENT_DeviceSdcardStatus_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备存储介质容量信息
 */

typedef struct DeviceSdcardStatusRequest 
{
	LCOpenApiRequest base;

	struct DeviceSdcardStatusRequestData
	{
		
		/** 需要格式化存储介质编号（不填该参数默认设备是单sd卡） */
		CSTR index;
		/** [cstr]deviceSdcardStatus */
		#define _STATIC_DeviceSdcardStatusRequestData_method "deviceSdcardStatus"
		CSTR method;
		/** 授权Token */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} DeviceSdcardStatusRequest;

C_API DeviceSdcardStatusRequest *LCOPENAPI_INIT(DeviceSdcardStatusRequest);

typedef struct DeviceSdcardStatusResponse 
{
	LCOpenApiResponse base;

	struct DeviceSdcardStatusResponseData
	{
		
		/** [String] empty-无SD卡，normal-正常，abnormal-异常，recovering-格式化中 */
		CSTR status;
 
	} data;

} DeviceSdcardStatusResponse;

C_API DeviceSdcardStatusResponse *LCOPENAPI_INIT(DeviceSdcardStatusResponse);

#endif
