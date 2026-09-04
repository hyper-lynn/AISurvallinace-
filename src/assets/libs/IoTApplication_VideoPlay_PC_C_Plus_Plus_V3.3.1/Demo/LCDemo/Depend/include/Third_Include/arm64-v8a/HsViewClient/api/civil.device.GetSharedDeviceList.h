/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetSharedDeviceList_H_
#define _HSVIEW_CLIENT_API_GetSharedDeviceList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取分享给别人的设备列表。
当type为空或者不存在时，表示获取共享和授权列表，同时存在共享和授权时，权限会被合并，列表中只有一个。


回复字段如下：
deviceId：设备ID
baseline：设备基线类型，详见设备Baseline类型
deviceModel:设备型号
name：设备名称
ability：设备能力选项列表，详见设备能力集选项
canBeUpgrade：设备是否能够升级，true/false
channels：设备的视频通道数组，其中：
  id：通道号
  name：通道名称
  ablility 通道能力项列表
  online：是否在线，true/false
  picurl：通道缩略图URL
  functions: 共享和授权的权限列表合集(并集)

contentEncrypt:设备通道封面码流加密模式，字段详细说明参考[设备加密](../设备加密.md)

【需要使用平台账号签名】

 */

typedef struct GetSharedDeviceListRequest 
{
	HsviewRequest base;

	struct GetSharedDeviceListRequestData
	{
		
		/** 用户名 */
		CSTR username;
		/** [O]类型，share或者auth，share表示共享，auth表示授权 */
		CSTR type;

	} data;

} GetSharedDeviceListRequest;

C_API GetSharedDeviceListRequest *HSAPI_INIT(GetSharedDeviceListRequest);

typedef struct GetSharedDeviceListResponse 
{
	HsviewResponse base;

	struct GetSharedDeviceListResponseData
	{
		
		/** define a list with struct of GetSharedDeviceListResponseData_DevicesElement */
		DECLARE_LIST(struct GetSharedDeviceListResponseData_DevicesElement
		{
			/** [O]设备品牌信息：lechange-乐橙设备，general-通用设备 */
			CSTR brand;
			/** [O]设备基线类型，详见华视微讯设备协议 */
			CSTR baseline;
			/** define a list with struct of GetSharedDeviceListResponseData_DevicesElement_ChannelsElement */
			DECLARE_LIST(struct GetSharedDeviceListResponseData_DevicesElement_ChannelsElement
			{
				/** struct of GetSharedDeviceListResponseData_DevicesElement_ChannelsElement_ContentEncrypt */
				struct GetSharedDeviceListResponseData_DevicesElement_ChannelsElement_ContentEncrypt {
					/** 密钥生成算法版本号 */
					CSTR ruleVersion;
					/** 内容加密模式 */
					CSTR encryptMode;
					/** 内容加密秘钥种子KeySeed的模式 */
					CSTR keyMode;
				} contentEncrypt;
				/** 通道名称 */
				CSTR channelName;
				/** 共享或者授权的功能列表（逗号隔开） */
				CSTR functions;
				/** 缩略图URL */
				CSTR channelPicUrl;
				/** [int]通道号 */
				int channelId;
				/** [bool]是否在线 */
				BOOL channelOnline;
			}) channels;
			/** [O]设备型号 */
			CSTR deviceModel;
			/** 设备ID */
			CSTR deviceId;
			/** [bool]是否有新版本可以升级 */
			BOOL canBeUpgrade;
			/** 设备名称 */
			CSTR name;
			/** [int][O] 设备接入是否通过大华paas协议，可选，无该字段或者为0表示通过老的乐橙平台接入，为1表示通过大华paas协议接入 */
			int paasFlag;
			/** [int]当前状态：0-离线，1-在线，3-升级中 */
			int status;
			/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
			CSTR ability;
			/** [O]设备分类【NVR/DVR/HCVR/IPC/SD/IHG/ARC】 */
			CSTR deviceCatalog;
			/** 设备软件版本号 */
			CSTR version;
		}) devices;
 
	} data;

} GetSharedDeviceListResponse;

C_API GetSharedDeviceListResponse *HSAPI_INIT(GetSharedDeviceListResponse);

#endif
