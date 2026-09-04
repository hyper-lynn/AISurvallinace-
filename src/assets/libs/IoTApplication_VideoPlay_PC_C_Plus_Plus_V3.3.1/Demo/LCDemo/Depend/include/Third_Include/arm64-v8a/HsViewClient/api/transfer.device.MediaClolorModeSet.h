/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_MediaClolorModeSet_H_
#define _HSVIEW_CLIENT_API_transferDevice_MediaClolorModeSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置画面颜色模式---仅支持lorex定制协议

请求参数说明
status:[string], 画面颜色模式，有三种：
Color：总是彩色；
BlackWhite：总是黑白；
Brightness：根据亮度自动切换；

参考PaaS协议：[设置画面颜色模式](http://paas.dahuatech.com/wiki/?p=%2F%E5%AE%9A%E5%88%B6%E5%AE%A2%E6%88%B7%2Florex%2F%E8%AE%BE%E7%BD%AE%E7%94%BB%E9%9D%A2%E9%A2%9C%E8%89%B2%E6%A8%A1%E5%BC%8F.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_MediaClolorModeSetRequest 
{
	HsviewRequest base;

	struct transferDevice_MediaClolorModeSetRequestData
	{
		
		/** [cstr]/device/night/vision/config */
		#define _STATIC_transferDevice_MediaClolorModeSetRequestData_url "/device/night/vision/config"
		CSTR url;
		/** struct of transferDevice_MediaClolorModeSetRequestData_Content */
		struct transferDevice_MediaClolorModeSetRequestData_Content {
			/** 画面颜色模式 */
			CSTR status;
			/** 通道号 */
			CSTR channelId;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_MediaClolorModeSetRequest;

C_API transferDevice_MediaClolorModeSetRequest *HSAPI_INIT(transferDevice_MediaClolorModeSetRequest);

typedef struct transferDevice_MediaClolorModeSetResponse 
{
	HsviewResponse base;

	struct transferDevice_MediaClolorModeSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_MediaClolorModeSetResponse;

C_API transferDevice_MediaClolorModeSetResponse *HSAPI_INIT(transferDevice_MediaClolorModeSetResponse);

#endif
