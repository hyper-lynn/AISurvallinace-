/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetDeviceSharePlus_H_
#define _HSVIEW_CLIENT_API_GetDeviceSharePlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取某个设备某个通道的分享信息，不包括授权。

friendInfo是可选字段，乐橙基线才会返回，其他的不会返回相关字段。
【使用平台账号签名】
 */

typedef struct GetDeviceSharePlusRequest 
{
	HsviewRequest base;

	struct GetDeviceSharePlusRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetDeviceSharePlusRequest;

C_API GetDeviceSharePlusRequest *HSAPI_INIT(GetDeviceSharePlusRequest);

typedef struct GetDeviceSharePlusResponse 
{
	HsviewResponse base;

	struct GetDeviceSharePlusResponseData
	{
		
		/** define a list with struct of GetDeviceSharePlusResponseData_ShareInfosElement */
		DECLARE_LIST(struct GetDeviceSharePlusResponseData_ShareInfosElement
		{
			/** 被分享者的头像URL */
			CSTR userIcon;
			/** 分享的功能，可选项见说明，用逗号分隔 */
			CSTR functions;
			/** 被分享者的昵称 */
			CSTR nickname;
			/** struct of GetDeviceSharePlusResponseData_ShareInfosElement_FriendInfo */
			struct GetDeviceSharePlusResponseData_ShareInfosElement_FriendInfo {
				/** 好友别名 */
				CSTR alias;
			} friendInfo;
			/** 被分享者的用户ID */
			CSTR userId;
			/** [long]分享时间，UNIX时间戳（秒） */
			int64 shareTime;
		}) shareInfos;
		/** [int]剩余分享和授权的数量 */
		int leftShareCount;
		/** [int]允许分享数量, 999表示不限制,999表示为vip */
		int allowShareCount;
		/** [int]设备通道默认分享授权数 */
		int defaultNum;
 
	} data;

} GetDeviceSharePlusResponse;

C_API GetDeviceSharePlusResponse *HSAPI_INIT(GetDeviceSharePlusResponse);

#endif
