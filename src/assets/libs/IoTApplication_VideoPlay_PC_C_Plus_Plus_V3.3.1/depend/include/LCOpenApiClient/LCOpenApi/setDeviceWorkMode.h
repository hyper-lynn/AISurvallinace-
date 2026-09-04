/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 223115, Author: 27665, Date: 2022-08-09 14:45:28 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_setDeviceWorkMode_H_
#define _LC_OPENAPI_CLIENT_setDeviceWorkMode_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置设备工作模式
 */

typedef struct setDeviceWorkModeRequest 
{
	LCOpenApiRequest base;

	struct setDeviceWorkModeRequestData
	{
		
		/** 告警触发间隔，单位s */
		CSTR intervalTime;
		/**  */
		CSTR token;
		/** 逗留时长，单位s */
		CSTR stayTime;
		/** 模式 */
		CSTR mode;
		/** 可选，不填即为设备级 */
		CSTR channelId;
		/** 每条录像片段时长，单位s */
		CSTR recordTime;
		/**  */
		CSTR deviceId;

	} data;

} setDeviceWorkModeRequest;

C_API setDeviceWorkModeRequest *LCOPENAPI_INIT(setDeviceWorkModeRequest);

typedef struct setDeviceWorkModeResponse 
{
	LCOpenApiResponse base;

	struct setDeviceWorkModeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} setDeviceWorkModeResponse;

C_API setDeviceWorkModeResponse *LCOPENAPI_INIT(setDeviceWorkModeResponse);

#endif
