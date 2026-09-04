/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227286, Author: 251672, Date: 2024-09-02 17:23:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UnBindDeviceInfo_H_
#define _LC_OPENAPI_CLIENT_UnBindDeviceInfo_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取未绑定的设备信息
 */

typedef struct UnBindDeviceInfoRequest 
{
	LCOpenApiRequest base;

	struct UnBindDeviceInfoRequestData
	{
		
		/** 设备市场型号 */
		CSTR deviceModelName;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备配网能力 */
		CSTR ncCode;
		/** 设备ID */
		CSTR deviceId;
		/** [cstr]unBindDeviceInfo */
		#define _STATIC_UnBindDeviceInfoRequestData_method "unBindDeviceInfo"
		CSTR method;
		/** 设备二维码型号 */
		CSTR deviceCodeModel;

	} data;

} UnBindDeviceInfoRequest;

C_API UnBindDeviceInfoRequest *LCOPENAPI_INIT(UnBindDeviceInfoRequest);

typedef struct UnBindDeviceInfoResponse 
{
	LCOpenApiResponse base;

	struct UnBindDeviceInfoResponseData
	{
		
		/** NVR */
		CSTR catalog;
		/** 设备类型 */
		CSTR deviceType;
		/** 设备支持的配对模式：SmartConfig,SoundWave,SoftAP,LAN,SIMCard,QRCode,SoundWaveV2,NBIOT,Bluetooth配件不返回 */
		CSTR wifiConfigMode;
		/** 37777 */
		CSTR port;
		/** exist */
		CSTR deviceExist;
		/** online */
		CSTR status;
		/** struct of UnBindDeviceInfoResponseData_DeviceModelImages */
		struct UnBindDeviceInfoResponseData_DeviceModelImages {
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
		/** 554 */
		CSTR rtspPort;
		/** 基础设备类型 */
		CSTR deviceCodeModelBase;
		/** 设备市场型号 */
		CSTR deviceModelName;
		/** device */
		CSTR type;
		/**  */
		CSTR modelName;
		/** [bool]设备是否支持用户自选可用的配网方式：true:支持自选,false:不支持自选 */
		BOOL wifiConfigModeOptional;
		/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见乐橙开放平台设备协议 */
		CSTR ability;
		/** unbind */
		CSTR bindStatus;
		/** 设备无线支持频段的序列：2.4Ghz,5Ghz */
		CSTR wifiTransferMode;
		/** 设备上报型号 */
		CSTR deviceCodeModel;
		/** 0 */
		CSTR privateMediaPort;
		/** xxx@qq.com */
		CSTR owner;
		/** IP Camera */
		CSTR deviceModel;
		/** 1 */
		CSTR channelNum;
		/** 37778 */
		CSTR tlsPrivatePort;
		/** PaaS */
		CSTR accessType;
		/** IPC-WL46AP:01:02:13:89:41:00:01:10:01:01:04:3E8:00:00:00:00:00:01:00:00:200 */
		CSTR hwId;
		/** 80 */
		CSTR httpPort;
 
	} data;

} UnBindDeviceInfoResponse;

C_API UnBindDeviceInfoResponse *LCOPENAPI_INIT(UnBindDeviceInfoResponse);

#endif
