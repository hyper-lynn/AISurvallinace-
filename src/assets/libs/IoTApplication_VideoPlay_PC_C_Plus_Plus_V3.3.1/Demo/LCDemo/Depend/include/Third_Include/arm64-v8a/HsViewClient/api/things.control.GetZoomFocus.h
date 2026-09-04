/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_GetZoomFocus_H_
#define _HSVIEW_CLIENT_API_thingsControl_GetZoomFocus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取变倍聚焦倍数

----------------请求参数说明-------------------
deviceId：[string]，设备序列号；
channels：通道号数组，该字段不存在则全量获取。
-----------------------------------------------

--------------响应参数说明-----------------
channelId：[int]，通道编号。
zoomFocus：[double]，变倍倍数，归一化到0~1。
-------------------------------------------


参考PaaS协议：[获取变倍聚焦倍数](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E5%8F%98%E5%80%8D%E8%81%9A%E7%84%A6%2F%E8%8E%B7%E5%8F%96%E5%8F%98%E5%80%8D%E8%81%9A%E7%84%A6%E5%80%8D%E6%95%B0.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_GetZoomFocusRequest 
{
	HsviewRequest base;

	struct thingsControl_GetZoomFocusRequestData
	{
		
		/** [int]通道号数组 */
		DECLARE_LIST(int) channels;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsControl_GetZoomFocusRequest;

C_API thingsControl_GetZoomFocusRequest *HSAPI_INIT(thingsControl_GetZoomFocusRequest);

typedef struct thingsControl_GetZoomFocusResponse 
{
	HsviewResponse base;

	struct thingsControl_GetZoomFocusResponseData
	{
		
		/** define a list with struct of thingsControl_GetZoomFocusResponseData_ChannelsElement */
		DECLARE_LIST(struct thingsControl_GetZoomFocusResponseData_ChannelsElement
		{
			/** [double]变倍倍数 */
			double zoomFocus;
			/** [int]通道号 */
			int channelId;
		}) channels;
 
	} data;

} thingsControl_GetZoomFocusResponse;

C_API thingsControl_GetZoomFocusResponse *HSAPI_INIT(thingsControl_GetZoomFocusResponse);

#endif
