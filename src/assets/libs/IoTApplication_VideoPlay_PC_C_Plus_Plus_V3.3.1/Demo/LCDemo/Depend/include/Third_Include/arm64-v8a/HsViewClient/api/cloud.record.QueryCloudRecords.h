/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudRecord_QueryCloudRecords_H_
#define _HSVIEW_CLIENT_API_cloudRecord_QueryCloudRecords_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
按条件查询所有录像记录(倒序)。

encryptMode为1表示标识云录像使用自定义密钥加密,为0表示使用序列号加密

类型 - 含义                  - 是否加密
2    - 留言                  -    是
1000 - 告警（移动检测）录像  -    是
1001 - 人头检测录像          -    是
2000 - 平台定时录像          -    是
5001 - 平台聚合快播录像      -    是

【使用平台账号签名】
 */

typedef struct cloudRecord_QueryCloudRecordsRequest 
{
	HsviewRequest base;

	struct cloudRecord_QueryCloudRecordsRequestData
	{
		
		/** [O]录像类型，为空表示不区分录像类型 */
		CSTR type;
		/** [int]分页查询的数量，最大100 */
		int count;
		/** [long]上次取到的最后录像ID，-1代表第一次获取 */
		int64 recordId;
		/** 设备本地结束时间,yyyyMMddTHHmmss格式 */
		CSTR localEndTime;
		/** 通道号 */
		CSTR channelId;
		/** 设备本地开始时间,yyyyMMddTHHmmss格式 */
		CSTR localBeginTime;
		/** 设备ID */
		CSTR deviceId;

	} data;

} cloudRecord_QueryCloudRecordsRequest;

C_API cloudRecord_QueryCloudRecordsRequest *HSAPI_INIT(cloudRecord_QueryCloudRecordsRequest);

typedef struct cloudRecord_QueryCloudRecordsResponse 
{
	HsviewResponse base;

	struct cloudRecord_QueryCloudRecordsResponseData
	{
		
		/** define a list with struct of cloudRecord_QueryCloudRecordsResponseData_RecordsElement */
		DECLARE_LIST(struct cloudRecord_QueryCloudRecordsResponseData_RecordsElement
		{
			/** 录像类型 */
			CSTR type;
			/** 区域唯一标识id */
			CSTR region;
			/** 设备本地开始时间,yyyyMMddTHHmmss格式 */
			CSTR localBeginTime;
			/** 录像文件路径 */
			CSTR recordPath;
			/** 缩略图URL */
			CSTR thumbUrl;
			/** 设备本地结束时间,yyyyMMddTHHmmss格式 */
			CSTR localEndTime;
			/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式 */
			int encryptMode;
			/** [long]录像ID */
			int64 recordId;
			/** [long]云录像的大小，单位byte */
			int64 size;
		}) records;
 
	} data;

} cloudRecord_QueryCloudRecordsResponse;

C_API cloudRecord_QueryCloudRecordsResponse *HSAPI_INIT(cloudRecord_QueryCloudRecordsResponse);

#endif
