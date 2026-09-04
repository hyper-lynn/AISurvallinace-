/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_TransferStream_H_
#define _LC_OPENAPI_CLIENT_TransferStream_H_

#include "LCOpenApiDefine.h"
#include "LCOpenApiRequest.h"
#include "LCOpenApiResponse.h"

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

namespace Dahua{
namespace LCOpenApi{
	using namespace std;
	class TransferStreamRequest : public LCOpenApiRequest
	{
	public:
		class TransferStreamRequestData
		{
		public:
			TransferStreamRequestData();
			~TransferStreamRequestData();
			
		public:
			/** 补充URI信息，在/device/[dev-id]/[cmd]后追加 */
			string appendUrl;
		public:
			/** 授权token(userToken或accessToken) */
			string token;
		public:
			/** 设备ID */
			string deviceId;

		};
	public:
		TransferStreamRequest();
		~TransferStreamRequest();
	public:
		virtual int build();
	public:
		TransferStreamRequestData data;
	};

	
	typedef TransferStreamRequest::TransferStreamRequestData TransferStreamRequestData;


	class TransferStreamResponse : public LCOpenApiResponse
	{
	public:
		class TransferStreamResponseData
		{
		public:
			TransferStreamResponseData();
			~TransferStreamResponseData();
			
		public:
			/** 返回的rtsp地址 */
			string url;

		};
	public:
		TransferStreamResponse();
		~TransferStreamResponse();
	public:
		virtual int parse();
	public:
		TransferStreamResponseData data;
	};

	
	typedef TransferStreamResponse::TransferStreamResponseData TransferStreamResponseData;

}
}

#endif
