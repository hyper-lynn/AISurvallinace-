/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_Wakeup_H_
#define _HSVIEW_CLIENT_API_transferDevice_Wakeup_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备唤醒

参考PaaS协议：[设备唤醒](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E5%94%A4%E9%86%92%E4%B8%8E%E4%BC%91%E7%9C%A0%2F%E8%AE%BE%E5%A4%87%E5%94%A4%E9%86%92.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_WakeupRequest 
{
	HsviewRequest base;

	struct transferDevice_WakeupRequestData
	{
		
		/** [cstr]/device/wakeup */
		#define _STATIC_transferDevice_WakeupRequestData_url "/device/wakeup"
		CSTR url;
		/** struct of transferDevice_WakeupRequestData_Content */
		struct transferDevice_WakeupRequestData_Content {
			/** [O]通道id */
			CSTR chan;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_WakeupRequest;

C_API transferDevice_WakeupRequest *HSAPI_INIT(transferDevice_WakeupRequest);

typedef struct transferDevice_WakeupResponse 
{
	HsviewResponse base;

	struct transferDevice_WakeupResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_WakeupResponse;

C_API transferDevice_WakeupResponse *HSAPI_INIT(transferDevice_WakeupResponse);

#endif
