/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_SearchLightWorkModeSet_H_
#define _HSVIEW_CLIENT_API_transferDevice_SearchLightWorkModeSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
探照灯模式设置

设备级操作，chan，sn不需要设置
通道级操作，需要设备支持通道探照灯能力 ChanSearchLight。sn，表示deviceId代表的设备通道下关联的设备序列号，chan是对应的通道号，当sn，chan都下发时，优先sn

参考PaaS协议：[探照灯模式设置](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8E%A2%E7%85%A7%E7%81%AF%E9%85%8D%E7%BD%AE%2F%E6%8E%A2%E7%85%A7%E7%81%AF%E6%A8%A1%E5%BC%8F%E8%AE%BE%E7%BD%AE.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_SearchLightWorkModeSetRequest 
{
	HsviewRequest base;

	struct transferDevice_SearchLightWorkModeSetRequestData
	{
		
		/** [cstr]/device/searchlight/mode/config */
		#define _STATIC_transferDevice_SearchLightWorkModeSetRequestData_url "/device/searchlight/mode/config"
		CSTR url;
		/** struct of transferDevice_SearchLightWorkModeSetRequestData_Content */
		struct transferDevice_SearchLightWorkModeSetRequestData_Content {
			/** [O]设备序列号 */
			CSTR sn;
			/** [O]通道,不存在默认为设备 */
			CSTR chan;
			/** 探照灯模式对应的索引值，有效值大于等于0 */
			CSTR index;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_SearchLightWorkModeSetRequest;

C_API transferDevice_SearchLightWorkModeSetRequest *HSAPI_INIT(transferDevice_SearchLightWorkModeSetRequest);

typedef struct transferDevice_SearchLightWorkModeSetResponse 
{
	HsviewResponse base;

	struct transferDevice_SearchLightWorkModeSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_SearchLightWorkModeSetResponse;

C_API transferDevice_SearchLightWorkModeSetResponse *HSAPI_INIT(transferDevice_SearchLightWorkModeSetResponse);

#endif
