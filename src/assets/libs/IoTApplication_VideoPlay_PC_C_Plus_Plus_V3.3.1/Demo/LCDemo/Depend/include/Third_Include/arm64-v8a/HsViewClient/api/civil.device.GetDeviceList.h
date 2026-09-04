/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetDeviceList_H_
#define _HSVIEW_CLIENT_API_GetDeviceList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

获取设备列表。根据请求中的mode字段，分为两种模式：
bind：获取已绑定的本账号下的设备
unbind：获取已注册，但未绑定的设备
请求中的filter字段表示对获取设备的过滤，是一个数组，每个元素代表一个设备ID。

例如：
mode为bind，filter为空时，表示获取本账号下所有设备。
mode为unbind，filter为["ABC123"]时，表示获取ID为ABC123这台未绑定设备的信息。（若这台设备已绑定，则返回空。）
 
回复字段如下：
deviceId：设备ID
online：是否在线，true/false
baseline：设备基线类型，详见设备Baseline类型
deviceModel:设备型号
name：设备名称
dms：所在的DMS访问地址
ability：设备能力选项列表，详见设备能力集选项
canBeUpgrade：设备是否能够升级，true/false
encryptMode为1表示标识是否使用自定义密钥加密,为0表示不加密或者使用序列号加密
channels：设备的视频通道数组，其中：
  id：通道号
  name：通道名称
  ablility 通道能力项列表
  online：是否在线，true/false
  picurl：通道缩略图URL

NVR/DVR/HCVR/IPC/SD/IHG/ARC : ARC-报警网关

functions：共享的功能,realtime(视频查看),videoMonitor(视频控制)，configure(基础配置管理)，alarmMsg(报警消息查看)，videoRecord(云录像查看),localVideoRecord(本地录像查看),cloudRecordManage(云录像管理),seniorConfigure(高级配置管理)

contentEncrypt:设备通道封面码流加密模式，字段详细说明参考[设备加密](../设备加密.md)

当设备具有Auth能力集时，deviceUsername、devicePassword作为返回必须参数
  
【需要使用平台账号签名】

 */

typedef struct GetDeviceListRequest 
{
	HsviewRequest base;

	struct GetDeviceListRequestData
	{
		
		/** 过滤器，每个元素表示要获取的设备ID，数组为空表示不过滤 */
		DECLARE_LIST(CSTR) filter;
		/** 请求模式，分为bind和unbind */
		CSTR mode;

	} data;

} GetDeviceListRequest;

C_API GetDeviceListRequest *HSAPI_INIT(GetDeviceListRequest);

