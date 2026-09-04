/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_OsdConfig_H_
#define _HSVIEW_CLIENT_API_transferDevice_OsdConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置OSD配置

参考PaaS协议：
http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2FOSD%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AEOSD%E9%85%8D%E7%BD%AE.md&s=pd
【需要使用平台账号签名】
 */

typedef struct transferDevice_OsdConfigRequest 
{
	HsviewRequest base;

	struct transferDevice_OsdConfigRequestData
	{
		
		/** [int]通道号 */
		int channelId;
		/** [cstr] /device/osd/config/ */
		#define _STATIC_transferDevice_OsdConfigRequestData_url " /device/osd/config/"
		CSTR url;
		/** struct of transferDevice_OsdConfigRequestData_Content */
		struct transferDevice_OsdConfigRequestData_Content {
			/** on使能打开,off使能关闭 */
			CSTR enable;
			/** [O]OSD字符，对应设备端channelTitle，不支持换行 */
			CSTR osd;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_OsdConfigRequest;

C_API transferDevice_OsdConfigRequest *HSAPI_INIT(transferDevice_OsdConfigRequest);

typedef struct transferDevice_OsdConfigResponse 
{
	HsviewResponse base;

	struct transferDevice_OsdConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_OsdConfigResponse;

C_API transferDevice_OsdConfigResponse *HSAPI_INIT(transferDevice_OsdConfigResponse);

#endif
