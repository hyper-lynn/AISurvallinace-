/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_IotDeviceNoiseReduction_H_
#define _HSVIEW_CLIENT_API_transferDevice_IotDeviceNoiseReduction_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
Iot设备消音
错误码待定

参考PaaS协议：[Iot设备消音](http://paas.dahuatech.com/wiki/?p=%2FSaaStoPaaS%2F%E8%B7%AF%E7%94%B1%E5%8D%8F%E8%AE%AE%E7%AE%A1%E7%90%86%2Fcloud.device.IotDeviceNoiseReduction.md&s=pj)

【需要使用平台账号签名】
 */

typedef struct transferDevice_IotDeviceNoiseReductionRequest 
{
	HsviewRequest base;

	struct transferDevice_IotDeviceNoiseReductionRequestData
	{
		
		/** [cstr] /iot/device/noise/reduction */
		#define _STATIC_transferDevice_IotDeviceNoiseReductionRequestData_url " /iot/device/noise/reduction"
		CSTR url;
		/** struct of transferDevice_IotDeviceNoiseReductionRequestData_Content */
		struct transferDevice_IotDeviceNoiseReductionRequestData_Content {
			/** 设备类型 */
			CSTR deviceModel;
			/** 设备Imei码 */
			CSTR imeiCode;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_IotDeviceNoiseReductionRequest;

C_API transferDevice_IotDeviceNoiseReductionRequest *HSAPI_INIT(transferDevice_IotDeviceNoiseReductionRequest);

typedef struct transferDevice_IotDeviceNoiseReductionResponse 
{
	HsviewResponse base;

	struct transferDevice_IotDeviceNoiseReductionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_IotDeviceNoiseReductionResponse;

C_API transferDevice_IotDeviceNoiseReductionResponse *HSAPI_INIT(transferDevice_IotDeviceNoiseReductionResponse);

#endif
