/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetWeatherArea_H_
#define _HSVIEW_CLIENT_API_SetWeatherArea_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备区域（TC5S需求）

Province: 必须，设备所在省，初次未设置时，为空

City: 必须，设备所在市，初次未设置时，为空

Area: 必须，未到区级则允许为空
 */

typedef struct SetWeatherAreaRequest 
{
	HsviewRequest base;

	struct SetWeatherAreaRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetWeatherAreaRequestData_METHOD "POST"
		/** [cstr]region */
		#define _STATIC_SetWeatherAreaRequestData_CMD "region"
		/** struct of SetWeatherAreaRequestData_Body */
		struct SetWeatherAreaRequestData_Body {
			/** 必须，未到区级则允许为空 */
			CSTR Area;
			/** 必须，设备所在市，初次未设置时，为空 */
			CSTR City;
			/** 必须，设备所在省，初次未设置时，为空 */
			CSTR Province;
		} body;

	} data;

} SetWeatherAreaRequest;

C_API SetWeatherAreaRequest *HSAPI_INIT(SetWeatherAreaRequest);

typedef struct SetWeatherAreaResponse 
{
	HsviewResponse base;

	struct SetWeatherAreaResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetWeatherAreaResponse;

C_API SetWeatherAreaResponse *HSAPI_INIT(SetWeatherAreaResponse);

#endif
