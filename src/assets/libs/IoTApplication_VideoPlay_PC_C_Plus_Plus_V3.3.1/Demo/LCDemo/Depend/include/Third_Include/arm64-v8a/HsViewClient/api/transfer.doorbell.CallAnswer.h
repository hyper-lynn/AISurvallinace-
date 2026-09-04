/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDoorbell_CallAnswer_H_
#define _HSVIEW_CLIENT_API_transferDoorbell_CallAnswer_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
呼叫接听

参考PaaS协议：[呼叫接听](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E5%8F%A3%E6%9C%BA%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E6%8E%A5%E5%90%AC.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDoorbell_CallAnswerRequest 
{
	HsviewRequest base;

	struct transferDoorbell_CallAnswerRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/call/answer */
		#define _STATIC_transferDoorbell_CallAnswerRequestData_url "/device/call/answer"
		CSTR url;

	} data;

} transferDoorbell_CallAnswerRequest;

C_API transferDoorbell_CallAnswerRequest *HSAPI_INIT(transferDoorbell_CallAnswerRequest);

typedef struct transferDoorbell_CallAnswerResponse 
{
	HsviewResponse base;

	struct transferDoorbell_CallAnswerResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDoorbell_CallAnswerResponse;

C_API transferDoorbell_CallAnswerResponse *HSAPI_INIT(transferDoorbell_CallAnswerResponse);

#endif
