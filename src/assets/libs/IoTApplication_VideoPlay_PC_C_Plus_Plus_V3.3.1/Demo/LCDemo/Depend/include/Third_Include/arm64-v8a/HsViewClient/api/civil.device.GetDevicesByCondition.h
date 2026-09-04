/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetDevicesByCondition_H_
#define _HSVIEW_CLIENT_API_GetDevicesByCondition_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

根据条件查询设备列表。可以根据名称或编号模糊匹配用户自己绑定或他人分享过来的设备
 
回复字段如下：
deviceId：设备ID
online：是否在线，true/false
baseline：设备基线类型，详见设备Baseline类型
deviceModel:设备型号
name：设备名称
dms：所在的DMS访问地址
ability：设备能力选项列表，详见设备能力集选项
canBeUpgrade：设备是否能够升级，true/false
channels：设备的视频通道数组，其中：
  id：通道号
  name：通道名称
  ablility 通道能力项列表
  online：是否在线，true/false
  picurl：通道缩略图URL
  
【需要使用平台账号签名】

 */

typedef struct GetDevicesByConditionRequest 
{
	HsviewRequest base;

	struct GetDevicesByConditionRequestData
	{
		
		/** 设备名称或序列号 */
		CSTR deviceNameOrCode;

	} data;

} GetDevicesByConditionRequest;

C_API GetDevicesByConditionRequest *HSAPI_INIT(GetDevicesByConditionRequest);

typedef struct GetDevicesByConditionResponse 
{
	HsviewResponse base;

	struct GetDevicesByConditionResponseData
	{
		
		/** define a list with struct of GetDevicesByConditionResponseData_DevicesElement */
		DECLARE_LIST(struct GetDevicesByConditionResponseData_DevicesElement
		{
			/** define a list with struct of GetDevicesByConditionResponseData_DevicesElement_ChannelsElement */
			DECLARE_LIST(struct GetDevicesByConditionResponseData_DevicesElement_ChannelsElement
			{
				/** [int]报警布撤防状态，0-撤防，1-布防 */
				int alarmStatus;
				/** [int]云存储状态：-1-未开通 0-已失效 1-使用中 2-套餐暂停 */
				int csStatus;
				/** [O]如果是分享过来的通道，填分享的功能列表（逗号隔开） */
				CSTR functions;
				/** [bool][O]是否分享给别人的 */
				BOOL channelBeSharedTo;
				/** 公开视频的token */
				CSTR publicToken;
				/** [int]提醒状态，0-不提醒，1-提醒 */
				int remindStatus;
				/** [int]SD卡状态：0-异常，1-正常，2-无SD卡，3-格式化中 */
				int sdcardState;
				/** 通道名称 */
				CSTR channelName;
				/** [long]公开到期时间，UNIX时间戳，单位秒。为0表示设置为非公共视频。 */
				int64 publicExpire;
				/** [O]通道能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P */
				CSTR channelAbility;
				/** 缩略图URL */
				CSTR channelPicUrl;
				/** [int]通道号 */
				int channelId;
				/** [bool]是否在线 */
				BOOL channelOnline;
				/** [long][O]公开时间，UNIX时间戳（秒） */
				int64 shareTime;
			}) channels;
			/** [O]全景图URL */
			CSTR panoUrl;
			/** 设备logo图片url */
			CSTR logoUrl;
			/** [O]分享者的用户名 */
			CSTR ownerUsername;
			/** [bool]是否有新版本可以升级 */
			BOOL canBeUpgrade;
			/** [int]当前状态：0-离线，1-在线，3-升级中 */
			int status;
			/** [bool][O]是否从别人那里分享的，分享者信息填在ownerInfo结构中 */
			BOOL beSharedFrom;
			/** [O]设备分类【NVR/DVR/HCVR/IPC/SD/IHG】 */
			CSTR deviceCatalog;
			/** [O]访问设备的DMS入口地址，例如122.233.34.45:9200 */
			CSTR dms;
			/** [O]分享者头像URL */
			CSTR ownerUserIcon;
			/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
			CSTR ability;
			/** [O]分享者的昵称 */
			CSTR ownerNickname;
			/** 设备ID */
			CSTR deviceId;
			/** [bool]是否在线 */
			BOOL online;
			/** 设备名称 */
			CSTR name;
			/** [O]设备基线类型，详见华视微讯设备协议 */
			CSTR baseline;
			/** [bool][O]是否分享给别人的 */
			BOOL beSharedTo;
			/** [O]设备型号 */
			CSTR deviceModel;
			/** 设备软件版本号 */
			CSTR version;
		}) devices;
 
	} data;

} GetDevicesByConditionResponse;

C_API GetDevicesByConditionResponse *HSAPI_INIT(GetDevicesByConditionResponse);

#endif
