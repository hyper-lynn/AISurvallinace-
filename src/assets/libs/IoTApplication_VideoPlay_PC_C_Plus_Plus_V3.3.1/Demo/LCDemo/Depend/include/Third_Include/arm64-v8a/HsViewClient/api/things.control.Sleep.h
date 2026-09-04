/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_Sleep_H_
#define _HSVIEW_CLIENT_API_thingsControl_Sleep_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备休眠

响应内容说明参考PaaS协议：[设备休眠](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E5%94%A4%E9%86%92%E4%B8%8E%E4%BC%91%E7%9C%A0%2F&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_SleepRequest 
{
	HsviewRequest base;

	struct thingsControl_SleepRequestData
	{
		
		/** 设备ID */
		CSTR deviceId;

	} data;

} thingsControl_SleepRequest;

C_API thingsControl_SleepRequest *HSAPI_INIT(thingsControl_SleepRequest);

typedef struct thingsControl_SleepResponse 
{
	HsviewResponse base;

	struct thingsControl_SleepResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsControl_SleepResponse;

C_API thingsControl_SleepResponse *HSAPI_INIT(thingsControl_SleepResponse);

#endif
