/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarmdevice_DoorsensorStateGet_H_
#define _HSVIEW_CLIENT_API_transferAlarmdevice_DoorsensorStateGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取门磁开门关门状态

参考PaaS协议：[获取门磁开门关门状态](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%93%8D%E4%BD%9C%E9%85%8D%E4%BB%B6%2F%E8%8E%B7%E5%8F%96%E9%97%A8%E7%A3%81%E5%BC%80%E9%97%A8%E5%85%B3%E9%97%A8%E7%8A%B6%E6%80%81.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarmdevice_DoorsensorStateGetRequest 
{
	HsviewRequest base;

	struct transferAlarmdevice_DoorsensorStateGetRequestData
	{
		
		/** [cstr]/device/alarmdevice/open-close-state/ */
		#define _STATIC_transferAlarmdevice_DoorsensorStateGetRequestData_url "/device/alarmdevice/open-close-state/"
		CSTR url;
		/** 配件ID */
		CSTR accessoryId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarmdevice_DoorsensorStateGetRequest;

C_API transferAlarmdevice_DoorsensorStateGetRequest *HSAPI_INIT(transferAlarmdevice_DoorsensorStateGetRequest);

typedef struct transferAlarmdevice_DoorsensorStateGetResponse 
{
	HsviewResponse base;

	struct transferAlarmdevice_DoorsensorStateGetResponseData
	{
		
		/** 开门关门状态：open：开,close：关 */
		CSTR type;
 
	} data;

} transferAlarmdevice_DoorsensorStateGetResponse;

C_API transferAlarmdevice_DoorsensorStateGetResponse *HSAPI_INIT(transferAlarmdevice_DoorsensorStateGetResponse);

#endif
