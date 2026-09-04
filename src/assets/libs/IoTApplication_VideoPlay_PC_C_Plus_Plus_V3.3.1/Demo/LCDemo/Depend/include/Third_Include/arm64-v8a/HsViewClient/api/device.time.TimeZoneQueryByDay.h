/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceTime_TimeZoneQueryByDay_H_
#define _HSVIEW_CLIENT_API_deviceTime_TimeZoneQueryByDay_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备时区夏令时(按日期)
timeZone：设备所在时区
mode：按周、或按日设置的夏令时模式区分，可选，该字段不存在，则默认为day：
	day：按日设置的夏令时
	week：按星期设置的夏令时
	none：夏令时使能关闭
beginSumTime：可选，格式为MM-dd HH:mm:ss夏令时开始时间，表示”3月15日18时59分20秒”。
endSumTime：可选，格式为MM-dd HH:mm:ss夏令时结束时间，表示”5月25日18时59分20秒”。
beginWeekSunTime：夏令时开始时间, 可选。表示“某月-该月的第几个星期-该星期的第几天，时分秒。
endWeekSunTime：夏令时结束时间, 可选。表示“某月-该月的第几个星期-该星期的第几天，时分秒。
areaDesc:可选, 城市描述信息
offset:可选, 夏令时偏移,单位秒
hourFormat:可选, 时间12小时制, true表示24小时，false为12小时,(需要设备有TAP能力，amcrest3.5.0版本新增)

参考PaaS协议：[获取设备时区夏令时(按日期)](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%97%B6%E5%8C%BA%E5%A4%8F%E4%BB%A4%E6%97%B6%2F%E8%8E%B7%E5%8F%96%E8%AE%BE%E5%A4%87%E6%97%B6%E5%8C%BA%E5%A4%8F%E4%BB%A4%E6%97%B6%28%E6%8C%89%E6%97%A5%E6%9C%9F%29.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct deviceTime_TimeZoneQueryByDayRequest 
{
	HsviewRequest base;

	struct deviceTime_TimeZoneQueryByDayRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} deviceTime_TimeZoneQueryByDayRequest;

C_API deviceTime_TimeZoneQueryByDayRequest *HSAPI_INIT(deviceTime_TimeZoneQueryByDayRequest);

typedef struct deviceTime_TimeZoneQueryByDayResponse 
{
	HsviewResponse base;

	struct deviceTime_TimeZoneQueryByDayResponseData
	{
		
		/** [O]时间12小时制, true表示24小时，false为12小时 */
		CSTR hourFormat;
		/** [O]格式为MM-dd HH:mm:ss夏令时开始时间 */
		CSTR beginSunTime;
		/** [int]设备所在时区 */
		int timeZone;
		/** [O]夏令时开始时间, 可选。表示“某月-该月的第几个星期-该星期的第几天，时分秒 */
		CSTR beginWeekSunTime;
		/** [O]夏令时结束时间, 可选。表示“某月-该月的第几个星期-该星期的第几天，时分秒 */
		CSTR endWeekSunTime;
		/** [O]夏令时偏移,单位秒 */
		CSTR offset;
		/** [O]时区描述，需设备支持该配置 */
		CSTR areaDesc;
		/** [O]按周、或按日设置的夏令时模式区分，可选，该字段不存在，则默认为day */
		CSTR mode;
		/** [O]格式为MM-dd HH:mm:ss夏令时结束时间 */
		CSTR endSunTime;
		/** [O]APP设置的时区对应索引值，服务保存，给app拉取用,未设置过不返回该字段 */
		CSTR areaIndex;
 
	} data;

} deviceTime_TimeZoneQueryByDayResponse;

C_API deviceTime_TimeZoneQueryByDayResponse *HSAPI_INIT(deviceTime_TimeZoneQueryByDayResponse);

#endif
