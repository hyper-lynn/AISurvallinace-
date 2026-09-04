/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_numberstatReport_AddReport_H_
#define _HSVIEW_CLIENT_API_numberstatReport_AddReport_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
创建报表
错误码
13501：报表命名不能重复
13507:报表名不匹配正则表达式
【使用平台账号签名】
 */

typedef struct numberstatReport_AddReportRequest 
{
	HsviewRequest base;

	struct numberstatReport_AddReportRequestData
	{
		
		/** 报表名称 */
		CSTR reportName;

	} data;

} numberstatReport_AddReportRequest;

C_API numberstatReport_AddReportRequest *HSAPI_INIT(numberstatReport_AddReportRequest);

typedef struct numberstatReport_AddReportResponse 
{
	HsviewResponse base;

	struct numberstatReport_AddReportResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} numberstatReport_AddReportResponse;

C_API numberstatReport_AddReportResponse *HSAPI_INIT(numberstatReport_AddReportResponse);

#endif
