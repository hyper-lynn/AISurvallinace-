/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAirdetect_ThresholdDataSet_H_
#define _HSVIEW_CLIENT_API_transferAirdetect_ThresholdDataSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
报警阈值设置
>    请求参数说明
 + type：报警阈值类型，参考[类型定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A9%BA%E6%B0%94%E6%8E%A2%E6%B5%8B%E7%9B%B8%E5%85%B3%2FHome.md&s=pd)
 + desc：备注信息
``` 
当type == temperature或type == humidity时:
{
"maxValue" : "100", // [String], 最大值;
"minValue" : "20",  // [String], 最小值;
}
当type == PM2.5或type == VOC时:
{
"qualityType" : "qualityV1",    // [String], 质量类型, 参考[质量等级定义];
}
```
参考PaaS协议：[报警阈值设置](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A9%BA%E6%B0%94%E6%8E%A2%E6%B5%8B%E7%9B%B8%E5%85%B3%2F%E6%8A%A5%E8%AD%A6%E9%98%88%E5%80%BC%E8%AE%BE%E7%BD%AE.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAirdetect_ThresholdDataSetRequest 
{
	HsviewRequest base;

	struct transferAirdetect_ThresholdDataSetRequestData
	{
		
		/** [cstr]/device/threshold/config */
		#define _STATIC_transferAirdetect_ThresholdDataSetRequestData_url "/device/threshold/config"
		CSTR url;
		/** struct of transferAirdetect_ThresholdDataSetRequestData_Content */
		struct transferAirdetect_ThresholdDataSetRequestData_Content {
			/** struct of transferAirdetect_ThresholdDataSetRequestData_Content_Desc */
			struct transferAirdetect_ThresholdDataSetRequestData_Content_Desc {
				/** [O]质量类型 */
				CSTR qualityType;
				/** [O]最小值 */
				CSTR minValue;
				/** [O]最大值 */
				CSTR maxValue;
			} desc;
			/** 报警阈值类型 */
			CSTR type;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAirdetect_ThresholdDataSetRequest;

C_API transferAirdetect_ThresholdDataSetRequest *HSAPI_INIT(transferAirdetect_ThresholdDataSetRequest);

typedef struct transferAirdetect_ThresholdDataSetResponse 
{
	HsviewResponse base;

	struct transferAirdetect_ThresholdDataSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferAirdetect_ThresholdDataSetResponse;

C_API transferAirdetect_ThresholdDataSetResponse *HSAPI_INIT(transferAirdetect_ThresholdDataSetResponse);

#endif
