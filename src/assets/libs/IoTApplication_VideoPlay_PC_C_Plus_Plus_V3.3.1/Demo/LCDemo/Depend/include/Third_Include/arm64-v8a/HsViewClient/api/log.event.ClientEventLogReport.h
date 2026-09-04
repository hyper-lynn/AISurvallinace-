/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_logEvent_ClientEventLogReport_H_
#define _HSVIEW_CLIENT_API_logEvent_ClientEventLogReport_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
type为客户端操作事件的类型，客户端自定义
log传的内容客户端自定义，为json对象序列化后的base64值


【使用平台账号签名】
 */

typedef struct logEvent_ClientEventLogReportRequest 
{
	HsviewRequest base;

	struct logEvent_ClientEventLogReportRequestData
	{
		
		/** define a list with struct of logEvent_ClientEventLogReportRequestData_LogsElement */
		DECLARE_LIST(struct logEvent_ClientEventLogReportRequestData_LogsElement
		{
			/** json对象序列化后的BASE64值 */
			CSTR log;
			/** 客户端操作事件 */
			CSTR type;
		}) logs;

	} data;

} logEvent_ClientEventLogReportRequest;

C_API logEvent_ClientEventLogReportRequest *HSAPI_INIT(logEvent_ClientEventLogReportRequest);

typedef struct logEvent_ClientEventLogReportResponse 
{
	HsviewResponse base;

	struct logEvent_ClientEventLogReportResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} logEvent_ClientEventLogReportResponse;

C_API logEvent_ClientEventLogReportResponse *HSAPI_INIT(logEvent_ClientEventLogReportResponse);

#endif
