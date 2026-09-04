/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetBeSharedDeviceList_H_
#define _HSVIEW_CLIENT_API_GetBeSharedDeviceList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户获取别人分享给自己的设备。
请求中的filter字段表示对获取设备的过滤，是一个数组，每个元素代表一个设备ID。
请求中的need表示分页获取,从第几条到第几条，如“1-25”,闭区间,最多一次查询100条"
filter与need是互斥的，filter优先级比need优先级高。
当filter不为空时，以filter为准，不处理need。
当filter为空时,以need为准，需要对need的合法性进行校验。
分页获取时sortType有效。

 
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

NVR/DVR/HCVR/IPC/SD/IHG/ARC : ARC-报警网关

contentEncrypt:设备通道封面码流加密模式，字段详细说明参考[设备加密](../设备加密.md)

【需要使用平台账号签名】

 */

typedef struct GetBeSharedDeviceListRequest 
{
	HsviewRequest base;

	struct GetBeSharedDeviceListRequestData
	{
		
		/** [int]分页获取时按绑定时间进行排序, sortType为0表示升序,sortType为1表示倒序 */
		int sortType;
		/** 分页获取,从第几条到第几条，如“1-100”,闭区间,最多一次查询100条 */
		CSTR need;
		/** 过滤器，每个元素表示要获取的设备ID，数组为空表示不过滤 */
		DECLARE_LIST(CSTR) filter;

	} data;

} GetBeSharedDeviceListRequest;

C_API GetBeSharedDeviceListRequest *HSAPI_INIT(GetBeSharedDeviceListRequest);

typedef struct GetBeSharedDeviceListResponse 
{
	HsviewResponse base;

	struct GetBeSharedDeviceListResponseData
	{
		
		/** define a list with struct of GetBeSharedDeviceListResponseData_DevicesElement */
		DECLARE_LIST(struct GetBeSharedDeviceListResponseData_DevicesElement
		{
			/** [O]设备品牌信息：lechange-乐橙设备，general-通用设备 */
			CSTR brand;
			/** define a list with struct of GetBeSharedDeviceListResponseData_DevicesElement_ChannelsElement */
			DECLARE_LIST(struct GetBeSharedDeviceListResponseData_DevicesElement_ChannelsElement
			{
				/** struct of GetBeSharedDeviceListResponseData_DevicesElement_ChannelsElement_ContentEncrypt */
				struct GetBeSharedDeviceListResponseData_DevicesElement_ChannelsElement_ContentEncrypt {
					/** 密钥生成算法版本号 */
					CSTR ruleVersion;
					/** 内容加密模式 */
					CSTR encryptMode;
					/** 内容加密秘钥种子KeySeed的模式 */
					CSTR keyMode;
				} contentEncrypt;
				/** 通道名称 */
				CSTR channelName;
				/** [O]通道能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
				CSTR channelAbility;
				/** 缩略图URL */
				CSTR channelPicUrl;
				/** [int]通道号 */
				int channelId;
				/** [bool]是否在线 */
				BOOL channelOnline;
				/** [int]报警布撤防状态，0-撤防，1-布防 */
				int alarmStatus;
			}) channels;
			/** 设备logo图片url */
			CSTR logoUrl;
			/** 分享者的用户名 */
			CSTR ownerUsername;
			/** [bool]是否有新版本可以升级 */
			BOOL canBeUpgrade;
			/** [int]当前状态：0-离线，1-在线，3-升级中 */
			int status;
			/** [O]设备分类【NVR/DVR/HCVR/IPC/SD/IHG/ARC】 */
			CSTR deviceCatalog;
			/** [O]设备基线类型，详见华视微讯设备协议 */
			CSTR baseline;
			/** [O]设备型号 */
			CSTR deviceModel;
			/** 设备ID */
			CSTR deviceId;
			/** [int]视频通道的总数量（包含未接入的通道） */
			int channelNum;
			/** 设备软件版本号 */
			CSTR version;
			/** [int][O] 设备接入是否通过大华paas协议，可选，无该字段或者为0表示通过老的乐橙平台接入，为1表示通过大华paas协议接入 */
			int paasFlag;
			/** define a list with struct of GetBeSharedDeviceListResponseData_DevicesElement_AplistElement */
			DECLARE_LIST(struct GetBeSharedDeviceListResponseData_DevicesElement_AplistElement
			{
				/** 报警网关配件id */
				CSTR apId;
				/** 配件的型号 */
				CSTR apModel;
				/** 配件名称 */
				CSTR apName;
				/** [int]配件的使能:1-使能开启 ，0-使能关闭 */
				int apEnable;
				/** [bool]是否有新版本可以升级 */
				BOOL canBeUpgrade;
				/** 配件的类型 */
				CSTR apType;
				/** [int]配件的在线状态：1-在线  0-离线 */
				int apStatus;
				/** [int]配件的io类型：0-输入  1-输出 */
				int ioType;
				/** struct of GetBeSharedDeviceListResponseData_DevicesElement_AplistElement_UpgradeInfo */
				struct GetBeSharedDeviceListResponseData_DevicesElement_AplistElement_UpgradeInfo {
					/** 下载地址 */
					CSTR packageUrl;
					/** 升级描述信息 */
					CSTR description;
					/** 最新版本号 */
					CSTR version;
				} upgradeInfo;
				/** 配件的版本号 */
				CSTR apVersion;
			}) aplist;
			/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式, 后续不再支持 */
			int encryptMode;
			/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
			CSTR ability;
			/** 设备名称 */
			CSTR name;
		}) devices;
 
	} data;

} GetBeSharedDeviceListResponse;

C_API GetBeSharedDeviceListResponse *HSAPI_INIT(GetBeSharedDeviceListResponse);

#endif
