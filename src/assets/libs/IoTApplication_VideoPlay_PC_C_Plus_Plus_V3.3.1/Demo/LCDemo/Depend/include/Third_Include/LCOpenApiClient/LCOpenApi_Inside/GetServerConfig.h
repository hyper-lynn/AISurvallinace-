/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetServerConfig_H_
#define _LC_OPENAPI_CLIENT_GetServerConfig_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
鉴权token是否在白名单中
 */

typedef struct GetServerConfigRequest 
{
	LCOpenApiRequest base;

	struct GetServerConfigRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;

	} data;

} GetServerConfigRequest;

C_API GetServerConfigRequest *LCOPENAPI_INIT(GetServerConfigRequest);

typedef struct GetServerConfigResponse 
{
	LCOpenApiResponse base;

	struct GetServerConfigResponseData
	{
		
		/** define a list with struct of GetServerConfigResponseData_ServersElement */
		DECLARE_LIST(struct GetServerConfigResponseData_ServersElement
		{
			/** 域名 */
			CSTR host;
			/** 端口 */
			CSTR port;
			/** 服务类型：p2p,pss,pns */
			CSTR type;
		}) servers;
		/** p2p服务鉴权ID */
		CSTR p2pAuthId;
		/** [bool]true标示要走p2pRelay,false 不走p2pRelay */
		BOOL p2pRelay;
 
	} data;

} GetServerConfigResponse;

C_API GetServerConfigResponse *LCOPENAPI_INIT(GetServerConfigResponse);

#endif
