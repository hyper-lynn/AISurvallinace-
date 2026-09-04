/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetDeviceShare_H_
#define _HSVIEW_CLIENT_API_GetDeviceShare_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取某个设备某个通道的分享信息，不包括授权。

friendInfo是可选字段，乐橙基线才会返回，其他的不会返回相关字段。
【使用平台账号签名】
 */

typedef struct GetDeviceShareRequest 
{
	HsviewRequest base;

	struct GetDeviceShareRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetDeviceShareRequest;

C_API GetDeviceShareRequest *HSAPI_INIT(GetDeviceShareRequest);

typedef struct GetDeviceShareResponse 
{
	HsviewResponse base;

	struct GetDeviceShareResponseData
	{
		
		/** define a list with struct of GetDeviceShareResponseData_ShareInfosElement */
		DECLARE_LIST(struct GetDeviceShareResponseData_ShareInfosElement
		{
			/** 被分享者的用户名 */
			CSTR username;
			/** 被分享者的头像URL */
			CSTR userIcon;
			/** [long]分享时间，UNIX时间戳（秒） */
			int64 shareTime;
			/** 分享的功能，可选项见说明，用逗号分隔 */
			CSTR functions;
			/** 被分享者的手机号码 */
			CSTR phoneNumber;
			/** struct of GetDeviceShareResponseData_ShareInfosElement_FriendInfo */
			struct GetDeviceShareResponseData_ShareInfosElement_FriendInfo {
				/** 好友别名 */
				CSTR alias;
			} friendInfo;
			/** 被分享者的昵称 */
			CSTR nickname;
			/** 被分享者的邮箱号 */
			CSTR email;
		}) shareInfos;
		/** [int]剩余分享和授权的数量 */
		int leftShareCount;
		/** 拥有者的用户名 */
		CSTR owner;
		/** [int]允许分享数量, 999表示不限制,999表示为vip */
		int allowShareCount;
		/** [int]设备通道默认分享授权数 */
		int defaultNum;
 
	} data;

} GetDeviceShareResponse;

C_API GetDeviceShareResponse *HSAPI_INIT(GetDeviceShareResponse);

#endif
