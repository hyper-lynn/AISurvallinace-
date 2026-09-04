/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_DefenceSceneModeInfoSet_H_
#define _HSVIEW_CLIENT_API_transferDevice_DefenceSceneModeInfoSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
情景模式配件配置列表设置

情景模式配置能力集SceneMode

参考PaaS协议：[情景模式配件配置列表设置](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%83%85%E6%99%AF%E6%A8%A1%E5%BC%8F%E9%85%8D%E7%BD%AE%2F%E6%83%85%E6%99%AF%E6%A8%A1%E5%BC%8F%E9%85%8D%E4%BB%B6%E5%88%97%E8%A1%A8%E8%AE%BE%E7%BD%AE.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_DefenceSceneModeInfoSetRequest 
{
	HsviewRequest base;

	struct transferDevice_DefenceSceneModeInfoSetRequestData
	{
		
		/** [cstr]/device/scenemode/list/config */
		#define _STATIC_transferDevice_DefenceSceneModeInfoSetRequestData_url "/device/scenemode/list/config"
		CSTR url;
		/** struct of transferDevice_DefenceSceneModeInfoSetRequestData_Content */
		struct transferDevice_DefenceSceneModeInfoSetRequestData_Content {
			/** 配件ID列表，在该列表中的配件都是在该模式下工作的，不在该列表中的配件都是不工作的 */
			DECLARE_LIST(CSTR) list;
			/** 情景模式类型：Home---在家模式,Away---离家模式,Disarm---撤防 */
			CSTR type;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_DefenceSceneModeInfoSetRequest;

C_API transferDevice_DefenceSceneModeInfoSetRequest *HSAPI_INIT(transferDevice_DefenceSceneModeInfoSetRequest);

typedef struct transferDevice_DefenceSceneModeInfoSetResponse 
{
	HsviewResponse base;

	struct transferDevice_DefenceSceneModeInfoSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_DefenceSceneModeInfoSetResponse;

C_API transferDevice_DefenceSceneModeInfoSetResponse *HSAPI_INIT(transferDevice_DefenceSceneModeInfoSetResponse);

#endif
