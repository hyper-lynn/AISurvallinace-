/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferUpgrade_UpgradePercentGet_H_
#define _HSVIEW_CLIENT_API_transferUpgrade_UpgradePercentGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备升级进度查询

----------响应参数说明--------------
status：[string],参考[升级状态](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E5%8D%87%E7%BA%A7%2FHome.md&s=pd)
若升级中存在异常，返回错误码：
	UpgradepackageUrlError：升级地址解析出错
	AbilityNotSupport：不支持的功能
------------------------------------

参考PaaS协议：[设备升级进度查询](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E5%8D%87%E7%BA%A7%2F%E8%8E%B7%E5%8F%96%E5%8D%87%E7%BA%A7%E8%BF%9B%E5%BA%A6.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferUpgrade_UpgradePercentGetRequest 
{
	HsviewRequest base;

	struct transferUpgrade_UpgradePercentGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/upgrade/process */
		#define _STATIC_transferUpgrade_UpgradePercentGetRequestData_url "/device/upgrade/process"
		CSTR url;

	} data;

} transferUpgrade_UpgradePercentGetRequest;

C_API transferUpgrade_UpgradePercentGetRequest *HSAPI_INIT(transferUpgrade_UpgradePercentGetRequest);

typedef struct transferUpgrade_UpgradePercentGetResponse 
{
	HsviewResponse base;

	struct transferUpgrade_UpgradePercentGetResponseData
	{
		
		/** 升级状态 */
		CSTR status;
		/** 当前版本 */
		CSTR version;
		/** 当前正在进行的百分比 */
		CSTR percent;
 
	} data;

} transferUpgrade_UpgradePercentGetResponse;

C_API transferUpgrade_UpgradePercentGetResponse *HSAPI_INIT(transferUpgrade_UpgradePercentGetResponse);

#endif
