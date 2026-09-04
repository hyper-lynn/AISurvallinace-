/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_Wakeup_H_
#define _HSVIEW_CLIENT_API_thingsControl_Wakeup_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备唤醒

响应内容说明参考PaaS协议：[设备唤醒](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E5%94%A4%E9%86%92%E4%B8%8E%E4%BC%91%E7%9C%A0%2F&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_WakeupRequest 
{
	HsviewRequest base;

	struct thingsControl_WakeupRequestData
	{
		
		/** 设备ID */
		CSTR deviceId;

	} data;

} thingsControl_WakeupRequest;

C_API thingsControl_WakeupRequest *HSAPI_INIT(thingsControl_WakeupRequest);

typedef struct thingsControl_WakeupResponse 
{
	HsviewResponse base;

	struct thingsControl_WakeupResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsControl_WakeupResponse;

C_API thingsControl_WakeupResponse *HSAPI_INIT(thingsControl_WakeupResponse);

#endif
