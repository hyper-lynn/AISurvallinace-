/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 220465, Author: 27665, Date: 2021-07-22 14:42:47 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetZoomFocus_H_
#define _LC_OPENAPI_CLIENT_SetZoomFocus_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置设备变焦倍数（需要设备拥有ZoomFocus能力集）

 */

typedef struct SetZoomFocusRequest 
{
	LCOpenApiRequest base;

	struct SetZoomFocusRequestData
	{
		
		/** large、small、cover */
		CSTR type;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 通道ID */
		CSTR channelId;
		/** 变倍倍数或缩放增量 */
		CSTR zoomFocus;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetZoomFocusRequest;

C_API SetZoomFocusRequest *LCOPENAPI_INIT(SetZoomFocusRequest);

typedef struct SetZoomFocusResponse 
{
	LCOpenApiResponse base;

	struct SetZoomFocusResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetZoomFocusResponse;

C_API SetZoomFocusResponse *LCOPENAPI_INIT(SetZoomFocusResponse);

#endif
