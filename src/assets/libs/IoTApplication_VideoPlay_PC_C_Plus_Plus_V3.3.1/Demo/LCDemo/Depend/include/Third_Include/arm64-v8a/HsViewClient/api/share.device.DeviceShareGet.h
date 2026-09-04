/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_shareDevice_DeviceShareGet_H_
#define _HSVIEW_CLIENT_API_shareDevice_DeviceShareGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取某个设备某个通道的分享信息，不包括授权。
老的device.share.DeviceShareGet废弃

friendAlias是可选字段，乐橙基线才会返回，其他的不会返回相关字段，海外也不会有该字段
【使用平台账号签名】
 */

typedef struct shareDevice_DeviceShareGetRequest 
{
	HsviewRequest base;

	struct shareDevice_DeviceShareGetRequestData
	{
		
		/** [O]通道号，海外分享是按照设备级别的，所以通道号不需要 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} shareDevice_DeviceShareGetRequest;

C_API shareDevice_DeviceShareGetRequest *HSAPI_INIT(shareDevice_DeviceShareGetRequest);

typedef struct shareDevice_DeviceShareGetResponse 
{
	HsviewResponse base;

	struct shareDevice_DeviceShareGetResponseData
	{
		
		/** define a list with struct of shareDevice_DeviceShareGetResponseData_ShareInfosElement */
		DECLARE_LIST(struct shareDevice_DeviceShareGetResponseData_ShareInfosElement
		{
			/** [O]被分享者的昵称 */
			CSTR nickname;
			/** [O]好友别名 */
			CSTR friendAlias;
			/** [O]分享的功能，可选项见说明，用逗号分隔 */
			CSTR functions;
			/** [O]被分享者的账号的哈希值，被邀请但未注册的用户返回该字段，用于取消用户邀请时传参 */
			CSTR accountHash;
			/** [O]被分享者的用户id */
			CSTR userId;
			/** [O]被分享者的头像URL */
			CSTR userIcon;
			/** 被分享者的账号状态，registered-账号已经注册，unregistered-账号未注册 */
			CSTR accountStatus;
			/** [O]分享的备注，可选项，海外SMB需求 */
			CSTR remark;
			/** [O]分享时间，UNIX时间戳（秒） */
			CSTR shareTime;
			/** 被分享者的账号 */
			CSTR account;
		}) shareInfos;
		/** [O]套餐结束时间时间，yyyyMMddTHHmmssZ格式，套餐到期后为空 */
		CSTR endTime;
		/** [O]允许分享数量, 999表示不限制,999表示为vip */
		CSTR allowShareCount;
		/** [O] [long] 套餐剩余时长  */
		CSTR leftDays;
		/** [O]分享次数，设备或者通道目前分享出去了多少次 */
		CSTR shareCount;
		/** [O]分享者的账号 */
		CSTR ownerAccount;
		/** [O]剩余分享和授权的数量 */
		CSTR leftShareCount;
		/** [O]套餐开始时间，yyyyMMddTHHmmssZ格式，套餐到期后为空 */
		CSTR beginTime;
		/** [O]设备通道默认分享授权数 */
		CSTR defaultNum;
 
	} data;

} shareDevice_DeviceShareGetResponse;

C_API shareDevice_DeviceShareGetResponse *HSAPI_INIT(shareDevice_DeviceShareGetResponse);

#endif
