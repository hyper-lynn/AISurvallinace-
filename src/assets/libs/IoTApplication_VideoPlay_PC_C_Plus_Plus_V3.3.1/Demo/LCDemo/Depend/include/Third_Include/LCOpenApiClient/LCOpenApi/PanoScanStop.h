/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_PanoScanStop_H_
#define _LC_OPENAPI_CLIENT_PanoScanStop_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
停止全景云台扫描
 */

typedef struct PanoScanStopRequest 
{
	LCOpenApiRequest base;

	struct PanoScanStopRequestData
	{
		
		/** xxx */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} PanoScanStopRequest;

C_API PanoScanStopRequest *LCOPENAPI_INIT(PanoScanStopRequest);

typedef struct PanoScanStopResponse 
{
	LCOpenApiResponse base;

	struct PanoScanStopResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} PanoScanStopResponse;

C_API PanoScanStopResponse *LCOPENAPI_INIT(PanoScanStopResponse);

#endif
