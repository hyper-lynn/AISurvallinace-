/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetWeatherArea_H_
#define _HSVIEW_CLIENT_API_GetWeatherArea_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备区域

Province: 必须，设备所在省，初次未设置时，为空

City: 必须，设备所在市，初次未设置时，为空

Area: 必须，未到区级则允许为空
 */

typedef struct GetWeatherAreaRequest 
{
	HsviewRequest base;

	struct GetWeatherAreaRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_GetWeatherAreaRequestData_METHOD "GET"
		/** [cstr]region */
		#define _STATIC_GetWeatherAreaRequestData_CMD "region"
		/** struct of GetWeatherAreaRequestData_Body */
		struct GetWeatherAreaRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetWeatherAreaRequest;

C_API GetWeatherAreaRequest *HSAPI_INIT(GetWeatherAreaRequest);

typedef struct GetWeatherAreaResponse 
{
	HsviewResponse base;

	struct GetWeatherAreaResponseData
	{
		
		/** 必须，未到区级则允许为空 */
		CSTR Area;
		/** 必须，设备所在市，初次未设置时，为空 */
		CSTR City;
		/** 必须，设备所在省，初次未设置时，为空 */
		CSTR Province;
 
	} data;

} GetWeatherAreaResponse;

C_API GetWeatherAreaResponse *HSAPI_INIT(GetWeatherAreaResponse);

#endif
