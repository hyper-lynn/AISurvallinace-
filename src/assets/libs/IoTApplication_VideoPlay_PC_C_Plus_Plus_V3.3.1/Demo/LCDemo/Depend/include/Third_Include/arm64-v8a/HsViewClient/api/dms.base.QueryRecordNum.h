/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryRecordNum_H_
#define _HSVIEW_CLIENT_API_QueryRecordNum_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询录像总数
Type表示录像类型，有：
	Manual：手动录像
	Event：事件录像
	All：所有录像
返回录像的总数RecordNum

<ChannelID>字段可填2种值：
1、通道号，从0开始，是一个数字。
2、前端设备ID，就是设备所接前端IPC的设备ID，是一个字符串。
接入库需要判断请求中到底填的是通道号还是设备ID，根据不同的值对录像进行查询。
 */

typedef struct QueryRecordNumRequest 
{
	HsviewRequest base;

	struct QueryRecordNumRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_QueryRecordNumRequestData_METHOD "POST"
		/** [cstr]record-num */
		#define _STATIC_QueryRecordNumRequestData_CMD "record-num"
		/** struct of QueryRecordNumRequestData_Body */
		struct QueryRecordNumRequestData_Body {
			/** 结束时间，如2010-05-25 23:59:59 */
			CSTR EndTime;
			/** 类型，Manual、Event、All */
			CSTR Type;
			/** 通道号或通道的设备ID */
			CSTR ChannelID;
			/** 开始时间，如2010-05-25 00:00:00 */
			CSTR BeginTime;
		} body;

	} data;

} QueryRecordNumRequest;

C_API QueryRecordNumRequest *HSAPI_INIT(QueryRecordNumRequest);

typedef struct QueryRecordNumResponse 
{
	HsviewResponse base;

	struct QueryRecordNumResponseData
	{
		
		/** [int]录像总数 */
		int RecordNum;
 
	} data;

} QueryRecordNumResponse;

C_API QueryRecordNumResponse *HSAPI_INIT(QueryRecordNumResponse);

#endif
