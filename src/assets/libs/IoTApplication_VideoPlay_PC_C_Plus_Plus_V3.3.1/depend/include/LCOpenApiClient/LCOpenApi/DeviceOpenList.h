/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceOpenList_H_
#define _LC_OPENAPI_CLIENT_DeviceOpenList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
分页获取开放平台添加设备的通道基本信息

 */

typedef struct DeviceOpenListRequest 
{
	LCOpenApiRequest base;

	struct DeviceOpenListRequestData
	{
		
		/** 类型，bind:绑定, share:被别人分享或者授权, bindAndShare：同时获取绑定和被别人分享授权,bind、bindAndShare或share */
		CSTR type;
		/** 条数,最大128 */
		CSTR limit;
		/** 上次查询最后一个设备id，为-1表示从最新绑定的设备开始获取（倒序查询） */
		CSTR bindId;
		/** 是否需要配件列表信息, false:表示不需要, true表示需要 */
		CSTR needApInfo;
		/** 授权token(userToken或accessToken) */
		CSTR token;

	} data;

} DeviceOpenListRequest;

C_API DeviceOpenListRequest *LCOPENAPI_INIT(DeviceOpenListRequest);

typedef struct DeviceOpenListResponse 
{
	LCOpenApiResponse base;

	struct DeviceOpenListResponseData
	{
		
		/** [int]设备总数 */
		int count;
		/** define a list with struct of DeviceOpenListResponseData_DeviceListElement */
		DECLARE_LIST(struct DeviceOpenListResponseData_DeviceListElement
		{
			/** define a list with struct of DeviceOpenListResponseData_DeviceListElement_AplistElement */
			DECLARE_LIST(struct DeviceOpenListResponseData_DeviceListElement_AplistElement
			{
				/** 配件id */
				CSTR apId;
				/** 配件类型 */
				CSTR apType;
				/** 配件名称 */
				CSTR apName;
			}) aplist;
			/** [long]绑定分享表自增id */
			int64 bindId;
			/** define a list with struct of DeviceOpenListResponseData_DeviceListElement_ChannelsElement */
			DECLARE_LIST(struct DeviceOpenListResponseData_DeviceListElement_ChannelsElement
			{
				/** 通道名称 */
				CSTR channelName;
				/** [int]通道号 */
				int channelId;
			}) channels;
			/** 设备序列号 */
			CSTR deviceId;
		}) deviceList;
 
	} data;

} DeviceOpenListResponse;

C_API DeviceOpenListResponse *LCOPENAPI_INIT(DeviceOpenListResponse);

#endif
