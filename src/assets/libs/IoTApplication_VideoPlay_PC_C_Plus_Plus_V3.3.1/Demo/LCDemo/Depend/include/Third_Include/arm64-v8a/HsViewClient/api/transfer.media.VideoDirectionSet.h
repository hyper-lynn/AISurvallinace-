/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferMedia_VideoDirectionSet_H_
#define _HSVIEW_CLIENT_API_transferMedia_VideoDirectionSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取视频翻转状态
>    请求参数说明
 + direction：[string],画面方向。
    - normal-正常
    - reverse-颠倒
回复内容
参考PaaS协议：[获取视频翻转状态](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%A7%86%E9%A2%91%E7%9B%B8%E5%85%B3%E5%8F%82%E6%95%B0%2F%E8%AE%BE%E7%BD%AE%E8%A7%86%E9%A2%91%E7%BF%BB%E8%BD%AC%E7%8A%B6%E6%80%81.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferMedia_VideoDirectionSetRequest 
{
	HsviewRequest base;

	struct transferMedia_VideoDirectionSetRequestData
	{
		
		/** 设备通道号 */
		CSTR channelId;
		/** [cstr]/device/video/direction/config/ */
		#define _STATIC_transferMedia_VideoDirectionSetRequestData_url "/device/video/direction/config/"
		CSTR url;
		/** struct of transferMedia_VideoDirectionSetRequestData_Content */
		struct transferMedia_VideoDirectionSetRequestData_Content {
			/** reverse */
			CSTR direction;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferMedia_VideoDirectionSetRequest;

C_API transferMedia_VideoDirectionSetRequest *HSAPI_INIT(transferMedia_VideoDirectionSetRequest);

typedef struct transferMedia_VideoDirectionSetResponse 
{
	HsviewResponse base;

	struct transferMedia_VideoDirectionSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferMedia_VideoDirectionSetResponse;

C_API transferMedia_VideoDirectionSetResponse *HSAPI_INIT(transferMedia_VideoDirectionSetResponse);

#endif
