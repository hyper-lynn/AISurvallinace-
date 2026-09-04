/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceGroup_BatchDeleteGroupDevice_H_
#define _HSVIEW_CLIENT_API_deviceGroup_BatchDeleteGroupDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
批量删除多个分组中的通道、配件列表

【需要使用平台账号签名】
 */

typedef struct deviceGroup_BatchDeleteGroupDeviceRequest 
{
	HsviewRequest base;

	struct deviceGroup_BatchDeleteGroupDeviceRequestData
	{
		
		/** define a list with struct of deviceGroup_BatchDeleteGroupDeviceRequestData_ListElement */
		DECLARE_LIST(struct deviceGroup_BatchDeleteGroupDeviceRequestData_ListElement
		{
			/** define a list with struct of deviceGroup_BatchDeleteGroupDeviceRequestData_ListElement_ApListElement */
			DECLARE_LIST(struct deviceGroup_BatchDeleteGroupDeviceRequestData_ListElement_ApListElement
			{
				/** 配件id */
				CSTR apId;
				/** 设备序列号 */
				CSTR deviceId;
			}) apList;
			/** define a list with struct of deviceGroup_BatchDeleteGroupDeviceRequestData_ListElement_ChannelListElement */
			DECLARE_LIST(struct deviceGroup_BatchDeleteGroupDeviceRequestData_ListElement_ChannelListElement
			{
				/** 通道号 */
				CSTR channelId;
				/** 设备序列号 */
				CSTR deviceId;
			}) channelList;
			/** [long]分组id */
			int64 groupId;
		}) list;

	} data;

} deviceGroup_BatchDeleteGroupDeviceRequest;

C_API deviceGroup_BatchDeleteGroupDeviceRequest *HSAPI_INIT(deviceGroup_BatchDeleteGroupDeviceRequest);

typedef struct deviceGroup_BatchDeleteGroupDeviceResponse 
{
	HsviewResponse base;

	struct deviceGroup_BatchDeleteGroupDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceGroup_BatchDeleteGroupDeviceResponse;

C_API deviceGroup_BatchDeleteGroupDeviceResponse *HSAPI_INIT(deviceGroup_BatchDeleteGroupDeviceResponse);

#endif
