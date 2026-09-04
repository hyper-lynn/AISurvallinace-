/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceList_BindDeviceBasicListPageGet_H_
#define _HSVIEW_CLIENT_API_deviceList_BindDeviceBasicListPageGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
以设备的维度，分页获取设备通道信息、以及配件信息。

只返回用户自己绑定的设备。

【需要使用平台账号签名】
 */

typedef struct deviceList_BindDeviceBasicListPageGetRequest 
{
	HsviewRequest base;

	struct deviceList_BindDeviceBasicListPageGetRequestData
	{
		
		/** [int]条数,最大128 */
		int limit;
		/** [long]上次查询最后一个设备id，为-1表示从最后一个开始获取 */
		int64 bindId;

	} data;

} deviceList_BindDeviceBasicListPageGetRequest;

C_API deviceList_BindDeviceBasicListPageGetRequest *HSAPI_INIT(deviceList_BindDeviceBasicListPageGetRequest);

typedef struct deviceList_BindDeviceBasicListPageGetResponse 
{
	HsviewResponse base;

	struct deviceList_BindDeviceBasicListPageGetResponseData
	{
		
		/** define a list with struct of deviceList_BindDeviceBasicListPageGetResponseData_DeviceListElement */
		DECLARE_LIST(struct deviceList_BindDeviceBasicListPageGetResponseData_DeviceListElement
		{
			/** 视频通道的总数量（包含未接入的通道） */
			CSTR channelNum;
			/** 设备名称 */
			CSTR name;
			/** define a list with struct of deviceList_BindDeviceBasicListPageGetResponseData_DeviceListElement_ChannelsElement */
			DECLARE_LIST(struct deviceList_BindDeviceBasicListPageGetResponseData_DeviceListElement_ChannelsElement
			{
				/** [O]设备能力集 */
				CSTR ability;
				/** 通道号 */
				CSTR channelId;
				/** 通道名称 */
				CSTR channelName;
			}) channels;
			/** [long]绑定分享表自增id */
			int64 bindId;
			/** define a list with struct of deviceList_BindDeviceBasicListPageGetResponseData_DeviceListElement_AplistElement */
			DECLARE_LIST(struct deviceList_BindDeviceBasicListPageGetResponseData_DeviceListElement_AplistElement
			{
				/** 配件id */
				CSTR apId;
				/** [O]配件能力项，逗号隔开，如AudioTalk,PT，详见华视微讯设备配件协议 */
				CSTR apCapacity;
				/** 配件名称 */
				CSTR apName;
			}) aplist;
			/** 设备序列号 */
			CSTR deviceId;
		}) deviceList;
 
	} data;

} deviceList_BindDeviceBasicListPageGetResponse;

C_API deviceList_BindDeviceBasicListPageGetResponse *HSAPI_INIT(deviceList_BindDeviceBasicListPageGetResponse);

#endif
