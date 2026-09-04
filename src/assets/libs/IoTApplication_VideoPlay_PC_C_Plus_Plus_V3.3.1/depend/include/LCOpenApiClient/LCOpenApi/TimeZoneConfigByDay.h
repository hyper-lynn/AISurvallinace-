/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227286, Author: 251672, Date: 2024-09-02 17:23:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_TimeZoneConfigByDay_H_
#define _LC_OPENAPI_CLIENT_TimeZoneConfigByDay_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询设备夏令时配置
 */

typedef struct TimeZoneConfigByDayRequest 
{
	LCOpenApiRequest base;

	struct TimeZoneConfigByDayRequestData
	{
		
		/** 夏令时开始时间,表示“某月-该月的第几个星期-该星期的第几天，时分秒 */
		CSTR beginSunTime;
		/** [String]授权的token(userToken或accessToken) */
		CSTR token;
		/** 设备来源，lc：乐橙设备，paas：大华设备 */
		CSTR sourceType;
		/** 夏令时结束时间,表示某月-该月的第几个星期-该星期的第几天，时分秒 */
		CSTR endSunTime;
		/** 设备所在时区 */
		CSTR timeZone;
		/** 设置的时区对应索引值 */
		CSTR areaIndex;
		/** 2342s****2323 */
		CSTR deviceId;

	} data;

} TimeZoneConfigByDayRequest;

C_API TimeZoneConfigByDayRequest *LCOPENAPI_INIT(TimeZoneConfigByDayRequest);

typedef struct TimeZoneConfigByDayResponse 
{
	LCOpenApiResponse base;

	struct TimeZoneConfigByDayResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TimeZoneConfigByDayResponse;

C_API TimeZoneConfigByDayResponse *LCOPENAPI_INIT(TimeZoneConfigByDayResponse);

#endif
