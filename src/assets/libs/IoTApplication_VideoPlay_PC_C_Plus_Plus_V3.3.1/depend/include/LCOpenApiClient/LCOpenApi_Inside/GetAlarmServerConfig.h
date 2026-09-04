/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetAlarmServerConfig_H_
#define _LC_OPENAPI_CLIENT_GetAlarmServerConfig_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取报警消息鉴权和推送服务器的地址和端口

 */

typedef struct GetAlarmServerConfigRequest 
{
	LCOpenApiRequest base;

	struct GetAlarmServerConfigRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;

	} data;

} GetAlarmServerConfigRequest;

C_API GetAlarmServerConfigRequest *LCOPENAPI_INIT(GetAlarmServerConfigRequest);

typedef struct GetAlarmServerConfigResponse 
{
	LCOpenApiResponse base;

	struct GetAlarmServerConfigResponseData
	{
		
		/** define a list with struct of GetAlarmServerConfigResponseData_ServersElement */
		DECLARE_LIST(struct GetAlarmServerConfigResponseData_ServersElement
		{
			/** 域名 */
			CSTR host;
			/** 端口 */
			CSTR port;
			/** 服务类型：auth, push */
			CSTR type;
		}) servers;
 
	} data;

} GetAlarmServerConfigResponse;

C_API GetAlarmServerConfigResponse *LCOPENAPI_INIT(GetAlarmServerConfigResponse);

#endif
