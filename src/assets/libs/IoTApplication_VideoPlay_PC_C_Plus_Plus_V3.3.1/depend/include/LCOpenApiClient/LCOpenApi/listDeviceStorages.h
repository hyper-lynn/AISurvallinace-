/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 222591, Author: 27665, Date: 2022-04-22 15:26:46 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_listDeviceStorages_H_
#define _LC_OPENAPI_CLIENT_listDeviceStorages_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询设备存储介质列表
 */

typedef struct listDeviceStoragesRequest 
{
	LCOpenApiRequest base;

	struct listDeviceStoragesRequestData
	{
		
		/** 授权的token */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} listDeviceStoragesRequest;

C_API listDeviceStoragesRequest *LCOPENAPI_INIT(listDeviceStoragesRequest);

typedef struct listDeviceStoragesResponse 
{
	LCOpenApiResponse base;

	struct listDeviceStoragesResponseData
	{
		
		/** define a list with struct of listDeviceStoragesResponseData_StorageListElement */
		DECLARE_LIST(struct listDeviceStoragesResponseData_StorageListElement
		{
			/** 从1开始表示存储介质的编号 */
			CSTR index;
			/** 可选,存储介质名称 */
			CSTR name;
		}) storageList;
 
	} data;

} listDeviceStoragesResponse;

C_API listDeviceStoragesResponse *LCOPENAPI_INIT(listDeviceStoragesResponse);

#endif
