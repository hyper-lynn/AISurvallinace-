/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetDeviceSnapEnhanced_H_
#define _LC_OPENAPI_CLIENT_SetDeviceSnapEnhanced_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备抓图。建议开发者根据设备性能实测接口后，来确定使用哪个设备抓图接口：
若设备性能较好（每秒都可以处理并返回抓图图片），则建议开发者调用setDeviceSnapEnhanced接口；
若设备性能较差（主要针对2017年前上市的设备），则建议开发者调用setDeviceSnap接口进行设备抓图；
注：客户端请求时间间隔需大于等于1s，若客户端请求时间间隔小于1s，默认返回上一次抓图图片。返回结果中，抓图访问地址（url）7天内有效。
 */

typedef struct SetDeviceSnapEnhancedRequest 
{
	LCOpenApiRequest base;

	struct SetDeviceSnapEnhancedRequestData
	{
		
		/** [cstr]setDeviceSnapEnhanced */
		#define _STATIC_SetDeviceSnapEnhancedRequestData_method "setDeviceSnapEnhanced"
		CSTR method;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetDeviceSnapEnhancedRequest;

C_API SetDeviceSnapEnhancedRequest *LCOPENAPI_INIT(SetDeviceSnapEnhancedRequest);

typedef struct SetDeviceSnapEnhancedResponse 
{
	LCOpenApiResponse base;

	struct SetDeviceSnapEnhancedResponseData
	{
		
		/** 抓图访问地址 */
		CSTR url;
 
	} data;

} SetDeviceSnapEnhancedResponse;

C_API SetDeviceSnapEnhancedResponse *LCOPENAPI_INIT(SetDeviceSnapEnhancedResponse);

#endif
