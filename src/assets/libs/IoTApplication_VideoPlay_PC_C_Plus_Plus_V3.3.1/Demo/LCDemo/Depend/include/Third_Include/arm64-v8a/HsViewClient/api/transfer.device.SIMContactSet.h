/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_SIMContactSet_H_
#define _HSVIEW_CLIENT_API_transferDevice_SIMContactSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置SIM卡联系人

能力集SIMCA

参考PaaS协议：[设置SIM卡联系人](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%81%94%E7%B3%BB%E4%BA%BA%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AE%E8%81%94%E7%B3%BB%E4%BA%BA.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_SIMContactSetRequest 
{
	HsviewRequest base;

	struct transferDevice_SIMContactSetRequestData
	{
		
		/** [cstr]/device/contacts/config */
		#define _STATIC_transferDevice_SIMContactSetRequestData_url "/device/contacts/config"
		CSTR url;
		/** struct of transferDevice_SIMContactSetRequestData_Content */
		struct transferDevice_SIMContactSetRequestData_Content {
			/** define a list with struct of transferDevice_SIMContactSetRequestData_Content_DetailsElement */
			DECLARE_LIST(struct transferDevice_SIMContactSetRequestData_Content_DetailsElement
			{
				/** 索引号 */
				CSTR index;
				/** 联系方式 */
				CSTR phone;
			}) details;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_SIMContactSetRequest;

C_API transferDevice_SIMContactSetRequest *HSAPI_INIT(transferDevice_SIMContactSetRequest);

typedef struct transferDevice_SIMContactSetResponse 
{
	HsviewResponse base;

	struct transferDevice_SIMContactSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_SIMContactSetResponse;

C_API transferDevice_SIMContactSetResponse *HSAPI_INIT(transferDevice_SIMContactSetResponse);

#endif
