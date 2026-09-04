/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetRealplayUrl_H_
#define _HSVIEW_CLIENT_API_GetRealplayUrl_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备直播的RTSP地址。
【使用appkey/secret签名认证】
 */

typedef struct GetRealplayUrlRequest 
{
	HsviewRequest base;

	struct GetRealplayUrlRequestData
	{
		
		/** [int] 0表示主码流，1表示辅码流 */
		int streamId;
		/** 通道号 */
		CSTR channelId;
		/** 需要操作的用户的accessToken */
		CSTR accessToken;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetRealplayUrlRequest;

C_API GetRealplayUrlRequest *HSAPI_INIT(GetRealplayUrlRequest);

typedef struct GetRealplayUrlResponse 
{
	HsviewResponse base;

	struct GetRealplayUrlResponseData
	{
		
		/** 返回的rtsp地址 */
		CSTR resource;
 
	} data;

} GetRealplayUrlResponse;

C_API GetRealplayUrlResponse *HSAPI_INIT(GetRealplayUrlResponse);

#endif
