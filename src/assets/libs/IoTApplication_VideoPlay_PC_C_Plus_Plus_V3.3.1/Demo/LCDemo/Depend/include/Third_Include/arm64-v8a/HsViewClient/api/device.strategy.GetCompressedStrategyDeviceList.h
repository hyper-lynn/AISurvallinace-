/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceStrategy_GetCompressedStrategyDeviceList_H_
#define _HSVIEW_CLIENT_API_deviceStrategy_GetCompressedStrategyDeviceList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取该用户开通“精彩一天”功能的设备列表

【默认AK、SK鉴权】
 */

typedef struct deviceStrategy_GetCompressedStrategyDeviceListRequest 
{
	HsviewRequest base;

	struct deviceStrategy_GetCompressedStrategyDeviceListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} deviceStrategy_GetCompressedStrategyDeviceListRequest;

C_API deviceStrategy_GetCompressedStrategyDeviceListRequest *HSAPI_INIT(deviceStrategy_GetCompressedStrategyDeviceListRequest);

typedef struct deviceStrategy_GetCompressedStrategyDeviceListResponse 
{
	HsviewResponse base;

	struct deviceStrategy_GetCompressedStrategyDeviceListResponseData
	{
		
		/** define a list with struct of deviceStrategy_GetCompressedStrategyDeviceListResponseData_DevicesElement */
		DECLARE_LIST(struct deviceStrategy_GetCompressedStrategyDeviceListResponseData_DevicesElement
		{
			/** 通道的缩略图URL */
			CSTR thumbUrl;
			/** 通道号 */
			CSTR channelId;
			/** 通道的名称 */
			CSTR name;
			/** 设备ID */
			CSTR deviceId;
		}) devices;
 
	} data;

} deviceStrategy_GetCompressedStrategyDeviceListResponse;

C_API deviceStrategy_GetCompressedStrategyDeviceListResponse *HSAPI_INIT(deviceStrategy_GetCompressedStrategyDeviceListResponse);

#endif
