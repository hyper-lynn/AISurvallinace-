/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 222587, Author: 27665, Date: 2022-04-22 15:26:14 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_wakeUpDevice_H_
#define _LC_OPENAPI_CLIENT_wakeUpDevice_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
唤醒休眠的门锁设备
 */

typedef struct wakeUpDeviceRequest 
{
	LCOpenApiRequest base;

	struct wakeUpDeviceRequestData
	{
		
		/** xxx */
		CSTR token;
		/**  */
		CSTR deviceId;

	} data;

} wakeUpDeviceRequest;

C_API wakeUpDeviceRequest *LCOPENAPI_INIT(wakeUpDeviceRequest);

typedef struct wakeUpDeviceResponse 
{
	LCOpenApiResponse base;

	struct wakeUpDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} wakeUpDeviceResponse;

C_API wakeUpDeviceResponse *LCOPENAPI_INIT(wakeUpDeviceResponse);

#endif
