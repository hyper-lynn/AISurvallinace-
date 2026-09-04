/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceList_DeviceBasicListPageGet_H_
#define _HSVIEW_CLIENT_API_deviceList_DeviceBasicListPageGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
以设备的维度，分页获取设备通道信息、以及配件信息。

同一个通道同时被分享、授权会被合并为一个通道返回，权限取并集。

同一个设备的不同通道分享，如NVR，会被合并为一个设备下面的通道列表一起返回。

同一个网关相关的通道分享和配件分享，会被合并为一个设备下面的通道和配件列表一起返回。

【需要使用平台账号签名】
 */

typedef struct deviceList_DeviceBasicListPageGetRequest 
{
	HsviewRequest base;

	struct deviceList_DeviceBasicListPageGetRequestData
	{
		
		/** [O]是否需要配件列表信息, false:表示不需要, true表示需要 */
		CSTR needApInfo;
		/** [long]上次查询最后一个设备id，为-1表示从最后一个开始获取 */
		int64 bindId;
		/** [int]条数,最大128 */
		int limit;
		/** 类型，bind:绑定, share:被别人分享或者授权, bindAndShare：同时获取绑定和被别人分享授权 */
		CSTR type;

	} data;

} deviceList_DeviceBasicListPageGetRequest;

C_API deviceList_DeviceBasicListPageGetRequest *HSAPI_INIT(deviceList_DeviceBasicListPageGetRequest);

typedef struct deviceList_DeviceBasicListPageGetResponse 
{
	HsviewResponse base;

	struct deviceList_DeviceBasicListPageGetResponseData
	{
		
		/** define a list with struct of deviceList_DeviceBasicListPageGetResponseData_DeviceListElement */
		DECLARE_LIST(struct deviceList_DeviceBasicListPageGetResponseData_DeviceListElement
		{
			/** 设备品牌 */
			CSTR brand;
			/** 设备外部型号 */
			CSTR deviceModelName;
			/** 设备大类 */
			CSTR catalog;
			/** define a list with struct of deviceList_DeviceBasicListPageGetResponseData_DeviceListElement_ChannelsElement */
			DECLARE_LIST(struct deviceList_DeviceBasicListPageGetResponseData_DeviceListElement_ChannelsElement
			{
				/** 通道号 */
				CSTR channelId;
				/** 分组名称 */
				CSTR groupName;
				/** 通道名称 */
				CSTR channelName;
			}) channels;
			/** 设备型号 */
			CSTR deviceModel;
			/** 分组名称 */
			CSTR groupName;
			/** 设备序列号 */
			CSTR deviceId;
			/** 视频通道的总数量（包含未接入的通道），网关的通道数可能为0 */
			CSTR channelNum;
			/** 设备名称 */
			CSTR deviceName;
			/** [long]绑定分享表自增id */
			int64 bindId;
			/** define a list with struct of deviceList_DeviceBasicListPageGetResponseData_DeviceListElement_AplistElement */
			DECLARE_LIST(struct deviceList_DeviceBasicListPageGetResponseData_DeviceListElement_AplistElement
			{
				/** 配件类型 */
				CSTR apType;
				/** 配件id */
				CSTR apId;
				/** 分组名称 */
				CSTR groupName;
				/** 配件名称 */
				CSTR apName;
			}) aplist;
		}) deviceList;
 
	} data;

} deviceList_DeviceBasicListPageGetResponse;

C_API deviceList_DeviceBasicListPageGetResponse *HSAPI_INIT(deviceList_DeviceBasicListPageGetResponse);

#endif
