/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetGrowupHistory_H_
#define _HSVIEW_CLIENT_API_GetGrowupHistory_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取成长记录。
平台根据当前时间返回前三天的抓拍图片和浓缩视频列表。
【使用平台账号签名】
 */

typedef struct GetGrowupHistoryRequest 
{
	HsviewRequest base;

	struct GetGrowupHistoryRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetGrowupHistoryRequest;

C_API GetGrowupHistoryRequest *HSAPI_INIT(GetGrowupHistoryRequest);

typedef struct GetGrowupHistoryResponse 
{
	HsviewResponse base;

	struct GetGrowupHistoryResponseData
	{
		
		/** define a list with struct of GetGrowupHistoryResponseData_SnapsElement */
		DECLARE_LIST(struct GetGrowupHistoryResponseData_SnapsElement
		{
			/** 日期，格式形如：20150811 */
			CSTR date;
			/** [int]图片数量 */
			int count;
			/** 缩略图URL */
			CSTR thumb;
		}) snaps;
		/** define a list with struct of GetGrowupHistoryResponseData_VideosElement */
		DECLARE_LIST(struct GetGrowupHistoryResponseData_VideosElement
		{
			/** 日期，格式形如：20150811 */
			CSTR date;
			/** [long]浓缩视频录像ID */
			int64 recordId;
			/** 缩略图URL */
			CSTR thumb;
		}) videos;
 
	} data;

} GetGrowupHistoryResponse;

C_API GetGrowupHistoryResponse *HSAPI_INIT(GetGrowupHistoryResponse);

#endif
