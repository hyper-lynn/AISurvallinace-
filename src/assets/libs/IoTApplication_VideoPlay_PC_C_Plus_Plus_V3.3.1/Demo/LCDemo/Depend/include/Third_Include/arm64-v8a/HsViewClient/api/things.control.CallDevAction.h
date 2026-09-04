/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_CallDevAction_H_
#define _HSVIEW_CLIENT_API_thingsControl_CallDevAction_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
响应呼叫

响应内容说明参考PaaS协议：[响应呼叫](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E5%8F%A3%E6%9C%BA%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_CallDevActionRequest 
{
	HsviewRequest base;

	struct thingsControl_CallDevActionRequestData
	{
		
		/** answer 接听 refuse 拒接 hangup 挂断 */
		CSTR action;
		/** 设备ID */
		CSTR deviceId;

	} data;

} thingsControl_CallDevActionRequest;

C_API thingsControl_CallDevActionRequest *HSAPI_INIT(thingsControl_CallDevActionRequest);

typedef struct thingsControl_CallDevActionResponse 
{
	HsviewResponse base;

	struct thingsControl_CallDevActionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsControl_CallDevActionResponse;

C_API thingsControl_CallDevActionResponse *HSAPI_INIT(thingsControl_CallDevActionResponse);

#endif
