/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_QuerySiren_H_
#define _HSVIEW_CLIENT_API_thingsControl_QuerySiren_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取警笛状态。

-------------请求参数说明-------------
deviceId: [string]，设备序列号
clientLocalTime：[String]，客户端握手成功后信令发送的本地系统时间，yyyyMMddTHHmmss格式。
--------------

-------------响应参数说明-------------
time: [int]，响铃倒计时剩余时间，单位为秒，若为-1则表示未响铃
whiteLight：[string]，白光灯开关状态，on-开启，off-关闭，[PaaS 可选]，由于app组件库实现问题，不支持可选，[SaaS 必选]设备未返回时，服务置为unknown。
clientLocalTime：[String]，app发送的本地系统时间，yyyyMMddTHHmmss格式,如20180301T111730，将Req的值原样带回。
--------------

-------------附加说明-------------
客户端根据握手成功后的信令发送时间t1、回复收到的时间t2，得到差值，除以2后四舍五入精确到秒，再用s剩余的倒计时时间减去该值。
如(t2 - t1) / 2后的结果若为4.5，则四舍五入为5，倒计时从25开始；若为4.4，则四舍五入为4，倒计时从26开始
--------------

参考PaaS协议：[获取警笛状态](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%AD%A6%E7%AC%9B%E6%93%8D%E4%BD%9C%2F%E8%8E%B7%E5%8F%96%E8%AD%A6%E7%AC%9B%E7%8A%B6%E6%80%81.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_QuerySirenRequest 
{
	HsviewRequest base;

	struct thingsControl_QuerySirenRequestData
	{
		
		/** 客户端握手成功后信令发送的本地系统时间，yyyyMMddTHHmmss格式 */
		CSTR clientLocalTime;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsControl_QuerySirenRequest;

C_API thingsControl_QuerySirenRequest *HSAPI_INIT(thingsControl_QuerySirenRequest);

typedef struct thingsControl_QuerySirenResponse 
{
	HsviewResponse base;

	struct thingsControl_QuerySirenResponseData
	{
		
		/** 本地系统时间，yyyyMMddTHHmmss格式,如20180301T111730，将Req的值原样带回 */
		CSTR clientLocalTime;
		/** 白光灯开关状态，on-开启，off-关闭 */
		CSTR whiteLight;
		/** [int]响铃倒计时时间，单位为秒 */
		int time;
 
	} data;

} thingsControl_QuerySirenResponse;

C_API thingsControl_QuerySirenResponse *HSAPI_INIT(thingsControl_QuerySirenResponse);

#endif
