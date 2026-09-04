/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_DefenceSceneModeGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_DefenceSceneModeGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
布防情景模式获取

情景模式配置能力集SceneMode

参考PaaS协议：[布防情景模式获取](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%83%85%E6%99%AF%E6%A8%A1%E5%BC%8F%E9%85%8D%E7%BD%AE%2F%E6%83%85%E6%99%AF%E6%A8%A1%E5%BC%8F%E8%8E%B7%E5%8F%96.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_DefenceSceneModeGetRequest 
{
	HsviewRequest base;

	struct transferDevice_DefenceSceneModeGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/scenemode/query */
		#define _STATIC_transferDevice_DefenceSceneModeGetRequestData_url "/device/scenemode/query"
		CSTR url;

	} data;

} transferDevice_DefenceSceneModeGetRequest;

C_API transferDevice_DefenceSceneModeGetRequest *HSAPI_INIT(transferDevice_DefenceSceneModeGetRequest);

typedef struct transferDevice_DefenceSceneModeGetResponse 
{
	HsviewResponse base;

	struct transferDevice_DefenceSceneModeGetResponseData
	{
		
		/** 支持的情景模式类型: Home---在家模式,Away---离家模式,Disarm---撤防 */
		DECLARE_LIST(CSTR) allType;
		/** 当前所在的情景模式类型：Home---在家模式,Away---离家模式,Disarm---撤防 */
		CSTR curType;
 
	} data;

} transferDevice_DefenceSceneModeGetResponse;

C_API transferDevice_DefenceSceneModeGetResponse *HSAPI_INIT(transferDevice_DefenceSceneModeGetResponse);

#endif
