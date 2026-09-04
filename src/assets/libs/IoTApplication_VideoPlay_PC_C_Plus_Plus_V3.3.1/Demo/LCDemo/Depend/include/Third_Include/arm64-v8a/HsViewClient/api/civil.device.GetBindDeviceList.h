/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetBindDeviceList_H_
#define _HSVIEW_CLIENT_API_GetBindDeviceList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取用户自己绑定的设备。
请求中的filter字段表示对获取设备的过滤，是一个数组，每个元素代表一个设备ID。
请求中的need表示分页获取,从第几条到第几条，如“1-25”,闭区间,最多一次查询100条"。
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

typedef struct GetBindDeviceListRequest 
{
	HsviewRequest base;

	struct GetBindDeviceListRequestData
	{
		
		/** [int]分页获取时按绑定时间进行排序, sortType为0表示升序,sortType为1表示倒序 */
		int sortType;
		/** 分页获取,从第几条到第几条，如“1-100”,闭区间,最多一次查询100条 */
		CSTR need;
		/** 过滤器，每个元素表示要获取的设备ID，数组为空表示不过滤 */
		DECLARE_LIST(CSTR) filter;

	} data;

} GetBindDeviceListRequest;

C_API GetBindDeviceListRequest *HSAPI_INIT(GetBindDeviceListRequest);

typedef struct GetBindDeviceListResponse 
{
	HsviewResponse base;

	struct GetBindDeviceListResponseData
	{
		
		/** define a list with struct of GetBindDeviceListResponseData_DevicesElement */
		DECLARE_LIST(struct GetBindDeviceListResponseData_DevicesElement
		{
			/** [O]设备品牌信息：lechange-乐橙设备，general-通用设备 */
			CSTR brand;
			/** define a list with struct of GetBindDeviceListResponseData_DevicesElement_ChannelsElement */
			DECLARE_LIST(struct GetBindDeviceListResponseData_DevicesElement_ChannelsElement
			{
				/** struct of GetBindDeviceListResponseData_DevicesElement_ChannelsElement_ContentEncrypt */
				struct GetBindDeviceListResponseData_DevicesElement_ChannelsElement_ContentEncrypt {
					/** 密钥生成算法版本号 */
					CSTR ruleVersion;
					/** 内容加密模式 */
					CSTR encryptMode;
					/** 内容加密秘钥种子KeySeed的模式 */
					CSTR keyMode;
				} contentEncrypt;
				/** [int]云存储状态：-1-未开通 0-已失效 1-使用中 2-套餐暂停 */
				int csStatus;
				/** [O][bool]是否分享或者授权给别人的 */
				CSTR channelBeSharedTo;
				/** [bool]是否分享给别人的,true表示分享给了别人,false表示未分享给别人 */
				BOOL shareStatus;
				/** [int]报警布撤防状态，0-撤防，1-布防 */
				int alarmStatus;
				/** [int] 提醒状态，0-不提醒，1-提醒 */
				int remindStatus;
				/** [bool]是否在线 */
				BOOL channelOnline;
				/** 通道名称 */
				CSTR channelName;
				/** [int] 云存储类型：-1-未开通,0-默认套餐 1-收费套餐,csType只有在csStatus不为-1的时候才有效 */
				int csType;
				/** [O]通道能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
				CSTR channelAbility;
				/** 缩略图URL */
				CSTR channelPicUrl;
				/** [int]通道号 */
				int channelId;
				/** [int]SD卡状态：0-异常，1-正常，2-无SD卡，3-格式化中 */
				int sdcardState;
				/** [O][int]channelBeSharedTo为true时有效，0表示同时分享和授权给别人的设备，1表示分享给别人的设备，2表示授权给别人的设备 */
				CSTR channelBeShareToState;
			}) channels;
			/** 设备logo图片url */
			CSTR logoUrl;
			/** [O][int]beSharedTo为true时有效，0表示同时分享和授权给别人的设备，1表示分享给别人的设备，2表示授权给别人的设备 */
			CSTR beShareToState;
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
			/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
			CSTR ability;
			/** define a list with struct of GetBindDeviceListResponseData_DevicesElement_AplistElement */
			DECLARE_LIST(struct GetBindDeviceListResponseData_DevicesElement_AplistElement
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
				/** struct of GetBindDeviceListResponseData_DevicesElement_AplistElement_UpgradeInfo */
				struct GetBindDeviceListResponseData_DevicesElement_AplistElement_UpgradeInfo {
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
			/** 设备ID */
			CSTR deviceId;
			/** [int]视频通道的总数量（包含未接入的通道） */
			int channelNum;
			/** [bool]设备是否在线 */
			BOOL online;
			/** 设备软件版本号 */
			CSTR version;
			/** [int][O] 设备接入是否通过大华paas协议，可选，无该字段或者为0表示通过老的乐橙平台接入，为1表示通过大华paas协议接入 */
			int paasFlag;
			/** [O]设备型号 */
			CSTR deviceModel;
			/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式, 后续不再支持 */
			int encryptMode;
			/** [O][bool] 是否分享或者授权给别人的 */
			CSTR beSharedTo;
			/** 设备名称 */
			CSTR name;
		}) devices;
 
	} data;

} GetBindDeviceListResponse;

C_API GetBindDeviceListResponse *HSAPI_INIT(GetBindDeviceListResponse);

#endif
