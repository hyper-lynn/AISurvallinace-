/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_OperateZoomFocus_H_
#define _HSVIEW_CLIENT_API_thingsControl_OperateZoomFocus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
开始或结束变倍聚焦

---------请求参数说明--------
deviceId: [string]，设备序列号
channelId: [string]，通道编号，单通道设备默认为0；
type: [string]，开始或停止，可选值如下：
start: 开始变倍聚焦；
stop: 停止变倍聚焦；
action: [string]，可选。放大或缩小，当type=="start"时有效，可选值如下：
large: 放大；
small: 缩小；
------------------------------

参考PaaS协议：[开始或结束变倍聚焦](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E5%8F%98%E5%80%8D%E8%81%9A%E7%84%A6%2F%E5%BC%80%E5%A7%8B%E6%88%96%E7%BB%93%E6%9D%9F%E5%8F%98%E5%80%8D%E8%81%9A%E7%84%A6.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_OperateZoomFocusRequest 
{
	HsviewRequest base;

	struct thingsControl_OperateZoomFocusRequestData
	{
		
		/** 操作类型，见参数说明 */
		CSTR type;
		/** 通道号 */
		CSTR channelId;
		/** 行为，见参数说明 */
		CSTR action;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsControl_OperateZoomFocusRequest;

C_API thingsControl_OperateZoomFocusRequest *HSAPI_INIT(thingsControl_OperateZoomFocusRequest);

typedef struct thingsControl_OperateZoomFocusResponse 
{
	HsviewResponse base;

	struct thingsControl_OperateZoomFocusResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsControl_OperateZoomFocusResponse;

C_API thingsControl_OperateZoomFocusResponse *HSAPI_INIT(thingsControl_OperateZoomFocusResponse);

#endif
