/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAirdetect_RealtimeDataGet_H_
#define _HSVIEW_CLIENT_API_transferAirdetect_RealtimeDataGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
实时数据获取
请求参数说明
 + type：数据类型，参考[类型定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A9%BA%E6%B0%94%E6%8E%A2%E6%B5%8B%E7%9B%B8%E5%85%B3%2FHome.md&s=pd)
响应参数说明
 + type：数据类型，参考[类型定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A9%BA%E6%B0%94%E6%8E%A2%E6%B5%8B%E7%9B%B8%E5%85%B3%2FHome.md&s=pd)
 + value：数据值
 + desc：备注信息 
 当type == PM2.5或type == VOC时:
{
  "qualityType" : "qualityV1",    // [String], 质量类型, 参考[质量等级定义];
}

参考PaaS协议：[实时数据获取](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A9%BA%E6%B0%94%E6%8E%A2%E6%B5%8B%E7%9B%B8%E5%85%B3%2F%E5%AE%9E%E6%97%B6%E6%95%B0%E6%8D%AE%E8%8E%B7%E5%8F%96.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAirdetect_RealtimeDataGetRequest 
{
	HsviewRequest base;

	struct transferAirdetect_RealtimeDataGetRequestData
	{
		
		/** [cstr]/device/real-time/data */
		#define _STATIC_transferAirdetect_RealtimeDataGetRequestData_url "/device/real-time/data"
		CSTR url;
		/** struct of transferAirdetect_RealtimeDataGetRequestData_Content */
		struct transferAirdetect_RealtimeDataGetRequestData_Content {
			/** 数据类型 */
			DECLARE_LIST(CSTR) type;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAirdetect_RealtimeDataGetRequest;

C_API transferAirdetect_RealtimeDataGetRequest *HSAPI_INIT(transferAirdetect_RealtimeDataGetRequest);

typedef struct transferAirdetect_RealtimeDataGetResponse 
{
	HsviewResponse base;

	struct transferAirdetect_RealtimeDataGetResponseData
	{
		
		/** define a list with struct of transferAirdetect_RealtimeDataGetResponseData_DataElement */
		DECLARE_LIST(struct transferAirdetect_RealtimeDataGetResponseData_DataElement
		{
			/** 数据值 */
			CSTR value;
			/** 数据类型 */
			CSTR type;
			/** struct of transferAirdetect_RealtimeDataGetResponseData_DataElement_Desc */
			struct transferAirdetect_RealtimeDataGetResponseData_DataElement_Desc {
				/** [O]质量类型 */
				CSTR qualityType;
			} desc;
		}) data;
 
	} data;

} transferAirdetect_RealtimeDataGetResponse;

C_API transferAirdetect_RealtimeDataGetResponse *HSAPI_INIT(transferAirdetect_RealtimeDataGetResponse);

#endif
