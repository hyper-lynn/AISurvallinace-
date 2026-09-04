/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetDeviceStream_H_
#define _HSVIEW_CLIENT_API_GetDeviceStream_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备码流地址，包括直播、回放、对讲。

码流分为三种类型：
type="real"时，表示直播；
type="playback"时，表示回放；
type="talk"时，表示语音对讲。

支持两种码流协议：RTSP和HLS，客户端请求时可选。注意：回放和语音对讲只支持RTSP！也即只有直播才能选择RTSP或HLS。

【使用平台账号签名认证】
 */

typedef struct GetDeviceStreamRequest 
{
	HsviewRequest base;

	struct GetDeviceStreamRequestData
	{
		
		/** 所需码流类型，“real”表示直播，“playback”表示回放，“talk”表示语音对讲 */
		CSTR type;
		/** 码流协议，可填“RTSP”或“HLS” */
		CSTR protocol;
		/** [int][O] 0表示主码流，1表示辅码流。直播类型必填 */
		int streamId;
		/** [O]通道号。直播类型必填 */
		CSTR channelId;
		/** [O]设备录像文件名。回放类型必填 */
		CSTR recordFile;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetDeviceStreamRequest;

C_API GetDeviceStreamRequest *HSAPI_INIT(GetDeviceStreamRequest);

typedef struct GetDeviceStreamResponse 
{
	HsviewResponse base;

	struct GetDeviceStreamResponseData
	{
		
		/** 可访问的码流地址，rtsp或http */
		CSTR url;
 
	} data;

} GetDeviceStreamResponse;

C_API GetDeviceStreamResponse *HSAPI_INIT(GetDeviceStreamResponse);

#endif
