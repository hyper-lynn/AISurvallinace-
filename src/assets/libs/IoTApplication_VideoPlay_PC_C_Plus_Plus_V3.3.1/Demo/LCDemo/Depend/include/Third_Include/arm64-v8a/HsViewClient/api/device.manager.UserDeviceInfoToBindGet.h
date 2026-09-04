/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_UserDeviceInfoToBindGet_H_
#define _HSVIEW_CLIENT_API_deviceManager_UserDeviceInfoToBindGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
添加设备前扫描获取设备基本信息

1、deviceCodeModel或deviceModelName存在；服务使用deviceCodeModel或deviceModelName查询是普通设备还是配件；

APP实现逻辑
1、app优先判断type是否存在，存在的话是否是配件，是配件的话，取catalog，走配件添加流程；
2、是设备的话判断bindStatus是否被绑定；
3、未绑定的话判断modelName是否存在，modelName不存在时需要用户手动选择设备型号；
4、接着判断deviceExist。。。。。。


字段说明：
    wifiConfigMode可选字段有：
        SmartConfig：SmartConfig方式
        SoundWave：声波方式
        SoftAP：软AP方式
        LAN：有线局域网
        SIMCard:SIM卡方式
		NBIOT：NB设备配网
		Bluetooth: 蓝牙锁配网
    wifiTransferMode可选字段有：
        2.4Ghz
        5Ghz

	wifiConfigModeOptional:由平台根据OMS配置的型号特定前缀特殊处理，对于OMS配置中带有optional_前缀的二维码型号，返回true使App端弹出配网方式列表让用户选择


【需要使用平台账号签名】
 */

typedef struct deviceManager_UserDeviceInfoToBindGetRequest 
{
	HsviewRequest base;

	struct deviceManager_UserDeviceInfoToBindGetRequestData
	{
		
		/** [O]APP展示的设备型号名称(产品称之为市场型号,用户自己选择设备类型时选的是市场型号) */
		CSTR deviceModelName;
		/** [O] NB iot设备唯一标识码 */
		CSTR imeiCode;
		/** [O]产品ID */
		CSTR productId;
		/** [O]用于标识设备配网能力，参见 https://pc-jira.dahuatech.com/pages/viewpage.action?pageId=97714507 */
		CSTR ncCode;
		/** [O]二维码型号 */
		CSTR deviceCodeModel;
		/** 序列号 */
		CSTR deviceId;

	} data;

} deviceManager_UserDeviceInfoToBindGetRequest;

C_API deviceManager_UserDeviceInfoToBindGetRequest *HSAPI_INIT(deviceManager_UserDeviceInfoToBindGetRequest);

typedef struct deviceManager_UserDeviceInfoToBindGetResponse 
{
	HsviewResponse base;

	struct deviceManager_UserDeviceInfoToBindGetResponseData
	{
		
		/** [O]设备品牌信息：国内：lechange-乐橙设备，general-通用设备, 海外：dahua-大华设备，general-通用设备 */
		CSTR brand;
		/** [O]设备大类【NVR/DVR/HCVR/IPC/SD/IHG/ARC】（saas返回的设备大类，基于oms配置） */
		CSTR catalog;
		/** [O]视频地址，海外3.100新增 */
		CSTR watchSetupVideoUrl;
		/** [O]设备大类（paas返回的设备上报的大类，用于开发平台，基线或者一键oem项目请使用catalog） */
		CSTR deviceType;
		/** [O]表示支持的配对模式：SmartConfig，SoundWave，SoftAP，LAN，SIMCard，QRCode，SoundWaveV2，NBIOT,iotWifi,iotLan，Bluetooth配件不用返回 */
		CSTR wifiConfigMode;
		/** [O]设备私有协议端口,海外使用 */
		CSTR port;
		/** [O]设备在数据库是否存在，exist，notExist；配件不用返回 */
		CSTR deviceExist;
		/** online-在线，offline-在线，upgrading-升级中，sleep-休眠；配件不用返回 */
		CSTR status;
		/** [O]APP展示的设备型号别名，当市场型号可修改时返回，作为客户端上展示 */
		CSTR deviceModelNameAlias;
		/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P；配件不用返回 */
		CSTR ability;
		/** [O]视频通道的总数量（包含未接入的通道），网关的通道数可能为0 */
		CSTR channelNum;
		/** [O]Tls使能开关,true-开启,false-关闭 */
		CSTR tlsEnable;
		/** [O]分类：ap，device */
		CSTR type;
		/** [O]APP展示的设备型号名称（产品称之为市场型号） */
		CSTR modelName;
		/** [O]设备私有拉流协议监听端口 */
		CSTR privateMediaPort;
		/** [O]设备上报型号 */
		CSTR deviceModel;
		/** [O]bindByMe, bindByOther, unbind；配件不用返回 */
		CSTR bindStatus;
		/** [O]所属账号，按产品需求做处理；配件不用返回 */
		CSTR userAccount;
		/** [O]设备加密端口,海外使用 */
		CSTR tlsPrivatePort;
		/** [O]true,表示可让用户自行选择可用的配网模式 */
		CSTR wifiConfigModeOptional;
		/** [O]设备Rtsp端口,海外使用 */
		CSTR rtspPort;
		/** [O]设备Http端口,海外使用 */
		CSTR httpPort;
		/** [O]设备当前是不是处于可以绑定的状态 , true-可绑定 false -不可绑定(DB12和v8i设备新增字段)，默认为true */
		CSTR canBeBind;
		/** [O]设备系列：'A'、'C'、'K'、'SE'等;服务中没有则返回空'' */
		CSTR family;
		/** [O]设备接入类型，PaaS-表示Paas程序接入、Lechange-表示乐橙非PaaS设备、Easy4IP表示Easy4IP程序设备、P2P表示P2P程序设备；配件不用返回 */
		CSTR accessType;
		/** camera-普通ipc设备；iot-iot设备 */
		CSTR deviceCategory;
		/** [O]表示无线支持频段的序列，逗号隔开：2.4Ghz,5Ghz */
		CSTR wifiTransferMode;
 
	} data;

} deviceManager_UserDeviceInfoToBindGetResponse;

C_API deviceManager_UserDeviceInfoToBindGetResponse *HSAPI_INIT(deviceManager_UserDeviceInfoToBindGetResponse);

#endif
