/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceBaseList_H_
#define _LC_OPENAPI_CLIENT_DeviceBaseList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
分页获取乐橙app添加或分享的设备通道基本信息

 */

typedef struct DeviceBaseListRequest 
{
	LCOpenApiRequest base;

	struct DeviceBaseListRequestData
	{
		
		/** 类型，bind:绑定, share:被别人分享或者授权, bindAndShare：同时获取绑定和被别人分享授权,bind、bindAndShare或share */
		CSTR type;
		/** [cstr]deviceBaseList */
		#define _STATIC_DeviceBaseListRequestData_method "deviceBaseList"
		CSTR method;
		/** [int]条数,最大128 */
		int limit;
		/** [long]上次查询最后一个设备Id */
		int64 bindId;
		/** 是否需要配件列表信息, false:表示不需要, true表示需要 */
		CSTR needApInfo;
		/** 授权token(userToken或accessToken) */
		CSTR token;

	} data;

} DeviceBaseListRequest;

C_API DeviceBaseListRequest *LCOPENAPI_INIT(DeviceBaseListRequest);

typedef struct DeviceBaseListResponse 
{
	LCOpenApiResponse base;

	struct DeviceBaseListResponseData
	{
		
		/** 设备数 */
		CSTR count;
		/** define a list with struct of DeviceBaseListResponseData_DeviceListElement */
		DECLARE_LIST(struct DeviceBaseListResponseData_DeviceListElement
		{
			/** define a list with struct of DeviceBaseListResponseData_DeviceListElement_AplistElement */
			DECLARE_LIST(struct DeviceBaseListResponseData_DeviceListElement_AplistElement
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
			/** define a list with struct of DeviceBaseListResponseData_DeviceListElement_ChannelsElement */
			DECLARE_LIST(struct DeviceBaseListResponseData_DeviceListElement_ChannelsElement
			{
				/** 通道号 */
				CSTR channelId;
				/** 通道名称 */
				CSTR channelName;
			}) channels;
			/** 设备序列号 */
			CSTR deviceId;
		}) deviceList;
 
	} data;

} DeviceBaseListResponse;

C_API DeviceBaseListResponse *LCOPENAPI_INIT(DeviceBaseListResponse);

#endif
