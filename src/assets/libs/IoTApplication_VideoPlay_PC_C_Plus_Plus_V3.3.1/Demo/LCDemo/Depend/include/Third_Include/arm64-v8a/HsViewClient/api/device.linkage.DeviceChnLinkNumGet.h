/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceLinkage_DeviceChnLinkNumGet_H_
#define _HSVIEW_CLIENT_API_deviceLinkage_DeviceChnLinkNumGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备被关联的数量
【需要使用平台账号签名】
 */

typedef struct deviceLinkage_DeviceChnLinkNumGetRequest 
{
	HsviewRequest base;

	struct deviceLinkage_DeviceChnLinkNumGetRequestData
	{
		
		/** define a list with struct of deviceLinkage_DeviceChnLinkNumGetRequestData_DevicesElement */
		DECLARE_LIST(struct deviceLinkage_DeviceChnLinkNumGetRequestData_DevicesElement
		{
			/** 设备通道号 */
			CSTR channelId;
			/** 设备序列号 */
			CSTR deviceId;
		}) devices;

	} data;

} deviceLinkage_DeviceChnLinkNumGetRequest;

C_API deviceLinkage_DeviceChnLinkNumGetRequest *HSAPI_INIT(deviceLinkage_DeviceChnLinkNumGetRequest);

typedef struct deviceLinkage_DeviceChnLinkNumGetResponse 
{
	HsviewResponse base;

	struct deviceLinkage_DeviceChnLinkNumGetResponseData
	{
		
		/** define a list with struct of deviceLinkage_DeviceChnLinkNumGetResponseData_LinkagesElement */
		DECLARE_LIST(struct deviceLinkage_DeviceChnLinkNumGetResponseData_LinkagesElement
		{
			/** [int]单个设备通道关联配件的最大限制数 */
			int maxNum;
			/** 设备通道号 */
			CSTR channelId;
			/** [int]通道已经关联的配件数量 */
			int num;
			/** 设备id */
			CSTR deviceId;
		}) linkages;
 
	} data;

} deviceLinkage_DeviceChnLinkNumGetResponse;

C_API deviceLinkage_DeviceChnLinkNumGetResponse *HSAPI_INIT(deviceLinkage_DeviceChnLinkNumGetResponse);

#endif
