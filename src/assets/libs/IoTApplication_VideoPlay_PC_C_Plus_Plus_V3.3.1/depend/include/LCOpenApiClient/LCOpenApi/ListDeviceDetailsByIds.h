/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227286, Author: 251672, Date: 2024-09-02 17:23:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ListDeviceDetailsByIds_H_
#define _LC_OPENAPI_CLIENT_ListDeviceDetailsByIds_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
批量根据设备序列号，获取设备的详细信息

 */

typedef struct ListDeviceDetailsByIdsRequest 
{
	LCOpenApiRequest base;

	struct ListDeviceDetailsByIdsRequestData
	{
		
		/** define a list with struct of ListDeviceDetailsByIdsRequestData_DeviceListElement */
		DECLARE_LIST(struct ListDeviceDetailsByIdsRequestData_DeviceListElement
		{
			/** 通道编码 */
			DECLARE_LIST(CSTR) channelId;
			/** 设备编码 */
			CSTR deviceId;
		}) deviceList;
		/** 授权token(userToken或accessToken) */
		CSTR token;

	} data;

} ListDeviceDetailsByIdsRequest;

C_API ListDeviceDetailsByIdsRequest *LCOPENAPI_INIT(ListDeviceDetailsByIdsRequest);

typedef struct ListDeviceDetailsByIdsResponse 
{
	LCOpenApiResponse base;

	struct ListDeviceDetailsByIdsResponseData
	{
		
		/** [int]本次查询到的设备通道数 */
		int count;
		/** define a list with struct of ListDeviceDetailsByIdsResponseData_DeviceListElement */
		DECLARE_LIST(struct ListDeviceDetailsByIdsResponseData_DeviceListElement
		{
			/** 设备来源，paas:来自大华，lc:来自乐橙 */
			CSTR sourceType;
			/** 设备大类：NVR/DVR/HCVR/IPC/SD/IHG/ARC */
			CSTR catalog;
			/** playToken秘钥 */
			CSTR playTokenKey;
			/** 设备安全码 */
			CSTR deviceSafeCode;
			/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps */
			struct ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps {
				/** [bool] */
				BOOL SupDisarmLinkageAlarmBellEnable;
				/** [bool]CMS相关配置 */
				BOOL SupCMS;
				/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupSpeakerFeaturesStruct */
				struct ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupSpeakerFeaturesStruct {
					/** [bool] */
					BOOL Support;
				} SupSpeakerFeatures;
				/** [bool]Led开关使能 */
				BOOL SupDisableLed;
				/** [bool] */
				BOOL SupUpLoadCloud;
				/** [int]SIM卡类型 */
				int SupSIMType;
				/** [bool]衰退模式设置 */
				BOOL SupAttenuationMode;
				/** [bool]流量统计 */
				BOOL SupFluxStat;
				/** [bool] */
				BOOL SupCard;
				/** [bool]SIA相关配置 */
				BOOL SupSIA;
				/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupAlarmUserManagerFeaturesStruct */
				struct ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupAlarmUserManagerFeaturesStruct {
					/** [bool] */
					BOOL UserNumber;
					/** 报警权限 */
					DECLARE_LIST(CSTR) AuthorityList;
				} SupAlarmUserManagerFeatures;
				/** [bool] */
				BOOL SupLog;
				/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupPowerFeaturesStruct */
				struct ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupPowerFeaturesStruct {
					/** [bool] */
					BOOL SupPowerFaultDelay;
				} SupPowerFeatures;
				/** [bool] */
				BOOL SupDelayArming;
				/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupTriggerAlarmFeaturesStruct */
				struct ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupTriggerAlarmFeaturesStruct {
					/** 支持多选报警类型 */
					DECLARE_LIST(CSTR) SupAlarmType;
					/** [bool]支持APP紧急报警按钮 */
					BOOL Support;
					/** [bool]支持GPS信息功能携带 */
					BOOL SupGPSInfo;
				} SupTriggerAlarmFeatures;
				/** [bool] */
				BOOL SupTriggerAlarm;
				/** [bool] */
				BOOL enable;
				/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupCameraFeaturesStruct */
				struct ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupCameraFeaturesStruct {
					/** [int]最大功能个数 */
					int MaxNum;
					/** [int] */
					int LogicChannelStart;
					/** [bool] */
					BOOL Access;
					/** 最大分辨率 */
					CSTR MaxResolutions;
				} SupCameraFeatures;
				/** [bool]临时停用功能 */
				BOOL SupDisableSensor;
				/** [bool] */
				BOOL SupSIARetransmissionTimes;
				/** 支持的用户管理 */
				DECLARE_LIST(CSTR) SupUserManager;
				/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupVoiceFileFeaturesStruct */
				struct ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupVoiceFileFeaturesStruct {
					/** [bool]是否支持设备语音语言 */
					BOOL Support;
					/** [bool] 是否支持上传语音文件 */
					BOOL SupUpload;
				} SupVoiceFileFeatures;
				/** [bool]网络优先级功能 */
				BOOL SupChangeNet;
				/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupMultiLanguageFeaturesStruct */
				struct ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupMultiLanguageFeaturesStruct {
					/** [bool]是否支持多语言配置 */
					BOOL Support;
				} SupMultiLanguageFeatures;
				/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupWifiStruct */
				struct ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupWifiStruct {
					/** [bool]WiFi相关配置 */
					BOOL Enable;
				} SupWifi;
				/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupPrivateFeaturesStruct */
				struct ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupPrivateFeaturesStruct {
					/** [bool] */
					BOOL EventVerification;
					/** [bool] */
					BOOL ManualTest;
					/** [bool] */
					BOOL PeriodicTest;
					/** [bool] */
					BOOL EventTypeList;
				} SupPrivateFeatures;
				/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupMobileFeaturesStruct */
				struct ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupMobileFeaturesStruct {
					/** 支持短信格式选择 */
					DECLARE_LIST(CSTR) SupSMSFormat;
					/** [bool] */
					BOOL Support;
					/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupMobileFeaturesStruct_SupCallLinkagePolicyFeaturesStruct */
					struct ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupMobileFeaturesStruct_SupCallLinkagePolicyFeaturesStruct {
						/** [bool]是否支持报警联动电话配置 */
						BOOL Support;
					} SupCallLinkagePolicyFeatures;
					/** [bool] */
					BOOL SupPINCode;
					/** [bool] */
					BOOL SupSMSMultiLanguage;
					/** [bool] */
					BOOL SupCellularRoaming;
					/** [bool] */
					BOOL SupAudioPlay;
				} SupMobileFeatures;
				/** [int]能力集大版本 */
				int FunctionVerison;
				/** 支持的探测器类型 */
				DECLARE_LIST(CSTR) SupSensorType;
				/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupSIAFeaturesStruct */
				struct ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupSIAFeaturesStruct {
					/** [bool] */
					BOOL ManualTest;
					/** [bool] */
					BOOL ModifyByRPC;
					/** [bool] */
					BOOL EventVerification;
					/** [bool] */
					BOOL PeriodicTest;
					/** [int] */
					int MaxCenterCount;
					/** 协议类型 */
					DECLARE_LIST(CSTR) ProtocolType;
					/** [bool] */
					BOOL DNS;
					/** 连接类型 */
					DECLARE_LIST(CSTR) SupConnectType;
					/** [bool] */
					BOOL RetransmissionDeadline;
				} SupSIAFeatures;
				/** [bool] */
				BOOL SupSIARetransmissionDeadline;
				/** [bool] */
				BOOL supportBeepOnDelay;
				/** [int]支持系统检测细化项 */
				int SupArmCheck;
				/** 版本号 */
				CSTR Version;
				/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupTalkbackFeaturesStruct */
				struct ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupTalkbackFeaturesStruct {
					/** [bool]支持对讲功能 */
					BOOL Support;
				} SupTalkbackFeatures;
				/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupSystemStatusCheckFeaturesStruct */
				struct ListDeviceDetailsByIdsResponseData_DeviceListElement_Caps_SupSystemStatusCheckFeaturesStruct {
					/** [bool]是否支持系统检查 */
					BOOL Support;
					/** [bool]是否支持系统检查带强制布防 */
					BOOL ArmingWithFault;
				} SupSystemStatusCheckFeatures;
				/** 默认检测集合 */
				DECLARE_LIST(CSTR) SupFaultDetectionItems;
				/** [bool] */
				BOOL SupPINCode;
				/** [bool] */
				BOOL SupIndexInfo;
			} caps;
			/** tls私有端口 */
			CSTR tlsPrivatePort;
			/** [int] 0表示没托管能力，1表示有托管能力 */
			int supportAsyncCheck;
			/** 设备版本号 */
			CSTR deviceVersion;
			/** 零通道号 */
			CSTR MultiPreview;
			/** 0设备的主辅码流 */
			CSTR deviceStreamEnable;
			/** 信号类型2G、4G、NOSIM */
			CSTR simType;
			/** [bool]是否支持tls */
			BOOL tlsEnable;
			/** define a list with struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_ChannelListElement */
			DECLARE_LIST(struct ListDeviceDetailsByIdsResponseData_DeviceListElement_ChannelListElement
			{
				/** 云存储状态，notExist：未开通套餐，using：开通云存储且没有过期，expired：套餐过期 */
				CSTR csStatus;
				/** define a list with struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_ChannelListElement_ResolutionsElement */
				DECLARE_LIST(struct ListDeviceDetailsByIdsResponseData_DeviceListElement_ChannelListElement_ResolutionsElement
				{
					/** [int]码流类型 */
					int streamType;
					/** 分辨率名称 */
					CSTR name;
					/** [bool]是否是当前分辨率 */
					BOOL enable;
					/** 分辨率模式名称 */
					CSTR mode;
					/** [int]分辨率编号 */
					int imageSize;
				}) resolutions;
				/** 通道状态，online：在线，offline：离线，sleep：休眠，upgrading升级中 */
				CSTR channelStatus;
				/** 0通道的主辅码流 */
				CSTR channelStreamEnable;
				/** 隐私模式开关相机状态，on：开，off：关 */
				CSTR cameraStatus;
				/** 通道名称 */
				CSTR channelName;
				/** on-打开，off-关闭 */
				CSTR trackFollowStatus;
				/** [int]单元类型 */
				int unitType;
				/** 通道能力集，逗号隔开 */
				CSTR channelAbility;
				/** 设备通道封面图，新设备可能不存在封面图，可上传设备通道封面图或者刷新设备封面图 */
				CSTR channelPicUrl;
				/** 通道号 */
				CSTR channelId;
				/** 分享权限下的权限字符串，逗号隔开 */
				CSTR shareFunctions;
				/** 通道最后离线时间 */
				CSTR lastOffLineTime;
			}) channelList;
			/** p2p端口 */
			CSTR p2pPort;
			/** 加密后的信息，APP需要用设备编码解密 */
			CSTR playInfo;
			/** 设备序列号 */
			CSTR deviceId;
			/** rtsp拉流端口 */
			CSTR rtspPort;
			/** on-打开，off-关闭 */
			CSTR trackFollowStatus;
			/** SD卡状态 */
			CSTR sdcardStatus;
			/** 设备接入类型，PaaS-表示Paas程序接入、Lechange-表示乐橙非PaaS设备、Easy4IP表示Easy4IP程序设备、P2P表示P2P程序设备 */
			CSTR accessType;
			/** 设备品牌信息：lechange-乐橙设备，general-通用设备 */
			CSTR brand;
			/** 设备能力集，逗号隔开 */
			CSTR deviceAbility;
			/** 权限类型：bind/share */
			CSTR source;
			/** 入网方式，LAN:有线  Wifi:无线 SIMCard:SIM卡 */
			CSTR netType;
			/** 强度 单位为dbm */
			CSTR simSigStrength;
			/** 强度 0最弱，5最强 */
			CSTR simIntensity;
			/** [bool]是否为子设备 */
			BOOL isSubDevice;
			/** WiFi配置模式，逗号隔开 */
			CSTR wifiConfigMode;
			/** 设备名称 */
			CSTR deviceName;
			/** [bool]是否支持WiFi配置模式 */
			BOOL wifiConfigModeOptional;
			/** netsdk私有协议拉流端口 */
			CSTR port;
			/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_DeviceModelImages */
			struct ListDeviceDetailsByIdsResponseData_DeviceListElement_DeviceModelImages {
				/** 设备图片url */
				CSTR commonList;
				/** 设备图片url */
				CSTR deviceManagerManualDetails;
				/** 设备图片url */
				CSTR deviceManagerWork;
				/** 设备图片url */
				CSTR messageList;
				/** 设备图片url */
				CSTR deviceManagerAddDevice;
			} deviceModelImages;
			/** [int]是否强制升级 */
			int isForcedUpgrade;
			/** 设备加密模式：0-设备默认加密 1-用户自定义加密 */
			CSTR encryptMode;
			/** 设备可升级到的版本号 */
			CSTR deviceUpgradeVersion;
			/** 设备密码 */
			CSTR devicePassword;
			/** [bool]设备软件程序是否有新版本可以升级 */
			BOOL canBeUpgrade;
			/** [bool] */
			BOOL multiFlag;
			/** 设备最后离线时间 */
			CSTR lastOffLineTime;
			/** 设备型号 */
			CSTR deviceModel;
			/** [int]当前使用卡的类型，0:内置卡 1:外置卡 */
			int currentSim;
			/** 盐值 */
			CSTR salt;
			/** define a list with struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_SimInfoElement */
			DECLARE_LIST(struct ListDeviceDetailsByIdsResponseData_DeviceListElement_SimInfoElement
			{
				/** 集成电路卡识别码即SIM卡卡号 */
				CSTR iccid;
				/** 手机序列号 */
				CSTR imei;
				/** [int]支持双卡时当前卡类型，0:内置卡 1:外置卡 */
				int type;
			}) simInfo;
			/** [int]通道数量 */
			int channelNum;
			/** define a list with struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_AplistElement */
			DECLARE_LIST(struct ListDeviceDetailsByIdsResponseData_DeviceListElement_AplistElement
			{
				/** 配件id */
				CSTR apId;
				/** 配件类型 */
				CSTR apType;
				/** 配件名称 */
				CSTR apName;
			}) aplist;
			/** http私有协议拉流端口 */
			CSTR httpPort;
			/** 设备播放码，opensdk使用 */
			CSTR playToken;
			/** WiFi可转换模式，逗号隔开 */
			CSTR wifiTransferMode;
			/** struct of ListDeviceDetailsByIdsResponseData_DeviceListElement_VoiceFileInfo */
			struct ListDeviceDetailsByIdsResponseData_DeviceListElement_VoiceFileInfo {
				/** 设备语音语言 */
				CSTR language;
				/** 设备语音包版本 */
				CSTR version;
			} voiceFileInfo;
			/** 设备用户名 */
			CSTR deviceUsername;
			/** 设备状态，online：在线，offline：离线，sleep：休眠，upgrading升级中 */
			CSTR deviceStatus;
		}) deviceList;
 
	} data;

} ListDeviceDetailsByIdsResponse;

C_API ListDeviceDetailsByIdsResponse *LCOPENAPI_INIT(ListDeviceDetailsByIdsResponse);

#endif
