/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetGrowupSnaps_H_
#define _HSVIEW_CLIENT_API_GetGrowupSnaps_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取指定时间内的设备抓拍图片。支持分页。
【使用平台账号签名】
 */

typedef struct GetGrowupSnapsRequest 
{
	HsviewRequest base;

	struct GetGrowupSnapsRequestData
	{
		
		/** [int]需要查的最大条数 */
		int count;
		/** [long]从该消息ID开始查询。若要从最新开始查，填-1 */
		int64 snapId;
		/** [long]结束时间。Unix时间（单位秒），为空表示最晚时间 */
		int64 endTime;
		/** [long]开始时间。Unix时间（单位秒），为空表示最早时间 */
		int64 beginTime;
		/** 查设备下该通道号的报警消息。若为空表示查该设备下所有通道的消息。也可填通道所接的设备ID。 */
		CSTR channelId;
		/** 查该设备ID的报警消息。若为空表示查用户所有设备的消息 */
		CSTR deviceId;

	} data;

} GetGrowupSnapsRequest;

C_API GetGrowupSnapsRequest *HSAPI_INIT(GetGrowupSnapsRequest);

typedef struct GetGrowupSnapsResponse 
{
	HsviewResponse base;

	struct GetGrowupSnapsResponseData
	{
		
		/** define a list with struct of GetGrowupSnapsResponseData_SnapsElement */
		DECLARE_LIST(struct GetGrowupSnapsResponseData_SnapsElement
		{
			/** 通道所接的设备ID */
			CSTR channelDeviceId;
			/** 缩略图URL */
			CSTR thumbUrl;
			/** 图片url */
			CSTR picurl;
			/** 设备ID */
			CSTR deviceId;
			/** 设备或通道的名称 */
			CSTR name;
			/** [long]消息ID */
			int64 snapId;
			/** 通道号 */
			CSTR channelId;
			/** [long]报警时间UNIX时间戳秒 */
			int64 time;
			/** 报警时设备本地时间，格式如2014-12-12 12:12:12 */
			CSTR localDate;
		}) snaps;
 
	} data;

} GetGrowupSnapsResponse;

C_API GetGrowupSnapsResponse *HSAPI_INIT(GetGrowupSnapsResponse);

#endif
