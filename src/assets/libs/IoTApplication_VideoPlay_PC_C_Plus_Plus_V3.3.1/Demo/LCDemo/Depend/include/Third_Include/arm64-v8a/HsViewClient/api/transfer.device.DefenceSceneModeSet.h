/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_DefenceSceneModeSet_H_
#define _HSVIEW_CLIENT_API_transferDevice_DefenceSceneModeSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
情景模式设置

情景模式配置能力集SceneMode

参考PaaS协议：[情景模式设置](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%83%85%E6%99%AF%E6%A8%A1%E5%BC%8F%E9%85%8D%E7%BD%AE%2F%E6%83%85%E6%99%AF%E6%A8%A1%E5%BC%8F%E8%AE%BE%E7%BD%AE.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_DefenceSceneModeSetRequest 
{
	HsviewRequest base;

	struct transferDevice_DefenceSceneModeSetRequestData
	{
		
		/** [cstr]/device/scenemode/config */
		#define _STATIC_transferDevice_DefenceSceneModeSetRequestData_url "/device/scenemode/config"
		CSTR url;
		/** struct of transferDevice_DefenceSceneModeSetRequestData_Content */
		struct transferDevice_DefenceSceneModeSetRequestData_Content {
			/** 情景模式类型：Home---在家模式,Away---离家模式,Disarm---撤防 */
			CSTR type;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_DefenceSceneModeSetRequest;

C_API transferDevice_DefenceSceneModeSetRequest *HSAPI_INIT(transferDevice_DefenceSceneModeSetRequest);

typedef struct transferDevice_DefenceSceneModeSetResponse 
{
	HsviewResponse base;

	struct transferDevice_DefenceSceneModeSetResponseData
	{
		
		/** 布防延时时间，单位秒S */
		CSTR time;
 
	} data;

} transferDevice_DefenceSceneModeSetResponse;

C_API transferDevice_DefenceSceneModeSetResponse *HSAPI_INIT(transferDevice_DefenceSceneModeSetResponse);

#endif
