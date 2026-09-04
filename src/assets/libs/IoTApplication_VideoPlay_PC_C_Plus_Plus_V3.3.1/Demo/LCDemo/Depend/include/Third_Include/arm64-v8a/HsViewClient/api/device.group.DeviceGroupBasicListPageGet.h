/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceGroup_DeviceGroupBasicListPageGet_H_
#define _HSVIEW_CLIENT_API_deviceGroup_DeviceGroupBasicListPageGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
分页获取该分组下子分组信息以及设备和通道基本信息。
  
【需要使用平台账号签名】
 */

typedef struct deviceGroup_DeviceGroupBasicListPageGetRequest 
{
	HsviewRequest base;

	struct deviceGroup_DeviceGroupBasicListPageGetRequestData
	{
		
		/** [int]条数,最大128 */
		int limit;
		/** [long]上次查询到最后一个设备分组的id, 为-1表示从最新获取 */
		int64 groupId;

	} data;

} deviceGroup_DeviceGroupBasicListPageGetRequest;

C_API deviceGroup_DeviceGroupBasicListPageGetRequest *HSAPI_INIT(deviceGroup_DeviceGroupBasicListPageGetRequest);

typedef struct deviceGroup_DeviceGroupBasicListPageGetResponse 
{
	HsviewResponse base;

	struct deviceGroup_DeviceGroupBasicListPageGetResponseData
	{
		
		/** define a list with struct of deviceGroup_DeviceGroupBasicListPageGetResponseData_GroupListElement */
		DECLARE_LIST(struct deviceGroup_DeviceGroupBasicListPageGetResponseData_GroupListElement
		{
			/** [long]上层的组id，第一层级的时候这个字段值默认为0 */
			int64 parentGroupId;
			/** define a list with struct of deviceGroup_DeviceGroupBasicListPageGetResponseData_GroupListElement_ChannelListElement */
			DECLARE_LIST(struct deviceGroup_DeviceGroupBasicListPageGetResponseData_GroupListElement_ChannelListElement
			{
				/** [long]上层的组id，第一层级的时候这个字段值默认为0 */
				int64 parentGroupId;
				/** [long]分组id */
				int64 groupId;
				/** 通道号 */
				CSTR channelId;
				/** [int]可选，国内必须，设备归属属性  0：自己的设备，1：他人分享，2：他人授权，3：他人分享+授权 */
				int belong;
				/** 设备序列号 */
				CSTR deviceId;
			}) channelList;
			/** [long]分组id */
			int64 groupId;
			/** 分组名称 */
			CSTR groupName;
			/** define a list with struct of deviceGroup_DeviceGroupBasicListPageGetResponseData_GroupListElement_ApListElement */
			DECLARE_LIST(struct deviceGroup_DeviceGroupBasicListPageGetResponseData_GroupListElement_ApListElement
			{
				/** [long]上层的组id，第一层级的时候这个字段值默认为0 */
				int64 parentGroupId;
				/** 配件号 */
				CSTR apId;
				/** [long]分组id */
				int64 groupId;
				/** [int]可选，国内必须，设备归属属性  0：自己的设备，1：他人分享 */
				int belong;
				/** 设备序列号 */
				CSTR deviceId;
			}) apList;
		}) groupList;
 
	} data;

} deviceGroup_DeviceGroupBasicListPageGetResponse;

C_API deviceGroup_DeviceGroupBasicListPageGetResponse *HSAPI_INIT(deviceGroup_DeviceGroupBasicListPageGetResponse);

#endif
