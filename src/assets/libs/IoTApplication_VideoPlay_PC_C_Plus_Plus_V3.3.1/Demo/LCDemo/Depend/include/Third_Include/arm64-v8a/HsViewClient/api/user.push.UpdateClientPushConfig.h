/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userPush_UpdateClientPushConfig_H_
#define _HSVIEW_CLIENT_API_userPush_UpdateClientPushConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
在用户手动设置推送配置时，强制更新推送配置，覆盖平台上所有配置。

备注：手机需要在UpdateClientPushConfig前调用GetClientPushConfig接口。


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

typedef struct userPush_UpdateClientPushConfigRequest 
{
	HsviewRequest base;

	struct userPush_UpdateClientPushConfigRequestData
	{
		
		/** [int]手机所在时区的时间与零时区时间差值，单位为秒，可正负 */
		int timezoneOffset;
		/** 标识手机voip推送的唯一ID，用于推送 */
		CSTR clientPushIdVoip;
		/** 标识手机的唯一ID，用于推送 */
		CSTR clientPushId;
		/** 日期格式，如“yyyy-MM-dd HH:mm:SS” */
		CSTR timeFormat;
		/** 时间设定，如08:00-11:30，是手机本地时间，开始范围（00:00到23:59），结束范围（00:00到23:59） */
		DECLARE_LIST(CSTR) receiveTime;
		/** 推送账号key */
		CSTR appKey;
		/** [int]是否订阅消息，1订阅，0不订阅 */
		int status;
		/** 语言类型：'zh_CN'；'en_US' etc.详见下面描述说明 */
		CSTR language;
		/** IOS提示音，填文件名或id */
		CSTR sound;

	} data;

} userPush_UpdateClientPushConfigRequest;

C_API userPush_UpdateClientPushConfigRequest *HSAPI_INIT(userPush_UpdateClientPushConfigRequest);

typedef struct userPush_UpdateClientPushConfigResponse 
{
	HsviewResponse base;

	struct userPush_UpdateClientPushConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userPush_UpdateClientPushConfigResponse;

C_API userPush_UpdateClientPushConfigResponse *HSAPI_INIT(userPush_UpdateClientPushConfigResponse);

#endif
