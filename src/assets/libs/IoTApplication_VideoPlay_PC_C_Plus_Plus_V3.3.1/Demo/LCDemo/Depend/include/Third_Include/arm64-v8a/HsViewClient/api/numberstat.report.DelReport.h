/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_numberstatReport_DelReport_H_
#define _HSVIEW_CLIENT_API_numberstatReport_DelReport_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除报表
code:13500 绑定设备的报表不可删除
code:13506 开通客流量统计的报表不可删除
【使用平台账号签名】
 */

typedef struct numberstatReport_DelReportRequest 
{
	HsviewRequest base;

	struct numberstatReport_DelReportRequestData
	{
		
		/** [long]报表id */
		int64 reportId;

	} data;

} numberstatReport_DelReportRequest;

C_API numberstatReport_DelReportRequest *HSAPI_INIT(numberstatReport_DelReportRequest);

typedef struct numberstatReport_DelReportResponse 
{
	HsviewResponse base;

	struct numberstatReport_DelReportResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} numberstatReport_DelReportResponse;

C_API numberstatReport_DelReportResponse *HSAPI_INIT(numberstatReport_DelReportResponse);

#endif
