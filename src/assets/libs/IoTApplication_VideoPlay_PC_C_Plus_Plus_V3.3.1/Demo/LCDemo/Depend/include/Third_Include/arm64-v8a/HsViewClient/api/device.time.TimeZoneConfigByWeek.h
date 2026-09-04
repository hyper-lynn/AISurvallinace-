/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceTime_TimeZoneConfigByWeek_H_
#define _HSVIEW_CLIENT_API_deviceTime_TimeZoneConfigByWeek_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备时区夏令时(按周)，需要设备有WeekSummerTime能力集（easy4ip设备不支持按周设置夏令时）
timeZone：设备所在时区, 可选, 无则以设备当前配置为准
beginSumTime： 夏令时开始时间, 可选, 无则以设备当前配置为准。表示“某月-该月的第几个星期-该星期的第几天，时分秒。
endSumTime：夏令时结束时间, 可选, 无则以设备当前配置为准。表示“某月-该月的第几个星期-该星期的第几天，时分秒。
areaDesc: 可选, 城市描述信息。（旧版本设备不支持，旧版本客户端也不支持）
offset:可选, 夏令时偏移,单位秒。默认是60minutes，支持30/45/60/90/120分钟设置（按档位设置）。设置该参数时，需要设备有SummerTimeOffset能力集（3.11.0版本需求新增）

参考PaaS协议：[设置设备时区夏令时(按周)](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%97%B6%E5%8C%BA%E5%A4%8F%E4%BB%A4%E6%97%B6%2F%E8%AE%BE%E7%BD%AE%E8%AE%BE%E5%A4%87%E6%97%B6%E5%8C%BA%E5%A4%8F%E4%BB%A4%E6%97%B6%28%E6%8C%89%E5%91%A8%29.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct deviceTime_TimeZoneConfigByWeekRequest 
{
	HsviewRequest base;

	struct deviceTime_TimeZoneConfigByWeekRequestData
	{
		
		/** [O]夏令时偏移,单位秒 */
		CSTR offset;
		/** [O]时区描述，需设备支持该配置 */
		CSTR areaDesc;
		/** 设备所在时区 */
		CSTR timeZone;
		/** [O]夏令时结束时间,表示“某月-该月的第几个星期-该星期的第几天，时分秒,不传时表示关闭夏令时 */
		CSTR endSunTime;
		/** [O]夏令时开始时间,表示“某月-该月的第几个星期-该星期的第几天，时分秒,不传时表示关闭夏令时 */
		CSTR beginSunTime;
		/** APP设置的时区对应索引值，服务保存，给app拉取用 */
		CSTR areaIndex;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} deviceTime_TimeZoneConfigByWeekRequest;

C_API deviceTime_TimeZoneConfigByWeekRequest *HSAPI_INIT(deviceTime_TimeZoneConfigByWeekRequest);

typedef struct deviceTime_TimeZoneConfigByWeekResponse 
{
	HsviewResponse base;

	struct deviceTime_TimeZoneConfigByWeekResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceTime_TimeZoneConfigByWeekResponse;

C_API deviceTime_TimeZoneConfigByWeekResponse *HSAPI_INIT(deviceTime_TimeZoneConfigByWeekResponse);

#endif
