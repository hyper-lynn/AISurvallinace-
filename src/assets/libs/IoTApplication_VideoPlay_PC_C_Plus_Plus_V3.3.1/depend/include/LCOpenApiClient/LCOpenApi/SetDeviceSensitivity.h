/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 223439, Author: 304780, Date: 2022-10-12 16:27:55 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetDeviceSensitivity_H_
#define _LC_OPENAPI_CLIENT_SetDeviceSensitivity_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置火情灵敏度
 */

typedef struct SetDeviceSensitivityRequest 
{
	LCOpenApiRequest base;

	struct SetDeviceSensitivityRequestData
	{
		
		/** 灵敏度类型,type = fwSens火灾预警灵敏度 */
		CSTR type;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 灵敏度 */
		CSTR sensitivity;
		/** 可选，档位 */
		CSTR gear;
		/** 通道,不存在默认为设备 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} SetDeviceSensitivityRequest;

C_API SetDeviceSensitivityRequest *LCOPENAPI_INIT(SetDeviceSensitivityRequest);

typedef struct SetDeviceSensitivityResponse 
{
	LCOpenApiResponse base;

	struct SetDeviceSensitivityResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetDeviceSensitivityResponse;

C_API SetDeviceSensitivityResponse *LCOPENAPI_INIT(SetDeviceSensitivityResponse);

#endif
