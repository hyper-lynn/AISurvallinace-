/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_numberstatReport_ReportUnBindDev_H_
#define _HSVIEW_CLIENT_API_numberstatReport_ReportUnBindDev_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 报表解绑设备
【使用平台账号签名】
 */

typedef struct numberstatReport_ReportUnBindDevRequest 
{
	HsviewRequest base;

	struct numberstatReport_ReportUnBindDevRequestData
	{
		
		/** 报表要绑定的设备通道号 */
		CSTR channelId;
		/** [long]报表id */
		int64 reportId;
		/** 报表要绑定的设备序列号 */
		CSTR deviceId;

	} data;

} numberstatReport_ReportUnBindDevRequest;

C_API numberstatReport_ReportUnBindDevRequest *HSAPI_INIT(numberstatReport_ReportUnBindDevRequest);

typedef struct numberstatReport_ReportUnBindDevResponse 
{
	HsviewResponse base;

	struct numberstatReport_ReportUnBindDevResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} numberstatReport_ReportUnBindDevResponse;

C_API numberstatReport_ReportUnBindDevResponse *HSAPI_INIT(numberstatReport_ReportUnBindDevResponse);

#endif
