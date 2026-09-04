/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_numberstatReport_GetReportList_H_
#define _HSVIEW_CLIENT_API_numberstatReport_GetReportList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 获取当前用户已创建的报表列表
查询结果按创建时间正序
【使用平台账号签名】
 */

typedef struct numberstatReport_GetReportListRequest 
{
	HsviewRequest base;

	struct numberstatReport_GetReportListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} numberstatReport_GetReportListRequest;

C_API numberstatReport_GetReportListRequest *HSAPI_INIT(numberstatReport_GetReportListRequest);

typedef struct numberstatReport_GetReportListResponse 
{
	HsviewResponse base;

	struct numberstatReport_GetReportListResponseData
	{
		
		/** define a list with struct of numberstatReport_GetReportListResponseData_ReportListElement */
		DECLARE_LIST(struct numberstatReport_GetReportListResponseData_ReportListElement
		{
			/** define a list with struct of numberstatReport_GetReportListResponseData_ReportListElement_BindDevicesElement */
			DECLARE_LIST(struct numberstatReport_GetReportListResponseData_ReportListElement_BindDevicesElement
			{
				/** 报表要绑定的设备通道号 */
				CSTR channelId;
				/** 设备通道名称 */
				CSTR channelName;
				/** 报表要绑定的设备序列号 */
				CSTR deviceId;
			}) bindDevices;
			/** [long]报表ID */
			int64 reportId;
			/** 报表名称 */
			CSTR reportName;
		}) reportList;
 
	} data;

} numberstatReport_GetReportListResponse;

C_API numberstatReport_GetReportListResponse *HSAPI_INIT(numberstatReport_GetReportListResponse);

#endif
