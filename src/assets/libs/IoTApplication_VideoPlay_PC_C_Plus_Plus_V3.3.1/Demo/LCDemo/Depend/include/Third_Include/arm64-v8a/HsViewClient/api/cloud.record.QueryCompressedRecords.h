/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudRecord_QueryCompressedRecords_H_
#define _HSVIEW_CLIENT_API_cloudRecord_QueryCompressedRecords_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备的压缩视频信息

【默认AK、SK鉴权】
 */

typedef struct cloudRecord_QueryCompressedRecordsRequest 
{
	HsviewRequest base;

	struct cloudRecord_QueryCompressedRecordsRequestData
	{
		
		/** 通道ID */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} cloudRecord_QueryCompressedRecordsRequest;

C_API cloudRecord_QueryCompressedRecordsRequest *HSAPI_INIT(cloudRecord_QueryCompressedRecordsRequest);

typedef struct cloudRecord_QueryCompressedRecordsResponse 
{
	HsviewResponse base;

	struct cloudRecord_QueryCompressedRecordsResponseData
	{
		
		/** define a list with struct of cloudRecord_QueryCompressedRecordsResponseData_RecordsElement */
		DECLARE_LIST(struct cloudRecord_QueryCompressedRecordsResponseData_RecordsElement
		{
			/** 区域唯一标识id */
			CSTR region;
			/** 录像文件路径 */
			CSTR recordPath;
			/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式 */
			int encryptMode;
			/** 录像创建时间,yyyyMMddTHHmmss格式 */
			CSTR createTime;
			/** [long]录像ID */
			int64 recordId;
			/** [long]录像播放时长，单位s */
			int64 recordLength;
			/** 封面URL */
			CSTR thumbUrl;
			/** [long]云录像的大小，单位byte */
			int64 size;
		}) records;
 
	} data;

} cloudRecord_QueryCompressedRecordsResponse;

C_API cloudRecord_QueryCompressedRecordsResponse *HSAPI_INIT(cloudRecord_QueryCompressedRecordsResponse);

#endif
