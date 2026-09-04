/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferUpgrade_RemoteUpgradePercentGet_H_
#define _HSVIEW_CLIENT_API_transferUpgrade_RemoteUpgradePercentGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
远程设备升级进度查询

----------响应参数说明--------------
status：[string],参考[升级状态](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E5%8D%87%E7%BA%A7%2FHome.md&s=pd)
若升级中存在异常，返回错误码：
	UpgradepackageUrlError：升级地址解析出错
	AbilityNotSupport：不支持的功能
------------------------------------

参考PaaS协议：[远程设备升级进度查询](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E5%8D%87%E7%BA%A7%2F%E8%BF%9C%E7%A8%8B%E8%AE%BE%E5%A4%87%E5%8D%87%E7%BA%A7%E8%BF%9B%E5%BA%A6%E6%9F%A5%E8%AF%A2.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferUpgrade_RemoteUpgradePercentGetRequest 
{
	HsviewRequest base;

	struct transferUpgrade_RemoteUpgradePercentGetRequestData
	{
		
		/** [cstr]/device/access/device/upgrade/process */
		#define _STATIC_transferUpgrade_RemoteUpgradePercentGetRequestData_url "/device/access/device/upgrade/process"
		CSTR url;
		/** struct of transferUpgrade_RemoteUpgradePercentGetRequestData_Content */
		struct transferUpgrade_RemoteUpgradePercentGetRequestData_Content {
			/** 远程设备序列号 */
			CSTR sn;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferUpgrade_RemoteUpgradePercentGetRequest;

C_API transferUpgrade_RemoteUpgradePercentGetRequest *HSAPI_INIT(transferUpgrade_RemoteUpgradePercentGetRequest);

typedef struct transferUpgrade_RemoteUpgradePercentGetResponse 
{
	HsviewResponse base;

	struct transferUpgrade_RemoteUpgradePercentGetResponseData
	{
		
		/** 升级状态 */
		CSTR status;
		/** 当前版本 */
		CSTR version;
		/** 当前正在进行的百分比 */
		CSTR percent;
 
	} data;

} transferUpgrade_RemoteUpgradePercentGetResponse;

C_API transferUpgrade_RemoteUpgradePercentGetResponse *HSAPI_INIT(transferUpgrade_RemoteUpgradePercentGetResponse);

#endif
