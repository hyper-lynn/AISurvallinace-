/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_ManStayStatGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_ManStayStatGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
预案获取

-channelId：[UInt8]，通道ID，默认从0开始。
-beginTime：[string]，记录的开始时间，设备时间。
-beginUtcTime：[string]，可选，记录的开始时间，UTC时间。
-endTime：[string]，记录的结束时间，设备时间。
-endUtcTime：[string]，可选，记录的结束时间，UTC时间。
-areaID：[int] 区域ID, 没有该字段或者为0，为单区域
-rule: [string] 可选，与设备协议保持一致
-ManNumDetection： 默认区域人员检测
-pageNum：[UInt64]，当前页码, 从0开始。
-numsPerPage：[UInt64]，每次返回的单页最大记录数。

参考PaaS协议：[获取人员滞留信息](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E5%AE%A2%E6%B5%81%E9%87%8F%E6%99%BA%E8%83%BD%E6%93%8D%E4%BD%9C%2F%E8%8E%B7%E5%8F%96%E4%BA%BA%E5%91%98%E6%BB%9E%E7%95%99%E4%BF%A1%E6%81%AF.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_ManStayStatGetRequest 
{
	HsviewRequest base;

	struct transferDevice_ManStayStatGetRequestData
	{
		
		/** [cstr]/device/manstaystat/data */
		#define _STATIC_transferDevice_ManStayStatGetRequestData_url "/device/manstaystat/data"
		CSTR url;
		/** struct of transferDevice_ManStayStatGetRequestData_Content */
		struct transferDevice_ManStayStatGetRequestData_Content {
			/** [int] 每次返回的单页最大记录数 */
			int numsPerPage;
			/** 记录的结束时间，设备时间20170613T160500 */
			CSTR endTime;
			/** [int] 当前页码, 从0开始 */
			int pageNum;
			/** 与设备协议保持一致,ManNumDetection区域人员检测 */
			CSTR rule;
			/** [O]可选，记录的开始时间，UTC时间20170613T160000Z */
			CSTR beginUtcTime;
			/** [int] 区域ID, 没有该字段或者为0，为单区域 */
			int areaID;
			/** [int] 通道ID */
			int channelId;
			/** [O]可选，记录的结束时间，UTC时间20170613T160500Z */
			CSTR endUtcTime;
			/** 记录的开始时间，设备时间20170613T160000 */
			CSTR beginTime;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_ManStayStatGetRequest;

C_API transferDevice_ManStayStatGetRequest *HSAPI_INIT(transferDevice_ManStayStatGetRequest);

typedef struct transferDevice_ManStayStatGetResponse 
{
	HsviewResponse base;

	struct transferDevice_ManStayStatGetResponseData
	{
		
		/** [int] 区域内人数, 没有该字段或者为0，为默认值 */
		int number;
		/** define a list with struct of transferDevice_ManStayStatGetResponseData_ManStayStatElement */
		DECLARE_LIST(struct transferDevice_ManStayStatGetResponseData_ManStayStatElement
		{
			/** 记录的结束时间20120104T000000 */
			CSTR endTime;
			/** 记录的开始时间20120104T000000 */
			CSTR beginTime;
		}) manStayStat;
		/** [int] 通道ID */
		int channelId;
		/** 与设备协议保持一致,ManNumDetection区域人员检测 */
		CSTR rule;
		/** [int] 区域ID, 没有该字段或者为0，为单区域 */
		int areaID;
 
	} data;

} transferDevice_ManStayStatGetResponse;

C_API transferDevice_ManStayStatGetResponse *HSAPI_INIT(transferDevice_ManStayStatGetResponse);

#endif
