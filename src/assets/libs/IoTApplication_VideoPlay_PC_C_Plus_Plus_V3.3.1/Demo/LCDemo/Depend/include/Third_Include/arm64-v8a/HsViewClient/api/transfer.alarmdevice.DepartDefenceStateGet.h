/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarmdevice_DepartDefenceStateGet_H_
#define _HSVIEW_CLIENT_API_transferAlarmdevice_DepartDefenceStateGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取防拆状态

配件防拆状态能力集SASQ

参考PaaS协议：[获取防拆状态](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%93%8D%E4%BD%9C%E9%85%8D%E4%BB%B6%2F%E8%8E%B7%E5%8F%96%E9%98%B2%E6%8B%86%E7%8A%B6%E6%80%81.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarmdevice_DepartDefenceStateGetRequest 
{
	HsviewRequest base;

	struct transferAlarmdevice_DepartDefenceStateGetRequestData
	{
		
		/** [cstr]/device/alarmdevice/sensor-state/ */
		#define _STATIC_transferAlarmdevice_DepartDefenceStateGetRequestData_url "/device/alarmdevice/sensor-state/"
		CSTR url;
		/** 配件ID */
		CSTR accessoryId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarmdevice_DepartDefenceStateGetRequest;

C_API transferAlarmdevice_DepartDefenceStateGetRequest *HSAPI_INIT(transferAlarmdevice_DepartDefenceStateGetRequest);

typedef struct transferAlarmdevice_DepartDefenceStateGetResponse 
{
	HsviewResponse base;

	struct transferAlarmdevice_DepartDefenceStateGetResponseData
	{
		
		/** 防拆状态：on：开,off：关 */
		CSTR type;
 
	} data;

} transferAlarmdevice_DepartDefenceStateGetResponse;

C_API transferAlarmdevice_DepartDefenceStateGetResponse *HSAPI_INIT(transferAlarmdevice_DepartDefenceStateGetResponse);

#endif
