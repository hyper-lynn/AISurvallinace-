/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_LightTimeSet_H_
#define _HSVIEW_CLIENT_API_transferDevice_LightTimeSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
亮灯时长设置

参考PaaS协议：[亮灯时长设置](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8E%A2%E7%85%A7%E7%81%AF%E9%85%8D%E7%BD%AE%2F%E4%BA%AE%E7%81%AF%E6%97%B6%E9%95%BF%E8%AE%BE%E7%BD%AE.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_LightTimeSetRequest 
{
	HsviewRequest base;

	struct transferDevice_LightTimeSetRequestData
	{
		
		/** [cstr]/device/searchlight/time/config */
		#define _STATIC_transferDevice_LightTimeSetRequestData_url "/device/searchlight/time/config"
		CSTR url;
		/** struct of transferDevice_LightTimeSetRequestData_Content */
		struct transferDevice_LightTimeSetRequestData_Content {
			/** 探照灯时长对应的索引值，有效值大于等于0 */
			CSTR index;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_LightTimeSetRequest;

C_API transferDevice_LightTimeSetRequest *HSAPI_INIT(transferDevice_LightTimeSetRequest);

typedef struct transferDevice_LightTimeSetResponse 
{
	HsviewResponse base;

	struct transferDevice_LightTimeSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_LightTimeSetResponse;

C_API transferDevice_LightTimeSetResponse *HSAPI_INIT(transferDevice_LightTimeSetResponse);

#endif
