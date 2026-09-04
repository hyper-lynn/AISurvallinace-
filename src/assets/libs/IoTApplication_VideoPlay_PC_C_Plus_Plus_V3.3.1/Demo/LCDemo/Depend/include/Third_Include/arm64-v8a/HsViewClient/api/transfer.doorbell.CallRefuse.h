/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDoorbell_CallRefuse_H_
#define _HSVIEW_CLIENT_API_transferDoorbell_CallRefuse_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备拒接

参考PaaS协议：[设备拒接](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E5%8F%A3%E6%9C%BA%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E6%8B%92%E6%8E%A5.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDoorbell_CallRefuseRequest 
{
	HsviewRequest base;

	struct transferDoorbell_CallRefuseRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/call/refuse */
		#define _STATIC_transferDoorbell_CallRefuseRequestData_url "/device/call/refuse"
		CSTR url;

	} data;

} transferDoorbell_CallRefuseRequest;

C_API transferDoorbell_CallRefuseRequest *HSAPI_INIT(transferDoorbell_CallRefuseRequest);

typedef struct transferDoorbell_CallRefuseResponse 
{
	HsviewResponse base;

	struct transferDoorbell_CallRefuseResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDoorbell_CallRefuseResponse;

C_API transferDoorbell_CallRefuseResponse *HSAPI_INIT(transferDoorbell_CallRefuseResponse);

#endif
