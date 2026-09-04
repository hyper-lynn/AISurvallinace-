/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_shareDevice_BeSharedPageListGet_H_
#define _HSVIEW_CLIENT_API_shareDevice_BeSharedPageListGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取被别人的分享或者授权的设备列表(配件分享信息可选)。

回复字段如下：
deviceId：设备ID
baseline：设备基线类型，详见设备Baseline类型
deviceModel:设备型号
name：设备名称
ability：设备能力选项列表，详见设备能力集选项
设备的视频通道，其中：
id：通道号
channelName：通道名称
ability 通道能力项列表

如果是配件分享，channels为空；如果是设备分享，apList为空；如果既有配件分享，又有设备分享，拆分为一个配件分享，一个设备分享
【需要使用平台账号签名】

 */

typedef struct shareDevice_BeSharedPageListGetRequest 
{
	HsviewRequest base;

	struct shareDevice_BeSharedPageListGetRequestData
	{
		
		/** 设备拥有者用户id，TA分享给我,TA的用户id */
		CSTR ownerId;
		/** [long]上次查询最后一个绑定分享表id，为-1表示从最后一个开始获取 */
		int64 bindId;
		/** [int]条数,最大128 */
		int limit;
		/** [bool]是否需要配件列表信息, false:表示不需要, true表示需要 */
		BOOL needApInfo;

	} data;

} shareDevice_BeSharedPageListGetRequest;

C_API shareDevice_BeSharedPageListGetRequest *HSAPI_INIT(shareDevice_BeSharedPageListGetRequest);

typedef struct shareDevice_BeSharedPageListGetResponse 
{
	HsviewResponse base;

	struct shareDevice_BeSharedPageListGetResponseData
	{
		
		/** define a list with struct of shareDevice_BeSharedPageListGetResponseData_DeviceListElement */
		DECLARE_LIST(struct shareDevice_BeSharedPageListGetResponseData_DeviceListElement
		{
			/** [O]通道总数 */
			CSTR channelNum;
			/** define a list with struct of shareDevice_BeSharedPageListGetResponseData_DeviceListElement_AplistElement */
			DECLARE_LIST(struct shareDevice_BeSharedPageListGetResponseData_DeviceListElement_AplistElement
			{
				/** [O]配件id */
				CSTR apId;
				/** [O]配件能力集，逗号隔开 */
				CSTR apCapacity;
				/** [O]配件的型号 */
				CSTR apModel;
				/** [O]配件名称 */
				CSTR apName;
				/** [O]配件的使能:on-使能开启 ，off-使能关闭 */
				CSTR apEnable;
				/** [O]配件的类型 */
				CSTR apType;
				/** [int][O]配件的在线状态：1-在线  0-离线 */
				int apStatus;
				/** [O]分享和授权的权限功能列表（逗号隔开） */
				CSTR shareFunctions;
				/** [O]配件的版本号 */
				CSTR apVersion;
			}) aplist;
			/** 设备名称 */
			CSTR name;
			/** define a list with struct of shareDevice_BeSharedPageListGetResponseData_DeviceListElement_ChannelsElement */
			DECLARE_LIST(struct shareDevice_BeSharedPageListGetResponseData_DeviceListElement_ChannelsElement
			{
				/** 通道名称 */
				CSTR channelName;
				/** [O]分享和授权的权限功能列表（逗号隔开）（saas）,shareStatus字段为share，auth，shareAndAuth时关注该字段的值 */
				CSTR shareFunctions;
				/** 远程通道状态 online-在线 offline-在线 close-未配置 */
				CSTR status;
				/** 通道号 */
				CSTR channelId;
				/** [O]绑定状态 share-别人分享 auth-别人授权 shareAndAuth-别人分享和授权（saas）,该字段没有或者为空的时候表示自己绑定设备的通道 */
				CSTR shareStatus;
				/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
				CSTR ability;
			}) channels;
			/** [O]设备型号 */
			CSTR deviceModel;
			/** [long]绑定分享表自增id */
			int64 bindId;
			/** define a list with struct of shareDevice_BeSharedPageListGetResponseData_DeviceListElement_ApListElement */
			DECLARE_LIST(struct shareDevice_BeSharedPageListGetResponseData_DeviceListElement_ApListElement
			{
				/** [O]配件id */
				CSTR apId;
				/** [O]配件能力集，逗号隔开 */
				CSTR apCapacity;
				/** [O]配件的型号 */
				CSTR apModel;
				/** [O]配件名称 */
				CSTR apName;
				/** [O]配件的使能:on-使能开启 ，off-使能关闭 */
				CSTR apEnable;
				/** [O]配件的类型 */
				CSTR apType;
				/** [int][O]配件的在线状态：1-在线  0-离线 */
				int apStatus;
				/** [O]分享和授权的权限功能列表（逗号隔开） */
				CSTR shareFunctions;
				/** [O]配件的版本号 */
				CSTR apVersion;
			}) apList;
			/** 设备ID */
			CSTR deviceId;
		}) deviceList;
 
	} data;

} shareDevice_BeSharedPageListGetResponse;

C_API shareDevice_BeSharedPageListGetResponse *HSAPI_INIT(shareDevice_BeSharedPageListGetResponse);

#endif
