/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceOpenList_H_
#define _LC_OPENAPI_CLIENT_DeviceOpenList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备列表获取

 */

typedef struct DeviceOpenListRequest 
{
	LCOpenApiRequest base;

	struct DeviceOpenListRequestData
	{
		
		/** 类型 */
		CSTR type;
		/** [cstr]deviceOpenList */
		#define _STATIC_DeviceOpenListRequestData_method "deviceOpenList"
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

} DeviceOpenListRequest;

C_API DeviceOpenListRequest *LCOPENAPI_INIT(DeviceOpenListRequest);

typedef struct DeviceOpenListResponse 
{
	LCOpenApiResponse base;

	struct DeviceOpenListResponseData
	{
		
		/** [int]当前获取的设备总数 */
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
				/** 通道号 */
				CSTR channelId;
				/** 通道名称 */
				CSTR channelName;
			}) channels;
			/** 设备序列号 */
			CSTR deviceId;
		}) deviceList;
 
	} data;

} DeviceOpenListResponse;

C_API DeviceOpenListResponse *LCOPENAPI_INIT(DeviceOpenListResponse);

#endif
