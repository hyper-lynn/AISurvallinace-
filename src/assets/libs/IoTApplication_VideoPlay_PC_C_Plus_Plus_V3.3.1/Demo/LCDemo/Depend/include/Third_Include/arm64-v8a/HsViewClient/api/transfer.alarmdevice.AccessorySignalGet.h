/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarmdevice_AccessorySignalGet_H_
#define _HSVIEW_CLIENT_API_transferAlarmdevice_AccessorySignalGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取配件信号强度

参考PaaS协议：[获取配件信号强度](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%93%8D%E4%BD%9C%E9%85%8D%E4%BB%B6%2F%E8%8E%B7%E5%8F%96%E9%85%8D%E4%BB%B6%E4%BF%A1%E5%8F%B7%E5%BC%BA%E5%BA%A6.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarmdevice_AccessorySignalGetRequest 
{
	HsviewRequest base;

	struct transferAlarmdevice_AccessorySignalGetRequestData
	{
		
		/** [cstr]/device/alarmdevice/signal */
		#define _STATIC_transferAlarmdevice_AccessorySignalGetRequestData_url "/device/alarmdevice/signal"
		CSTR url;
		/** struct of transferAlarmdevice_AccessorySignalGetRequestData_Content */
		struct transferAlarmdevice_AccessorySignalGetRequestData_Content {
			/** 配件ID */
			DECLARE_LIST(CSTR) accessoryId;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarmdevice_AccessorySignalGetRequest;

C_API transferAlarmdevice_AccessorySignalGetRequest *HSAPI_INIT(transferAlarmdevice_AccessorySignalGetRequest);

typedef struct transferAlarmdevice_AccessorySignalGetResponse 
{
	HsviewResponse base;

	struct transferAlarmdevice_AccessorySignalGetResponseData
	{
		
		/** define a list with struct of transferAlarmdevice_AccessorySignalGetResponseData_SignalElement */
		DECLARE_LIST(struct transferAlarmdevice_AccessorySignalGetResponseData_SignalElement
		{
			/** 配件ID */
			CSTR accessoryId;
			/** [int]强度。0最弱，5最强 */
			int intensity;
		}) signal;
 
	} data;

} transferAlarmdevice_AccessorySignalGetResponse;

C_API transferAlarmdevice_AccessorySignalGetResponse *HSAPI_INIT(transferAlarmdevice_AccessorySignalGetResponse);

#endif
