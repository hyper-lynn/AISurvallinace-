/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_SetDevStayTime_H_
#define _HSVIEW_CLIENT_API_thingsControl_SetDevStayTime_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备逗留时长

type说明参考PaaS协议：[逗留时长设置](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E9%80%97%E7%95%99%E6%97%B6%E9%95%BF%2F%E8%AE%BE%E7%BD%AE%E9%80%97%E7%95%99%E6%97%B6%E9%95%BF.md&s=pd)
错误码：13003，表示设备不具备该功能。
【需要使用平台账号签名】
 */

typedef struct thingsControl_SetDevStayTimeRequest 
{
	HsviewRequest base;

	struct thingsControl_SetDevStayTimeRequestData
	{
		
		/** [int]逗留时长 单位S */
		int stayTime;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsControl_SetDevStayTimeRequest;

C_API thingsControl_SetDevStayTimeRequest *HSAPI_INIT(thingsControl_SetDevStayTimeRequest);

typedef struct thingsControl_SetDevStayTimeResponse 
{
	HsviewResponse base;

	struct thingsControl_SetDevStayTimeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsControl_SetDevStayTimeResponse;

C_API thingsControl_SetDevStayTimeResponse *HSAPI_INIT(thingsControl_SetDevStayTimeResponse);

#endif
