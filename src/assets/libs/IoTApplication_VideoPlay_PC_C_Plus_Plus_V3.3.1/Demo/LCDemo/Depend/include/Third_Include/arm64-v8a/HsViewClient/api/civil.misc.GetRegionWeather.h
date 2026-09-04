/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetRegionWeather_H_
#define _HSVIEW_CLIENT_API_GetRegionWeather_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取地区的天气信息
region：格式为：省/市/区，由设置设备区域的省市区字段通过"/"分割组合而成。
startDate：天气预报起始日期，只能查询当天和以后的日期,格式：yyyyMMdd
days：天气预报天数，仅支持一周内天气预报（7天）

【不需要签名】
 */

typedef struct GetRegionWeatherRequest 
{
	HsviewRequest base;

	struct GetRegionWeatherRequestData
	{
		
		/** 天气预报起始日期 */
		CSTR startDate;
		/** [int]要查询的天气天数 */
		int days;
		/** 地区信息 */
		CSTR region;

	} data;

} GetRegionWeatherRequest;

C_API GetRegionWeatherRequest *HSAPI_INIT(GetRegionWeatherRequest);

typedef struct GetRegionWeatherResponse 
{
	HsviewResponse base;

	struct GetRegionWeatherResponseData
	{
		
		/** define a list with struct of GetRegionWeatherResponseData_WeathersElement */
		DECLARE_LIST(struct GetRegionWeatherResponseData_WeathersElement
		{
			/** 晚上天气，格式：阴 */
			CSTR night_weather;
			/** 02 */
			CSTR night_weather_code;
			/** 白天天气编号07 */
			CSTR day_weather_code;
			/** 日期,格式：yyyyMMdd */
			CSTR date;
			/** struct of GetRegionWeatherResponseData_WeathersElement_Index */
			struct GetRegionWeatherResponseData_WeathersElement_Index {
				/** struct of GetRegionWeatherResponseData_WeathersElement_Index_Clothes */
				struct GetRegionWeatherResponseData_WeathersElement_Index_Clothes {
					/** 较舒适 */
					CSTR title;
					/** 建议穿薄外套或牛仔裤等服装。 */
					CSTR desc;
				} clothes;
				/** struct of GetRegionWeatherResponseData_WeathersElement_Index_Aqi */
				struct GetRegionWeatherResponseData_WeathersElement_Index_Aqi {
					/** 良 */
					CSTR title;
					/** 气象条件有利于空气污染物扩散。 */
					CSTR desc;
				} aqi;
				/** struct of GetRegionWeatherResponseData_WeathersElement_Index_Travel */
				struct GetRegionWeatherResponseData_WeathersElement_Index_Travel {
					/** 较不宜 */
					CSTR title;
					/** 有降水，推荐您在室内进行休闲运动。 */
					CSTR desc;
				} travel;
				/** struct of GetRegionWeatherResponseData_WeathersElement_Index_Wash_car */
				struct GetRegionWeatherResponseData_WeathersElement_Index_Wash_car {
					/** 不宜 */
					CSTR title;
					/** 有雨，雨水和泥水会弄脏爱车。 */
					CSTR desc;
				} wash_car;
				/** struct of GetRegionWeatherResponseData_WeathersElement_Index_Uv */
				struct GetRegionWeatherResponseData_WeathersElement_Index_Uv {
					/** 最弱 */
					CSTR title;
					/** 辐射弱，涂擦SPF8-12防晒护肤品。 */
					CSTR desc;
				} uv;
				/** struct of GetRegionWeatherResponseData_WeathersElement_Index_Cold */
				struct GetRegionWeatherResponseData_WeathersElement_Index_Cold {
					/** 较易发 */
					CSTR title;
					/** 天较凉，增加衣服，注意防护。 */
					CSTR desc;
				} cold;
			} index;
			/** 晚上温度（单位摄氏度）：6 */
			CSTR night_air_temperature;
			/** 白天天气图标，格式：http://app1.showapi.com/weather/icon/day/07.png */
			CSTR day_weather_pic;
			/** 白天温度（单位摄氏度）：9 */
			CSTR day_air_temperature;
			/** [O]空气质量，目前只有当天会有，没有值则不传该字段，优、良、轻度污染、中度污染、重度污染、严重污染 6类 */
			CSTR quality;
			/** 白天天气，格式：小雨 */
			CSTR day_weather;
			/** 北风 */
			CSTR day_wind_direction;
			/** 北风 */
			CSTR night_wind_direction;
			/** 白天风力：4-5级 8.0~10.7m/s */
			CSTR day_wind_power;
			/** 晚上天气图标，格式：http://app1.showapi.com/weather/icon/night/02.png */
			CSTR night_weather_pic;
			/** 晚上风力：4-5级 8.0~10.7m/s */
			CSTR night_wind_power;
		}) weathers;
 
	} data;

} GetRegionWeatherResponse;

C_API GetRegionWeatherResponse *HSAPI_INIT(GetRegionWeatherResponse);

#endif
