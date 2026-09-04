/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_DoorLockStateQuery_H_
#define _HSVIEW_CLIENT_API_transferDevice_DoorLockStateQuery_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
门锁状态获取

参考PaaS协议：[门锁状态获取](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E9%97%A8%E9%94%81%E7%9B%B8%E5%85%B3%2F%E9%97%A8%E9%94%81%E7%8A%B6%E6%80%81%E8%8E%B7%E5%8F%96.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_DoorLockStateQueryRequest 
{
	HsviewRequest base;

	struct transferDevice_DoorLockStateQueryRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/doorlock/state/query */
		#define _STATIC_transferDevice_DoorLockStateQueryRequestData_url "/device/doorlock/state/query"
		CSTR url;

	} data;

} transferDevice_DoorLockStateQueryRequest;

C_API transferDevice_DoorLockStateQueryRequest *HSAPI_INIT(transferDevice_DoorLockStateQueryRequest);

typedef struct transferDevice_DoorLockStateQueryResponse 
{
	HsviewResponse base;

	struct transferDevice_DoorLockStateQueryResponseData
	{
		
		/** 门锁状态, falseLock：假锁，beClosed：已关，notClosed：未关，antiLock：反锁 */
		CSTR state;
		/** [O]door 为空或者不存在代表门状态  door:门状态  lock: 锁状态 */
		CSTR objectType;
 
	} data;

} transferDevice_DoorLockStateQueryResponse;

C_API transferDevice_DoorLockStateQueryResponse *HSAPI_INIT(transferDevice_DoorLockStateQueryResponse);

#endif
