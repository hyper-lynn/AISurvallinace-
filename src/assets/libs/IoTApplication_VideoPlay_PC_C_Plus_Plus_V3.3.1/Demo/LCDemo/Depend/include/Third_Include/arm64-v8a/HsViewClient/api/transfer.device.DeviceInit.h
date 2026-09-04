/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_DeviceInit_H_
#define _HSVIEW_CLIENT_API_transferDevice_DeviceInit_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
收到请求后，完成设备的初始化（采用设备程序内的SC码进行初始化）


------------请求参数说明------------
deviceId:设备序列号
-----------------------------------

参考PaaS协议：[设备初始化](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E5%A4%87%E5%90%AF%E5%8A%A8%2F%E8%AE%BE%E5%A4%87%E5%88%9D%E5%A7%8B%E5%8C%96.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_DeviceInitRequest 
{
	HsviewRequest base;

	struct transferDevice_DeviceInitRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/init */
		#define _STATIC_transferDevice_DeviceInitRequestData_url "/device/init"
		CSTR url;

	} data;

} transferDevice_DeviceInitRequest;

C_API transferDevice_DeviceInitRequest *HSAPI_INIT(transferDevice_DeviceInitRequest);

typedef struct transferDevice_DeviceInitResponse 
{
	HsviewResponse base;

	struct transferDevice_DeviceInitResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_DeviceInitResponse;

C_API transferDevice_DeviceInitResponse *HSAPI_INIT(transferDevice_DeviceInitResponse);

#endif
