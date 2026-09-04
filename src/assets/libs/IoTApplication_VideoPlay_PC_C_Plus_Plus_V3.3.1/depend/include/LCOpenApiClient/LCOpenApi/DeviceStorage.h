/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 222590, Author: 27665, Date: 2022-04-22 15:26:39 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceStorage_H_
#define _LC_OPENAPI_CLIENT_DeviceStorage_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备存储介质容量信息
 */

typedef struct DeviceStorageRequest 
{
	LCOpenApiRequest base;

	struct DeviceStorageRequestData
	{
		
		/** 可选，需要格式化的存储介质编号 */
		CSTR index;
		/** 授权Token */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} DeviceStorageRequest;

C_API DeviceStorageRequest *LCOPENAPI_INIT(DeviceStorageRequest);

typedef struct DeviceStorageResponse 
{
	LCOpenApiResponse base;

	struct DeviceStorageResponseData
	{
		
		/** [long]总容量，单位为Byte */
		int64 totalBytes;
		/** [long]已使用容量，单位为Byte */
		int64 usedBytes;
 
	} data;

} DeviceStorageResponse;

C_API DeviceStorageResponse *LCOPENAPI_INIT(DeviceStorageResponse);

#endif
