/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_DeleteDevKeys_H_
#define _HSVIEW_CLIENT_API_thingsControl_DeleteDevKeys_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 


响应内容说明参考PaaS协议：[删除设备秘钥 临时秘钥](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A7%98%E9%92%A5%E7%AE%A1%E7%90%86%2F&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_DeleteDevKeysRequest 
{
	HsviewRequest base;

	struct thingsControl_DeleteDevKeysRequestData
	{
		
		/** 密码、卡、指纹、临时密码的唯一标示符 */
		CSTR keyId;
		/** password:密码 card:卡,fingerPrint:指纹,face：人脸,snapkey:临时密码 */
		CSTR type;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsControl_DeleteDevKeysRequest;

C_API thingsControl_DeleteDevKeysRequest *HSAPI_INIT(thingsControl_DeleteDevKeysRequest);

typedef struct thingsControl_DeleteDevKeysResponse 
{
	HsviewResponse base;

	struct thingsControl_DeleteDevKeysResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsControl_DeleteDevKeysResponse;

C_API thingsControl_DeleteDevKeysResponse *HSAPI_INIT(thingsControl_DeleteDevKeysResponse);

#endif
