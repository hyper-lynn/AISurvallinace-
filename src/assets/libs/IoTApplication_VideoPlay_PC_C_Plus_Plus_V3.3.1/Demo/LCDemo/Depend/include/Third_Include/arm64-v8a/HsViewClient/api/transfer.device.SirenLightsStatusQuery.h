/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_SirenLightsStatusQuery_H_
#define _HSVIEW_CLIENT_API_transferDevice_SirenLightsStatusQuery_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取警笛白光灯状态

参考PaaS协议：[获取警笛白光灯状态](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%AD%A6%E7%AC%9B%E6%93%8D%E4%BD%9C%2F%E8%8E%B7%E5%8F%96%E8%AD%A6%E7%AC%9B%E7%99%BD%E5%85%89%E7%81%AF%E7%8A%B6%E6%80%81.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_SirenLightsStatusQueryRequest 
{
	HsviewRequest base;

	struct transferDevice_SirenLightsStatusQueryRequestData
	{
		
		/** [cstr]/device/siren/query */
		#define _STATIC_transferDevice_SirenLightsStatusQueryRequestData_url "/device/siren/query"
		CSTR url;
		/** struct of transferDevice_SirenLightsStatusQueryRequestData_Content */
		struct transferDevice_SirenLightsStatusQueryRequestData_Content {
			/** 客户端握手成功后信令发送的本地系统时间，yyyyMMddTHHmmss格式，如20180301T111730 */
			CSTR clientLocalTime;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_SirenLightsStatusQueryRequest;

C_API transferDevice_SirenLightsStatusQueryRequest *HSAPI_INIT(transferDevice_SirenLightsStatusQueryRequest);

typedef struct transferDevice_SirenLightsStatusQueryResponse 
{
	HsviewResponse base;

	struct transferDevice_SirenLightsStatusQueryResponseData
	{
		
		/** 客户端请求中的clientLocalTime值，将Req的值原样带回 */
		CSTR clientLocalTime;
		/** [O]探照灯开关状态，on-开启，off-关闭 */
		CSTR searchLight;
		/** [O]白光灯开关状态，on:开启，off:关闭 */
		CSTR whiteLight;
		/** [int]响铃倒计时剩余时间，单位为秒，若为-1则表示未响铃 */
		int time;
 
	} data;

} transferDevice_SirenLightsStatusQueryResponse;

C_API transferDevice_SirenLightsStatusQueryResponse *HSAPI_INIT(transferDevice_SirenLightsStatusQueryResponse);

#endif
