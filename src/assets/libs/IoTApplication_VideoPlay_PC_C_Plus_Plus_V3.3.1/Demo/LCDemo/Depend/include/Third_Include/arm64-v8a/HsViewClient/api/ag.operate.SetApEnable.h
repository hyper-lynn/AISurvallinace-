/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_agOperate_SetApEnable_H_
#define _HSVIEW_CLIENT_API_agOperate_SetApEnable_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置报警网关配件相关功能的使能

type取值参考PaaS协议：[报警网关使能类型定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2F&s=pd)
类型			备注
sound-light		声光报警使能		
accessories		配件使能		
alarm			报警使能		
24HEnable		24小时使能        能力集24HEnable
linkageSiren	联动警笛使能	  能力集LinkageSiren


仅在type为accessories时，apId必填

【需要使用平台账号签名】
 */

typedef struct agOperate_SetApEnableRequest 
{
	HsviewRequest base;

	struct agOperate_SetApEnableRequestData
	{
		
		/** 使能状态：on-开启 off-关闭 */
		CSTR enable;
		/** [O]配件ID */
		CSTR apId;
		/** 类型 */
		CSTR type;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} agOperate_SetApEnableRequest;

C_API agOperate_SetApEnableRequest *HSAPI_INIT(agOperate_SetApEnableRequest);

typedef struct agOperate_SetApEnableResponse 
{
	HsviewResponse base;

	struct agOperate_SetApEnableResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} agOperate_SetApEnableResponse;

C_API agOperate_SetApEnableResponse *HSAPI_INIT(agOperate_SetApEnableResponse);

#endif
