/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_logEvent_ClientLogFileInfoReport_H_
#define _HSVIEW_CLIENT_API_logEvent_ClientLogFileInfoReport_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
批量上报客户端日志文件信息
日志获取接口(仅对后台系统开放，不对app开放)：https://paas.dahuatech.com/wiki/?p=%2FSaaS%2F%E5%90%8E%E5%8F%B0%E6%8E%A5%E5%8F%A3API%2F%E6%97%A5%E5%BF%97%2Flog.event.UserClientLogFileListGet&s=pj

OfflineDeviceLog,  //离线设备日志上传功能
AddingDeviceLog //配网设备日志上传功能 
【使用平台账号签名】
 */

typedef struct logEvent_ClientLogFileInfoReportRequest 
{
	HsviewRequest base;

	struct logEvent_ClientLogFileInfoReportRequestData
	{
		
		/** define a list with struct of logEvent_ClientLogFileInfoReportRequestData_LogsElement */
		DECLARE_LIST(struct logEvent_ClientLogFileInfoReportRequestData_LogsElement
		{
			/** 功能唯一id，同一个功能成功或者失败使用不同的唯一编号 */
			CSTR id;
			/** 文件名称，例：0130c2924a50411386eb056e7bf4329b.txt */
			CSTR fileIndex;
			/** [O] 设备序列号 */
			CSTR did;
			/** [O]获取签名地址协议返回的区域信息 */
			CSTR region;
		}) logs;

	} data;

} logEvent_ClientLogFileInfoReportRequest;

C_API logEvent_ClientLogFileInfoReportRequest *HSAPI_INIT(logEvent_ClientLogFileInfoReportRequest);

typedef struct logEvent_ClientLogFileInfoReportResponse 
{
	HsviewResponse base;

	struct logEvent_ClientLogFileInfoReportResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} logEvent_ClientLogFileInfoReportResponse;

C_API logEvent_ClientLogFileInfoReportResponse *HSAPI_INIT(logEvent_ClientLogFileInfoReportResponse);

#endif
