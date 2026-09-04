/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryCloudRecords_H_
#define _HSVIEW_CLIENT_API_QueryCloudRecords_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
按条件查询所有录像记录。

类型 - 含义                  - 是否加密    -  备注
1    - 手动录像              -    否       -  X-MINI设备功能
2    - 留言                  -    是       -  TC5S需求
3    - 求救录像              -    是       -  TC5S需求（废弃）
1000 - 告警（移动检测）录像  -    是       -  同file-stream（原报警录像）
1001 - 人头检测录像          -    是       -  TC5S需求
2000 - 云录像                -    是       -  定时录像
注：为空表示原报警录像

encryptMode为1表示标识云录像是否使用自定义密钥加密,为0表示不加密或者使用序列号加密
【使用平台账号签名】
 */

typedef struct QueryCloudRecordsRequest 
{
	HsviewRequest base;

	struct QueryCloudRecordsRequestData
	{
		
		/** [O]录像类型，如果为空表示原报警录像 */
		CSTR type;
		/** 通道号或通道的设备ID */
		CSTR channelId;
		/** [long]结束时间，Unix时间戳，1970年秒数 */
		int64 endTime;
		/** [long]开始时间，Unix时间戳，1970年秒数 */
		int64 beginTime;
		/** 从第几条到第几条，如“0-25” */
		CSTR need;
		/** 设备ID */
		CSTR deviceId;

	} data;

} QueryCloudRecordsRequest;

C_API QueryCloudRecordsRequest *HSAPI_INIT(QueryCloudRecordsRequest);

typedef struct QueryCloudRecordsResponse 
{
	HsviewResponse base;

	struct QueryCloudRecordsResponseData
	{
		
		/** define a list with struct of QueryCloudRecordsResponseData_RecordsElement */
		DECLARE_LIST(struct QueryCloudRecordsResponseData_RecordsElement
		{
			/** 录像本地开始时间（字符串） */
			CSTR beginTimeLocal;
			/** [long]录像ID */
			int64 recordId;
			/** 设备ID */
			CSTR deviceId;
			/** 录像本地结束时间（字符串） */
			CSTR endTimeLocal;
			/** 录像文件路径 */
			CSTR recordPath;
			/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式 */
			int encryptMode;
			/** [long]开始时间，Unix时间戳，1970年秒数 */
			int64 beginTime;
			/** 缩略图URL */
			CSTR thumbUrl;
			/** 通道号 */
			CSTR channelId;
			/** [long]结束时间，Unix时间戳，1970年秒数 */
			int64 endTime;
			/** [long]云录像的大小，单位byte */
			int64 size;
		}) records;
 
	} data;

} QueryCloudRecordsResponse;

C_API QueryCloudRecordsResponse *HSAPI_INIT(QueryCloudRecordsResponse);

#endif
