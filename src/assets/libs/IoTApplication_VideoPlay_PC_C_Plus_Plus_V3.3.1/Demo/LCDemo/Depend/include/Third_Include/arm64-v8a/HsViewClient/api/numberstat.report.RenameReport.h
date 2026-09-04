/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_numberstatReport_RenameReport_H_
#define _HSVIEW_CLIENT_API_numberstatReport_RenameReport_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
报表重命名
错误码
13501：报表命名不能重复
13507:报表名不匹配正则表达式
【使用平台账号签名】
 */

typedef struct numberstatReport_RenameReportRequest 
{
	HsviewRequest base;

	struct numberstatReport_RenameReportRequestData
	{
		
		/** [long]报表id */
		int64 reportId;
		/** [String]报表新名称 */
		CSTR reportName;

	} data;

} numberstatReport_RenameReportRequest;

C_API numberstatReport_RenameReportRequest *HSAPI_INIT(numberstatReport_RenameReportRequest);

typedef struct numberstatReport_RenameReportResponse 
{
	HsviewResponse base;

	struct numberstatReport_RenameReportResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} numberstatReport_RenameReportResponse;

C_API numberstatReport_RenameReportResponse *HSAPI_INIT(numberstatReport_RenameReportResponse);

#endif
