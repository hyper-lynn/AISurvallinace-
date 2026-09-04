/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_LightTimeGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_LightTimeGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
亮灯时长获取

参考PaaS协议：[亮灯时长获取](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8E%A2%E7%85%A7%E7%81%AF%E9%85%8D%E7%BD%AE%2F%E4%BA%AE%E7%81%AF%E6%97%B6%E9%95%BF%E8%8E%B7%E5%8F%96.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_LightTimeGetRequest 
{
	HsviewRequest base;

	struct transferDevice_LightTimeGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/searchlight/time/query */
		#define _STATIC_transferDevice_LightTimeGetRequestData_url "/device/searchlight/time/query"
		CSTR url;

	} data;

} transferDevice_LightTimeGetRequest;

C_API transferDevice_LightTimeGetRequest *HSAPI_INIT(transferDevice_LightTimeGetRequest);

typedef struct transferDevice_LightTimeGetResponse 
{
	HsviewResponse base;

	struct transferDevice_LightTimeGetResponseData
	{
		
		/** 探照灯时长对应的索引值，有效值大于等于0 */
		CSTR index;
		/** define a list with struct of transferDevice_LightTimeGetResponseData_ValuesElement */
		DECLARE_LIST(struct transferDevice_LightTimeGetResponseData_ValuesElement
		{
			/** 探照灯时长对应的索引值，有效值大于等于0，从0顺序递增 */
			CSTR index;
			/** 探照灯时长，单位为S */
			CSTR time;
		}) values;
 
	} data;

} transferDevice_LightTimeGetResponse;

C_API transferDevice_LightTimeGetResponse *HSAPI_INIT(transferDevice_LightTimeGetResponse);

#endif
