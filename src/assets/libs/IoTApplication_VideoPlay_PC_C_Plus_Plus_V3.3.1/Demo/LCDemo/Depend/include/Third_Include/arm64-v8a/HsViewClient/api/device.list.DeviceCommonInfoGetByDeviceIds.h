/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceList_DeviceCommonInfoGetByDeviceIds_H_
#define _HSVIEW_CLIENT_API_deviceList_DeviceCommonInfoGetByDeviceIds_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
批量根据设备序列号、通道号列表和配件号列表，获取设备的基本信息
deviceList:最大支持8个设备
channelList:没有长度限制，客户端传多少个就查多少个，当channelList长度为0时，不返回通道信息
apList:返回全部配件信息，长度为0或者不传的话不返回配件信息

upnp内容的定义如下：
serviceType: [string], 服务类型
	WebService : HTTP服务
	PrivService : DVRIP的TCP/UDP服务
	RTSPService : RTSP服务
enable:[string]，"on"开启， "off" 关闭
innerAddress:[string], 内网IP
outerAddress:[string],外网IP
innerPort:[int], 内网端口
outerPort:[int], 外网端口
protocol:[string],协议类型,TCP或UDP
格式如下：
{
	"services" : [
			{
				"serviceType", : "WebService",
				"enable" : "on",
				"innerAddress" : "1.1.1.1",
				"outerAddress" : "1.1.1.1",
				"innerPort" : 1,
				"outerPort" : 1,
				"protocol" : "TCP",
				"IP": "1.1.1.1"
			}
	]
}

