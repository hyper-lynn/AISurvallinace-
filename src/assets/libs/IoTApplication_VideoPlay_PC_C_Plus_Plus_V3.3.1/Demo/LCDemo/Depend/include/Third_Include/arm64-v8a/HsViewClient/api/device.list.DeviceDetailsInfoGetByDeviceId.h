/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceList_DeviceDetailsInfoGetByDeviceId_H_
#define _HSVIEW_CLIENT_API_deviceList_DeviceDetailsInfoGetByDeviceId_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据单个设备序列号获取设备详情

[paas协议](https://paas.dahuatech.com/wiki/?p=%2FSaaStoPaaS%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2Fcloud.device.DeviceDetailInfoGet&s=pj)
【需要使用平台账号签名】
 */

typedef struct deviceList_DeviceDetailsInfoGetByDeviceIdRequest 
{
	HsviewRequest base;

	struct deviceList_DeviceDetailsInfoGetByDeviceIdRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} deviceList_DeviceDetailsInfoGetByDeviceIdRequest;

C_API deviceList_DeviceDetailsInfoGetByDeviceIdRequest *HSAPI_INIT(deviceList_DeviceDetailsInfoGetByDeviceIdRequest);

typedef struct deviceList_DeviceDetailsInfoGetByDeviceIdResponse 
{
	HsviewResponse base;

	struct deviceList_DeviceDetailsInfoGetByDeviceIdResponseData
	{
		
		/** define a list with struct of deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement */
		DECLARE_LIST(struct deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement
		{
			/** [O]设备大类【NVR/DVR/HCVR/IPC/SD/IHG/ARC】（saas） */
			CSTR catalog;
			/** [O]OEM厂商，用于统计, 值可能为 空、DH、Dahua、OEM...,设备上报，如果基于此值做业务，忽略大小写 */
			CSTR vendor;
			/** [O]设备外网地址,限定Lorex返回 */
			CSTR deviceIp;
			/** [O]被分享和授权的备注（saas）,海外SMB需求 */
			CSTR shareRemark;
			/** [O]设备加密端口,海外使用 */
			CSTR tlsPrivatePort;
			/** 是否有新版本可以升级, true：有, false：无 */
			CSTR canBeUpgrade;
			/** online-在线 offline-在线 upgrading-升级中 sleep-休眠 */
			CSTR status;
			/** [O]Tls使能开关,ture-开启,false-关闭 */
			CSTR tlsEnable;
			/** define a list with struct of deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement_AplistElement */
			DECLARE_LIST(struct deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement_AplistElement
			{
				/** [O]分享给他人的标志,shareToOthers-已经分享给他人，none-没有分享给他人，默认表示没有分享给别人 */
				CSTR shareToOthers;
				/** 报警网关配件id */
				CSTR apId;
				/** [O]配件型号图片的URL地址（oms上配置，根据配件市场型号匹配） */
				CSTR apImageURI;
				/** [O]配件能力项，逗号隔开，如AudioTalk,PT，详见华视微讯设备配件协议 */
				CSTR apCapacity;
				/** 海外为配件市场型号，国内为配件上报型号 */
				CSTR apModel;
				/** [O]share-别人分享，该字段没有或者为空的时候表示该配件在自己绑定的网关下 */
				CSTR shareStatus;
				/** [O]被分享和授权的权限功能列表（逗号隔开）（saas） */
				CSTR shareFunctions;
				/** 配件名称 */
				CSTR apName;
				/** struct of deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement_AplistElement_ApState */
				struct deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement_AplistElement_ApState {
					/** [O]上报时间,yyyyMMddTHHmmss时间格式 */
					CSTR reportTime;
					/** [O]电量百分比强度 */
					CSTR electric;
					/** [O]门磁开关状态,open:门磁开启,close:门磁关闭 */
					CSTR doormagnetic;
					/** [O]信号强度 */
					CSTR sigIntensity;
				} apState;
				/** 配件的使能 on-使能开启 off-使能关闭 */
				CSTR apEnable;
				/** 是否有新版本可以升级, true：有, false：无 */
				CSTR canBeUpgrade;
				/** 配件的类型 */
				CSTR apType;
				/** 配件的在线状态 online-在线  offline-离线 */
				CSTR apStatus;
				/** 配件的io类型 in-输入  out-输出 */
				CSTR ioType;
				/** 配件的市场型号 */
				CSTR apModelName;
				/** 配件的版本号 */
				CSTR apVersion;
			}) aplist;
			/** [O]表示无线支持频段的序列，逗号隔开：2.4Ghz,5Ghz(saas) */
			CSTR wifiTransferMode;
			/** define a list with struct of deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement_ChannelsElement */
			DECLARE_LIST(struct deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement_ChannelsElement
			{
				/** 云存储状态 notExist:未开通套餐，using:开通云存储且没有过期， expired：套餐过期（saas） */
				CSTR storageStrategyStatus;
				/** 缩略图URL */
				CSTR picUrl;
				/** AI 人形套餐状态 notExist:未开通套餐，using：开通且没有过期， expired：套餐过期（saas） */
				CSTR humanStrategyStatus;
				/** [O]自动续费状态，on:表示当前正在使用的是自动续费套餐，off：表示为普通套餐。只有在storageStrategyStatus为using状态下才有效。intelbras需求新增字段 */
				CSTR autoRenewalStatus;
				/** [O]通道最后一次离线的时间，时间格式yyyyMMddTHHmmssZ时间格式 */
				CSTR lastOffLineTime;
				/** [O]被分享和授权的备注（saas）,海外SMB需求 */
				CSTR shareRemark;
				/** struct of deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement_ChannelsElement_WifiState */
				struct deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement_ChannelsElement_WifiState {
					/** [O]WIFI名称,如TP-link */
					CSTR ssId;
					/** [O]强度,0最弱,5最强 */
					CSTR intensity;
					/** [O]强度,单位为dbm */
					CSTR sigStrength;
					/** [O]上报时间,yyyyMMddTHHmmss时间格式 */
					CSTR reportTime;
					/** [O]当前有无连接热点,exist-有,notExist-无 */
					CSTR linkEnable;
				} wifiState;
				/** [O]是否有新版本可以升级, true：有, false：无（目前只有HUB下面带序列号的通道设备有） */
				CSTR canBeUpgrade;
				/** [O] 安恒加密套餐过期时间encryptStrategyStatus=using时，storageStrategyExpireTime为空表示是永久免费，有值表示套餐最后的过期时间，套餐过期时间yyyyMMddTHHmmssZ格式（saas） */
				CSTR encryptStrategyExpireTime;
				/** 远程通道状态 online-在线 offline-在线 close-未配置 sleep-休眠 upgrading升级中 */
				CSTR status;
				/** [O]提醒状态，off-不提醒，on-提醒 */
				CSTR remindStatus;
				/** [O]分享给他人的标志，shareToOthers-已经分享给他人，none-没有分享给他人 */
				CSTR shareToOthers;
				/** 通道名称 */
				CSTR channelName;
				/** [O] humanStrategyStatus=using时,套餐过期时间yyyyMMddTHHmmssZ格式（saas） */
				CSTR humanStrategyExpireTime;
				/** [O]安恒加密套餐开关，on:表示开启，off：表示关闭。只有在encryptStrategyStatus为using状态下才有效。 */
				CSTR encryptStrategySwitch;
				/** [O]提醒状态，off-不提醒，on-提醒,snooze-打盹 */
				CSTR snoozeStatus;
				/** [O]云录像上报开关，on:表示开启，off：表示关闭。只有在storageStrategyStatus为using状态下才有效。intelbras需求新增字段 */
				CSTR cloudRecordSwitch;
				/** [O]通道能力集 如AlarmMD,AudioTalk逗号隔开 */
				CSTR ability;
				/** [O]通道封面类型，auto--自动抓图,custom--用户自定义图片 */
				CSTR picType;
				/** [O]被分享和授权的权限功能列表（逗号隔开）（saas） */
				CSTR shareFunctions;
				/** [int] -1 开关关,1->半小时,2->1小时,3->2小时,0->默认开 */
				int snoozeDuration;
				/** [O]远程设备型号(Lorex设备) */
				CSTR deviceModel;
				/** [O]遮罩状态，on-打开 off-关闭 */
				CSTR cameraStatus;
				/** struct of deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement_ChannelsElement_ElectricState */
				struct deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement_ChannelsElement_ElectricState {
					/** [O]电量百分比,取值范围0-100,-1设备无该电池 */
					CSTR electric;
					/** [O]碱性电池电量百分比,取值范围0-100,-1设备无该电池 */
					CSTR alkElec;
					/** [O]上报时间,yyyyMMddTHHmmss时间格式 */
					CSTR reportTime;
					/** [O]锂电池电量百分比,取值范围0-100,-1设备无该电池 */
					CSTR litElec;
					/** [O]供电类型,当type为空时,默认为battery类型 */
					CSTR type;
				} electricState;
				/** 安恒加密套餐状态 notExist:未开通套餐，using:开通云存储且没有过期， expired：套餐过期（saas） */
				CSTR encryptStrategyStatus;
				/** [O] 当storageStrategyStatus=using时，storageStrategyExpireTime为空表示是永久免费，有值表示套餐最后的过期时间，套餐过期时间yyyyMMddTHHmmssZ格式（saas） */
				CSTR storageStrategyExpireTime;
				/** 通道号 */
				CSTR channelId;
				/** [O]被分享状态 share-别人分享 auth-别人授权 shareAndAuth-别人分享和授权（saas） */
				CSTR shareStatus;
				/** [O]通道序列号,只有hub下面的通道这种带序列号的特殊通道有 */
				CSTR channelCode;
			}) channels;
			/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P */
			CSTR ability;
			/** struct of deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement_ElectricState */
			struct deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement_ElectricState {
				/** [O]电量百分比,取值范围0-100,-1设备无该电池 */
				CSTR electric;
				/** [O]碱性电池电量百分比,取值范围0-100,-1设备无该电池 */
				CSTR alkElec;
				/** [O]上报时间,yyyyMMddTHHmmss时间格式 */
				CSTR reportTime;
				/** [O]锂电池电量百分比,取值范围0-100,-1设备无该电池 */
				CSTR litElec;
				/** [O]供电类型,当type为空时,默认为battery类型 */
				CSTR type;
			} electricState;
			/** struct of deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement_WifiState */
			struct deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement_WifiState {
				/** [O]WIFI名称,如TP-link */
				CSTR ssId;
				/** [O]强度,0最弱,5最强 */
				CSTR intensity;
				/** [O]强度,单位为dbm */
				CSTR sigStrength;
				/** [O]上报时间,yyyyMMddTHHmmss时间格式 */
				CSTR reportTime;
				/** [O]当前有无连接热点,exist-有,notExist-无 */
				CSTR linkEnable;
			} wifiState;
			/** 设备序列号 */
			CSTR deviceId;
			/** [O]设备Rtsp端口,海外使用 */
			CSTR rtspPort;
			/** struct of deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement_NetworkSignal */
			struct deviceList_DeviceDetailsInfoGetByDeviceIdResponseData_DeviceListElement_NetworkSignal {
				/** [O]强度。单位为dbm */
				CSTR sigStrength;
				/** [O]类型，枚举值为2G、4G、NOSIM、NB */
				CSTR type;
				/** [O]强度。0最弱，5最强 */
				CSTR intensity;
				/** [O]上报时间,yyyyMMddTHHmmss时间格式 */
				CSTR reportTime;
			} networkSignal;
			/** 设备名称 */
			CSTR name;
			/** SD卡状态，empty-无SK卡，abnormal-异常，normal-正常，recovering-格式化中, check-盘检状态 */
			CSTR sdcardStatus;
			/** [long][O]设备拥有者id */
			int64 ownerId;
			/** [O]设备Http端口,海外使用 */
			CSTR httpPort;
			/** [O]iot设备唯一标识码 */
			CSTR imei;
			/** [O]获取实时流url的入口地址，app3.15.0拉流优化新增 */
			CSTR streamEntryAddr;
			/** [O]乐橙设备品牌信息：lechange-乐橙设备，general-通用设备 */
			CSTR brand;
			/** [O]设备高清图片 */
			CSTR HDImage;
			/** [O]表示需要对该设备进行的动作,目前仅支持setPassword,在paas侧modify字段为true并且为自己的设备时返回 */
			CSTR action;
			/** [O]入网类型：LAN：有线；Wifi：无线；SIMCard：SIM卡 */
			CSTR networkAccessType;
			/** 设备接入类型，PaaS-表示Paas程序接入、Lechange-表示乐橙非PaaS设备、Easy4IP表示Easy4IP程序设备、P2P表示P2P程序设备 */
			CSTR accessType;
			/** [O]有能力集SceneMode的才有，情景模式类型:Home---在家模式,Away---离家模式,Disarm---撤防 */
			CSTR sceneMode;
			/** [O]报警输出通道的总数量 */
			CSTR alarmOutChannels;
			/** [O]被分享和授权的权限功能列表（逗号隔开）（saas）,shareStatus字段为share，auth，shareAndAuth时关注该字段的值 */
			CSTR shareFunctions;
			/** [O]表示支持的配对模式：SmartConfig，SoundWave，SoftAP，LAN，SIMCard，QRCode，SoundWaveV2，NBIOT，配件不用返回(saas) */
			CSTR wifiConfigMode;
			/** [O]设备私有协议端口,海外使用 */
			CSTR port;
			/** [O]设备用户名（Base64(AES256加密)）（saas） */
			CSTR deviceUsername;
			/** [O]设备内网地址,限定Lorex返回 */
			CSTR deviceInnerIp;
			/** Normal-正常状态 Stint-省电状态 SStint-超级省电状态 */
			CSTR powerStatus;
			/** [O]APP展示的设备型号别名，当市场型号可修改时返回，作为客户端上展示（saas） */
			CSTR deviceModelNameAlias;
			/** [O]设备MAC地址,限定Lorex返回 */
			CSTR mac;
			/** [O]门锁状态，falseLock：假锁，beClosed：已锁，notClosed：未锁，antiLock：反锁 */
			CSTR lockState;
			/** [O]设备密码（Base64(AES256加密)）（saas） */
			CSTR devicePassword;
			/** [O]设备外部型号，海外使用，外部型号给app展示使用（saas） */
			CSTR deviceModelName;
			/** 默认为空,SDCardEncryption-SD卡加密，且未认证解密,SDCardLifeExhausted-SD卡寿命已尽,MediumAbnormal-普通异常提示格式化,SDCardNotSupportLife-SD卡不支持寿命查询,SDCheck-SD卡盘检中 */
			CSTR sdcardErrorCode;
			/** [O]报警输入通道的总数量 */
			CSTR alarmInChannels;
			/** 设备型号（saas） */
			CSTR deviceModel;
			/** [long][O]云平台业务能力集掩码使用long型数字的数组表示的设备平台能力，数字的每个二进制位会表示一项能力，具体参见 https://pc-jira.dahuatech.com/pages/viewpage.action?pageId=190218611 */
			DECLARE_LIST(int64) cloudCapacity;
			/** [O]盐值,给P2P用（saas进行Base64(AES256加密)） */
			CSTR salt;
			/** 视频通道的总数量（包含未接入的通道），网关的通道数可能为0 */
			CSTR channelNum;
			/** [O]设备私有拉流协议监听端口 */
			CSTR privateMediaPort;
			/** [O]海外设备级别分享使用，国内不使用该字段：分享给他人的标志，shareToOthers-已经分享给他人，none-没有分享给他人 */
			CSTR shareToOthers;
			/** [O]门锁状态对象,空代表门状态  door：门状态 lock：锁状态 */
			CSTR lockStateObject;
			/** [O]布防延时生效时间,单位秒;Amcrest项目 */
			CSTR delayTime;
			/** 加密模式，default表示默认加密模式, custom表示用户加密模式，用于设备上传云端录像、报警图片以及全景图等 */
			CSTR encryptMode;
			/** 设备软件版本号 */
			CSTR version;
			/** [O]海外设备级别分享使用，国内不使用该字段：被分享状态 share-别人分享 auth-别人授权 shareAndAuth-别人分享和授权（saas）,owner-自己绑定的设备 */
			CSTR shareStatus;
			/** [O]设备最后一次离线的时间，时间格式yyyyMMddTHHmmssZ时间格式 */
			CSTR lastOffLineTime;
		}) deviceList;
 
	} data;

} deviceList_DeviceDetailsInfoGetByDeviceIdResponse;

C_API deviceList_DeviceDetailsInfoGetByDeviceIdResponse *HSAPI_INIT(deviceList_DeviceDetailsInfoGetByDeviceIdResponse);

#endif
