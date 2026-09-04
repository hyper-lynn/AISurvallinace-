/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_SIMInfoGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_SIMInfoGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取SIM卡信息

能力集SIMCA

参考PaaS协议：[获取SIM卡信息](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2FSIM%E5%8D%A1%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96SIM%E5%8D%A1.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_SIMInfoGetRequest 
{
	HsviewRequest base;

	struct transferDevice_SIMInfoGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/sim/query */
		#define _STATIC_transferDevice_SIMInfoGetRequestData_url "/device/sim/query"
		CSTR url;

	} data;

} transferDevice_SIMInfoGetRequest;

C_API transferDevice_SIMInfoGetRequest *HSAPI_INIT(transferDevice_SIMInfoGetRequest);

typedef struct transferDevice_SIMInfoGetResponse 
{
	HsviewResponse base;

	struct transferDevice_SIMInfoGetResponseData
	{
		
		/** 用户名 */
		CSTR userName;
		/** 接入点名称 */
		CSTR apn;
		/** 密码 */
		CSTR userPW;
		/** 鉴权模式 */
		CSTR authMode;
		/** 拨号号码 */
		CSTR number;
 
	} data;

} transferDevice_SIMInfoGetResponse;

C_API transferDevice_SIMInfoGetResponse *HSAPI_INIT(transferDevice_SIMInfoGetResponse);

#endif
