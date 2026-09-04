/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227286, Author: 251672, Date: 2024-09-02 17:23:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_TimeZoneConfigByWeek_H_
#define _LC_OPENAPI_CLIENT_TimeZoneConfigByWeek_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置设备夏令时
 */

typedef struct TimeZoneConfigByWeekRequest 
{
	LCOpenApiRequest base;

	struct TimeZoneConfigByWeekRequestData
	{
		
		/** 夏令时开始时间,表示“某月-第几个-周几（周日：0，周一：1,....周六：6），时分秒 */
		CSTR beginSunTime;
		/** [String]授权的token(userToken或accessToken) */
		CSTR token;
		/** 设备来源，lc：乐橙设备，paas：大华设备 */
		CSTR sourceType;
		/** 夏令时结束时间,表示“某月-第几个-周几（周日：0，周一：1,....周六：6），时分秒 */
		CSTR endSunTime;
		/** 设备所在时区 */
		CSTR timeZone;
		/** 设置的时区对应索引值 */
		CSTR areaIndex;
		/** 2342s****2323 */
		CSTR deviceId;

	} data;

} TimeZoneConfigByWeekRequest;

C_API TimeZoneConfigByWeekRequest *LCOPENAPI_INIT(TimeZoneConfigByWeekRequest);

typedef struct TimeZoneConfigByWeekResponse 
{
	LCOpenApiResponse base;

	struct TimeZoneConfigByWeekResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TimeZoneConfigByWeekResponse;

C_API TimeZoneConfigByWeekResponse *LCOPENAPI_INIT(TimeZoneConfigByWeekResponse);

#endif
