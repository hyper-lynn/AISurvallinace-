/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceGroup_BatchMoveGroupDevice_H_
#define _HSVIEW_CLIENT_API_deviceGroup_BatchMoveGroupDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
批量移动不同分组中的多个通道到某个分组中

注：
无通道的设备channelId传 -1

【需要使用平台账号签名】
 */

typedef struct deviceGroup_BatchMoveGroupDeviceRequest 
{
	HsviewRequest base;

	struct deviceGroup_BatchMoveGroupDeviceRequestData
	{
		
		/** [long]目标分组id */
		int64 destGroupId;
		/** define a list with struct of deviceGroup_BatchMoveGroupDeviceRequestData_ListElement */
		DECLARE_LIST(struct deviceGroup_BatchMoveGroupDeviceRequestData_ListElement
		{
			/** define a list with struct of deviceGroup_BatchMoveGroupDeviceRequestData_ListElement_ApListElement */
			DECLARE_LIST(struct deviceGroup_BatchMoveGroupDeviceRequestData_ListElement_ApListElement
			{
				/** 配件id */
				CSTR apId;
				/** [int]可选，国内必须，设备归属属性  0：自己的设备，1：他人分享 */
				int belong;
				/** 设备序列号 */
				CSTR deviceId;
			}) apList;
			/** define a list with struct of deviceGroup_BatchMoveGroupDeviceRequestData_ListElement_ChannelListElement */
			DECLARE_LIST(struct deviceGroup_BatchMoveGroupDeviceRequestData_ListElement_ChannelListElement
			{
				/** 通道号 */
				CSTR channelId;
				/** [int]可选，国内必须，设备归属属性  0：自己的设备，1：他人分享，2：他人授权 */
				int belong;
				/** 设备序列号 */
				CSTR deviceId;
			}) channelList;
			/** [long]分组id */
			int64 groupId;
		}) list;

	} data;

} deviceGroup_BatchMoveGroupDeviceRequest;

C_API deviceGroup_BatchMoveGroupDeviceRequest *HSAPI_INIT(deviceGroup_BatchMoveGroupDeviceRequest);

typedef struct deviceGroup_BatchMoveGroupDeviceResponse 
{
	HsviewResponse base;

	struct deviceGroup_BatchMoveGroupDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceGroup_BatchMoveGroupDeviceResponse;

C_API deviceGroup_BatchMoveGroupDeviceResponse *HSAPI_INIT(deviceGroup_BatchMoveGroupDeviceResponse);

#endif
