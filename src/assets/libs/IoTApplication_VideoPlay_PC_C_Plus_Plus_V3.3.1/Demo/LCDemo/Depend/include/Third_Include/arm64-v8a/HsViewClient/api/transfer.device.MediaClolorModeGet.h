/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_MediaClolorModeGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_MediaClolorModeGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取画面颜色模式---仅支持lorex定制协议

响应参数说明
status:[string], 画面颜色模式，有三种：
Color：总是彩色；
BlackWhite：总是黑白；
Brightness：根据亮度自动切换；

参考PaaS协议：[获取画面颜色模式](http://paas.dahuatech.com/wiki/?p=%2F%E5%AE%9A%E5%88%B6%E5%AE%A2%E6%88%B7%2Florex%2F%E8%8E%B7%E5%8F%96%E7%94%BB%E9%9D%A2%E9%A2%9C%E8%89%B2%E6%A8%A1%E5%BC%8F.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_MediaClolorModeGetRequest 
{
	HsviewRequest base;

	struct transferDevice_MediaClolorModeGetRequestData
	{
		
		/** [cstr]/device/night/vision/query */
		#define _STATIC_transferDevice_MediaClolorModeGetRequestData_url "/device/night/vision/query"
		CSTR url;
		/** struct of transferDevice_MediaClolorModeGetRequestData_Content */
		struct transferDevice_MediaClolorModeGetRequestData_Content {
			/** 通道号 */
			CSTR channelId;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_MediaClolorModeGetRequest;

C_API transferDevice_MediaClolorModeGetRequest *HSAPI_INIT(transferDevice_MediaClolorModeGetRequest);

typedef struct transferDevice_MediaClolorModeGetResponse 
{
	HsviewResponse base;

	struct transferDevice_MediaClolorModeGetResponseData
	{
		
		/** 画面颜色模式 */
		CSTR status;
 
	} data;

} transferDevice_MediaClolorModeGetResponse;

C_API transferDevice_MediaClolorModeGetResponse *HSAPI_INIT(transferDevice_MediaClolorModeGetResponse);

#endif
