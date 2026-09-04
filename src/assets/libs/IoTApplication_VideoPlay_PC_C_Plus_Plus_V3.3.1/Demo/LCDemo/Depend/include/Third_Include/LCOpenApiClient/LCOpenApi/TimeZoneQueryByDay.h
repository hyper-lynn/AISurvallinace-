/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227286, Author: 251672, Date: 2024-09-02 17:23:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_TimeZoneQueryByDay_H_
#define _LC_OPENAPI_CLIENT_TimeZoneQueryByDay_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询设备夏令时配置
 */

typedef struct TimeZoneQueryByDayRequest 
{
	LCOpenApiRequest base;

	struct TimeZoneQueryByDayRequestData
	{
		
		/** 设备来源，lc：乐橙设备，paas：大华设备 */
		CSTR sourceType;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TimeZoneQueryByDayRequest;

C_API TimeZoneQueryByDayRequest *LCOPENAPI_INIT(TimeZoneQueryByDayRequest);

typedef struct TimeZoneQueryByDayResponse 
{
	LCOpenApiResponse base;

	struct TimeZoneQueryByDayResponseData
	{
		
		/** 3-1-1 18:59:20 */
		CSTR endWeekSunTime;
		/** 02-01 18:59:20 */
		CSTR beginSunTime;
		/** 8,The time zone of the device is optional. If not, the current configuration of the device shall prevail */
		CSTR timeZone;
		/** day/week */
		CSTR mode;
		/** 3-1-1 18:59:20 */
		CSTR beginWeekSunTime;
		/** 10-01 18:59:20 */
		CSTR endSunTime;
		/** 1,Set time zone corresponding to the index value */
		CSTR areaIndex;
 
	} data;

} TimeZoneQueryByDayResponse;

C_API TimeZoneQueryByDayResponse *LCOPENAPI_INIT(TimeZoneQueryByDayResponse);

#endif
