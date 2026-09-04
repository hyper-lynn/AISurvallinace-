/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userPush_SetClientPushConfig_H_
#define _HSVIEW_CLIENT_API_userPush_SetClientPushConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
在客户端登录成功后调用，设置手机的推送配置。

备注：
1. 平台上不存在clientPushId的配置，那么生成一个新的配置记录，接收时间为24小时，订阅状态。
2. 平台上已经存在clientPushId的配置，那么使用本次上报信息覆盖平台上的language、和timezoneOffset，保留不覆盖平台原有的timeFormat、sound、status和receiveTime。


language格式定义及说明(http://www.lingoes.net/en/translator/langcode.htm)：
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

typedef struct userPush_SetClientPushConfigRequest 
{
	HsviewRequest base;

	struct userPush_SetClientPushConfigRequestData
	{
		
		/** [int]手机所在时区的时间与零时区时间差值，单位为秒，可正负 */
		int timezoneOffset;
		/** [O] 海外需要该字段，系统推送支持的方式，推送方式后续增加值为2^n， 1-phoneid方式推送， 2-topic方式推送。没有默认为topic推送 */
		CSTR systemPushType;
		/** 推送账号key */
		CSTR appKey;
		/** 标识手机voip推送的唯一ID，用于推送 */
		CSTR clientPushIdVoip;
		/** [O]IOS提示音，填文件名或id */
		CSTR sound;
		/** 标识手机的唯一ID，用于推送 */
		CSTR clientPushId;
		/** 语言类型：'zh_CN'；'en_US' etc.详见下面描述说明 */
		CSTR language;
		/** 日期格式，如“yyyy-MM-dd HH:mm:SS” */
		CSTR timeFormat;

	} data;

} userPush_SetClientPushConfigRequest;

C_API userPush_SetClientPushConfigRequest *HSAPI_INIT(userPush_SetClientPushConfigRequest);

typedef struct userPush_SetClientPushConfigResponse 
{
	HsviewResponse base;

	struct userPush_SetClientPushConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userPush_SetClientPushConfigResponse;

C_API userPush_SetClientPushConfigResponse *HSAPI_INIT(userPush_SetClientPushConfigResponse);

#endif
