/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceNumberStatReport_H_
#define _LC_OPENAPI_CLIENT_DeviceNumberStatReport_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询设备客流统计报表
 */

typedef struct DeviceNumberStatReportRequest 
{
	LCOpenApiRequest base;

	struct DeviceNumberStatReportRequestData
	{
		
		/** 设备通道号 */
		CSTR channelId;
		/** 授权的token */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} DeviceNumberStatReportRequest;

C_API DeviceNumberStatReportRequest *LCOPENAPI_INIT(DeviceNumberStatReportRequest);

typedef struct DeviceNumberStatReportResponse 
{
	LCOpenApiResponse base;

	struct DeviceNumberStatReportResponseData
	{
		
		/** [long]报表ID */
		int64 reportId;
		/** 报表名称 */
		CSTR reportName;
 
	} data;

} DeviceNumberStatReportResponse;

C_API DeviceNumberStatReportResponse *LCOPENAPI_INIT(DeviceNumberStatReportResponse);

#endif
