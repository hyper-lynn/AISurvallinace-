/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_SIMInfoSet_H_
#define _HSVIEW_CLIENT_API_transferDevice_SIMInfoSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置SIM卡

能力集SIMCA

参考PaaS协议：[设置SIM卡](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2FSIM%E5%8D%A1%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AESIM%E5%8D%A1.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_SIMInfoSetRequest 
{
	HsviewRequest base;

	struct transferDevice_SIMInfoSetRequestData
	{
		
		/** [cstr]/device/sim/config */
		#define _STATIC_transferDevice_SIMInfoSetRequestData_url "/device/sim/config"
		CSTR url;
		/** struct of transferDevice_SIMInfoSetRequestData_Content */
		struct transferDevice_SIMInfoSetRequestData_Content {
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
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_SIMInfoSetRequest;

C_API transferDevice_SIMInfoSetRequest *HSAPI_INIT(transferDevice_SIMInfoSetRequest);

typedef struct transferDevice_SIMInfoSetResponse 
{
	HsviewResponse base;

	struct transferDevice_SIMInfoSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_SIMInfoSetResponse;

C_API transferDevice_SIMInfoSetResponse *HSAPI_INIT(transferDevice_SIMInfoSetResponse);

#endif
