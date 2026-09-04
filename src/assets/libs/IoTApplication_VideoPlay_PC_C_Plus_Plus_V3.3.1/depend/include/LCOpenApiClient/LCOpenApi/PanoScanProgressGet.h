/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_PanoScanProgressGet_H_
#define _LC_OPENAPI_CLIENT_PanoScanProgressGet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取全景扫描的进度
 */

typedef struct PanoScanProgressGetRequest 
{
	LCOpenApiRequest base;

	struct PanoScanProgressGetRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} PanoScanProgressGetRequest;

C_API PanoScanProgressGetRequest *LCOPENAPI_INIT(PanoScanProgressGetRequest);

typedef struct PanoScanProgressGetResponse 
{
	LCOpenApiResponse base;

	struct PanoScanProgressGetResponseData
	{
		
		/** 进度百分比 */
		CSTR percent;
 
	} data;

} PanoScanProgressGetResponse;

C_API PanoScanProgressGetResponse *LCOPENAPI_INIT(PanoScanProgressGetResponse);

#endif
