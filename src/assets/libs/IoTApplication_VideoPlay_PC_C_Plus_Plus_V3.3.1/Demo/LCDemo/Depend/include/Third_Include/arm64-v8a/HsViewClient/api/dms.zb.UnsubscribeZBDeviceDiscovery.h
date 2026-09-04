/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UnsubscribeZBDeviceDiscovery_H_
#define _HSVIEW_CLIENT_API_UnsubscribeZBDeviceDiscovery_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据订阅ID取消某个配件的发现消息订阅。
 */

typedef struct UnsubscribeZBDeviceDiscoveryRequest 
{
	HsviewRequest base;

	struct UnsubscribeZBDeviceDiscoveryRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_UnsubscribeZBDeviceDiscoveryRequestData_METHOD "POST"
		/** [cstr]ihg-cmd/unsubscribeZBDeviceDiscovery */
		#define _STATIC_UnsubscribeZBDeviceDiscoveryRequestData_CMD "ihg-cmd/unsubscribeZBDeviceDiscovery"
		/** struct of UnsubscribeZBDeviceDiscoveryRequestData_Body */
		struct UnsubscribeZBDeviceDiscoveryRequestData_Body {
			/** 订阅ID，是PhoneID */
			CSTR SubscribeID;
		} body;

	} data;

} UnsubscribeZBDeviceDiscoveryRequest;

C_API UnsubscribeZBDeviceDiscoveryRequest *HSAPI_INIT(UnsubscribeZBDeviceDiscoveryRequest);

typedef struct UnsubscribeZBDeviceDiscoveryResponse 
{
	HsviewResponse base;

	struct UnsubscribeZBDeviceDiscoveryResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UnsubscribeZBDeviceDiscoveryResponse;

C_API UnsubscribeZBDeviceDiscoveryResponse *HSAPI_INIT(UnsubscribeZBDeviceDiscoveryResponse);

#endif
