/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceShare_DeviceShareGet_H_
#define _HSVIEW_CLIENT_API_deviceShare_DeviceShareGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取某个设备某个通道的分享信息，不包括授权。

friendAlias是可选字段，乐橙基线才会返回，其他的不会返回相关字段，海外也不会有该字段
【使用平台账号签名】
 */

typedef struct deviceShare_DeviceShareGetRequest 
{
	HsviewRequest base;

	struct deviceShare_DeviceShareGetRequestData
	{
		
		/** [O]通道号，海外分享是按照设备级别的，所以通道号不需要 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} deviceShare_DeviceShareGetRequest;

C_API deviceShare_DeviceShareGetRequest *HSAPI_INIT(deviceShare_DeviceShareGetRequest);

typedef struct deviceShare_DeviceShareGetResponse 
{
	HsviewResponse base;

	struct deviceShare_DeviceShareGetResponseData
	{
		
		/** [O]分享次数，设备或者通道目前分享出去了多少次 */
		CSTR shareCount;
		/** define a list with struct of deviceShare_DeviceShareGetResponseData_ShareInfosElement */
		DECLARE_LIST(struct deviceShare_DeviceShareGetResponseData_ShareInfosElement
		{
			/** [O]被分享者的头像URL */
			CSTR userIcon;
			/** [O]好友别名 */
			CSTR friendAlias;
			/** [O]分享的功能，可选项见说明，用逗号分隔 */
			CSTR functions;
			/** [O]分享时间，UNIX时间戳（秒） */
			CSTR shareTime;
			/** [O]被分享者的昵称 */
			CSTR nickname;
			/** [O]被分享者的用户id */
			CSTR userId;
			/** 被分享者的账号 */
			CSTR account;
		}) shareInfos;
		/** [O]剩余分享和授权的数量 */
		CSTR leftShareCount;
		/** [O]允许分享数量, 999表示不限制,999表示为vip */
		CSTR allowShareCount;
		/** [O]设备通道默认分享授权数 */
		CSTR defaultNum;
 
	} data;

} deviceShare_DeviceShareGetResponse;

C_API deviceShare_DeviceShareGetResponse *HSAPI_INIT(deviceShare_DeviceShareGetResponse);

#endif
