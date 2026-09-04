/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_numberstatReport_QueryReportStatisticData_H_
#define _HSVIEW_CLIENT_API_numberstatReport_QueryReportStatisticData_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 查看报表客流分析数据
请求参数：
unit:客流分析折线图展示单位
 day按天展示24小时数据
 week按周展示7天数据
 month按月展示28/29/30/31天数据
 year按年展示12个月数据
timeList：分析数据的时间条件，根据unit来作区分
 day：yyyyMMdd,代表具体日期到日如20170914
 week: yyyyMMdd,代表某周第一天日期，如20170911为该周第一天
 month：yyyyMM,代表某年某月
 year：yyyy,代表某年
响应参数：
type:报表类型，normal普通报表，vip表示增值报表
dataList:折线图数据，返回参数依赖折线图单位unit
day：返回每一天24小时数据
week: 返回每周7天数据
month：返回每月28/29/30/31天数据
year：返回每年12月的数据
错误码：
13000：设备不存在，13006：设备未绑定用户，13008：设备未绑定报表，13508：报表不存在
【使用平台账号签名】
 */

typedef struct numberstatReport_QueryReportStatisticDataRequest 
{
	HsviewRequest base;

	struct numberstatReport_QueryReportStatisticDataRequestData
	{
		
		/** [O][long]报表id,pc端查看报表必须传报表id */
		CSTR reportId;
		/** 折线图展示单位 */
		CSTR unit;
		/** [O]报表要绑定的设备通道号,app端查看报表必须 */
		CSTR channelId;
		/** 时间段 */
		DECLARE_LIST(CSTR) timeList;
		/** [O]设备序列号,app端查看报表必须传设备序列号 */
		CSTR deviceId;

	} data;

} numberstatReport_QueryReportStatisticDataRequest;

C_API numberstatReport_QueryReportStatisticDataRequest *HSAPI_INIT(numberstatReport_QueryReportStatisticDataRequest);

typedef struct numberstatReport_QueryReportStatisticDataResponse 
{
	HsviewResponse base;

	struct numberstatReport_QueryReportStatisticDataResponseData
	{
		
		/** 报表套餐类型 */
		CSTR strategyType;
		/** [long]报表id */
		int64 reportId;
		/** 数据更新时间,yyyyMMddTHHmmss */
		CSTR updateTime;
		/** define a list with struct of numberstatReport_QueryReportStatisticDataResponseData_DataListElement */
		DECLARE_LIST(struct numberstatReport_QueryReportStatisticDataResponseData_DataListElement
		{
			/** 请求时间段 */
			CSTR time;
			/** [long]时间点客流总量 */
			DECLARE_LIST(int64) number;
		}) dataList;
		/** struct of numberstatReport_QueryReportStatisticDataResponseData_NumberStatList */
		struct numberstatReport_QueryReportStatisticDataResponseData_NumberStatList {
			/** [long]去年客流总量 */
			int64 lastyear;
			/** [long]本周客流总量 */
			int64 week;
			/** [long]今日客流总量 */
			int64 day;
			/** [long]本月客流总量 */
			int64 month;
			/** [long]上周客流总量 */
			int64 lastweek;
			/** [long]今年客流总量 */
			int64 year;
			/** [long]上月客流总量 */
			int64 lastmonth;
			/** [long]昨日客流总量 */
			int64 yesterday;
		} numberStatList;
		/** 我的客流报表 */
		CSTR reportName;
 
	} data;

} numberstatReport_QueryReportStatisticDataResponse;

C_API numberstatReport_QueryReportStatisticDataResponse *HSAPI_INIT(numberstatReport_QueryReportStatisticDataResponse);

#endif
