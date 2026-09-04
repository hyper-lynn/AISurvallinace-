/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferUpgrade_RemoteUpgradeExcute_H_
#define _HSVIEW_CLIENT_API_transferUpgrade_RemoteUpgradeExcute_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
远程设备升级

参考PaaS协议：[远程设备升级](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E5%8D%87%E7%BA%A7%2F%E8%BF%9C%E7%A8%8B%E8%AE%BE%E5%A4%87%E5%8D%87%E7%BA%A7.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferUpgrade_RemoteUpgradeExcuteRequest 
{
	HsviewRequest base;

	struct transferUpgrade_RemoteUpgradeExcuteRequestData
	{
		
		/** [cstr]/device/access/device/upgrade/excute */
		#define _STATIC_transferUpgrade_RemoteUpgradeExcuteRequestData_url "/device/access/device/upgrade/excute"
		CSTR url;
		/** struct of transferUpgrade_RemoteUpgradeExcuteRequestData_Content */
		struct transferUpgrade_RemoteUpgradeExcuteRequestData_Content {
			/** 远程设备序列号 */
			CSTR sn;
			/** 设备升级包的URL */
			CSTR packageUrl;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferUpgrade_RemoteUpgradeExcuteRequest;

C_API transferUpgrade_RemoteUpgradeExcuteRequest *HSAPI_INIT(transferUpgrade_RemoteUpgradeExcuteRequest);

typedef struct transferUpgrade_RemoteUpgradeExcuteResponse 
{
	HsviewResponse base;

	struct transferUpgrade_RemoteUpgradeExcuteResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferUpgrade_RemoteUpgradeExcuteResponse;

C_API transferUpgrade_RemoteUpgradeExcuteResponse *HSAPI_INIT(transferUpgrade_RemoteUpgradeExcuteResponse);

#endif
