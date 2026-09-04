/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_SIMContactGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_SIMContactGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取SIM卡联系人

能力集SIMCA

参考PaaS协议：[获取SIM卡联系人](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%81%94%E7%B3%BB%E4%BA%BA%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96%E8%81%94%E7%B3%BB%E4%BA%BA.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_SIMContactGetRequest 
{
	HsviewRequest base;

	struct transferDevice_SIMContactGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/contacts/query */
		#define _STATIC_transferDevice_SIMContactGetRequestData_url "/device/contacts/query"
		CSTR url;

	} data;

} transferDevice_SIMContactGetRequest;

C_API transferDevice_SIMContactGetRequest *HSAPI_INIT(transferDevice_SIMContactGetRequest);

typedef struct transferDevice_SIMContactGetResponse 
{
	HsviewResponse base;

	struct transferDevice_SIMContactGetResponseData
	{
		
		/** define a list with struct of transferDevice_SIMContactGetResponseData_DetailsElement */
		DECLARE_LIST(struct transferDevice_SIMContactGetResponseData_DetailsElement
		{
			/** 索引号 */
			CSTR index;
			/** 联系方式 */
			CSTR phone;
		}) details;
 
	} data;

} transferDevice_SIMContactGetResponse;

C_API transferDevice_SIMContactGetResponse *HSAPI_INIT(transferDevice_SIMContactGetResponse);

#endif
