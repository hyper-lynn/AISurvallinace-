/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetPushConfig_H_
#define _HSVIEW_CLIENT_API_GetPushConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户将自己的手机信息添加到自身账号下。
【使用平台账号签名】
 */

typedef struct GetPushConfigRequest 
{
	HsviewRequest base;

	struct GetPushConfigRequestData
	{
		
		/** 推送账号ID */
		CSTR appId;

	} data;

} GetPushConfigRequest;

C_API GetPushConfigRequest *HSAPI_INIT(GetPushConfigRequest);

typedef struct GetPushConfigResponse 
{
	HsviewResponse base;

	struct GetPushConfigResponseData
	{
		
		/** 推送类型：'IOS_APNS' or 'ANDROID_JPUSH' or 'ANDROID_GCM' or 'ANDROID_DH' */
		CSTR pushType;
		/** [int]是否订阅消息，1订阅，0不订阅 */
		int status;
		/** 提示音，填文件名或id */
		CSTR sound;
		/** 语言类型：'zh_CN' or 'en_US' */
		CSTR language;
		/** 日期格式，如“yyyy-MM-dd HH:mm:SS” */
		CSTR timeFormat;
 
	} data;

} GetPushConfigResponse;

C_API GetPushConfigResponse *HSAPI_INIT(GetPushConfigResponse);

#endif
