/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceTime_TimeZoneQueryByWeek_H_
#define _HSVIEW_CLIENT_API_deviceTime_TimeZoneQueryByWeek_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备时区夏令时(按周)，easy4ip设备不支持

timeZone：设备所在时区, 可选, 无则以设备当前配置为准
beginSumTime：夏令时开始时间, 可选, 无则以设备当前配置为准。表示“某月-该月的第几个星期-该星期的第几天，时分秒。
endSumTime：夏令时结束时间, 可选, 无则以设备当前配置为准。表示“某月-该月的第几个星期-该星期的第几天，时分秒。
areaDesc:可选, 城市描述信息
offset:可选, 夏令时偏移,单位秒

参考PaaS协议：[获取设备时区夏令时(按周)](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%97%B6%E5%8C%BA%E5%A4%8F%E4%BB%A4%E6%97%B6%2F%E8%8E%B7%E5%8F%96%E8%AE%BE%E5%A4%87%E6%97%B6%E5%8C%BA%E5%A4%8F%E4%BB%A4%E6%97%B6%28%E6%8C%89%E5%91%A8%29.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct deviceTime_TimeZoneQueryByWeekRequest 
{
	HsviewRequest base;

	struct deviceTime_TimeZoneQueryByWeekRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} deviceTime_TimeZoneQueryByWeekRequest;

C_API deviceTime_TimeZoneQueryByWeekRequest *HSAPI_INIT(deviceTime_TimeZoneQueryByWeekRequest);

typedef struct deviceTime_TimeZoneQueryByWeekResponse 
{
	HsviewResponse base;

	struct deviceTime_TimeZoneQueryByWeekResponseData
	{
		
		/** [O]夏令时偏移,单位秒 */
		CSTR offset;
		/** [O]时区描述，需设备支持该配置 */
		CSTR areaDesc;
		/** [int]设备所在时区, 可选, 无则以设备当前配置为准 */
		int timeZone;
		/** 夏令时结束时间, 可选, 无则以设备当前配置为准。表示“某月-该月的第几个星期-该星期的第几天，时分秒 */
		CSTR endSunTime;
		/** 夏令时开始时间, 可选, 无则以设备当前配置为准。表示“某月-该月的第几个星期-该星期的第几天，时分秒 */
		CSTR beginSunTime;
		/** [O]APP设置的时区对应索引值，服务保存，给app拉取用,未设置过不返回该字段 */
		CSTR areaIndex;
 
	} data;

} deviceTime_TimeZoneQueryByWeekResponse;

C_API deviceTime_TimeZoneQueryByWeekResponse *HSAPI_INIT(deviceTime_TimeZoneQueryByWeekResponse);

#endif
