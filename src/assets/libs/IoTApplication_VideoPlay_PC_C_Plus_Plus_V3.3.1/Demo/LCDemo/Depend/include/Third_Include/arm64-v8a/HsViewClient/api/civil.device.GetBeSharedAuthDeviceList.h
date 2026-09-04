/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetBeSharedAuthDeviceList_H_
#define _HSVIEW_CLIENT_API_GetBeSharedAuthDeviceList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取被别人分享或者授权的设备列表。
  
【需要使用平台账号签名】
 */

typedef struct GetBeSharedAuthDeviceListRequest 
{
	HsviewRequest base;

	struct GetBeSharedAuthDeviceListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetBeSharedAuthDeviceListRequest;

C_API GetBeSharedAuthDeviceListRequest *HSAPI_INIT(GetBeSharedAuthDeviceListRequest);

typedef struct GetBeSharedAuthDeviceListResponse 
{
	HsviewResponse base;

	struct GetBeSharedAuthDeviceListResponseData
	{
		
		/** define a list with struct of GetBeSharedAuthDeviceListResponseData_DevicesElement */
		DECLARE_LIST(struct GetBeSharedAuthDeviceListResponseData_DevicesElement
		{
			/** [O]设备品牌信息：lechange-乐橙设备，general-通用设备 */
			CSTR brand;
			/** define a list with struct of GetBeSharedAuthDeviceListResponseData_DevicesElement_ChannelsElement */
			DECLARE_LIST(struct GetBeSharedAuthDeviceListResponseData_DevicesElement_ChannelsElement
			{
				/** [int]云存储状态：-1-未开通 0-已失效 1-使用中 2-套餐暂停 */
				int csStatus;
				/** [O]如果是分享或者授权过来的通道，填分享或者授权的功能列表（逗号隔开） */
				CSTR functions;
				/** [int]SD卡状态：0-异常，1-正常，2-无SD卡，3-格式化中 */
				int sdcardState;
				/** 通道名称 */
				CSTR channelName;
				/** [int]云存储类型：-1-未开通,0-默认套餐 1-收费套餐,csType只有在csStatus不为-1的时候才有效 */
				int csType;
				/** [O]通道能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
				CSTR channelAbility;
				/** 缩略图URL */
				CSTR channelPicUrl;
				/** [int]提醒状态，0-不提醒，1-提醒 */
				int remindStatus;
				/** [bool]是否在线 */
				BOOL channelOnline;
				/** [int]通道号 */
				int channelId;
			}) channels;
			/** [O]分享者的用户名 */
			CSTR ownerUsername;
			/** [bool]是否有新版本可以升级 */
			BOOL canBeUpgrade;
			/** [int]当前状态：0-离线，1-在线，3-升级中 */
			int status;
			/** [O]设备分类【NVR/DVR/HCVR/IPC/SD/IHG/ARC】 */
			CSTR deviceCatalog;
			/** [O]设备密码（Base64(AES256加密)） */
			CSTR devicePassword;
			/** [O]设备基线类型，详见华视微讯设备协议 */
			CSTR baseline;
			/** [O]设备用户名（Base64(AES256加密)） */
			CSTR deviceUsername;
			/** [O]分享者头像URL */
			CSTR ownerUserIcon;
			/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
			CSTR ability;
			/** [O]分享者的昵称 */
			CSTR ownerNickname;
			/** 设备ID */
			CSTR deviceId;
			/** [int][O]1表示别人分享给自己的设备，2表示别人授权给自己的设备 */
			int shareState;
			/** [bool]是否在线 */
			BOOL online;
			/** 设备名称 */
			CSTR name;
			/** [int][O] 设备接入是否通过大华paas协议，可选，无该字段或者为0表示通过老的乐橙平台接入，为1表示通过大华paas协议接入 */
			int paasFlag;
			/** [int]视频通道的总数量（包含未接入的通道） */
			int channelNum;
			/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式, 后续不再支持 */
			int encryptMode;
			/** [O]设备型号 */
			CSTR deviceModel;
			/** 设备软件版本号 */
			CSTR version;
		}) devices;
 
	} data;

} GetBeSharedAuthDeviceListResponse;

C_API GetBeSharedAuthDeviceListResponse *HSAPI_INIT(GetBeSharedAuthDeviceListResponse);

#endif
