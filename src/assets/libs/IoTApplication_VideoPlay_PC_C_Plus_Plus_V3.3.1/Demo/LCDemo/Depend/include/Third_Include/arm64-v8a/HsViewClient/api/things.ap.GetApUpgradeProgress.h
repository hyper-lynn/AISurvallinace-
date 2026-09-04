/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsAp_GetApUpgradeProgress_H_
#define _HSVIEW_CLIENT_API_thingsAp_GetApUpgradeProgress_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
配件升级进度查询

status：升级状态，取值如下：
idle ： 没在升级
downloading ： 正在下载升级包
upgrading ： 升级中

参考PaaS协议：[配件升级进度查询](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%93%8D%E4%BD%9C%E9%85%8D%E4%BB%B6%2F%E8%8E%B7%E5%8F%96%E9%85%8D%E4%BB%B6%E5%8D%87%E7%BA%A7%E8%BF%9B%E5%BA%A6.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsAp_GetApUpgradeProgressRequest 
{
	HsviewRequest base;

	struct thingsAp_GetApUpgradeProgressRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsAp_GetApUpgradeProgressRequest;

C_API thingsAp_GetApUpgradeProgressRequest *HSAPI_INIT(thingsAp_GetApUpgradeProgressRequest);

typedef struct thingsAp_GetApUpgradeProgressResponse 
{
	HsviewResponse base;

	struct thingsAp_GetApUpgradeProgressResponseData
	{
		
		/** 升级状态 */
		CSTR status;
		/** [O][int]进度百分比 */
		CSTR percent;
		/** [O]当前版本 */
		CSTR version;
 
	} data;

} thingsAp_GetApUpgradeProgressResponse;

C_API thingsAp_GetApUpgradeProgressResponse *HSAPI_INIT(thingsAp_GetApUpgradeProgressResponse);

#endif
