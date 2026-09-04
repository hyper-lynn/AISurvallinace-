/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceList_H_
#define _LC_OPENAPI_CLIENT_DeviceList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备列表获取
只返回在该应用下添加的设备列表,openapi层会做下过滤

 */

typedef struct DeviceListRequest 
{
	LCOpenApiRequest base;

	struct DeviceListRequestData
	{
		
		/** 第几条到第几条,数字取值范围为：[1,N](N为正整数，且后者＞前者),单次查询上限100 */
		CSTR queryRange;
		/** [cstr]deviceList */
		#define _STATIC_DeviceListRequestData_method "deviceList"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;

	} data;

} DeviceListRequest;

C_API DeviceListRequest *LCOPENAPI_INIT(DeviceListRequest);

typedef struct DeviceListResponse 
{
	LCOpenApiResponse base;

	struct DeviceListResponseData
	{
		
		/** [int]当前获取的设备总数 */
		int count;
		/** define a list with struct of DeviceListResponseData_DevicesElement */
		DECLARE_LIST(struct DeviceListResponseData_DevicesElement
		{
			/** 设备品牌信息：lechange-乐橙设备，general-通用设备 */
			CSTR brand;
			/** [int]平台类型 */
			int platForm;
			/** define a list with struct of DeviceListResponseData_DevicesElement_ChannelsElement */
			DECLARE_LIST(struct DeviceListResponseData_DevicesElement_ChannelsElement
			{
				/** 通道名称 */
				CSTR channelName;
				/** [bool]是否分享给别人的,true表示分享给了别人,false表示未分享给别人 */
				BOOL shareStatus;
				/** 通道能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见乐橙设备协议 */
				CSTR channelAbility;
				/** 缩略图URL */
				CSTR channelPicUrl;
				/** [int]通道号 */
				int channelId;
				/** [bool]是否在线 */
				BOOL channelOnline;
				/** [int]云存储状态：-1-未开通 0-已失效 1-使用中 2-套餐暂停 */
				int csStatus;
			}) channels;
			/** [int]p2p拉流端口 */
			int streamPort;
			/** [bool]是否有新版本可以升级 */
			BOOL canBeUpgrade;
			/** [int]当前状态：0-离线，1-在线，3-升级中 */
			int status;
			/** 设备登陆密码 */
			CSTR devLoginPassword;
			/** 设备分类（NVR/DVR/HCVR/IPC/SD/IHG/ARC) */
			CSTR deviceCatalog;
			/** 设备基线类型，详见华视微讯设备协议 */
			CSTR baseline;
			/** 绑定设备的appId（若为乐橙App绑定，该字段为空字符串） */
			CSTR appId;
			/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见乐橙开放平台设备协议 */
			CSTR ability;
			/** 设备ID */
			CSTR deviceId;
			/** [int]总的视频通道数，包含未接入的通道 */
			int channelNum;
			/** 设备软件版本号 */
			CSTR version;
			/** [int]私有协议p2p拉流端口 */
			int privateStreamPort;
			/** [O]设备型号 */
			CSTR deviceModel;
			/** [int]加密模式 */
			int encryptMode;
			/** 设备名称 */
			CSTR name;
			/** 设备登陆用户名 */
			CSTR devLoginName;
		}) devices;
 
	} data;

} DeviceListResponse;

C_API DeviceListResponse *LCOPENAPI_INIT(DeviceListResponse);

#endif
