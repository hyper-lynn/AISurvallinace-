/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UnbindLive_H_
#define _LC_OPENAPI_CLIENT_UnbindLive_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
删除直播地址
 */

typedef struct UnbindLiveRequest 
{
	LCOpenApiRequest base;

	struct UnbindLiveRequestData
	{
		
		/** 授权的管理员token(accessToken) */
		CSTR token;
		/**  */
		CSTR liveToken;

	} data;

} UnbindLiveRequest;

C_API UnbindLiveRequest *LCOPENAPI_INIT(UnbindLiveRequest);

typedef struct UnbindLiveResponse 
{
	LCOpenApiResponse base;

	struct UnbindLiveResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UnbindLiveResponse;

C_API UnbindLiveResponse *LCOPENAPI_INIT(UnbindLiveResponse);

#endif
