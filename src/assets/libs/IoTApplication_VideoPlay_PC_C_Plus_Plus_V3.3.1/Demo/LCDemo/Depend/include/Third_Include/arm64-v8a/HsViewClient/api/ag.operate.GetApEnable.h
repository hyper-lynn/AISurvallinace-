/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_agOperate_GetApEnable_H_
#define _HSVIEW_CLIENT_API_agOperate_GetApEnable_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取报警网关配件相关功能的使能

报警网关使能类型
http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2FHome.md&s=pd

仅在type为accessories时，apId必填


sound-light	声光报警使能开关（是否报警）
accessories	配件布防使能开关
alarm	报警状态使能，关闭立刻生效
【需要使用平台账号签名】
 */

typedef struct agOperate_GetApEnableRequest 
{
	HsviewRequest base;

	struct agOperate_GetApEnableRequestData
	{
		
		/** [O]配件ID */
		CSTR apId;
		/** 类型 */
		CSTR type;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} agOperate_GetApEnableRequest;

C_API agOperate_GetApEnableRequest *HSAPI_INIT(agOperate_GetApEnableRequest);

typedef struct agOperate_GetApEnableResponse 
{
	HsviewResponse base;

	struct agOperate_GetApEnableResponseData
	{
		
		/** 使能状态：on-开启 off-关闭 */
		CSTR enable;
 
	} data;

} agOperate_GetApEnableResponse;

C_API agOperate_GetApEnableResponse *HSAPI_INIT(agOperate_GetApEnableResponse);

#endif
