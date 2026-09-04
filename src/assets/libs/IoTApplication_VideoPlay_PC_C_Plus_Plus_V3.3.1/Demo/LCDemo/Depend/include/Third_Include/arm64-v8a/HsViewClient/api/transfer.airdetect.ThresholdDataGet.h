/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAirdetect_ThresholdDataGet_H_
#define _HSVIEW_CLIENT_API_transferAirdetect_ThresholdDataGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
报警阈值获取
请求参数说明
 + type：报警阈值类型，参考类型定义
 
响应参数说明
 + type：报警阈值类型，参考类型定义
 + desc：备注信息
```
   当type == temperature或type == humidity时:
   {
    "maxValue" : "100",
    "minValue" : "20"
   }
   当type == PM2.5或type == VOC时:
  {
    "qualityType" : "qualityV1"
  }
```
参考PaaS协议：[报警阈值获取](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A9%BA%E6%B0%94%E6%8E%A2%E6%B5%8B%E7%9B%B8%E5%85%B3%2F%E6%8A%A5%E8%AD%A6%E9%98%88%E5%80%BC%E8%8E%B7%E5%8F%96.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAirdetect_ThresholdDataGetRequest 
{
	HsviewRequest base;

	struct transferAirdetect_ThresholdDataGetRequestData
	{
		
		/** [cstr]/device/threshold/query */
		#define _STATIC_transferAirdetect_ThresholdDataGetRequestData_url "/device/threshold/query"
		CSTR url;
		/** struct of transferAirdetect_ThresholdDataGetRequestData_Content */
		struct transferAirdetect_ThresholdDataGetRequestData_Content {
			/** 报警阈值类型 */
			DECLARE_LIST(CSTR) type;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAirdetect_ThresholdDataGetRequest;

C_API transferAirdetect_ThresholdDataGetRequest *HSAPI_INIT(transferAirdetect_ThresholdDataGetRequest);

typedef struct transferAirdetect_ThresholdDataGetResponse 
{
	HsviewResponse base;

	struct transferAirdetect_ThresholdDataGetResponseData
	{
		
		/** define a list with struct of transferAirdetect_ThresholdDataGetResponseData_ThresholdElement */
		DECLARE_LIST(struct transferAirdetect_ThresholdDataGetResponseData_ThresholdElement
		{
			/** struct of transferAirdetect_ThresholdDataGetResponseData_ThresholdElement_Desc */
			struct transferAirdetect_ThresholdDataGetResponseData_ThresholdElement_Desc {
				/** [O]质量类型 */
				CSTR qualityType;
				/** [O]最小值 */
				CSTR minValue;
				/** [O]最大值 */
				CSTR maxValue;
			} desc;
			/** 报警阈值类型 */
			CSTR type;
		}) threshold;
 
	} data;

} transferAirdetect_ThresholdDataGetResponse;

C_API transferAirdetect_ThresholdDataGetResponse *HSAPI_INIT(transferAirdetect_ThresholdDataGetResponse);

#endif
