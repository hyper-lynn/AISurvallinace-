/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_numberstatReport_GetReportAbleBindDevList_H_
#define _HSVIEW_CLIENT_API_numberstatReport_GetReportAbleBindDevList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 获取可被报表绑定的设备列表
【使用平台账号签名】
 */

typedef struct numberstatReport_GetReportAbleBindDevListRequest 
{
	HsviewRequest base;

	struct numberstatReport_GetReportAbleBindDevListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} numberstatReport_GetReportAbleBindDevListRequest;

C_API numberstatReport_GetReportAbleBindDevListRequest *HSAPI_INIT(numberstatReport_GetReportAbleBindDevListRequest);

typedef struct numberstatReport_GetReportAbleBindDevListResponse 
{
	HsviewResponse base;

	struct numberstatReport_GetReportAbleBindDevListResponseData
	{
		
		/** define a list with struct of numberstatReport_GetReportAbleBindDevListResponseData_DevicesElement */
		DECLARE_LIST(struct numberstatReport_GetReportAbleBindDevListResponseData_DevicesElement
		{
			/** 设备通道号 */
			CSTR channelId;
			/** 设备通道名称 */
			CSTR channelName;
			/** 设备序列号 */
			CSTR deviceId;
		}) devices;
 
	} data;

} numberstatReport_GetReportAbleBindDevListResponse;

C_API numberstatReport_GetReportAbleBindDevListResponse *HSAPI_INIT(numberstatReport_GetReportAbleBindDevListResponse);

#endif
