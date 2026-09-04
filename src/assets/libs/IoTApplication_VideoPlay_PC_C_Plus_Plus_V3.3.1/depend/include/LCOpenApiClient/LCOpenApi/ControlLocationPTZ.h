/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ControlLocationPTZ_H_
#define _LC_OPENAPI_CLIENT_ControlLocationPTZ_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
第二版云台定位接口

 */

typedef struct ControlLocationPTZRequest 
{
	LCOpenApiRequest base;

	struct ControlLocationPTZRequestData
	{
		
		/** [double]水平操作参数 */
		double h;
		/** [cstr]controlLocationPTZ */
		#define _STATIC_ControlLocationPTZRequestData_method "controlLocationPTZ"
		CSTR method;
		/** [double]变倍参数 */
		double z;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 通道号 */
		CSTR channelId;
		/** [double]垂直操作参数 */
		double v;
		/** 设备ID */
		CSTR deviceId;

	} data;

} ControlLocationPTZRequest;

C_API ControlLocationPTZRequest *LCOPENAPI_INIT(ControlLocationPTZRequest);

typedef struct ControlLocationPTZResponse 
{
	LCOpenApiResponse base;

	struct ControlLocationPTZResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ControlLocationPTZResponse;

C_API ControlLocationPTZResponse *LCOPENAPI_INIT(ControlLocationPTZResponse);

#endif
