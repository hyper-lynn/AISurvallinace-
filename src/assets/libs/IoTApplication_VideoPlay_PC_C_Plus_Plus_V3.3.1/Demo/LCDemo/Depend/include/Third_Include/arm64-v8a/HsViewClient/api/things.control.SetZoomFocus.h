/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_SetZoomFocus_H_
#define _HSVIEW_CLIENT_API_thingsControl_SetZoomFocus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置变倍聚焦倍数

-------------请求参数说明--------------
deviceId: [string]，设备序列号；
channelId: [string]，通道编号，单通道设备默认为0；
type：[String]，操作类型：large：增量放大；small：增量缩小；cover：全量覆盖；
zoomFocus: [double]，type为cover时表示变倍倍数，归一化到0.0~1.0；type为large或small时表示缩放增量；
--------------

-------------答复参数说明--------------
"zoomFocus": [double]，设备操作后，当前的变倍倍数,归一化到0.0~1.0
--------------

参考PaaS协议：[设置变倍聚焦倍数](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E5%8F%98%E5%80%8D%E8%81%9A%E7%84%A6%2F%E8%AE%BE%E7%BD%AE%E5%8F%98%E5%80%8D%E8%81%9A%E7%84%A6%E5%80%8D%E6%95%B0.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_SetZoomFocusRequest 
{
	HsviewRequest base;

	struct thingsControl_SetZoomFocusRequestData
	{
		
		/** [double]变倍倍数或缩放增量 */
		double zoomFocus;
		/** 通道号 */
		CSTR channelId;
		/** 操作类型：large:增量放大,small:增量缩小,cover:全量覆盖 */
		CSTR type;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsControl_SetZoomFocusRequest;

C_API thingsControl_SetZoomFocusRequest *HSAPI_INIT(thingsControl_SetZoomFocusRequest);

typedef struct thingsControl_SetZoomFocusResponse 
{
	HsviewResponse base;

	struct thingsControl_SetZoomFocusResponseData
	{
		
		/** [double]设备操作后，当前的变倍倍数,归一化到0.0~1.0 */
		double zoomFocus;
 
	} data;

} thingsControl_SetZoomFocusResponse;

C_API thingsControl_SetZoomFocusResponse *HSAPI_INIT(thingsControl_SetZoomFocusResponse);

#endif
