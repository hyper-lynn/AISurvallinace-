/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_numberstatReport_ReportBindDev_H_
#define _HSVIEW_CLIENT_API_numberstatReport_ReportBindDev_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 报表绑定设备
【使用平台账号签名】
错误码
code：13509报表绑定设备达上限
 */

typedef struct numberstatReport_ReportBindDevRequest 
{
	HsviewRequest base;

	struct numberstatReport_ReportBindDevRequestData
	{
		
		/** 报表要绑定的设备通道号 */
		CSTR channelId;
		/** [long]报表id */
		int64 reportId;
		/** 报表要绑定的设备序列号 */
		CSTR deviceId;

	} data;

} numberstatReport_ReportBindDevRequest;

C_API numberstatReport_ReportBindDevRequest *HSAPI_INIT(numberstatReport_ReportBindDevRequest);

typedef struct numberstatReport_ReportBindDevResponse 
{
	HsviewResponse base;

	struct numberstatReport_ReportBindDevResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} numberstatReport_ReportBindDevResponse;

C_API numberstatReport_ReportBindDevResponse *HSAPI_INIT(numberstatReport_ReportBindDevResponse);

#endif
