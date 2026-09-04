/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 220465, Author: 27665, Date: 2021-07-22 14:42:47 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetZoomFocus_H_
#define _LC_OPENAPI_CLIENT_GetZoomFocus_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备变焦倍数（需要设备拥有ZoomFocus能力集）

 */

typedef struct GetZoomFocusRequest 
{
	LCOpenApiRequest base;

	struct GetZoomFocusRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetZoomFocusRequest;

C_API GetZoomFocusRequest *LCOPENAPI_INIT(GetZoomFocusRequest);

typedef struct GetZoomFocusResponse 
{
	LCOpenApiResponse base;

	struct GetZoomFocusResponseData
	{
		
		/** define a list with struct of GetZoomFocusResponseData_ChannelsElement */
		DECLARE_LIST(struct GetZoomFocusResponseData_ChannelsElement
		{
			/** 0.5变倍系数 */
			CSTR zoomFocus;
			/** 通道号 */
			CSTR channelId;
		}) channels;
 
	} data;

} GetZoomFocusResponse;

C_API GetZoomFocusResponse *LCOPENAPI_INIT(GetZoomFocusResponse);

#endif
