/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_StartSiren_H_
#define _HSVIEW_CLIENT_API_thingsControl_StartSiren_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
开启警笛。

-------------请求参数说明-------------
deviceId: [string]，设备序列号
clientLocalTime：[String]，客户端握手成功后信令发送的本地系统时间，yyyyMMddTHHmmss格式。
--------------

-------------响应参数说明-------------
time: [int]，响铃倒计时时间，单位为秒
clientLocalTime：[String]，app发送的本地系统时间，yyyyMMddTHHmmss格式,如20180301T111730，将Req的值原样带回。
--------------

-------------附加说明-------------
客户端根据握手成功后的信令发送时间t1、回复收到的时间t2，得到差值，除以2后四舍五入精确到秒，再用s剩余的倒计时时间减去该值。
如(t2 - t1) / 2后的结果若为4.5，则四舍五入为5，倒计时从25开始；若为4.4，则四舍五入为4，倒计时从26开始
--------------

参考PaaS协议：[开启警笛](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%AD%A6%E7%AC%9B%E6%93%8D%E4%BD%9C%2F%E5%BC%80%E5%90%AF%E8%AD%A6%E7%AC%9B.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_StartSirenRequest 
{
	HsviewRequest base;

	struct thingsControl_StartSirenRequestData
	{
		
		/** 客户端握手成功后信令发送的本地系统时间，yyyyMMddTHHmmss格式 */
		CSTR clientLocalTime;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsControl_StartSirenRequest;

C_API thingsControl_StartSirenRequest *HSAPI_INIT(thingsControl_StartSirenRequest);

typedef struct thingsControl_StartSirenResponse 
{
	HsviewResponse base;

	struct thingsControl_StartSirenResponseData
	{
		
		/** [int]响铃倒计时时间，单位为秒 */
		int time;
		/** 本地系统时间，yyyyMMddTHHmmss格式,如20180301T111730，将Req的值原样带回 */
		CSTR clientLocalTime;
 
	} data;

} thingsControl_StartSirenResponse;

C_API thingsControl_StartSirenResponse *HSAPI_INIT(thingsControl_StartSirenResponse);

#endif
