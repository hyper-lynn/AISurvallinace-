/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceList_DeviceBasicInfoGetForOpenPlatform_H_
#define _HSVIEW_CLIENT_API_deviceList_DeviceBasicInfoGetForOpenPlatform_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
批量根据设备序列号获取设备的端口信息。
注：该接口暂不进行用户校验，只给开放平台使用。

【需要使用平台账号签名】
 */

typedef struct deviceList_DeviceBasicInfoGetForOpenPlatformRequest 
{
	HsviewRequest base;

	struct deviceList_DeviceBasicInfoGetForOpenPlatformRequestData
	{
		
		/** 设备序列号数组,多个用,分隔 */
		DECLARE_LIST(CSTR) deviceIds;

	} data;

} deviceList_DeviceBasicInfoGetForOpenPlatformRequest;

C_API deviceList_DeviceBasicInfoGetForOpenPlatformRequest *HSAPI_INIT(deviceList_DeviceBasicInfoGetForOpenPlatformRequest);

typedef struct deviceList_DeviceBasicInfoGetForOpenPlatformResponse 
{
	HsviewResponse base;

	struct deviceList_DeviceBasicInfoGetForOpenPlatformResponseData
	{
		
		/** define a list with struct of deviceList_DeviceBasicInfoGetForOpenPlatformResponseData_DeviceListElement */
		DECLARE_LIST(struct deviceList_DeviceBasicInfoGetForOpenPlatformResponseData_DeviceListElement
		{
			/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P */
			CSTR ability;
			/** [O]设备Rtsp端口 */
			CSTR rtspPort;
			/** 设备序列号 */
			CSTR deviceId;
			/** 视频通道的总数量（包含未接入的通道） */
			CSTR channelNum;
			/** [O]设备私有协议端口 */
			CSTR port;
			/** 设备软件版本号 */
			CSTR version;
			/** 设备名称 */
			CSTR name;
			/** 设备状态，online-在线 offline-在线 upgrading-升级中 sleep-休眠 */
			CSTR status;
			/** 设备接入类型，PaaS-表示Paas程序接入、Lechange-表示乐橙非PaaS设备、Easy4IP表示Easy4IP程序设备、P2P表示P2P程序设备 */
			CSTR accessType;
			/** 是否有新版本可以升级 */
			CSTR canBeUpgrade;
			/** 设备型号 */
			CSTR deviceModel;
		}) deviceList;
 
	} data;

} deviceList_DeviceBasicInfoGetForOpenPlatformResponse;

C_API deviceList_DeviceBasicInfoGetForOpenPlatformResponse *HSAPI_INIT(deviceList_DeviceBasicInfoGetForOpenPlatformResponse);

#endif
