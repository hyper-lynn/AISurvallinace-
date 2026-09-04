/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetGroupDeviceList_H_
#define _HSVIEW_CLIENT_API_GetGroupDeviceList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

获取该分组下面的子分组和设备列表。
groupId为-1表示获取返回所有未分组的设备，包括自己的和别人共享、授权给自己的所有设备。
 
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

contentEncrypt:设备通道封面码流加密模式，字段详细说明参考[设备加密](../设备加密.md)
  
【需要使用平台账号签名】

 */

typedef struct GetGroupDeviceListRequest 
{
	HsviewRequest base;

	struct GetGroupDeviceListRequestData
	{
		
		/** [long]设备分组的id,为-1表示获取所有未分组的设备，包括自己的和别人共享、授权给自己的所有设备 */
		int64 groupId;

	} data;

} GetGroupDeviceListRequest;

C_API GetGroupDeviceListRequest *HSAPI_INIT(GetGroupDeviceListRequest);

typedef struct GetGroupDeviceListResponse 
{
	HsviewResponse base;

	struct GetGroupDeviceListResponseData
	{
		
		/** define a list with struct of GetGroupDeviceListResponseData_GroupsElement */
		DECLARE_LIST(struct GetGroupDeviceListResponseData_GroupsElement
		{
			/** 分组的封面，为空代表使用默认封面 */
			CSTR cover;
			/** [long]分组的最后修改unix时间戳，精确到秒 */
			int64 ts;
			/** 分组名称 */
			CSTR groupName;
			/** [long]分组id */
			int64 groupId;
		}) groups;
		/** define a list with struct of GetGroupDeviceListResponseData_DevicesElement */
		DECLARE_LIST(struct GetGroupDeviceListResponseData_DevicesElement
		{
			/** define a list with struct of GetGroupDeviceListResponseData_DevicesElement_ChannelsElement */
			DECLARE_LIST(struct GetGroupDeviceListResponseData_DevicesElement_ChannelsElement
			{
				/** struct of GetGroupDeviceListResponseData_DevicesElement_ChannelsElement_ContentEncrypt */
				struct GetGroupDeviceListResponseData_DevicesElement_ChannelsElement_ContentEncrypt {
					/** 密钥生成算法版本号 */
					CSTR ruleVersion;
					/** 内容加密模式 */
					CSTR encryptMode;
					/** 内容加密秘钥种子KeySeed的模式 */
					CSTR keyMode;
				} contentEncrypt;
				/** [int]云存储状态：-1-未开通 0-已失效 1-使用中 2-套餐暂停 */
				int csStatus;
				/** [long][O]公开时间，UNIX时间戳（秒） */
				int64 shareTime;
				/** [O]如果是分享或者授权过来的通道，填分享或者授权的功能列表（逗号隔开） */
				CSTR functions;
				/** [bool][O]是否分享或者授权给别人的 */
				BOOL channelBeSharedTo;
				/** [int]SD卡状态：0-异常，1-正常，2-无SD卡，3-格式化中 */
				int sdcardState;
				/** 公开视频的token */
				CSTR publicToken;
				/** [int]提醒状态，0-不提醒，1-提醒 */
				int remindStatus;
				/** [int]报警布撤防状态，0-撤防，1-布防 */
				int alarmStatus;
				/** 通道名称 */
				CSTR channelName;
				/** [long]公开到期时间，UNIX时间戳，单位秒。为0表示设置为非公共视频。 */
				int64 publicExpire;
				/** [O]通道能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
				CSTR channelAbility;
				/** 缩略图URL */
				CSTR channelPicUrl;
				/** [int]通道号 */
				int channelId;
				/** [bool]是否在线 */
				BOOL channelOnline;
				/** [int][O]channelBeSharedTo为true时有效，0表示同时分享和授权给别人的设备，1表示分享给别人的设备，2表示授权给别人的设备 */
				int channelBeShareToState;
			}) channels;
			/** [O]全景图URL */
			CSTR panoUrl;
			/** 设备logo图片url */
			CSTR logoUrl;
			/** [int][O]beSharedTo为true时有效，0表示同时分享和授权给别人的设备，1表示分享给别人的设备，2表示授权给别人的设备 */
			int beShareToState;
			/** [bool]是否有新版本可以升级 */
			BOOL canBeUpgrade;
			/** [O]设备所属的用户id，PC5.1需求新增 */
			CSTR ownerId;
			/** [int]当前状态：0-离线，1-在线，3-升级中 */
			int status;
			/** [bool][O]是否从别人那里分享或者授权的，分享者信息填在ownerInfo结构中 */
			BOOL beSharedFrom;
			/** [O]设备分类【NVR/DVR/HCVR/IPC/SD/IHG】 */
			CSTR deviceCatalog;
			/** [O]分享者的用户名 */
			CSTR ownerUsername;
			/** [O]设备密码（Base64(AES256加密)） */
			CSTR devicePassword;
			/** [O]访问设备的DMS入口地址，例如122.233.34.45:9200 */
			CSTR dms;
			/** [O]设备用户名（Base64(AES256加密)） */
			CSTR deviceUsername;
			/** [O]分享者头像URL */
			CSTR ownerUserIcon;
			/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
			CSTR ability;
			/** [O]设备型号 */
			CSTR deviceModel;
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
			/** [O]设备基线类型，详见华视微讯设备协议 */
			CSTR baseline;
			/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式, 后续不再支持 */
			int encryptMode;
			/** [bool][O]是否分享或者授权给别人的 */
			BOOL beSharedTo;
			/** 设备软件版本号 */
			CSTR version;
		}) devices;
 
	} data;

} GetGroupDeviceListResponse;

C_API GetGroupDeviceListResponse *HSAPI_INIT(GetGroupDeviceListResponse);

#endif
