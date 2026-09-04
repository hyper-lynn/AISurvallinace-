/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetRealTransferStream_H_
#define _HSVIEW_CLIENT_API_GetRealTransferStream_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取实时流转发地址。

encryptType取值如下：
encrypt：表示请求加密的码流
字段为空：表示请求正常的码流。

错误码补充：
9050:"device auth failed"


【使用平台账号签名】

 */

typedef struct GetRealTransferStreamRequest 
{
	HsviewRequest base;

	struct GetRealTransferStreamRequestData
	{
		
		/** 主、辅码流编号，0或者1 */
		CSTR streamId;
		/** 通道号 */
		CSTR channelId;
		/** [O]所要请求码流的加密类型 */
		CSTR encryptType;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetRealTransferStreamRequest;

C_API GetRealTransferStreamRequest *HSAPI_INIT(GetRealTransferStreamRequest);

typedef struct GetRealTransferStreamResponse 
{
	HsviewResponse base;

	struct GetRealTransferStreamResponseData
	{
		
		/** 转发源地址，如：rtsp://202.30.1.8:554/stream/12345678 */
		CSTR resource;
		/** 转发内部源地址，如：rtsp://202.30.1.8:554/stream/12345678 */
		CSTR internal_resource;
 
	} data;

} GetRealTransferStreamResponse;

C_API GetRealTransferStreamResponse *HSAPI_INIT(GetRealTransferStreamResponse);

#endif
