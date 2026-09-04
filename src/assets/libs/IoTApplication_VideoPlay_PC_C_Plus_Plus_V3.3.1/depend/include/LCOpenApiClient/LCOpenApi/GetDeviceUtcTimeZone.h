/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227286, Author: 251672, Date: 2024-09-02 17:23:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetDeviceUtcTimeZone_H_
#define _LC_OPENAPI_CLIENT_GetDeviceUtcTimeZone_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取UTC时间

 */

typedef struct GetDeviceUtcTimeZoneRequest 
{
	LCOpenApiRequest base;

	struct GetDeviceUtcTimeZoneRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetDeviceUtcTimeZoneRequest;

C_API GetDeviceUtcTimeZoneRequest *LCOPENAPI_INIT(GetDeviceUtcTimeZoneRequest);

typedef struct GetDeviceUtcTimeZoneResponse 
{
	LCOpenApiResponse base;

	struct GetDeviceUtcTimeZoneResponseData
	{
		
		/** 夏令时偏移,单位秒, 可选。 */
		CSTR offset;
		/** 地区描述 */
		CSTR areaDesc;
		/** 时区 */
		CSTR timeZone;
		/** 夏令时开始时间, 可选。表示“某月-该月的第几个星期-该星期的第几天，时分秒 */
		CSTR beginWeekSunTime;
		/** UTC时间 */
		CSTR utcTime;
		/** 夏令时开始时间, 可选。表示“某月-该月的第几个星期-该星期的第几天，时分秒 */
		CSTR endWeekSunTime;
		/** 按周、或按日设置的夏令时模式区分，可选，该字段不存在，则默认为day */
		CSTR mode;
		/** 格式为MM-dd HH:mm:ss夏令时开始时间, 可选。 */
		CSTR beginSunTime;
		/** 格式为MM-dd HH:mm:ss夏令时结束时间, 可选。 */
		CSTR endSunTime;
 
	} data;

} GetDeviceUtcTimeZoneResponse;

C_API GetDeviceUtcTimeZoneResponse *LCOPENAPI_INIT(GetDeviceUtcTimeZoneResponse);

#endif
