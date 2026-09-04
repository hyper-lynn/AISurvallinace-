/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_DefenceSceneModeInfoGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_DefenceSceneModeInfoGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
情景模式配件配置列表获取

情景模式配置能力集SceneMode

参考PaaS协议：[情景模式配件配置列表获取](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%83%85%E6%99%AF%E6%A8%A1%E5%BC%8F%E9%85%8D%E7%BD%AE%2F%E6%83%85%E6%99%AF%E6%A8%A1%E5%BC%8F%E9%85%8D%E4%BB%B6%E5%88%97%E8%A1%A8%E8%8E%B7%E5%8F%96.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_DefenceSceneModeInfoGetRequest 
{
	HsviewRequest base;

	struct transferDevice_DefenceSceneModeInfoGetRequestData
	{
		
		/** [cstr]/device/scenemode/list/query */
		#define _STATIC_transferDevice_DefenceSceneModeInfoGetRequestData_url "/device/scenemode/list/query"
		CSTR url;
		/** struct of transferDevice_DefenceSceneModeInfoGetRequestData_Content */
		struct transferDevice_DefenceSceneModeInfoGetRequestData_Content {
			/** 情景模式类型：Home---在家模式,Away---离家模式,Disarm---撤防 */
			CSTR type;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_DefenceSceneModeInfoGetRequest;

C_API transferDevice_DefenceSceneModeInfoGetRequest *HSAPI_INIT(transferDevice_DefenceSceneModeInfoGetRequest);

typedef struct transferDevice_DefenceSceneModeInfoGetResponse 
{
	HsviewResponse base;

	struct transferDevice_DefenceSceneModeInfoGetResponseData
	{
		
		/** 配件ID列表，在该列表中的配件都是在该模式下工作的，不在该列表中的配件都是不工作的 */
		DECLARE_LIST(CSTR) list;
 
	} data;

} transferDevice_DefenceSceneModeInfoGetResponse;

C_API transferDevice_DefenceSceneModeInfoGetResponse *HSAPI_INIT(transferDevice_DefenceSceneModeInfoGetResponse);

#endif
