/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudRecord_QueryCondensedRecords_H_
#define _HSVIEW_CLIENT_API_cloudRecord_QueryCondensedRecords_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据人脸库id获取浓缩视频列表

【默认AK、SK鉴权】
 */

typedef struct cloudRecord_QueryCondensedRecordsRequest 
{
	HsviewRequest base;

	struct cloudRecord_QueryCondensedRecordsRequestData
	{
		
		/** [long]上次取到的最后录像ID，-1代表第一次获取 */
		int64 recordId;
		/** [O]录像类型，为空表示不区分录像类型 */
		CSTR type;
		/** 每次获取的最大值 */
		CSTR count;

	} data;

} cloudRecord_QueryCondensedRecordsRequest;

C_API cloudRecord_QueryCondensedRecordsRequest *HSAPI_INIT(cloudRecord_QueryCondensedRecordsRequest);

typedef struct cloudRecord_QueryCondensedRecordsResponse 
{
	HsviewResponse base;

	struct cloudRecord_QueryCondensedRecordsResponseData
	{
		
		/** define a list with struct of cloudRecord_QueryCondensedRecordsResponseData_RecordsElement */
		DECLARE_LIST(struct cloudRecord_QueryCondensedRecordsResponseData_RecordsElement
		{
			/** [O]录像类型 */
			CSTR type;
			/** 区域唯一标识id */
			CSTR region;
			/** [long]录像ID */
			int64 recordId;
			/** [int]录像播放时长 */
			int timeLength;
			/** 设备序列号 */
			CSTR deviceId;
			/** 设备通道名称 */
			CSTR channelName;
			/** 开始时间，固定为0 */
			CSTR startTime;
			/** 浓缩录像相对地址 */
			CSTR recordPath;
			/** 设备通道号 */
			CSTR channelId;
			/** 缩略图URL */
			CSTR thumbUrl;
			/** [int]录像长度 */
			int size;
		}) records;
 
	} data;

} cloudRecord_QueryCondensedRecordsResponse;

C_API cloudRecord_QueryCondensedRecordsResponse *HSAPI_INIT(cloudRecord_QueryCondensedRecordsResponse);

#endif
