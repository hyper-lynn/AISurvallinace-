/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAirdetect_AllDataGet_H_
#define _HSVIEW_CLIENT_API_transferAirdetect_AllDataGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
监测数据各项指标获取
响应参数说明
 + type：数据类型，参考[类型定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A9%BA%E6%B0%94%E6%8E%A2%E6%B5%8B%E7%9B%B8%E5%85%B3%2FHome.md&s=pd)
 + minRange：取值范围最小值；
 + maxRange：取值范围最大值；
 + precision：精确度；
 + unit：单位，参考[单位定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A9%BA%E6%B0%94%E6%8E%A2%E6%B5%8B%E7%9B%B8%E5%85%B3%2FHome.md&s=pd)
 + mode：模式，参考[模式定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A9%BA%E6%B0%94%E6%8E%A2%E6%B5%8B%E7%9B%B8%E5%85%B3%2FHome.md&s=pd)
 + space：时间刻度，参考[时间刻度定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A9%BA%E6%B0%94%E6%8E%A2%E6%B5%8B%E7%9B%B8%E5%85%B3%2FHome.md&s=pd)

参考PaaS协议：[监测数据各项指标获取](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A9%BA%E6%B0%94%E6%8E%A2%E6%B5%8B%E7%9B%B8%E5%85%B3%2F%E7%9B%91%E6%B5%8B%E6%95%B0%E6%8D%AE%E5%90%84%E9%A1%B9%E6%8C%87%E6%A0%87%E8%8E%B7%E5%8F%96.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAirdetect_AllDataGetRequest 
{
	HsviewRequest base;

	struct transferAirdetect_AllDataGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/test-data/details */
		#define _STATIC_transferAirdetect_AllDataGetRequestData_url "/device/test-data/details"
		CSTR url;

	} data;

} transferAirdetect_AllDataGetRequest;

C_API transferAirdetect_AllDataGetRequest *HSAPI_INIT(transferAirdetect_AllDataGetRequest);

typedef struct transferAirdetect_AllDataGetResponse 
{
	HsviewResponse base;

	struct transferAirdetect_AllDataGetResponseData
	{
		
		/** define a list with struct of transferAirdetect_AllDataGetResponseData_DetailsElement */
		DECLARE_LIST(struct transferAirdetect_AllDataGetResponseData_DetailsElement
		{
			/** 数据类型 */
			CSTR type;
			/** 取值范围最大值 */
			CSTR maxRange;
			/** 取值范围最小值 */
			CSTR minRange;
			/** 时间刻度 */
			DECLARE_LIST(CSTR) space;
			/** 精确度 */
			CSTR precision;
			/** 模式， 如7Day */
			CSTR mode;
			/** 单位，如ppm */
			CSTR unit;
		}) details;
 
	} data;

} transferAirdetect_AllDataGetResponse;

C_API transferAirdetect_AllDataGetResponse *HSAPI_INIT(transferAirdetect_AllDataGetResponse);

#endif
