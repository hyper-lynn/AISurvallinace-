/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_NetworkAccessTypeGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_NetworkAccessTypeGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取入网方式

能力集SIMCA

参考PaaS协议：[获取入网方式](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96%E5%85%A5%E7%BD%91%E6%96%B9%E5%BC%8F%2F%E8%8E%B7%E5%8F%96%E5%85%A5%E7%BD%91%E6%96%B9%E5%BC%8F.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_NetworkAccessTypeGetRequest 
{
	HsviewRequest base;

	struct transferDevice_NetworkAccessTypeGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/into-network/query */
		#define _STATIC_transferDevice_NetworkAccessTypeGetRequestData_url "/device/into-network/query"
		CSTR url;

	} data;

} transferDevice_NetworkAccessTypeGetRequest;

C_API transferDevice_NetworkAccessTypeGetRequest *HSAPI_INIT(transferDevice_NetworkAccessTypeGetRequest);

typedef struct transferDevice_NetworkAccessTypeGetResponse 
{
	HsviewResponse base;

	struct transferDevice_NetworkAccessTypeGetResponseData
	{
		
		/** 入网类型：LAN：有线；Wifi：无线；SIMCard：SIM卡 */
		CSTR type;
 
	} data;

} transferDevice_NetworkAccessTypeGetResponse;

C_API transferDevice_NetworkAccessTypeGetResponse *HSAPI_INIT(transferDevice_NetworkAccessTypeGetResponse);

#endif