[paas协议](https://paas.dahuatech.com/wiki/?p=%2FSaaStoPaaS%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2Fcloud.device.DeviceCommonInfoGetByDeviceIds&s=pj)

【需要使用平台账号签名】
 */

typedef struct deviceList_DeviceCommonInfoGetByDeviceIdsRequest 
{
	HsviewRequest base;

	struct deviceList_DeviceCommonInfoGetByDeviceIdsRequestData
	{
		
		/** define a list with struct of deviceList_DeviceCommonInfoGetByDeviceIdsRequestData_DeviceListElement */
		DECLARE_LIST(struct deviceList_DeviceCommonInfoGetByDeviceIdsRequestData_DeviceListElement
		{
			/** 配件Id */
			DECLARE_LIST(CSTR) apList;
			/** 通道号 */
			DECLARE_LIST(CSTR) channelList;
			/** 设备序列号 */
			CSTR deviceId;
		}) deviceList;

	} data;

} deviceList_DeviceCommonInfoGetByDeviceIdsRequest;

C_API deviceList_DeviceCommonInfoGetByDeviceIdsRequest *HSAPI_INIT(deviceList_DeviceCommonInfoGetByDeviceIdsRequest);

typedef struct deviceList_DeviceCommonInfoGetByDeviceIdsResponse 
{
	HsviewResponse base;

	struct deviceList_DeviceCommonInfoGetByDeviceIdsResponseData
	{
		
		/** define a list with struct of deviceList_DeviceCommonInfoGetByDeviceIdsResponseData_DeviceListElement */
		DECLARE_LIST(struct deviceList_DeviceCommonInfoGetByDeviceIdsResponseData_DeviceListElement
		{
			/** [O]设备大类【NVR/DVR/HCVR/IPC/SD/IHG/ARC】（saas） */
			CSTR catalog;
			/** [O]被分享和授权的备注（saas）,海外SMB需求,shareStatus字段为share，auth，shareAndAuth时关注该字段的值 */
			CSTR shareRemark;
			/** [O]设备加密端口,海外使用 */
			CSTR tlsPrivatePort;
			/** 是否有新版本可以升级, true：有, false：无 */
			CSTR canBeUpgrade;
			/** online-在线 offline-在线 upgrading-升级中 sleep-休眠 */
			CSTR status;
			/** [O]设备用户名（Base64(AES256加密)）（saas） */
			CSTR deviceUsername;
			/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P */
			CSTR ability;
			/** 设备序列号 */
			CSTR deviceId;
			/** [O]设备Rtsp端口,海外使用 */
			CSTR rtspPort;
			/** 设备软件版本号 */
			CSTR version;
			/** [O]设备拥有者账号，海外是邮箱 */
			CSTR ownerAccount;
			/** [O] upnp 信息,具体定义见描述 */
			CSTR upnp;
			/** [O]设备Http端口,海外使用 */
			CSTR httpPort;
			/** [O]iot设备唯一标识码 */
			CSTR imei;
			/** [O]获取实时流url的入口地址，app3.15.0拉流优化新增 */
			CSTR streamEntryAddr;
			/** [O]乐橙设备品牌信息：lechange-乐橙设备，general-通用设备，海外使用：dahua-大华设备(大华品牌设备,DMSS品牌设备,DMSS定制设备), lechange-基线设备(Imou,一键OEM设备) */
			CSTR brand;
			/** define a list with struct of deviceList_DeviceCommonInfoGetByDeviceIdsResponseData_DeviceListElement_ChannelsElement */
			DECLARE_LIST(struct deviceList_DeviceCommonInfoGetByDeviceIdsResponseData_DeviceListElement_ChannelsElement
			{
				/** 云存储状态 notExist:未开通套餐，using：开通云存储且没有过期， expired：套餐过期（saas） */
				CSTR storageStrategyStatus;
				/** 缩略图URL */
				CSTR picUrl;
				/** [O]被分享和授权的备注（saas）,海外SMB需求,shareStatus字段为share，auth，shareAndAuth时关注该字段的值 */
				CSTR shareRemark;
				/** [O]被分享和授权的权限功能列表（逗号隔开）（saas） */
				CSTR shareFunctions;
				/** [O]是否有新版本可以升级, true：有, false：无（目前只有HUB下面带序列号的通道设备有） */
				CSTR canBeUpgrade;
				/** 远程通道状态 online-在线 offline-在线 close-未配置 sleep-休眠 upgrading升级中 */
				CSTR status;
				/** [O]提醒状态，off-不提醒，on-提醒 */
				CSTR remindStatus;
				/** [O]通道能力集 如AlarmMD,AudioTalk 逗号隔开 */
				CSTR ability;
				/** [O]通道封面类型，auto--自动抓图,custom--用户自定义图片 */
				CSTR picType;
				/** 设备序列号 */
				CSTR deviceId;
				/** [O]通道最后一次离线的时间，时间格式yyyyMMddTHHmmssZ时间格式 */
				CSTR lastOffLineTime;
				/** [O]提醒状态，off-不提醒，on-提醒,snooze-打盹 */
				CSTR snoozeStatus;
				/** [O]分享给他人的标志，shareToOthers-已经分享给他人，none-没有分享给他人 */
				CSTR shareToOthers;
				/** [O]遮罩状态，on-打开 off-关闭 */
				CSTR cameraStatus;
				/** 通道名称 */
				CSTR channelName;
				/** 通道号 */
				CSTR channelId;
				/** [O]被分享状态 share-别人分享 auth-别人授权 shareAndAuth-别人分享和授权（saas）,该字段没有或者为空的时候表示自己绑定设备的通道 */
				CSTR shareStatus;
				/** [O]通道序列号,只有hub下面的通道这种带序列号的特殊通道有 */
				CSTR channelCode;
			}) channels;
			/** [O]设备上报的大类 */
			CSTR deviceType;
			/** [O]设备私有协议端口,海外使用 */
			CSTR port;
			/** [O]设备高清图片 */
			CSTR HDImage;
			/** [O]设备密码（Base64(AES256加密)）（saas） */
			CSTR devicePassword;
			/** [O]设备外部型号，海外使用，外部型号给app展示使用（saas） */
			CSTR deviceModelName;
			/** [O]设备倍数回放信息 */
			CSTR replayMultiple;
			/** define a list with struct of deviceList_DeviceCommonInfoGetByDeviceIdsResponseData_DeviceListElement_AplistElement */
			DECLARE_LIST(struct deviceList_DeviceCommonInfoGetByDeviceIdsResponseData_DeviceListElement_AplistElement
			{
				/** 报警网关配件id */
				CSTR apId;
				/** [O]配件型号图片的URL地址（oms上配置，根据配件市场型号匹配） */
				CSTR apImageURI;
				/** [O]配件能力项，逗号隔开，如AudioTalk,PT，详见华视微讯设备配件协议 */
				CSTR apCapacity;
				/** 配件的型号 */
				CSTR apModel;
				/** 配件名称 */
				CSTR apName;
				/** 配件的使能 on-使能开启 off-使能关闭 */
				CSTR apEnable;
				/** [O]被分享和授权的权限功能列表（逗号隔开）（saas） */
				CSTR shareFunctions;
				/** 配件的类型 */
				CSTR apType;
				/** 配件的在线状态 online-在线  offline-离线 */
				CSTR apStatus;
				/** 配件的io类型 in-输入  out-输出 */
				CSTR ioType;
				/** [O]share-别人分享，该字段没有或者为空的时候表示该配件在自己绑定的网关下（saas） */
				CSTR shareStatus;
				/** 配件的版本号 */
				CSTR apVersion;
			}) aplist;
			/** 设备型号（saas） */
			CSTR deviceModel;
			/** [O]设备拥有者id */
			CSTR ownerId;
			/** 设备接入类型，PaaS-表示Paas程序接入、Lechange-表示乐橙非PaaS设备、Easy4IP表示Easy4IP程序设备、P2P表示P2P程序设备 */
			CSTR accessType;
			/** [O]被分享和授权的权限功能列表（逗号隔开）（saas）,shareStatus字段为share，auth，shareAndAuth时关注该字段的值 */
			CSTR shareFunctions;
			/** 视频通道的总数量（包含未接入的通道）,网关的通道数可能为0 */
			CSTR channelNum;
			/** [O]海外设备级别分享使用，国内不使用该字段：分享给他人的标志，shareToOthers-已经分享给他人，none-没有分享给他人 */
			CSTR shareToOthers;
			/** 设备名称 */
			CSTR name;
			/** 加密模式，default表示默认加密模式, custom表示用户加密模式，用于设备上传云端录像、报警图片以及全景图等 */
			CSTR encryptMode;
			/** [O]报警输出通道的总数量 */
			CSTR alarmOutChannels;
			/** [O]报警输入通道的总数量 */
			CSTR alarmInChannels;
			/** [O]海外设备级别分享使用，国内不使用该字段：被分享状态 share-别人分享 auth-别人授权 shareAndAuth-别人分享和授权（saas）,owner-自己绑定的设备 */
			CSTR shareStatus;
			/** [O]设备最后一次离线的时间，时间格式yyyyMMddTHHmmssZ时间格式 */
			CSTR lastOffLineTime;
		}) deviceList;
 
	} data;

} deviceList_DeviceCommonInfoGetByDeviceIdsResponse;

C_API deviceList_DeviceCommonInfoGetByDeviceIdsResponse *HSAPI_INIT(deviceList_DeviceCommonInfoGetByDeviceIdsResponse);

#endif
