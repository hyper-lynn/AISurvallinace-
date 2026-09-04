/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceBaseDetailList_H_
#define _LC_OPENAPI_CLIENT_DeviceBaseDetailList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备列表获取

 */

typedef struct DeviceBaseDetailListRequest 
{
	LCOpenApiRequest base;

	struct DeviceBaseDetailListRequestData
	{
		
		/** define a list with struct of DeviceBaseDetailListRequestData_DeviceListElement */
		DECLARE_LIST(struct DeviceBaseDetailListRequestData_DeviceListElement
		{
			/** 批量配件Id */
			CSTR apList;
			/** 批量通道号 */
			CSTR channelList;
			/** 设备序列号 */
			CSTR deviceId;
		}) deviceList;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** [cstr]deviceBaseDetailList */
		#define _STATIC_DeviceBaseDetailListRequestData_method "deviceBaseDetailList"
		CSTR method;

	} data;

} DeviceBaseDetailListRequest;

C_API DeviceBaseDetailListRequest *LCOPENAPI_INIT(DeviceBaseDetailListRequest);

typedef struct DeviceBaseDetailListResponse 
{
	LCOpenApiResponse base;

	struct DeviceBaseDetailListResponseData
	{
		
		/** [int]当前获取的设备总数 */
		int count;
		/** define a list with struct of DeviceBaseDetailListResponseData_DeviceListElement */
		DECLARE_LIST(struct DeviceBaseDetailListResponseData_DeviceListElement
		{
			/** 设备品牌信息：lechange-乐橙设备，general-通用设备 */
			CSTR brand;
			/** 设备大类 */
			CSTR catalog;
			/** define a list with struct of DeviceBaseDetailListResponseData_DeviceListElement_ChannelsElement */
			DECLARE_LIST(struct DeviceBaseDetailListResponseData_DeviceListElement_ChannelsElement
			{
				/** 云存储状态 notExist:未开通套餐，using：开通云存储且没有过期， expired：套餐过期 */
				CSTR storageStrategyStatus;
				/** 缩略图URL */
				CSTR picUrl;
				/** 通道能力集 如AlarmMD,AudioTalk 逗号隔开 */
				CSTR ability;
				/** 设备序列号 */
				CSTR deviceId;
				/** 通道名称 */
				CSTR channelName;
				/** 被共享和授权的权限功能列表（逗号隔开） */
				CSTR shareFunctions;
				/** 遮罩状态，on-打开 off-关闭 */
				CSTR cameraStatus;
				/** 远程通道状态 online-在线 offline-离线 close-未配置 sleep-休眠 */
				CSTR status;
				/** 通道号 */
				CSTR channelId;
				/** 设备属于自己；share：通过开放平台共享给此用户 */
				CSTR shareStatus;
				/** 提醒状态，off-不提醒，on-提醒 */
				CSTR remindStatus;
			}) channels;
			/** 设备型号 */
			CSTR deviceModel;
			/** 设备ID */
			CSTR deviceId;
			/** define a list with struct of DeviceBaseDetailListResponseData_DeviceListElement_AplistElement */
			DECLARE_LIST(struct DeviceBaseDetailListResponseData_DeviceListElement_AplistElement
			{
				/** 报警网关配件id */
				CSTR apId;
				/** 配件能力项，逗号隔开，如AudioTalk,PT */
				CSTR apCapacity;
				/** 配件的型号 */
				CSTR apModel;
				/** 配件名称 */
				CSTR apName;
				/** 配件的使能 on-使能开启 off-使能关闭 */
				CSTR apEnable;
				/** 配件的类型 */
				CSTR apType;
				/** 配件的在线状态 online-在线 offline-离线 */
				CSTR apStatus;
				/** 配件的io类型 in-输入 out-输出 */
				CSTR ioType;
				/** 配件的版本号 */
				CSTR apVersion;
			}) aplist;
			/** 设备软件版本号 */
			CSTR version;
			/** 当前状态：online-在线 offline-离线 upgrading-升级中 sleep-休眠 */
			CSTR status;
			/** 设备接入类型，PaaS-表示Paas程序接入、Lechange-表示乐橙非PaaS设备、Easy4IP表示Easy4IP程序设备、P2P表示P2P程序设备 */
			CSTR accessType;
			/** 设备能力项，逗号隔开，详见设备能力集 */
			CSTR ability;
			/** 设备名称 */
			CSTR name;
		}) deviceList;
 
	} data;

} DeviceBaseDetailListResponse;

C_API DeviceBaseDetailListResponse *LCOPENAPI_INIT(DeviceBaseDetailListResponse);

#endif
