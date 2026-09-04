/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsAp_ExecuteApUpgrade_H_
#define _HSVIEW_CLIENT_API_thingsAp_ExecuteApUpgrade_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
配件升级

参考PaaS协议：[配件升级](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%93%8D%E4%BD%9C%E9%85%8D%E4%BB%B6%2F%E9%85%8D%E4%BB%B6%E5%8D%87%E7%BA%A7.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsAp_ExecuteApUpgradeRequest 
{
	HsviewRequest base;

	struct thingsAp_ExecuteApUpgradeRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** 设备升级包的URL，http://202.30.1.254/device-1.0.002.rar */
		CSTR packageUrl;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsAp_ExecuteApUpgradeRequest;

C_API thingsAp_ExecuteApUpgradeRequest *HSAPI_INIT(thingsAp_ExecuteApUpgradeRequest);

typedef struct thingsAp_ExecuteApUpgradeResponse 
{
	HsviewResponse base;

	struct thingsAp_ExecuteApUpgradeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsAp_ExecuteApUpgradeResponse;

C_API thingsAp_ExecuteApUpgradeResponse *HSAPI_INIT(thingsAp_ExecuteApUpgradeResponse);

#endif
