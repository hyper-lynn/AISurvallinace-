/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetZBDeviceCountDown_H_
#define _HSVIEW_CLIENT_API_SetZBDeviceCountDown_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置配件的倒计时。
【需要使用平台账号签名】
 */

typedef struct SetZBDeviceCountDownRequest 
{
	HsviewRequest base;

	struct SetZBDeviceCountDownRequestData
	{
		
		/** [int]默认为0，表示设置倒计时；若为1，表示取消这个倒计时。 */
		int cancel;
		/** 切换为什么状态，on或off */
		CSTR operation;
		/** 倒计时时间，格式如2014-08-31 22:10:15 */
		CSTR cdTime;
		/** 通道号 */
		CSTR channelId;
		/** 盒子的设备ID */
		CSTR deviceId;

	} data;

} SetZBDeviceCountDownRequest;

C_API SetZBDeviceCountDownRequest *HSAPI_INIT(SetZBDeviceCountDownRequest);

typedef struct SetZBDeviceCountDownResponse 
{
	HsviewResponse base;

	struct SetZBDeviceCountDownResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetZBDeviceCountDownResponse;

C_API SetZBDeviceCountDownResponse *HSAPI_INIT(SetZBDeviceCountDownResponse);

#endif
