/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SubscribeZBDeviceDiscovery_H_
#define _HSVIEW_CLIENT_API_SubscribeZBDeviceDiscovery_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
向配件订阅发现消息。
SubscribeID：订阅ID，是PhoneID 
推送新配件设备需携带订阅ID。设备在同一时间只维护一个订阅事件。
注明：增加超时时间参数，超时设备自动取消订阅。超时指的是在连续时间内没有任何相应的行为（添加、拒绝等）。
 */

typedef struct SubscribeZBDeviceDiscoveryRequest 
{
	HsviewRequest base;

	struct SubscribeZBDeviceDiscoveryRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SubscribeZBDeviceDiscoveryRequestData_METHOD "POST"
		/** [cstr]ihg-cmd/subscribeZBDeviceDiscovery */
		#define _STATIC_SubscribeZBDeviceDiscoveryRequestData_CMD "ihg-cmd/subscribeZBDeviceDiscovery"
		/** struct of SubscribeZBDeviceDiscoveryRequestData_Body */
		struct SubscribeZBDeviceDiscoveryRequestData_Body {
			/** 订阅ID，是PhoneID */
			CSTR SubscribeID;
			/** [int]超时时间(sec) */
			int TimeoutPeriod;
		} body;

	} data;

} SubscribeZBDeviceDiscoveryRequest;

C_API SubscribeZBDeviceDiscoveryRequest *HSAPI_INIT(SubscribeZBDeviceDiscoveryRequest);

typedef struct SubscribeZBDeviceDiscoveryResponse 
{
	HsviewResponse base;

	struct SubscribeZBDeviceDiscoveryResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SubscribeZBDeviceDiscoveryResponse;

C_API SubscribeZBDeviceDiscoveryResponse *HSAPI_INIT(SubscribeZBDeviceDiscoveryResponse);

#endif
