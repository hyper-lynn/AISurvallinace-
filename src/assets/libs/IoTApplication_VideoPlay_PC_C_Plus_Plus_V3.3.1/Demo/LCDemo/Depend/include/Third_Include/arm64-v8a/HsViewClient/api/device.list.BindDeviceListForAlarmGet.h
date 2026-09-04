/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceList_BindDeviceListForAlarmGet_H_
#define _HSVIEW_CLIENT_API_deviceList_BindDeviceListForAlarmGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
以设备的维度，获取设备通道信息、以及配件信息。

只返回用户自己绑定的符合通话提醒的指定类型的设备（指定型号，平台配置）。

【需要使用平台账号签名】
 */

typedef struct deviceList_BindDeviceListForAlarmGetRequest 
{
	HsviewRequest base;

	struct deviceList_BindDeviceListForAlarmGetRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} deviceList_BindDeviceListForAlarmGetRequest;

C_API deviceList_BindDeviceListForAlarmGetRequest *HSAPI_INIT(deviceList_BindDeviceListForAlarmGetRequest);

typedef struct deviceList_BindDeviceListForAlarmGetResponse 
{
	HsviewResponse base;

	struct deviceList_BindDeviceListForAlarmGetResponseData
	{
		
		/** define a list with struct of deviceList_BindDeviceListForAlarmGetResponseData_DeviceListElement */
		DECLARE_LIST(struct deviceList_BindDeviceListForAlarmGetResponseData_DeviceListElement
		{
			/** 视频通道的总数量（包含未接入的通道） */
			CSTR channelNum;
			/** 设备名称 */
			CSTR name;
			/** define a list with struct of deviceList_BindDeviceListForAlarmGetResponseData_DeviceListElement_ChannelsElement */
			DECLARE_LIST(struct deviceList_BindDeviceListForAlarmGetResponseData_DeviceListElement_ChannelsElement
			{
				/** 通道名称 */
				CSTR channelName;
				/** 通道号 */
				CSTR channelId;
			}) channels;
			/** define a list with struct of deviceList_BindDeviceListForAlarmGetResponseData_DeviceListElement_AplistElement */
			DECLARE_LIST(struct deviceList_BindDeviceListForAlarmGetResponseData_DeviceListElement_AplistElement
			{
				/** 配件名称 */
				CSTR apName;
				/** 配件id */
				CSTR apId;
			}) aplist;
			/** 设备序列号 */
			CSTR deviceId;
		}) deviceList;
 
	} data;

} deviceList_BindDeviceListForAlarmGetResponse;

C_API deviceList_BindDeviceListForAlarmGetResponse *HSAPI_INIT(deviceList_BindDeviceListForAlarmGetResponse);

#endif
