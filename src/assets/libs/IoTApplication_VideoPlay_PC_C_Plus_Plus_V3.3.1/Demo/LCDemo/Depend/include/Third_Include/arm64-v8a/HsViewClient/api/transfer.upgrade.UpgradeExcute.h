/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferUpgrade_UpgradeExcute_H_
#define _HSVIEW_CLIENT_API_transferUpgrade_UpgradeExcute_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备升级

参考PaaS协议：[设备升级](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E5%8D%87%E7%BA%A7%2F%E8%AE%BE%E5%A4%87%E5%8D%87%E7%BA%A7.md&s=pd)
code:13010 (低电量拒绝升级(带电池设备) 详见[错误码](http://paas.dahuatech.com/wiki/?p=%2FSaaS%2F%E9%94%99%E8%AF%AF%E7%A0%81.md&s=pj)

【需要使用平台账号签名】
 */

typedef struct transferUpgrade_UpgradeExcuteRequest 
{
	HsviewRequest base;

	struct transferUpgrade_UpgradeExcuteRequestData
	{
		
		/** [cstr]/device/upgrade/excute */
		#define _STATIC_transferUpgrade_UpgradeExcuteRequestData_url "/device/upgrade/excute"
		CSTR url;
		/** struct of transferUpgrade_UpgradeExcuteRequestData_Content */
		struct transferUpgrade_UpgradeExcuteRequestData_Content {
			/** 设备升级包的URL */
			CSTR packageUrl;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferUpgrade_UpgradeExcuteRequest;

C_API transferUpgrade_UpgradeExcuteRequest *HSAPI_INIT(transferUpgrade_UpgradeExcuteRequest);

typedef struct transferUpgrade_UpgradeExcuteResponse 
{
	HsviewResponse base;

	struct transferUpgrade_UpgradeExcuteResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferUpgrade_UpgradeExcuteResponse;

C_API transferUpgrade_UpgradeExcuteResponse *HSAPI_INIT(transferUpgrade_UpgradeExcuteResponse);

#endif
