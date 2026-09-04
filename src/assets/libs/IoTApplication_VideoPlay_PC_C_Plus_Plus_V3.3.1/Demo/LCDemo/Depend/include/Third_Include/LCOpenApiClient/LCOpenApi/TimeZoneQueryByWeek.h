/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_TimeZoneQueryByWeek_H_
#define _LC_OPENAPI_CLIENT_TimeZoneQueryByWeek_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询设备夏令时配置
 */

typedef struct TimeZoneQueryByWeekRequest 
{
	LCOpenApiRequest base;

	struct TimeZoneQueryByWeekRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TimeZoneQueryByWeekRequest;

C_API TimeZoneQueryByWeekRequest *LCOPENAPI_INIT(TimeZoneQueryByWeekRequest);

typedef struct TimeZoneQueryByWeekResponse 
{
	LCOpenApiResponse base;

	struct TimeZoneQueryByWeekResponseData
	{
		
		/** 夏令时结束时间,表示“某月-第几个-周几（周日：0，周一：1,....周六：6），时分秒 */
		CSTR endSunTime;
		/** 夏令时开始时间,表示“某月-第几个-周几（周日：0，周一：1,....周六：6），时分秒 */
		CSTR beginSunTime;
		/** 设备所在时区 */
		CSTR timeZone;
		/** 设置的时区对应索引值 */
		CSTR areaIndex;
 
	} data;

} TimeZoneQueryByWeekResponse;

C_API TimeZoneQueryByWeekResponse *LCOPENAPI_INIT(TimeZoneQueryByWeekResponse);

#endif
