/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_SearchLightWorkModeGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_SearchLightWorkModeGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
探照灯模式获取

设备级操作，chan，sn不需要设置,即content可传空
通道级操作，需要设备支持通道探照灯能力 ChanSearchLight。sn，表示deviceId代表的设备通道下关联的设备序列号，chan是对应的通道号，当sn，chan都下发时，优先sn

参考PaaS协议：[探照灯模式获取](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8E%A2%E7%85%A7%E7%81%AF%E9%85%8D%E7%BD%AE%2F%E6%8E%A2%E7%85%A7%E7%81%AF%E6%A8%A1%E5%BC%8F%E8%8E%B7%E5%8F%96.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_SearchLightWorkModeGetRequest 
{
	HsviewRequest base;

	struct transferDevice_SearchLightWorkModeGetRequestData
	{
		
		/** [cstr]/device/searchlight/mode/query */
		#define _STATIC_transferDevice_SearchLightWorkModeGetRequestData_url "/device/searchlight/mode/query"
		CSTR url;
		/** struct of transferDevice_SearchLightWorkModeGetRequestData_Content */
		struct transferDevice_SearchLightWorkModeGetRequestData_Content {
			/** [O]通道,不存在默认为设备 */
			CSTR chan;
			/** [O]设备序列号 */
			CSTR sn;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_SearchLightWorkModeGetRequest;

C_API transferDevice_SearchLightWorkModeGetRequest *HSAPI_INIT(transferDevice_SearchLightWorkModeGetRequest);

typedef struct transferDevice_SearchLightWorkModeGetResponse 
{
	HsviewResponse base;

	struct transferDevice_SearchLightWorkModeGetResponseData
	{
		
		/** 探照灯模式对应的索引值，有效值大于等于0 */
		CSTR index;
		/** define a list with struct of transferDevice_SearchLightWorkModeGetResponseData_ValuesElement */
		DECLARE_LIST(struct transferDevice_SearchLightWorkModeGetResponseData_ValuesElement
		{
			/** 探照灯模式对应的索引值，有效值大于等于0，从0顺序递增 */
			CSTR index;
			/** 探照灯模式: manual：通用模式,motion activation：PIR联动模式,dusk to dawn：光敏联动模式 */
			CSTR mode;
		}) values;
 
	} data;

} transferDevice_SearchLightWorkModeGetResponse;

C_API transferDevice_SearchLightWorkModeGetResponse *HSAPI_INIT(transferDevice_SearchLightWorkModeGetResponse);

#endif
