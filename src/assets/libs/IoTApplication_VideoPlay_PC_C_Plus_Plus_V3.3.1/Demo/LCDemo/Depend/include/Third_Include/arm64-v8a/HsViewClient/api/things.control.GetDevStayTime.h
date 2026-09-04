/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_GetDevStayTime_H_
#define _HSVIEW_CLIENT_API_thingsControl_GetDevStayTime_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备逗留时长

type说明参考PaaS协议：[获取设备逗留时长](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E9%80%97%E7%95%99%E6%97%B6%E9%95%BF%2F%E8%8E%B7%E5%8F%96%E9%80%97%E7%95%99%E6%97%B6%E9%95%BF.md&s=pd)
备注：
错误码：13003，表示设备不具备该功能。
【需要使用平台账号签名】
 */

typedef struct thingsControl_GetDevStayTimeRequest 
{
	HsviewRequest base;

	struct thingsControl_GetDevStayTimeRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsControl_GetDevStayTimeRequest;

C_API thingsControl_GetDevStayTimeRequest *HSAPI_INIT(thingsControl_GetDevStayTimeRequest);

typedef struct thingsControl_GetDevStayTimeResponse 
{
	HsviewResponse base;

	struct thingsControl_GetDevStayTimeResponseData
	{
		
		/** 徘徊报警使能开关，on-开启 off-关闭 */
		CSTR hoveringAlarm;
		/** [int] 逗留时长，单位S */
		int stayTime;
 
	} data;

} thingsControl_GetDevStayTimeResponse;

C_API thingsControl_GetDevStayTimeResponse *HSAPI_INIT(thingsControl_GetDevStayTimeResponse);

#endif
