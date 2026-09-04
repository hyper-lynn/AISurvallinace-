/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetTouristModePushConfig_H_
#define _HSVIEW_CLIENT_API_SetTouristModePushConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户第一次下载APP后，未登录，处于游客模式下才进行推送的设置。
只设置这一次，后面用户登录成功再退出登录，也不能进行设置。

【不鉴权】
 */

typedef struct SetTouristModePushConfigRequest 
{
	HsviewRequest base;

	struct SetTouristModePushConfigRequestData
	{
		
		/** 日期格式，如“yyyy-MM-dd HH:mm:SS” */
		CSTR timeFormat;
		/** 推送类型：'IOS_APNS' or 'ANDROID_JPUSH' or 'ANDROID_GCM' or 'ANDROID_DH' */
		CSTR pushType;
		/** 语言类型：'zh_CN' or 'en_US' */
		CSTR language;
		/** 推送账号ID */
		CSTR appId;

	} data;

} SetTouristModePushConfigRequest;

C_API SetTouristModePushConfigRequest *HSAPI_INIT(SetTouristModePushConfigRequest);

typedef struct SetTouristModePushConfigResponse 
{
	HsviewResponse base;

	struct SetTouristModePushConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetTouristModePushConfigResponse;

C_API SetTouristModePushConfigResponse *HSAPI_INIT(SetTouristModePushConfigResponse);

#endif
