/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 221328, Author: 27665, Date: 2021-10-19 14:35:56 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryDeviceSmokeSensitivityConfig_H_
#define _LC_OPENAPI_CLIENT_QueryDeviceSmokeSensitivityConfig_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询设备烟感灵敏度配置
 */

typedef struct QueryDeviceSmokeSensitivityConfigRequest 
{
	LCOpenApiRequest base;

	struct QueryDeviceSmokeSensitivityConfigRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} QueryDeviceSmokeSensitivityConfigRequest;

C_API QueryDeviceSmokeSensitivityConfigRequest *LCOPENAPI_INIT(QueryDeviceSmokeSensitivityConfigRequest);

typedef struct QueryDeviceSmokeSensitivityConfigResponse 
{
	LCOpenApiResponse base;

	struct QueryDeviceSmokeSensitivityConfigResponseData
	{
		
		/** 当前灵敏度档位 */
		CSTR gear;
		/** 设备支持的灵敏度档位 */
		DECLARE_LIST(CSTR) gearRange;
 
	} data;

} QueryDeviceSmokeSensitivityConfigResponse;

C_API QueryDeviceSmokeSensitivityConfigResponse *LCOPENAPI_INIT(QueryDeviceSmokeSensitivityConfigResponse);

#endif
