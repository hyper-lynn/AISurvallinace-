/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_SirenTimeSet_H_
#define _HSVIEW_CLIENT_API_transferDevice_SirenTimeSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置警笛时长

参考PaaS协议：[设置警笛时长](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%AD%A6%E7%AC%9B%E6%93%8D%E4%BD%9C%2F%E8%AE%BE%E7%BD%AE%E8%AD%A6%E7%AC%9B%E6%97%B6%E9%95%BF.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_SirenTimeSetRequest 
{
	HsviewRequest base;

	struct transferDevice_SirenTimeSetRequestData
	{
		
		/** [cstr]/device/siren/time/config */
		#define _STATIC_transferDevice_SirenTimeSetRequestData_url "/device/siren/time/config"
		CSTR url;
		/** struct of transferDevice_SirenTimeSetRequestData_Content */
		struct transferDevice_SirenTimeSetRequestData_Content {
			/** 警笛时长对应的索引值，有效值大于等于0 */
			CSTR index;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_SirenTimeSetRequest;

C_API transferDevice_SirenTimeSetRequest *HSAPI_INIT(transferDevice_SirenTimeSetRequest);

typedef struct transferDevice_SirenTimeSetResponse 
{
	HsviewResponse base;

	struct transferDevice_SirenTimeSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_SirenTimeSetResponse;

C_API transferDevice_SirenTimeSetResponse *HSAPI_INIT(transferDevice_SirenTimeSetResponse);

#endif
