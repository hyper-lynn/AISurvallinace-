/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_logEvent_UserEventLogReport_H_
#define _HSVIEW_CLIENT_API_logEvent_UserEventLogReport_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
批量上报用户登录后的操作日志，业务统计数据请在content中把结果填上即可，本协议内容上报后平台不再进行二次计算，后台直接根据上报的内容进行统计。

平台针对这个协议的token鉴权，在token失效时，返回的错误码与通用接口token鉴权返回的错误不一致，特殊处理。

注：客户端统计耗时事件时（如：用户某个操作的耗时），请在content中增加cost=50（表示耗时是50毫秒），
示例：
1、 "content":"[O]deviceId=abc&channelId=0&operType=xxx&cost=50"
2、 "content":"[O]cost=50"

注：新版本的客户端业务埋点日志上报，统一以logsV3为准，上报的条数以平台控制为准。

【使用平台账号签名】
 */

typedef struct logEvent_UserEventLogReportRequest 
{
	HsviewRequest base;

	struct logEvent_UserEventLogReportRequestData
	{
		
		/** define a list with struct of logEvent_UserEventLogReportRequestData_LogsElement */
		DECLARE_LIST(struct logEvent_UserEventLogReportRequestData_LogsElement
		{
			/** [long]结束UNIX时间戳（精确到毫秒），普通的点击事件时stopTimestamp与startTimestamp填写一样 */
			int64 stopTimestamp;
			/** [O]页面、按钮对象唯一ID，直至根路径 */
			CSTR object;
			/** [O]功能名称 */
			CSTR name;
			/** [long]起始UNIX时间戳（精确到毫秒） */
			int64 startTimestamp;
			/** 功能唯一id，同一个功能成功或者失败使用不同的唯一编号 */
			CSTR id;
			/** [O]ssl握手时间,单位为ms */
			CSTR sslcost;
			/** [O]deviceId=xxx&channelId=xxx&operType=xxx&timeSpan=xxx&flow=xxx&streamType=hls */
			CSTR content;
			/** [O]接口整体耗时,单位为ms */
			CSTR apicost;
		}) logs;
		/** 新的客户端手动日志埋点的上报内容，Base64后的值，原格式是Json格式,具体原Json内容格式参考业务相关协议 */
		DECLARE_LIST(CSTR) logsV3;
		/** 神策埋点日志的上报内容，Base64后的值，原格式是Json格式，平台接收到后，格式不正确就丢弃掉。 */
		DECLARE_LIST(CSTR) logsV2;

	} data;

} logEvent_UserEventLogReportRequest;

C_API logEvent_UserEventLogReportRequest *HSAPI_INIT(logEvent_UserEventLogReportRequest);

typedef struct logEvent_UserEventLogReportResponse 
{
	HsviewResponse base;

	struct logEvent_UserEventLogReportResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} logEvent_UserEventLogReportResponse;

C_API logEvent_UserEventLogReportResponse *HSAPI_INIT(logEvent_UserEventLogReportResponse);

#endif
