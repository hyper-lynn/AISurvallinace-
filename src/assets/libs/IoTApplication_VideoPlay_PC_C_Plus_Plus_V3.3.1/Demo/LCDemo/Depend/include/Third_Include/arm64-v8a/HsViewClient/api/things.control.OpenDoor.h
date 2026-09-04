/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_OpenDoor_H_
#define _HSVIEW_CLIENT_API_thingsControl_OpenDoor_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
呼叫开锁

响应内容说明参考PaaS协议：[呼叫开锁](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E5%8F%A3%E6%9C%BA%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E5%BC%80%E9%94%81.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_OpenDoorRequest 
{
	HsviewRequest base;

	struct thingsControl_OpenDoorRequestData
	{
		
		/** 设备ID */
		CSTR deviceId;

	} data;

} thingsControl_OpenDoorRequest;

C_API thingsControl_OpenDoorRequest *HSAPI_INIT(thingsControl_OpenDoorRequest);

typedef struct thingsControl_OpenDoorResponse 
{
	HsviewResponse base;

	struct thingsControl_OpenDoorResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsControl_OpenDoorResponse;

C_API thingsControl_OpenDoorResponse *HSAPI_INIT(thingsControl_OpenDoorResponse);

#endif
