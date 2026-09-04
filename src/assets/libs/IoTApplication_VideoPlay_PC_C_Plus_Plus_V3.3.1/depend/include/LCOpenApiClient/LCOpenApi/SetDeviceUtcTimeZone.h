/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227286, Author: 251672, Date: 2024-09-02 17:23:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetDeviceUtcTimeZone_H_
#define _LC_OPENAPI_CLIENT_SetDeviceUtcTimeZone_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置UTC时区

 */

typedef struct SetDeviceUtcTimeZoneRequest 
{
	LCOpenApiRequest base;

	struct SetDeviceUtcTimeZoneRequestData
	{
		
		/** 夏令时偏移,单位秒, 可选 */
		CSTR offset;
		/** 城市描述 */
		CSTR areaDesc;
		/** [int][Not Null]时区, 取值范围: 0-38 */
		int timeZone;
		/** 夏令时开始时间, 可选,表示某月-该月的第几个星期-该星期的第几天,时分秒 */
		CSTR beginWeekSunTime;
		/** 设备ID */
		CSTR deviceId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 夏令时开始时间, 可选,表示某月-该月的第几个星期-该星期的第几天,时分秒 */
		CSTR endWeekSunTime;
		/** 夏令时开始时间, 可选 */
		CSTR beginSunTime;
		/** 夏令时结束时间, 可选 */
		CSTR endSunTime;

	} data;

} SetDeviceUtcTimeZoneRequest;

C_API SetDeviceUtcTimeZoneRequest *LCOPENAPI_INIT(SetDeviceUtcTimeZoneRequest);

typedef struct SetDeviceUtcTimeZoneResponse 
{
	LCOpenApiResponse base;

	struct SetDeviceUtcTimeZoneResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetDeviceUtcTimeZoneResponse;

C_API SetDeviceUtcTimeZoneResponse *LCOPENAPI_INIT(SetDeviceUtcTimeZoneResponse);

#endif
