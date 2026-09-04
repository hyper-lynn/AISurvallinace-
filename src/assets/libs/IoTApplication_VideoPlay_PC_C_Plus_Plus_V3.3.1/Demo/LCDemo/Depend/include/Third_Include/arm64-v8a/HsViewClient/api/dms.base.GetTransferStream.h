/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetTransferStream_H_
#define _HSVIEW_CLIENT_API_GetTransferStream_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
请求中的[request-uri]分为以下几种：
# 实时视频：/real/[channel-id]/[stream-id]（主副码流编号0或1）
# 按文件回放：/playback/[record-id]（文件名）
# 按时间回放：/playback/[channel-id]/[starttime]
# 按时间回放（带结束时间）：/playback/[channel-id]/[starttime]-[endtime]
# 语音对讲：/talk

回复中的Resource表示转发源地址。

V2.3新增：
[sub-stream]表示所要请求的子码流类型，有以下几种取值：
# 字段为空：表示请求正常的码流
# encrypt：表示请求加密的码流
设备需要判断客户端请求的是何种码流并做相应处理。

V2.5变更:
按时间回放时，starttime和endtime取值可以有两种：
1、1970年来秒数，即Unix时间戳，这是原先的方式。
2、可以填写设备本地时间，格式为：2014_07_25_14_41_00

注：请求URI中的[request-uri]里面[channel-id]与查询录像总数一样，即可填通道号，又可填通道对应IPC的设备ID，接入库注意区分。
 */

typedef struct GetTransferStreamRequest 
{
	HsviewRequest base;

	struct GetTransferStreamRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 补充URI信息，在/device/[dev-id]/[cmd]后追加 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_GetTransferStreamRequestData_METHOD "GET"
		/** [cstr]transfer-stream */
		#define _STATIC_GetTransferStreamRequestData_CMD "transfer-stream"
		/** struct of GetTransferStreamRequestData_Body */
		struct GetTransferStreamRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetTransferStreamRequest;

C_API GetTransferStreamRequest *HSAPI_INIT(GetTransferStreamRequest);

typedef struct GetTransferStreamResponse 
{
	HsviewResponse base;

	struct GetTransferStreamResponseData
	{
		
		/** 返回的rtsp地址 */
		CSTR Resource;
 
	} data;

} GetTransferStreamResponse;

C_API GetTransferStreamResponse *HSAPI_INIT(GetTransferStreamResponse);

#endif
