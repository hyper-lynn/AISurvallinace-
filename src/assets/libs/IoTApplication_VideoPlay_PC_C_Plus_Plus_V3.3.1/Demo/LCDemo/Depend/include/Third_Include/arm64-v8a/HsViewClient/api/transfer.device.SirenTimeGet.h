/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_SirenTimeGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_SirenTimeGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取警笛时长

参考PaaS协议：[获取警笛时长](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%AD%A6%E7%AC%9B%E6%93%8D%E4%BD%9C%2F%E8%8E%B7%E5%8F%96%E8%AD%A6%E7%AC%9B%E6%97%B6%E9%95%BF.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_SirenTimeGetRequest 
{
	HsviewRequest base;

	struct transferDevice_SirenTimeGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/siren/time/query */
		#define _STATIC_transferDevice_SirenTimeGetRequestData_url "/device/siren/time/query"
		CSTR url;

	} data;

} transferDevice_SirenTimeGetRequest;

C_API transferDevice_SirenTimeGetRequest *HSAPI_INIT(transferDevice_SirenTimeGetRequest);

typedef struct transferDevice_SirenTimeGetResponse 
{
	HsviewResponse base;

	struct transferDevice_SirenTimeGetResponseData
	{
		
		/** 警笛时长对应的索引值，有效值大于等于0。-1表示未设置 */
		CSTR index;
		/** define a list with struct of transferDevice_SirenTimeGetResponseData_ValuesElement */
		DECLARE_LIST(struct transferDevice_SirenTimeGetResponseData_ValuesElement
		{
			/** 警笛时长对应的索引值，有效值大于等于0 */
			CSTR index;
			/** 警笛时长，单位为S */
			CSTR time;
		}) values;
 
	} data;

} transferDevice_SirenTimeGetResponse;

C_API transferDevice_SirenTimeGetResponse *HSAPI_INIT(transferDevice_SirenTimeGetResponse);

#endif
