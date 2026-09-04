/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_RemoteDebugGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_RemoteDebugGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
远程调试使能查询


------------响应参数说明------------
log: [string], "on"开启日志上传， "off" 关闭
debug: [string]，可选，"on"开启调试日志上传， "off" 关闭, 客户端统一为"off", 仅允许公有云后台系统打开, 并且接入库实现时每次重启后重置为"off"
level: [string]，可选，日志等级
debug:调试级别
info:重要级别
warn:警告级别
error:错误级别
logCloud：[string]，可选，日志直存是否开启
-----------------------------------

参考PaaS协议：[远程调试使能查询](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%BF%9C%E7%A8%8B%E8%B0%83%E8%AF%95%2F%E8%BF%9C%E7%A8%8B%E8%B0%83%E8%AF%95%E4%BD%BF%E8%83%BD%E6%9F%A5%E8%AF%A2.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_RemoteDebugGetRequest 
{
	HsviewRequest base;

	struct transferDevice_RemoteDebugGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/remotedebug/query */
		#define _STATIC_transferDevice_RemoteDebugGetRequestData_url "/device/remotedebug/query"
		CSTR url;

	} data;

} transferDevice_RemoteDebugGetRequest;

C_API transferDevice_RemoteDebugGetRequest *HSAPI_INIT(transferDevice_RemoteDebugGetRequest);

typedef struct transferDevice_RemoteDebugGetResponse 
{
	HsviewResponse base;

	struct transferDevice_RemoteDebugGetResponseData
	{
		
		/** [O]日志等级debug:调试级别info:重要级别warn:警告级别error:错误级别 */
		CSTR level;
		/** 设备日志上传开关，on-开启，off-关闭 */
		CSTR log;
		/** [O]设备调试日志开关，on-开启，off-关闭，客户端统一为off */
		CSTR debug;
		/** [O]日志直存是否开启 */
		CSTR logCloud;
 
	} data;

} transferDevice_RemoteDebugGetResponse;

C_API transferDevice_RemoteDebugGetResponse *HSAPI_INIT(transferDevice_RemoteDebugGetResponse);

#endif
