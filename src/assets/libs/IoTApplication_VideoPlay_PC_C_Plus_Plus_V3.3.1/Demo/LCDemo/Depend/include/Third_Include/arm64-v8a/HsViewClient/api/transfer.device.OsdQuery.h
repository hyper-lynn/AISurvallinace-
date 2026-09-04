/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_OsdQuery_H_
#define _HSVIEW_CLIENT_API_transferDevice_OsdQuery_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取OSD配置

参考PaaS协议：
http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2FOSD%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96OSD%E9%85%8D%E7%BD%AE.md&s=pd
【需要使用平台账号签名】
 */

typedef struct transferDevice_OsdQueryRequest 
{
	HsviewRequest base;

	struct transferDevice_OsdQueryRequestData
	{
		
		/** [cstr] /device/osd/query/ */
		#define _STATIC_transferDevice_OsdQueryRequestData_url " /device/osd/query/"
		CSTR url;
		/** [int]通道号 */
		int channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_OsdQueryRequest;

C_API transferDevice_OsdQueryRequest *HSAPI_INIT(transferDevice_OsdQueryRequest);

typedef struct transferDevice_OsdQueryResponse 
{
	HsviewResponse base;

	struct transferDevice_OsdQueryResponseData
	{
		
		/** on使能打开,off使能关闭 */
		CSTR enable;
		/** [O]OSD字符，对应设备端channelTitle，不支持换行 */
		CSTR osd;
 
	} data;

} transferDevice_OsdQueryResponse;

C_API transferDevice_OsdQueryResponse *HSAPI_INIT(transferDevice_OsdQueryResponse);

#endif
