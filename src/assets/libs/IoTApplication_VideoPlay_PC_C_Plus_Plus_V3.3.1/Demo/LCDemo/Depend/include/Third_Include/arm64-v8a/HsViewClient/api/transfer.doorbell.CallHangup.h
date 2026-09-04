/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDoorbell_CallHangup_H_
#define _HSVIEW_CLIENT_API_transferDoorbell_CallHangup_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
呼叫挂断

参考PaaS协议：[呼叫挂断](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E5%8F%A3%E6%9C%BA%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E6%8C%82%E6%96%AD.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDoorbell_CallHangupRequest 
{
	HsviewRequest base;

	struct transferDoorbell_CallHangupRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/call/hangup */
		#define _STATIC_transferDoorbell_CallHangupRequestData_url "/device/call/hangup"
		CSTR url;

	} data;

} transferDoorbell_CallHangupRequest;

C_API transferDoorbell_CallHangupRequest *HSAPI_INIT(transferDoorbell_CallHangupRequest);

typedef struct transferDoorbell_CallHangupResponse 
{
	HsviewResponse base;

	struct transferDoorbell_CallHangupResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDoorbell_CallHangupResponse;

C_API transferDoorbell_CallHangupResponse *HSAPI_INIT(transferDoorbell_CallHangupResponse);

#endif
