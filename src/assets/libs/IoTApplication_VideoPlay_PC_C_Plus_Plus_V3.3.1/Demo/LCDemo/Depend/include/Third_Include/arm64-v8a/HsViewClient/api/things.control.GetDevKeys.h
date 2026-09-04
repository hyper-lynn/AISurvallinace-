/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_GetDevKeys_H_
#define _HSVIEW_CLIENT_API_thingsControl_GetDevKeys_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 


响应内容说明参考PaaS协议：[获取设备秘钥列表](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A7%98%E9%92%A5%E7%AE%A1%E7%90%86%2F&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_GetDevKeysRequest 
{
	HsviewRequest base;

	struct thingsControl_GetDevKeysRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsControl_GetDevKeysRequest;

C_API thingsControl_GetDevKeysRequest *HSAPI_INIT(thingsControl_GetDevKeysRequest);

typedef struct thingsControl_GetDevKeysResponse 
{
	HsviewResponse base;

	struct thingsControl_GetDevKeysResponseData
	{
		
		/** define a list with struct of thingsControl_GetDevKeysResponseData_KeysElement */
		DECLARE_LIST(struct thingsControl_GetDevKeysResponseData_KeysElement
		{
			/** [bool]是否为管理员钥匙，true-是，false-否 */
			BOOL bManager;
			/** password:密码 card:卡,fingerPrint:指纹,face：人脸 */
			CSTR type;
			/** xxxx 钥匙名称 */
			CSTR name;
			/** xxxx 密码、卡、指纹的唯一标示符 */
			CSTR keyId;
			/** [bool]是否为劫持报警，true-是，false-否 */
			BOOL bHijackAlarm;
		}) keys;
 
	} data;

} thingsControl_GetDevKeysResponse;

C_API thingsControl_GetDevKeysResponse *HSAPI_INIT(thingsControl_GetDevKeysResponse);

#endif
