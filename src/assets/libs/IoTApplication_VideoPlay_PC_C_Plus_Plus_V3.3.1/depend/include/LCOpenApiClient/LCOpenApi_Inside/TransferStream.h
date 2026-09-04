/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 224461, Author: 317222, Date: 2023-04-27 10:01:02 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_TransferStream_H_
#define _LC_OPENAPI_CLIENT_TransferStream_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
请求中的[request-uri]分为以下几种：
# 实时视频：/real/[channel-id]/[stream-id]（主副码流编号0或1）
# 按文件回放：/playback/[record-id]（文件名）
# 按时间回放：/playback/[channel-id]/[starttime]-[endtime]
# 语音对讲：/talk

回复中的Resource表示转发源地址。

[sub-stream]表示所要请求的子码流类型，有以下几种取值：
# 字段为空：表示请求正常的码流
# encrypt：表示请求加密的码流
设备需要判断客户端请求的是何种码流并做相应处理。

按时间回放时，starttime和endtime取值可以有两种：
1、1970年来秒数，即Unix时间戳，这是原先的方式。
2、	可以填写设备本地时间，格式为：2014_07_25_14_41_00
错误码：
10004：超过指定路数，拒绝给予RTSP地址
10005：超过指定个流量，拒绝给予RTSP地址

 */

typedef struct TransferStreamRequest 
{
	LCOpenApiRequest base;

	struct TransferStreamRequestData
	{
		
		/** [bool]是否为安恒加密 */
		BOOL ahEncrypt;
		/** 对讲时使用，不传表示普通对讲talk，传call表示呼叫对讲 */
		CSTR talkType;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** VTO、VTH设备对讲时，需携带该字符串告知设备，设备用于区分对讲链路 */
		CSTR callId;
		/** [int]对讲时使用，对应subType字段。设备能力集包含AudioEncodeControlV2或AECV3，传5，其他情况传0 */
		int streamId;
		/** 补充URI信息，在/device/[dev-id]/[cmd]后追加 */
		CSTR appendUrl;
		/** first：方案一，实时流和语音对讲，两个不同的链路 second：方案二，实时流和语音对讲，在同一个链路 */
		CSTR design;
		/** 设备ID */
		CSTR deviceId;

	} data;

} TransferStreamRequest;

C_API TransferStreamRequest *LCOPENAPI_INIT(TransferStreamRequest);

typedef struct TransferStreamResponse 
{
	LCOpenApiResponse base;

	struct TransferStreamResponseData
	{
		
		/** 返回的tls拉流地址(新增) */
		CSTR tlsUrl;
		/** 返回的拉流地址 */
		CSTR url;
 
	} data;

} TransferStreamResponse;

C_API TransferStreamResponse *LCOPENAPI_INIT(TransferStreamResponse);

#endif
