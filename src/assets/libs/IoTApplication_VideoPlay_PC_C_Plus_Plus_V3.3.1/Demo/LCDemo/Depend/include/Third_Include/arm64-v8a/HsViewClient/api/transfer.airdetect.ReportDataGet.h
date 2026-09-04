/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAirdetect_ReportDataGet_H_
#define _HSVIEW_CLIENT_API_transferAirdetect_ReportDataGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
报表数据获取
>    请求参数说明
 + type：数据类型，参考[类型定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A9%BA%E6%B0%94%E6%8E%A2%E6%B5%8B%E7%9B%B8%E5%85%B3%2FHome.md&s=pd)
 + mode：模式，参考[模式定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A9%BA%E6%B0%94%E6%8E%A2%E6%B5%8B%E7%9B%B8%E5%85%B3%2FHome.md&s=pd)
 + beginLocalTime：可选，开始时间对应的设备本地时间；
 + beginUtcTime：可选，开始时间对应的UTC时间；
 + endLocalTime：可选，结束时间对应的设备本地时间；
 + endUtcTime：可选，结束时间对应的UTC时间；
 + space：时间刻度，参考[时间刻度定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A9%BA%E6%B0%94%E6%8E%A2%E6%B5%8B%E7%9B%B8%E5%85%B3%2FHome.md&s=pd)
>    响应参数说明
 + localTime：可选，数据产生的设备本地时间；
 + utcTime：可选，数据产生的UTC时间；
 + desc：备注信息；
```
当mode == 24Hour时:
{
"value" : "80", // [String], 数据值; 
}
当mode == 7Day时:
{
"value" : "80", // [String], 数据平均值; 
"maxValue" : "80",  // [String], 数据最大值; 
"minValue" : "80",  // [String], 数据最小值
}
``` 

参考PaaS协议：[报表数据获取](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A9%BA%E6%B0%94%E6%8E%A2%E6%B5%8B%E7%9B%B8%E5%85%B3%2F%E6%8A%A5%E8%A1%A8%E6%95%B0%E6%8D%AE%E8%8E%B7%E5%8F%96.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAirdetect_ReportDataGetRequest 
{
	HsviewRequest base;

	struct transferAirdetect_ReportDataGetRequestData
	{
		
		/** [cstr]/device/report/data */
		#define _STATIC_transferAirdetect_ReportDataGetRequestData_url "/device/report/data"
		CSTR url;
		/** struct of transferAirdetect_ReportDataGetRequestData_Content */
		struct transferAirdetect_ReportDataGetRequestData_Content {
			/** 数据类型 */
			CSTR type;
			/** [O]结束时间对应的UTC时间， 20180423T101326Z */
			CSTR endUtcTime;
			/** [O]开始时间对应的UTC时间， 20180423T101326Z */
			CSTR beginUtcTime;
			/** 时间刻度 */
			CSTR space;
			/** 模式 */
			CSTR mode;
			/** [O]开始时间对应的设备本地时间，20180423T101326 */
			CSTR beginLocalTime;
			/** [O]结束时间对应的设备本地时间， 20180423T101326 */
			CSTR endLocalTime;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAirdetect_ReportDataGetRequest;

C_API transferAirdetect_ReportDataGetRequest *HSAPI_INIT(transferAirdetect_ReportDataGetRequest);

typedef struct transferAirdetect_ReportDataGetResponse 
{
	HsviewResponse base;

	struct transferAirdetect_ReportDataGetResponseData
	{
		
		/** define a list with struct of transferAirdetect_ReportDataGetResponseData_DataElement */
		DECLARE_LIST(struct transferAirdetect_ReportDataGetResponseData_DataElement
		{
			/** [O]数据产生的设备本地时间， 20180423T101326 */
			CSTR localTime;
			/** [O]数据产生的UTC时间， 20180423T101326Z */
			CSTR utcTime;
			/** struct of transferAirdetect_ReportDataGetResponseData_DataElement_Desc */
			struct transferAirdetect_ReportDataGetResponseData_DataElement_Desc {
				/** [O]数据值 */
				CSTR value;
				/** [O]数据最小值 */
				CSTR minValue;
				/** [O]数据最大值 */
				CSTR maxValue;
			} desc;
		}) data;
 
	} data;

} transferAirdetect_ReportDataGetResponse;

C_API transferAirdetect_ReportDataGetResponse *HSAPI_INIT(transferAirdetect_ReportDataGetResponse);

#endif
