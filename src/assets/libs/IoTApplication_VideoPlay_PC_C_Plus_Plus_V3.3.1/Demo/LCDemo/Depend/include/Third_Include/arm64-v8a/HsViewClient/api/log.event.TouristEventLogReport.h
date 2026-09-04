/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_logEvent_TouristEventLogReport_H_
#define _HSVIEW_CLIENT_API_logEvent_TouristEventLogReport_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
批量上报用户未登录情况下的操作日志


注：新版本的客户端业务埋点日志上报，统一以logsV3为准，上报的条数以平台控制为准。


【使用鉴权AK/SK签名】
 */

typedef struct logEvent_TouristEventLogReportRequest 
{
	HsviewRequest base;

	struct logEvent_TouristEventLogReportRequestData
	{
		
		/** define a list with struct of logEvent_TouristEventLogReportRequestData_LogsElement */
		DECLARE_LIST(struct logEvent_TouristEventLogReportRequestData_LogsElement
		{
			/** [long]毫秒时间，普通的点击事件时stopTimestamp与startTimestamp填写一样 */
			int64 stopTimestamp;
			/** [O]功能名称 */
			CSTR name;
			/** 功能唯一id，同一个功能成功或者失败使用不同的唯一编号 */
			CSTR id;
			/** [long]毫秒时间 */
			int64 startTimestamp;
			/** [O]deviceId=xxx&channelId=xxx&operType=xxx&timeSpan=xxx&flow=xxx&streamType=hls */
			CSTR content;
			/** [O]页面、按钮对象唯一ID，直至根路径 */
			CSTR object;
		}) logs;
		/** 新的客户端手动日志埋点的上报内容，Base64后的值，原格式是Json格式,具体原Json内容格式参考业务相关协议 */
		DECLARE_LIST(CSTR) logsV3;
		/** 上报内容，Base64后的值，原格式是Json格式，平台接收到后，格式不正确就丢弃掉。 */
		DECLARE_LIST(CSTR) logsV2;

	} data;

} logEvent_TouristEventLogReportRequest;

C_API logEvent_TouristEventLogReportRequest *HSAPI_INIT(logEvent_TouristEventLogReportRequest);

typedef struct logEvent_TouristEventLogReportResponse 
{
	HsviewResponse base;

	struct logEvent_TouristEventLogReportResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} logEvent_TouristEventLogReportResponse;

C_API logEvent_TouristEventLogReportResponse *HSAPI_INIT(logEvent_TouristEventLogReportResponse);

#endif
