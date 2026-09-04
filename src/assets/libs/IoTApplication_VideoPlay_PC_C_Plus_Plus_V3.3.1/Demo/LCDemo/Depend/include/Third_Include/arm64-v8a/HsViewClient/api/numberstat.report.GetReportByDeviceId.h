/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_numberstatReport_GetReportByDeviceId_H_
#define _HSVIEW_CLIENT_API_numberstatReport_GetReportByDeviceId_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据设备信息获取其绑定的客流报表

code:
13000:设备未注册;13003:设备能力集不支持客流统计;13006:用户未绑定该设备或设备通道不匹配;13008:设备未绑定报表
 */

typedef struct numberstatReport_GetReportByDeviceIdRequest 
{
	HsviewRequest base;

	struct numberstatReport_GetReportByDeviceIdRequestData
	{
		
		/** 设备通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} numberstatReport_GetReportByDeviceIdRequest;

C_API numberstatReport_GetReportByDeviceIdRequest *HSAPI_INIT(numberstatReport_GetReportByDeviceIdRequest);

typedef struct numberstatReport_GetReportByDeviceIdResponse 
{
	HsviewResponse base;

	struct numberstatReport_GetReportByDeviceIdResponseData
	{
		
		/** [long]报表ID */
		int64 reportId;
		/** 报表名称 */
		CSTR reportName;
 
	} data;

} numberstatReport_GetReportByDeviceIdResponse;

C_API numberstatReport_GetReportByDeviceIdResponse *HSAPI_INIT(numberstatReport_GetReportByDeviceIdResponse);

#endif
