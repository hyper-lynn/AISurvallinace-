/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_StopSiren_H_
#define _HSVIEW_CLIENT_API_thingsControl_StopSiren_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
停止警笛。

-------------请求参数说明-------------
deviceId: [string]，设备序列号
--------------

参考PaaS协议：[停止警笛](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%AD%A6%E7%AC%9B%E6%93%8D%E4%BD%9C%2F%E5%81%9C%E6%AD%A2%E8%AD%A6%E7%AC%9B.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_StopSirenRequest 
{
	HsviewRequest base;

	struct thingsControl_StopSirenRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsControl_StopSirenRequest;

C_API thingsControl_StopSirenRequest *HSAPI_INIT(thingsControl_StopSirenRequest);

typedef struct thingsControl_StopSirenResponse 
{
	HsviewResponse base;

	struct thingsControl_StopSirenResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsControl_StopSirenResponse;

C_API thingsControl_StopSirenResponse *HSAPI_INIT(thingsControl_StopSirenResponse);

#endif
