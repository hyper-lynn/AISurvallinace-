/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_WifiCheckAddrGet_H_
#define _LC_OPENAPI_CLIENT_WifiCheckAddrGet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
远程设备升级
 */

typedef struct WifiCheckAddrGetRequest 
{
	LCOpenApiRequest base;

	struct WifiCheckAddrGetRequestData
	{
		
		/** xxx */
		CSTR token;

	} data;

} WifiCheckAddrGetRequest;

C_API WifiCheckAddrGetRequest *LCOPENAPI_INIT(WifiCheckAddrGetRequest);

typedef struct WifiCheckAddrGetResponse 
{
	LCOpenApiResponse base;

	struct WifiCheckAddrGetResponseData
	{
		
		/** 检测wifi服务的地址 */
		CSTR addr;
 
	} data;

} WifiCheckAddrGetResponse;

C_API WifiCheckAddrGetResponse *LCOPENAPI_INIT(WifiCheckAddrGetResponse);

#endif
