/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsAp_QueryApUpgradeInfo_H_
#define _HSVIEW_CLIENT_API_thingsAp_QueryApUpgradeInfo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取配件可以升级版本和URL

注：
配件在没有可升级的版本时，upgradeVersion、upgradeDescription、upgradeUrl节点不存在或者为空串。

【需要使用平台账号签名】
 */

typedef struct thingsAp_QueryApUpgradeInfoRequest 
{
	HsviewRequest base;

	struct thingsAp_QueryApUpgradeInfoRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsAp_QueryApUpgradeInfoRequest;

C_API thingsAp_QueryApUpgradeInfoRequest *HSAPI_INIT(thingsAp_QueryApUpgradeInfoRequest);

typedef struct thingsAp_QueryApUpgradeInfoResponse 
{
	HsviewResponse base;

	struct thingsAp_QueryApUpgradeInfoResponseData
	{
		
		/** [O]配件升级包URL */
		CSTR upgradeUrl;
		/** [O]配件可升级版本的描述信息 */
		CSTR upgradeDescription;
		/** [int]配件的在线状态：1-在线  0-离线（在线才能升级，首页在线状态可能不及时） */
		int apStatus;
		/** [O]配件可升级版本 */
		CSTR upgradeVersion;
		/** 配件当前版本信息 */
		CSTR apVersion;
 
	} data;

} thingsAp_QueryApUpgradeInfoResponse;

C_API thingsAp_QueryApUpgradeInfoResponse *HSAPI_INIT(thingsAp_QueryApUpgradeInfoResponse);

#endif
