/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetDeviceSnapList_H_
#define _HSVIEW_CLIENT_API_GetDeviceSnapList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
按条件查询设备抓图记录。

【使用平台账号签名】
 */

typedef struct GetDeviceSnapListRequest 
{
	HsviewRequest base;

	struct GetDeviceSnapListRequestData
	{
		
		/** [int]需要查的最大条数 */
		int count;
		/** [long]从该抓图ID开始查询。若要从最新开始查，填-1 */
		int64 snapId;
		/** [long]结束时间。Unix时间（单位秒），0表示最晚时间 */
		int64 endTime;
		/** [long]开始时间。Unix时间（单位秒），0表示最早时间 */
		int64 beginTime;
		/** 查设备下该通道号的报警消息。若为空表示查该设备下所有通道的抓图。也可填通道所接的设备ID。 */
		CSTR channelId;
		/** 查该设备ID的报警消息。若为空表示查用户所有抓图 */
		CSTR deviceId;

	} data;

} GetDeviceSnapListRequest;

C_API GetDeviceSnapListRequest *HSAPI_INIT(GetDeviceSnapListRequest);

typedef struct GetDeviceSnapListResponse 
{
	HsviewResponse base;

	struct GetDeviceSnapListResponseData
	{
		
		/** define a list with struct of GetDeviceSnapListResponseData_SnapsElement */
		DECLARE_LIST(struct GetDeviceSnapListResponseData_SnapsElement
		{
			/** [long]报警时间UNIX时间戳秒 */
			int64 time;
			/** [long]消息ID */
			int64 snapId;
			/** [String]设备抓图token */
			CSTR token;
			/** [String]通道号 */
			CSTR channelId;
			/** [String]设备抓图地址 */
			CSTR url;
			/** [String]设备ID */
			CSTR deviceId;
		}) snaps;
 
	} data;

} GetDeviceSnapListResponse;

C_API GetDeviceSnapListResponse *HSAPI_INIT(GetDeviceSnapListResponse);

#endif
