/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ExShareDeviceAdd_H_
#define _LC_OPENAPI_CLIENT_ExShareDeviceAdd_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备分享,支持分享给单个或多个用户 
functions详细描述： 
	realtime：视频查看权限
	videoMonitor：视频控制权限
	alarmMsg：报警消息查看 
	alarmManage：报警消息管理 
	localVideoRecord：本地录像查看 
	videoRecord：云录像查看 
	cloudRecordManage：云录像管理 
	configure：基础配置管理 
	seniorConfigure：高级配置管理 
	functions为空，取默认值："realtime,videoMonitor,alarmMsg,videoRecord,localVideoRecord"
 */

typedef struct ExShareDeviceAddRequest 
{
	LCOpenApiRequest base;

	struct ExShareDeviceAddRequestData
	{
		
		/** 分享的功能 */
		CSTR functions;
		/** 被分享账号 */
		CSTR account;
		/** 授权token */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} ExShareDeviceAddRequest;

C_API ExShareDeviceAddRequest *LCOPENAPI_INIT(ExShareDeviceAddRequest);

typedef struct ExShareDeviceAddResponse 
{
	LCOpenApiResponse base;

	struct ExShareDeviceAddResponseData
	{
		
		/** 可选 用户ID,被分享用户为一个人时返回 */
		CSTR userId;
 
	} data;

} ExShareDeviceAddResponse;

C_API ExShareDeviceAddResponse *LCOPENAPI_INIT(ExShareDeviceAddResponse);

#endif
