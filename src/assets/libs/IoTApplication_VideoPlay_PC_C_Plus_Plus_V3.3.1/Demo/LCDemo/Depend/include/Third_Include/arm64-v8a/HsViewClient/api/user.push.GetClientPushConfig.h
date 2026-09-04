/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userPush_GetClientPushConfig_H_
#define _HSVIEW_CLIENT_API_userPush_GetClientPushConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取推送配置信息。

language格式定义及说明：
1、格式：
	language_region(或者language-region)
	语言文字种类_国家和地区
2、说明：
	语言文字种类:按ISO 639-1  标准(2字节)
	国家和地区:  按ISO 3166-1 标准(2字节)
3、eg.
	zh_CN或者zh-CN
	en_US或者en-US 
【使用平台账号签名】
 */

typedef struct userPush_GetClientPushConfigRequest 
{
	HsviewRequest base;

	struct userPush_GetClientPushConfigRequestData
	{
		
		/** 推送账号key */
		CSTR appKey;
		/** 标识手机的唯一ID，用于推送 */
		CSTR clientPushId;

	} data;

} userPush_GetClientPushConfigRequest;

C_API userPush_GetClientPushConfigRequest *HSAPI_INIT(userPush_GetClientPushConfigRequest);

typedef struct userPush_GetClientPushConfigResponse 
{
	HsviewResponse base;

	struct userPush_GetClientPushConfigResponseData
	{
		
		/** [int]手机所在时区与零时区差值，单位为秒，可正负 */
		int timezoneOffset;
		/** [O]语言类型：'zh_CN'；'en_US' etc.详见下面描述说明 */
		CSTR language;
		/** [int]是否订阅消息，1订阅，0不订阅 */
		int status;
		/** [O]提示音，填文件名或id */
		CSTR sound;
		/** [O]日期格式，如“yyyy-MM-dd HH:mm:SS” */
		CSTR timeFormat;
		/** 时间设定，如08:00-11:30，是手机本地时间，开始范围（00:00到23:59），结束范围（00:00到23:59） */
		DECLARE_LIST(CSTR) receiveTime;
 
	} data;

} userPush_GetClientPushConfigResponse;

C_API userPush_GetClientPushConfigResponse *HSAPI_INIT(userPush_GetClientPushConfigResponse);

#endif
