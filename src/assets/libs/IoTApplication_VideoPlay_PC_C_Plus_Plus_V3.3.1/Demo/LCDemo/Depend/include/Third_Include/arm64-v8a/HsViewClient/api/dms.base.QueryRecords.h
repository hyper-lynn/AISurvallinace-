/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryRecords_H_
#define _HSVIEW_CLIENT_API_QueryRecords_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询录像条目
相关参数可参考查询录像总数
Need表示需要查询从第几条到第几条。
返回录像的实际数目。具体每一条录像信息放在<Record>
 */

typedef struct QueryRecordsRequest 
{
	HsviewRequest base;

	struct QueryRecordsRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_QueryRecordsRequestData_METHOD "POST"
		/** [cstr]records */
		#define _STATIC_QueryRecordsRequestData_CMD "records"
		/** struct of QueryRecordsRequestData_Body */
		struct QueryRecordsRequestData_Body {
			/** 类型，Manual、Event、All */
			CSTR Type;
			/** 结束时间，如2010-05-25 23:59:59 */
			CSTR EndTime;
			/** 开始时间，如2010-05-25 00:00:00 */
			CSTR BeginTime;
			/** 通道号或通道的设备ID */
			CSTR ChannelID;
			/** 从第几条到第几条，如“0-25” */
			CSTR Need;
		} body;

	} data;

} QueryRecordsRequest;

C_API QueryRecordsRequest *HSAPI_INIT(QueryRecordsRequest);

typedef struct QueryRecordsResponse 
{
	HsviewResponse base;

	struct QueryRecordsResponseData
	{
		
		/** [int]录像数目 */
		int RecordNum;
		/** define a list with struct of QueryRecordsResponseData_RecordStructElement */
		DECLARE_LIST(struct QueryRecordsResponseData_RecordStructElement
		{
			/** 类型，Manual、Event、All */
			CSTR Type;
			/** 录像文件名 */
			CSTR Filename;
			/** 结束时间，如2010-05-25 23:59:59 */
			CSTR EndTime;
			/** 开始时间，如2010-05-25 00:00:00 */
			CSTR BeginTime;
			/** 通道号或通道的设备ID */
			CSTR ChannelID;
			/** [int]录像文件长度 */
			int FileLength;
		}) Record;
 
	} data;

} QueryRecordsResponse;

C_API QueryRecordsResponse *HSAPI_INIT(QueryRecordsResponse);

#endif
