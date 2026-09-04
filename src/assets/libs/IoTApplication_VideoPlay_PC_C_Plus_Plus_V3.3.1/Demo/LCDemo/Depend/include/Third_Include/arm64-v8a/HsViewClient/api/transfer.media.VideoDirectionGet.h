/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferMedia_VideoDirectionGet_H_
#define _HSVIEW_CLIENT_API_transferMedia_VideoDirectionGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取视频翻转状态
>    响应参数说明
 + direction：画面方向。
    - normal-正常
    - reverse-颠倒

参考PaaS协议：[获取视频翻转状态](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%A7%86%E9%A2%91%E7%9B%B8%E5%85%B3%E5%8F%82%E6%95%B0%2F%E8%8E%B7%E5%8F%96%E8%A7%86%E9%A2%91%E7%BF%BB%E8%BD%AC%E7%8A%B6%E6%80%81.md&s=pd)
【需要使用平台账号签名】
 */

typedef struct transferMedia_VideoDirectionGetRequest 
{
	HsviewRequest base;

	struct transferMedia_VideoDirectionGetRequestData
	{
		
		/** [cstr]/device/video/direction/query/ */
		#define _STATIC_transferMedia_VideoDirectionGetRequestData_url "/device/video/direction/query/"
		CSTR url;
		/** 设备通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferMedia_VideoDirectionGetRequest;

C_API transferMedia_VideoDirectionGetRequest *HSAPI_INIT(transferMedia_VideoDirectionGetRequest);

typedef struct transferMedia_VideoDirectionGetResponse 
{
	HsviewResponse base;

	struct transferMedia_VideoDirectionGetResponseData
	{
		
		/** 画面方向 */
		CSTR direction;
 
	} data;

} transferMedia_VideoDirectionGetResponse;

C_API transferMedia_VideoDirectionGetResponse *HSAPI_INIT(transferMedia_VideoDirectionGetResponse);

#endif
