/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetPushConfig_H_
#define _HSVIEW_CLIENT_API_SetPushConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户将自己的手机信息添加到自身账号下。
【使用平台账号签名】
 */

typedef struct SetPushConfigRequest 
{
	HsviewRequest base;

	struct SetPushConfigRequestData
	{
		
		/** 日期格式，如“yyyy-MM-dd HH:mm:SS” */
		CSTR timeFormat;
		/** 提示音，填文件名或id */
		CSTR sound;
		/** 推送账号ID */
		CSTR appId;
		/** [int]是否订阅消息，1订阅，0不订阅 */
		int status;
		/** [O]标识手机的唯一ID，用于推送。该字段已废弃。 */
		CSTR clientPushId;
		/** 语言类型：'zh_CN' or 'en_US' */
		CSTR language;
		/** 推送类型：'IOS_APNS' or 'ANDROID_JPUSH' or 'ANDROID_GCM' or 'ANDROID_DH' */
		CSTR pushType;

	} data;

} SetPushConfigRequest;

C_API SetPushConfigRequest *HSAPI_INIT(SetPushConfigRequest);

typedef struct SetPushConfigResponse 
{
	HsviewResponse base;

	struct SetPushConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetPushConfigResponse;

C_API SetPushConfigResponse *HSAPI_INIT(SetPushConfigResponse);

#endif
