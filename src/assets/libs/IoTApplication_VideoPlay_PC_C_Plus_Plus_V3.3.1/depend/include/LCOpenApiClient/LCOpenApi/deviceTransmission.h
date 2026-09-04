/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 224271, Author: 233705, Date: 2023-03-13 09:34:47 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_deviceTransmission_H_
#define _LC_OPENAPI_CLIENT_deviceTransmission_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备透传协议

 */

typedef struct deviceTransmissionRequest 
{
	LCOpenApiRequest base;

	struct deviceTransmissionRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/**  */
		CSTR type;
		/** 三代协议base64 */
		CSTR content;
		/** 设备ID */
		CSTR deviceId;

	} data;

} deviceTransmissionRequest;

C_API deviceTransmissionRequest *LCOPENAPI_INIT(deviceTransmissionRequest);

typedef struct deviceTransmissionResponse 
{
	LCOpenApiResponse base;

	struct deviceTransmissionResponseData
	{
		
		/**  */
		CSTR content;
 
	} data;

} deviceTransmissionResponse;

C_API deviceTransmissionResponse *LCOPENAPI_INIT(deviceTransmissionResponse);

#endif
