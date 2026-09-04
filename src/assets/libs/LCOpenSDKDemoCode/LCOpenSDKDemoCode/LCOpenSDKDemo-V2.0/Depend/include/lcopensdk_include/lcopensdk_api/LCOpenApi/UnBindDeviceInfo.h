/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UnBindDeviceInfo_H_
#define _LC_OPENAPI_CLIENT_UnBindDeviceInfo_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取未绑定的设备信息
 */

typedef struct UnBindDeviceInfoRequest 
{
	LCOpenApiRequest base;

	struct UnBindDeviceInfoRequestData
	{
		
		/** [cstr]unBindDeviceInfo */
		#define _STATIC_UnBindDeviceInfoRequestData_method "unBindDeviceInfo"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} UnBindDeviceInfoRequest;

C_API UnBindDeviceInfoRequest *LCOPENAPI_INIT(UnBindDeviceInfoRequest);

typedef struct UnBindDeviceInfoResponse 
{
	LCOpenApiResponse base;

	struct UnBindDeviceInfoResponseData
	{
		
		/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见乐橙开放平台设备协议 */
		CSTR ability;
 
	} data;

} UnBindDeviceInfoResponse;

C_API UnBindDeviceInfoResponse *LCOPENAPI_INIT(UnBindDeviceInfoResponse);

#endif
