/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetPublicLive_H_
#define _HSVIEW_CLIENT_API_SetPublicLive_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置摄像头公共视频属性。
若修改成非公共视频，则返回字段url和page都为空。

错误码：
1、1322 ：设备已经自定义加密密钥
【使用平台账号签名】
 */

typedef struct SetPublicLiveRequest 
{
	HsviewRequest base;

	struct SetPublicLiveRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** [long]公开到期时间，UNIX时间戳，单位秒。为0表示设置为非公共视频。 */
		int64 publicExpire;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetPublicLiveRequest;

C_API SetPublicLiveRequest *HSAPI_INIT(SetPublicLiveRequest);

typedef struct SetPublicLiveResponse 
{
	HsviewResponse base;

	struct SetPublicLiveResponseData
	{
		
		/** 直播流hls访问地址 */
		CSTR url;
		/** 直播网页http地址 */
		CSTR page;
		/** 公开视频的token，凭此token通过GetPublicLiveStream接口获取url和page */
		CSTR token;
 
	} data;

} SetPublicLiveResponse;

C_API SetPublicLiveResponse *HSAPI_INIT(SetPublicLiveResponse);

#endif