typedef struct GetDeviceListResponse 
{
	HsviewResponse base;

	struct GetDeviceListResponseData
	{
		
		/** define a list with struct of GetDeviceListResponseData_DevicesElement */
		DECLARE_LIST(struct GetDeviceListResponseData_DevicesElement
		{
			/** [O]设备品牌信息：lechange-乐橙设备，general-通用设备 */
			CSTR brand;
			/** define a list with struct of GetDeviceListResponseData_DevicesElement_AplistElement */
			DECLARE_LIST(struct GetDeviceListResponseData_DevicesElement_AplistElement
			{
				/** 报警网关配件id */
				CSTR apId;
				/** [O]配件能力项，逗号隔开，如AudioTalk,PT，详见华视微讯设备配件协议 */
				CSTR apCapacity;
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
				/** struct of GetDeviceListResponseData_DevicesElement_AplistElement_UpgradeInfo */
				struct GetDeviceListResponseData_DevicesElement_AplistElement_UpgradeInfo {
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
			/** [O]设备所属的用户id，PC5.1需求新增 */
			CSTR ownerId;
			/** define a list with struct of GetDeviceListResponseData_DevicesElement_ChannelsElement */
			DECLARE_LIST(struct GetDeviceListResponseData_DevicesElement_ChannelsElement
			{
				/** struct of GetDeviceListResponseData_DevicesElement_ChannelsElement_ContentEncrypt */
				struct GetDeviceListResponseData_DevicesElement_ChannelsElement_ContentEncrypt {
					/** 密钥生成算法版本号 */
					CSTR ruleVersion;
					/** 内容加密模式 */
					CSTR encryptMode;
					/** 内容加密秘钥种子KeySeed的模式 */
					CSTR keyMode;
				} contentEncrypt;
				/** [int]云存储状态：-1-未开通 0-已失效 1-使用中 2-套餐暂停 */
				int csStatus;
				/** [int]云存储类型：-1-未开通,0-默认套餐 1-收费套餐,csType只有在csStatus不为-1的时候才有效 */
				int csType;
				/** [O]通道能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
				CSTR channelAbility;
				/** [O]列表中最后一个套餐过期时间，当csStatus为1或者2时，storageStrategyExpireTime为空：表明永久，不为空表明:套餐总过期时间，套餐过期时间yyyyMMddTHHmmssZ格式 */
				CSTR csExpireTime;
				/** [int]提醒状态，0-不提醒，1-提醒 */
				int remindStatus;
				/** [int]SD卡状态：0-异常，1-正常，2-无SD卡，3-格式化中 */
				int sdcardState;
				/** [int]报警布撤防状态，0-撤防，1-布防 */
				int alarmStatus;
				/** [int]设备摄像头是否被遮罩, 有遮罩能力集时，0表示未遮罩，1表示遮罩；无遮罩能力集时此字段无效 */
				int isCloseCamera;
				/** [O]如果是分享或者授权过来的通道，填分享或者授权的功能列表（逗号隔开） */
				CSTR functions;
				/** [bool][O]是否分享或者授权给别人的 */
				BOOL channelBeSharedTo;
				/** 公开视频的token */
				CSTR publicToken;
				/** [O]通道最后一次离线时间，yyyyMMddTHHmmssZ时间格式，app3.8需求 */
				CSTR lastOffLineTime;
				/** 通道名称 */
				CSTR channelName;
				/** [long]公开到期时间，UNIX时间戳，单位秒。为0表示设置为非公共视频。 */
				int64 publicExpire;
				/** [long][O]公开时间，UNIX时间戳（秒） */
				int64 shareTime;
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
			/** 设备软件版本号 */
			CSTR version;
			/** [O]设备最后一次的注册时间，yyyyMMddTHHmmssZ时间格式 */
			CSTR updateTime;
			/** [int]视频通道的总数量（包含未接入的通道） */
			int channelNum;
			/** [int][O]beSharedTo为true时有效，0表示同时分享和授权给别人的设备，1表示分享给别人的设备，2表示授权给别人的设备 */
			int beShareToState;
			/** [bool]是否有新版本可以升级 */
			BOOL canBeUpgrade;
			/** [O]设备基线类型，详见华视微讯设备协议 */
			CSTR baseline;
			/** [int]当前状态：0-离线，1-在线，3-升级中，5-休眠中 */
			int status;
			/** [bool][O]是否从别人那里分享或者授权的，分享者信息填在ownerInfo结构中 */
			BOOL beSharedFrom;
			/** [O]设备分类【NVR/DVR/HCVR/IPC/SD/IHG/ARC】 */
			CSTR deviceCatalog;
			/** [O]设备型号 */
			CSTR deviceModel;
			/** [O]设备MAC */
			CSTR mac;
			/** [O]访问设备的DMS入口地址，例如122.233.34.45:9200 */
			CSTR dms;
			/** [O]设备用户名（Base64(AES256加密)） */
			CSTR deviceUsername;
			/** [O]分享者头像URL */
			CSTR ownerUserIcon;
			/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
			CSTR ability;
			/** [O]分享者的用户名 */
			CSTR ownerUsername;
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
			/** [bool][O]是否分享或者授权给别人的 */
			BOOL beSharedTo;
			/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式, 后续不再支持 */
			int encryptMode;
			/** [O]设备密码（Base64(AES256加密)） */
			CSTR devicePassword;
			/** [O]设备最后一次离线时间，yyyyMMddTHHmmssZ时间格式，app3.8需求 */
			CSTR lastOffLineTime;
		}) devices;
 
	} data;

} GetDeviceListResponse;

C_API GetDeviceListResponse *HSAPI_INIT(GetDeviceListResponse);

#endif
