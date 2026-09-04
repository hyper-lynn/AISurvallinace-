/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_PanoScanStart_H_
#define _LC_OPENAPI_CLIENT_PanoScanStart_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
开始全景云台扫描
 */

typedef struct PanoScanStartRequest 
{
	LCOpenApiRequest base;

	struct PanoScanStartRequestData
	{
		
		/** 密钥 */
		CSTR secretKey;
		/** xxx */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} PanoScanStartRequest;

C_API PanoScanStartRequest *LCOPENAPI_INIT(PanoScanStartRequest);

typedef struct PanoScanStartResponse 
{
	LCOpenApiResponse base;

	struct PanoScanStartResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} PanoScanStartResponse;

C_API PanoScanStartResponse *LCOPENAPI_INIT(PanoScanStartResponse);

#endif
