/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsEnable_TransferGetEnable_H_
#define _HSVIEW_CLIENT_API_thingsEnable_TransferGetEnable_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备功能开关。
鱼眼使能:heatMap

type说明参考PaaS协议：[设置设备功能开关](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2F%E8%A7%86%E9%A2%91%E8%83%BD%E5%8A%9B-%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2F&s=pd)
备注：
错误码：13003，表示设备不具备该功能。
【需要使用平台账号签名】
 */

typedef struct thingsEnable_TransferGetEnableRequest 
{
	HsviewRequest base;

	struct thingsEnable_TransferGetEnableRequestData
	{
		
		/** [O]通道号 */
		CSTR channelId;
		/** smartTrack,类型 */
		CSTR type;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsEnable_TransferGetEnableRequest;

C_API thingsEnable_TransferGetEnableRequest *HSAPI_INIT(thingsEnable_TransferGetEnableRequest);

typedef struct thingsEnable_TransferGetEnableResponse 
{
	HsviewResponse base;

	struct thingsEnable_TransferGetEnableResponseData
	{
		
		/** on打开，off关闭 */
		CSTR enable;
 
	} data;

} thingsEnable_TransferGetEnableResponse;

C_API thingsEnable_TransferGetEnableResponse *HSAPI_INIT(thingsEnable_TransferGetEnableResponse);

#endif
