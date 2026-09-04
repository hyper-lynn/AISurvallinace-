/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceBaseList_H_
#define _LC_OPENAPI_CLIENT_DeviceBaseList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备列表获取

 */

typedef struct DeviceBaseListRequest 
{
	LCOpenApiRequest base;

	struct DeviceBaseListRequestData
	{
		
		/** 类型 */
		CSTR type;
		/** [cstr]deviceBaseList */
		#define _STATIC_DeviceBaseListRequestData_method "deviceBaseList"
		CSTR method;
		/** [int]条数 */
		int limit;
		/** [long]上次查询最后一个设备Id */
		int64 bindId;
		/** 是否需要配件列表信息 */
		CSTR needApInfo;
		/** 授权token */
		CSTR token;

	} data;

} DeviceBaseListRequest;

C_API DeviceBaseListRequest *LCOPENAPI_INIT(DeviceBaseListRequest);

typedef struct DeviceBaseListResponse 
{
	LCOpenApiResponse base;

	struct DeviceBaseListResponseData
	{
		
		/** [int]当前获取的设备总数 */
		int count;
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
