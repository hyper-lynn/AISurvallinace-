/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 223153, Author: 27665, Date: 2022-08-11 16:03:58 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_setDeviceSleepParam_H_
#define _LC_OPENAPI_CLIENT_setDeviceSleepParam_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备休眠设置
 */

typedef struct setDeviceSleepParamRequest 
{
	LCOpenApiRequest base;

	struct setDeviceSleepParamRequestData
	{
		
		/**  */
		CSTR token;
		/** [bool]休眠使能是否开启 */
		BOOL enable;
		/** 可选，不存在默认查询的是设备 */
		CSTR channelId;
		/** 休眠阈值0-100 */
		CSTR electricity;
		/** 设备ID */
		CSTR deviceId;

	} data;

} setDeviceSleepParamRequest;

C_API setDeviceSleepParamRequest *LCOPENAPI_INIT(setDeviceSleepParamRequest);

typedef struct setDeviceSleepParamResponse 
{
	LCOpenApiResponse base;

	struct setDeviceSleepParamResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} setDeviceSleepParamResponse;

C_API setDeviceSleepParamResponse *LCOPENAPI_INIT(setDeviceSleepParamResponse);

#endif
