/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferOpenDoor_H_
#define _HSVIEW_CLIENT_API_TransferOpenDoor_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
门口机开锁

响应内容说明参考PaaS协议：[门口机开锁](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E5%8F%A3%E6%9C%BA%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E5%BC%80%E9%94%81.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct TransferOpenDoorRequest 
{
	HsviewRequest base;

	struct TransferOpenDoorRequestData
	{
		
		/** 通道ID */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} TransferOpenDoorRequest;

C_API TransferOpenDoorRequest *HSAPI_INIT(TransferOpenDoorRequest);

typedef struct TransferOpenDoorResponse 
{
	HsviewResponse base;

	struct TransferOpenDoorResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TransferOpenDoorResponse;

C_API TransferOpenDoorResponse *HSAPI_INIT(TransferOpenDoorResponse);

#endif
