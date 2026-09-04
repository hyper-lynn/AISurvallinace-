/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_shareDevice_DeviceShareAuthListGet_H_
#define _HSVIEW_CLIENT_API_shareDevice_DeviceShareAuthListGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取批量设备的通道分享信息

注：若设备有通道被授权分享或者购买过分享套餐，则会返回在channels列表中；
不在列表中的设备通道 允许和剩余数量为默认分享授权数；
infoList如果没有分享则为空数组

【使用平台账号签名】
 */

typedef struct shareDevice_DeviceShareAuthListGetRequest 
{
	HsviewRequest base;

	struct shareDevice_DeviceShareAuthListGetRequestData
	{
		
		/** 设备序列号 */
		DECLARE_LIST(CSTR) devices;

	} data;

} shareDevice_DeviceShareAuthListGetRequest;

C_API shareDevice_DeviceShareAuthListGetRequest *HSAPI_INIT(shareDevice_DeviceShareAuthListGetRequest);

typedef struct shareDevice_DeviceShareAuthListGetResponse 
{
	HsviewResponse base;

	struct shareDevice_DeviceShareAuthListGetResponseData
	{
		
		/** define a list with struct of shareDevice_DeviceShareAuthListGetResponseData_ChannelsElement */
		DECLARE_LIST(struct shareDevice_DeviceShareAuthListGetResponseData_ChannelsElement
		{
			/** define a list with struct of shareDevice_DeviceShareAuthListGetResponseData_ChannelsElement_InfoListElement */
			DECLARE_LIST(struct shareDevice_DeviceShareAuthListGetResponseData_ChannelsElement_InfoListElement
			{
				/** [long]被分享者的用户ID */
				int64 userId;
				/** 分享的权限 */
				CSTR shareFunction;
			}) infoList;
			/** [long]被分享者的用户ID */
			DECLARE_LIST(int64) shareUserIds;
			/** [long]被授权者的用户ID */
			DECLARE_LIST(int64) authUserIds;
			/** 剩余分享和授权的数量 */
			CSTR leftShareCount;
			/** 通道号 */
			CSTR channelId;
			/** 允许分享数量, 最大为999 */
			CSTR allowShareCount;
			/** 设备ID */
			CSTR deviceId;
		}) channels;
		/** [int]设备通道默认分享授权数 */
		int defaultNum;
 
	} data;

} shareDevice_DeviceShareAuthListGetResponse;

C_API shareDevice_DeviceShareAuthListGetResponse *HSAPI_INIT(shareDevice_DeviceShareAuthListGetResponse);

#endif
